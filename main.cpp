#include "Kalman.h"

using namespace cv;
using namespace std;


struct mouse_info_struct { int x,y; };
struct mouse_info_struct mouse_info = {-1,-1}, last_mouse;

vector<Point> mousev,kalmanv;

void on_mouse(int event, int x, int y, int flags, void* param)
{
    last_mouse = mouse_info;
    mouse_info.x = x;
    mouse_info.y = y;
}


int main (int argc, char * const argv[])
{
    Mat img(500, 1000, CV_8UC3);
    char key = -1;
    namedWindow("Mouse-Kalman");
    setMouseCallback("Mouse-Kalman", on_mouse, 0);
    MyKalmanFilter myKalmanFilter(Point(mouse_info.x,mouse_info.y));
    while (mouse_info.x < 0 || mouse_info.y < 0)
    {
        imshow("Mouse-Kalman", img);
        waitKey(30);
        continue;
    }
    while ( (char)key != 's' )
    {
    	myKalmanFilter.Measure(Point(mouse_info.x,mouse_info.y));
        // /// STATE UPDATE
        // Mat prediction = KF.predict();

        // /// MAKE A MEASUREMENT
        // measurement.at<double>(0) = mouse_info.x;
        // measurement.at<double>(1) = mouse_info.y;

        // /// MEASUREMENT NOISE SIMULATION
        // randn( measurementNoise, Scalar(0),
        //   Scalar::all(sqrtf(measurementNoiseCov)));
        // noisyMeasurement = measurement + measurementNoise;

        // /// MEASUREMENT UPDATE
        // Mat estimated = KF.correct(noisyMeasurement);

        // // cv::Mat u(nInputs,1,CV_64F);
        // // u.at<double>(0,0) = 0.0 * sqrtf(pow((prevMeasurement.at<double>(0) - measurement.at<double>(0)),2)
        // //             + pow((prevMeasurement.at<double>(1) - measurement.at<double>(1)),2));

        // /// STORE ALL DATA
        // Point noisyPt(noisyMeasurement.at<double>(0),noisyMeasurement.at<double>(1));
        // Point estimatedPt(estimated.at<double>(0),estimated.at<double>(1));
        // Point measuredPt(measurement.at<double>(0),measurement.at<double>(1));


        /// PLOT POINTS
#define drawCross( center, color, d )                                 \
        line( img, Point( center.x - d, center.y - d ),                \
        Point( center.x + d, center.y + d ), color, 2, CV_AA, 0); \
        line( img, Point( center.x + d, center.y - d ),                \
        Point( center.x - d, center.y + d ), color, 2, CV_AA, 0 )

        /// DRAW ALL ON IMAGE
        img = Scalar::all(0);
        drawCross( myKalmanFilter.noisyPt, Scalar(255,255,255), 9 );     //WHITE
        drawCross( myKalmanFilter.estimatedPt, Scalar(0,0,255), 6 );       //RED
        drawCross( myKalmanFilter.measuredPt, Scalar(0,255,0), 3 );        //GREEN


        line( img, myKalmanFilter.estimatedPt, myKalmanFilter.measuredPt, Scalar(100,255,255), 3, CV_AA, 0 );
        line( img, myKalmanFilter.estimatedPt, myKalmanFilter.noisyPt, Scalar(0,255,255), 3, CV_AA, 0 );

        imshow( "Mouse-Kalman", img );
        key=cv::waitKey(10);
        if(key == 27) break;
    }

    return 0;
}
