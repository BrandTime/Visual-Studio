#ifndef _HUFFMAN_COMPRESS_
#define _HUFFMAN_COMPRESS_
#include"huffman_tree.h"

struct BufferType {
	char ch;
	unsigned int bits;

	BufferType() :ch(0), bits(0) {};
};
class HuffmanCompress {
protected:
	HuffmanTree<char, unsigned long> *pHuffmanTree;
	FILE *infp, *outfp;
	BufferType buf;
	
	void Write(unsigned int bit);//��Ŀ���ļ���д��һ������
	void WriteToOutfp();//ǿ��д��Ŀ���ļ�
public:
	HuffmanCompress();
	HuffmanCompress(const HuffmanCompress& copy);
	HuffmanCompress& operator=(const HuffmanCompress& copy);
	virtual ~HuffmanCompress();
	void EnCompress();//ѹ��
	void DeCompress();//��ѹ��
};

HuffmanCompress::~HuffmanCompress() {
	delete[]pHuffmanTree;
	delete infp;
	delete outfp;
	buf.bits = 0;
	buf.ch = 0;
}
HuffmanCompress& HuffmanCompress::operator=(const HuffmanCompress& copy) {
	if (&copy != this) {
		if (pHuffmanTree)
			delete[]pHuffmanTree;
		if (infp)
			delete infp;
		if (outfp)
			delete outfp;
		buf.bits = copy.buf.bits;
		buf.ch = copy.buf.ch;
		infp = copy.infp;
		outfp = copy.outfp;
		pHuffmanTree = new HuffmanTree<char, unsigned long>(*(copy.pHuffmanTree));
	}
	return *this;
}
HuffmanCompress::HuffmanCompress(const HuffmanCompress& copy) {
	if (pHuffmanTree)
		delete[]pHuffmanTree;
	if (infp)
		delete infp;
	if (outfp)
		delete outfp;
	buf.bits = copy.buf.bits;
	buf.ch = copy.buf.ch;
	infp = copy.infp;
	outfp = copy.outfp;
	pHuffmanTree = new HuffmanTree<char, unsigned long>(*(copy.pHuffmanTree));
}
void HuffmanCompress::DeCompress() {
	char infName[256], outfName[256];
	cout << "���������ѹ���ļ�����" << endl;
	cin >> infName;
	if ((infp = fopen(infName, "rb")) == nullptr)
		throw runtime_error("Դ�ļ���ʧ��");
	fgetc(infp);
	if (feof(infp))
		throw runtime_error("Դ�ļ�Ϊ���ļ�");
	cout << "������Ŀ���ļ�����" << endl;
	cin >> outfName;
	if ((outfp = fopen(outfName, "wb")) == nullptr)
		throw runtime_error("Ŀ���ļ���ʧ��");

	const unsigned long n = 256;
	char ch[n];
	unsigned long w[256];
	unsigned long size = 0, i = 0;
	char cha;
	rewind(infp);
	fread(&size, sizeof(unsigned long), 1,infp);
	fread(&w, sizeof(unsigned long), n, infp);
	for (; i < n; ++i)
		ch[i] = (char)i;
	if (pHuffmanTree)
		delete[]pHuffmanTree;
	pHuffmanTree = new HuffmanTree<char, unsigned long>(ch, w, n);
	rewind(outfp);
	cha = fgetc(infp);
	unsigned long len = 0;//Ŀǰ��ת�����ַ���
	while (!feof(infp)) {
		string strTmp = "";
		unsigned char c = (unsigned char)cha;
		for (i = 0; i < 8; ++i) {
			if (c >= 128)
				strTmp.push_back('1');
			else
				strTmp.push_back('0');
			c = c << 1;
		}
		vector<char> temp = pHuffmanTree->Decode(strTmp);
		string strTemp=VecToString(temp);
		for (auto j : strTemp) {
			++len;
			fputc(j, outfp);
			if (len == size)
				break;
		}
		if (len == size)
			break;
		cha = fgetc(infp);
	}

	fclose(infp);
	fclose(outfp);
	cout << "�������" << endl;
	return;
}
void HuffmanCompress::EnCompress() {
	char inFileName[256], outFileName[256];
	cout << "��������ѹ�����ļ�����" << endl;
	cin >> inFileName;
	if ((infp = fopen(inFileName, "rb")) == nullptr)
		throw runtime_error("�����ļ���ʧ��");
	fgetc(infp);
	if (feof(infp))
		throw runtime_error("�������ļ�");
	cout << "������ѹ������ļ�����" << endl;
	cin >> outFileName;
	if ((outfp = fopen(outFileName,"wb")) == nullptr)
		throw runtime_error("����ļ���ʧ��");
	cout << "�����С���" << endl;

	const unsigned long n = 256;
	unsigned long w[n];//�ַ����ֵĴ���
	char ch[n];
	char cha;
	unsigned long i=0, size=0;
	for (; i < n; ++i) {
		w[i] = 0;
		ch[i] = (char)i;
	}
	rewind(infp);
	cha = fgetc(infp);
	while (!feof(infp)) {
		++size;
		w[(unsigned char)cha]++;
		cha = fgetc(infp);
	}
	if (pHuffmanTree)
		delete[]pHuffmanTree;
	pHuffmanTree = new HuffmanTree<char, unsigned long>(ch, w, n);
	rewind(outfp);
	fwrite(&size, sizeof(unsigned long), 1, outfp);
	fwrite(&w, sizeof(unsigned long), n, outfp);
	buf.bits = 0;
	buf.ch = 0;
	rewind(infp);
	cha = fgetc(infp);
	while (!feof(infp)) {
		string temp = pHuffmanTree->Encode(cha);
		for (auto j : temp) {
			if (j == '0')
				Write(0);
			else
				Write(1);
		}
		cha = fgetc(infp);
	}
	WriteToOutfp();

	fclose(infp);
	fclose(outfp);
	cout << "�������" << endl;
	return;
}
HuffmanCompress::HuffmanCompress() :pHuffmanTree(nullptr),
	infp(nullptr), outfp(nullptr) {};
void HuffmanCompress::Write(unsigned int bit) {
	buf.bits++;
	buf.ch = (buf.ch << 1) | bit;
	if (buf.bits == 8) {
		fputc(buf.ch, outfp);
		buf.bits = 0;
		buf.ch = 0;
	}
	return;
}
void HuffmanCompress::WriteToOutfp() {
	unsigned int len = buf.bits;
	for (unsigned int i = 0; i < 8 - len; ++i)
		buf.ch = buf.ch << 1;
	fputc(buf.ch, outfp);
	buf.bits = 0;
	buf.ch = 0;
	return;
}
//debug program
#if 0
#include"Huffman_compress.h"

template<class WeightType>
void Visit(WeightType &w) {
	cout << w;
	return;
}
int main(void) {
	try {
		HuffmanCompress compress, compress1;
		compress.EnCompress();
		compress1 = compress;
		compress1.DeCompress();
	}
	catch (runtime_error &err) {
		cout << err.what() << endl;
	}

	system("PAUSE");
	return 0;
}
#endif
#endif // !_HUFFMAN_COMPRESS_