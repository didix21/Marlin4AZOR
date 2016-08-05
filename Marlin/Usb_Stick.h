
/* This File Initialize all the variable and libraries to use
 * a USB Stick
 */
 // Include All necessary files
 #include <SPI.h>
 #include <UsbFat.h>
 #include <masstorage.h>

 //Create USB host object
// USB usbStick;
// 
// BulkOnly bulk(&usbStick);
//
// //File system
// UsbFat key(&bulk);
//
// // Create a object File
// File file;
//
// /* Variables */
// uint8_t usbState;
// uint8_t usbLastSate;
//
// 
// 
// //Function to know the status of USB
// bool isSomeDeviceConnected (USB *usbDevice) {
//  static bool deviceConnected = false;
//  usbState = usbDevice->getUsbTaskState();
//  if(usbState != usbLastSate){
//    usbLastSate = usbState;
//    switch(usbState){
//      case(USB_DETACHED_SUBSTATE_WAIT_FOR_DEVICE):
//        deviceConnected = false;
//      break;
//      case(USB_STATE_RUNNING):
//        deviceConnected = true;
//      break;
//    }
//    
//  }
//  return deviceConnected;
// }
// 
 
