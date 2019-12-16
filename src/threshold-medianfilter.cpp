#include <opencv2/opencv.hpp>
#include "common.h"
#include "compare.hpp"

void process()
{
    Mat img_test = imread("../data/log1/001-rgb.png", CV_LOAD_IMAGE_COLOR);
    if (!img_test.data) {
        cout << ERROR << "Could not open the image." << endl;
        exit(1);
    }
    int width = img_test.size().width;
    int height = img_test.size().height;
    Mat img_hsv(height, width, CV_8UC3); cvtColor(img_test, img_hsv, CV_BGR2HSV);
    Mat ims_threshold(height, width, CV_8UC1);

    for (int img_nb = 1; img_nb <= 374; img_nb++)
    {
        string current_ims_name = "../data/log1/";
        if (img_nb < 10) {current_ims_name += "00";}
        else if (img_nb < 100) {current_ims_name += "0";}
        stringstream img_nb_ss; img_nb_ss << img_nb;
        current_ims_name += img_nb_ss.str() + "-rgb.png";

        Mat img_bgr = imread(current_ims_name, CV_LOAD_IMAGE_COLOR);
        Mat img_hsv; cvtColor(img_bgr, img_hsv, CV_BGR2HSV);
        Mat img_blur(height, width, CV_8UC3);
        Mat img_thresh(height, width, CV_8UC1);
        Mat img_res(height, width, CV_8UC1);

        //-- Processing

        // léger median blur sur hsv
        medianBlur(img_hsv, img_blur, 3);
        // seuillage du vert
        for (int row = 0; row < height; row++){
            for (int col = 0; col < width; col++){
                uchar h = img_hsv.at<Vec3b>(row,col)[0];
                if ((h > 30) && (h < 90))
                    img_thresh.at<uchar>(row,col) = 255;
                else
                    img_thresh.at<uchar>(row,col) = 0;
            }
        }
        // median blur bcp bcp bcp
        medianBlur(img_thresh, img_res, 39);


        //-- Convex

        // contours
        Mat img_res_contoured; img_res.copyTo(img_res_contoured);
        vector< vector<Point> > contours;
        vector<Vec4i> hierarchy; 
        findContours(img_res_contoured, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

        // convex
        vector< vector<Point> > hull(contours.size());
        for(unsigned int i = 0; i < contours.size(); i++)
            convexHull(Mat(contours[i]), hull[i]);
        
        // application
        Mat drawing = Mat::zeros(img_res.size(), CV_8UC3);
        for(unsigned int i = 0; i < contours.size(); i++)
        {
            cv::Scalar color = Scalar(255, 255, 255); // white - color for convex hull (white so we can fill with it after)
            drawContours(img_res, hull, i, color, -1, 8, vector<Vec4i>(), 0, Point()); //we fill the zone with white (-1)
        }

        imshow("img_processed", img_res);
        waitKey(0);
    }
}

int main(int argc, char* argv[])
{
    (void) argc;
    (void) argv;

    process();

    return EXIT_SUCCESS;  
}