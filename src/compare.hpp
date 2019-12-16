#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

Mat compare_visually(Mat& inputArray, int img_number);
void compare_numberly(Mat& inputArray, int img_number);
Mat get_img_true(int img_number);