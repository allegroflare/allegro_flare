#ifndef __CURL_HEADER
#define __CURL_HEADER




#include <string>
#include <allegro5/allegro_memfile.h>




void download_binary_file(std::string url, std::string dest_filename); //TODO KNOWN ISSUE: dest_filename will crash if it includes path "/"
void download_file(std::string url, std::string dest_filename); //TODO KNOWN ISSUE: dest_filename will crash if it includes path "/"
float get_progress_percent();

int upload_file_via_ftp(std::string local_file_location, std::string filename_while_uploading, std::string remote_filename_after_uploading,
      std::string remote_url, std::string username, std::string password);




//TODO: do some more testing on the functions from here down.  For example, when files do not exist, or the request times out, etc...

struct DownloadMemoryStruct
{
   char *memory;
   size_t size;
};

DownloadMemoryStruct *download_to_memory(std::string url="http://www.example.com/", bool (*do_something_with_it)(DownloadMemoryStruct *str)=NULL);
bool delete_downloaded_to_memory_file(DownloadMemoryStruct *mem);

/*

// An example of a "do_something_with_it" function that will write the downloaded data to a file (via allegro's ALLEGRO_FILE routines)

bool something_done(DownloadMemoryStruct *stru)
{
   if (!stru) return false;

   printf("  ... to ALLEGRO_FILE ...");
   ALLEGRO_FILE *f = al_fopen("THIS_FILE.jpg", "wb");
   for (long i=0; i<(long)stru->size; i++)
   {
      al_fputc(f, stru->memory[i]);
   }
   al_fclose(f);
   printf("  ... ALLEGRO_FILE written ...");
}

*/




struct DOWNLOADED_ALLEGRO_FILE
{
public:
   ALLEGRO_FILE *file;
   char *memory;
   size_t size;
};


DOWNLOADED_ALLEGRO_FILE *create_downloaded_al_memfile(std::string url="http://www.example.com/");
bool delete_downloaded_al_memfile(DOWNLOADED_ALLEGRO_FILE *file);




ALLEGRO_BITMAP *af_download_bitmap(std::string url, std::string extension="");
// example:
//ALLEGRO_BITMAP *af_download_bitmap(std::string url="http://zeoxdesign.com/images/zeox_design_websites.jpg", std::sting extension=".jpg");
// or:
//ALLEGRO_BITMAP *af_download_bitmap(std::string url="http://zeoxdesign.com/images/zeox_design_websites.jpg", std::sting extension="");





#endif
