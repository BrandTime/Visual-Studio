#if 0
#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<string>
#include<fstream>
#include<memory>
using namespace cv;
using namespace std;

int g_slider_pos = 0;
int g_run = 1, g_dontset = 0;
VideoCapture g_cap;

void onTrackbarSlide(int pos, void *) {
	g_cap.set(CAP_PROP_POS_FRAMES, pos);
	if (!g_dontset)
		g_run = 1;
	g_dontset = 0;
}

int main(void) {
	cout << '\27' << endl;
	namedWindow("Example", WINDOW_AUTOSIZE);
	g_cap.open("../temp.mp4");
	int frames = (int)g_cap.get(CAP_PROP_FRAME_COUNT);
	int height = (int)g_cap.get(CAP_PROP_FRAME_HEIGHT);
	int width = (int)g_cap.get(CAP_PROP_FRAME_WIDTH);
	cout << "Video has " << frames << " frames of dimentions(" <<
		width << ", " << height << ")." << endl;
	createTrackbar("Position", "Example", &g_slider_pos, frames,
		(TrackbarCallback)onTrackbarSlide);
	Mat frame;
	while (1) {
		if (g_run != 0) {
			g_cap >> frame;
			if (frame.empty())
				break;
			int cur_pos = (int)g_cap.get(CAP_PROP_POS_FRAMES);
			g_dontset = 1;

			setTrackbarPos("Position", "Example", cur_pos);
			imshow("Example", frame);

			g_run -= 1;
		}

		char c = (char)waitKey(10);
		if (c == 's') {
			g_run = 1;
			cout << "Single step, run =" << g_run << endl;
		}
		else if (c == 'r') {
			g_run = -1;
			cout << "Run mode, run = " << g_run << endl;
		}
		else if (c == '\ESC')
			break;
	}

	destroyWindow("Example");
	return 0;
}
#endif