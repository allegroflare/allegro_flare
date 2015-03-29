#!/bin/bash


# DISCLAIMER!!
# This file is very dirty and requires drastic cleaning



#
# This is a helper file to help build allegro_flare.  This is a temporary
# solution, you may find that your own build system may work better for you.
#




PROJECT_BASE="~/Programs/allegro_flare/allegro_flare"
INCLUDE_DIR="$PROJECT_BASE/include"
SOURCE_DIR="$PROJECT_BASE/src"
LIB_DESTINATION_DIR="$PROJECT_BASE/lib"

ALLEGRO_INCLUDE_DIR="/home/mark/Libraries/allegro-5.1.8/include/"
ALLEGRO_LIB_DIR="~/Libraries/allegro-5.1.8/build/lib/"
# -I"$ALLEGRO_INCLUDE_DIR" -L"ALLEGRO_LIB_DIR"




#LINKY_LINK_LINK=-lallegro -lallegro_color -lallegro_primitives -lallegro_audio -lallegro_dialog -lallegro_image -lallegro_font -lallegro_ttf -lallegro_acodec





# list the files here that are to be compiled and linked into the library

files=( path2d appearance2d color collision_mesh )







echo ""
echo " === Compiling .o files... ==="

for i in "${files[@]}"
do
	echo $i
	g++ -c ./../src/"$i".cpp -I"./../include/" -I"/home/mark/Libraries/allegro-5.1.8/include/"
done

#g++ color.o -Wall -lallegro -lallegro_color -o color






echo ""
echo " === Assembling .a library file... ==="

# make a list of all the filenames with .o at the end

count=${#files[@]}
for ((i=0;i<count;i++)); do
    files_with_o[i]="${files[i]}.o"
done

ar rvs allegro_flare_build.a ${files_with_o[@]}






echo ""
echo " === Cleaning up... ==="

for i in "${files[@]}"
do
	echo "removing $i.o"
	rm "$i.o"
done



