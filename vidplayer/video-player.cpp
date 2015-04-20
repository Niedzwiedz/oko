#include "opencv2/opencv.hpp" 
#include "highgui.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>

cv::CascadeClassifier face_cascade;
cv::CascadeClassifier eye_cascade;


int detectEye(cv::Mat& im, cv::Mat& tpl, cv::Rect& rect)
{
    std::vector<cv::Rect> faces, eyes;
    face_cascade.detectMultiScale(im, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, cv::Size(30,30));
    for (int i = 0; i < faces.size(); i++)
    {
        cv::Mat face = im(faces[i]);
        eye_cascade.detectMultiScale(face, eyes, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, cv::Size(20,20));
        if (eyes.size())
        {
            rect = eyes[0] + cv::Point(faces[i].x, faces[i].y);
            tpl = im(rect);
        }
    }
    return eyes.size();
}

//initialize global variables
int g_slider_position = 0; // trackbar position
CvCapture* g_capture = NULL; // structure to create a video input

// routine to be called when user moves a trackbar slider
void onTrackbarSlide(int pos) {
  cvSetCaptureProperty(
  g_capture,
  CV_CAP_PROP_POS_FRAMES,
  pos
  );
}

int main( int argc, char** argv ) {

    face_cascade.load("/usr/share/opencv/haarcascades/haarcascade_frontalface_alt2.xml");
    eye_cascade.load("/usr/share/opencv/haarcascades/haarcascade_eye.xml");
    // create a window with appropriate size. Windows name is determined by file name
    // supplied as an argument
    cvNamedWindow( argv[1], CV_WINDOW_AUTOSIZE );
    // open video
    g_capture = cvCreateFileCapture( argv[1] );
    if (face_cascade.empty() || eye_cascade.empty())
        return 1;
    // set read position in units of frames and retrieve total number of frames
    int frames = (int) cvGetCaptureProperty(

    g_capture,
    CV_CAP_PROP_FRAME_COUNT
    );


    // do not create treackbar if video does not include an information
    // about number of frames
    if( frames!=0 ) {
        cvCreateTrackbar(
            "Position",
             argv[1],
             &g_slider_position,
             frames,
             onTrackbarSlide
         );
    }
    cv::Mat eye_tpl;
    cv::Rect eye_bb;

    // display video frame by frame
    IplImage* frame;
    cv::Mat gray;
    while(1) {
        

        frame = cvQueryFrame( g_capture );
        if( !frame ) break;

        cvCvtColor( frame, gray, CV_BGR2HSV );  
        if (eye_bb.width == 0 && eye_bb.height == 0)
        {
            // Detection stage
            // // Try to detect the face and the eye of the user
            detectEye(gray, eye_tpl, eye_bb);
        }   

        cvShowImage( argv[1], gray );
        // set trackbar to a current frame position
        cvSetTrackbarPos("Position", argv[1], g_slider_position);

        g_slider_position++;

        char c = cvWaitKey(33);
        // quit if ESC is pressed
        if( c == 27 ) break;
    }
    // free memory
    cvReleaseCapture( &g_capture );
    cvDestroyWindow( argv[1] );
    return(0);
}
