

#include <AllegroFlare/Testing/TemporaryFilenameCreator.hpp>

#include <AllegroFlare/Testing/TemporaryDirectoryCreator.hpp>
#include <cstdio>


namespace AllegroFlare
{
namespace Testing
{


TemporaryFilenameCreator::TemporaryFilenameCreator()
{
}


TemporaryFilenameCreator::~TemporaryFilenameCreator()
{
}


std::string TemporaryFilenameCreator::create_filename()
{
   return std::tmpnam(nullptr);
}

std::string TemporaryFilenameCreator::create_filename_within_guaranteed_unique_directory()
{
   AllegroFlare::Testing::TemporaryDirectoryCreator temporary_directory_creator;
   std::string unique_directory = temporary_directory_creator.create().string();
   std::string unique_filename = std::filesystem::path(std::tmpnam(nullptr)).filename().string();
   return unique_directory + "/" + unique_filename;
}


} // namespace Testing
} // namespace AllegroFlare


