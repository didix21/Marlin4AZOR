
/* This File Initialize all the variable and libraries to use
 * a USB Stick
 */
 // Include All necessary files
 #include <SPI.h>
 #include <UsbFat.h>
 #include <masstorage.h>

#ifdef ARDUINO_ARCH_AVR
//------------------------------------------------------------------------------
/**
 * SPI init rate for SD initialization commands. Must be 5 (F_CPU/64)
 * or 6 (F_CPU/128).
 */
#define SPI_SD_INIT_RATE 5

#elif defined(ARDUINO_ARCH_SAM)

#define SPI_SD_INIT_RATE SPI_INIT_SPEED

#endif
 
/** Number of UTF-16 characters per entry */
#define FILENAME_LENGTH 13

/**
 * Defines for long (vfat) filenames
 */
/** Number of VFAT entries used. Every entry has 13 UTF-16 characters */
#define MAX_VFAT_ENTRIES (2)
/** Total size of the buffer used to store the long filenames */
#define LONG_FILENAME_LENGTH (FILENAME_LENGTH*MAX_VFAT_ENTRIES+1)
