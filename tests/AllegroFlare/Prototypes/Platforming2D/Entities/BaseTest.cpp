
#include <gtest/gtest.h>

#include <AllegroFlare/Prototypes/Platforming2D/Entities/Base.hpp>


class EntitiesBaseTestClass : public AllegroFlare::Prototypes::Platforming2D::Entities::Base
{
public:
   EntitiesBaseTestClass()
      : AllegroFlare::Prototypes::Platforming2D::Entities::Base("EntitiesBaseTestClass")
   {}
};


TEST(AllegroFlare_Prototypes_Platforming2D_Entities_BaseTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Prototypes::Platforming2D::Entities::Base base;
}


TEST(AllegroFlare_Prototypes_Platforming2D_Entities_BaseTest, TYPE__has_the_expected_value)
{
   AllegroFlare::Prototypes::Platforming2D::Entities::Base base;
   EXPECT_EQ("AllegroFlare/Prototypes/Platforming2D/Entities/Base", base.get_type());
}


TEST(AllegroFlare_Prototypes_Platforming2D_Entities_BaseTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Prototypes::Platforming2D::Entities::Base base;
   EXPECT_EQ(AllegroFlare::Prototypes::Platforming2D::Entities::Base::TYPE, base.get_type());
}


TEST(AllegroFlare_Prototypes_Platforming2D_Entities_BaseTest, derived_classes_will_have_the_expected_type)
{
   EntitiesBaseTestClass test_class;
   EXPECT_EQ("EntitiesBaseTestClass", test_class.get_type());
}


TEST(AllegroFlare_Prototypes_Platforming2D_Entities_BaseTest, update__can_be_called_without_blowing_up)
{
   EntitiesBaseTestClass test_class;
   test_class.update();
   SUCCEED();
}


TEST(AllegroFlare_Prototypes_Platforming2D_Entities_BaseTest, draw__can_be_called_without_blowing_up)
{
   EntitiesBaseTestClass test_class;
   test_class.draw();
   SUCCEED();
}








/*
#pragma once


#include <allegro_flare/bitmap_object.h>
#include <allegro_flare/placement2d.h>
#include <AllegroFlare/ElementID.hpp>


namespace DragonWrath
{
   namespace Entities
   {
      class Base : public AllegroFlare::ElementID
      {
      private:
         float created_at;

      public:
         allegro_flare::placement2d place;
         allegro_flare::placement2d velocity;
         allegro_flare::BitmapObject bitmap;

         Base(AllegroFlare::ElementID *parent, std::string type, float x, float y);
         virtual ~Base();

         virtual void update();
         virtual void draw();

         float get_created_at();

         void flag_for_deletion();
         bool collides(const Base &other);
      };
   }
}







#include <DragonWrath/Entities/Base.hpp>
#include <allegro5/allegro_primitives.h>



namespace DragonWrath
{
namespace Entities
{



Base::Base(ElementID *parent, std::string type, float x, float y)
   : ElementID(parent)
   , place(x, y, 1, 1)
   , velocity()
   , bitmap(nullptr)
   , created_at(al_get_time())
{
   set("type", type);
   velocity.scale = AllegroFlare::vec2d(0, 0);
   velocity.align = AllegroFlare::vec2d(0, 0);
}



Base::~Base()
{}



void Base::update()
{}



void Base::flag_for_deletion()
{
   set("can_be_deleted");
}



void Base::draw()
{
   place.start_transform();
   //al_draw_filled_rectangle(0, 0, place.size.x, place.size.y, AllegroFlare::color::red);
   bitmap.position(place.size.x/2, place.size.y/2);
   bitmap.draw();
   place.restore_transform();
}


float Base::get_created_at()
{
   return created_at;
}


bool Base::collides(const Base &other)
{
   float h_width = place.size.x * 0.5;
   float h_height = place.size.y * 0.5;

   // this will not account for rotation or anything fancy.
   // it's an unofficial ballpark close enough for jazz doodad:

   return other.place.collide(place.x, place.y, h_height, h_width, h_height, h_width);
}



} // namespace Entities
} // namespace DragonWrath



*/


