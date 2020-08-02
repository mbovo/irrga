
#include <ThreeWire.h>
#include <RtcDS1302.h>
#include "includes.h"

ThreeWire myWire(RTC_IO_PIN, RTC_SCLK_PIN, RTC_CE_PIN);
RtcDS1302<ThreeWire> Rtc(myWire);

char HumanDOW[7][4] = { "DOM","LUN", "MAR", "MER", "GIO", "VEN", "SAB"};

void setupRTC(){
  Serial.println("INIT RTC");
  Rtc.Begin();
  RtcDateTime compileTime = RtcDateTime(__DATE__,__TIME__);
  if (!Rtc.IsDateTimeValid()){
    Serial.println("Invalid time found, setting to compile time");
    Rtc.SetDateTime(compileTime);
  }
  if (Rtc.GetIsWriteProtected()){ 
    Rtc.SetIsWriteProtected(false);
    Serial.println("RTC was r/o setting r/w");
  }
  if (!Rtc.GetIsRunning()){ 
    Rtc.SetIsRunning(true);
    Serial.println("RTC was not running, start it");
  }
  RtcDateTime now = Rtc.GetDateTime();
  if ( now < compileTime ){
    Rtc.SetDateTime(compileTime);  
    Serial.println("RTC saved time was in the past, update it");
  }
}

void dateToStr(char *str, size_t size, const RtcDateTime &dt){
  snprintf(str,
           size,
           PSTR("%02u/%02u/%04u"),
           dt.Month(),
           dt.Day(),
           dt.Year());
}

void timeToStr(char *str, size_t size, const RtcDateTime &dt){
  snprintf(str,
           size,
          PSTR("%02u:%02u:%02u"),
           dt.Hour(),
           dt.Minute(),
           dt.Second());
}

void dateTimeToStr(char *str, size_t size, const RtcDateTime& dt){

  snprintf_P(str,
             size,
             PSTR("%02u/%02u/%04u %02u:%02u:%02u  %s"),
             dt.Day(),
             dt.Month(),
             dt.Year(),
             dt.Hour(),
             dt.Minute(),
             dt.Second(),
             HumanDOW[dt.DayOfWeek()]);
}

void serialPrintNow(){
  char *str = (char *)calloc(sizeof(char), 30);
  dateTimeToStr(str, 30, Rtc.GetDateTime());
  Serial.println(str);
  free(str);
}