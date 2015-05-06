#include <allegro_flare/curl.h>

#include <curl/curl.h>
#include <allegro5/allegro.h>


static ALLEGRO_FILE *file_to_write_to;
static double download_total_size = 0.0;
static double downloaded_so_far = 0.0;


static size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp)
{
	size_t count;
	count = al_fwrite(file_to_write_to, buffer, size*nmemb);
	return count;
}


static int progress_callback(void *clientp, double dltotal, double dlnow, double ultotal, double ulnow)
{
	download_total_size = dltotal;
	downloaded_so_far = dlnow;
	return 0;
}


static inline void af_download_file(std::string url, std::string dest_filename, std::string write_mode)
{
	CURL *curl_handle = curl_easy_init();

	file_to_write_to = al_fopen(dest_filename.c_str(), write_mode.c_str());

	curl_easy_setopt(curl_handle, CURLOPT_URL, url.c_str());
	curl_easy_setopt(curl_handle, CURLOPT_FOLLOWLOCATION, 1);
	curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_data);
	curl_easy_setopt(curl_handle, CURLOPT_PROGRESSFUNCTION, &progress_callback);
	curl_easy_perform(curl_handle);

	al_fclose(file_to_write_to);
	file_to_write_to = NULL;

	curl_easy_cleanup(curl_handle);
}



/**************/

void download_binary_file(std::string url, std::string dest_filename)
{
	af_download_file(url, dest_filename, "wb");
}


void download_file(std::string url, std::string dest_filename)
{
	af_download_file(url, dest_filename, "w");
}

float get_progress_percent()
{
	if (download_total_size == 0.0) return -1;
	return downloaded_so_far / download_total_size;
}






/**********dirty from here on down, clean it up later? :)**************/

/***************************************************************************
 *                                  _   _ ____  _
 *  Project                     ___| | | |  _ \| |
 *                             / __| | | | |_) | |
 *                            | (__| |_| |  _ <| |___
 *                             \___|\___/|_| \_\_____|
 *
 * Copyright (C) 1998 - 2012, Daniel Stenberg, <daniel@haxx.se>, et al.
 *
 * This software is licensed as described in the file COPYING, which
 * you should have received as part of this distribution. The terms
 * are also available at http://curl.haxx.se/docs/copyright.html.
 *
 * You may opt to use, copy, modify, merge, publish, distribute and/or sell
 * copies of the Software, and permit persons to whom the Software is
 * furnished to do so, under the terms of the COPYING file.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 ***************************************************************************/ 
#include <stdio.h>
#include <string.h>
 
#include <curl/curl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#ifdef WIN32
//#include <io.h>
#else
//#include <unistd.h>
#endif
//#include <iostream>
 

 
/* NOTE: if you want this example to work on Windows with libcurl as a
   DLL, you MUST also provide a read callback with CURLOPT_READFUNCTION.
   Failing to do so will give you a crash since a DLL may not use the
   variable's memory when passed in to it from an app like this. */ 
static size_t read_callback(void *ptr, size_t size, size_t nmemb, void *stream)
{
  curl_off_t nread;
  /* in real-world cases, this would probably get this data differently
     as this fread() stuff is exactly what the library already would do
     by default internally */ 
  size_t retcode = fread(ptr, size, nmemb, (FILE *)stream);
 
  nread = (curl_off_t)retcode;
 
  fprintf(stderr, "*** We read %" CURL_FORMAT_CURL_OFF_T
          " bytes from file\n", nread);
  return retcode;
}
 


#include <string>
#include <iostream>
int upload_file_via_ftp(std::string local_file_location, std::string filename_while_uploading, std::string remote_filename_after_uploading,
						std::string remote_url, std::string username, std::string password);



/*
int main(void)
{
	#define _LOCAL_FILE      "c:/162-17x42.jpg"
	#define _UPLOAD_FILE_AS  "162-17x42-uploading.jpg"
	#define _RENAME_FILE_TO  "162-17x42-renamed.jpg"
	#define _REMOTE_URL_ROOT "ftp://ftp.zeoxdesign.com"
	#define _REMOTE_URL      _REMOTE_URL_ROOT "/" UPLOAD_FILE_AS
	#define _USERNAME		"soncb@zeoxdesign.com"
	#define _PASSWORD		"soncb_pass"

	upload_file_via_ftp(_LOCAL_FILE, _UPLOAD_FILE_AS, _RENAME_FILE_TO,
						_REMOTE_URL_ROOT, _USERNAME, _PASSWORD);
}
*/



int upload_file_via_ftp(std::string local_file_location, std::string filename_while_uploading, std::string remote_filename_after_uploading,
						std::string remote_url, std::string username, std::string password)
{
  CURL *curl;
  CURLcode res;
  FILE *hd_src;
  struct stat file_info;
  curl_off_t fsize;
 
  struct curl_slist *headerlist=NULL;
  //static const char buf_1 [] = "RNFR " UPLOAD_FILE_AS;
  //static const char buf_2 [] = "RNTO " RENAME_FILE_TO;
 
  /* get the file size of the local file */ 
  if(stat(local_file_location.c_str(), &file_info)) {
	  std::cout << "{upload_file_via_ftp()]: Couldn't open " << remote_url << "." << std::endl;
		//printf("Couldnt open '%s': %s\n", local_file_location.c_str(), strerror(errno));
    return 1;
  }
  fsize = (curl_off_t)file_info.st_size;
 
  printf("Local file size: %" CURL_FORMAT_CURL_OFF_T " bytes.\n", fsize);
 
  /* get a FILE * of the same file */ 
  hd_src = fopen(local_file_location.c_str(), "rb");
 
  /* In windows, this will init the winsock stuff */ 
  curl_global_init(CURL_GLOBAL_ALL);
 
  /* get a curl handle */ 
  curl = curl_easy_init();
  if(curl) {
    /* build a list of commands to pass to libcurl */ 
    headerlist = curl_slist_append(headerlist, ("RNFR " + filename_while_uploading).c_str());
    headerlist = curl_slist_append(headerlist, ("RNTO " + remote_filename_after_uploading).c_str());
 
    /* we want to use our own read function */ 
    curl_easy_setopt(curl, CURLOPT_READFUNCTION, read_callback);
 
    /* enable uploading */ 
    curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
 
    /* specify target */ 
    curl_easy_setopt(curl, CURLOPT_URL, (remote_url + "/" + filename_while_uploading).c_str());
 
	//"ftp.zeoxdesign.com/"

	curl_easy_setopt(curl, CURLOPT_USERNAME, username.c_str());
	curl_easy_setopt(curl, CURLOPT_PASSWORD, password.c_str());

    /* pass in that last of FTP commands to run after the transfer */ 
    curl_easy_setopt(curl, CURLOPT_POSTQUOTE, headerlist);
 
    /* now specify which file to upload */ 
    curl_easy_setopt(curl, CURLOPT_READDATA, hd_src);
 
    /* Set the size of the file to upload (optional).  If you give a *_LARGE
       option you MUST make sure that the type of the passed-in argument is a
       curl_off_t. If you use CURLOPT_INFILESIZE (without _LARGE) you must
       make sure that to pass in a type 'long' argument. */ 
    curl_easy_setopt(curl, CURLOPT_INFILESIZE_LARGE,
                     (curl_off_t)fsize);
 
    /* Now run off and do what you've been told! */ 
    res = curl_easy_perform(curl);
    /* Check for errors */ 
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
 
    /* clean up the FTP commands list */ 
    curl_slist_free_all (headerlist);
 
    /* always cleanup */ 
    curl_easy_cleanup(curl);
  }
  fclose(hd_src); /* close the local file */ 
 
  curl_global_cleanup();


  //Sleep(1);

  return 0;
}















///////////////// DOWNLOAD DIRECTLY TO MEMORY /////////////////////



/***************************************************************************
 *                                  _   _ ____  _
 *  Project                     ___| | | |  _ \| |
 *                             / __| | | | |_) | |
 *                            | (__| |_| |  _ <| |___
 *                             \___|\___/|_| \_\_____|
 *
 * Copyright (C) 1998 - 2013, Daniel Stenberg, <daniel@haxx.se>, et al.
 *
 * This software is licensed as described in the file COPYING, which
 * you should have received as part of this distribution. The terms
 * are also available at http://curl.haxx.se/docs/copyright.html.
 *
 * You may opt to use, copy, modify, merge, publish, distribute and/or sell
 * copies of the Software, and permit persons to whom the Software is
 * furnished to do so, under the terms of the COPYING file.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 ***************************************************************************/ 
/* Example source code to show how the callback function can be used to
 * download data into a chunk of memory instead of storing it in a file.
 */ 
 


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#include <curl/curl.h>
 


 

static size_t grab_url_to_memory__WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
  size_t realsize = size * nmemb;
  struct DownloadMemoryStruct *mem = (struct DownloadMemoryStruct *)userp;
 
  mem->memory = (char *)realloc(mem->memory, mem->size + realsize + 1);
  if(mem->memory == NULL) {
    /* out of memory! */ 
    printf("not enough memory (realloc returned NULL)\n");
    return 0;
  }
 
  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;
 
  return realsize;
}
 
 


/*

// An example of a function that will write the downloaded data to a file (via allegro's ALLEGRO_FILE routines)

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





DownloadMemoryStruct *download_to_memory(std::string url, bool (*do_something_with_it)(DownloadMemoryStruct *str))
{
  CURL *curl_handle;
  CURLcode res;
 
  DownloadMemoryStruct *chunk_ptr = new DownloadMemoryStruct();
 
  DownloadMemoryStruct &chunk = (*chunk_ptr);


  chunk.memory = (char *)malloc(1);  /* will be grown as needed by the realloc above */ 
  chunk.size = 0;    /* no data at this point */ 

  curl_global_init(CURL_GLOBAL_ALL);
 
  /* init the curl session */ 
  curl_handle = curl_easy_init();
 
  /* specify URL to get */ 
  curl_easy_setopt(curl_handle, CURLOPT_URL, url.c_str());
 
  /* send all data to this function  */ 
  curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, grab_url_to_memory__WriteMemoryCallback);
 
  /* we pass our 'chunk' struct to the callback function */ 
  curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);
 
  /* some servers don't like requests that are made without a user-agent
     field, so we provide one */ 
  curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows; U; Windows NT 6.1; en-US; rv:1.9.1.2) Gecko/20090729 Firefox/3.5.2 GTB5");
  //libcurl-agent/1.0");
 
  printf("downloading file to memory...");

  /* get it! */ 
  res = curl_easy_perform(curl_handle);
 
  /* check for errors */ 
  if(res != CURLE_OK) {
    fprintf(stderr, "curl_easy_perform() failed: %s\n",
            curl_easy_strerror(res));
  }
  else {
    /*
     * Now, our chunk.memory points to a memory block that is chunk.size
     * bytes big and contains the remote file.
     *
     * Do something nice with it!
     */ 
 
	  if (do_something_with_it) do_something_with_it(chunk_ptr);



	printf("%lu bytes retrieved\n", (long)chunk.size);
  }
 
  /* cleanup curl stuff */ 
  curl_easy_cleanup(curl_handle);
 
  /*
  if(chunk.memory)
    free(chunk.memory);
 
  // we're done with libcurl, so clean it up
  curl_global_cleanup();
 
  return NULL;
  */

  return chunk_ptr;
}


bool delete_downloaded_to_memory_file(DownloadMemoryStruct *mem)
{
	if (!mem) return false;
	if(mem->memory) free(mem->memory);
	else return false;
	delete mem;
	return true;
}




// could be made more optimal if it allowed for the reuse of handles





bool delete_downloaded_al_memfile(DOWNLOADED_ALLEGRO_FILE *file)
{
	if (!file) return false;
	if (file->file) al_fclose(file->file);
	if (file->memory) free(file->memory);
	delete file;
	return true;
}
 



DOWNLOADED_ALLEGRO_FILE *create_downloaded_al_memfile(std::string url)
{
	DOWNLOADED_ALLEGRO_FILE *al_file = new DOWNLOADED_ALLEGRO_FILE();
  CURL *curl_handle;
  CURLcode res;
 
  DownloadMemoryStruct *chunk_ptr = new DownloadMemoryStruct();
 
  DownloadMemoryStruct &chunk = (*chunk_ptr);


  chunk.memory = (char *)malloc(1);  /* will be grown as needed by the realloc above */ 
  chunk.size = 0;    /* no data at this point */ 

  curl_global_init(CURL_GLOBAL_ALL);
 
  /* init the curl session */ 
  curl_handle = curl_easy_init();
 
  /* specify URL to get */ 
  curl_easy_setopt(curl_handle, CURLOPT_URL, url.c_str());
 
  /* send all data to this function  */ 
  curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, grab_url_to_memory__WriteMemoryCallback);
 
  /* we pass our 'chunk' struct to the callback function */ 
  curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);
 
  /* some servers don't like requests that are made without a user-agent
     field, so we provide one */ 
  curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows; U; Windows NT 6.1; en-US; rv:1.9.1.2) Gecko/20090729 Firefox/3.5.2 GTB5");
  //libcurl-agent/1.0");
 
  printf("downloading file to memory\n");

  /* get it! */ 
  res = curl_easy_perform(curl_handle);
 
  /* check for errors */ 
  if(res != CURLE_OK) {
    fprintf(stderr, "curl_easy_perform() failed: %s\n",
            curl_easy_strerror(res));
  }
  else {
    /*
     * Now, our chunk.memory points to a memory block that is chunk.size
     * bytes big and contains the remote file.
     *
     * Do something nice with it!
     */ 
 
	  //if (do_something_with_it) do_something_with_it(chunk_ptr);

	  
	  //if (!stru) return false;

	//std::cout << "AAA";
	  //DOWNLOADED_ALLEGRO_FILE
	al_file->memory = new char[chunk.size];
	al_file->size = chunk.size;

	printf("writing to ALLEGRO_FILE\n");
	al_file->file = al_open_memfile(al_file->memory, chunk.size, "rwb");
	if (!al_file)
	{
		std::cout << "error: al_file could not be created via al_open_memfile\n";
		delete_downloaded_to_memory_file(&chunk);
		return NULL;
	}
	for (long i=0; i<(long)chunk.size; i++)
	{
		al_fputc(al_file->file, chunk.memory[i]);
	}//al_file->memory
	al_fflush(al_file->file);
	//al_fclose(f);
	printf("ALLEGRO_FILE written\n");


	//al_file


	  printf("%lu bytes retrieved\n", (long)chunk.size);
  }
 

  delete_downloaded_to_memory_file(&chunk);

  /* cleanup curl stuff */ 
  curl_easy_cleanup(curl_handle);
 
  /*
  if(chunk.memory)
    free(chunk.memory);
 
  // we're done with libcurl, so clean it up
  curl_global_cleanup();
 
  return NULL;
  */

  return al_file;
}










ALLEGRO_BITMAP *af_download_bitmap(std::string url, std::string extension)
{

	ALLEGRO_BITMAP *bmp = NULL;
	DOWNLOADED_ALLEGRO_FILE *downloaded_file = create_downloaded_al_memfile(url);

	size_t last_dot_pos = url.rfind(".");
	if (extension.empty())
	{
		if (last_dot_pos != std::string::npos)
		{
			extension = url.substr(last_dot_pos);
			std::cout << "auto-detected extension \"" << extension << "\"" << std::endl;
		}
	}


	if (downloaded_file->file)
	{
		bmp = al_load_bitmap_f(downloaded_file->file, extension.c_str());
		if (!bmp) std::cout << "bitmap not valid";
		//al_save_bitmap("my_saved_bitmap.png", bmp);
	}
	else
	{
		std::cout << "null downloaded_file->file";
	}
	delete_downloaded_al_memfile(downloaded_file);


	return bmp;
}
