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
    void getStatus(); 
    void initUsb(); // Inits the USB Stick
    void openFile(char* name,bool read, bool replace_current=true); // Open a file 
    void pauseUSBPrint();
    void release();
    void startFileprint();
    
    

  public:
    bool usbOK, usbprinting;

  private:
    /** 
     * USB Variables  
     */
    USB usb;
    File file, root, *curDir;
    BulkOnly bulk;
    UsbFat key;

    uint8_t usbState, usbLastSate;
    uint32_t filesize;
    size_t namesize;

    
    
};



#endif //USBSUPPORT

#endif //__USBREADER_H

