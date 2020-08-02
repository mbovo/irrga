#define DEBUG 1

// RELAY PINS
#define REL_1_PIN       4
#define REL_2_PIN       7
#define REL_3_PIN       8
#define REL_4_PIN       12

#define RTC_IO_PIN      A1
#define RTC_SCLK_PIN    A0
#define RTC_CE_PIN      A2

#define MAGIC_NUMBER 0xAE
#define MEMORY_BASE_ADDRESS 0x00
#define MEMORY_EVENT_BASE_ADDRESS  0x40

#define ALARM_SIZE  16

#define countof(a) (sizeof(a) / sizeof(a[0]))

#ifdef DEBUG
  #define debug(x)  Serial.println(x)
#else
  #define debug(x) ;
#endif

//// LCD Display pins
//#define LCD_BACKLIT_PIN 10
//#define LCD_RS_PIN      11 // 8
//#define LCD_EN_PIN      13 // 9
//#define LCD_D4_PIN      2 // 4
//#define LCD_D5_PIN      3 // 5
//#define LCD_D6_PIN      5 // 6
//#define LCD_D7_PIN      6 // 7

//// Vcc Tension on analog pin
//#define CMD_Vc_0 30
//#define CMD_Vc_1 150
//#define CMD_Vc_2 360
//#define CMD_Vc_3 535
//#define CMD_Vc_4 760
//int adc_key_val[5] = {CMD_Vc_0, CMD_Vc_1, CMD_Vc_2, CMD_Vc_3, CMD_Vc_4};
//
//// Internal use only: mapping voltage to integers
//#define KEY_RIGHT  0
//#define KEY_UP     1
//#define KEY_DOWN   2
//#define KEY_LEFT   3
//#define KEY_SEL    4
