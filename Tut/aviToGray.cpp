#include <cv.h>
#include <iostream>
#include <highgui.h>


int main (int argc, char **argv)
{
   if (argc !=2)
   { 
    std::cout << "USE: " << argv[0] << " <video-filename>" << std::endl;
    return -1;
                            }

    //Open the video that you pass from the command line
    cv::VideoCapture cap(argv[1]);
    if (!cap.isOpened())
    {
     std::cerr << "ERROR: Could not open video " << argv[1] << std::endl;
     return -1;
    }
    int frame_count = 0;
    bool should_stop = false;
 
    while(!should_stop){
         cv::Mat frame;
         cap >> frame; //get a new frame from the video
         if (frame.empty())
         { 
        should_stop = true; //we arrived to the end of the video
        continue;
        }
  }
 return 0;
}
