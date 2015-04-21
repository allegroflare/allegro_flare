

SET ALLEGRO_INCLUDE_DIR="E:/allegro-5.1.8-mingw-4.7.0/include"
SET ALLEGRO_LIB_DIR="E:/allegro-5.1.8-mingw-4.7.2/lib"

SET BOOST_INCLUDE_DIR="E:/boost/boost_1_57_0"
SET OPEN_CV_INCLUDE_DIR="E:/opencv-2.4.3/include"
SET CURL_INCLUDE_DIR="E:/curl-7.19.3/include"

SET ALLEGRO_FLARE_INCLUDE_DIR="E:/allegro_flare/include"

REM g++ *.o -Wall -lallegro -lallegro_color -lallegro_primitives -lallegro_audio -lallegro_dialog -lallegro_image -lallegro_font -lallegro_ttf -lallegro_acodec -o allegro_flare



REM "---------------------"

FOR %%i IN (../src/*) DO (
	g++ -c -o "./tmp/%%~ni.o" "../src/%%~ni.cpp" -I%ALLEGRO_FLARE_INCLUDE_DIR% -I%ALLEGRO_INCLUDE_DIR% -I%BOOST_INCLUDE_DIR% -I%OPEN_CV_INCLUDE_DIR% -I%CURL_INCLUDE_DIR%
)

