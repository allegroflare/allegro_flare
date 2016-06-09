#ifndef __AF_INTERPROCESS_THROUGH_FILES_HEADER
#define __AF_INTERPROCESS_THROUGH_FILES_HEADER




#include <allegro_flare/allegro_flare.h>




class InterprocessThroughFiles
{
private:
   friend class AllegroFlare;

   class instruction_data_t
   {
   public:
      double time_found;
      std::string filename;
      ALLEGRO_PATH *path;
      bool found;
      bool removed;

      instruction_data_t(std::string filename, ALLEGRO_PATH *directory_location);
      bool exists();
      bool delete_file();
      const char *get_full_path();
   };

   bool instruction_file_exists(std::string &filename);
   ALLEGRO_PATH *directory_location;
   ALLEGRO_PATH *participant_file_path;
   std::vector<std::string> instruction_filename;
   std::vector<instruction_data_t *> instruction_data;
   std::string this_controller_id;
   std::ostream *log_output;

public:
   void set_log_output(std::ostream *output);

   InterprocessThroughFiles(std::string full_path="C:/II/");
   ~InterprocessThroughFiles();

   void write_interprocess_instruction(std::string instruction);
   void check_for_interprocess_instructions();
   virtual void process_interprocess_instruction(std::string &filename);

   std::string get_controller_id();

   // cleanup
   void delete_interprocess_files_aged(double age_in_sec);
   void delete_interprocess_file(std::string &filename);
   void clear_folder(); // should only be used by the controller;
};





#endif
