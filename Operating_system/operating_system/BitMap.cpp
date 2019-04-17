#include "BitMap.h"
#include <math.h>
#include <stdio.h>

void createEmptyBitMap(SBitMap& voBitMap, int vNumTotalBits){
	voBitMap.NumBits  = vNumTotalBits;
	int NumWords = (int)ceil(vNumTotalBits / (double)g_NumBitsInWord);
	voBitMap.pMapData = new int[NumWords];

	for (int i=0; i<NumWords; ++i) voBitMap.pMapData[i] = 0;
}

void markBitAt(int vBitPosition, SBitMap& vioBitMap) { 
	vioBitMap.pMapData[vBitPosition / g_NumBitsInWord] |= 1 << (vBitPosition % g_NumBitsInWord);
}

void clearBitAt(int vBitPosition, SBitMap& vioBitMap) {
	vioBitMap.pMapData[vBitPosition / g_NumBitsInWord] &= 0 << (vBitPosition%g_NumBitsInWord);
}

bool isAvailableBitAt(int vBitPosition, const SBitMap& vBitMap){
	int n = 0;
	n = (vBitMap.pMapData[vBitPosition / g_NumBitsInWord] & (1 << (vBitPosition%g_NumBitsInWord)));
	if (n==1)
		return true;
	else
		return false;
}
int findAndSetAvailableBit(SBitMap& voBitMap) {
	for (short i = 0; i < voBitMap.NumBits; ++i)
		if (isAvailableBitAt(i, voBitMap)) {
			//voBitMap.pMapData[i] = 0;
			return i;
		}
	return -1;
}
int countClearBits(const SBitMap& vBitMap){
	int n = 0;
	for (int i = 0; i < vBitMap.NumBits; ++i) {
		if (isAvailableBitAt(i, vBitMap))
			++n;
	}
	return n;
}

void printfBitMap(const SBitMap& vBitMap)
{
	for (int i=0; i<vBitMap.NumBits; ++i) 
	{
		if (isAvailableBitAt(i, vBitMap)) printf("0 ");
		else printf("1 "); 
	}
	printf("\n"); 
}