



#include <allegro5/allegro_primitives.h>

#include <allegro_flare/open_cv_video.h>
#include <allegro_flare/screen.h>
#include <allegro_flare/profile_timer.h>
#include <allegro_flare/color.h>
#include <allegro_flare/bins/font_bin.h>

#include <opencv/cv.h>
#include <opencv/highgui.h>




OpenCVVideo::OpenCVVideo(std::string video_file_location, std::string audio_file_location)
   //: Screen(display)
   //: place(0, 0, 0, 0)
   : video(video_file_location)
   //, video_capture(0)
   , video_bitmap(NULL)
   , video_fps(0)
   , frame()
   , edges()
   , current_frame(0)
   , playhead(0)
   , fonts("data/fonts")
   , samples("data/videos")
   , sound(samples[audio_file_location])
   , playing(false)
   , time_at_start(0)
{
   if (!video.isOpened())
   {
      std::cout << "could not open cam capture." << std::endl;
   }
   else
   {
      video_bitmap = al_create_bitmap(video.get(CV_CAP_PROP_FRAME_WIDTH), video.get(CV_CAP_PROP_FRAME_HEIGHT));
      //place.w = video.get(CV_CAP_PROP_FRAME_WIDTH);
      //place.h = video.get(CV_CAP_PROP_FRAME_HEIGHT);
      std::cout << "cam_bitmap created." << std::endl;
      video_fps = video.get(CV_CAP_PROP_FPS);
      current_frame = 0;
      playhead = 0;
   }

   //place.align_x = 0.5;
   //place.align_y = 0.5;
   //place.scale_x = 0.75;
   //place.scale_y = 0.75;

   //if (display)
   //{
   //	place.x = display->width()/2;
   //	place.y = display->height()/2;
   //}

   //play();
}




int get_frame_num_at_time(double time, double framerate_fps)
{
   return (int)(time * framerate_fps);
}




OpenCVVideo::~OpenCVVideo()
{
   std::cout << "releasing VideoCapture" << std::endl;
   video.release();
   std::cout << "   ...done" << std::endl;

   al_rest(1);
}




int OpenCVVideo::get_width()
{
   return video.get(CV_CAP_PROP_FRAME_WIDTH);
}




int OpenCVVideo::get_height()
{
   return video.get(CV_CAP_PROP_FRAME_HEIGHT);
}




void OpenCVVideo::play()
{
   if (playing) return;
   playing = true;

   time_at_start = al_get_time();
   sound.play();
}




void OpenCVVideo::stop()
{
   if (!playing) return;
   playing = false;

   time_at_start = al_get_time();
   set_pos(0);
   sound.stop();
}




void OpenCVVideo::set_pos(double time)
{
   double time_now = al_get_time();
   video.set(CV_CAP_PROP_POS_MSEC, time * 1000);
   sound.position(time).play();
   time_at_start = time_now - time;
   current_frame = get_frame_num_at_time(time_now - time_at_start, video_fps);
}




void OpenCVVideo::refresh_bitmap()
{
   if (!playing) return;

   int bitmap_width = al_get_bitmap_width(video_bitmap);
   int bitmap_height = al_get_bitmap_height(video_bitmap);

   int video_width = video.get(CV_CAP_PROP_FRAME_WIDTH);
   int video_height = video.get(CV_CAP_PROP_FRAME_HEIGHT);

   int total_num_frames = video.get(CV_CAP_PROP_FRAME_COUNT);


   //ProfileTimer video_to_frame_timer;
   //ProfileTimer frame_to_al_bitmap_timer;


   int current_frame_should_be = get_frame_num_at_time(al_get_time() - time_at_start, video_fps);
   //std::cout << current_frame_should_be << ".";

   while ((current_frame < current_frame_should_be) && (current_frame < total_num_frames))
   {
      //video_to_frame_timer.start();
      video.read(frame);
      current_frame++;
   }
   //video_to_frame_timer.stop();


   //cv::cvtColor(frame, edges, CV_BGR2GRAY);
   //cv::GaussianBlur(edges, edges, cv::Size(7,7), 1.5, 1.5);
   //cv::Canny(edges, edges, 0, 30, 3);


   //frame_to_al_bitmap_timer.start();
   if (!frame.empty())
   {
      ALLEGRO_LOCKED_REGION *region = al_lock_bitmap(video_bitmap, ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_WRITEONLY);
      for (int y=0; y<bitmap_height; y++)
      {
         for (int x=0; x<bitmap_width; x++)
         {
            uint32_t *ptr32 = (uint32_t *)region->data + x + y * (region->pitch / 4);
            *ptr32 = (frame.data[y * video_width * 3 + x * 3 + 0] << 0) | (frame.data[y * video_width * 3 + x * 3 + 1] << 8) | (frame.data[y * video_width * 3 + x * 3 + 2] << 16);
         }
      }
      al_unlock_bitmap(video_bitmap);
   }
   //frame_to_al_bitmap_timer.stop();
}




/*
void OpenCVVideo::primary_timer_func()
{
   static bool strobe_dot_flag = false;
   strobe_dot_flag = !strobe_dot_flag;
   refresh_bitmap();

   place.start_transform();

   al_draw_filled_rectangle(0, 0, place.w, place.h, color::black);

   //al_draw_text(fonts["arialbd.ttf 42"], color::aqua, 20, 20, NULL, tostring(current_frame).c_str());

   if (video_bitmap) al_draw_bitmap(video_bitmap, 0, 0, NULL);

   if (strobe_dot_flag) al_draw_filled_circle(20, 20, 10, color::white);

   place.restore_transform();
}
*/




