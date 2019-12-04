#include <iostream>
#include <cstdlib>
#include <math.h>
#include <opencv2/opencv.hpp>


#ifndef COMMON_H
#define COMMON_H

#define INFO        "\033[32mInfo : \033[0m"
#define WARNING     "\033[33mWarning : \033[0m"
#define ERROR       "\033[31mError : \033[0m"
#define ENDING      ".png"

using namespace cv;
using namespace std;

bool hasEnding(std::string const &fullString, std::string const &ending) ;
void saveImage(const char *imdname, Mat *image);

#endif