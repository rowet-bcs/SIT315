// C++ code

const uint8_t PIR_PIN = 2;
const uint8_t LED_PIN = 12;

uint8_t pirValue;
uint8_t ledValue;

void setup()
{
  pinMode(PIR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  attachInterrupt(0, interrupt, CHANGE);
  Serial.begin(9600);
}

void loop()
{
 
}

void interrupt()
{
  pirValue = digitalRead(PIR_PIN);
  ledValue = pirValue;
  
  digitalWrite(LED_PIN, ledValue);
   
  Serial.print("PIR value: ");
  Serial.print(pirValue);
  Serial.print(" LED value : ");
  Serial.println(digitalRead(LED_PIN));
  
}