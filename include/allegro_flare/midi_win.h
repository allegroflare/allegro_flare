#ifndef __AF_MIDI_WIN_HEADER
#define __AF_MIDI_WIN_HEADER





#include <vector>


#define NOTE_OFF			 0x80
#define NOTE_ON				 0x90
#define AFTERTOUCH			 0xA0
#define CONTINOUS_CONTROLLER 0xB0
#define PATCH_CHANGE	     0xC0
#define CHANNEL_PRESSURE     0xD0
#define PITCH_BEND		     0xE0
#define SYSTEM_MESSAGE		 0xF0



class MIDI_IN_DEVICE
{
public:
	bool open;
	unsigned short device_port_num;
	unsigned short manufacturer_id;
	unsigned short product_id;
	unsigned int driver_version;
	char name[32]; // replace this with a string
};


class MIDI_OUT_DEVICE
{
public:
	bool open;
	unsigned short device_port_num;
	unsigned short manufacturer_id;
	unsigned short product_id;
	unsigned int driver_version;
	char name[32]; // replace this with a string
	unsigned short device_type;
	unsigned short num_voices; //<- if this device is a port, then this number is 0
	unsigned short num_notes; //<- if this device is a port, then this number is 0
	unsigned short num_channels;
};


extern std::vector<MIDI_IN_DEVICE *> midi_in_device;
extern std::vector<MIDI_OUT_DEVICE *> midi_out_device;

void init_midi();
void uninstall_midi();

bool open_midi_device(MIDI_OUT_DEVICE *dev);
bool midi_patch_change(unsigned char channel, unsigned char patch_num);
bool midi_note_on(unsigned char channel, unsigned char pitch, unsigned char velocity);
bool midi_note_off(unsigned char channel, unsigned char pitch);
void midi_all_notes_off();

bool midi_sysex_send_message(char device_id, char command_format, char command, char data);




#endif