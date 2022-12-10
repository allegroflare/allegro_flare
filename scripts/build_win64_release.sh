#!/bin/sh


## TODO: validate "unzip" is present


SOURCE_URL="https://drive.google.com/uc?export=download&id=1NyqegdnLt8auGmsZfq9aeIBAbUmv-I6N";
SOURCE_FOLDER_NAME="Krampus22_test1-SourceRelease-221209225033UTC"

TEMP_BUILD_DIR="/c/Users/Mark/Desktop/temp_location_for_building/"
FOOBAR="local_zip_name.zip"
FOOBAR_WITHOUT_ZIP="local_zip_name"


#"Krampus22_test1-SourceRelease-221209225033UTC.zip"
#"https://drive.google.com/uc?export=download&id=1NyqegdnLt8auGmsZfq9aeIBAbUmv-I6N"


# Note a "share link":
# https://drive.google.com/file/d/1NyqegdnLt8auGmsZfq9aeIBAbUmv-I6N/view?usp=share_link
# ... converted into a direct download link:
# "https://drive.google.com/uc?export=download&id=1NyqegdnLt8auGmsZfq9aeIBAbUmv-I6N"


# Create the necessary temp build folder if it does not exist

mkdir -p $TEMP_BUILD_DIR


# Download the source release

echo "===== Downloading $SOURCE_URL"
curl -L -o $TEMP_BUILD_DIR$FOOBAR $SOURCE_URL


# Go to the temp location, unzip the folder, and make

(cd $TEMP_BUILD_DIR || exit 1)

(cd $TEMP_BUILD_DIR && (unzip $FOOBAR || exit 1))

(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && make)


# Cleanup the unnecessary folders / files

(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && rm -rdf include/)
(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && rm -rdf programs/)
(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && rm -rdf src/)
(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && rm Makefile)



(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && cp /mingw64/bin/allegro-5.2.dll ./allegro-5.2.dll)
(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && cp /mingw64/bin/allegro_acodec-5.2.dll ./allegro_acodec-5.2.dll)
(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && cp /mingw64/bin/allegro_audio-5.2.dll ./allegro_audio-5.2.dll)
(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && cp /mingw64/bin/allegro_color-5.2.dll ./allegro_color-5.2.dll)
(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && cp /mingw64/bin/allegro_dialog-5.2.dll ./allegro_dialog-5.2.dll)
(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && cp /mingw64/bin/allegro_font-5.2.dll ./allegro_font-5.2.dll)
(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && cp /mingw64/bin/allegro_image-5.2.dll ./allegro_image-5.2.dll)
(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && cp /mingw64/bin/allegro_primitives-5.2.dll ./allegro_primitives-5.2.dll)
(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && cp /mingw64/bin/allegro_ttf-5.2.dll ./allegro_ttf-5.2.dll)
(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && cp /mingw64/bin/libgcc_s_seh-1.dll ./libgcc_s_seh-1.dll)
(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && cp /mingw64/bin/libdumb.dll ./libdumb.dll)
(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && cp /mingw64/bin/libFLAC-8.dll ./libFLAC-8.dll)
(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && cp /mingw64/bin/libopusfile-0.dll ./libopusfile-0.dll)
(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && cp /mingw64/bin/libvorbisfile-3.dll ./libvorbisfile-3.dll)
(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && cp /mingw64/bin/libopenal-1.dll ./libopenal-1.dll)




allegro_acodec-5.2.dll
allegro_audio-5.2.dll
allegro_color-5.2.dll
allegro_dialog-5.2.dll
allegro_font-5.2.dll
allegro_image-5.2.dll
allegro_main-5.2.dll
allegro_memfile-5.2.dll
allegro_physfs-5.2.dll
allegro_primitives-5.2.dll
allegro_ttf-5.2.dll
allegro_video-5.2.dll
allegro-5.2.dll
libbz2-1.dll
libdumb.dll
libFLAC-8.dll
libfreetype-6.dll
libgcc_s_seh-1.dll
libglib-2.0-0.dll
libgraphite2.dll
libharfbuzz-0.dll
libhogweed-5.dll
libiconv-2.dll
libintl-8.dll
libjpeg-8.dll
libogg-0.dll
libopenal-1.dll
libopus-0.dll
libopusfile-0.dll
libpcre-1.dll
libpng16-16.dll
libstdc++-6.dll
libtheora-0.dll
libvorbis-0.dll
libvorbisfile-3.dll
libwebp-7.dll
libwinpthread-1.dll
zlib1.dll

