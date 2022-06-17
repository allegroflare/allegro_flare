#include <allegro5/allegro.h>
#include <AllegroFlare/Color.hpp>
#include <AllegroFlare/Screen.hpp>
#include <AllegroFlare/Useful.hpp> // for distance()
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Screen.hpp>
#include <AllegroFlare/Frameworks/Full.hpp>
#include <AllegroFlare/EventEmitter.hpp>

#include <allegro5/allegro_primitives.h>



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
      , speed(5.0)
   {}

   void move_up()
   {
      velocity_x = 0;
      velocity_y = -speed;
   }

   void move_down()
   {
      velocity_x = 0;
      velocity_y = speed;
   }

   void move_left()
   {
      velocity_x = -speed;
      velocity_y = 0;
   }

   void move_right()
   {
      velocity_x = speed;
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
   AllegroFlare::EventEmitter &event_emitter;
   float width, height; 
   std::vector<std::pair<bool, Fruit>> fruits;
   Snake snake;
   int player_score;

public:
   Gameboard(int width, int height, AllegroFlare::EventEmitter &event_emitter)
      : event_emitter(event_emitter)
      , width(width)
      , height(height)
      , fruits()
      , snake(0, 0)
      , player_score(0)
   {}

   void create_fruit()
   {
      float new_fruit_x = AllegroFlare::random_float(0, width);
      float new_fruit_y = AllegroFlare::random_float(0, height);
      std::vector<Fruit::fruit_t> possible_fruits = { Fruit::APPLE, Fruit::GRAPE, Fruit::CHERRY, Fruit::ORANGE, Fruit::PEAR, Fruit::PINEAPPLE, };
      Fruit::fruit_t new_fruit_type = AllegroFlare::random_element<Fruit::fruit_t>(possible_fruits);

      fruits.push_back(std::pair<bool, Fruit>(true, { new_fruit_x, new_fruit_y, new_fruit_type }));
   }

   void draw()
   {
      ALLEGRO_COLOR gameboard_border_color = al_color_name("red");
      al_draw_rectangle(0, 0, width, height, gameboard_border_color, 3.0);

      for (auto &fruit : fruits) fruit.second.draw();

      snake.draw();
   }

   int get_player_score()
   {
      return player_score;
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

   void update_positions_and_check_collisions()
   {
      snake.x += snake.velocity_x;
      snake.y += snake.velocity_y;

      float min_distance_for_collision = 20;

      for (auto &fruit : fruits)
      {
         if (AllegroFlare::distance(snake.x, snake.y, fruit.second.x, fruit.second.y) <= min_distance_for_collision)
         {
            fruit.first = false;
            player_score += 1;
            event_emitter.emit_play_sound_effect_event("pickup_fruit");
         }
      }
   }

   void remove_dead_elements()
   {
      for (unsigned i=0; i<fruits.size(); i++)
      {
         bool fruit_marked_for_deletion = fruits[i].first;
         if (fruit_marked_for_deletion == false)
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



class HUD
{
public:
   int player_score;
   AllegroFlare::FontBin fonts;

   HUD()
      : player_score(0)
      , fonts()
   {}

   void initialize()
   {
      fonts.set_path("../data/fonts");
   }

   void set_player_score(int new_score)
   {
      player_score = new_score;
   }

   void draw()
   {
      ALLEGRO_FONT *font = fonts["DroidSans.ttf 26"];
      ALLEGRO_COLOR color = al_color_name("white");

      std::stringstream player_score_text;
      player_score_text << player_score;

      al_draw_text(font, color, 20, 10, 0, player_score_text.str().c_str());
   }
};



class SnakeGame : public AllegroFlare::Screen
{
public:
   AllegroFlare::Frameworks::Full &framework;
   Gameboard gameboard;
   HUD hud;

   SnakeGame(AllegroFlare::Frameworks::Full &framework)
      : AllegroFlare::Screen()
      , framework(framework)
      , gameboard(1920, 1080, framework.get_event_emitter_ref())
      , hud()
   {}

   void initialize()
   {
      hud.initialize();
      framework.load_jukebox_sound_effects({
            { "pickup_fruit", { "pickup_health-01.ogg", false } }
         });
      gameboard.spawn_random_fruit();
   }

   void refresh_player_score_on_hud()
   {
      hud.set_player_score(gameboard.get_player_score());
   }

   void primary_timer_func() override
   {
      // update
      gameboard.update_positions_and_check_collisions();
      gameboard.remove_dead_elements();
      refresh_player_score_on_hud();

      // draw
      al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 0});
      gameboard.draw();
      hud.draw();
   }

   void key_down_func(ALLEGRO_EVENT *ev) override
   {
      switch(ev->keyboard.keycode)
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
   AllegroFlare::Frameworks::Full framework;
   framework.initialize_with_display();

   SnakeGame snake(framework);
   snake.initialize();

   framework.register_screen(&snake);

   framework.run_loop();
}



