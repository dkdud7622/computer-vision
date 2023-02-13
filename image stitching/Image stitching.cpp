
#include <iostream>
#include <stdio.h>

#include <opencv2/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/core/ocl.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/imgproc.hpp>



using namespace cv;
using namespace std;


int main(int argc, const char* argv[])
{
    Mat img1 = imread("img3.jpg");
    Mat img2 = imread("img4.jpg");

    Mat img_1;
    Mat img_2;

    resize(img1, img_1, Size(img1.cols *0.25, img1.rows *0.25));
    resize(img2, img_2, Size(img2.cols * 0.25, img2.rows * 0.25));

    Mat descriptors1, descriptors2;
    

    //특정점 추출 ORB사용
    int minHessian = 1000; //threshold
    Ptr<ORB> orb = ORB::create(minHessian);

    vector<KeyPoint> keypoint1, keypoint2; //키포인트

    orb->detectAndCompute(img_1, noArray(), keypoint1, descriptors1);
    orb->detectAndCompute(img_2, noArray(), keypoint2, descriptors2);

    Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create(DescriptorMatcher::BRUTEFORCE);
    vector< DMatch > matches;
    matcher->match(descriptors1, descriptors2, matches);

    Mat img_matches;
    drawMatches(img_1, keypoint1, img_2, keypoint2, matches, img_matches, Scalar::all(-1), Scalar::all(-1), vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

    //Mat test_resize;
    //resize(img_matches, test_resize, Size(img_matches.cols* 1 / 5, img_matches.rows * 1 / 5), 0, 0,INTER_CUBIC);

    //호모그라피 찾기
    vector <Point2f> obj;
    vector <Point2f> scene;

    for (int i = 0; i < matches.size(); i++) {
        obj.push_back(keypoint1[matches[i].queryIdx].pt);
        scene.push_back(keypoint2[matches[i].trainIdx].pt);
    }

    Mat HomoMatrix = findHomography(obj ,scene,  RANSAC);

    Mat matResult;
    warpPerspective(img_1, matResult, HomoMatrix, Size(img_1.cols*2, img_1.rows*1.2), INTER_CUBIC);

    Mat matPanorama;
    matPanorama = matResult.clone();

    Mat R(matPanorama, Rect(0, 0, img_2.cols, img_2.rows));
    img_2.copyTo(R);

    imshow("Panorama", matPanorama);


    int colorx = 0, colory = 0;
    for (int y = 0; y < matPanorama.rows; y++) {
        for (int x = 0; x < matPanorama.cols; x++) {
            if (matPanorama.at<Vec3b>(y, x)[0] == 0 && matPanorama.at<Vec3b>(y, x)[1] == 0 && matPanorama.at<Vec3b>(y, x)[2] == 0) {
                continue;
            }
            if (colorx < x) {
                colorx = x;
            }
            if (colory < y) {
                colory = y;
            }
        }
    }

    Mat blackCutPanorama;
    blackCutPanorama = matPanorama(Range(0, colory), Range(0, colorx));
    imshow("cutblack", blackCutPanorama);

    waitKey();


}