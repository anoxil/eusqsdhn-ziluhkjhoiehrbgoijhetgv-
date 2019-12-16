#include <opencv2/opencv.hpp>
#include "common.h"
#include "compare.hpp"

#define PARAM   1

VideoCapture *cap;

void onTrackbarSlide(int pos, void *) {
    cap->set(CV_CAP_PROP_POS_FRAMES, pos);
    //cout << "Destinate frame : " << pos << endl;
}

int getMaxAreaContourId(vector <vector<cv::Point> > contours) {
    double maxArea = 0;
    int maxAreaContourId = -1;
    for (int j = 0; j < contours.size(); j++) {
        double newArea = cv::contourArea(contours.at(j));
        if (newArea > maxArea) {
            maxArea = newArea;
            maxAreaContourId = j;
        } // End if
    } // End for
    return maxAreaContourId;
} // End function

void process(const char *vidname) {
    (void) vidname;
    int trackbar_pos = 0;

    Mat frame;

    cap = new VideoCapture();
    cap->open(vidname);

    if (!cap->isOpened()) {
        cout << ERROR << "File \"" << vidname << "\"don't exist, please check the name." << endl;
        exit(1);
    }


    namedWindow(vidname, 1);

    int frame_width = int(cap->get(CV_CAP_PROP_FRAME_WIDTH));
    int frame_height = int(cap->get(CV_CAP_PROP_FRAME_HEIGHT));
    int max_frame = int(cap->get(CV_CAP_PROP_FRAME_COUNT));
    double fps = cap->get(CV_CAP_PROP_FPS);

    createTrackbar("slide bar", vidname, &trackbar_pos, max_frame, &onTrackbarSlide);

    cout << "fps : " << fps << endl;
    cout << "width : " << frame_width << "   heigth : " << frame_height << endl;
    cout << "Number of frame : " << max_frame << endl;

    double delay = 1000000.0 / fps;

    clock_t start;

    for (;;) {
        *cap >> frame;

        start = clock();
        if (!frame.data)
            break;

//        int act_frame = int(cap->get(CV_CAP_PROP_POS_FRAMES));
//        ostringstream nb_frame;
//        nb_frame << act_frame;
//        string text = "frame number = " + nb_frame.str();
//
//        if (act_frame <= 1000)
//            putText(frame, text, Point(0, 20), FONT_HERSHEY_COMPLEX_SMALL, 1.0, Scalar(255, 255, 255));


        Mat img_blur(frame_height, frame_width, CV_8UC3);
        medianBlur(frame, img_blur, 5); // ca fout en l'air le imshow quand le chiffre est trop grand

        Mat img_hsv;
        cvtColor(img_blur, img_hsv, CV_BGR2HSV);

        Mat img_thresh(frame_height, frame_width, CV_8UC1);
        //Mat img_res(frame_height, frame_width, CV_8UC1); // attention fait planter l'image, chelou

        //léger median blur sur hsv
//        medianBlur(img_hsv, img_blur, 3);
        //seuillage du vert
        for (int row = 0; row < frame_height; row++) {
            for (int col = 0; col < frame_width; col++) {
                uchar h = img_hsv.at<Vec3b>(row, col)[0];
                if ((h > 30) && (h < 90))
                    img_thresh.at<uchar>(row, col) = 255;
            }
        }
        //median blur samere sur thresh
        //medianBlur(img_thresh, img_res, 39);
        //imshow("res", img_res);


        //us
        vector <vector<Point> > contours;
        vector <Vec4i> hierarchy;
        findContours(img_thresh, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

        //us
        vector <vector<Point> > hull(contours.size());
        for (int i = 0; i < contours.size(); i++)
            convexHull(Mat(contours[i]), hull[i]);
//
        // create a blank image (black image)
        Mat drawing = Mat::zeros(img_thresh.size(), CV_8UC3);
//        for (int i = 0; i < contours.size(); i++) {
//            cv::Scalar color_contours = Scalar(0, 255, 0); // green - color for contours
//            cv::Scalar color = Scalar(255, 0, 0); // blue - color for convex hull
//            cv::Scalar color_c = Scalar(0, 0, 255); // red - color for convex hull real
//            // draw ith contour
//            drawContours(drawing, contours, i, color_contours, 1, 8, vector<Vec4i>(), 0, Point());
//            // draw ith convex hull
//            //drawContours(drawing, hull_c, i, color_c, 1, 8, vector<Vec4i>(), 0, Point()); //cheat
//            drawContours(drawing, hull, i, color, 1, 8, vector<Vec4i>(), 0, Point()); //us
//        }

        drawContours(frame, hull, getMaxAreaContourId(contours), Scalar(255, 0, 0), 1, 8, vector<Vec4i>(), 0, Point()); //us
//        imshow("contour", drawing);
//        waitKey(0);


        //imshow(vidname, frame);
        imshow(vidname, frame);


        if (waitKey(30) >= 0) {
            break;
        }

        while (clock() - start < delay) {
            //waitKey(1);
        }

    }
    cap->release();
//    destroyAllWindows();
}

void usage(const char *s) {
    std::cerr << ERROR << "Usage: " << s << " imsname \n" << std::endl;
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    if (argc != (PARAM + 1))
        usage(argv[0]);

    process(argv[1]);

    return EXIT_SUCCESS;
}