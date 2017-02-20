

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

CORE_ITEMS=appearance2d attributes automation bitmap_object blender camera2d camera3d color config cubemap decorated_cout display drawing_interface file_path file_path_object filesys_watcher framework frustum generate_textures grid2d element_id i18n image_processing interpolators json md5 model3d motion random render_cache render_music_notation object2d path2d placement2d placement3d profile_timer programming_language render_sample screen sha2 shader shadow_mask skeleton sound_object text_object timeline useful useful_php vec2b vec2d vec3d
BIN_ITEMS=font_bin sample_bin bitmap_bin model_bin
DI_ITEMS=drawing_interface_allegro5 drawing_interface_html_canvas drawing_interface_svg
FONT_ITEMS=font_bravura font_font_awesome font_segoe_ui_symbol
SCREEN_ITEMS=simple_notification_screen gamer_input_screen
GUI_WIDGET_ITEMS=style_assets button camera checkbox dial draggable_region float_spinner framed_window image int_spinner labeled_checkbox list_spinner music_notation picking_buffer progress_bar scaled_text scroll_area scrollbar slider spinner_base surface_area text text_area text_box text_input text_list toggle_button widget gui_screen window xy_controller
GUI_SURFACE_AREA_ITEMS=always_collide bitmap_alpha box box_padded circle column never_collide row
GUI_LAYOUT_LOADER_ITEMS=layout_loader_base gui_tool_layout_loader
WEB_ITEMS=file_downloader

CORE_OBJ_FILES=$(CORE_ITEMS:%=obj/%.o)
BIN_OBJ_FILES=$(BIN_ITEMS:%=obj/%.o)
DI_OBJ_FILES=$(DI_ITEMS:%=obj/%.o)
FONT_OBJ_FILES=$(FONT_ITEMS:%=obj/%.o)
SCREEN_OBJ_FILES=$(SCREEN_ITEMS:%=obj/%.o)
GUI_WIDGET_OBJ_FILES=$(GUI_WIDGET_ITEMS:%=obj/%.o)
GUI_SURFACE_AREA_OBJ_FILES=$(GUI_SURFACE_AREA_ITEMS:%=obj/%.o)
GUI_LAYOUT_LOADER_OBJ_FILES=$(GUI_LAYOUT_LOADER_ITEMS:%=obj/%.o)
WEB_OBJ_FILES=$(WEB_ITEMS:%=obj/%.o)


# Append platform-specific components to the items
# using this technique - http://stackoverflow.com/questions/714100/os-detecting-makefile


ifeq ($(OS), Windows_NT)
	BINARY_EXTENSION=.exe
	PLATFORM_FOLDER_NAME = win
else
	BINARY_EXTENSION=
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		PLATFORM_FOLDER_NAME = generic
	endif
	ifeq ($(UNAME_S),Darwin)
		PLATFORM_FOLDER_NAME = mac_os
	endif
endif



#
# Library Targets
# ===============================================
#

ALL_SOURCES := $(shell find src -name '*.cpp')
ALL_PLATFORM_SOURCES := $(shell find src/platform -name '*.cpp')
CURRENT_PLATFORM_SOURCES := $(shell find src/platform/$(PLATFORM_FOLDER_NAME) -name '*.cpp')

SOURCES := $(filter-out $(ALL_PLATFORM_SOURCES), $(ALL_SOURCES))
SOURCES += $(CURRENT_PLATFORM_SOURCES)
OBJECTS := $(SOURCES:src/%.cpp=obj/%.o)

obj/%.o: src/%.cpp
	g++ -c -std=gnu++11 -Wall $< -o $@ -I$(ALLEGRO_FLARE_DIR)/include -I$(ALLEGRO_DIR)/include -I./include

core: $(OBJECTS)
	@ar rs lib/lib$(ALLEGROFLARE_LIB_NAME).a $^
	@echo "building $(ALLEGROFLARE_LIB_NAME)"




#
# Example Programs
# ===============================================
#

EXAMPLES=$(wildcard examples/*.cpp)
EXAMPLE_OBJS=$(EXAMPLES:examples/%.cpp=bin/%$(BINARY_EXTENSION))

ALLEGRO_LIBS=-lallegro_color -lallegro_font -lallegro_ttf -lallegro_dialog -lallegro_audio -lallegro_acodec -lallegro_primitives -lallegro_image -lallegro_main -lallegro

examples: $(EXAMPLE_OBJS)

bin/%$(BINARY_EXTENSION): examples/gui/%.cpp
	@g++ -std=gnu++11 $< -o $@ -I$(ALLEGROFLARE_DIR)/include -I$(ALLEGRO_DIR)/include -L$(ALLEGROFLARE_DIR)/lib -l$(ALLEGROFLARE_LIB_NAME) -L$(ALLEGRO_LIB_DIR) $(ALLEGRO_LIBS)
	@echo "compiling $@"

bin/%$(BINARY_EXTENSION): examples/%.cpp
	@g++ -std=gnu++11 $< -o $@ -I$(ALLEGROFLARE_DIR)/include -I$(ALLEGRO_DIR)/include -L$(ALLEGROFLARE_DIR)/lib -l$(ALLEGROFLARE_LIB_NAME) -L$(ALLEGRO_LIB_DIR) $(ALLEGRO_LIBS)
	@echo "compiling $@"




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
	g++ -std=gnu++11 $< -o $@ -I$(ALLEGROFLARE_DIR)/include -I$(ALLEGRO_DIR)/include -L$(ALLEGROFLARE_DIR)/lib -l$(ALLEGROFLARE_LIB_NAME) -L$(ALLEGRO_LIB_DIR) $(ALLEGRO_TEST_LIBS) -lboost_unit_test_framework -lcurl




#
# Cleanup
# ===============================================
#

clean:
	-rm ./obj/*.o
	-rm ./lib/*.a
	-rm $(EXAMPLE_OBJS)
	-rm $(TEST_OBJS)
	-rm $(OBJECTS)
