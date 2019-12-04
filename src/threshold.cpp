#include <opencv2/opencv.hpp>
#include "common.h"

void process(const char* ims_name)
{
    Mat ims_rgb = imread(ims_name, CV_LOAD_IMAGE_COLOR);
    Mat ims_hsv; cvtColor(ims_rgb, ims_hsv, CV_RGB2HSV);
    int width = ims_rgb.size().width;
    int height = ims_rgb.size().height;
    Mat ims_threshold(height, width, CV_8UC1);

    int min_H = 255;
    int min_S = 255;
    int min_V = 255;
    int max_H = 0;
    int max_S = 0;
    int max_V = 0;

    for(int i = 0; i<height; i++){
        for(int j = 0; j<width; j++){
            int H = ims_hsv.at<Vec3b>(i,j)[0];  // 0-180
            int S = ims_hsv.at<Vec3b>(i,j)[1];  // 0-255
            int V = ims_hsv.at<Vec3b>(i,j)[2];  // 0-255

            if ((S != 0) && (H != 0))
            {
                if (H < min_H) min_H = H;
                if (S < min_S) min_S = S;
                if (V < min_V) min_V = V;
                if (H > max_H) max_H = H;
                if (S > max_S) max_S = S;
                if (V > max_V) max_V = V;
            }

            // min_h:60|min_S:1|min_V:38|max_h:110|max_S:255|max_V:255 (terrain)
            // min_h:1|min_S:2|min_V:32|max_h:179|max_S:255|max_V:255  (fullimg)
            if( ((H > 55) && (H < 115)) && (V > 35) ) //it's green & saturation > 0.6
            {
                ims_threshold.at<uchar>(i,j) = 255;
            }
            else
            {
                ims_threshold.at<uchar>(i,j) = 0;
            }
        }
    }

    cout << "min_h:" << min_H << "|min_S:" << min_S << "|min_V:" << min_V << "|max_h:" << max_H << "|max_S:" << max_S << "|max_V:" << max_V << endl;
    
    imshow("rgb_ims", ims_rgb);
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