#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

float *HOG(Mat refMat) {
	int blockSize = 16;
	int nX = refMat.cols / blockSize;
	int nY = refMat.rows / blockSize;
	int num = nX * nY;
	int bins = num * 8;
	Mat gx, gy;
	Mat mag, angle;
	Sobel(refMat, gx, CV_32F, 1, 0, 1);
	Sobel(refMat, gy, CV_32F, 0, 1, 1);
	cartToPolar(gx, gy, mag, angle, true);



	float* ref_hist = new float[bins];
	memset(ref_hist, 0, sizeof(float) * bins);


	int counts = 0;

	for (int j = 0; j < nY; j++) {
		for (int i = 0; i < nX; i++) {

			for (int a = 0; a < 16; a++) {
				for (int b = 0; b < 16; b++) {
					int angle1 = 0;
					angle1 = angle.at<float>(a, b) / 45;
					float mag1 = mag.at<float>(a, b);
					ref_hist[angle1 + counts * 8] = ref_hist[angle1 + counts * 8] + mag1;
				}
			}
			counts++;
		}
	}
	return ref_hist;
	delete[] ref_hist;
}

int main() {
	Mat src = imread("D:\\cankao.jpg");
	Mat src1 = imread("D:\\img1.jpg");
	Mat src2 = imread("D:\\img2.jpg");

	int blockSize = 16;
	int nX = src.cols / blockSize;
	int nY = src.rows / blockSize;
	int num = nX * nY;
	int bins = num * 8;

	*HOG(src);
	*HOG(src1);
	*HOG(src2);

	int res1 = 0;
	int res2 = 0;
	for (int i = 0; i < bins; i++)
	{

		res1 = res1 + abs(HOG(src)[i] - HOG(src1)[i]);
		res2 = res2 + abs(HOG(src)[i] - HOG(src2)[i]);
	}
	cout << res1 << endl;
	cout << res2 << endl;
	if (res1 < res2)
	{
		cout << "图片一与参考图片匹配度较高" << endl;
	}
	else
		cout << "图片二与参考图片匹配度较高" << endl;

	waitKey(0);
	return 0;
}