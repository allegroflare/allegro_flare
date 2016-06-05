#ifndef __AF_I18N_HEADER
#define __AF_I18N_HEADER




#include <string>
#include <map>




class I18n
{
private:
   I18n();
   ~I18n();

   static I18n *get_instance();
   static I18n *instance;

   std::string languages_folder;
   std::string current_locale;
   std::string current_language_filename;
   std::map<std::string, std::string> lines;

public:
   static bool initialize(std::string folder="data/languages/");
   static bool destruct();
   static bool set_languages_folder(std::string folder="data/languages/");
   static std::string get_languages_folder();
   static bool set_locale(std::string locale);
   static bool load_language_file(std::string filename);
   static std::string get_locale();
   static std::string get_language_name();
   static std::string t(std::string text_label);
};




#endif
