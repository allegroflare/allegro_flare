
## Simple Guide to Build Allegro on Linux:


# update everything

sudo apt-get update

# get the dependencies (everything)

sudo apt-get install build-essential git cmake cmake-curses-gui xorg-dev libgl1-mesa-dev libglu-dev

sudo apt-get install libpng-dev libcurl4-openssl-dev libfreetype6-dev libjpeg-dev libvorbis-dev libopenal-dev libphysfs-dev libgtk2.0-dev libasound-dev libpulse-dev libflac-dev libdumb1-dev

sudo apt-get install exuberant-ctags dvi2ps dvipdfmx latex2html pandoc

# clone the most recent allegro repo

git clone git://git.code.sf.net/p/alleg/allegro

# build allegro

cd allegro

mkdir build; cd build

cmake ..

make

# normally "make install" but "sudo make install" will allow it to install to /usr folder

sudo make install