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
    void closeFile(bool store_location=false);
    void getStatus(); 
    void initUsb(); // Inits the USB Stick
    void openFile(char* name, bool read, bool replace_current=true); // Open a file 
    void pauseUSBPrint();
    void release();
    void removeFile(char* name);
    void startFileprint();
    
    

  public:
    bool saving, usbOK, usbprinting;

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
    uint32_t usbpos;
    size_t namesize;

    
    
};



#endif //USBSUPPORT

#endif //__USBREADER_H

