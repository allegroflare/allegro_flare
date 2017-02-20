



#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE TestFileDownloader
#include <boost/test/unit_test.hpp>




#include <allegro_flare/web/file_downloader.h>

#include <fstream>




BOOST_AUTO_TEST_CASE(FileHandle_get_local_filename_returns_the_local_filename)
{
   FileDownloader::FileHandle handle("", "a_local_filename.htm");
   BOOST_CHECK_EQUAL("a_local_filename.htm", handle.get_local_filename());
}




BOOST_AUTO_TEST_CASE(FileHandle_get_file_url_returns_the_file_url)
{
   FileDownloader::FileHandle handle("http://www.fakeurl.com", "");
   BOOST_CHECK_EQUAL("http://www.fakeurl.com", handle.get_file_url());
}




BOOST_AUTO_TEST_CASE(FileDownloader_with_no_URL_will_return_an_error_status)
{
   FileDownloader::FileHandle handle = FileDownloader::download_file("", "");
   BOOST_CHECK_EQUAL(FileDownloader::ERROR, handle.get_status());
}




BOOST_AUTO_TEST_CASE(FileDownloader_with_no_URL_will_return_an_error_message)
{
   FileDownloader::FileHandle handle = FileDownloader::download_file("", "");
   BOOST_CHECK_EQUAL("URL using bad/illegal format or missing URL", handle.get_error());
}




BOOST_AUTO_TEST_CASE(FileDownloader_will_download_a_remote_file)
{
   std::string file_url = "https://www.allegro.cc/theme/default/image/logo.png";
   std::string local_filename = "logo.png";
   FileDownloader::FileHandle handle = FileDownloader::download_file(file_url, local_filename);

   BOOST_CHECK_EQUAL(true, std::ifstream(local_filename).good());

   remove(local_filename.c_str());
}




BOOST_AUTO_TEST_CASE(FileDownloader_will_set_DOWNLOADED_status_on_a_successful_download)
{
   std::string file_url = "https://www.allegro.cc/theme/default/image/logo.png";
   std::string local_filename = "logo.png";
   FileDownloader::FileHandle handle = FileDownloader::download_file(file_url, local_filename);

   BOOST_CHECK_EQUAL(FileDownloader::DOWNLOADED, handle.get_status());

   remove(local_filename.c_str());
}




BOOST_AUTO_TEST_CASE(FileDownloader_will_set_an_error_status_when_a_file_url_does_not_exist)
{
   std::string file_url = "https://www.allegro.cc/this_file_does_not_exist.png";
   std::string local_filename = "";
   FileDownloader::FileHandle handle = FileDownloader::download_file(file_url, local_filename);

   BOOST_CHECK_EQUAL(FileDownloader::ERROR, handle.get_status());
}




BOOST_AUTO_TEST_CASE(FileDownloader_will_set_an_error_message_of_404_when_a_file_url_does_not_exist)
{
   std::string file_url = "https://www.allegro.cc/this_file_does_not_exist.png";
   std::string local_filename = "";
   FileDownloader::FileHandle handle = FileDownloader::download_file(file_url, local_filename);

   BOOST_CHECK_EQUAL("404", handle.get_error());
}




BOOST_AUTO_TEST_CASE(FileDownloader_will_set_an_ERROR_status_on_an_invalid_URL)
{
   std::string invalid_file_url = "htxs//wINVALID_URL_ww..cc.png";
   FileDownloader::FileHandle handle = FileDownloader::download_file(invalid_file_url, "");

   BOOST_CHECK_EQUAL(FileDownloader::ERROR, handle.get_status());
}




BOOST_AUTO_TEST_CASE(FileDownloader_will_set_an_error_message_on_an_invalid_URL)
{
   std::string invalid_file_url = "htxs//www..cc.png";
   FileDownloader::FileHandle handle = FileDownloader::download_file(invalid_file_url, "");

   BOOST_CHECK_EQUAL("Couldn't resolve host name", handle.get_error());
}




