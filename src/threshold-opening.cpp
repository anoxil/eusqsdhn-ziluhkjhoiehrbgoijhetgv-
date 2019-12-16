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
    Mat img_temp(height, width, CV_8UC1);
    Mat img_res(height, width, CV_8UC1);
    Mat shape = makeShape(12);

    vector<int> cheats;
    //{1,27,105,117,151,161,247,271}
    cheats.push_back(1); cheats.push_back(27); cheats.push_back(105); cheats.push_back(117); cheats.push_back(151); cheats.push_back(161); cheats.push_back(247); cheats.push_back(271);

    for (int img_nb = 161; img_nb <= 161; img_nb++)
    {
        string current_ims_name = "../data/log1/";
        string result_ims_name = "../data/log1_results/opening-";
        if (img_nb < 10) {current_ims_name += "00";}
        else if (img_nb < 100) {current_ims_name += "0";}
        stringstream img_nb_ss; img_nb_ss << img_nb;
        current_ims_name += img_nb_ss.str() + "-rgb.png";
        result_ims_name += img_nb_ss.str() + "-rgb.png";

        ims_bgr = imread(current_ims_name, CV_LOAD_IMAGE_COLOR);
        cvtColor(ims_bgr, ims_hsv, CV_BGR2HSV);

        //first step
        inRange(ims_hsv, Scalar(30,0,0), Scalar(90,255,255), mask);

        //second step
        //-- Make the erosion
        mm(shape, mask, img_temp, minimum);

        //-- Make the dilation
        mm(shape, img_temp, img_res, maximum);
        //imwrite(result_ims_name, img_res);

        /*////////
        vector< vector<Point> > contours;
        vector<Vec4i> hierarchy; 
        findContours(img_res, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

        vector< vector<Point> > hull(contours.size());
        for(int i = 0; i < contours.size(); i++)
            convexHull(Mat(contours[i]), hull[i]);

        Mat drawing = Mat::zeros(img_res.size(), CV_8UC3);

        for(int i = 0; i < contours.size(); i++) {
            cv::Scalar color_contours = Scalar(0, 255, 0); // green - color for contours
            cv::Scalar color = Scalar(255, 0, 0); // blue - color for convex hull
            // draw ith contour
            drawContours(drawing, contours, i, color_contours, 1, 8, vector<Vec4i>(), 0, Point());
            // draw ith convex hull
            drawContours(drawing, hull, i, color, 1, 8, vector<Vec4i>(), 0, Point()); //us
        }
        imshow("result", drawing);
        waitKey(0);
        */

        if (std::find(cheats.begin(), cheats.end(), img_nb) != cheats.end()) {
          string txt = "=== Comparing image " + img_nb_ss.str(); cout << txt << " ===\n" << endl;
          compare_numberly(img_res, img_nb);
          compare_visually(img_res, img_nb);
        }
    }
}

int main(int argc, char* argv[])
{
    (void) argc;

   process(argv[1]);

   return EXIT_SUCCESS;  
}