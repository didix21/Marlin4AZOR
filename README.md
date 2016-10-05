# Marlin4AZOR 3D Printer Firmware
<img align="right" src="Documentation/LOGO/marlin_logo.png" />

This Repository contains the Marlin firmware modified to be used with [AZOR 1.0](https://github.com/didix21/AZOR) boards.  

## About it

Marlin4AZOR is a opensource beta firmware to be used exclusively with [AZOR 1.0](https://github.com/didix21/AZOR) electronic boards. I suggest don't use it with any other board because important modifications have been done to make it work with [SAM3X8E MCU](http://www.atmel.com/devices/ATSAM3X8E.aspx).

This project is based on work done by [Wurstnase](https://github.com/Wurstnase) with [Marlin4Due](https://github.com/Wurstnase/Marlin4Due). 

Marlin4AZOR has been created in collaboration with [JFonS](https://github.com/JFonS).

## Release

The stable release is AZOR 1.0 that you will find in master branch.

## Recent Changes

No recent changes done.

## Main Features

The main features of this marlin are:

- Support for 32-bits MCU.
- Implemented M408: Report JSON-style response.
- Support for USB Stick.
- Support for PTS-Panel.

## Requirements

To compile this project it will be necessary to use [Arduino](https://www.arduino.cc) version 1.6.0 or later.
In future will be needed the following libraries:
- **UsbFat**
  - You can find it here: https://github.com/greiman/UsbFat

- **Usb_Host_Shield_2.0**
  - This library is included in UsbFat but it is a modified version of Usb_Host_Shield_2.0, in case that you want the latest version you can find it in the following link: https://github.com/felis/USB_Host_Shield_2.0
  
## License

Marlin is published under the [GPL license](/Documentation/License/GPL.md).



