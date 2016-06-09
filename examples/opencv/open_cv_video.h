#ifndef __AF_OPEN_CV_VIDEO_HEADER
#define __AF_OPEN_CV_VIDEO_HEADER




#include <allegro_flare/screen.h>
#include <allegro_flare/profile_timer.h>
#include <allegro_flare/bins/font_bin.h>
#include <allegro_flare/bins/sample_bin.h>
#include <allegro_flare/objects/sound_object.h>
#include <allegro_flare/placement2d.h>

#include <opencv/cv.h>
#include <opencv/highgui.h>




class OpenCVVideo// : public Screen
{
private:
   cv::VideoCapture video;
   cv::Mat frame, edges;

   SampleBin samples;
   FontBin fonts;
   Sound sound;

   bool playing;
   double time_at_start;
   double playhead;
   double video_fps;
   int current_frame;

public:
   ALLEGRO_BITMAP *video_bitmap;
   //placement2d place;

   OpenCVVideo(std::string video_file_location, std::string audio_file_location);

   ~OpenCVVideo();

   int get_width();
   int get_height();

   void play();
   void stop();
   void set_pos(double time); // this isn't exactly operating internally as expected (but works - probably buggy in some instances)
   void refresh_bitmap(); // should be called once before each time the frame is to be drawn
   //void primary_timer_func() override;
   //void key_char_func() override;
};




#endif
