#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv){

    Mat image;
    image=imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);

    if(! image.data){

        cout << "Could not load image " << endl;
        return -1;
    }
    namedWindow("Moje okno", WINDOW_AUTOSIZE);
    imshow("Moje okno", image);

    waitKey(0);
    return 0;
}
