#include <AllegroFlare/TileMaps/AutoTile/Filters/MonolineBlobsHorizontal.hpp>
#include <AllegroFlare/TileMaps/Basic2D.hpp>

#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/DeploymentEnvironment.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Placement2D.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <gtest/gtest.h>
#include <string>
#include <vector>


//#include <AllegroFlare/TerminalColors.hpp>
//#include <AllegroFlare/Testing/TestNameInference.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <chrono>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <thread>



ALLEGRO_DISPLAY* display = nullptr;
AllegroFlare::FontBin font_bin;
AllegroFlare::BitmapBin bitmap_bin;
int display_samples = 0;
AllegroFlare::DeploymentEnvironment deployment_environment;
std::vector<std::string> test_prefix_tokens;



#include <iostream>
#include <fstream>
#include <vector>
#include <string>

std::vector<std::vector<int>> load_input_matrix_from_file(const std::string& filename)
{
    std::vector<std::vector<int>> numbers;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return numbers;
    }

    std::string line;
    std::vector<int> currentLine;

    // Read each line in the file
    while (std::getline(file, line)) {
        if (!currentLine.empty() && line.length() != currentLine.size()) {
            std::cerr << "Invalid line length: " << line << std::endl;
            numbers.clear();
            return numbers;
        }

        currentLine.clear();

        // Process each character in the line
        for (char c : line) {
            if (c == '0')
                currentLine.push_back(0);
            else if (c == '1')
                currentLine.push_back(1);
            else {
                std::cerr << "Invalid character: " << c << std::endl;
                numbers.clear();
                return numbers;
            }
        }

        numbers.push_back(currentLine);
    }

    file.close();
    return numbers;
}



void setup()
{
   al_is_system_installed();
   al_init();
   al_init_primitives_addon();
   al_init_font_addon();
   al_init_ttf_addon();
   al_init_image_addon();

   deployment_environment.set_environment(AllegroFlare::DeploymentEnvironment::ENVIRONMENT_PRODUCTION);

   font_bin.set_path("bin/data/fonts/");
   bitmap_bin.set_path("bin/data/bitmaps/");

   if (display_samples > 0) al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
   al_set_new_display_option(ALLEGRO_DEPTH_SIZE, 32, ALLEGRO_SUGGEST);
   if (display_samples > 0) al_set_new_display_option(ALLEGRO_SAMPLES, display_samples, ALLEGRO_SUGGEST);
   al_set_new_display_flags(ALLEGRO_OPENGL | ALLEGRO_PROGRAMMABLE_PIPELINE);
   display = al_create_display(1920, 1080);

   // clear the display to a slightly gray black color
   //al_clear_to_color(ALLEGRO_COLOR{0.05f, 0.05f, 0.055f, 1.0f});

   // set the window title to the current test name
   std::string new_window_title = "Monoline blob generator"; 

   al_set_window_title(display, new_window_title.c_str());
}



void shutdown()
{
   font_bin.clear();
   bitmap_bin.clear();
   al_destroy_display(display);
   al_shutdown_ttf_addon(); // this is required otherwise subsequent al_init_ttf_addon will not work
                            // this is a bug in Allegro
   al_uninstall_system();
}


AllegroFlare::Placement2D build_centered_placement(float width, float height)
{
   if (!(al_get_target_bitmap()))
   {
      std::stringstream error_message;
      error_message << "[WithAllegroRenderingFixture::build_centered_placement]: error: guard \"al_get_target_bitmap()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("WithAllegroRenderingFixture::build_centered_placement: error: guard \"al_get_target_bitmap()\" not met");
   }
   AllegroFlare::Placement2D place(al_get_display_width(display)/2, al_get_display_height(display)/2, width, height);
   return place;
}


int main(int argc, char **argv)
{
   std::vector<std::string> args;
   for (int i=1; i<argc; i++) args.push_back(argv[i]);


   setup();


   // load our source file (if present)
   std::vector<std::vector<int>> input_matrix = {
      { 0, 0, 0, 0, 0, 0 },
      { 0, 1, 0, 0, 0, 0 },
      { 0, 0, 1, 1, 1, 0 },
      { 0, 1, 1, 1, 0, 0 },
      { 0, 0, 0, 1, 1, 0 },
      { 0, 0, 1, 1, 1, 0 },
      { 0, 0, 0, 0, 0, 0 },
   };


   if (args.size() == 1)
   {
      // load a file if one is passed
      std::string filename_containing_input_matrix = args[0];
      input_matrix = load_input_matrix_from_file(filename_containing_input_matrix);
   }


   // Build our basic tile map

   AllegroFlare::TileMaps::Basic2D basic2d_tile_map(&bitmap_bin);
   basic2d_tile_map.set_atlas_configuration("monoline-grouped-art-tiles-02.png", 200, 200);
   basic2d_tile_map.initialize();
   basic2d_tile_map.resize(100, 32);


   // Create our filter and build our input matrix

   AllegroFlare::TileMaps::AutoTile::Filters::MonolineBlobsHorizontal filter;
   filter.set_input_matrix(
      AllegroFlare::TileMaps::AutoTile::FilterMatrix::build(input_matrix)
   );


   // Get our collision tile map from the basic tile map and fill it (skipping this step)

   //AllegroFlare::TileMaps::TileMap<int> &basic2d_tile_map_collision_tile_map =
      //basic2d_tile_map.get_collision_tile_map_ref();


   // Apply the filter to the input matrix

   EXPECT_EQ(true, filter.process());


   // Assign the values of our result matrix into the tile map

   AllegroFlare::TileMaps::AutoTile::FilterMatrix &result_matrix = filter.get_result_matrix_ref();
   AllegroFlare::TileMaps::PrimMesh &prim_mesh = basic2d_tile_map.get_prim_mesh_ref();
   for (int y=0; y<result_matrix.get_height(); y++)
      for (int x=0; x<result_matrix.get_width(); x++)
      {
         int result_tile_value = result_matrix.get_tile(x, y);
         prim_mesh.set_tile_id(x, y, result_tile_value);
      }


   // Tweak the appearance of the tilemap for clearer presentation

   basic2d_tile_map.rescale_tile_dimensions_to(200, 200);
   AllegroFlare::Placement2D place;
   //AllegroFlare::Placement2D place = build_centered_placement(
      //basic2d_tile_map.infer_real_width(),
      //basic2d_tile_map.infer_real_height()
   //);
   //place.position = {1920/2, 1080/2};
   place.scale = AllegroFlare::Vec2D{0.2, 0.2};


   // Render our result

   al_clear_to_color(ALLEGRO_COLOR{0.05f, 0.05f, 0.055f, 1.0f});

   place.start_transform();
   basic2d_tile_map.render();
   place.restore_transform();

   al_flip_display();
   al_rest(2);

   shutdown();

   return 0;
}
