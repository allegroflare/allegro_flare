#ifndef __AF_CAM_VIEW_HEADER
#define __AF_CAM_VIEW_HEADER




#include <opencv2/opencv.hpp>
#include <allegro5/allegro.h>




class CamView
{
protected:
   cv::VideoCapture video_capture;
   cv::Mat mat;
   ALLEGRO_BITMAP *bitmap;
   int bitmap_width, bitmap_height, cam_width, cam_height;

public:

   CamView(int input_device_num=0);
   ~CamView();

   virtual void process();

   void update();

   void draw_bitmap(float x, float y);

   int get_width();
   int get_height();
};




#endif
