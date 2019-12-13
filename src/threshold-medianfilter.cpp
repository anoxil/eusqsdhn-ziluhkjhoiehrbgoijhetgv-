#include <opencv2/opencv.hpp>
#include "common.h"
#include "compare.hpp"

void process(const char* ims_name)
{

    Mat img_bgr = imread(ims_name, CV_LOAD_IMAGE_COLOR);
    if (!img_bgr.data) {
        cout << ERROR << "Could not open the image." << ims_name << endl;
        exit(1);
    }
    int width = img_bgr.size().width;
    int height = img_bgr.size().height;
    Mat img_hsv(height, width, CV_8UC3); cvtColor(img_bgr, img_hsv, CV_BGR2HSV);
    Mat ims_threshold(height, width, CV_8UC1);

    vector<int> cheats;
    //{1,27,105,117,151,161,247,271}
    cheats.push_back(1); cheats.push_back(27); cheats.push_back(105); cheats.push_back(117); cheats.push_back(151); cheats.push_back(161); cheats.push_back(247); cheats.push_back(271);


    for (int img_nb = 1; img_nb <= 1; img_nb++)
    {
        string current_ims_name = "../data/log1/";
        string result_ims_name = "../data/log1_results/medianfilter-";
        if (img_nb < 10) {current_ims_name += "00";}
        else if (img_nb < 100) {current_ims_name += "0";}
        stringstream ss; ss << img_nb;
        current_ims_name += ss.str() + "-rgb.png";
        result_ims_name += ss.str() + "-rgb.png";

        Mat img_bgr = imread(current_ims_name, CV_LOAD_IMAGE_COLOR);
        Mat img_hsv; cvtColor(img_bgr, img_hsv, CV_BGR2HSV);
        Mat img_blur(height, width, CV_8UC3);
        Mat img_thresh(height, width, CV_8UC1);
        Mat img_res(height, width, CV_8UC1);

        //léger median blur sur hsv
        medianBlur(img_hsv, img_blur, 3);
        //seuillage du vert
        for (int row = 0; row < height; row++){
            for (int col = 0; col < width; col++){
                uchar h = img_hsv.at<Vec3b>(row,col)[0];
                if ((h > 30) && (h < 90))
                    img_thresh.at<uchar>(row,col) = 255;
            }
        }
        //median blur samere sur thresh
        medianBlur(img_thresh, img_res, 39);
        imshow("res", img_res);

        /*
        //us
        vector< vector<Point> > contours;
        vector<Vec4i> hierarchy; 
        findContours(img_res, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
        //cheat
        vector< vector<Point> > contours_c;
        vector<Vec4i> hierarchy_c; 
        findContours(img_res, contours_c, hierarchy_c, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
        //us
        vector< vector<Point> > hull(contours.size());
        for(int i = 0; i < contours.size(); i++)
            convexHull(Mat(contours[i]), hull[i]);
        //cheat
        vector< vector<Point> > hull_c(contours_c.size());
        for(int i = 0; i < contours_c.size(); i++)
            convexHull(Mat(contours_c[i]), hull_c[i]);
        // create a blank image (black image)
        Mat drawing = Mat::zeros(img_res.size(), CV_8UC3);
        for(int i = 0; i < contours.size(); i++) {
            cv::Scalar color_contours = Scalar(0, 255, 0); // green - color for contours
            cv::Scalar color = Scalar(255, 0, 0); // blue - color for convex hull
            cv::Scalar color_c = Scalar(0, 0, 255); // red - color for convex hull real
            // draw ith contour
            drawContours(drawing, contours, i, color_contours, 1, 8, vector<Vec4i>(), 0, Point());
            // draw ith convex hull
            drawContours(drawing, hull_c, i, color_c, 1, 8, vector<Vec4i>(), 0, Point()); //cheat
            drawContours(drawing, hull, i, color, 1, 8, vector<Vec4i>(), 0, Point()); //us
        }
        imshow("contour", drawing);
        waitKey(0);
        */

        if (std::find(cheats.begin(), cheats.end(), img_nb) != cheats.end()) {
            compare_visually(img_res, img_nb);
            compare_numberly(img_res, img_nb);
        }
    }
}

int main(int argc, char* argv[])
{
    (void) argc;

    process(argv[1]);

    return EXIT_SUCCESS;  
}