// C++ code

const uint8_t PIR_PIN = 2;
const uint8_t LED_PIN = 12;

uint8_t pirValue;
uint8_t ledValue;

void setup()
{
  pinMode(PIR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  pirValue = digitalRead(PIR_PIN);
  
  if (pirValue == HIGH)
  {
    ledValue = HIGH;

  } else if (pirValue == LOW)
  {
    ledValue = LOW;
  }
  
  digitalWrite(LED_PIN, ledValue);
  
  Serial.print("PIR value: ");
  Serial.print(pirValue);
  Serial.print(" LED value : ");
  Serial.println(digitalRead(LED_PIN)); 
}