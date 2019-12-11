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
    Mat ims_threshold(height, width, CV_8UC1);

    Mat ims_hsv(height, width, CV_8UC3); cvtColor(ims_bgr, ims_hsv, CV_BGR2HSV);
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

    //adaptiveThreshold(ims_bgr, ims_bgr_thresh, );

    //VideoWriter video("output.avi", CV_FOURCC('P','I','M','1'), 24, Size(width, height));

    Mat ims_bgr_thresh(height, width, CV_8UC3);
    Mat mask;
    inRange(ims_hsv, Scalar(30,0,0), Scalar(90,255,255), mask);
    imshow("mask", mask);

    for (int img = 1; img <= 1; img++)
    {
        /*
        string current_ims_name = "../data/log1/";
        if (img < 10) {current_ims_name += "00";}
        else if (img < 100) {current_ims_name += "0";}
        stringstream ss; ss << img;
        current_ims_name += ss.str() + "-rgb.png";
        

        Mat ims_bgr = imread(ims_name, CV_LOAD_IMAGE_COLOR); //change ims_name to current_ims_name when using for
        Mat ims_hsv; cvtColor(ims_bgr, ims_hsv, CV_BGR2HSV);

        Mat ims_threshold(height, width, CV_8UC1);
        */

        for(int i = 0; i<height; i++){
            for(int j = 0; j<width; j++){
                int H = ims_hsv.at<Vec3b>(i,j)[0];  // 0-180
                //int S = ims_hsv.at<Vec3b>(i,j)[1];  // 0-255
                int V = ims_hsv.at<Vec3b>(i,j)[2];  // 0-255
                int B = ims_bgr.at<Vec3b>(i,j)[0];  // 0-255
                //int G = ims_bgr.at<Vec3b>(i,j)[1];  // 0-255
                //int R = ims_bgr.at<Vec3b>(i,j)[2];  // 0-255

                // min_h:60|min_S:1|min_V:38|max_h:110|max_S:255|max_V:255 (terrain)
                // min_h:1|min_S:2|min_V:32|max_h:179|max_S:255|max_V:255  (fullimg)
                if( (B < 50) && ((H > 40) && (H < 110)) && (V > 38) ) //it's green & saturation > 0.6
                {
                    ims_threshold.at<uchar>(i,j) = 255;
                }
                else
                {
                    ims_threshold.at<uchar>(i,j) = 0;
                }
            }
        }
        //video.write(ims_threshold);
    }

    imshow("bgr_ims", ims_bgr);
    imshow("hsv_ims", ims_hsv);
    imshow("thresholded_ims", ims_threshold);
    waitKey(0);
    
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