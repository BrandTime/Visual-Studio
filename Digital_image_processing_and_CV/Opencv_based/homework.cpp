#if 0
//homework 1
/*
请计算黄色部分像素个数占整个图像像素数的比例。
图片请从“资料下载”中下载作业图片homework_YellowSeg.bmp。
答案
10% ~ 13%
*/
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<iostream>
using namespace std;
using namespace cv;

int main(void) {
	Mat srcImage, dstImage;
	srcImage = imread("../yellowImg.bmp", 1);
	if (!srcImage.data) {
		printf("fff");
		return -1;
	}
	imshow("temp", srcImage);
	cvtColor(srcImage, srcImage, COLOR_BGR2GRAY);
	threshold(srcImage, dstImage, 200, 255, THRESH_BINARY);
	imshow("re", dstImage);
	int row = dstImage.rows;
	int col = dstImage.cols;
	long count = 0;
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			if (dstImage.at<uchar>(i, j) == 255)
				++count;
		}
	}
	cout << (double)count / (row*col) * 100 << endl;
	waitKey(0);
	return 0;
}

//homework 2
/*
在网站下载图片homework_boy_hist.png， 对它进行直方图均衡化增强。注意：要自己实现直方图增强的函数代码。

总代码行一般在<50行左右。

上交结果图片，也可以再用其它的图片处理，但请上交原图及处理后结果，代码，及实现过程的思路简介。

不要调用现用的函数，请自己实现直方图函数！！！！！

答案
与ppt中结果图片进行比较即可得知自己完成的效果如何。
*/
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<iostream>
using namespace std;
using namespace cv;

void equalizeHistogram(Mat &, Mat &);

int main(void) {
	Mat srcImage, dstImage;
	srcImage = imread("../boy_hist.png", 1);
	if (!srcImage.data) {
		printf("fff");
		return -1;
	}
	cvtColor(srcImage, srcImage, COLOR_BGR2GRAY);
	imshow("source image", srcImage);
	equalizeHist(srcImage, dstImage);
	imshow("Call function", dstImage);
	equalizeHistogram(srcImage, dstImage);
	imshow("implementation", dstImage);

	waitKey(0);
	return 0;
}

void equalizeHistogram(Mat& srcImage, Mat& dstImage) {
	if (!dstImage.data) {
		dstImage.create(srcImage.rows, srcImage.cols, srcImage.type());
	}
	long row = srcImage.rows;
	long col = srcImage.cols;
	int gray[256] = {};
	int newGray[256] = {};//均衡化后的灰度集
	double prob[256] = {};//probability density function
	double cum[256] = {};//cummulative distribution function
	//计算源图像灰度分布概率密度变量
	for (long i = 0; i < row; ++i) {
		for (long j = 0; j < col; ++j) {
			gray[srcImage.at<uchar>(i, j)]++;
		}
	}
	for (long i = 0; i < 256; ++i) {
		prob[i] = (double)gray[i] / (row*col);
	}

	//直方图均衡化
	for (long i = 0; i < 256; ++i) {
		if (i == 0) {
			cum[0] = prob[0];
		}
		else {
			cum[i] = cum[i - 1] + prob[i];
		}
		newGray[i] = (int)(255.0*cum[i] + 0.5);//均匀量化
	}
	//将直方图均衡化结果写到目标图像中
	for (long i = 0; i < row; ++i) {
		for (long j = 0; j < col; ++j) {
			dstImage.at<uchar>(i, j) =
				newGray[srcImage.at<uchar>(i, j)];
		}
	}
}
#endif