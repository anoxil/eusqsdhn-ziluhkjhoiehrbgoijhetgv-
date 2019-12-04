#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void process(const char* ims_name)
{
    Mat ims = imread("../data/log1/001-rgb.png", CV_LOAD_IMAGE_COLOR);
    Mat ims_hsv; cvtColor(ims, ims_hsv, CV_RGB2HSV);
}

int main(int argc, char* argv[])
{
    /* 
    boucle sur les images
        inrange sur l'image n
        extraire forme des points les plus externes parmi les thresholdés
    */

   process(argv[1]);

   return EXIT_SUCCESS;  
}