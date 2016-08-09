#include "UsbReader.h"

#ifdef USBSUPPORT

UsbReader::UsbReader() {
  usbOK = false;
  usbState = 0;
  usbLastSate = 0;
}

bool UsbReader::isSomeDeviceConnected (USB *usbDevice) {
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

void UsbReader::initUsb(){
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
  
}



#endif //USBSUPPORT
