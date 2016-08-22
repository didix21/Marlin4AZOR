#include "Marlin.h"
#include "UsbReader.h"
#include "temperature.h"
#include "language.h"
#include "stepper.h"

#ifdef USBSUPPORT

UsbReader::UsbReader():bulk(&usb),key(&bulk) { // Quick Initialitzation of constructors BulkOnly and UsbFat
  autostart_index = 0;
  autostart_stilltocheck = true; //The USB start is delayed, because otherwise the serial cannot answer fast enough to make contact with the host software.
  logging = false;
  file_subcall_ctr = 0;
  filesize = 0;
  saving = false;
  usbpos = 0;
  usbprinting = false;
  usbOK = false;
  usbState = 0;
  usbLastSate = 0;
  
  next_autostart_ms = millis() + 5000;
}

bool UsbReader::eof() { //End of file
 return iosFile.eof();
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

float UsbReader::getFractionPrinted() {
  return usbpos/filesize*100;
}

void UsbReader::closeFile(bool store_location) {
  file.sync();
  file.close();
  saving = logging = false;
  if (store_location) {
    //future: store printer state, filename and position for continuing a stopped print
    // so one can unplug the printer and continue printing the next day.
  }
 }

void UsbReader::checkAutoStart (bool force) {
  if (!force && (!autostart_stilltocheck || next_autostart_ms < millis()))
   return;

  autostart_stilltocheck = false;

  if (!usbOK) {
    initUsb();
    if (!usbOK) return; // fail
  }
//
  char autoname[10];
  sprintf_P(autoname, PSTR("auto%i.g"), autostart_index);
  for (int8_t i = 0; i < (int8_t)strlen(autoname); i++) autoname[i] = tolower(autoname[i]);

  dir_t p;

  root.rewind();

  bool found = false;
  while (root.readDir(&p) > 0) {
    for (int8_t i = 0; i < (int8_t)strlen((char*)p.name); i++) p.name[i] = tolower(p.name[i]);
    if (p.name[9] != '~' && strncmp((char*)p.name, autoname, 5) == 0) {
      char cmd[4 + (FILENAME_LENGTH + 1) * MAX_DIR_DEPTH + 2];
      sprintf_P(cmd, PSTR("M23 %s"), autoname);
      enqueuecommand(cmd);
      enqueuecommands_P(PSTR("M24"));
      found = true;
    }
  }
  if (!found)
    autostart_index = -1;
  else
    autostart_index++;
}

void UsbReader::getAbsFilename(char *t){
//  uint8_t cnt = 0;
//  *t = '/'; t++; cnt++;
//  for (uint8_t i = 0; i < workDirDepth; i++) {
//    workDirParents[i].getFilename(t); //SDBaseFile.getfilename!
//    while(*t && cnt < MAXPATHNAMELENGTH) { t++; cnt++; } //crawl counter forward.
//  }
//  if (cnt < MAXPATHNAMELENGTH - FILENAME_LENGTH)
//    file.getFilename(t);
//  else
//    t[0] = 0;
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
  if(!usbOK) return; // Not initialized? Then return
  if(file.isOpen()) { // replacing current file by new file, or subfile call
    if(!replace_current) {
      if( file_subcall_ctr > USB_PROCEDURE_DEPTH - 1) {
        SERIAL_ERROR_START;
        SERIAL_ERRORPGM("trying to call sub-gcode files with too many levels. MAX level is:");
        SERIAL_ERRORLN(USB_PROCEDURE_DEPTH);
        kill(PSTR(MSG_KILLED));
        return;
      }

      SERIAL_ECHO_START;
      SERIAL_ECHOPGM("SUBROUTINE CALL target:\"");
      SERIAL_ECHO(name);
      SERIAL_ECHOPGM("\" PARENT:\"");

      //store current filename and position
      getAbsFilename(filenames[file_subcall_ctr]); // code not implemented yet

      SERIAL_ECHO(filenames[file_subcall_ctr]);
      SERIAL_ECHOPGM("\" pos");
      SERIAL_ECHOLN(usbpos);
      filespos[file_subcall_ctr] = usbpos;
      file_subcall_ctr++;
    }
    else {
      SERIAL_ECHO_START;
      SERIAL_ECHOPGM("Now doing file: ");
      SERIAL_ECHOLN(name);
    }
    file.close();
  }
  else { // opening fresh file
    file_subcall_ctr = 0; // resetting procedure depth in case user cancels print while in procedure
    SERIAL_ECHO_START;
    SERIAL_ECHOPGM("Now fresh file: ");
    SERIAL_ECHOLN(name);
  }
  
  usbprinting = false;
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
   }
   else {
     SERIAL_PROTOCOLPGM(MSG_USB_OPEN_FILE_FAIL);
     SERIAL_PROTOCOL(fname);
     SERIAL_PROTOCOLPGM(".\n");
   }
}

void UsbReader::openLogFile(char *name) {
  logging = true;
  openFile(name, false);
}

void UsbReader::pauseUSBPrint() {
  if(usbprinting) usbprinting = false;
}

void UsbReader::printingHasFinished() {
    st_synchronize();
  if (file_subcall_ctr > 0) { // Heading up to a parent file that called current as a procedure.
    file.close();
    file_subcall_ctr--;
    openFile(filenames[file_subcall_ctr], true, true);
    setIndex(filespos[file_subcall_ctr]);
    startFileprint();
  }
  else {
    file.close();
    usbprinting = false;
    if (USB_FINISHED_STEPPERRELEASE) {
      //finishAndDisableSteppers(); /* Commented by default */ 
      enqueuecommands_P(PSTR(USB_FINISHED_RELEASECOMMAND));
    }
    autotempShutdown();
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

void UsbReader::write_command(char *buf) {
  char* begin = buf;
  char* npos = 0;
  char* end = buf + strlen(buf) - 1;

  /* Instead of: file.writeError = false;
   *  use clearWriteError()
   */
  file.clearWriteError();
  if ((npos = strchr(buf, 'N')) != NULL) {
    begin = strchr(npos, ' ') + 1;
    end = strchr(npos, '*') - 1;
  }
  end[1] = '\r';
  end[2] = '\n';
  end[3] = '\0';
  file.write(begin);
  if(file.getWriteError()) {
    SERIAL_ERROR_START;
    SERIAL_ERRORLNPGM(MSG_USB_WRITE_TO_FILE);
  }
}


#endif //USBSUPPORT
