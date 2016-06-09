



#include <allegro_flare/dmx.h>




#define DMX_DATA_LENGTH 513

// 513 values would create a maximum-sized packet (including the start code)
// This is enough data for a full frame DMX message (512 channels)
// http://en.wikipedia.org/wiki/DMX512#Protocol




static unsigned char dmxData_[DMX_DATA_LENGTH];




static void *_current_dmx_device = 0; //null




void dmx_out(int channel, char data, const DMXDevice *device)
{
   //send_data_to_channel(
}




