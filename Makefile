

#
# Makefile for Allegro Flare
# ==========================
#


ALLEGRO_FLARE_VERSION_STR=0.8.6

INCLUDE_FLAGS=-IE:/allegro-5.1.11-mingw-edgar/include -IE:/allegro_flare/include



CORE_ITEMS=appearance2d attr_save_load automation bitmap_object blender camera2d camera3d color config data_attr display drawing_interface file_path file_path_object framework frustum generate_textures grid2d identification image_processing md5 model motion music_notation object2d paragraph path2d placement2d placement3d profile_timer programming_language render_sample screen sha2 shader skeleton sound_object text_object timeline useful
BIN_ITEMS=font_bin sample_bin bitmap_bin model_bin
DI_ITEMS=drawing_interface_allegro5 drawing_interface_html_canvas drawing_interface_svg
FONT_ITEMS=font_bravura font_font_awesome font_segoe_ui_symbol
SCREEN_ITEMS=simple_notification_screen gamer_input_screen filesys_change_notification_screen

CORE_OBJ_FILES=$(CORE_ITEMS:%=obj/%.o)
BIN_OBJ_FILES=$(BIN_ITEMS:%=obj/%.o)
DI_OBJ_FILES=$(DI_ITEMS:%=obj/%.o)
FONT_OBJ_FILES=$(FONT_ITEMS:%=obj/%.o)
SCREEN_OBJ_FILES=$(SCREEN_ITEMS:%=obj/%.o)


#
# Add platform-specific targets to the items
# using this technique - http://stackoverflow.com/questions/714100/os-detecting-makefile
#

ifeq ($(OS), Windows_NT)
	CORE_ITEMS += clipboard_win
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		CORE_ITEMS += clipboard_generic
	endif
endif



#
# Targets
#

core: $(CORE_OBJ_FILES) $(BIN_OBJ_FILES) $(DI_OBJ_FILES) $(FONT_OBJ_FILES) $(SCREEN_OBJ_FILES)
	ar rvs lib/liballegro_flare-$(ALLEGRO_FLARE_VERSION_STR)-mingw-4.8.1.a $^

$(CORE_OBJ_FILES): obj/%.o : src/%.cpp
	g++ -c -Wall -o obj/$(notdir $@) $< $(INCLUDE_FLAGS)

$(BIN_OBJ_FILES): obj/%.o : src/bins/%.cpp
	g++ -c -Wall -o obj/$(notdir $@) $< $(INCLUDE_FLAGS)

$(DI_OBJ_FILES): obj/%.o : src/drawing_interfaces/%.cpp
	g++ -c -Wall -o obj/$(notdir $@) $< $(INCLUDE_FLAGS)

$(FONT_OBJ_FILES): obj/%.o : src/fonts/%.cpp
	g++ -c -Wall -o obj/$(notdir $@) $< $(INCLUDE_FLAGS)

$(SCREEN_OBJ_FILES): obj/%.o : src/screens/%.cpp
	g++ -c -Wall -std=gnu++11 -o obj/$(notdir $@) $< $(INCLUDE_FLAGS)



#
# Example Programs
# ==========================
#


EXAMPLES=$(wildcard examples/*.cpp)
EXAMPLE_OBJS=$(EXAMPLES:examples/%.cpp=bin/%.exe)

examples: $(EXAMPLE_OBJS)

bin/%.exe: examples/%.cpp
	g++ -std=gnu++11 $< -o $@ -IE:/allegro_flare/include -IE:/allegro-5.1.11-mingw-edgar/include -LE:/allegro_flare/lib -lallegro_flare-0.8.6-mingw-4.8.1 -LE:/allegro-5.1.11-mingw-edgar/lib -lallegro_monolith-debug.dll



