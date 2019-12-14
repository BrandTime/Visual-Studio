#if 0
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void example2_5(const Mat& img) {
	namedWindow("Example2_5-in", WINDOW_AUTOSIZE);
	namedWindow("Example2_5-out", WINDOW_AUTOSIZE);
	imshow("Example2_5-in", img);

	Mat out;
	GaussianBlur(img, out, Size(5, 5), 3, 3);
	GaussianBlur(out, out, Size(5, 5), 3, 3);
	imshow("Example2_5-out", out);
	waitKey(0);
	destroyAllWindows();
}

int main(void) {
	namedWindow("Example1", WINDOW_AUTOSIZE);
	namedWindow("Log_Polar", WINDOW_AUTOSIZE);
	VideoCapture cap("../temp.mp4");
	double fps = cap.get(CAP_PROP_FPS);
	Size size(
		(int)cap.get(CAP_PROP_FRAME_WIDTH),
		(int)cap.get(CAP_PROP_FRAME_HEIGHT)
	);
	VideoWriter writer;
	writer.open("../temp.avi", CV_FOURCC('M', 'J', 'P', 'G'), fps, size);
	Mat logpolar_frame, rgb_frame;
	while (1) {
		cap >> rgb_frame;
		if (rgb_frame.empty())
			break;
		imshow("Example1", rgb_frame);
		logPolar(
			rgb_frame,
			logpolar_frame,
			Point2f(
				rgb_frame.cols / 2,
				rgb_frame.rows / 2
			),
			40,
			WARP_FILL_OUTLIERS
		);
		imshow("Log_Polar", logpolar_frame);
		writer << logpolar_frame;

		char c = waitKey(10);
		if (c == 27)
			break;
	}
	cap.release();

	waitKey(0);
	return 0;
}
#endif
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<iostream>
using namespace std;
using namespace cv;

void equalizeHistogram(Mat &, Mat &);

int main(void) {
	Mat srcImage, dstImage;
	srcImage = imread("../temp.png", 1);
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

void equalizeHistogram(Mat& srcImage,Mat& dstImage) {
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
		newGray[i] = (int)(255.0*cum[i]);//均匀量化
	}
	//将直方图均衡化结果写到目标图像中
	for (long i = 0; i < row; ++i) {
		for (long j = 0; j < col; ++j) {
			dstImage.at<uchar>(i, j) =
				newGray[srcImage.at<uchar>(i, j)];
		}
	}
}