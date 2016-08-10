

#
# ===============================================
# Makefile for AllegroFlare
# ===============================================
#



#
# Build Settings and Directories
# ===============================================
#

LIBS_ROOT=/Users/markoates/Repos
ALLEGRO_DIR=$(LIBS_ROOT)/allegro5
ALLEGRO_LIB_DIR=$(LIBS_ROOT)/allegro5/build/lib
ALLEGROFLARE_DIR=$(LIBS_ROOT)/allegro_flare



#
# Build Settings and Directories
# ===============================================
#

ALLEGROFLARE_VERSION_STR=0.8.8wip
ALLEGROFLARE_LIB_NAME=allegro_flare-$(ALLEGROFLARE_VERSION_STR)
INCLUDE_FLAGS=-I$(ALLEGRO_DIR)/include -I$(ALLEGROFLARE_DIR)/include



#
# Core components
# ===============================================
#

CORE_ITEMS=appearance2d attributes automation bitmap_object blender camera2d camera3d color config cubemap data_attr decorated_cout display drawing_interface file_path file_path_object filesys_watcher framework frustum generate_textures grid2d element_id i18n image_processing interpolators json md5 model3d motion render_cache render_music_notation object2d path2d placement2d placement3d profile_timer programming_language render_sample screen sha2 shader skeleton sound_object text_object timeline useful useful_php vec2d vec3d
BIN_ITEMS=font_bin sample_bin bitmap_bin model_bin
DI_ITEMS=drawing_interface_allegro5 drawing_interface_html_canvas drawing_interface_svg
FONT_ITEMS=font_bravura font_font_awesome font_segoe_ui_symbol
SCREEN_ITEMS=simple_notification_screen gamer_input_screen
GUI_WIDGET_ITEMS=style_assets button checkbox dial draggable_region family float_spinner framed_window image int_spinner labeled_checkbox list_spinner music_notation picking_buffer progress_bar scaled_text scroll_area scrollbar slider spinner_base surface_area text text_area text_box text_input text_list toggle_button widget gui_screen window xy_controller
GUI_SURFACE_AREA_ITEMS=bitmap_alpha box box_padded circle column row

CORE_OBJ_FILES=$(CORE_ITEMS:%=obj/%.o)
BIN_OBJ_FILES=$(BIN_ITEMS:%=obj/%.o)
DI_OBJ_FILES=$(DI_ITEMS:%=obj/%.o)
FONT_OBJ_FILES=$(FONT_ITEMS:%=obj/%.o)
SCREEN_OBJ_FILES=$(SCREEN_ITEMS:%=obj/%.o)
GUI_WIDGET_OBJ_FILES=$(GUI_WIDGET_ITEMS:%=obj/%.o)
GUI_SURFACE_AREA_OBJ_FILES=$(GUI_SURFACE_AREA_ITEMS:%=obj/%.o)


# Append platform-specific components to the items
# using this technique - http://stackoverflow.com/questions/714100/os-detecting-makefile

ifeq ($(OS), Windows_NT)
	BINARY_EXTENSION=.exe
	CORE_ITEMS += clipboard_win
else
	BINARY_EXTENSION=
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		CORE_ITEMS += clipboard_generic
	endif
	ifeq ($(UNAME_S),Darwin)
		CORE_ITEMS += clipboard_osx
	endif
endif




#
# Library Targets
# ===============================================
#

core: $(CORE_OBJ_FILES) $(BIN_OBJ_FILES) $(DI_OBJ_FILES) $(FONT_OBJ_FILES) $(SCREEN_OBJ_FILES) $(GUI_WIDGET_OBJ_FILES) $(GUI_SURFACE_AREA_OBJ_FILES)
	ar rs lib/lib$(ALLEGROFLARE_LIB_NAME).a $^

$(CORE_OBJ_FILES): obj/%.o : source/%.cpp
	g++ -c -std=gnu++11 -Wall -o obj/$(notdir $@) $< $(INCLUDE_FLAGS)

$(BIN_OBJ_FILES): obj/%.o : source/bins/%.cpp
	g++ -c -Wall -o obj/$(notdir $@) $< $(INCLUDE_FLAGS)

$(DI_OBJ_FILES): obj/%.o : source/drawing_interfaces/%.cpp
	g++ -c -std=gnu++11 -Wall -o obj/$(notdir $@) $< $(INCLUDE_FLAGS)

$(FONT_OBJ_FILES): obj/%.o : source/fonts/%.cpp
	g++ -c -Wall -o obj/$(notdir $@) $< $(INCLUDE_FLAGS)

$(SCREEN_OBJ_FILES): obj/%.o : source/screens/%.cpp
	g++ -c -std=gnu++11 -Wall -o obj/$(notdir $@) $< $(INCLUDE_FLAGS)

$(GUI_WIDGET_OBJ_FILES): obj/%.o : source/gui/%.cpp
	g++ -c -std=gnu++11 -o obj/$(notdir $@) $< $(INCLUDE_FLAGS)

$(GUI_SURFACE_AREA_OBJ_FILES): obj/%.o : source/gui/surface_areas/%.cpp
	g++ -c -std=gnu++11 -o obj/$(notdir $@) $< $(INCLUDE_FLAGS)




#
# Example Programs
# ===============================================
#

EXAMPLES=$(wildcard examples/*.cpp)
EXAMPLE_OBJS=$(EXAMPLES:examples/%.cpp=bin/%$(BINARY_EXTENSION))
GUI_EXAMPLES=$(wildcard examples/gui/*.cpp)
GUI_EXAMPLE_OBJS=$(GUI_EXAMPLES:examples/gui/%.cpp=bin/%$(BINARY_EXTENSION))

ALLEGRO_LIBS=-lallegro_color -lallegro_font -lallegro_ttf -lallegro_dialog -lallegro_audio -lallegro_acodec -lallegro_primitives -lallegro_image -lallegro_main -lallegro

examples: $(EXAMPLE_OBJS) $(GUI_EXAMPLE_OBJS)

bin/%$(BINARY_EXTENSION): examples/gui/%.cpp
	g++ -std=gnu++11 $< -o $@ -I$(ALLEGROFLARE_DIR)/include -I$(ALLEGRO_DIR)/include -L$(ALLEGROFLARE_DIR)/lib -l$(ALLEGROFLARE_LIB_NAME) -L$(ALLEGRO_LIB_DIR) $(ALLEGRO_LIBS)

bin/%$(BINARY_EXTENSION): examples/%.cpp
	g++ -std=gnu++11 $< -o $@ -I$(ALLEGROFLARE_DIR)/include -I$(ALLEGRO_DIR)/include -L$(ALLEGROFLARE_DIR)/lib -l$(ALLEGROFLARE_LIB_NAME) -L$(ALLEGRO_LIB_DIR) $(ALLEGRO_LIBS)




#
# Documentation
# ===============================================
#

documentation:
	python docs/compile_docs.py




#
# Testing
# ===============================================
#

TESTS=$(wildcard tests/*.cpp)
TEST_OBJS=$(TESTS:tests/%.cpp=bin/%$(BINARY_EXTENSION))

ALLEGRO_TEST_LIBS=-lallegro_color -lallegro_font -lallegro_ttf -lallegro_dialog -lallegro_audio -lallegro_acodec -lallegro_primitives -lallegro_image -lallegro

tests: $(TEST_OBJS)

bin/%$(BINARY_EXTENSION): tests/%.cpp lib/lib$(ALLEGROFLARE_LIB_NAME).a
	g++ -std=gnu++11 $< -o $@ -I$(ALLEGROFLARE_DIR)/include -I$(ALLEGRO_DIR)/include -L$(ALLEGROFLARE_DIR)/lib -l$(ALLEGROFLARE_LIB_NAME) -L$(ALLEGRO_LIB_DIR) $(ALLEGRO_TEST_LIBS) -lboost_unit_test_framework




#
# Cleanup
# ===============================================
#

clean:
	-rm ./obj/*.o
	-rm ./lib/*.a
	-rm $(EXAMPLE_OBJS)
	-rm $(GUI_EXAMPLE_OBJS)
	-rm $(TEST_OBJS)

