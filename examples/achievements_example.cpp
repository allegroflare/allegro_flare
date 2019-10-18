#include <allegro_flare/inventory.h>
#include <allegro_flare/achievement.h>
#include <allegro_flare/achievements.h>


class MyCollectedTenBarleyAchievement : public Achievement
{
private:
   Inventory &player_inventory;
   
public:
   MyCollectedTenBarleyAchievement(Inventory &player_inventory)
      : player_inventory(player_inventory)
   {}

   void test_condition() override
   {
      return player_inventory.get_item_count(ITEM_BARLEY) >= 10;
   }

   void on_achived() override
   {
      std::cout << "Congratulations! You've got 10 bundles of barley! Epic!" << std::endl;
   }
};


class MyGame : public Game
{
public:
   Inventory player_inventory;
   Achievements achievements;
   enum items {
      ITEM_NONE = 0,
      ITEM_BARLEY,
   };

   void initialize()
   {
      MyCollectedTenBarleyAchievement my_collected_ten_barley_achievement(player_inventory);
      achievments.add(my_collected_ten_barley_achievement);
   }
   
   void on_key_press() override
   {
      my_player_inventory.add_item(ITEM_BARLEY);
      std::cout << "1 Barley added." << std::endl;   // <-- *** NEW
   }

   void timer_loop() override
   {
      achievements.check_all();
   }
};


int main(int argc, char **argv)
{
   Framework framework;
   framework.initialize();
   
   MyGame my_game;
   framework.set_game(my_game);
   
   framework.run_loop();
}

