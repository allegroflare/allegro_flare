



#include <allegro_flare/file_downloader.h>
#include <curl.h>




FileDownloader::FileHandle::FileHandle(std::string file_url, std::string local_filename)
{
}




FileDownloader::FileHandle::~FileHandle()
{
}




float FileDownloader::FileHandle::get_percentage()
{
}




download_status_t FileDownloader::FileHandle::get_status()
{
}




std::string FileDownloader::FileHandle::get_local_filename()
{
}




bool FileDownloader::FileHandle::erase_downloaded_file()
{
}




std::string FileDownloader::FileHandle::get_error()
{
}




int FileDownloader::num_downloading_files()
{
}




bool FileDownloader::clear_all_downloaded_files()
{
}




bool FileDownloader::clear_history()
{
}




FileDownloader::FileHandle FileDownloader::download_file(std::string file_url, std::string local_filename)
{
}




