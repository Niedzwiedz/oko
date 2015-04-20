#include <cv.h>
#include <highgui.h>

using namespace cv;

int main( int argc, char** argv ) {
    char* imageName = argv[1];

    Mat image;
    image = imread( imageName, 1);
    
    Mat gray_img;
    cvtColor( image, gray_img, CV_BGR2GRAY );

    imwrite("../gray_lena.jpg", gray_img);

    namedWindow( imageName, CV_WINDOW_AUTOSIZE);
    namedWindow( "gray_lena", CV_WINDOW_AUTOSIZE);

    imshow( imageName, image);
    imshow("gray_lena", gray_img);

    waitKey(0);
    return 0;
}
