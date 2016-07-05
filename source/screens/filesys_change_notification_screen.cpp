



/*

Disclaimer:

Ok, this is nasty code.  It needs a lot of work to be user friendly and more readable

*/




#include <allegro_flare/screens/filesys_change_notification_screen.h>




FileSysChangeNotificationScreen *FileSysChangeNotificationScreen::instance = NULL;




FileSysChangeNotificationScreen::FileSysChangeNotificationScreen()
{
   al_init_user_event_source(&filesys_change_event_source);
   al_register_event_source(Framework::event_queue, &filesys_change_event_source);
   // spawn watcher thread
}




FileSysChangeNotificationScreen::~FileSysChangeNotificationScreen()
{
   al_unregister_event_source(Framework::event_queue, &filesys_change_event_source);
   // join watcher thread
}




FileSysChangeNotificationScreen *FileSysChangeNotificationScreen::get_instance()
{
   if (!instance) instance = new FileSysChangeNotificationScreen();
   return instance;
}




void _filesys_change_event_dtor(ALLEGRO_EVENT *e)
{
   if (!e) return;
   if (e->user.type == ALLEGRO_EVENT_FILESYS_CHANGE)
   {
      // TODO
      // distruct data here
      //std::string *ptr = static_cast<std::string *>(e->user.data2);
      //delete ptr;
      //my_event.user.data2 = (intptr_t)(new std::string(value)); // directory that fired the changed as std::string*
   }
}




void FileSysChangeNotificationScreen::emit_filesys_change(std::string value)
{
   ALLEGRO_EVENT my_event;
   my_event.user.type = ALLEGRO_EVENT_FILESYS_CHANGE;
   // TODO:
   // the string data needs to be destructed at some later point!!
   // this is a danggling pointer.
   my_event.user.data1 = 0; // directory that fired the changed as std::string*
   my_event.user.data2 = (intptr_t)(new std::string(value)); // directory that fired the changed as std::string*
   al_emit_user_event(&get_instance()->filesys_change_event_source, &my_event, NULL);
}







#ifdef _WIN32






//
//
//
//
// Windows implementation below
//
//
//
//

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>



struct folder_watch_handle
{
   HANDLE handle;
   std::string folder;
};


std::vector<folder_watch_handle> folder_watch_handles;






static ALLEGRO_THREAD *_filesys_watch_thread = NULL;

static void RefreshDirectory(LPTSTR);
static void RefreshTree(LPTSTR);
static void WatchDirectory(LPTSTR);



/*
void _tmain(int argc, TCHAR *argv[])
{
   if(argc != 2)
   {
      _tprintf(TEXT("Usage: %s <dir>\n"), argv[0]);
      return;
   }

   WatchDirectory(argv[1]);
}
*/

void WatchDirectory(LPTSTR lpDir)
{
   //	LPTSTR lpDir = "C:/Users/Mark/Desktop";
   DWORD dwWaitStatus; 
   HANDLE dwChangeHandles[2]; 


   char lpDrive[4] = "C:\\";


   std::cout << "Initializing watch directory... " << std::endl;

   /*
   TCHAR lpDrive[4];
   TCHAR lpFile[_MAX_FNAME];
   TCHAR lpExt[_MAX_EXT];

   _tsplitpath_s(lpDir, lpDrive, 4, NULL, 0, lpFile, _MAX_FNAME, lpExt, _MAX_EXT);

   lpDrive[2] = (TCHAR)'\\';
   lpDrive[3] = (TCHAR)'\0';
   */


   // Watch the directory for file creation and deletion. 

   dwChangeHandles[0] = FindFirstChangeNotification( 
         lpDir,                         // directory to watch 
         FALSE,                         // do not watch subtree 
         FILE_NOTIFY_CHANGE_FILE_NAME); // watch file name changes 

   if (dwChangeHandles[0] == INVALID_HANDLE_VALUE)
   {
      printf("\n ERROR: FindFirstChangeNotification function failed.\n");
      ExitProcess(GetLastError()); 
   }

   // Watch the subtree for directory creation and deletion. 

   dwChangeHandles[1] = FindFirstChangeNotification( 
         lpDrive,                       // directory to watch 
         TRUE,                          // watch the subtree 
         FILE_NOTIFY_CHANGE_DIR_NAME);  // watch dir name changes 

   if (dwChangeHandles[1] == INVALID_HANDLE_VALUE) 
   {
      printf("\n ERROR: FindFirstChangeNotification function failed.\n");
      ExitProcess(GetLastError()); 
   }


   // Make a final validation check on our handles.

   if ((dwChangeHandles[0] == NULL) || (dwChangeHandles[1] == NULL))
   {
      printf("\n ERROR: Unexpected NULL from FindFirstChangeNotification.\n");
      ExitProcess(GetLastError()); 
   }

   // Change notification is set. Now wait on both notification 
   // handles and refresh accordingly. 

   while (TRUE) 
   { 
      // Wait for notification.

      printf("\nWaiting for notification...\n");

      dwWaitStatus = WaitForMultipleObjects(2, dwChangeHandles, 
            FALSE, INFINITE); 

      printf("\nWaiting for notification...\n");

      switch (dwWaitStatus) 
      { 
      case WAIT_OBJECT_0: 

         // A file was created, renamed, or deleted in the directory.
         // Refresh this directory and restart the notification.

         RefreshDirectory(lpDir); 
         if ( FindNextChangeNotification(dwChangeHandles[0]) == FALSE )
         {
            printf("\n ERROR: FindNextChangeNotification function failed.\n");
            ExitProcess(GetLastError()); 
         }
         break; 

      case WAIT_OBJECT_0 + 1: 

         // A directory was created, renamed, or deleted.
         // Refresh the tree and restart the notification.

         RefreshTree(lpDrive); 
         if (FindNextChangeNotification(dwChangeHandles[1]) == FALSE )
         {
            printf("\n ERROR: FindNextChangeNotification function failed.\n");
            ExitProcess(GetLastError()); 
         }
         break; 

      case WAIT_TIMEOUT:

         // A timeout occurred, this would happen if some value other 
         // than INFINITE is used in the Wait call and no changes occur.
         // In a single-threaded environment you might not want an
         // INFINITE wait.

         printf("\nNo changes in the timeout period.\n");
         break;

      default: 
         printf("\n ERROR: Unhandled dwWaitStatus.\n");
         ExitProcess(GetLastError());
         break;
      }
   }
}

void RefreshDirectory(LPTSTR lpDir)
{
   // This is where you might place code to refresh your
   // directory listing, but not the subtree because it
   // would not be necessary.
   FileSysChangeNotificationScreen::emit_filesys_change(lpDir);
   _tprintf(TEXT("Directory (%s) changed.\n"), lpDir);
}

void RefreshTree(LPTSTR lpDrive)
{
   // This is where you might place code to refresh your
   // directory listing, including the subtree.

   FileSysChangeNotificationScreen::emit_filesys_change(lpDrive);
   _tprintf(TEXT("Directory tree (%s) changed.\n"), lpDrive);
}





//////////////////////////////////


void *_filesys_watch_thread_proc(ALLEGRO_THREAD *this_thread, void *args)
{
   if (!args) return NULL;

   // what a mess :(

   std::string directory = *static_cast<std::string *>(args);
   WatchDirectory(const_cast<char *>(directory.c_str()));
}


//////////////////////////////////


void FileSysChangeNotificationScreen::watch_directory__blocking(std::string directory)
{
   WatchDirectory(const_cast<char *>(directory.c_str()));
}



void FileSysChangeNotificationScreen::watch_directory__in_thread(std::string directory)
{
   if (_filesys_watch_thread)
   {
      std::cout << "Thread already exists watching another directory.  Limit 1" << std::endl;
      return;
   }

   FileSysChangeNotificationScreen *inst = get_instance();
   std::string *args = new std::string(directory);
   _filesys_watch_thread = al_create_thread(_filesys_watch_thread_proc, args);
   if (_filesys_watch_thread) al_start_thread(_filesys_watch_thread);
   else std::cout << "there was an error with allegro when trying to create the thread." << std::endl;
}



#else


// TODO
void FileSysChangeNotificationScreen::watch_directory__in_thread(std::string directory)
{
   std::cout << "FileSysChangeNotificationSccreen::whatch_directory__blocking() is not supported on this platform" << std::endl;
}


// TODO
void FileSysChangeNotificationScreen::watch_directory__blocking(std::string directory)
{
   std::cout << "FileSysChangeNotificationSccreen::whatch_directory__blocking() is not supported on this platform" << std::endl;
}


#endif


