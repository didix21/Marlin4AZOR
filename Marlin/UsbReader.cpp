#include "Marlin.h"
#include "UsbReader.h"

#ifdef USBSUPPORT

UsbReader::UsbReader():bulk(&usb),key(&bulk) { // Quick Initialitzation of constructors BulkOnly and UsbFat
  usbOK = false;
  usbState = 0;
  usbLastSate = 0;
}

bool UsbReader::isSomeDeviceConnected (USB *usbDevice) { // Is Some device Connected
  static bool deviceConnected = false;
  usbState = usbDevice->getUsbTaskState();
  if(usbState != usbLastSate){
    usbLastSate = usbState;
    switch(usbState){
      case(USB_DETACHED_SUBSTATE_WAIT_FOR_DEVICE):
        deviceConnected = false;
      break;
      case(USB_STATE_RUNNING):
        deviceConnected = true;
      break;
    }   
  }
  return deviceConnected;
 }

void UsbReader::initUsb(){ //Inits USB
  usbOK = false;
  if(!isSomeDeviceConnected(&usb)){
     SERIAL_ECHOLNPGM(MSG_USB_INIT_FAIL);
  }
  else if(!key.begin()){ 
    SERIAL_ECHOLNPGM(MSG_USB_VOL_INIT_FAIL);
  }
  else{
     usbOK = true;
     SERIAL_ECHOLNPGM(MSG_USB_STICK_OK);
  }     
}

void UsbReader::openFile(char* name, bool read, bool replace_current/*=true*/){
  if(!usbOK) return; //Not initialized? Then return
  char *dirname_start , *dirname_end;

  if(name[0] == '/') {
    dirname_start = &name[1];
    while (dirname_start > 0) {
      dirname_end = strchr(dirname_start, '/');
      if(dirname_end > 0 && dirname_end > dirname_start) {
        char subdirname[FILENAME_LENGTH];
        strncpy(subdirname, dirname_start, dirname_end - dirname_start);
        subdirname[dirname_end - dirname_start] = 0;
        SERIAL_ECHOLN(subdirname);     

       // curDir = &myDir;
        dirname_start = dirname_end + 1;
      }
      else {
        fname = dirname_start;
      }
    }
  }
  
}



#endif //USBSUPPORT
