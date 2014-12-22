



#include <allegro_flare/cam_view.h>

#include <iostream>






CamView::CamView(int input_device_num)
	: video_capture(input_device_num)
	, mat()
	, bitmap(NULL)
	, bitmap_width(0)
	, bitmap_height(0)
	, cam_width(0)
	, cam_height(0)
{
	if (!video_capture.isOpened())
	{
		std::cout << "could not open cam capture." << std::endl;
		//video_capture.set(CV_CAP_PROP_FPS, 60);
	}
	else
	{
		cam_width = video_capture.get(CV_CAP_PROP_FRAME_WIDTH);
		cam_height = video_capture.get(CV_CAP_PROP_FRAME_HEIGHT);
		bitmap_width = video_capture.get(CV_CAP_PROP_FRAME_WIDTH);
		bitmap_height = video_capture.get(CV_CAP_PROP_FRAME_HEIGHT);
		bitmap = al_create_bitmap(bitmap_width, bitmap_height);
		//cam_bitmap = al_create_bitmap(video_capture.get(CV_CAP_PROP_FRAME_WIDTH), video_capture.get(CV_CAP_PROP_FRAME_HEIGHT));
			
		//std::cout << "bitmap created (" << al_get_bitmap_width(bitmap) << "x" << al_get_bitmap_height(bitmap) << ")" << std::endl;
	}
}




CamView::~CamView()
{
	video_capture.release();
}




void CamView::process() {}




void CamView::update()
{
	video_capture.read(mat);
	process();

	cv::Mat &mat_to_draw = mat;

	//frame_to_al_bitmap_timer.start();
	if (!mat_to_draw.empty())
	{
		ALLEGRO_LOCKED_REGION *region = al_lock_bitmap(bitmap, ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_WRITEONLY);
		for ( int y = 0; y < bitmap_height; y++ ) {
			for ( int x = 0; x < bitmap_width; x++ ) {
				uint32_t *ptr32 = (uint32_t *)region->data + x + y * (region->pitch / 4);
				*ptr32 = (mat_to_draw.data[y * cam_width * 3 + x * 3 + 0] << 0) | (mat_to_draw.data[y * cam_width * 3 + x * 3 + 1] << 8) | (mat_to_draw.data[y * cam_width * 3 + x * 3 + 2] << 16);
			}
		}
		al_unlock_bitmap(bitmap);
	}
}




void CamView::draw_bitmap(float x, float y)
{
	//al_draw_filled_rectangle(x, y, x+bitmap_width, y+bitmap_height, color::black);
	al_draw_bitmap(bitmap, x, y, NULL);
}




int CamView::get_width()
{
	return bitmap_width;
}




int CamView::get_height()
{
	return bitmap_height;
}


