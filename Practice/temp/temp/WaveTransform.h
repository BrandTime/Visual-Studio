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
	Mat WDT(const Mat &_src, const string _wname, const int _level);//小波分解
	Mat IWDT(const Mat &_src, const string _wname, const int _level);//小波重构
	void wavelet_D(const string _wname, Mat &_lowFilter, Mat &_highFilter);//分解包
	void wavelet_R(const string _wname, Mat &_lowFilter, Mat &_highFilter);//重构包
	Mat waveletDecompose(const Mat &_src, const Mat &_lowFilter, const Mat &_highFilter);
	Mat waveletReconstruct(const Mat &_src, const Mat &_lowFilter, const Mat &_highFilter);
};
#endif