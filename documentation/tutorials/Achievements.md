## Achievements

Achievements happen when your gamer has reached some goal, collected some number of items, or done anything that unlocks a feature or reward.  These achievements can vary based on a bunch of stuff in your game, but they all inherently follow the same shape:

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

When you create your own custom achievements for the gamer, you should inherit from this `Achievement` class and override the `test_condition()` and `on_achieved()` functions with your own custom logic. 

The `test_condition()` function is where you'll put the logic to check if the requirements of the achievement has been met.

The `on_achieved()` function is where the logic goes that will happen _after_ the achievement is actually met for the first time.  Maybe you want to notify the user that they reached an achievement, or maybe you want update the gamer's stats and level them up!

Also, when you write your custom achievement class, you should also create a custom constructor and **pass along whatever dependencies you need into your class's constructor**.  That way, you can use those dependencies in your logic for `test_condition()` or `on_achieved()`.  More on that next.

### Example

Let's say you want your gamer to get an achievement when they have accumulated 10 bundles of barley.  Let's say, too, that when they make that achievement we'll output a special "congratulations" message of some kind.  I'll assume we already know about the `Inventory` class, and we have an `ITEM_BARLEY`  defined in our `MyGame` (from the previous chapter (cough cough)).

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

This is awesome.  We've created our custom achievement.  Now, in order to actually get it to work, we're going to have to 1) install `Achievements` into our main game and then 2) add the `MyCollectedTenBarleyAchievement` to the list of achievements that our game is checking for.  Lucky for us, these are both really easy.

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

For the sake of brevity, we'll add an item to the user's inventory after the user presses a key.  Once the user has added 10 of these items, then the achievement should fire off.  Note that in reality, rather than using a keystroke, we'd probably add a piece of barley to their inventory after 1) the players bounding box collided with the bounding box of the barley item, 2) we safely destroy that item instance from the map, and 3) we spawned a fancy `VisualFX` for style points.  _Then_, we would add it.  But for now, let's keep things simple.

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
