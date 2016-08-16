#include "Marlin.h"
#include "UsbReader.h"

#ifdef USBSUPPORT

UsbReader::UsbReader():bulk(&usb),key(&bulk) { // Quick Initialitzation of constructors BulkOnly and UsbFat
  filesize = 0;
  saving = false;
  usbpos = 0;
  usbprinting = false;
  usbOK = false;
  usbState = 0;
  usbLastSate = 0;
}

bool UsbReader::isSomeDeviceConnected (USB *usbDevice) { // Is Some device Connected
  static bool deviceConnected = false;
  usbState = usbDevice->getUsbTaskState();
  if(usbState != usbLastSate) {
    usbLastSate = usbState;
    switch(usbState) {
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

 void UsbReader::closeFile(bool store_location) {
  file.sync();
  file.close();
  saving = false;
  if (store_location) {
    //future: store printer state, filename and position for continuing a stopped print
    // so one can unplug the printer and continue printing the next day.
  }
 }
 
 void UsbReader::getStatus() {
  if(usbOK) {
    SERIAL_PROTOCOLPGM(MSG_USB_PRINTING_BYTE);
    SERIAL_PROTOCOL(usbpos);
    SERIAL_PROTOCOLCHAR('/');
    SERIAL_PROTOCOLLN(filesize);
  }
  else {
    SERIAL_PROTOCOLLNPGM(MSG_USB_NOT_PRINTING);   
  }
}

void UsbReader::initUsb() { //Inits USB
  usbOK = false;
  if(!isSomeDeviceConnected(&usb)) {
     SERIAL_ECHOLNPGM(MSG_USB_INIT_FAIL);
  }
  else if(!key.begin()) { 
    SERIAL_ECHOLNPGM(MSG_USB_VOL_INIT_FAIL);
  }
  else {
     usbOK = true;
     SERIAL_ECHOLNPGM(MSG_USB_STICK_OK);
  }      
}

void UsbReader::openFile(char* name, bool read, bool replace_current/*=true*/) {
  if(!usbOK) return; //Not initialized? Then return
  curDir = &root;
  char *fname = name;
  char *dirname_start , *dirname_end;
    if(file.open(curDir, fname, O_READ)){
      filesize = file.fileSize();
      SERIAL_PROTOCOLPGM(MSG_USB_FILE_OPENED);
      SERIAL_PROTOCOL(fname);
      SERIAL_PROTOCOLPGM(MSG_USB_SIZE);
      SERIAL_PROTOCOLLN(filesize);
  
      SERIAL_PROTOCOLLNPGM(MSG_USB_FILE_SELECTED);
      file.getName(fname, namesize);
      //getfilename(0,fname);
    }
    else {
      SERIAL_PROTOCOLPGM(MSG_USB_OPEN_FILE_FAIL);
      SERIAL_PROTOCOL(fname);
      SERIAL_PROTOCOLPGM(".\n");
    }
}

void UsbReader::release() {
  usbprinting = false;
  usbOK = false;
}

void UsbReader::removeFile(char *name) {
  if(!usbOK) return;
  file.close();
  usbprinting = false;

  curDir = &root;
  char *fname = name;

  file.remove(curDir, fname);
  
}

void UsbReader::startFileprint() {
  if(usbOK){
    usbprinting = true;
  }
}

void UsbReader::pauseUSBPrint() {
  if(usbprinting) usbprinting = false;
}

#endif //USBSUPPORT
