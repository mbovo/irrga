#include "serialCallbacks.h"

bool parseSerialCommand(char *buffer, int size = 26)
{

  char localbuffer[size];
  strncpy(localbuffer, buffer, size);

  char *cmd = strtok(localbuffer, " ");
  char *arg = strtok(NULL, " ");
  char *val = strtok(NULL, " ");
  for (int i = 0; i < SERIAL_CALLBACKS_COUNT; i++)
  {
    if (!strncmp(cmd, "++", 2))
    {
      Serial.println("I'm alive");
      return true;
    }
    if (!strncmp(cmd, serialCommands[i].cmd, 2))
    {
      return serialCommands[i].callback((void *)arg, (void *)val);
    }
  }
  return false;
}
