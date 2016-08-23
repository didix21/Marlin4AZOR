
/* This File Initialize all the variable and libraries to use
 * a USB Stick
 */
 // Include All necessary files
 #include <SPI.h>
 #include <UsbFat.h>
 #include <masstorage.h>

 //Create USB host object
 USB usbStick
 BulkOnly bulk(&usbStick)

 //File system
 UsbFat key(&bulk);

 // Create a object File
 File file;

 //
 class usbStickStatus
 
