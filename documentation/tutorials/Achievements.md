## Achievements

Achievements happen when your gamer has reached some goal, collected some number of items, or done anything that unlocks a feature or reward.  The kind of achievements you might have can vary depending on your game, but they all inherently follow the same shape:

```cpp

class Achievement
{
public:
   Achievement();
   
   void achieved();
   virtual bool test_condition();
   virtual void on_achieved();
}
```

When you create your own custom achievements, you should inherit from the [`AllegroFlare::Achievement`](https://github.com/allegroflare/allegro_flare/blob/master/include/AllegroFlare/Achievement.hpp) class and override the `test_condition()` and `on_achieved()` functions with your custom logic.

The `test_condition()` function is where you put your logic to check if the requirements of the achievement has been met.

The `on_achieved()` function is where you put the logic for what will happen after the achievement is actually met for the first time.  Maybe you want to notify the user that they reached the achievement, or maybe you want update the gamer's stats, or level them up and unlock new parts of the game!  Note that the achievement will have already been met and marked as completed before `on_achieved()` is called, so you don't need to modify the status of the achievement.

Each `Achivement` you create should be registed with an `AllegroFlare::Achievements` (plural), which is a container used to evaluate and maintain the list of all the achievements that have been met, and check that unmet achievements might have been completed.

Also, when you write your custom achievement class, you may want to create a custom constructor and pass along whatever dependencies you need into your class.  That way, you can use those dependencies in your logic for `test_condition()` or `on_achieved()`.

### Example

Let's say you want your player to get an achievement when they have accumulated 10 bundles of barley.  Let's say, too, that when they make that achievement, we'll output a special "congratulations" message of some kind.  I'm assuming you already know about the `Inventory` class.  Also, we'll need to have an `ITEM_BARLEY`  defined in our program.

```cpp
   enum items {
      ITEM_NONE = 0,
      ITEM_BARLEY,
   };
```

Here's what a `MyCollectedTenBarleyAchievement` would look like:

```cpp
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
```

We've created a class `MyCollectedTenBarleyAchievement`, and filled in the logic.

Notice that our `test_condition()` contains a call to get the count of `ITEM_BARLEY` currently in the inventory with `player_inventory.get_item_count(ITEM_BARLEY)`.   We then return if that value is greater or equal to 10 with the whole conditional `player_inventory.get_item_count(ITEM_BARLEY) >= 10`.

Also, we've filled in the `on_achieved()` function, which now contains `std::cout << "Congratulations! You've got 10 bundles of barley! Epic!" << std::endl;`, outputting a nice little message to the user's console.


### Adding Achievements to Your Game

We've created our custom achievement.  Now, in order to actually get it to work, we're going to have to 1) install `Achievements` into our main game and then 2) add the `MyCollectedTenBarleyAchievement` to the list of achievements that our game is checking for.  Lucky for us, these are both really easy.

### 1) Install `Achievements`

In our `MyGame` class, we would add the `Achievements` class into it and include the `check_all()` in our `game_loop()`:

```cpp
#include <allegro_flare/achievements.h>

class MyGame : public Game
{
public:
   Achievements achievements;      // <-- *** NEW

   void game_loop() override
   {
      achievements.check_all();    // <-- *** NEW
   }
};
```

```cpp
#include <allegro_flare/achievements.h>
#include <MyCollectedTenBarleyAchievement.hpp>


class MyGame : public Game
{
public:
   Inventory player_inventory;    // <-- *** NEW
   Achievements achievements;

   void initialize_game()
   {
      // NEW --> {
      MyCollectedTenBarleyAchievement my_collected_ten_barley_achievement(player_inventory);
      achievments.add(my_collected_ten_barley_achievement);
      // } NEW
   }

   void game_loop() override
   {
      achievements.check_all();
   }
};
```


### Awesome! Let's See Achievements It In Action

To keep things simple, we'll add an item to the user's inventory when they press a key.  Once the user has added 10 of these items, then the achievement should fire off.

In your game, let's add some logic to override the `on_key_press()` so we can catch that gamer's action and translate it into the acquisition of some sweet barley:

```cpp
class MyGame : public Game
{
public:
   void on_key_press() override
   {
      my_player_inventory.add_item(ITEM_BARLEY);    // <-- *** NEW
      std::cout << "1 Barley added" << std::endl;   // <-- *** NEW
   }
};
```

###  Full Example

```cpp
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
```

Now, let's run our program and watch it work!

```sh
$> make
```
```sh
$> bin/programs/my_game
```
Now... if I press any key 10 times...
```sh
1 Barley added.
1 Barley added.
1 Barley added.
1 Barley added.
1 Barley added.
1 Barley added.
1 Barley added.
1 Barley added.
1 Barley added.
1 Barley added.
Congratulations! You've got 10 bundles of barley! Epic!
```

## Moving Forward

Note that in reality, rather than using a keystroke, we'd probably add a piece of barley to their inventory after 1) the players bounding box collided with the bounding box of the barley item, 2) we safely destroy that item instance from the map, and 3) we spawned a fancy `VisualFX` for style points.  _Then_, we would add it.

You might also want to have all the achievements checked periodically rather
than on each timer click.
