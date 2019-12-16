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
    for (unsigned int j = 0; j < contours.size(); j++) {
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

    createTrackbar("Slide Bar", vidname, &trackbar_pos, max_frame, &onTrackbarSlide);

    cout << "FPS : " << fps << endl;
    cout << "Width : " << frame_width << "\tHeight : " << frame_height << endl;
    cout << "Number of frame : " << max_frame << endl;

    double delay = 1000000.0 / fps;

    clock_t start;

    for (;;) {
        *cap >> frame;

        start = clock();
        if (!frame.data)
            break;

        Mat img_blur(frame_height, frame_width, CV_8UC3);
        medianBlur(frame, img_blur, 9);

        Mat img_hsv; cvtColor(img_blur, img_hsv, CV_BGR2HSV);

        Mat img_thresh(frame_height, frame_width, CV_8UC1);

        // seuillage du vert
        for (int row = 0; row < frame_height; row++) {
            for (int col = 0; col < frame_width; col++) {
                uchar h = img_hsv.at<Vec3b>(row, col)[0];
                if ((h > 30) && (h < 90))
                    img_thresh.at<uchar>(row, col) = 255;
                else
                    img_thresh.at<uchar>(row, col) = 0;
            }
        }

        vector <vector<Point> > contours;
        vector <Vec4i> hierarchy;
        findContours(img_thresh, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

        vector <vector<Point> > hull(contours.size());
        for (unsigned int i = 0; i < contours.size(); i++)
            convexHull(Mat(contours[i]), hull[i]);

        drawContours(frame, hull, getMaxAreaContourId(contours), Scalar(255, 0, 0), 1, 8, vector<Vec4i>(), 0, Point());

        imshow(vidname, frame);

        if (waitKey(30) >= 0) {
            break;
        }

        while (clock() - start < delay) {
            //waitKey(1);
        }

    }
    cap->release();
    //destroyAllWindows();
}

void usage(const char *s) {
    std::cerr << ERROR << "Usage: " << s << " vidname \n" << std::endl;
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    if (argc != (PARAM + 1))
        usage(argv[0]);

    process(argv[1]);

    return EXIT_SUCCESS;
}