


# bins drawing_interfaces fonts screens


ALLEGRO_FLARE_VERSION_STR=0.8.6

INCLUDE_FLAGS=-IE:/allegro-5.1.11-mingw-edgar/include -IE:/allegro_flare/include



CORE_ITEMS=appearance2d attr_save_load automation bitmap_object blender camera2d camera3d clipboard_generic color config data_attr display drawing_interface file_path file_path_object framework frustum generate_textures grid2d identification image_processing md5 model model_bin motion music_notation object2d paragraph path2d placement2d placement3d profile_timer programming_language render_sample screen sha2 skeleton sound_object text_object timeline useful

BIN_ITEMS=font_bin sample_bin bitmap_bin

DI_ITEMS=drawing_interface_allegro5 drawing_interface_html_canvas drawing_interface_svg

FONT_ITEMS=font_bravura font_font_awesome font_segoe_ui_symbol

SCREEN_ITEMS=simple_notification_screen



OBJ_FILES=$(CORE_ITEMS:%=obj/%.o)
BIN_OBJ_FILES=$(BIN_ITEMS:%=obj/%.o)
DI_OBJ_FILES=$(DI_ITEMS:%=obj/%.o)
FONT_OBJ_FILES=$(FONT_ITEMS:%=obj/%.o)
SCREEN_OBJ_FILES=$(SCREEN_ITEMS:%=obj/%.o)



core: $(OBJ_FILES) $(BIN_OBJ_FILES) $(DI_OBJ_FILES) $(FONT_OBJ_FILES) $(SCREEN_OBJ_FILES)
	ar rvs lib/liballegro_flare-$(ALLEGRO_FLARE_VERSION_STR)-mingw-4.8.1.a $^



$(OBJ_FILES): obj/%.o : src/%.cpp
	g++ -c -std=gnu++11 -o obj/$(notdir $@) $< $(INCLUDE_FLAGS)

$(BIN_OBJ_FILES): obj/%.o : src/bins/%.cpp
	g++ -c -std=gnu++11 -o obj/$(notdir $@) $< $(INCLUDE_FLAGS)

$(DI_OBJ_FILES): obj/%.o : src/drawing_interfaces/%.cpp
	g++ -c -std=gnu++11 -o obj/$(notdir $@) $< $(INCLUDE_FLAGS)

$(FONT_OBJ_FILES): obj/%.o : src/fonts/%.cpp
	g++ -c -std=gnu++11 -o obj/$(notdir $@) $< $(INCLUDE_FLAGS)

$(SCREEN_OBJ_FILES): obj/%.o : src/screens/%.cpp
	g++ -c -std=gnu++11 -o obj/$(notdir $@) $< $(INCLUDE_FLAGS)




#
# Example Programs
# ==========================
#

# here are the directories of the projects 
#

# these are the names of the libs you are linking
EXAMPLESDIR=./examples
ALLEGRO_BASE_DIR=E:/allegro-5.1.11-mingw-edgar
ALLEGRO_FLARE_BASE_DIR=E:/allegro_flare
ALLEGRO_MONOLITH_LIB=allegro_monolith-debug.dll
ALLEGRO_FLARE_LIB=allegro_flare-$(ALLEGRO_FLARE_VERSION_STR)-mingw-4.8.1
CC=g++

examples: ex_masked_bitmap.exe ex_model_viewer.exe ex_histogram.exe ex_unicode_font_viewer.exe test_encryption.exe test_generated_textures.exe ex_blur.exe

ex_masked_bitmap.exe: ./examples/ex_masked_bitmap.cpp
	$(CC) -c $(COMPILE_FLAGS) -std=gnu++11 $(EXAMPLESDIR)/$(basename $@).cpp $(INCLUDE_FLAGS)
	$(CC) $(basename $@).o -o $(EXAMPLESDIR)/$(basename $@).exe -l$(ALLEGRO_FLARE_LIB) -l$(ALLEGRO_MONOLITH_LIB) -L$(ALLEGRO_FLARE_BASE_DIR)/lib -L$(ALLEGRO_BASE_DIR)/lib

ex_model_viewer.exe: ./examples/ex_model_viewer.cpp
	$(CC) -c $(COMPILE_FLAGS) -std=gnu++11 $(EXAMPLESDIR)/$(basename $@).cpp $(INCLUDE_FLAGS)
	$(CC) $(basename $@).o -o $(EXAMPLESDIR)/$(basename $@).exe -l$(ALLEGRO_FLARE_LIB) -l$(ALLEGRO_MONOLITH_LIB) -L$(ALLEGRO_FLARE_BASE_DIR)/lib -L$(ALLEGRO_BASE_DIR)/lib

ex_histogram.exe: ./examples/ex_histogram.cpp
	$(CC) -c $(COMPILE_FLAGS) -std=gnu++11 $(EXAMPLESDIR)/$(basename $@).cpp $(INCLUDE_FLAGS)
	$(CC) $(basename $@).o -o $(EXAMPLESDIR)/$(basename $@).exe -l$(ALLEGRO_FLARE_LIB) -l$(ALLEGRO_MONOLITH_LIB) -L$(ALLEGRO_FLARE_BASE_DIR)/lib -L$(ALLEGRO_BASE_DIR)/lib

ex_unicode_font_viewer.exe: ./examples/ex_unicode_font_viewer.cpp
	$(CC) -c $(COMPILE_FLAGS) -std=gnu++11 $(EXAMPLESDIR)/$(basename $@).cpp $(INCLUDE_FLAGS)
	$(CC) $(basename $@).o -o $(EXAMPLESDIR)/$(basename $@).exe -l$(ALLEGRO_FLARE_LIB) -l$(ALLEGRO_MONOLITH_LIB) -L$(ALLEGRO_FLARE_BASE_DIR)/lib -L$(ALLEGRO_BASE_DIR)/lib

test_encryption.exe: ./examples/test_encryption.cpp
	$(CC) -c $(COMPILE_FLAGS) -std=gnu++11 $(EXAMPLESDIR)/$(basename $@).cpp $(INCLUDE_FLAGS)
	$(CC) $(basename $@).o -o $(EXAMPLESDIR)/$(basename $@).exe -l$(ALLEGRO_FLARE_LIB) -l$(ALLEGRO_MONOLITH_LIB) -L$(ALLEGRO_FLARE_BASE_DIR)/lib -L$(ALLEGRO_BASE_DIR)/lib

test_generated_textures.exe: ./examples/test_generated_textures.cpp
	$(CC) -c $(COMPILE_FLAGS) -std=gnu++11 $(EXAMPLESDIR)/$(basename $@).cpp $(INCLUDE_FLAGS)
	$(CC) $(basename $@).o -o $(EXAMPLESDIR)/$(basename $@).exe -l$(ALLEGRO_FLARE_LIB) -l$(ALLEGRO_MONOLITH_LIB) -L$(ALLEGRO_FLARE_BASE_DIR)/lib -L$(ALLEGRO_BASE_DIR)/lib

ex_blur.exe: ./examples/ex_blur.cpp
	$(CC) -c $(COMPILE_FLAGS) -std=gnu++11 $(EXAMPLESDIR)/$(basename $@).cpp $(INCLUDE_FLAGS)
	$(CC) $(basename $@).o -o $(EXAMPLESDIR)/$(basename $@).exe -l$(ALLEGRO_FLARE_LIB) -l$(ALLEGRO_MONOLITH_LIB) -L$(ALLEGRO_FLARE_BASE_DIR)/lib -L$(ALLEGRO_BASE_DIR)/lib



