

#include <AllegroFlare/AssetStudio/Record.hpp>




namespace AllegroFlare
{
namespace AssetStudio
{


Record::Record()
   : id(0)
   , identifier("[unset-identifier]")
   , source_csv_column_num(0)
   , status("[unset-status]")
   , visibility("[unset-visibility]")
   , type("[unset-type]")
   , asset_pack_identifier("[unset-asset-pack-identifier]")
   , intra_pack_identifier("[unset-intra-pack-identifier]")
   , cell_width(0)
   , cell_height(0)
   , align_x(0.0f)
   , align_y(0.0f)
   , align_in_container_x(0.0f)
   , align_in_container_y(0.0f)
   , anchor_x(0.0f)
   , anchor_y(0.0f)
   , image_filename("[unset-image_filename]")
   , images_list({})
   , full_path_to_initial_image("[unset-full_path_to_initial_image]")
   , playmode("[unset-playmode]")
   , notes("[unset-notes]")
   , frame_data__build_n_frames__num_frames(0)
   , frame_data__build_n_frames__start_from_frame(0)
   , frame_data__build_n_frames__each_frame_duration(0)
   , frame_data__in_hash("[unset-frame_data__in_hash]")
{
}


Record::~Record()
{
}


bool Record::visibility_is_hidden()
{
   return (visibility == "hidden");
}


} // namespace AssetStudio
} // namespace AllegroFlare


