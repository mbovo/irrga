
#include "includes.h"
#include "irriga.h"
#include "time.h"
#include "memory.h"
#include "commands.h"

void serialSetup()
{
  Serial.begin(9600);
  Serial.println("=== I R R I G A ===");
  debug("DEBUG ENABLED");
}

void loop()
{
  const RtcDateTime &dt = Rtc.GetDateTime();
  for (byte i = 0; i < ALARM_SIZE; i++)
  {
    if (alarms[i].enabled && alarms[i].dow == dt.DayOfWeek())
    {
      if (alarms[i].hour == dt.Hour() && alarms[i].min == dt.Minute() && config.running == 0)
      {
        Serial.println("Irrigation starts");
        irrigaStart();
        config.running = alarms[i].duration;
        config.prevMin = (byte)dt.Minute();
        Serial.print("Running for: ");
        Serial.println(config.running);
      }
    }
  }
  // Decrease min counter and set previous minute
  if (config.running > 0 && config.prevMin != dt.Minute())
  {
    config.running -= 1;
    config.prevMin = dt.Minute();
    Serial.print("Running for ");
    Serial.println(config.running);
    if (config.running == 0)
    {
      Serial.println("Irrigation stops");
      irrigaStop();
    }
  }
  // Wait for 1s but avoding locks
  for (byte k = 0; k < 20; k++)
  {
    delay(50);
  }
  irrigaReset();
}

void setup()
{
  serialSetup();
  setupRTC();
  initPresets();
  initRelays();
  // just in case, close the valves
  irrigaStop();
  // reset the outputs
  irrigaReset();
}

void serialEvent()
{
  char *buffer = (char *)calloc(26, sizeof(char));
  Serial.readBytes(buffer, 26);
  if (!parseSerialCommand(buffer))
  {
    Serial.print("???");
    Serial.println(buffer);
    Serial.println("Try: +h");
  }
  free(buffer);
}

void initRelays(){
  pinMode(REL_1_PIN, OUTPUT);
  pinMode(REL_2_PIN, OUTPUT);
  pinMode(REL_3_PIN, OUTPUT);
  pinMode(REL_4_PIN, OUTPUT);
  digitalWrite(REL_1_PIN, HIGH);
  digitalWrite(REL_2_PIN, HIGH);
  digitalWrite(REL_3_PIN, HIGH);
  digitalWrite(REL_4_PIN, HIGH);
  delay(50);
  digitalWrite(REL_1_PIN, LOW);
  digitalWrite(REL_2_PIN, LOW);
  digitalWrite(REL_3_PIN, LOW);
  digitalWrite(REL_4_PIN, LOW);
}