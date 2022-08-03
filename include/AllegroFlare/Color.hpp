#pragma once


#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <iostream>
//#include <AllegroFlare/Useful.hpp>
//#include <allegro_flare/color_names.h>


namespace AllegroFlare
{
   class Color
   {
   public:
      float r;
      float g;
      float b;
      float a;

      Color();
      Color(float r, float g, float b, float a=1.0f);
      Color(ALLEGRO_COLOR allegro_color, float a=1.0f);
      Color(std::string color_name, float a=1.0f);
      Color(int hex, float a=1.0f);
      ~Color();
      
      static Color rgba(int r, int g, int b, float a=1.0f);
      static inline float clamp_color(float v);
      
      Color mix(Color &c1, Color &c2, float scale=0.5f);
      
      Color operator+(const Color &c2);
      Color operator-(const Color &c2);
      Color operator*(const Color &c2);
      
      friend std::ostream& operator<<(std::ostream& os, const Color& c);

      ALLEGRO_COLOR to_al();

      static const ALLEGRO_COLOR Eigengrau;
      static const ALLEGRO_COLOR Nothing;
      static const ALLEGRO_COLOR Null;
      static const ALLEGRO_COLOR MagicPink;
      static const ALLEGRO_COLOR Transparent;

      static const ALLEGRO_COLOR AliceBlue;
      static const ALLEGRO_COLOR AntiqueWhite;
      static const ALLEGRO_COLOR Aqua;
      static const ALLEGRO_COLOR Aquamarine;
      static const ALLEGRO_COLOR Azure;
      static const ALLEGRO_COLOR Beige;
      static const ALLEGRO_COLOR Bisque;
      static const ALLEGRO_COLOR Black;
      static const ALLEGRO_COLOR BlanchedAlmond;
      static const ALLEGRO_COLOR Blue;
      static const ALLEGRO_COLOR BlueViolet;
      static const ALLEGRO_COLOR Brown;
      static const ALLEGRO_COLOR Burlywood;
      static const ALLEGRO_COLOR CadetVlue;
      static const ALLEGRO_COLOR Chartreuse;
      static const ALLEGRO_COLOR Chocolate;
      static const ALLEGRO_COLOR Coral;
      static const ALLEGRO_COLOR CornflowerBlue;
      static const ALLEGRO_COLOR Cornsilk;
      static const ALLEGRO_COLOR Crimson;
      static const ALLEGRO_COLOR Cyan;
      static const ALLEGRO_COLOR DarkBlue;
      static const ALLEGRO_COLOR DarkCyan;
      static const ALLEGRO_COLOR DarkGoldenrod;
      static const ALLEGRO_COLOR DarkGray;
      static const ALLEGRO_COLOR DarkGreen;
      static const ALLEGRO_COLOR DarkKhaki;
      static const ALLEGRO_COLOR DarkMagenta;
      static const ALLEGRO_COLOR DarkOliveGreen;
      static const ALLEGRO_COLOR DarkOrange;
      static const ALLEGRO_COLOR DarkOrchid;
      static const ALLEGRO_COLOR DarkRed;
      static const ALLEGRO_COLOR DarkSalmon;
      static const ALLEGRO_COLOR DarkSeaGreen;
      static const ALLEGRO_COLOR DarkSlateBlue;
      static const ALLEGRO_COLOR DarkSlateGray;
      static const ALLEGRO_COLOR DarkTurquoise;
      static const ALLEGRO_COLOR DarkViolet;
      static const ALLEGRO_COLOR DeepPink;
      static const ALLEGRO_COLOR DeepSkyBlue;
      static const ALLEGRO_COLOR DimGray;
      static const ALLEGRO_COLOR DodgerBlue;
      static const ALLEGRO_COLOR FireBrick;
      static const ALLEGRO_COLOR FloralWhite;
      static const ALLEGRO_COLOR ForestGreen;
      static const ALLEGRO_COLOR Fuchsia;
      static const ALLEGRO_COLOR Gainsboro;
      static const ALLEGRO_COLOR GhostWhite;
      static const ALLEGRO_COLOR Goldenrod;
      static const ALLEGRO_COLOR Gold;
      static const ALLEGRO_COLOR Gray;
      static const ALLEGRO_COLOR Green;
      static const ALLEGRO_COLOR GreenYellow;
      static const ALLEGRO_COLOR Honeydew;
      static const ALLEGRO_COLOR HotPink;
      static const ALLEGRO_COLOR IndianRed;
      static const ALLEGRO_COLOR Indigo;
      static const ALLEGRO_COLOR Ivory;
      static const ALLEGRO_COLOR Khaki;
      static const ALLEGRO_COLOR LavenderBlush;
      static const ALLEGRO_COLOR Lavender;
      static const ALLEGRO_COLOR LawnGreen;
      static const ALLEGRO_COLOR LemonChiffon;
      static const ALLEGRO_COLOR LightBlue;
      static const ALLEGRO_COLOR LightCoral;
      static const ALLEGRO_COLOR LightCyan;
      static const ALLEGRO_COLOR LightGoldenrodYellow;
      static const ALLEGRO_COLOR LightGreen;
      static const ALLEGRO_COLOR LightGrey;
      static const ALLEGRO_COLOR LightPink;
      static const ALLEGRO_COLOR LightSalmon;
      static const ALLEGRO_COLOR LightSeaGreen;
      static const ALLEGRO_COLOR LightSkyBlue;
      static const ALLEGRO_COLOR LightSlateGray;
      static const ALLEGRO_COLOR LightSteelBlue;
      static const ALLEGRO_COLOR LightYellow;
      static const ALLEGRO_COLOR Lime;
      static const ALLEGRO_COLOR LimeGreen;
      static const ALLEGRO_COLOR Linen;
      static const ALLEGRO_COLOR Magenta;
      static const ALLEGRO_COLOR Maroon;
      static const ALLEGRO_COLOR MediumAquamarine;
      static const ALLEGRO_COLOR MediumBlue;
      static const ALLEGRO_COLOR MediumOrchid;
      static const ALLEGRO_COLOR MediumPurple;
      static const ALLEGRO_COLOR MediumSeaGreen;
      static const ALLEGRO_COLOR MediumSlateBlue;
      static const ALLEGRO_COLOR MediumSpringGreen;
      static const ALLEGRO_COLOR MediumTurquoise;
      static const ALLEGRO_COLOR MediumVioletRed;
      static const ALLEGRO_COLOR MidnightBlue;
      static const ALLEGRO_COLOR MintCream;
      static const ALLEGRO_COLOR MistyRose;
      static const ALLEGRO_COLOR Moccasin;
      static const ALLEGRO_COLOR NavajoWhite;
      static const ALLEGRO_COLOR Navy;
      static const ALLEGRO_COLOR Oldlace;
      static const ALLEGRO_COLOR Olive;
      static const ALLEGRO_COLOR OliveDrab;
      static const ALLEGRO_COLOR Orange;
      static const ALLEGRO_COLOR OrangeRed;
      static const ALLEGRO_COLOR Orchid;
      static const ALLEGRO_COLOR PaleGoldenrod;
      static const ALLEGRO_COLOR PaleGreen;
      static const ALLEGRO_COLOR PaleTurquoise;
      static const ALLEGRO_COLOR PaleVioletRed;
      static const ALLEGRO_COLOR PapayaWhip;
      static const ALLEGRO_COLOR PeachPuff;
      static const ALLEGRO_COLOR Peru;
      static const ALLEGRO_COLOR Pink;
      static const ALLEGRO_COLOR Plum;
      static const ALLEGRO_COLOR PowderBlue;
      static const ALLEGRO_COLOR Purple;
      static const ALLEGRO_COLOR WebPurple;
      static const ALLEGRO_COLOR RebeccaPurple;
      static const ALLEGRO_COLOR Red;
      static const ALLEGRO_COLOR RosyBrown;
      static const ALLEGRO_COLOR RoyalBlue;
      static const ALLEGRO_COLOR SaddleBrown;
      static const ALLEGRO_COLOR Salmon;
      static const ALLEGRO_COLOR SandyBrown;
      static const ALLEGRO_COLOR SeaGreen;
      static const ALLEGRO_COLOR Seashell;
      static const ALLEGRO_COLOR Sienna;
      static const ALLEGRO_COLOR Silver;
      static const ALLEGRO_COLOR SkyBlue;
      static const ALLEGRO_COLOR SlateBlue;
      static const ALLEGRO_COLOR SlateGray;
      static const ALLEGRO_COLOR Snow;
      static const ALLEGRO_COLOR SpringGreen;
      static const ALLEGRO_COLOR SteelBlue;
      static const ALLEGRO_COLOR Tan;
      static const ALLEGRO_COLOR Teal;
      static const ALLEGRO_COLOR Thistle;
      static const ALLEGRO_COLOR Tomato;
      static const ALLEGRO_COLOR Turquoise;
      static const ALLEGRO_COLOR Violet;
      static const ALLEGRO_COLOR Wheat;
      static const ALLEGRO_COLOR White;
      static const ALLEGRO_COLOR WhiteSmoke;
      static const ALLEGRO_COLOR Yellow;
      static const ALLEGRO_COLOR YellowGreen;
   };
   
   Color operator*(const Color &c, float k);
   Color operator*(float k, const Color &c);
   
   ALLEGRO_COLOR operator+(const ALLEGRO_COLOR& lhs, const ALLEGRO_COLOR& rhs);
   ALLEGRO_COLOR operator-(const ALLEGRO_COLOR& lhs, const ALLEGRO_COLOR& rhs);
   ALLEGRO_COLOR operator*(const ALLEGRO_COLOR& lhs, const ALLEGRO_COLOR& rhs);
   ALLEGRO_COLOR operator*(const ALLEGRO_COLOR& lhs, float rhs);
   ALLEGRO_COLOR operator*(float lhs, const ALLEGRO_COLOR& rhs);



   namespace color
   {
      namespace blend_op
      {
         float add(float val1, float val2);
         float subtract(float val1, float val2);
         float multiply(float val1, float val2);
         float divide(float val1, float val2);
      }




      ALLEGRO_COLOR color(const char *color_name, float alpha=1.0);

      ALLEGRO_COLOR color(ALLEGRO_COLOR color, float alpha=1.0f);

      ALLEGRO_COLOR hex(const char *hex, float alpha=1.0f);

      ALLEGRO_COLOR name(const char *name, float alpha=1.0f);

      ALLEGRO_COLOR rgb(float r, float g, float b, float alpha=1.0f);

      ALLEGRO_COLOR hsl(float h, float s, float l, float alpha=1.0f);




      ALLEGRO_COLOR mix(const ALLEGRO_COLOR &col1, const ALLEGRO_COLOR &col2, float scale);




      std::string get_css_str(ALLEGRO_COLOR &col); // at this point in time, it only does rgb(255, 255, 255), not rgba.




      bool basically_equal(const ALLEGRO_COLOR &col1, const ALLEGRO_COLOR &col2, float threshold=0.0001);

      void change_alpha(ALLEGRO_COLOR &color, float alpha);

      float get_lightness(ALLEGRO_COLOR &color); // should be called luminance




      void change_hue(ALLEGRO_COLOR &color, float amount, float (*operation)(float op1, float op2)=blend_op::multiply);

      void change_saturation(ALLEGRO_COLOR &color, float amount, float (*operation)(float op1, float op2)=blend_op::multiply);

      void change_lightness(ALLEGRO_COLOR &color, float amount, float (*operation)(float op1, float op2)=blend_op::multiply);

      void change_value(ALLEGRO_COLOR &color, float amount, float (*operation)(float op1, float op2)=blend_op::multiply);




      void change_hue(ALLEGRO_BITMAP *bitmap, float amount, float (*operation)(float op1, float op2)=blend_op::multiply);

      void change_saturation(ALLEGRO_BITMAP *bitmap, float amount, float (*operation)(float op1, float op2)=blend_op::multiply);

      void change_lightness(ALLEGRO_BITMAP *bitmap, float amount, float (*operation)(float op1, float op2)=blend_op::multiply);

      void change_value(ALLEGRO_BITMAP *bitmap, float amount, float (*operation)(float op1, float op2)=blend_op::multiply);




      void adjust_image(ALLEGRO_BITMAP *bitmap, float amount,
            void (*filter_func)(ALLEGRO_COLOR &, float, float (*)(float, float)),
            float (*filter_func_op)(float op1, float op2)=color::blend_op::multiply);




      bool basically_equal(const ALLEGRO_COLOR &col1, const ALLEGRO_COLOR &col2, float threshold);

      // TODO: fix for potential floating point errors
      bool operator ==(const ALLEGRO_COLOR &lhs, const ALLEGRO_COLOR &rhs);




      extern const ALLEGRO_COLOR null_color;
      extern const ALLEGRO_COLOR magic_pink;
      extern const ALLEGRO_COLOR transparent;
      extern const ALLEGRO_COLOR aliceblue;
      extern const ALLEGRO_COLOR antiquewhite;
      extern const ALLEGRO_COLOR aqua;
      extern const ALLEGRO_COLOR aquamarine;
      extern const ALLEGRO_COLOR azure;
      extern const ALLEGRO_COLOR beige;
      extern const ALLEGRO_COLOR bisque;
      extern const ALLEGRO_COLOR black;
      extern const ALLEGRO_COLOR blanchedalmond;
      extern const ALLEGRO_COLOR blue;
      extern const ALLEGRO_COLOR blueviolet;
      extern const ALLEGRO_COLOR brown;
      extern const ALLEGRO_COLOR burlywood;
      extern const ALLEGRO_COLOR cadetblue;
      extern const ALLEGRO_COLOR chartreuse;
      extern const ALLEGRO_COLOR chocolate;
      extern const ALLEGRO_COLOR coral;
      extern const ALLEGRO_COLOR cornflowerblue;
      extern const ALLEGRO_COLOR cornsilk;
      extern const ALLEGRO_COLOR crimson;
      extern const ALLEGRO_COLOR cyan;
      extern const ALLEGRO_COLOR darkblue;
      extern const ALLEGRO_COLOR darkcyan;
      extern const ALLEGRO_COLOR darkgoldenrod;
      extern const ALLEGRO_COLOR darkgray;
      extern const ALLEGRO_COLOR darkgreen;
      extern const ALLEGRO_COLOR darkkhaki;
      extern const ALLEGRO_COLOR darkmagenta;
      extern const ALLEGRO_COLOR darkolivegreen;
      extern const ALLEGRO_COLOR darkorange;
      extern const ALLEGRO_COLOR darkorchid;
      extern const ALLEGRO_COLOR darkred;
      extern const ALLEGRO_COLOR darksalmon;
      extern const ALLEGRO_COLOR darkseagreen;
      extern const ALLEGRO_COLOR darkslateblue;
      extern const ALLEGRO_COLOR darkslategray;
      extern const ALLEGRO_COLOR darkturquoise;
      extern const ALLEGRO_COLOR darkviolet;
      extern const ALLEGRO_COLOR deeppink;
      extern const ALLEGRO_COLOR deepskyblue;
      extern const ALLEGRO_COLOR dimgray;
      extern const ALLEGRO_COLOR dodgerblue;
      extern const ALLEGRO_COLOR firebrick;
      extern const ALLEGRO_COLOR floralwhite;
      extern const ALLEGRO_COLOR forestgreen;
      extern const ALLEGRO_COLOR fuchsia;
      extern const ALLEGRO_COLOR gainsboro;
      extern const ALLEGRO_COLOR ghostwhite;
      extern const ALLEGRO_COLOR goldenrod;
      extern const ALLEGRO_COLOR gold;
      extern const ALLEGRO_COLOR gray;
      extern const ALLEGRO_COLOR green;
      extern const ALLEGRO_COLOR greenyellow;
      extern const ALLEGRO_COLOR honeydew;
      extern const ALLEGRO_COLOR hotpink;
      extern const ALLEGRO_COLOR indianred;
      extern const ALLEGRO_COLOR indigo;
      extern const ALLEGRO_COLOR ivory;
      extern const ALLEGRO_COLOR khaki;
      extern const ALLEGRO_COLOR lavenderblush;
      extern const ALLEGRO_COLOR lavender;
      extern const ALLEGRO_COLOR lawngreen;
      extern const ALLEGRO_COLOR lemonchiffon;
      extern const ALLEGRO_COLOR lightblue;
      extern const ALLEGRO_COLOR lightcoral;
      extern const ALLEGRO_COLOR lightcyan;
      extern const ALLEGRO_COLOR lightgoldenrodyellow;
      extern const ALLEGRO_COLOR lightgreen;
      extern const ALLEGRO_COLOR lightgrey;
      extern const ALLEGRO_COLOR lightpink;
      extern const ALLEGRO_COLOR lightsalmon;
      extern const ALLEGRO_COLOR lightseagreen;
      extern const ALLEGRO_COLOR lightskyblue;
      extern const ALLEGRO_COLOR lightslategray;
      extern const ALLEGRO_COLOR lightsteelblue;
      extern const ALLEGRO_COLOR lightyellow;
      extern const ALLEGRO_COLOR lime;
      extern const ALLEGRO_COLOR limegreen;
      extern const ALLEGRO_COLOR linen;
      extern const ALLEGRO_COLOR magenta;
      extern const ALLEGRO_COLOR maroon;
      extern const ALLEGRO_COLOR mediumaquamarine;
      extern const ALLEGRO_COLOR mediumblue;
      extern const ALLEGRO_COLOR mediumorchid;
      extern const ALLEGRO_COLOR mediumpurple;
      extern const ALLEGRO_COLOR mediumseagreen;
      extern const ALLEGRO_COLOR mediumslateblue;
      extern const ALLEGRO_COLOR mediumspringgreen;
      extern const ALLEGRO_COLOR mediumturquoise;
      extern const ALLEGRO_COLOR mediumvioletred;
      extern const ALLEGRO_COLOR midnightblue;
      extern const ALLEGRO_COLOR mintcream;
      extern const ALLEGRO_COLOR mistyrose;
      extern const ALLEGRO_COLOR moccasin;
      extern const ALLEGRO_COLOR navajowhite;
      extern const ALLEGRO_COLOR navy;
      extern const ALLEGRO_COLOR oldlace;
      extern const ALLEGRO_COLOR olive;
      extern const ALLEGRO_COLOR olivedrab;
      extern const ALLEGRO_COLOR orange;
      extern const ALLEGRO_COLOR orangered;
      extern const ALLEGRO_COLOR orchid;
      extern const ALLEGRO_COLOR palegoldenrod;
      extern const ALLEGRO_COLOR palegreen;
      extern const ALLEGRO_COLOR paleturquoise;
      extern const ALLEGRO_COLOR palevioletred;
      extern const ALLEGRO_COLOR papayawhip;
      extern const ALLEGRO_COLOR peachpuff;
      extern const ALLEGRO_COLOR peru;
      extern const ALLEGRO_COLOR pink;
      extern const ALLEGRO_COLOR plum;
      extern const ALLEGRO_COLOR powderblue;
      extern const ALLEGRO_COLOR purple;
      extern const ALLEGRO_COLOR purwablue; // << WTF?
      extern const ALLEGRO_COLOR red;
      extern const ALLEGRO_COLOR rosybrown;
      extern const ALLEGRO_COLOR royalblue;
      extern const ALLEGRO_COLOR saddlebrown;
      extern const ALLEGRO_COLOR salmon;
      extern const ALLEGRO_COLOR sandybrown;
      extern const ALLEGRO_COLOR seagreen;
      extern const ALLEGRO_COLOR seashell;
      extern const ALLEGRO_COLOR sienna;
      extern const ALLEGRO_COLOR silver;
      extern const ALLEGRO_COLOR skyblue;
      extern const ALLEGRO_COLOR slateblue;
      extern const ALLEGRO_COLOR slategray;
      extern const ALLEGRO_COLOR snow;
      extern const ALLEGRO_COLOR springgreen;
      extern const ALLEGRO_COLOR steelblue;
      extern const ALLEGRO_COLOR tan;
      extern const ALLEGRO_COLOR teal;
      extern const ALLEGRO_COLOR thistle;
      extern const ALLEGRO_COLOR tomato;
      extern const ALLEGRO_COLOR turquoise;
      extern const ALLEGRO_COLOR violet;
      extern const ALLEGRO_COLOR wheat;
      extern const ALLEGRO_COLOR white;
      extern const ALLEGRO_COLOR whitesmoke;
      extern const ALLEGRO_COLOR yellow;
      extern const ALLEGRO_COLOR yellowgreen;
   }
}


