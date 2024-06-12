
#include <gtest/gtest.h>

#include <Tileo/TileoTileVertexAllegroVertexDeclaration.hpp>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Logger.hpp>

static bool operator==(const ALLEGRO_COLOR& color1, const ALLEGRO_COLOR& color2)
{
   return (color1.r == color2.r)
      && (color1.g == color2.g)
      && (color1.b == color2.b)
      && (color1.a == color2.a);
}

static bool operator!=(const ALLEGRO_COLOR& color1, const ALLEGRO_COLOR& color2)
{
   return (color1.r != color2.r)
      || (color1.g != color2.g)
      || (color1.b != color2.b)
      || (color1.a != color2.a);
}

bool operator==(const TILEO_TILE_VERTEX &v1, const TILEO_TILE_VERTEX &v2)
{
  if (v1.x != v2.x) return false;
  if (v1.y != v2.y) return false;
  if (v1.z != v2.z) return false;
  if (v1.texture_u != v2.texture_v) return false;
  if (v1.normal_u != v2.normal_v) return false;
  if (v1.height_u != v2.height_v) return false;
  if (v1.height != v2.height) return false;
  if (v1.color != v2.color) return false;
  return true;
}


TEST(Tileo_TileoTileVertexAllegroVertexDeclarationTest, can_be_created_without_blowing_up)
{
   Tileo::TileoTileVertexAllegroVertexDeclaration declaration;
}


TEST(Tileo_TileoTileVertexAllegroVertexDeclarationTest, initialize__without_allegro_initialized__will_throw_an_error)
{
   Tileo::TileoTileVertexAllegroVertexDeclaration declaration;
   std::string expected_error_message = AllegroFlare::Logger::build_guard_error_message(
      "Tileo::TileoTileVertexAllegroVertexDeclaration::initialize",
      "al_is_system_installed()"
   );

   EXPECT_THROW_WITH_MESSAGE(declaration.initialize(), std::runtime_error, expected_error_message);
}


TEST(Tileo_TileoTileVertexAllegroVertexDeclarationTest,
   initialize__without_primitives_addon_initialized__will_throw_an_error)
{
   al_init();
   Tileo::TileoTileVertexAllegroVertexDeclaration declaration;
   std::string expected_error_message = AllegroFlare::Logger::build_guard_error_message(
      "Tileo::TileoTileVertexAllegroVertexDeclaration::initialize",
      "al_is_primitives_addon_initialized()"
   );

   EXPECT_THROW_WITH_MESSAGE(declaration.initialize(), std::runtime_error, expected_error_message);

   al_uninstall_system();
}


TEST(Tileo_TileoTileVertexAllegroVertexDeclarationTest, initialize__without_a_display__throws_an_error)
{
   al_init();
   al_init_primitives_addon();
   Tileo::TileoTileVertexAllegroVertexDeclaration declaration;
   std::string expected_error_message = AllegroFlare::Logger::build_guard_error_message(
      "Tileo::TileoTileVertexAllegroVertexDeclaration::initialize",
      "al_get_current_display()"
   );

   EXPECT_THROW_WITH_MESSAGE(declaration.initialize(), std::runtime_error, expected_error_message);

   al_shutdown_primitives_addon();
   al_uninstall_system();
}


TEST(Tileo_TileoTileVertexAllegroVertexDeclarationTest,
   initialize__with_a_display_that_was_created_without_the_ALLEGRO_PRORGRAMMABLE_PIPELINE_flag__throws_an_error)
{
   al_init();
   al_init_primitives_addon();
   ALLEGRO_DISPLAY *d = al_create_display(800, 600);

   Tileo::TileoTileVertexAllegroVertexDeclaration declaration;
   std::string expected_error_message = AllegroFlare::Logger::build_guard_error_message(
      "Tileo::TileoTileVertexAllegroVertexDeclaration::initialize",
      "(al_get_display_flags(al_get_current_display()) & ALLEGRO_PROGRAMMABLE_PIPELINE)"
   );

   EXPECT_THROW_WITH_MESSAGE(declaration.initialize(), std::runtime_error, expected_error_message);

   al_shutdown_primitives_addon();
   al_uninstall_system();
}


TEST(Tileo_TileoTileVertexAllegroVertexDeclarationTest, initialize__works_without_blowing_up)
{
   al_init();
   al_init_primitives_addon();
   al_set_new_display_flags(ALLEGRO_PROGRAMMABLE_PIPELINE);
   ALLEGRO_DISPLAY *d = al_create_display(800, 600);

   Tileo::TileoTileVertexAllegroVertexDeclaration declaration;

   declaration.initialize();

   declaration.destroy();
   al_shutdown_primitives_addon();
   al_uninstall_system();
}


TEST(Tileo_TileoTileVertexAllegroVertexDeclarationTest, initialize__if_called_more_than_once__will_throw_an_error)
{
   al_init();
   al_init_primitives_addon();
   al_set_new_display_flags(ALLEGRO_PROGRAMMABLE_PIPELINE);
   ALLEGRO_DISPLAY *d = al_create_display(800, 600);
   Tileo::TileoTileVertexAllegroVertexDeclaration declaration;
   declaration.initialize();
   std::string expected_error_message = AllegroFlare::Logger::build_guard_error_message(
      "Tileo::TileoTileVertexAllegroVertexDeclaration::initialize",
      "(!initialized)"
   );

   EXPECT_THROW_WITH_MESSAGE(declaration.initialize(), std::runtime_error, expected_error_message);

   declaration.destroy();
   al_shutdown_primitives_addon();
   al_uninstall_system();
}


TEST(Tileo_TileoTileVertexAllegroVertexDeclarationTest, destroy__if_called_more_than_once__will_throw_an_error)
{
   al_init();
   al_init_primitives_addon();
   al_set_new_display_flags(ALLEGRO_PROGRAMMABLE_PIPELINE);
   ALLEGRO_DISPLAY *d = al_create_display(800, 600);
   Tileo::TileoTileVertexAllegroVertexDeclaration declaration;
   declaration.initialize();
   declaration.destroy();

   std::string expected_error_message = AllegroFlare::Logger::build_guard_error_message(
      "Tileo::TileoTileVertexAllegroVertexDeclaration::destroy",
      "(!destroyed)"
   );
   EXPECT_THROW_WITH_MESSAGE(declaration.destroy(), std::runtime_error, expected_error_message);

   al_shutdown_primitives_addon();
   al_uninstall_system();
}


TEST(Tileo_TileoTileVertexAllegroVertexDeclarationTest,
   get_vertex_declaration__without_initialization__will_throw_an_error)
{
   Tileo::TileoTileVertexAllegroVertexDeclaration declaration;

   std::string expected_error_message = AllegroFlare::Logger::build_guard_error_message(
      "Tileo::TileoTileVertexAllegroVertexDeclaration::get_vertex_declaration",
      "initialized"
   );
   EXPECT_THROW_WITH_MESSAGE(declaration.get_vertex_declaration(), std::runtime_error, expected_error_message);
}


TEST(Tileo_TileoTileVertexAllegroVertexDeclarationTest,
   get_vertex_declaration__after_detroying__will_throw_an_error)
{
   al_init();
   al_init_primitives_addon();
   al_set_new_display_flags(ALLEGRO_PROGRAMMABLE_PIPELINE);
   ALLEGRO_DISPLAY *d = al_create_display(800, 600);
   Tileo::TileoTileVertexAllegroVertexDeclaration declaration;
   declaration.initialize();
   declaration.destroy();

   std::string expected_error_message = AllegroFlare::Logger::build_guard_error_message(
      "Tileo::TileoTileVertexAllegroVertexDeclaration::get_vertex_declaration",
      "(!destroyed)"
   );
   EXPECT_THROW_WITH_MESSAGE(declaration.get_vertex_declaration(), std::runtime_error, expected_error_message);

   al_shutdown_primitives_addon();
   al_uninstall_system();
}


TEST(Tileo_TileoTileVertexAllegroVertexDeclarationTest, get_vertex_declaration__returns_the_expected_vertex_declaration)
{
   al_init();
   al_init_primitives_addon();
   al_set_new_display_flags(ALLEGRO_PROGRAMMABLE_PIPELINE);
   ALLEGRO_DISPLAY *d = al_create_display(800, 600);
   Tileo::TileoTileVertexAllegroVertexDeclaration declaration;
   declaration.initialize();

   EXPECT_NE(nullptr, declaration.get_vertex_declaration());

   declaration.destroy();
   al_shutdown_primitives_addon();
   al_uninstall_system();
}


TEST(Tileo_TileoTileVertexAllegroVertexDeclarationTest,
   build_empty_vertex__returns_a_vertex_with_zeroed_values_and_white_color_value)
{
   Tileo::TileoTileVertexAllegroVertexDeclaration declaration;
   TILEO_TILE_VERTEX expected_vertex{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, {1, 1, 1, 1}};
   TILEO_TILE_VERTEX actual_vertex = declaration.build_empty_vertex();
   EXPECT_EQ(expected_vertex, actual_vertex);
}


