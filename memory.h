
#include <EEPROM.h>
#include <avr/eeprom.h>

void loadConf();
void storeConf();
void loadAlarms();
void storeAlarms();
void initPresets();
void initMemory();
void saveMemory();

typedef struct alarm_s
{
  byte hour;
  byte min;
  byte dow;
  byte duration;
  bool enabled;
} alarm_t;

typedef struct config_s {
  byte running;
  byte prevMin;
} config_t;

alarm_t alarms[ALARM_SIZE];
config_t config;

void storeConf(){
  debug("+DBG   storeConf()");
  eeprom_busy_wait();
  
  uint8_t addr = MEMORY_BASE_ADDRESS;
  EEPROM.write(addr++, MAGIC_NUMBER);
  eeprom_update_block(&config, (void *)addr, sizeof(config_t));
  
  eeprom_busy_wait();
}

void loadConf(){
  debug("+DBG   loadConf()");
  eeprom_busy_wait();

  uint8_t addr = MEMORY_BASE_ADDRESS + 1;

  eeprom_read_block(&config, (void *)addr, sizeof(config_t));

  eeprom_busy_wait();
}

void storeAlarms(){
  debug("+DBG   storeAlarms");
  eeprom_busy_wait();
  
  uint8_t addr = MEMORY_BASE_ADDRESS + sizeof(config_t) + sizeof(alarm_t) + 1;
  eeprom_update_block(&alarms, (void *)addr, sizeof(alarm_t) * ALARM_SIZE);

  eeprom_busy_wait();
}

void loadAlarms(){
  debug("+DBG   loadAlarms");
  eeprom_busy_wait();

  uint8_t addr = MEMORY_BASE_ADDRESS + sizeof(config_t) + sizeof(alarm_t) + 1;
  eeprom_read_block(&alarms, (void *)addr, sizeof(alarm_t) * ALARM_SIZE);

  eeprom_busy_wait();
}

void initPresets()
{
  if (EEPROM.read(0) == MAGIC_NUMBER)
  {
    Serial.println("Loading saved data");
    loadConf();
    loadAlarms();
  }
  else
  {
    Serial.println("EEPROM Memory corrupted or old storage version");
    initMemory();
    saveMemory();
  }
}

void saveMemory(){
  EEPROM.write(0,MAGIC_NUMBER);
  storeConf();
  storeAlarms();
}

void initMemory(){
  Serial.println("+ DBG: initMemory()");
  config.running = 0;
  config.prevMin = 0;
  for (int i = 0; i < ALARM_SIZE; i++)
  {
    alarms[i].hour = 0;
    alarms[i].min = 0;
    alarms[i].dow = 0;
    alarms[i].duration = 0;
    alarms[i].enabled = false;
  }
}

void printAlarms(){
  for (byte i=0; i< ALARM_SIZE; i++){
    Serial.print("ALARM ");
    Serial.print(i, DEC);
    Serial.print(" is ");
    if ( alarms[i].enabled ){
      Serial.print("ON");
    }else{
      Serial.print("OFF");
    }
    Serial.print("\t ");
    
    char *out = (char *)calloc(sizeof(char),9);
    snprintf(out, 8, PSTR("%02u:%02u"),
              alarms[i].hour,
              alarms[i].min
    );
    Serial.print(alarms[i].hour);
    Serial.print(":");
    Serial.print(alarms[i].min);
    Serial.print(" Duration: ");
    Serial.print(alarms[i].duration);
    Serial.print(" ");
    Serial.println(HumanDOW[alarms[i].dow]);
    free(out);
  }
}
