#if 0
#include<string>
#include<iostream>
#include<opencv.hpp>
#include <imgproc/imgproc.hpp>
using namespace cv;
using namespace std;
class WaveTransform
{
public:
	WaveTransform(void);
	~WaveTransform(void);
	Mat WDT(const Mat &_src, const string _wname, const int _level);//С���ֽ�
	Mat IWDT(const Mat &_src, const string _wname, const int _level);//С���ع�
	void wavelet_D(const string _wname, Mat &_lowFilter, Mat &_highFilter);//�ֽ��
	void wavelet_R(const string _wname, Mat &_lowFilter, Mat &_highFilter);//�ع���
	Mat waveletDecompose(const Mat &_src, const Mat &_lowFilter, const Mat &_highFilter);
	Mat waveletReconstruct(const Mat &_src, const Mat &_lowFilter, const Mat &_highFilter);
};
#endif