#ifndef AF_SEGOE_SYMBOL_HEADER
#define AF_SEGOE_SYMBOL_HEADER




#include <stdint.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>




namespace segoe_ui_symbol
{
   //void draw(ALLEGRO_FONT *font, ALLEGRO_COLOR color, int32_t icon, int flags, float x, float y);

   /* Hearts */
   extern const int32_t outlinedheart;
   extern const int32_t solidheart;
   extern const int32_t brokenheart;
   extern const int32_t solidheartzerowidth;
   extern const int32_t brokenheartzerowidth;

   /* Rating Stars */
   extern const int32_t outlinedstar;
   extern const int32_t solidstar;
   extern const int32_t solidstarzerowidth;
   extern const int32_t solidstarreducedpadding;
   extern const int32_t smallstar;

   /* Checkbox Components */
   extern const int32_t checkmark;
   extern const int32_t checkfill;
   extern const int32_t checkbox;
   extern const int32_t checkindeterminatestate;
   extern const int32_t checkreversed;
   extern const int32_t e106;
   extern const int32_t e107;
   extern const int32_t checkmarkzerowidth;
   extern const int32_t checkfillzerowidth;
   extern const int32_t checkcomposite;

   /* Miscellaneous */
   extern const int32_t comment;
   extern const int32_t favorite;
   extern const int32_t like;
   extern const int32_t video;
   extern const int32_t mailmessage;
   extern const int32_t reply;
   extern const int32_t favorite_A;
   extern const int32_t unfavorite;
   extern const int32_t mobilecontact;
   extern const int32_t blockedconent;
   extern const int32_t typingindicator;
   extern const int32_t videopresencechicklet;
   extern const int32_t presencechicklet;

   /*Scrollbararrows*/
   extern const int32_t chevronleft;
   extern const int32_t chevronright;
   extern const int32_t chevronleftbold;
   extern const int32_t chevronrightbold;
   extern const int32_t chevronup;
   extern const int32_t chevrondown;
   extern const int32_t chevronupbold;
   extern const int32_t chevrondownbold;

   /* Progressive Disclosure Arrows */
   extern const int32_t arrowleft;
   extern const int32_t arrowright;
   extern const int32_t arrowup;
   extern const int32_t arrowdown;
   extern const int32_t arrowleft2;
   extern const int32_t arrowright2;
   extern const int32_t arrowup2;
   extern const int32_t arrowdown2;
   extern const int32_t arrowleft3;
   extern const int32_t arrowright3;
   extern const int32_t arrowup3;
   extern const int32_t arrowdown3;
   extern const int32_t arrowleft4;
   extern const int32_t arrowright4;
   extern const int32_t arrowup4;
   extern const int32_t arrowdown4;

   /* Back buttons  20pt */
   extern const int32_t backbutton;
   extern const int32_t backbuttonoutline;
   extern const int32_t backbuttonarrow;
   extern const int32_t backbuttonfill;
   extern const int32_t backbuttonreversed;
   extern const int32_t backbuttonmirrored;
   extern const int32_t backbuttonarrowmirrored;
   extern const int32_t backbuttonreversedmirrored;

   /* Back Buttons  42pt */
   extern const int32_t backbuttonlarge;
   extern const int32_t backbuttonoutlinelarge;
   extern const int32_t backbuttonarrowlarge;
   extern const int32_t backbuttonfilllarge;
   extern const int32_t backbuttonreversedlarge;
   extern const int32_t backbuttonmirroredlarge;
   extern const int32_t backbuttonarrowmirroredlarge;
   extern const int32_t backbuttonreversedmirroredlarge;

   /* Back arrows for HTML */
   extern const int32_t arrowhtml;
   extern const int32_t arrowhtmlmirrored;

   /* Appbar Glyphs*/
   extern const int32_t previous;
   extern const int32_t next;
   extern const int32_t play;
   extern const int32_t pause;
   extern const int32_t edit;
   extern const int32_t save;
   extern const int32_t clear;
   extern const int32_t trash;
   extern const int32_t remove;
   extern const int32_t add;
   extern const int32_t cancel;
   extern const int32_t accept;
   extern const int32_t more;
   extern const int32_t redo;
   extern const int32_t undo;
   extern const int32_t home;
   extern const int32_t up;
   extern const int32_t forward;
   extern const int32_t back;
   extern const int32_t favorite;
   extern const int32_t camera;
   extern const int32_t settings;
   extern const int32_t video_A;
   extern const int32_t sync;
   extern const int32_t download;
   extern const int32_t mail;
   extern const int32_t find;
   extern const int32_t help;
   extern const int32_t upload;
   extern const int32_t emoticon;
   extern const int32_t layout;
   extern const int32_t leavemultipartyconversation;
   extern const int32_t forward_A;
   extern const int32_t timer;
   extern const int32_t send;
   extern const int32_t crop;
   extern const int32_t rotatecamera;
   extern const int32_t people;
   extern const int32_t closemetadata;
   extern const int32_t openmetadata;
   extern const int32_t openinweb;
   extern const int32_t viewnotifications;
   extern const int32_t previewlink;
   extern const int32_t globe;
   extern const int32_t trimvideo;
   extern const int32_t usbcamera;
   extern const int32_t zoom;
   extern const int32_t bookmarks;
   extern const int32_t pdf;
   extern const int32_t pdfprotected;
   extern const int32_t page;
   extern const int32_t moreoptions;
   extern const int32_t post;
   extern const int32_t mail2;
   extern const int32_t contactinfo;
   extern const int32_t hangup;
   extern const int32_t viewallalbums;
   extern const int32_t mapaddress;
   extern const int32_t phone;
   extern const int32_t videochat;
   extern const int32_t switch_;  // switch_ is used because switch is a keyword
   extern const int32_t presence;
   extern const int32_t rename;
   extern const int32_t expandtile;
   extern const int32_t reducetile;
   extern const int32_t pin;
   extern const int32_t viewallinfo;
   extern const int32_t go;
   extern const int32_t keyboard;
   extern const int32_t dock;
   extern const int32_t charmsbar;
   extern const int32_t appbar;
   extern const int32_t remotedesktophome;
   extern const int32_t refresh;
   extern const int32_t rotate;
   extern const int32_t shuffle;
   extern const int32_t details;
   extern const int32_t shop;
   extern const int32_t selectall;
   extern const int32_t rotate_A;
   extern const int32_t import;
   extern const int32_t importall;
   extern const int32_t singlefile;
   extern const int32_t showallfiles;
   extern const int32_t browsephotos;
   extern const int32_t takewebcampicture;
   extern const int32_t picturelibrary;
   extern const int32_t saveloval;
   extern const int32_t caption;
   extern const int32_t stop;
   extern const int32_t results;
   extern const int32_t volume;
   extern const int32_t tools;
   extern const int32_t startchat;
   extern const int32_t document;
   extern const int32_t day;
   extern const int32_t week;
   extern const int32_t month;
   extern const int32_t matchoptions;
   extern const int32_t replyall;
   extern const int32_t read;
   extern const int32_t link;
   extern const int32_t accounts;
   extern const int32_t showbcc;
   extern const int32_t bcc;
   extern const int32_t cut;
   extern const int32_t attach;
   extern const int32_t e16d;
   extern const int32_t filter;
   extern const int32_t copy;
   extern const int32_t emoji2;
   extern const int32_t highpriority;
   extern const int32_t reply_A;
   extern const int32_t slideshow;
   extern const int32_t sort;
   extern const int32_t allapplications;
   extern const int32_t disconnectnetworkdrive;
   extern const int32_t mapnetworkdrive;
   extern const int32_t opennewwindows;
   extern const int32_t openwith;
   extern const int32_t circleforDUI;
   extern const int32_t fillforDUI;
   extern const int32_t statuspresence;
   extern const int32_t options;
   extern const int32_t skydrive;
   extern const int32_t calendar;
   extern const int32_t font;
   extern const int32_t fontcolor;
   extern const int32_t status;
   extern const int32_t browsebyalbum;
   extern const int32_t alternateaudiotrack;
   extern const int32_t placeholder;
   extern const int32_t view;
   extern const int32_t setaslockscreenimage;
   extern const int32_t setastileimage;
   extern const int32_t closedcaptionjapan;
   extern const int32_t closedcaptioneuro;
   extern const int32_t closedcaption;
   extern const int32_t autoplaystop;
   extern const int32_t permissions;
   extern const int32_t highlight;
   extern const int32_t disableupdates;
   extern const int32_t unfavorite_A;
   extern const int32_t unpin;
   extern const int32_t openfilelocation;
   extern const int32_t volumemute;
   extern const int32_t italic;
   extern const int32_t underline;
   extern const int32_t bold;
   extern const int32_t movetofolder;
   extern const int32_t chooselikeordislike;
   extern const int32_t dislike;
   extern const int32_t like_A;
   extern const int32_t alignright;
   extern const int32_t aligncenter;
   extern const int32_t alignleft;
   extern const int32_t zoomneutral;
   extern const int32_t zoomout;
   extern const int32_t openfile;
   extern const int32_t runasotheruser;
   extern const int32_t runasadmin;
   extern const int32_t italic2;
   extern const int32_t bold2;
   extern const int32_t underline2;
   extern const int32_t bold3;
   extern const int32_t italic3;
   extern const int32_t underline3;
   extern const int32_t italic4;
   extern const int32_t bold4;
   extern const int32_t underline4;
   extern const int32_t bold5;
   extern const int32_t fontstylekorean;
   extern const int32_t underlinekorean;
   extern const int32_t italickorean;
   extern const int32_t boldkorean;
   extern const int32_t fontcolorkorean;
   extern const int32_t street;
   extern const int32_t map;
   extern const int32_t clearselection;
   extern const int32_t fontsizedecrease;
   extern const int32_t fontsizeincrease;
   extern const int32_t fontsize;
   extern const int32_t cellphone;
   extern const int32_t retweet;
   extern const int32_t tag;
   extern const int32_t repeatonce;
   extern const int32_t repeatloop;
   extern const int32_t favoritestarempty;
   extern const int32_t addtofavorite;
   extern const int32_t calculator;
   extern const int32_t direction;
   extern const int32_t currentlocationgps;
   extern const int32_t library;
   extern const int32_t addressbook;
   extern const int32_t voicemailmemo;
   extern const int32_t microphone;
   extern const int32_t postupdate;
   extern const int32_t backtowindow;
   extern const int32_t fullscreen;
   extern const int32_t addnewfolder;
   extern const int32_t calendarreply;
   extern const int32_t unsyncfolder;
   extern const int32_t reporthacked;
   extern const int32_t syncfolder;
   extern const int32_t blockcontact;
   extern const int32_t rdswitchapps;
   extern const int32_t addfriendviewinvites;
   extern const int32_t rdtouchpointer;
   extern const int32_t rdgotostart;
   extern const int32_t rdzerobars;
   extern const int32_t rdonebar;
   extern const int32_t rdtwobars;
   extern const int32_t rdthreebars;
   extern const int32_t rdfourbars;
   extern const int32_t italic5;
}




#endif
