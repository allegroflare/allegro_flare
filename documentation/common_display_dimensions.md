```
enum resolution_t
{
  RESOLUTION_XGA,
  RESOLUTION_WXGA,
  RESOLUTION_WXGA_PLUS, // WXGA+
  RESOLUTION_HD_1080,
  RESOLUTION_HD_720,
  RESOLUTION_RETINA,
  FULLSCREEN_AUTO
};
```

```
Display *Full::create_display(Display::resolution_t resolution)
{
   int w, h;
   int screen_flags = ALLEGRO_FLAGS_EMPTY;
   int display_adapter_to_use = 0;

   switch(resolution)
   {
   case Display::RESOLUTION_XGA:
      w = 1024;
      h = 768;
      break;
   case Display::RESOLUTION_WXGA:
      w = 1280;
      h = 800;
      break;
   case Display::RESOLUTION_WXGA_PLUS:
      w = 1440;
      h = 900;
      break;
   case Display::RESOLUTION_HD_1080:
      w = 1920;
      h = 1080;
      break;
   case Display::RESOLUTION_HD_720:
      w = 1280;
      h = 720;
      break;
   case Display::RESOLUTION_RETINA:
      w = 2880;
      h = 1800;
      break;
   case Display::FULLSCREEN_AUTO:
      {
         ALLEGRO_MONITOR_INFO monitor_info;
         al_get_monitor_info(display_adapter_to_use, &monitor_info);
         w = monitor_info.x2 - monitor_info.x1;
         h = monitor_info.y2 - monitor_info.y1;
         screen_flags = ALLEGRO_FULLSCREEN;
      }
      break;
   default:
      w = 1024;
      h = 768;
      break;
   }

   return create_display(w, h, screen_flags, display_adapter_to_use);
}
```
