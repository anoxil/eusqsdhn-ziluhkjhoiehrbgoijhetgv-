#include <opencv2/opencv.hpp>
#include "common.h"

void process(const char* ims_name)
{
    Mat ims_bgr = imread(ims_name, CV_LOAD_IMAGE_COLOR);
    if (!ims_bgr.data) {
        cout << ERROR << "Could not open the image." << ims_name << endl;
        exit(1);
    }
    int width = ims_bgr.size().width;
    int height = ims_bgr.size().height;
    Mat ims_hsv(height, width, CV_8UC3); cvtColor(ims_bgr, ims_hsv, CV_BGR2HSV);
    Mat ims_threshold(height, width, CV_8UC1);
    /*
    Mat ims_cheat_oc(imread("../data/log1/001-cheat.png"));
    Mat ims_cheat(height, width, CV_8UC1); Vec3b blank(0,0,0);
    for (int row = 0; row < height; row++){
        for (int col = 0; col < width; col++){
            if (ims_cheat_oc.at<Vec3b>(row,col) == blank) {
                ims_cheat.at<uchar>(row,col) = 255;
            }
            else {
                cout << "coucou" << endl;
                ims_cheat.at<uchar>(row,col) = 0;
                ims_cheat_oc.at<uchar>(row, col) = 255;
            }   
        }
    }
    imshow("i", ims_cheat);
    waitKey(0);
*/
    /*
    vector<Mat> hsv_channels(3);
    split(ims_hsv, hsv_channels);
    imshow("H", hsv_channels[0]);
    imshow("S", hsv_channels[1]);
    imshow("V", hsv_channels[2]);

    vector<Mat> bgr_channels(3);
    split(ims_bgr, bgr_channels);
    imshow("B", bgr_channels[0]);
    imshow("G", bgr_channels[1]);
    imshow("R", bgr_channels[2]);
    */

    //adaptiveThreshold(ims_bgr, ims_bgr_thresh, );

    //VideoWriter video("output.avi", CV_FOURCC('M','J','P','G'), 20, Size(width, height), true);

    /*
    Mat mask;
    inRange(ims_hsv, Scalar(30,0,0), Scalar(90,255,255), mask);
    imshow("mask", mask);
    waitKey(0);
    */

    for (int img = 1; img <= 1; img++)
    {
        string current_ims_name = "../data/log1/";
        string result_ims_name = "../data/log1_results/medianfilter-";
        if (img < 10) {current_ims_name += "00";}
        else if (img < 100) {current_ims_name += "0";}
        stringstream ss; ss << img;
        current_ims_name += ss.str() + "-rgb.png";
        result_ims_name += ss.str() + "-rgb.png";

        Mat ims_bgr = imread(current_ims_name, CV_LOAD_IMAGE_COLOR); //change ims_name to current_ims_name when using for
        Mat ims_hsv; cvtColor(ims_bgr, ims_hsv, CV_BGR2HSV);
        Mat ims_blur(height, width, CV_8UC3);
        Mat ims_bin(height, width, CV_8UC1);
        Mat ims_res(height, width, CV_8UC1);

        //median blur à 1 2 sur hsv
        medianBlur(ims_hsv, ims_blur, 3);
        imshow("ims_blur", ims_blur);
        //binarization (???) sur res
        for (int row = 0; row < height; row++){
            for (int col = 0; col < width; col++){
                uchar h = ims_hsv.at<Vec3b>(row,col)[0];
                if ((h > 30) && (h < 90))
                    ims_bin.at<uchar>(row,col) = 255; //ims_hsv.at<Vec3b>(row,col)[0];
            }
        }
        imshow("h_blurred", ims_bin);
        //median blur samere à ~50 sur res
        medianBlur(ims_bin, ims_res, 39);
        imshow("ims_res", ims_res);

        waitKey(0);
    }
}

int main(int argc, char* argv[])
{
    (void) argc;
    /* 
    boucle sur les images
        inrange sur l'image n
        extraire forme des points les plus externes parmi les thresholdés
    */

   process(argv[1]);

   return EXIT_SUCCESS;  
}