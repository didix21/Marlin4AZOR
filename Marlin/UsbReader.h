/**
 * This file is exclusive and only has to be used if you have an AZOR 1.0 
 * Created by: didix21
 */
#ifndef USBREADER_H
#define USBREADER_H

#ifdef USBSUPPORT


#include "Usb_Stick.h"

#define FILENAME_LENGTH 13

enum LsAction {LS_SerialPrint, LS_Count, LS_GetFilename};



class UsbReader {

  public:
    UsbReader(); //Constructor
    /**
     * Main Class Functions
     */
    bool chdir(const char* relpath);
    bool eof();   
    bool isSomeDeviceConnected (USB *usbDevice);

    float getFractionPrinted();

    void checkAutoStart(bool x);
    void closeFile(bool store_location=false);
    void getAbsFilename(char *t);
    void getFileName(uint16_t nr, const char* const mastch = NULL);
    void getStatus(); 
    void initUsb(); // Inits the USB Stick
    void ls(print_t* pr, const char *path);
   
    
    void openFile(char* name, bool read, bool replace_current=true); // Open a file 
    void openLogFile(char* name);
    void pauseUSBPrint();
    void printingHasFinished();
    void release();
    void removeFile(char* name);
    void setroot();
    void startFileprint();
    void write_command(char *buf);

    FORCE_INLINE bool isFileOpen() {return file.isOpen(); }
    FORCE_INLINE int16_t get() {usbpos = file.curPosition(); return (int16_t)file.read();}
    FORCE_INLINE int freeRam() {return FreeRam();}
    FORCE_INLINE uint8_t percentDone() {return (isFileOpen() && filesize) ? usbpos / ((filesize + 99) / 100) : 0; }
    FORCE_INLINE void setIndex(long index) {usbpos = index; file.seekSet(index);}
    

  public:
    bool logging, filenameIsDir, saving, usbOK, usbprinting;
    char filename[FILENAME_LENGTH];
    int autostart_index;
  private:  
    /**
     * DEFINES
     */
    #define USB_PROCEDURE_DEPTH   1
    #define FILENAME_LENGTH       13
    #define MAX_DIR_DEPTH         10 // Maximum folder depth
    #define MAXPATHNAMELENGTH     (FILENAME_LENGTH*MAX_DIR_DEPTH + MAX_DIR_DEPTH + 1)
    
    /** 
     * USB Classes  
     */
    USB usb;
    FatFile file, root, *curDir, workDir, workDirParents[MAX_DIR_DEPTH];
    FatFile fatFile;
    BulkOnly bulk;
    UsbFat key;
    ios iosFile;

    /**
     * USB Classes Created by didix21
     */
    void lsDive(const char *prepend, FatFile parent, const char * const match=NULL);
    
    /** 
     * USB Variables  
     */  
    bool autostart_stilltocheck; //the sd start is delayed, because otherwise the serial cannot answer fast enought to make contact with the hostsoftware.
   
    char filenames[USB_PROCEDURE_DEPTH][MAXPATHNAMELENGTH];

    LsAction lsAction;
    
    unsigned long next_autostart_ms;
    size_t namesize;
    
    uint8_t file_subcall_ctr; 
    uint8_t usbState, usbLastSate;

    uint16_t workDirDepth;
    uint16_t nrFiles;

    uint32_t filesize;
    uint32_t filespos[USB_PROCEDURE_DEPTH];
    uint32_t usbpos;
        
};
  extern UsbReader usbStick;

  #define IS_USB_PRINTING (usbStick.usbprinting)
 


#endif //USBSUPPORT

#endif //__USBREADER_H

