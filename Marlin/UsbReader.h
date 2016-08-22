/**
 * This file is exclusive and only has to be used if you have an AZOR 1.0 
 * Created by: didix21
 */
#ifndef USBREADER_H
#define USBREADER_H

#ifdef USBSUPPORT


#include "Usb_Stick.h"

class UsbReader {

  public:
    UsbReader(); //Constructor
    /**
     * Main Class Functions
     */
    bool eof();   
    bool isSomeDeviceConnected (USB *usbDevice);

    float getFractionPrinted();

    void checkAutoStart(bool x);
    void closeFile(bool store_location=false);
    void getAbsFilename(char *t);
    void getStatus(); 
    void initUsb(); // Inits the USB Stick
    void openFile(char* name, bool read, bool replace_current=true); // Open a file 
    void pauseUSBPrint();
    void printingHasFinished();
    void release();
    void removeFile(char* name);
    void startFileprint();

    FORCE_INLINE bool isFileOpen() {return file.isOpen(); }
    FORCE_INLINE int16_t get() {usbpos = file.curPosition(); return (int16_t)file.read();}
    FORCE_INLINE uint8_t percentDone() {return (isFileOpen() && filesize) ? usbpos / ((filesize + 99) / 100) : 0; }
    FORCE_INLINE void setIndex(long index) {usbpos = index; file.seekSet(index);}
    

  public:
    bool saving, usbOK, usbprinting;
    //char filename[FILENAME_LENGTH];
    int autostart_index;
  private:
    /** 
     * USB Classes  
     */
    USB usb;
    FatFile file, root, *curDir;
    FatFile fatFile;
    BulkOnly bulk;
    UsbFat key;
    ios iosFile;

    /**
     * DEFINES
     */
    #define USB_PROCEDURE_DEPTH   1
    #define FILENAME_LENGTH       13
    #define MAX_DIR_DEPTH         10 // Maximum folder depth
    #define MAXPATHNAMELENGTH     (FILENAME_LENGTH*MAX_DIR_DEPTH + MAX_DIR_DEPTH + 1)
    
    /** 
     * USB Variables  
     */  
    bool autostart_stilltocheck; //the sd start is delayed, because otherwise the serial cannot answer fast enought to make contact with the hostsoftware.
   
    char filenames[USB_PROCEDURE_DEPTH][MAXPATHNAMELENGTH];

    unsigned long next_autostart_ms;
    size_t namesize;
    
    uint8_t file_subcall_ctr; 
    uint8_t usbState, usbLastSate;

    uint32_t filesize;
    uint32_t filespos[USB_PROCEDURE_DEPTH];
    uint32_t usbpos;
        
};
  extern UsbReader usbStick;

  #define IS_USB_PRINTING (usbStick.usbprinting)



#endif //USBSUPPORT

#endif //__USBREADER_H

