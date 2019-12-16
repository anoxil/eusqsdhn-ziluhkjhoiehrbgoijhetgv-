#include "compare.hpp"

Mat get_img_true(int img_number)
{
    stringstream ss; ss << img_number;
    string img_true_name = "../data/log1/" + ss.str() + "-true.png";
    Mat img_true(imread(img_true_name, CV_LOAD_IMAGE_GRAYSCALE));
    return img_true;
}

Mat compare_visually(Mat& inputArray, int img_number)
{
    Mat img_true = get_img_true(img_number);
    int height = inputArray.size().height;
    int width = inputArray.size().width;

    imshow("true", img_true);

    Mat img_res(height, width, CV_8UC1);
    for (int row = 0; row < height; row++){
        for (int col = 0; col < width; col++){
            if ((inputArray.at<uchar>(row,col) == 0) && (img_true.at<uchar>(row,col) == 0)) { //bon négatif
                img_res.at<uchar>(row,col) = 0;
            } else if ((inputArray.at<uchar>(row,col) == 0) && (img_true.at<uchar>(row,col) == 255)) { //faux négatif
                img_res.at<uchar>(row,col) = 90;
            } else if ((inputArray.at<uchar>(row,col) == 255) && (img_true.at<uchar>(row,col) == 0)) { //faux positif
                img_res.at<uchar>(row,col) = 180;
            } else if ((inputArray.at<uchar>(row,col) == 255) && (img_true.at<uchar>(row,col) == 255)) { //bon positif
                img_res.at<uchar>(row,col) = 255;
            }
        }
    }

    imshow("Comparison processed vs true", img_res);
    waitKey(0);

    return img_res;
}

void compare_numberly(Mat& inputArray, int img_number)
{
    Mat img_true = get_img_true(img_number);
    int height = inputArray.size().height;
    int width = inputArray.size().width;
    double total = height * width;

    int nb_true_neg = 0;
    int nb_false_neg = 0;
    int nb_false_pos = 0;
    int nb_true_pos = 0;
    int nb_total = 0;

    for (int row = 0; row < height; row++){
        for (int col = 0; col < width; col++){
            if ((inputArray.at<uchar>(row,col) == 0) && (img_true.at<uchar>(row,col) == 0)) { //true negative
                nb_true_neg++; nb_total++;
            } else if ((inputArray.at<uchar>(row,col) == 0) && (img_true.at<uchar>(row,col) == 255)) { //false negative
                nb_false_neg++; nb_total++;
            } else if ((inputArray.at<uchar>(row,col) == 255) && (img_true.at<uchar>(row,col) == 0)) { //false positive
                nb_false_pos++; nb_total++;
            } else if ((inputArray.at<uchar>(row,col) == 255) && (img_true.at<uchar>(row,col) == 255)) { //true positive
                nb_true_pos++; nb_total++;
            }
        }
    }

    cout << "False Negative : " << nb_false_neg << " pixels\t" << "False Positive : " << nb_false_pos << " pixels\n"
         << "True Negative : " << nb_true_neg << " pixels\t" << "True Positive : " << nb_true_pos << " pixels\n"
         << "Total : " << nb_total << " pixels\t" << "Missed : " << total - nb_total << " pixels\n" << endl;

    double perc_true_neg = (double)nb_true_neg/total;
    double perc_false_neg = (double)nb_false_neg/total;
    double perc_false_pos = (double)nb_false_pos/total;
    double perc_true_pos = (double)nb_true_pos/total;

    cout << "False Negative : " << perc_false_neg << "%\t" << "False Positive : " << perc_false_pos << "%\n"
         << "True Negative : " << perc_true_neg << "%\t" << "True Positive : " << perc_true_pos << "%\n" << endl;
}