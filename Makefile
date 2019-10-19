

#
# ===============================================
# Makefile for AllegroFlare
# ===============================================
#



#
# Build Settings and Directories
# ===============================================
#

LIBS_ROOT=/usr/lib/
ALLEGRO_INCLUDE_DIR=/usr/include/allegro5
ALLEGRO_LIB_DIR=/usr/lib
ALLEGROFLARE_DIR=${PWD}
GOOGLE_TEST_LIB_DIR=/usr/lib
GOOGLE_TEST_INCLUDE_DIR=/usr/include/gtest
CXXFLAGS=""


#
# Build Settings and Directories
# ===============================================
#

ALLEGROFLARE_VERSION_STR=0.9.0wip
ALLEGROFLARE_LIB_NAME=allegro_flare-$(ALLEGROFLARE_VERSION_STR)
INCLUDE_FLAGS=-I$(ALLEGRO_DIR)/include -I$(ALLEGROFLARE_DIR)/include



#
# Library Targets
# ===============================================
#

# Append platform-specific components to the items
# using this technique - http://stackoverflow.com/questions/714100/os-detecting-makefile

ifeq ($(OS), Windows_NT)
	BINARY_EXTENSION=.exe
	PLATFORM_FOLDER_NAME = win
else
	BINARY_EXTENSION=
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		LIBS_ROOT=/usr/lib
		ALLEGRO_INCLUDE_DIR=/usr/include/allegro5
		ALLEGRO_LIB_DIR=/usr/lib
		ALLEGROFLARE_DIR=${PWD}
		GOOGLE_TEST_LIB_DIR=/usr/lib
		GOOGLE_TEST_INCLUDE_DIR=/usr/include/gtest
		PLATFORM_FOLDER_NAME = generic
	endif
	ifeq ($(UNAME_S),Darwin)
		# WARNING : Non-standard lib root ! It usually is in /Library/ or /opt/lib (if user has brew or Mac Ports)
		LIBS_ROOT=/Users/markoates/Repos
		ALLEGRO_INCLUDE_DIR=$(LIBS_ROOT)/allegro5
		ALLEGRO_DIR=$(LIBS_ROOT)/allegro5
		ALLEGRO_LIB_DIR=$(LIBS_ROOT)/allegro5/build/lib
		GOOGLE_TEST_DIR=$(LIBS_ROOT)/googletest
		GOOGLE_TEST_LIB_DIR=$(GOOGLE_TEST_DIR)/build/googlemock/gtest
		GOOGLE_TEST_INCLUDE_DIR=$(GOOGLE_TEST_DIR)/googletest/include
		PLATFORM_FOLDER_NAME = mac_os
		
	endif
endif


ALL_SOURCES := $(shell find src -name '*.cpp')
ALL_PLATFORM_SOURCES := $(shell find src/allegro_flare/platform -name '*.cpp')
CURRENT_PLATFORM_SOURCES := $(shell find src/allegro_flare/platform/$(PLATFORM_FOLDER_NAME) -name '*.cpp')

SOURCES := $(filter-out $(ALL_PLATFORM_SOURCES), $(ALL_SOURCES))
SOURCES += $(CURRENT_PLATFORM_SOURCES)
OBJECTS := $(SOURCES:src/%.cpp=obj/%.o)
REQUIRED_DIRECTORIES := $(dir $(OBJECTS))

core: $(OBJECTS)
	@echo "building $(ALLEGROFLARE_LIB_NAME)"
	@ar rs lib/lib$(ALLEGROFLARE_LIB_NAME).a $^

obj/%.o: src/%.cpp | required_obj_dirs
	@echo "compiling $< -> $@"
	@g++ -c -Wnon-virtual-dtor -std=gnu++11 -Wall $< -o $@ -I$(ALLEGRO_FLARE_DIR)/include -I$(ALLEGRO_INCLUDE_DIR)/include -I./include


required_obj_dirs:
	@echo "creating required directories"
	@mkdir -p $(REQUIRED_DIRECTORIES)
	@mkdir -p bin/tests
	@mkdir -p lib

#
# Example Programs
# ===============================================
#

EXAMPLES=$(wildcard examples/*.cpp)
EXAMPLE_OBJS=$(EXAMPLES:examples/%.cpp=bin/%$(BINARY_EXTENSION))

ALLEGRO_LIBS=-lallegro_color -lallegro_font -lallegro_ttf -lallegro_dialog -lallegro_audio -lallegro_acodec -lallegro_primitives -lallegro_image -lallegro_main -lallegro
ifeq ($(OS), Windows_NT)
	OPENGL_LIB=-lopengl32
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		OPENGL_LIB=[ERROR:OPENGL_LIBS_NOT_DEFINED_FOR_LINUX]
	endif
	ifeq ($(UNAME_S),Darwin)
		OPENGL_LIB=-framework OpenGL
	endif
endif

examples: $(EXAMPLE_OBJS)

bin/%$(BINARY_EXTENSION): examples/gui/%.cpp
	@g++ -std=gnu++11 $< -o $@ -I$(ALLEGROFLARE_DIR)/include -I$(ALLEGRO_INCLUDE_DIR)/include -L$(ALLEGROFLARE_DIR)/lib -l$(ALLEGROFLARE_LIB_NAME) -L$(ALLEGRO_LIB_DIR) $(ALLEGRO_LIBS)
	@echo "compiling $< -> $@"

bin/%$(BINARY_EXTENSION): examples/%.cpp
	@g++ -std=gnu++11 $< -o $@ -I$(ALLEGROFLARE_DIR)/include -I$(ALLEGRO_INCLUDE_DIR)/include -L$(ALLEGROFLARE_DIR)/lib -l$(ALLEGROFLARE_LIB_NAME) -L$(ALLEGRO_LIB_DIR) $(ALLEGRO_LIBS) $(OPENGL_LIB)
	@echo "compiling $< -> $@"




#
# Documentation
# ===============================================
#

documentation:
	python docs/build_scripts/parse_source.py
	python docs/build_scripts/compile_docs.py




#
# Testing
# ===============================================
#

TEST_SOURCES := $(shell find tests -name '*Test.cpp' -o -name '*_test.cpp')
TEST_OBJS=$(TEST_SOURCES:tests/%.cpp=bin/tests/%$(BINARY_EXTENSION))

ALLEGRO_TEST_LIBS=-lallegro_color -lallegro_font -lallegro_ttf -lallegro_dialog -lallegro_audio -lallegro_acodec -lallegro_primitives -lallegro_image -lallegro
GOOGLE_TEST_LIB=-lgtest

tests: $(TEST_OBJS)

bin/tests/%$(BINARY_EXTENSION): tests/%.cpp lib/lib$(ALLEGROFLARE_LIB_NAME).a
	@mkdir -p $(@D)
	@echo "compiling $< -> $@"
	@g++ -std=gnu++11 $< -o $@ -I$(ALLEGROFLARE_DIR)/include -I$(ALLEGRO_INCLUDE_DIR)/include -I$(GOOGLE_TEST_INCLUDE_DIR) -L$(ALLEGROFLARE_DIR)/lib -l$(ALLEGROFLARE_LIB_NAME) -L$(ALLEGRO_LIB_DIR) -L$(GOOGLE_TEST_LIB_DIR) $(ALLEGRO_TEST_LIBS) -lboost_unit_test_framework -lcurl $(GOOGLE_TEST_LIB)

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
	-rm -rf $(filter-out obj/, $(wildcard obj/*))
