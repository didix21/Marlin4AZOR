# Marlin4AZOR 3D Printer Firmware
======================================
![version-image](https://badge.fury.io/gh/didix21%2FMarlin4AZOR.svg)
<img align="right" src="Documentation/LOGO/marlin_logo.png" />
_______
This Repository contains a Marlin **BETA** firmware modified to be mainly used with [AZOR 1.0]() boards. The main characteristic of this Marlin is that is ready to use with 32-bits MCU like **ATSAM3X8E**. The MCU which is used with [Arduino DUE](https://www.arduino.cc/en/Main/ArduinoBoardDue). 

## About it

Marlin4AZOR is a opensource beta firmware to be used exclusively with [AZOR 1.0](https://github.com/didix21/AZOR) electronic boards. I strongly recoommend do not use it with any other board because important modifications have been done to make it work with [SAM3X8E MCU](http://www.atmel.com/devices/ATSAM3X8E.aspx).

This project is based on work done by [Wurstnase](https://github.com/Wurstnase) with [Marlin4Due](https://github.com/Wurstnase/Marlin4Due). 

Marlin4AZOR has been created in collaboration with [JFonS](https://github.com/JFonS).

## Release

"The stable release is AZOR 1.0 that you will find it in Release branch"(Not Yet).

## Recent Changes

- Communicate with the PC and the PTS-Panel via serial communication at the same time. 

## Main Features

The main features of this marlin are:

- Support for 32-bits MCU.
- Implemented M408: Report JSON-style response.
- Support for USB Stick.
- Support for PTS-Panel.

## Requirements

**IMPORTANT**
To compile this project it will be necessary to use [Arduino](https://www.arduino.cc) version 1.6.0 or later.
To compile the program will be needed the following libraries:
- **UsbFat**
  - Download or clone from here: https://github.com/didix21/UsbFat
  - The **UsbFat** has been created by [greiman](https://github.com/greiman). if you want more information about the library I suggest to visit the [original repository](https://github.com/greiman/UsbFat).

- **Usb_Host_Shield_2.0**
  - Download or clone from here: https://github.com/didix21/USB_Host_Shield_2.0.
  - The original **USB_Host_Shield_2.0** can be found [HERE](https://github.com/felis/USB_Host_Shield_2.0). ** IMPORTANT ** If you want to use it for AZOR download from the first link.

if you know how git works I recommend to clone both of them. Possible modifications will be needed in future.

## About AZOR 1.0

AZOR 1.0 is an open board created by [Presolid S.L](http://presolid.com/es/). You can find more information about it [HERE]().

- [Bulding Files]()

## How to upload Marlin4AZOR firmware to AZOR 1.0

This section contains all the information to compile and upload the program to AZOR 1.0.
 - Install the last version of [Arduino IDE](https://www.arduino.cc/en/Main/Software).
 - Download or clone [UsbFat]() and [USB_Host_Shield_2.0]() libraries.
 - if they have been download unzipid. 
 - Place them at:
    - Documents/Arduino/libraries 
 - Once it has been installed, open the program and then open the marlin with it. 
 - Now it has to select the board, to do that go to:
    - Tools -> Board
    - Select Arduino DUE (Native Port).
 - Select the COM:
    - Tools -> Port
    - And the corresponding COM. 
 - Compile the Marlin and upload it.

## License

Marlin is published under the [GPL license](/Documentation/License/GPL.md).



