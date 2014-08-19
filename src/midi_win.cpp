


#include <allegro_flare/midi_win.h>


// this is the windows specific midi calls


#include <windows.h>   /* required before including mmsystem.h */
#include <mmsystem.h>  /* multimedia functions (such as MIDI) for Windows */

#include <vector>
#include <string>
#include <iostream>




static bool midi_initialized = false;



std::vector<MIDI_IN_DEVICE *> midi_in_device;
std::vector<MIDI_OUT_DEVICE *> midi_out_device;



static HMIDIOUT current_midi_out_device_handler; //<- eventually this will be a vector
										  // so multiple devices can be used
										  // simultaniously.


void init_midi()
{
	if (midi_initialized) return;

	std::cout << "init_midi();" << std::endl;

	for (int i=0; i<(int)midi_out_device.size(); i++)
		delete midi_out_device[i];
	for (int i=0; i<(int)midi_in_device.size(); i++)
		delete midi_in_device[i];

	midi_out_device.clear();
	midi_in_device.clear();

	for (int i=0; i<(int)midiOutGetNumDevs(); i++)
	{
		midi_out_device.push_back(new MIDI_OUT_DEVICE());
		MIDIOUTCAPS device;
		midiOutGetDevCaps(i, &device, sizeof(MIDIOUTCAPS));

		midi_out_device.back()->device_port_num = i;
		midi_out_device.back()->open = false;
		midi_out_device.back()->manufacturer_id = device.wMid;
		midi_out_device.back()->product_id = device.wPid;
		midi_out_device.back()->driver_version = device.vDriverVersion;
		strcpy(midi_out_device.back()->name, device.szPname);
		strncpy(midi_out_device.back()->name, device.szPname, 32);
		midi_out_device.back()->device_type = device.wTechnology;
		midi_out_device.back()->num_voices = device.wVoices;
		midi_out_device.back()->num_notes = device.wNotes;
		midi_out_device.back()->num_channels = device.wChannelMask;
	}

	for (int i=0; i<(int)midiInGetNumDevs(); i++)
	{
		midi_in_device.push_back(new MIDI_IN_DEVICE());
		MIDIINCAPS device;
		midiInGetDevCaps(i, &device, sizeof(MIDIINCAPS));

		midi_in_device.back()->device_port_num = i;
		midi_in_device.back()->open = false;
		midi_in_device.back()->manufacturer_id = device.wMid;
		midi_in_device.back()->product_id = device.wPid;
		midi_in_device.back()->driver_version = device.vDriverVersion;
		strcpy(midi_out_device.back()->name, device.szPname);
	}

	for (unsigned i=0; i<midi_out_device.size(); i++)
	{
		std::cout << "out " << midi_out_device[i]->device_port_num << ": " << midi_out_device[i]->name << "" << std::endl;
	}
	for (unsigned i=0; i<midi_in_device.size(); i++)
	{
		std::cout << "in " << midi_in_device[i]->device_port_num << ": " << midi_in_device[i]->name << "" << std::endl;
	}

	midi_initialized = true;
}



void uninstall_midi()
{
	if (!midi_initialized) return;

   // turn any MIDI notes currently playing:
   midiOutReset(current_midi_out_device_handler);

   // Remove any data in MIDI device and close the MIDI Output port
   midiOutClose(current_midi_out_device_handler);
}



bool open_midi_device(MIDI_OUT_DEVICE *dev)
{
	if (!midi_initialized) return false;
	if (!dev) return false;
	if (dev->open) return false;
	MIDIOUTCAPS device;
	midiOutGetDevCaps(dev->device_port_num, &device, sizeof(MIDIOUTCAPS));
	MMRESULT flag = midiOutOpen(&current_midi_out_device_handler, dev->device_port_num, 0, 0, CALLBACK_NULL);
	if (flag != MMSYSERR_NOERROR) return false;
	dev->open = true;
	return true;
}



typedef union
{
	unsigned long word;
	unsigned char data[4];
} midi_message;





bool midi_patch_change(unsigned char channel, unsigned char patch_num)
{
	midi_message message;
	message.data[0] = PATCH_CHANGE;  // MIDI command byte
	message.data[1] = patch_num;    // MIDI first data byte
	message.data[2] = 0;   // MIDI second data byte
	message.data[3] = 0;     // Unused parameter
	
	MMRESULT flag = midiOutShortMsg(current_midi_out_device_handler, message.word);
    if (flag != MMSYSERR_NOERROR)
	{
		std::cout << "midi_patch_change(): MIDI output is not open." << std::endl;
		return false;
    }
	return true;
}





bool midi_note_on(unsigned char channel, unsigned char pitch, unsigned char velocity)
	// max velocity of 127
{
	midi_message message;
	message.data[0] = NOTE_ON;  // MIDI command byte
	message.data[1] = pitch;    // MIDI first data byte
	message.data[2] = velocity;   // MIDI second data byte (0-127)
	message.data[3] = 0;     // Unused parameter
	
	MMRESULT flag = midiOutShortMsg(current_midi_out_device_handler, message.word);
    if (flag != MMSYSERR_NOERROR)
	{
		std::cout << "note_on(): MIDI output is not open." << std::endl;
		return false;
    }
	return true;
}



bool midi_note_off(unsigned char channel, unsigned char pitch)
{
	midi_message message;
	message.data[0] = NOTE_ON;  // MIDI command byte
	message.data[1] = pitch;    // MIDI first data byte
	message.data[2] = 0;   // MIDI second data byte
	message.data[3] = 0;     // Unused parameter
	
	MMRESULT flag = midiOutShortMsg(current_midi_out_device_handler, message.word);
    if (flag != MMSYSERR_NOERROR)
	{
		std::cout << "note_off(): MIDI output is not open." << std::endl;
		return false;
    }
	return true;
}




void midi_all_notes_off()
{
	midiOutReset(current_midi_out_device_handler);
}








// below is untested

typedef union
{
	unsigned long word;
	unsigned char data[8];
} midi_sysex_message;




#include <sstream>

std::string __get_midiOutPrepareHeader_error_message(UINT err)
{
	switch (err)
	{
	case MIDIERR_NOTREADY: return "MIDIERR_NOTREADY"; break;
	case MIDIERR_UNPREPARED : return "MIDIERR_UNPREPARED"; break;
	case MMSYSERR_INVALHANDLE: return "MMSYSERR_INVALHANDLE"; break;
	case MMSYSERR_INVALPARAM: return "MIDIERR_NOTREADY"; break;
	default: break;
	}

	std::stringstream ss;
	ss << "(unknown error code " << err << ")";
	return ss.str();
}

bool midi_sysex_send_message(char device_id, char command_format, char command, char data)
{
	if (device_id == 0xF7
	 || command_format == 0xF7
	 || command == 0xF7
	 || data == 0xF7
	 )
	{
		std::cout
			<< "[" << __FILE__ << " : " << __FUNCTION__ << "] end message byte (0xF7) within the message. Not sending.]"
			<< std::endl;
		return false;
	}







	// help here:
	// http://msdn.microsoft.com/en-us/library/windows/desktop/dd798474%28v=vs.85%29.aspx
	// and here:
	// http://web.tiscalinet.it/giordy/midi-tech/lowmidi.htm


	MIDIHDR header;
	//char sysEx[] = {0xF0, 0x7F, 0x7F, 0x04, 0x01, 0x7F, 0x7F, 0xF7};  //< WAS, but this caused a narrowing error
	//unsigned char sysEx[] = {0xF0, 0x7F, 0x7F, 0x04, 0x01, 0x7F, 0x7F, 0xF7};

	/* Store pointer in MIDIHDR */
   // header.lpData = (LPBYTE)&sysEx[0];

    /* Store its size in the MIDIHDR */
    //header.dwBufferLength = sizeof(sysEx);

    /* Flags must be set to 0 */
    //header.dwFlags = 0;

	UINT err = midiOutPrepareHeader(current_midi_out_device_handler, &header, sizeof(MIDIHDR));
	if (err)
	{
		std::cout
			<< "[" << __FILE__ << " : " << __FUNCTION__ << "] could not prepare header for the midi message."
			<< " -- " << __get_midiOutPrepareHeader_error_message(err) << std::endl;
		return false;
	}






	midi_sysex_message message;
	message.data[0] = SYSTEM_MESSAGE;	// MIDI command byte
	message.data[1] = 0x7F;				// MIDI start message byte
	message.data[2] = device_id;
	message.data[3] = 0x02;
	message.data[4] = command_format;
	message.data[5] = command;
	message.data[6] = data;
	message.data[7] = 0xF7;				// MIDI end message byte

	// ok, this function needs to check that the correct paramaters are being sent out.
	// right now, it's just a complete guess!  the NULL param should be something else
	MMRESULT flag = midiOutLongMsg(current_midi_out_device_handler, &header, message.word);
    if (flag != MMSYSERR_NOERROR)
	{
		std::cout << __FUNCTION__ << ": MIDI output is not open." << std::endl;
		return false;
    }

	// yuck, a busy wait
    while (midiOutUnprepareHeader(current_midi_out_device_handler, &header, sizeof(MIDIHDR)) == MIDIERR_STILLPLAYING)
    {
        /* Should put a delay in here rather than a busy-wait */		    
    }

	return true;
}



/*

// example program

void main()
{
		init_midi();

		for (unsigned i=0; i<midi_out_device.size(); i++)
			std::cout << midi_out_device[i]->device_port_num << ": " << midi_out_device[i]->name << std::endl;

		if (!midi_out_device.empty()) { open_midi_device(midi_out_device[0]); }

		midi_note_on(0, 60, 127);
}

*/