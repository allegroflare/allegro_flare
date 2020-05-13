#include <AllegroFlare/Screen.hpp>
#include <AllegroFlare/Inventory.hpp>
#include <AllegroFlare/Achievement.hpp>
#include <AllegroFlare/Achievements.hpp>
#include <AllegroFlare/Framework.hpp>


#include <iostream>


using namespace AllegroFlare;


enum item_t
{
   ITEM_NONE = 0,
   ITEM_BARLEY,
};


class CollectedTenBarleyAchievement : public Achievement
{
private:
   Inventory &player_inventory;
   
public:
   CollectedTenBarleyAchievement(Inventory &player_inventory)
      : player_inventory(player_inventory)
   {}

   bool test_condition() override
   {
      return player_inventory.get_item_count(ITEM_BARLEY) >= 2;
   }

   void on_achieved() override
   {
      std::cout << "Congratulations! You've got 10 bundles of barley! Epic!" << std::endl;
   }
};


class MyGame : public Screen
{
public:
   Inventory player_inventory;
   Achievements achievements;
   enum items {
      ITEM_NONE = 0,
      ITEM_BARLEY,
   };

   MyGame(Framework &framework, Screens &screens, Display *display)
      : Screen(display)
   {}

   void initialize()
   {
      CollectedTenBarleyAchievement *achievement = new CollectedTenBarleyAchievement(player_inventory);
      achievements.add("my_collected_ten_barley_achievement", achievement);
   }
   
   void key_down_func(ALLEGRO_EVENT *ev) override
   {
      player_inventory.add_item(ITEM_BARLEY);
      std::cout << "1 Barley added." << std::endl;   // <-- *** NEW
   }

   void primary_timer_func() override
   {
      achievements.check_all();
   }
};


int main(int argc, char **argv)
{
   Screens screens;

   Framework framework(screens);
   framework.initialize();
   Display *display = framework.create_display(800, 600);

   MyGame my_game(framework, screens, display);
   
   framework.run_loop();
}
