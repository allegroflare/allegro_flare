#ifndef __ALLEGRO_FLARE_FILE_DOWNLOADER
#define __ALLEGRO_FLARE_FILE_DOWNLOADER




#include <vector>
#include <string>




class FileDownloader
{
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
   private:
      int id;
      download_status_t status;
      float percentage;
      std::string file_url;
      std::string local_filename;
      std::string error;

   public:
      FileHandle(std::string file_url, std::string local_filename);
      ~FileHandle();

      float get_percentage();
      download_status_t get_status();
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
