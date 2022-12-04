#include <allegro5/allegro.h>
#include <AllegroFlare/MusicMesh/MusicMesh.hpp>

int main(int argc, char** argv)
{
   AllegroFlare::MusicMesh::MusicMesh music_mesh;
   music_mesh.render(); // should throw an error
   return 0;
}
