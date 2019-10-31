#include <allegro5/allegro.h>
#include <AllegroFlare/Color.hpp>
#include <AllegroFlare/Screen.hpp>
#include <AllegroFlare/Useful.hpp> // for distance()

#include <allegro5/allegro_primitives.h>

using namespace AllegroFlare;


class Fruit
{
public:
   enum fruit_t
   {
      UNDEFINED = 0,
      APPLE,
      GRAPE,
      CHERRY,
      ORANGE,
      PEAR,
      PINEAPPLE,
   };

   float x, y;
   int type;

   Fruit(float x, float y, int type)
      : x(x)
      , y(y)
      , type(type)
   {}

   void draw()
   {
      ALLEGRO_COLOR color = al_color_name("gray");

      switch(type)
      {
      case UNDEFINED:
         color = al_color_name("gray");
         break;
      case APPLE:
         color = al_color_name("brown");
         break;
      case GRAPE:
         color = al_color_name("violet");
         break;
      case CHERRY:
         color = al_color_name("red");
         break;
      case ORANGE:
         color = al_color_name("orange");
         break;
      case PEAR:
         color = al_color_name("yellow");
         break;
      case PINEAPPLE:
         break;
      default:
         throw std::runtime_error("unhandled fruit type");
         break;
      }

      al_draw_filled_circle(x, y, 7, color);
   }
};


class Snake
{
public:
   float x, y, velocity_x, velocity_y;
   float speed;

   Snake(float x, float y)
      : x(x)
      , y(y)
      , velocity_x(0)
      , velocity_y(0)
      , speed(1.0)
   {}

   void move_up()
   {
      velocity_x = 0;
      velocity_y = -1;
   }

   void move_down()
   {
      velocity_x = 0;
      velocity_y = 1;
   }

   void move_left()
   {
      velocity_x = -1;
      velocity_y = 0;
   }

   void move_right()
   {
      velocity_x = 1;
      velocity_y = 0;
   }

   void draw()
   {
      float size = 10;
      float hsize = size/2;
      ALLEGRO_COLOR color = al_color_name("aliceblue");
      al_draw_filled_rectangle(x-hsize, y-hsize, x+hsize, y+hsize, color);
   }
};


class Gameboard
{
private:
   float width, height; 
   std::vector<std::pair<bool, Fruit>> fruits;
   Snake snake;
   int player_score;

public:
   Gameboard(Display *display)
      : width(700)
      , height(600)
      , fruits()
      , snake(0, 0)
      , player_score(0)
   {}

   void create_fruit()
   {
      float new_fruit_x = random_float(0, width);
      float new_fruit_y = random_float(0, height);
      Fruit::fruit_t new_fruit_type = Fruit::CHERRY;
      fruits.push_back(std::pair<bool, Fruit>(false, { new_fruit_x, new_fruit_y, new_fruit_type }));
   }

   void draw()
   {
      ALLEGRO_COLOR gameboard_border_color = al_color_name("red");
      al_draw_rectangle(0, 0, width, height, gameboard_border_color, 3.0);

      for (auto &fruit : fruits) fruit.second.draw();

      snake.draw();
   }

   void point_snake_up()
   {
      snake.move_up();
   }

   void point_snake_down()
   {
      snake.move_down();
   }

   void point_snake_left()
   {
      snake.move_left();
   }

   void point_snake_right()
   {
      snake.move_right();
   }

   void update_collisions()
   {
      snake.x += snake.velocity_x;
      snake.y += snake.velocity_y;

      float min_distance_for_collision = 10;

      for (auto &fruit : fruits)
      {
         if (manhattan_distance(snake.x, snake.y, fruit.second.x, fruit.second.y) <= min_distance_for_collision)
         {
            fruit.first = false;
         }
      }
   }

   void remove_dead_elements()
   {
      for (unsigned i=0; i<fruits.size(); i++)
      {
         bool fruit_marked_for_deletion = fruits[i].first;
         if (fruit_marked_for_deletion)
         {
            fruits.erase(fruits.begin() + i);
            i--;
         }
      }
   }

   void spawn_random_fruit()
   {
      unsigned num_fruit = 10;
      for (unsigned i=0; i<num_fruit; i++)
      {
         create_fruit();
      }
   }
};


class SnakeGame : public Screen
{
public:
   Gameboard gameboard;

   SnakeGame(Framework &framework, Screens &screens, Display *display)
      : Screen(framework, screens, display)
      , gameboard(display)
   {}

   void initialize()
   {
      gameboard.spawn_random_fruit();
   }

   void primary_timer_func() override
   {
      gameboard.update_collisions();
      gameboard.remove_dead_elements();
      gameboard.draw();
   }

   void key_down_func() override
   {
      switch(framework.current_event->keyboard.keycode)
      {
      case ALLEGRO_KEY_UP:
         gameboard.point_snake_up();
         break;
      case ALLEGRO_KEY_DOWN:
         gameboard.point_snake_down();
         break;
      case ALLEGRO_KEY_LEFT:
         gameboard.point_snake_left();
         break;
      case ALLEGRO_KEY_RIGHT:
         gameboard.point_snake_right();
         break;
      }
   }
};


int main(int argc, char **argv)
{
   Screens screens;
   Framework framework(screens);
   framework.initialize();
   Display *display = framework.create_display(800, 600);

   SnakeGame snake(framework, screens, display);
   snake.initialize();

   framework.run_loop();
}


