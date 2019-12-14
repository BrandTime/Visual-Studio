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
	Mat img = imread("../yellowImg.bmp");
	example2_5(img);

	return 0;
}