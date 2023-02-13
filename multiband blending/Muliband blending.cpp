
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
const int PYR_LEVEL = 30; //loop문의 범위를 나타내는 변수의 경우 상수(최소 변수)로 선언하는게 수정하기 편함.

std::vector<Mat> buildGaussianPyramid(const Mat& mask) {
	std::vector<Mat> GaussianPyramid(PYR_LEVEL); //Mat type의 벡터 선언
	GaussianPyramid[0] = mask;
	for (int i = 1; i < PYR_LEVEL; i++) {
		pyrDown(GaussianPyramid[i - 1], GaussianPyramid[i]); //pryDown(input,output)
	}
	return GaussianPyramid;
}//이 함수는 벡터를 만들고 거기에 mask로 시작하여금 가우시안 피라미드를 만드는 역할만 함.

std::vector<Mat> buildLaplacianpyramid(const Mat& src) {
	std::vector<Mat> Laplacianpyramid(PYR_LEVEL);
	Laplacianpyramid[0] = src;
	for (int i = 1; i < PYR_LEVEL; i++) {
		pyrDown(Laplacianpyramid[i - 1], Laplacianpyramid[i]); //i-1 전단계. i 현재 다루는거

		Mat temp;
		pyrUp(Laplacianpyramid[i], temp, Laplacianpyramid[i - 1].size() ); //인풋.아웃풋,사이즈 -> 인풋을 사이즈 크기로 바꿔 아웃풋에 넣음.
		Laplacianpyramid[i - 1] -= temp;
	}
	return Laplacianpyramid;
}

Mat reconstruct(const std::vector<Mat>& mask, const std::vector<Mat>& mask2, const std::vector<Mat>& left, const std::vector<Mat>& right) {
	std::vector<Mat> Amul(PYR_LEVEL); //for apple
	std::vector<Mat> Omul(PYR_LEVEL); //for orange
	multiply(left.back(), mask.back(), Amul.back());
	multiply(right.back(), mask2.back(), Omul.back());
	add(Amul.back(), Omul.back(), Amul.back());

	for (int i = int(left.size()) - 2; i >= 0; i--) {
		multiply(left[i], mask[i], Amul[i]);
		multiply(right[i], mask2[i], Omul[i]);
		add(Amul[i], Omul[i], Amul[i]);
	} 
	
	Mat out = Amul.back();
	for (int i = int(left.size()) - 2; i >= 0; i--) {
		pyrUp(out, out, Amul[i].size());
		out += Amul[i];
	}
	return out;
}

int main()
{
	Mat image = imread("burt_mask.png");
	Mat image2 = imread("burt_apple.png");
	Mat image3 = imread("burt_orange.png");
	Mat mask,mask2, apple, orange;


	image.convertTo(mask, CV_32F, 1/255.f); //1/255.f를 안해주면 어어어어어엄청 밝은 영역만 나옴.
	image.convertTo(mask2, CV_32F, 1 / 255.f);
	image2.convertTo(apple, CV_32F, 1 / 255.f);
	image3.convertTo(orange, CV_32F, 1 / 255.f);
	//밝기는 0부터 1까지 있으므로, RGB값을 0~1사이의 float로 바꿔주는 것.

	mask2 = Scalar(1, 1, 1) - mask; //강의시간에 0.5 0.5 0.5로 회색 더해주신거 보고 해봤는데 잘 작동. 

	std::vector<Mat> AMask = buildGaussianPyramid(mask);
	std::vector<Mat> OMask = buildGaussianPyramid(mask2);
	std::vector<Mat> AppleLaplacian = buildLaplacianpyramid(apple);
	std::vector<Mat> OrangeLaplacian = buildLaplacianpyramid(orange);

	Mat result = reconstruct(AMask,OMask, AppleLaplacian, OrangeLaplacian);
	imshow("resule", result);
	//imshow("mask2", mask2);

	waitKey();
	return 0;
}

