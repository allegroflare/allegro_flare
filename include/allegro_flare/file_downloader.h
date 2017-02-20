#pragma once




#include <vector>
#include <string>




class FileDownloader
{
private:
   static size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream);
   static int progress_function(void *ptr,
         double download_total, double download_now,
         double upload_total, double upload_now
         );

public:
   enum download_status_t
   {
      NONE,
      DOWNLOADING,
      DOWNLOADED,
      ERROR
   };

   class FileHandle
   {
   friend class FileDownloader;

   private:
      static int last_id;
      int id;
      download_status_t status;
      float download_size;
      float percentage;
      bool abort;
      std::string file_url;
      std::string local_filename;
      std::string error;

   public:
      FileHandle(std::string file_url, std::string local_filename);
      ~FileHandle();

      float get_download_size();
      float get_percentage();
      bool abort_download();
      bool is_done();
      download_status_t get_status();
      std::string get_file_url();
      std::string get_local_filename();
      bool erase_downloaded_file();
      std::string get_error();
   };

   static std::vector<FileHandle> download_history;

   static int num_downloading_files();
   static bool clear_all_downloaded_files();
   static bool clear_history();
   static FileHandle download_file(std::string file_url, std::string local_filename);
};




/*
int main()
{
   std::string file_url = "https://www.allegro.cc/theme/default/image/logo.png";
   FileDownloader::FileHandle handle = FileDownloader::download_file(file_url);
}
*/




#endif
