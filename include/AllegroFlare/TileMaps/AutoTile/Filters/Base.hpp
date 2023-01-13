#pragma once


#include <AllegroFlare/TileMaps/AutoTile/FilterMatrix.hpp>
#include <string>


namespace AllegroFlare
{
   namespace TileMaps
   {
      namespace AutoTile
      {
         namespace Filters
         {
            class Base
            {
            public:
               static constexpr char* TYPE = (char*)"Filters/Base";

            private:
               std::string type;
               AllegroFlare::TileMaps::AutoTile::FilterMatrix input_matrix;
               AllegroFlare::TileMaps::AutoTile::FilterMatrix result_matrix;

            protected:


            public:
               Base(std::string type=AllegroFlare::TileMaps::AutoTile::Filters::Base::TYPE, AllegroFlare::TileMaps::AutoTile::FilterMatrix input_matrix={});
               virtual ~Base();

               void set_input_matrix(AllegroFlare::TileMaps::AutoTile::FilterMatrix input_matrix);
               std::string get_type() const;
               AllegroFlare::TileMaps::AutoTile::FilterMatrix get_input_matrix() const;
               AllegroFlare::TileMaps::AutoTile::FilterMatrix get_result_matrix() const;
               AllegroFlare::TileMaps::AutoTile::FilterMatrix &get_input_matrix_ref();
               AllegroFlare::TileMaps::AutoTile::FilterMatrix &get_result_matrix_ref();
               virtual bool process();
            };
         }
      }
   }
}



