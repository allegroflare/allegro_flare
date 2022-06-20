
#include <AllegroFlare/Frameworks/Full.hpp>
#include <AllegroFlare/Screens/Basic.hpp>

#include <AllegroFlare/Inventory.hpp>
#include <AllegroFlare/Achievements.hpp>


#include <iostream>



enum item_t
{
   ITEM_NONE = 0,
   ITEM_BARLEY,
};



class CollectedTenBarleyAchievement : public AllegroFlare::Achievement
{
private:
   AllegroFlare::Inventory &player_inventory;

public:
   CollectedTenBarleyAchievement(AllegroFlare::Inventory &player_inventory)
      : player_inventory(player_inventory)
   {}

   bool test_condition() override
   {
      return player_inventory.get_item_count(ITEM_BARLEY) >= 10;
   }

   void on_achieved() override
   {
      std::cout << "Congratulations! You've got 10 bundles of barley! Epic!" << std::endl;
      std::cout << std::flush;
   }
};



class ExampleProgram : public AllegroFlare::Screens::Basic
{
public:
   AllegroFlare::Inventory player_inventory;
   AllegroFlare::Achievements achievements;
   bool initialized;

   ExampleProgram()
      : AllegroFlare::Screens::Basic()
      , player_inventory()
      , achievements()
      , initialized(false)
   {}

   void initialize()
   {
      if (initialized) return;
      CollectedTenBarleyAchievement *collected_ten_barley_achievement = new CollectedTenBarleyAchievement(player_inventory);
      achievements.add("Collected 10 Barley", collected_ten_barley_achievement);
      initialized = true;
   }

   void key_down_func(ALLEGRO_EVENT *ev) override
   {
      // add the item to the inventory
      player_inventory.add_item(ITEM_BARLEY);
      std::cout << "1 Barley added." << std::endl;   // <-- *** NEW
      std::cout << std::flush;
   }

   void primary_timer_func() override
   {
      // check for any new achievements
      achievements.check_all();
   }
};



int main(int argc, char **argv)
{
   AllegroFlare::Frameworks::Full full_framework;
   full_framework.initialize();

   // create the screen where our example program exists
   ExampleProgram example_program;
   example_program.initialize();

   // register the screen to the system
   full_framework.register_screen("main", &example_program);

   // run the loop
   full_framework.run_loop();
}



