/*
 *
 */

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

int main (int argc, char **argv)
{
	VideoCapture video(0);
	video.set(CV_CAP_PROP_FRAME_WIDTH, 640);
	video.set(CV_CAP_PROP_FRAME_HEIGHT, 480);

	Mat image, hsv, hv(180, 256, CV_8UC1), hs(180, 256, CV_8UC1);
	vector<Mat> channels;

	for (bool loop = video.isOpened(); loop; )
	{
		video >> image;
		imshow("Input", image);

		switch (waitKey(10))
		{
		case 'q':
			loop = false;
			break;
		}
		cvtColor(image, hsv, CV_BGR2HSV);
		split(hsv, channels);

		hv.setTo(Scalar(0));
		hs.setTo(Scalar(0));
		for (int y = 0; y < hsv.rows; y++)
		{
			Point3_<uchar> *row = hsv.ptr< Point3_<uchar> >(y);
			for (int x = 0; x < hsv.cols; x++)
			{
				uchar h = row[x].x;
				uchar s = row[x].y;
				uchar v = row[x].z;
				uchar count = hv.at<uchar>(Point(h, v));
				if (count < 255)
				{
					hv.at<uchar>(Point(h, v))++;
				}
				count = hs.at<uchar>(Point(h, s));
				if (count < 255)
				{
					hs.at<uchar>(Point(h, s))++;
				}
			}
		}
		imshow("Hue-Val", hv);
		imshow("Hue-Sat", hs);
		imshow("Hue", channels[0] * 1.4);

	}

}
