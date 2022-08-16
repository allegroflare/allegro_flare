

#include <AllegroFlare/Timeline/ScriptLoader.hpp>


   static std::vector<std::string> explode(const std::string &delimiter, const std::string &str)
   {
      // note: this function skips multiple delimiters, e.g. it will not return return empty tokens
      std::vector<std::string> arr;

      int strleng = str.length();
      int delleng = delimiter.length();
      if (delleng==0)
         return arr;//no change

      int i=0;
      int k=0;
      while(i<strleng)
      {
         int j=0;
         while (i+j<strleng && j<delleng && str[i+j]==delimiter[j])
            j++;
         if (j==delleng)//found delimiter
         {
            arr.push_back(str.substr(k, i-k));
            i+=delleng;
            k=i;
         }
         else
         {
            i++;
         }
      }
      arr.push_back(str.substr(k, i-k));
      return arr;
   }



namespace AllegroFlare
{
namespace Timeline
{



std::string ScriptLoader::remove_comments(std::string &line)
{
   std::size_t comment_pos = line.find("//");
   if (comment_pos == std::string::npos) return line;
   else return line.substr(0, comment_pos);
}



ScriptLoader::ScriptLoader()
{
}



ScriptLoader::~ScriptLoader()
{
}



ScriptLoader::ScriptLoader(std::string script)
   : current_line_index(0)
{
   lines = explode("\n", script);
};



int ScriptLoader::get_current_line_num()
{
   return current_line_index+1;
}



bool ScriptLoader::at_end()
{
   if (current_line_index >= lines.size()) return true;
   return false;
}




std::string ScriptLoader::get_next_line(bool remove_comments)
{
   return (remove_comments) ? ScriptLoader::remove_comments(lines[current_line_index++]) : lines[current_line_index++];
}



} // namespace Timeline
} // namespace AllegroFlare


