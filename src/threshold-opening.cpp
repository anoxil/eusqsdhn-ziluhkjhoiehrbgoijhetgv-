#include <opencv2/opencv.hpp>
#include "common.h"
#include "morphology.hpp"

Mat makeShape(int halfsize)
{
    int shape_size = 2 * halfsize + 1;
    int x1, x2;
    double norme_x;
    Mat result = Mat::zeros( shape_size, shape_size, CV_8UC1);

    /*
    //square
    for( int i = 0; i < shape_size; i++ ){
        for( int j = 0; j < shape_size; j++ ){
            x1 = abs( i - halfsize );
            x2 = abs( j - halfsize );
            if ( x1 >= x2 )
              norme_x = x1;
            else
              norme_x = x2;
            if ( norme_x <= halfsize )
              result.ptr<uchar>(i)[j] = 255;
        }
    }
    */
   
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

void process(const char* ims_name)
{
    Mat ims_bgr = imread(ims_name, CV_LOAD_IMAGE_COLOR);
    if (!ims_bgr.data) {
        cout << ERROR << "Could not open the image." << ims_name << endl;
        exit(1);
    }
    int width = ims_bgr.size().width;
    int height = ims_bgr.size().height;
    Mat ims_hsv(height, width, CV_8UC3);
    Mat mask(height, width, CV_8UC1);
    Mat mask_temp(height, width, CV_8UC1);
    Mat mask_result(height, width, CV_8UC1);

    for (int img = 1; img <= 374; img++)
    {
        cout << "img:" << img << endl;
        string current_ims_name = "../data/log1/";
        string result_ims_name = "../data/log1_results/opening-";
        if (img < 10) {current_ims_name += "00";}
        else if (img < 100) {current_ims_name += "0";}
        stringstream ss; ss << img;
        current_ims_name += ss.str() + "-rgb.png";
        result_ims_name += ss.str() + "-rgb.png";

        ims_bgr = imread(current_ims_name, CV_LOAD_IMAGE_COLOR);
        cvtColor(ims_bgr, ims_hsv, CV_BGR2HSV);

        //first step
        inRange(ims_hsv, Scalar(30,0,0), Scalar(90,255,255), mask);

        //second step
        //-- Get the shape
        Mat shape = makeShape(12);

        //-- Make the erosion
        mm(shape, mask, mask_temp, minimum);

        //-- Make the dilation
        mm(shape, mask_temp, mask_result, maximum);
        imwrite(result_ims_name, mask_result);
    }
}

int main(int argc, char* argv[])
{
    (void) argc;

   process(argv[1]);

   return EXIT_SUCCESS;  
}