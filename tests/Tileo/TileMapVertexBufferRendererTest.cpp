
#include <gtest/gtest.h>

#include <Tileo/TileMapVertexBufferRenderer.hpp>


TEST(Tileo_TileMapVertexBufferRendererTest, can_be_created_without_blowing_up)
{
   AllegroFlare::TileMaps::PrimMeshAtlas atlas;
   TileMapVertexBufferRenderer renderer(atlas);
}


