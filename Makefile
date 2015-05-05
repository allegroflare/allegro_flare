




# These are some system variables that you might set:

CC=g++
CVER=-minigw-4.8.1
DELETE_FILE_COMMAND=del #rm for linux



# Here are the locations of the other library's header files, you might want to modify these:

ALLEGRO_INCLUDE_DIR=E:/allegro-5.1.8-mingw-4.7.0/include
BOOST_INCLUDE_DIR=E:/boost/boost_1_47






# Everything from here to the end of the file can be ignored

# These variables you do not set, they are automatic:

ALLEGRO_FLARE_INCLUDE_DIR=./include
SOURCEDIR=./src
EXAMPLESDIR=./examples
INCLUDE_FLAGS=-I$(ALLEGRO_INCLUDE_DIR) -I$(ALLEGRO_FLARE_INCLUDE_DIR)
# OBJECT_TEMP_DIR=./build/temp
# COMPILE_FLAGS=-Wall




# build targets:
# there are several different targets; based on your platform and dependencies you may have installed

all: allegro_flare appearance2d attr_save_load automation bitmap_object blender camera2d camera3d color config data_attr display drawing_interface file_path file_path_object frustum generate_textures grid2d identification image_processing interprocess_through_files md5 model model_bin motion music_notation object2d paragraph path2d placement2d placement3d profile_timer programming_language render_sample screen sha2 skeleton sound_object text_object timeline useful bins drawing_interfaces fonts screens windows
	ar rvs ./lib/liballegro_flare-0.8.5-mingw-4.8.1.a *.o

open_cv: cam_view open_cv_video

curl: curl

boost: interprocess shared_memory 

dmx: dmx

windows: clipboard_win midi_win 

# osx:

# linux:








# these are the independent build targets for each file

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

generate_textures:
	$(CC) -c -std=gnu++11 $(COMPILE_FLAGS) $(SOURCEDIR)/$@.cpp $(INCLUDE_FLAGS)

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

useful:
	$(CC) -c $(COMPILE_FLAGS) $(SOURCEDIR)/$@.cpp $(INCLUDE_FLAGS) 



# in bins/

bins: bitmap_bin font_bin sample_bin

bitmap_bin:
	$(CC) -c $(COMPILE_FLAGS) $(SOURCEDIR)/bins/$@.cpp $(INCLUDE_FLAGS) 

font_bin:
	$(CC) -c $(COMPILE_FLAGS) $(SOURCEDIR)/bins/$@.cpp $(INCLUDE_FLAGS) 

sample_bin:
	$(CC) -c $(COMPILE_FLAGS) $(SOURCEDIR)/bins/$@.cpp $(INCLUDE_FLAGS) 



# in drawing_interfaces/

drawing_interfaces: drawing_interface_allegro5 drawing_interface_html_canvas drawing_interface_svg

drawing_interface_allegro5:
	$(CC) -c $(COMPILE_FLAGS) $(SOURCEDIR)/drawing_interfaces/$@.cpp $(INCLUDE_FLAGS) 

drawing_interface_html_canvas:
	$(CC) -c $(COMPILE_FLAGS) $(SOURCEDIR)/drawing_interfaces/$@.cpp $(INCLUDE_FLAGS) 

drawing_interface_svg:
	$(CC) -c $(COMPILE_FLAGS) $(SOURCEDIR)/drawing_interfaces/$@.cpp $(INCLUDE_FLAGS) 



# in fonts/

fonts: font_bravura font_font_awesome font_segoe_ui_symbol

font_bravura:
	$(CC) -c $(COMPILE_FLAGS) $(SOURCEDIR)/fonts/$@.cpp $(INCLUDE_FLAGS) 

font_font_awesome:
	$(CC) -c $(COMPILE_FLAGS) $(SOURCEDIR)/fonts/$@.cpp $(INCLUDE_FLAGS) 

font_segoe_ui_symbol:
	$(CC) -c $(COMPILE_FLAGS) $(SOURCEDIR)/fonts/$@.cpp $(INCLUDE_FLAGS) 



# in screens/

screens: simple_notification_screen

simple_notification_screen:
	$(CC) -c -std=gnu++11 $(COMPILE_FLAGS) $(SOURCEDIR)/screens/$@.cpp $(INCLUDE_FLAGS)




# and finally, the cleanup

clean:
	$(DELETE_FILE_COMMAND) *o






#
# Example Programs
# ==========================
#

# here are the directories of the projects 
ALLEGRO_FLARE_DIR=E:/allegro_flare
ALLEGRO_DIR=E:/allegro-5.1.8-mingw-4.7.0

# these are the names of the libs you are linking
ALLEGRO_MONOLITH_LIB=allegro-5.1.8-monolith-md
ALLEGRO_FLARE_LIB=allegro_flare-0.8.5-mingw-4.8.1

examples: ex_masked_bitmap.exe ex_model_viewer.exe ex_generated_textures.exe

ex_masked_bitmap.exe: ./examples/ex_masked_bitmap.cpp
	$(CC) -c $(COMPILE_FLAGS) -std=gnu++11 $(EXAMPLESDIR)/$(basename $@).cpp $(INCLUDE_FLAGS)
	$(CC) $(basename $@).o -o $(EXAMPLESDIR)/$(basename $@).exe -l$(ALLEGRO_FLARE_LIB) -l$(ALLEGRO_MONOLITH_LIB) -L$(ALLEGRO_FLARE_DIR)/lib -L$(ALLEGRO_DIR)/lib

ex_model_viewer.exe: ./examples/ex_model_viewer.cpp
	$(CC) -c $(COMPILE_FLAGS) -std=gnu++11 $(EXAMPLESDIR)/$(basename $@).cpp $(INCLUDE_FLAGS)
	$(CC) $(basename $@).o -o $(EXAMPLESDIR)/$(basename $@).exe -l$(ALLEGRO_FLARE_LIB) -l$(ALLEGRO_MONOLITH_LIB) -L$(ALLEGRO_FLARE_DIR)/lib -L$(ALLEGRO_DIR)/lib

ex_generated_textures.exe: ./examples/ex_generated_textures.cpp
	$(CC) -c $(COMPILE_FLAGS) -std=gnu++11 $(EXAMPLESDIR)/$(basename $@).cpp $(INCLUDE_FLAGS)
	$(CC) $(basename $@).o -o $(EXAMPLESDIR)/$(basename $@).exe -l$(ALLEGRO_FLARE_LIB) -l$(ALLEGRO_MONOLITH_LIB) -L$(ALLEGRO_FLARE_DIR)/lib -L$(ALLEGRO_DIR)/lib



