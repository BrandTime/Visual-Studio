#if 0
#include <memory.h>
#include <iostream>
#include "FileSystem.h"
char *pTemp;

int writeData2File(const void *vSrc, int vNumBytes, SOpenFile& vioFile) {
	if (vNumBytes == 0)
		return 0;
	if (vioFile.CurSeekPos + vNumBytes > g_MaxFileSize)
		vNumBytes = g_MaxFileSize - vioFile.CurSeekPos;
	if (vioFile.CurSeekPos + vNumBytes > vioFile.Inode.FileSize) {
		int FileLength = vioFile.Inode.FileSize;
		SBitMap DataBlockBitMap;
		createEmptyBitMap(DataBlockBitMap, g_NumBlocks);
		memcpy(DataBlockBitMap.pMapData, g_Disk, g_BlockBitMapSize);
		vioFile.Inode.FileSize = FileLength + vNumBytes;
		vioFile.Inode.NumBlocks = (int)ceil((FileLength + vNumBytes) / (double)g_BlockSize);
		if (countClearBits(DataBlockBitMap) < vioFile.Inode.NumBlocks) {
			printf("no enough space\n");
			return -1;
		}
		for (int i = 0; i < vioFile.Inode.NumBlocks; ++i) {
			vioFile.Inode.BlockNums[i] = findAndSetAvailableBit(DataBlockBitMap);
			if ((vioFile.CurSeekPos + vNumBytes) % g_BlockSize != 0) {
				int tempWriteSize = g_BlockSize - ((vioFile.CurSeekPos + vNumBytes) % g_BlockSize);
				memcpy(pTemp,pDiskDataPos,)
			}
		}
	}
}
void test(){
	formatDisk();

	SBitMap InodeBitMap;
	createEmptyBitMap(InodeBitMap, g_NumInodes);

	SBitMap DataBlockBitMap;
	createEmptyBitMap(DataBlockBitMap, g_NumBlocks);
	printf("formatDisk:\n");
	memcpy(InodeBitMap.pMapData, g_Disk+g_BlockBitMapSize, g_InodeBitMapSize);  
	memcpy(DataBlockBitMap.pMapData, g_Disk, g_BlockBitMapSize);                
	printf("Inode usage:");
	printfBitMap(InodeBitMap);
	printf("Block usage:");
	printfBitMap(DataBlockBitMap);
	printf("\n");

	createFile("a.txt", 0, 'f', g_MaxFileSize);
	printf("create file: a.txt, fileSize:%d\n", g_MaxFileSize);
	memcpy(InodeBitMap.pMapData, g_Disk+g_BlockBitMapSize, g_InodeBitMapSize);   
	memcpy(DataBlockBitMap.pMapData, g_Disk, g_BlockBitMapSize);                 
	printf("Inode usage:");
	printfBitMap(InodeBitMap);
	printf("Block usage:");
	printfBitMap(DataBlockBitMap);
	printf("\n");

	createFile("b.txt", 0, 'f', g_MaxFileSize-10);
	printf("create file: b.txt, fileSize:%d\n", g_MaxFileSize);
	memcpy(InodeBitMap.pMapData, g_Disk + g_BlockBitMapSize, g_InodeBitMapSize);  
	memcpy(DataBlockBitMap.pMapData, g_Disk, g_BlockBitMapSize);                 
	printf("Inode usage:");
	printfBitMap(InodeBitMap);
	printf("Block usage:");
	printfBitMap(DataBlockBitMap);
	printf("\n");

	createFile("c.txt", 0, 'f', g_MaxFileSize - 50);
	printf("create file: c.txt, fileSize:%d\n", g_MaxFileSize-50);
	memcpy(InodeBitMap.pMapData, g_Disk + g_BlockBitMapSize, g_InodeBitMapSize);   
	memcpy(DataBlockBitMap.pMapData, g_Disk, g_BlockBitMapSize);                 
	printf("Inode usage:");
	printfBitMap(InodeBitMap);
	printf("Block usage:");
	printfBitMap(DataBlockBitMap);
	printf("\n");

	removeFile("b.txt", 0);
	printf("remove file:b.txt\n");
	memcpy(InodeBitMap.pMapData, g_Disk + g_BlockBitMapSize, g_InodeBitMapSize);   
	memcpy(DataBlockBitMap.pMapData, g_Disk, g_BlockBitMapSize);                
	printf("Inode usage:");
	printfBitMap(InodeBitMap);
	printf("Block usage:");
	printfBitMap(DataBlockBitMap);
	printf("\n");

	SOpenFile f = *openFile("c.txt");
	char writeData[100] = "hello world";
	printf("write 'hello' to file c\n");
	writeData2File(writeData, 100, f);

	SOpenFile fr = *openFile("c.txt");
	char *readData = new char[100];

	printf("read data from file c\n");
	readDataFromFile(readData, 100, fr);
	printf("data read from a.txt:%s\n", readData);
	printf("\n");

	removeFile("a.txt", 0);
	printf("remove file: a.txt\n");
	memcpy(InodeBitMap.pMapData, g_Disk + g_BlockBitMapSize, g_InodeBitMapSize);  
	memcpy(DataBlockBitMap.pMapData, g_Disk, g_BlockBitMapSize);                 
	printf("Inode usage:");
	printfBitMap(InodeBitMap);
	printf("Block usage:");
	printfBitMap(DataBlockBitMap);
	printf("\n");

	delete InodeBitMap.pMapData;
	delete DataBlockBitMap.pMapData;
}

int main(void)
{
	test();
	system("pause");
	return 0;
} 
#endif