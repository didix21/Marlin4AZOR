#ifndef USBREADER_H
#define USBREADER_H

#ifdef USBSUPPORT


#include "Usb_Stick.h"
#include "language.h"

class UsbReader {

  public:
    UsbReader(); //Constructor
    /**
     * Main Class Function
     */
    bool isSomeDeviceConnected (USB *usbDevice);
    void initUsb(); // Inits the USB Stick
    void openFile(char* name,bool read, bool replace_current=true); // Open a file 

  public:
    bool usbOK;

  private:
    /** 
     * USB Variables  
     */
    USB usb;
    File file;
    BulkOnly bulk;
    UsbFat key;

    uint8_t usbState, usbLastSate;

    
    
};



#endif //USBSUPPORT

#endif //__USBREADER_H

