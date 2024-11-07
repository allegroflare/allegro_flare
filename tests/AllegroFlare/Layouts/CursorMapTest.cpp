
#include <gtest/gtest.h>

//#include <Layouts/CursorMaps/CursorMap.hpp>
#include <AllegroFlare/Layouts/CursorMap.hpp>
#include <AllegroFlare/Testing/WithInteractionFixture.hpp>
#include <AllegroFlare/Elements/SelectionCursorBox.hpp>


class AllegroFlare_Layouts_CursorMapTest : public ::testing::Test {};
class AllegroFlare_Layouts_CursorMapTestWithInteraction : public AllegroFlare::Testing::WithInteractionFixture
{
public:
AllegroFlare::Layouts::Elements::CursorDestination *current_cursor_destination;
   AllegroFlare::Elements::SelectionCursorBox selection_cursor_box;

   AllegroFlare_Layouts_CursorMapTestWithInteraction()
      : current_cursor_destination(nullptr)
   {}

   void move_cursor_to(AllegroFlare::Layouts::CursorMap &cursor_map, int target_tmj_object_id)
   {
      AllegroFlare::Layouts::Elements::CursorDestination *next_destination =
         cursor_map.find_position_by_tmj_object_id(target_tmj_object_id);
      if (target_tmj_object_id == 0)
      {
         // Nothing
         // TODO: Consider >boop< sound or unmoving cursor animation
      }
      else
      {
         if (current_cursor_destination && current_cursor_destination->on_blur)
         {
            current_cursor_destination->on_blur();
         }

         current_cursor_destination = next_destination;

         if (current_cursor_destination && current_cursor_destination->on_focus)
         {
            current_cursor_destination->on_focus();
         }

         set_selection_cursor_box_to_new_position();
      }
   }

   void move_cursor_up(AllegroFlare::Layouts::CursorMap &cursor_map)
   {
      int next_id = current_cursor_destination->move_up_to_target_tmj_object_id;
      move_cursor_to(cursor_map, next_id);
   }

   void move_cursor_down(AllegroFlare::Layouts::CursorMap &cursor_map)
   {
      int next_id = current_cursor_destination->move_down_to_target_tmj_object_id;
      move_cursor_to(cursor_map, next_id);
   }

   void move_cursor_left(AllegroFlare::Layouts::CursorMap &cursor_map)
   {
      int next_id = current_cursor_destination->move_left_to_target_tmj_object_id;
      move_cursor_to(cursor_map, next_id);
   }

   void move_cursor_right(AllegroFlare::Layouts::CursorMap &cursor_map)
   {
      int next_id = current_cursor_destination->move_right_to_target_tmj_object_id;
      move_cursor_to(cursor_map, next_id);
   }

   void activate_current_cursor_selection()
   {
      // TODO: Assert current_cursor_destination
      if (current_cursor_destination->on_activation) current_cursor_destination->on_activation();

      // TODO: Possibly some custom behavior would be here if it fit the design
   }

   void set_selection_cursor_box_to_new_position()
   {
      selection_cursor_box.reposition_to(
         current_cursor_destination->x,
         current_cursor_destination->y
      );
      selection_cursor_box.resize_to(
         current_cursor_destination->width,
         current_cursor_destination->height
      );
   }
};


TEST_F(AllegroFlare_Layouts_CursorMapTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Layouts::CursorMap cursor_map;
}


TEST_F(AllegroFlare_Layouts_CursorMapTestWithInteraction, CAPTURE__INTERACTIVE__will_work_as_expected)
{
   AllegroFlare::Placement2D placement;
   AllegroFlare::Layouts::CursorMap cursor_map;
   //cursor_map.set_tmj_filename(get_data_path() + "maps/" + "layout_with_cursor_destinations-01.tmj");
   cursor_map.set_tmj_filename(get_data_path() + "maps/" + "layout_with_many_features-02.tmj");
   //cursor_map.set_tmj_filename(get_data_path() + "maps/" + "inventory-01.tmj");
   cursor_map.initialize();

   placement.size.x = cursor_map.get_layout_width();
   placement.size.y = cursor_map.get_layout_height();
   placement.position.x = 1920/2;
   placement.position.y = 1080/2;
   placement.scale.x = 2.0;
   placement.scale.y = 2.0;

   current_cursor_destination = cursor_map.get_initial_cursor_destination();
   set_selection_cursor_box_to_new_position();

   while(interactive_test_wait_for_event())
   {
      ALLEGRO_EVENT &current_event = *interactive_test_get_current_event();

      switch(current_event.type)
      {
         case ALLEGRO_EVENT_TIMER: {
            // Update
            selection_cursor_box.update();

            // Render
            clear();

            placement.start_transform();
            cursor_map.render_debug(1.0);
            selection_cursor_box.render();
            placement.restore_transform();

            interactive_test_render_status();
            al_flip_display();
         } break;

         case ALLEGRO_EVENT_KEY_CHAR:
         {
            //bool shift = current_event.keyboard.modifiers & ALLEGRO_KEYMOD_SHIFT;
            switch(current_event.keyboard.keycode)
            {
               case ALLEGRO_KEY_UP:
                  move_cursor_up(cursor_map);
               break;

               case ALLEGRO_KEY_DOWN:
                  move_cursor_down(cursor_map);
               break;

               case ALLEGRO_KEY_LEFT:
                  move_cursor_left(cursor_map);
               break;

               case ALLEGRO_KEY_RIGHT:
                  move_cursor_right(cursor_map);
               break;

               case ALLEGRO_KEY_ENTER:
                  activate_current_cursor_selection();
               break;
            }
         }
         break;
      }
   }
}


TEST_F(AllegroFlare_Layouts_CursorMapTestWithInteraction, CAPTURE__INTERACTIVE__will_work_as_expected__2)
{
   AllegroFlare::Placement2D placement;
   AllegroFlare::Layouts::CursorMap cursor_map;
   //cursor_map.set_tmj_filename(get_data_path() + "maps/" + "layout_with_cursor_destinations-01.tmj");
   cursor_map.set_tmj_filename(get_data_path() + "layouts/" + "inventory-01.tmj");
   cursor_map.initialize();

   placement.size.x = cursor_map.get_layout_width();
   placement.size.y = cursor_map.get_layout_height();
   placement.position.x = 1920/2;
   placement.position.y = 1080/2;
   //placement.scale.x = 2.0;
   //placement.scale.y = 2.0;
   placement.scale.x = 1.0;
   placement.scale.y = 1.0;

   current_cursor_destination = cursor_map.get_initial_cursor_destination();
   set_selection_cursor_box_to_new_position();

   while(interactive_test_wait_for_event())
   {
      ALLEGRO_EVENT &current_event = *interactive_test_get_current_event();

      switch(current_event.type)
      {
         case ALLEGRO_EVENT_TIMER: {
            // Update
            selection_cursor_box.update();

            // Render
            clear();

            placement.start_transform();
            cursor_map.render_debug(1.0);
            selection_cursor_box.render();
            placement.restore_transform();

            interactive_test_render_status();
            al_flip_display();
         } break;

         case ALLEGRO_EVENT_KEY_CHAR:
         {
            //bool shift = current_event.keyboard.modifiers & ALLEGRO_KEYMOD_SHIFT;
            switch(current_event.keyboard.keycode)
            {
               case ALLEGRO_KEY_UP:
                  move_cursor_up(cursor_map);
               break;

               case ALLEGRO_KEY_DOWN:
                  move_cursor_down(cursor_map);
               break;

               case ALLEGRO_KEY_LEFT:
                  move_cursor_left(cursor_map);
               break;

               case ALLEGRO_KEY_RIGHT:
                  move_cursor_right(cursor_map);
               break;

               case ALLEGRO_KEY_ENTER:
                  activate_current_cursor_selection();
               break;
            }
         }
         break;
      }
   }
}


