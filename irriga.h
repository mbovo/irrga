

void irrigaStart()
{
  digitalWrite(REL_3_PIN, HIGH);
  digitalWrite(REL_4_PIN, LOW);
  delay(1500);
}

void irrigaStop()
{
  digitalWrite(REL_3_PIN, LOW);
  digitalWrite(REL_4_PIN, HIGH);
  delay(1500);
}

void irrigaReset()
{
  digitalWrite(REL_3_PIN, LOW);
  digitalWrite(REL_4_PIN, LOW);
}
