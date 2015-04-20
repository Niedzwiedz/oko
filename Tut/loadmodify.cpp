#include <cv.h>
#include <highgui.h>
#include <imgproc.h>
#include <objdetect.h>

using namespace cv;

CascadeClassifier face_cascade;
CascadeClassifier eye_cascade;

int detectEye(Mat& im, Mat& tpl, Rect& rect){
    std::vector<Rect> faces, eyes;
    face_cascade.detectMultiScale(im, faces, 1.1,2,0|CV_HAAR_SCALE_IMAGE, Size(30,30));
    for( int i = 0; i < faces.size(); i++){
        Mat face = im(faces[i]);
        eye_cascade.detectMultiScale(face, eyes, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(20,20));
        if (eyes.size())
        {
            rect = eyes[0] + Point(faces[i].x, faces[i].y);
            tpl = im(rect);
        }
    }
    return eyes.size();
}


int main( int argc, char** argv ) {
    face_cascade.load("haarcascade_frontalface_alt2.xml");
    eye_cascade.load("haarcascade_eye.xml");
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
