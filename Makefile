

CC=g++
SOURCEDIR=./src
# OBJECT_TEMP_DIR=./build/temp
DELETE_FILE_COMMAND=del #rm for linux

ALLEGRO_INCLUDE_DIR=E:/allegro-5.1.8-mingw-4.7.0/include
ALLEGRO_FLARE_INCLUDE_DIR=E:/allegro_flare/include
BOOST_INCLUDE_DIR=E:/boost/boost_1_47
INCLUDE_FLAGS=-I$(ALLEGRO_INCLUDE_DIR) -I$(ALLEGRO_FLARE_INCLUDE_DIR)
# COMPILE_FLAGS=-Wall



# build targets:
# there are several different targets; based on your platform and dependencies you may have installed

all: allegro_flare appearance2d attr_save_load automation bitmap_object blender camera2d camera3d color config data_attr display drawing_interface file_path file_path_object frustum grid2d identification image_processing interprocess_through_files md5 model model_bin motion music_notation object2d paragraph path2d placement2d placement3d profile_timer programming_language render_sample screen sha2 skeleton sound_object text_object timeline useful_

open_cv: cam_view open_cv_video

curl: curl

boost: interprocess shared_memory 

dmx: dmx

windows: clipboard_win midi_win text_to_speech_win

# osx:

# linux:





# these are the independent build commands for each file

allegro_flare:
	$(CC) -c $(COMPILE_FLAGS) $(SOURCEDIR)/$@.cpp $(INCLUDE_FLAGS)

appearance2d:
	$(CC) -c $(COMPILE_FLAGS) $(SOURCEDIR)/$@.cpp $(INCLUDE_FLAGS)

attr_save_load:
	$(CC) -c $(COMPILE_FLAGS) $(SOURCEDIR)/$@.cpp $(INCLUDE_FLAGS)

automation:
	$(CC) -c $(COMPILE_FLAGS) $(SOURCEDIR)/$@.cpp $(INCLUDE_FLAGS)

bitmap_object:
	$(CC) -c $(COMPILE_FLAGS) $(SOURCEDIR)/$@.cpp $(INCLUDE_FLAGS)

blender:
	$(CC) -c $(COMPILE_FLAGS) $(SOURCEDIR)/$@.cpp $(INCLUDE_FLAGS)

cam_view:
	$(CC) -c $(COMPILE_FLAGS) $(SOURCEDIR)/$@.cpp $(INCLUDE_FLAGS)

camera2d:
	$(CC) -c $(COMPILE_FLAGS) $(SOURCEDIR)/$@.cpp $(INCLUDE_FLAGS)

camera3d:
	$(CC) -c $(COMPILE_FLAGS) $(SOURCEDIR)/$@.cpp $(INCLUDE_FLAGS)

clipboard_win:
	$(CC) -c $(COMPILE_FLAGS) $(SOURCEDIR)/$@.cpp $(INCLUDE_FLAGS)

color:
	$(CC) -c $(COMPILE_FLAGS) $(SOURCEDIR)/$@.cpp $(INCLUDE_FLAGS)

config:
	$(CC) -c $(COMPILE_FLAGS) $(SOURCEDIR)/$@.cpp $(INCLUDE_FLAGS)

curl:
	$(CC) -c $(COMPILE_FLAGS) $(SOURCEDIR)/$@.cpp $(INCLUDE_FLAGS)

data_attr:
	$(CC) -c $(COMPILE_FLAGS) $(SOURCEDIR)/$@.cpp $(INCLUDE_FLAGS)

display:
	$(CC) -c $(COMPILE_FLAGS) $(SOURCEDIR)/$@.cpp $(INCLUDE_FLAGS)

dmx:
	$(CC) -c $(COMPILE_FLAGS) $(SOURCEDIR)/$@.cpp $(INCLUDE_FLAGS)

drawing_interface:
	$(CC) -c $(COMPILE_FLAGS) $(SOURCEDIR)/$@.cpp $(INCLUDE_FLAGS)

file_path:
	$(CC) -c $(COMPILE_FLAGS) $(SOURCEDIR)/$@.cpp $(INCLUDE_FLAGS)

file_path_object:
	$(CC) -c $(COMPILE_FLAGS) $(SOURCEDIR)/$@.cpp $(INCLUDE_FLAGS)

frustum:
	$(CC) -c $(COMPILE_FLAGS) $(SOURCEDIR)/$@.cpp $(INCLUDE_FLAGS)

grid2d:
	$(CC) -c $(COMPILE_FLAGS) $(SOURCEDIR)/$@.cpp $(INCLUDE_FLAGS)

identification:
	$(CC) -c $(COMPILE_FLAGS) $(SOURCEDIR)/$@.cpp $(INCLUDE_FLAGS)

image_processing:
	$(CC) -c $(COMPILE_FLAGS) $(SOURCEDIR)/$@.cpp $(INCLUDE_FLAGS)

interprocess:
	$(CC) -c $(COMPILE_FLAGS) $(SOURCEDIR)/$@.cpp $(INCLUDE_FLAGS)

interprocess_through_files:
	$(CC) -c $(COMPILE_FLAGS) $(SOURCEDIR)/$@.cpp $(INCLUDE_FLAGS) 

md5:
	$(CC) -c $(COMPILE_FLAGS) $(SOURCEDIR)/$@.cpp $(INCLUDE_FLAGS) 

midi_win:
	$(CC) -c $(COMPILE_FLAGS) $(SOURCEDIR)/$@.cpp $(INCLUDE_FLAGS) 

model:
	$(CC) -c $(COMPILE_FLAGS) $(SOURCEDIR)/$@.cpp $(INCLUDE_FLAGS) 

model_bin:
	$(CC) -c $(COMPILE_FLAGS) $(SOURCEDIR)/$@.cpp $(INCLUDE_FLAGS) 

motion:
	$(CC) -c $(COMPILE_FLAGS) $(SOURCEDIR)/$@.cpp $(INCLUDE_FLAGS) 

music_notation:
	$(CC) -c $(COMPILE_FLAGS) $(SOURCEDIR)/$@.cpp $(INCLUDE_FLAGS) 

object2d:
	$(CC) -c $(COMPILE_FLAGS) $(SOURCEDIR)/$@.cpp $(INCLUDE_FLAGS) 

open_cv_video:
	$(CC) -c $(COMPILE_FLAGS) $(SOURCEDIR)/$@.cpp $(INCLUDE_FLAGS) 

path2d:
	$(CC) -c $(COMPILE_FLAGS) $(SOURCEDIR)/$@.cpp $(INCLUDE_FLAGS) 

paragraph:
	$(CC) -c $(COMPILE_FLAGS) $(SOURCEDIR)/$@.cpp $(INCLUDE_FLAGS) 

placement2d:
	$(CC) -c $(COMPILE_FLAGS) $(SOURCEDIR)/$@.cpp $(INCLUDE_FLAGS) 

placement3d:
	$(CC) -c $(COMPILE_FLAGS) $(SOURCEDIR)/$@.cpp $(INCLUDE_FLAGS) 

profile_timer:
	$(CC) -c $(COMPILE_FLAGS) $(SOURCEDIR)/$@.cpp $(INCLUDE_FLAGS) 

programming_language:
	$(CC) -c $(COMPILE_FLAGS) $(SOURCEDIR)/$@.cpp $(INCLUDE_FLAGS) 

render_sample:
	$(CC) -c $(COMPILE_FLAGS) $(SOURCEDIR)/$@.cpp $(INCLUDE_FLAGS) 

screen:
	$(CC) -c $(COMPILE_FLAGS) $(SOURCEDIR)/$@.cpp $(INCLUDE_FLAGS) 

sha2:
	$(CC) -c $(COMPILE_FLAGS) $(SOURCEDIR)/$@.cpp $(INCLUDE_FLAGS) 

shared_memory:
	$(CC) -c $(COMPILE_FLAGS) $(SOURCEDIR)/$@.cpp $(INCLUDE_FLAGS) 

skeleton:
	$(CC) -c $(COMPILE_FLAGS) $(SOURCEDIR)/$@.cpp $(INCLUDE_FLAGS) 

sound_object:
	$(CC) -c $(COMPILE_FLAGS) $(SOURCEDIR)/$@.cpp $(INCLUDE_FLAGS) 

text_object:
	$(CC) -c $(COMPILE_FLAGS) $(SOURCEDIR)/$@.cpp $(INCLUDE_FLAGS) 

text_to_speech_win:
	$(CC) -c $(COMPILE_FLAGS) $(SOURCEDIR)/$@.cpp $(INCLUDE_FLAGS) 

timeline:
	$(CC) -c $(COMPILE_FLAGS) $(SOURCEDIR)/$@.cpp $(INCLUDE_FLAGS) 

useful_:
	$(CC) -c $(COMPILE_FLAGS) $(SOURCEDIR)/$@.cpp $(INCLUDE_FLAGS) 



# and finally, the cleanup

clean:
	$(DELETE_FILE_COMMAND) *o

