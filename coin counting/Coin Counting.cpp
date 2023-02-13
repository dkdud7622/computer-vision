
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;


int main(int argc, const char* argv[])
{
    Mat img_0 = imread("coins0.jpg");
    Mat img_1 = imread("coins1.jpg");
    Mat img_2 = imread("coins2.jpg");
    Mat img_3 = imread("coins3.jpg");
    Mat img_4 = imread("coins4.jpg");
    Mat img_5 = imread("coins5.jpg");

    Mat gray_0, gray_1, gray_2, gray_3, gray_4, gray_5;

    //0번
    cvtColor(img_0, gray_0, COLOR_BGR2GRAY);
    GaussianBlur(gray_0, gray_0, Size(), 2.307, 2.3);
    vector<Vec3f> circle0;
    HoughCircles(gray_0, circle0, HOUGH_GRADIENT, 1, 25, 120, 45, 30, 120 );
    //파라미터 : gray이미지, 원검출 출력을 위한 벡터, 허프 원검출 상수(허프 그래디언트),
    //해상도의 역비(dp) , minDist, 하이쓰레숄드/로우쓰레숄드/minRdius/maxRdius


    //1번
    cvtColor(img_1, gray_1, COLOR_BGR2GRAY);
    GaussianBlur(gray_1, gray_1, Size(), 2.307, 2.3);
    vector<Vec3f> circle1;
    HoughCircles(gray_1, circle1, HOUGH_GRADIENT, 1, 25, 120, 45, 30, 120);

    //2번
    cvtColor(img_2, gray_2, COLOR_BGR2GRAY);
    GaussianBlur(gray_2, gray_2, Size(), 2.307, 2.3);
    vector<Vec3f> circle2;
    HoughCircles(gray_2, circle2, HOUGH_GRADIENT, 1, 25, 120, 45, 30, 120);

    //3번
    cvtColor(img_3, gray_3, COLOR_BGR2GRAY);
    GaussianBlur(gray_3, gray_3, Size(), 2.307, 2.3);
    vector<Vec3f> circle3;
    HoughCircles(gray_3, circle3, HOUGH_GRADIENT, 1, 25, 120, 45, 30, 120);


    //4번은 정확한 값이 나오지 않습니다.
    //4번
    cvtColor(img_4, gray_4, COLOR_BGR2GRAY);
    GaussianBlur(gray_4, gray_4, Size(), 2.307, 2.3);
    vector<Vec3f> circle4;
    HoughCircles(gray_4, circle4, HOUGH_GRADIENT, 1, 25, 120, 45, 30, 120);

    //5번
    cvtColor(img_5, gray_5, COLOR_BGR2GRAY);
    GaussianBlur(gray_5, gray_5, Size(), 2.307, 2.3);
    vector<Vec3f> circle5;
    HoughCircles(gray_5, circle5, HOUGH_GRADIENT, 1, 25, 120, 45, 30, 120);
    


    //각 이미지에 원을 그리는 부분
    for (size_t i = 0; i < circle0.size(); i++) {
        Point center0(cvRound(circle0[i][0]), cvRound(circle0[i][1]));
        int radius0 = cvRound(circle0[i][2]);
        circle(img_0, center0, 3, Scalar(180, 255, 255), -1, 8, 0);
        circle(img_0, center0, radius0, Scalar(20, 255, 20), 3, 8, 0);

    }

    for (size_t i = 0; i < circle1.size(); i++) {
        Point center1(cvRound(circle1[i][0]), cvRound(circle1[i][1]));
        int radius1 = cvRound(circle1[i][2]);
        circle(img_1, center1, 3, Scalar(180, 255, 255), -1, 8, 0);
        circle(img_1, center1, radius1, Scalar(20, 255, 20), 3, 8, 0);
    }

    for (size_t i = 0; i < circle2.size(); i++) {
        Point center2(cvRound(circle2[i][0]), cvRound(circle2[i][1]));
        int radius2 = cvRound(circle2[i][2]);
        circle(img_2, center2, 3, Scalar(180, 255, 255), -1, 8, 0);
        circle(img_2, center2, radius2, Scalar(20, 255, 20), 3, 8, 0);
    }

    for (size_t i = 0; i < circle3.size(); i++) {
        Point center3(cvRound(circle3[i][0]), cvRound(circle3[i][1]));
        int radius3 = cvRound(circle3[i][2]);
        circle(img_3, center3, 3, Scalar(180, 255, 255), -1, 8, 0);
        circle(img_3, center3, radius3, Scalar(20, 255, 20), 3, 8, 0);
    }
    for (size_t i = 0; i < circle4.size(); i++) {
        Point center4(cvRound(circle4[i][0]), cvRound(circle4[i][1]));
        int radius4 = cvRound(circle4[i][2]);
        circle(img_4, center4, 3, Scalar(180, 255, 255), -1, 8, 0);
        circle(img_4, center4, radius4, Scalar(20, 255, 20), 3, 8, 0);
    }
    for (size_t i = 0; i < circle5.size(); i++) {
        Point center5(cvRound(circle5[i][0]), cvRound(circle5[i][1]));
        int radius5 = cvRound(circle5[i][2]);
        circle(img_5, center5, 3, Scalar(180, 255, 255), -1, 8, 0);
        circle(img_5, center5, radius5, Scalar(20, 255, 20), 3, 8, 0);
    }
    
    Point my_point;
    my_point.x = 30;
    my_point.y = 30;
    
    putText(img_0, to_string(circle0.size()), my_point, 4, 1.4, 255);
    putText(img_1, to_string(circle1.size()), my_point, 4, 1.4, 255);
    putText(img_2, to_string(circle2.size()), my_point, 4, 1.4, 255);
    putText(img_3, to_string(circle3.size()), my_point, 4, 1.4, 255);
    putText(img_4, to_string(circle4.size()), my_point, 4, 1.4, 255);
    putText(img_5, to_string(circle5.size()), my_point, 4, 1.4, 255);




    imshow("img0", img_0);
    imshow("img1", img_1);
    imshow("img2", img_2);
    imshow("img3", img_3);
    imshow("img4", img_4);
    imshow("img5", img_5);

    waitKey();
   

}