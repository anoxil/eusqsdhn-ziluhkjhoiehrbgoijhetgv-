#include <opencv2/opencv.hpp>
#include "common.h"
#include "morphology.hpp"
#include "compare.hpp"

Mat makeShape(int halfsize)
{
    int shape_size = 2 * halfsize + 1;
    int x1, x2;
    double norme_x;
    Mat result = Mat::zeros( shape_size, shape_size, CV_8UC1);
   
    //diamond
    for( int i = 0; i < shape_size; i++ ){
      for( int j = 0; j < shape_size; j++ ){
        x1 = abs( i - halfsize );
        x2 = abs( j - halfsize );
        norme_x = x1 + x2;
        if (norme_x <= halfsize){
          result.ptr<uchar>(i)[j] = 255;
        }
      }
    }

    return result;
}

void process()
{
    Mat ims_bgr = imread("../data/log1/001-rgb.png", CV_LOAD_IMAGE_COLOR);
    if (!ims_bgr.data) {
        cout << ERROR << "Could not open the image." << endl;
        exit(1);
    }
    int width = ims_bgr.size().width;
    int height = ims_bgr.size().height;
    Mat ims_hsv(height, width, CV_8UC3);
    Mat mask(height, width, CV_8UC1);
    Mat img_temp(height, width, CV_8UC1);
    Mat img_res(height, width, CV_8UC1);
    Mat shape = makeShape(12);

    for (int img_nb = 1; img_nb <= 374; img_nb++)
    {
        string current_ims_name = "../data/log1/";
        if (img_nb < 10) {current_ims_name += "00";}
        else if (img_nb < 100) {current_ims_name += "0";}
        stringstream img_nb_ss; img_nb_ss << img_nb;
        current_ims_name += img_nb_ss.str() + "-rgb.png";

        ims_bgr = imread(current_ims_name, CV_LOAD_IMAGE_COLOR);
        cvtColor(ims_bgr, ims_hsv, CV_BGR2HSV);

        // seuillage green
        inRange(ims_hsv, Scalar(30,0,0), Scalar(90,255,255), mask);

        // erosion
        mm(shape, mask, img_temp, minimum);

        // dilation
        mm(shape, img_temp, img_res, maximum);

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