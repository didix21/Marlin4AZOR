/****************************************************************************************
* 
* Azor_1.0 pin assignment
* 
****************************************************************************************/
#define INVERTED_HEATER_PINS 
#define INVERTED_MOSFET_CHANNELS // It is necessary for AZOR electronics, the mosfets works inverted respect RAMPS
// Changed
#define X_STEP_PIN         14
#define X_DIR_PIN          15
#define X_ENABLE_PIN       29
#define X_MIN_PIN          11
#define X_MAX_PIN          -1
// Changed
#define Y_STEP_PIN         25
#define Y_DIR_PIN          26
#define Y_ENABLE_PIN       27
#define Y_MIN_PIN          28
#define Y_MAX_PIN          -1
// Changed
#define Z_STEP_PIN         5
#define Z_DIR_PIN          4
#define Z_ENABLE_PORT      PIOC
#define Z_ENABLE_MASK      1<<27
#define Z_ENABLE_PIN       1380 //SAM3X8E={Pin=138,Port=PC5,Register=0x08000000} 
#define Z_MIN_PIN          60 /*A6=60*/ //84 of SAM3X8E, 6 analog pin of Arduino Due
#define Z_MIN_PIN_AX       A6 
#define Z_MAX_PIN          -1
#define Z_PROBE_PIN        -1
// Changed
#define Y2_STEP_PIN        -1
#define Y2_DIR_PIN         -1
#define Y2_ENABLE_PIN      -1
// Changed
#undef Z2_STEP_PIN         -1
#undef Z2_DIR_PIN          -1
#undef Z2_ENABLE_PIN       -1
// Changed
#define Z2_STEP_PIN        -1
#define Z2_DIR_PIN         -1
#define Z2_ENABLE_PIN      -1
// Changed
#define E0_STEP_PIN        230 //Arduino_Due{PIN=A0} SAM3X8E={Pin=23,Port=PA0,Register=0x0}
#define E0_STEP_PORT       PIOA
#define E0_STEP_MASK       1<<0
#define E0_DIR_PIN         240 //SAM3X8E={Pin=24,Port=PA0,Register=0x0}
#define E0_DIR_PORT        PIOA
#define E0_DIR_MASK        1<<1
#define E0_ENABLE_PIN      250 //SAM3X8E={Pin=25,Port=PA5,Register=0x00000020} 
#define E0_ENABLE_PORT     PIOA
#define E0_ENABLE_MASK     1<<5

#define E1_STEP_PIN        36
#define E1_DIR_PIN         34
#define E1_ENABLE_PIN      30

#define SDPOWER            -1
#define SDSS               -1
#define LED_PIN            -1

#if MB(RAMPS_13_EEB) && defined(FILAMENT_SENSOR)  // FMM added for Filament Extruder
  // define analog pin for the filament width sensor input
  // Use the RAMPS 1.4 Analog input 5 on the AUX2 connector
  #define FILWIDTH_PIN        5
#endif

#ifdef Z_PROBE_ENDSTOP
  // Define a pin to use as the signal pin on Arduino for the Z_PROBE endstop.
  #define Z_PROBE_PIN 32
#endif

#ifdef FILAMENT_RUNOUT_SENSOR
  // define digital pin 4 for the filament runout sensor. Use the RAMPS 1.4 digital input 4 on the servos connector
  #define FILRUNOUT_PIN        4
#endif

#define FAN_PIN            34 //FAN_0 for AZOR

#define PS_ON_PIN          12 

#if defined(REPRAP_DISCOUNT_SMART_CONTROLLER) || defined(G3D_PANEL)
  #define KILL_PIN           41
#else
  #define KILL_PIN           -1
#endif

//Changed Heaters
#define HEATER_0_PIN       40 // EXTRUDER 1 //Done
#define HEATER_1_PIN       38 // EXTRUDER 2
#define HEATER_2_PIN       -1

#define TEMP_0_PIN          4   // ANALOG NUMBERING
#define TEMP_1_PIN          0   // ANALOG NUMBERING
#define TEMP_2_PIN         -1   // ANALOG NUMBERING

#define HEATER_BED_PIN     6    // BED

#define TEMP_BED_PIN       5   // ANALOG NUMBERING

//#ifdef NUM_SERVOS
//  #define SERVO0_PIN         11
//  #if NUM_SERVOS > 1
//    #define SERVO1_PIN        6
//    #if NUM_SERVOS > 2
//      #define SERVO2_PIN      5
//      #if NUM_SERVOS > 3
//        #define SERVO3_PIN    4
//      #endif
//    #endif
//  #endif
//#endif

#ifdef ULTRA_LCD

  #ifdef NEWPANEL
    #ifdef PANEL_ONE
      #define LCD_PINS_RS 40
      #define LCD_PINS_ENABLE 42
      #define LCD_PINS_D4 65
      #define LCD_PINS_D5 66
      #define LCD_PINS_D6 44
      #define LCD_PINS_D7 64
    #else
      #define LCD_PINS_RS 16
      #define LCD_PINS_ENABLE 17
      #define LCD_PINS_D4 23
      #define LCD_PINS_D5 25
      #define LCD_PINS_D6 27
      #define LCD_PINS_D7 29
    #endif


    #ifdef REPRAP_DISCOUNT_SMART_CONTROLLER
      #define BEEPER 37

      #define BTN_EN1 31
      #define BTN_EN2 33
      #define BTN_ENC 35

      #define SDCARDDETECT 49
          
      #elif defined(SSD1306_OLED_I2C_CONTROLLER)
        #define BTN_EN1 31
        #define BTN_EN2 33
        #define BTN_ENC 35
        #define BEEPER -1
        #define LCD_SDSS 49
        #define SDCARDDETECT 37
        #define KILL_PIN 39
      
     #elif defined(LCD_I2C_PANELOLU2)
      #define BTN_EN1 47  // reverse if the encoder turns the wrong way.
      #define BTN_EN2 43
      #define BTN_ENC 32
      #define LCD_SDSS 53
      #define SDCARDDETECT -1
      #define KILL_PIN 41
    #elif defined(LCD_I2C_VIKI)
      #define BTN_EN1 22  // reverse if the encoder turns the wrong way.
      #define BTN_EN2 7
      #define BTN_ENC -1
      #define LCD_SDSS 53
      #define SDCARDDETECT 49
    #else
      // arduino pin which triggers an piezzo beeper
      #define BEEPER 33  // Beeper on AUX-4

      // buttons are directly attached using AUX-2
      #ifdef REPRAPWORLD_KEYPAD
        #define BTN_EN1 64 // encoder
        #define BTN_EN2 59 // encoder
        #define BTN_ENC 63 // enter button
        #define SHIFT_OUT 40 // shift register
        #define SHIFT_CLK 44 // shift register
        #define SHIFT_LD 42 // shift register
      #elif defined(PANEL_ONE)
        #define BTN_EN1 59 // AUX2 PIN 3
        #define BTN_EN2 63 // AUX2 PIN 4
        #define BTN_ENC 49 // AUX3 PIN 7
      #else
        #define BTN_EN1 37
        #define BTN_EN2 35
        #define BTN_ENC 31  // the click
      #endif

      #ifdef G3D_PANEL
        #define SDCARDDETECT 49
      #else
        #define SDCARDDETECT -1  // Ramps does not use this port
      #endif

    #endif

  #else // Old-style panel with shift register
    // Arduino pin witch triggers an piezzo beeper
    #define BEEPER 33   // No Beeper added

    // Buttons are attached to a shift register
    // Not wired yet
    // #define SHIFT_CLK 38
    // #define SHIFT_LD 42
    // #define SHIFT_OUT 40
    // #define SHIFT_EN 17

    #define LCD_PINS_RS 16
    #define LCD_PINS_ENABLE 17
    #define LCD_PINS_D4 23
    #define LCD_PINS_D5 25
    #define LCD_PINS_D6 27
    #define LCD_PINS_D7 29
  #endif
#endif // ULTRA_LCD

// SPI for Max6675 Thermocouple
#ifndef SDSUPPORT
  #define MAX6675_SS       66 // Do not use pin 53 if there is even the remote possibility of using Display/SD card
#else
  #define MAX6675_SS       66 // Do not use pin 49 as this is tied to the switch inside the SD card socket to detect if there is an SD card present
#endif

#ifndef SDSUPPORT
  // these pins are defined in the SD library if building with SD support
  #define SCK_PIN          52
  #define MISO_PIN         50
  #define MOSI_PIN         51
#endif
