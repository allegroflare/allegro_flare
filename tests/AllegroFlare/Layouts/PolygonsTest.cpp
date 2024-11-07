
#include <gtest/gtest.h>

//#include <Layouts/CursorMaps/CursorMap.hpp>
#include <AllegroFlare/Layouts/Polygons.hpp>
#include <AllegroFlare/Testing/WithInteractionFixture.hpp>
#include <AllegroFlare/Elements/SelectionCursorBox.hpp>


class AllegroFlare_Layouts_PolygonsTest : public ::testing::Test {};
class AllegroFlare_Layouts_PolygonsTestWithInteraction : public AllegroFlare::Testing::WithInteractionFixture
{
public:
   //AllegroFlare::Layouts::Elements::Frame *current_cursor_destination;
   //::Layouts::CursorMaps::CursorDestination *current_cursor_destination;
   //AllegroFlare::Elements::SelectionCursorBox selection_cursor_box;

   AllegroFlare_Layouts_PolygonsTestWithInteraction()
      //: current_cursor_destination(nullptr)
   {}
};


TEST_F(AllegroFlare_Layouts_PolygonsTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Layouts::Polygons polygons_layout;
}


TEST_F(AllegroFlare_Layouts_PolygonsTestWithInteraction, CAPTURE__INTERACTIVE__will_work_as_expected)
{
   AllegroFlare::Placement2D placement;
   AllegroFlare::Layouts::Polygons polygons_layout;
   //frames_layout.set_tmj_filename(get_data_path() + "maps/" + "layout_with_cursor_destinations-01.tmj");
   polygons_layout.set_tmj_filename(get_data_path() + "maps/" + "layout_with_many_features-02.tmj");
   //polygons_layout.set_tmj_filename(get_data_path() + "maps/" + "inventory-01.tmj");
   polygons_layout.initialize();

   placement.size.x = polygons_layout.get_layout_width();
   placement.size.y = polygons_layout.get_layout_height();
   placement.position.x = 1920/2;
   placement.position.y = 1080/2;
   placement.scale.x = 2.0;
   placement.scale.y = 2.0;

   //current_cursor_destination = polygons_layout.get_initial_cursor_destination();
   //set_selection_cursor_box_to_new_position();

   while(interactive_test_wait_for_event())
   {
      ALLEGRO_EVENT &current_event = *interactive_test_get_current_event();

      switch(current_event.type)
      {
         case ALLEGRO_EVENT_TIMER: {
            // Update
            //selection_cursor_box.update();

            // Render
            clear();

            placement.start_transform();
            polygons_layout.render_debug(1.0);
            //selection_cursor_box.render();
            placement.restore_transform();

            interactive_test_render_status();
            al_flip_display();
         } break;

         case ALLEGRO_EVENT_KEY_CHAR:
         {
            //bool shift = current_event.keyboard.modifiers & ALLEGRO_KEYMOD_SHIFT;
            switch(current_event.keyboard.keycode)
            {
               //case ALLEGRO_KEY_UP:
                  //move_cursor_up(polygons_layout);
               //break;

               //case ALLEGRO_KEY_DOWN:
                  //move_cursor_down(polygons_layout);
               //break;

               //case ALLEGRO_KEY_LEFT:
                  //move_cursor_left(polygons_layout);
               //break;

               //case ALLEGRO_KEY_RIGHT:
                  //move_cursor_right(polygons_layout);
               //break;

               //case ALLEGRO_KEY_ENTER:
                  //activate_current_cursor_selection();
               //break;
            }
         }
         break;
      }
   }
}


TEST_F(AllegroFlare_Layouts_PolygonsTestWithInteraction, CAPTURE__INTERACTIVE__will_work_as_expected__2)
{
   AllegroFlare::Placement2D placement;
   AllegroFlare::Layouts::Polygons polygons_layout;
   //polygons_layout.set_tmj_filename(get_data_path() + "maps/" + "layout_with_cursor_destinations-01.tmj");
   polygons_layout.set_tmj_filename(get_data_path() + "layouts/" + "inventory-01.tmj");
   polygons_layout.initialize();

   placement.size.x = polygons_layout.get_layout_width();
   placement.size.y = polygons_layout.get_layout_height();
   placement.position.x = 1920/2;
   placement.position.y = 1080/2;
   //placement.scale.x = 2.0;
   //placement.scale.y = 2.0;
   placement.scale.x = 1.0;
   placement.scale.y = 1.0;

   //current_cursor_destination = polygons_layout.get_initial_cursor_destination();
   //set_selection_cursor_box_to_new_position();

   while(interactive_test_wait_for_event())
   {
      ALLEGRO_EVENT &current_event = *interactive_test_get_current_event();

      switch(current_event.type)
      {
         case ALLEGRO_EVENT_TIMER: {
            // Update
            //selection_cursor_box.update();

            // Render
            clear();

            placement.start_transform();
            //polygons_layout.render_debug(1.0);
            polygons_layout.render();
            //selection_cursor_box.render();
            placement.restore_transform();

            interactive_test_render_status();
            al_flip_display();
         } break;

         case ALLEGRO_EVENT_KEY_CHAR:
         {
            //bool shift = current_event.keyboard.modifiers & ALLEGRO_KEYMOD_SHIFT;
            switch(current_event.keyboard.keycode)
            {
               //case ALLEGRO_KEY_UP:
                  //move_cursor_up(polygons_layout);
               //break;

               //case ALLEGRO_KEY_DOWN:
                  //move_cursor_down(polygons_layout);
               //break;

               //case ALLEGRO_KEY_LEFT:
                  //move_cursor_left(polygons_layout);
               //break;

               //case ALLEGRO_KEY_RIGHT:
                  //move_cursor_right(polygons_layout);
               //break;

               //case ALLEGRO_KEY_ENTER:
                  //activate_current_cursor_selection();
               //break;
            }
         }
         break;
      }
   }
}


