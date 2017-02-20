



#include "file_downloader.h"

#include <curl/curl.h>
#include <iostream>
#include <fstream>



FileDownloader::FileHandle::FileHandle(std::string file_url, std::string local_filename)
   : id(last_id++)
   , status(NONE)
   , download_size(0.0)
   , percentage(0.0)
   , file_url(file_url)
   , local_filename(local_filename)
   , error("")
{
}




FileDownloader::FileHandle::~FileHandle()
{
}




float FileDownloader::FileHandle::get_download_size()
{
   return download_size;
}




float FileDownloader::FileHandle::get_percentage()
{
   return percentage;
}




bool FileDownloader::FileHandle::abort_download()
{
   if (abort) return false;
   abort = true;
   return true;
}




bool FileDownloader::FileHandle::is_done()
{
   return status == DOWNLOADED || status == ERROR;
}




FileDownloader::download_status_t FileDownloader::FileHandle::get_status()
{
   return status;
}




std::string FileDownloader::FileHandle::get_file_url()
{
   return file_url;
}




std::string FileDownloader::FileHandle::get_local_filename()
{
   return local_filename;
}




bool FileDownloader::FileHandle::erase_downloaded_file()
{
   return false;
}




std::string FileDownloader::FileHandle::get_error()
{
   return error;
}




int FileDownloader::num_downloading_files()
{
   return -1;
}




bool FileDownloader::clear_all_downloaded_files()
{
   return false;
}




bool FileDownloader::clear_history()
{
   return false;
}




FileDownloader::FileHandle FileDownloader::download_file(std::string file_url, std::string local_filename)
{
   FileHandle file_handle(file_url, local_filename);
   std::string temp_filename = std::string(local_filename).insert(0, "~");
   CURL *curl = nullptr;
   FILE *file_pointer = nullptr;
   CURLcode res;
   curl = curl_easy_init();

   if (!curl)
   {
      file_handle.status = ERROR;
      file_handle.error = "CURL initialization error";
      return file_handle;
   }

   file_pointer = fopen(temp_filename.c_str(), "wb");
   curl_easy_setopt(curl, CURLOPT_URL, file_url.c_str());
   curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, FileDownloader::write_data);
   curl_easy_setopt(curl, CURLOPT_WRITEDATA, file_pointer);
   curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0);
   curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, progress_function);
   curl_easy_setopt(curl, CURLOPT_PROGRESSDATA, &file_handle);

   res = curl_easy_perform(curl);

   if (res == CURLE_OK)
   {
      long http_response_code = 0;
      curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_response_code);

      switch (http_response_code)
      {
      case 200:
         {
            // copy the temp file to the destination
            std::ifstream src(temp_filename, std::ios::binary);
            std::ofstream dst(local_filename, std::ios::binary);
            dst << src.rdbuf();

            file_handle.status = DOWNLOADED;
            file_handle.percentage = 1.0;
         }
         break;
      case 404:
      default:
         file_handle.status = ERROR;
         file_handle.error = std::to_string(http_response_code);
         break;
      }
   }
   else
   {
      file_handle.status = ERROR;
      file_handle.error = curl_easy_strerror(res);
   }

   // erase the temp file
   remove(temp_filename.c_str());

   // cleanup the curl session
   curl_easy_cleanup(curl);
   fclose(file_pointer);

   return file_handle;
}




size_t FileDownloader::write_data(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
   size_t written = fwrite(ptr, size, nmemb, stream);
   return written;
}




int FileDownloader::progress_function(void *ptr, double download_total, double download_now, double upload_total, double upload_now)
{
   FileDownloader::FileHandle &handle = *static_cast<FileDownloader::FileHandle *>(ptr);
   if (download_total == 0) return 0;
   if (handle.abort) return 1;

   handle.status = DOWNLOADING;
   handle.percentage = download_now / download_total;
   handle.download_size = download_total;

   return 0;
}




int FileDownloader::FileHandle::last_id = -1;




