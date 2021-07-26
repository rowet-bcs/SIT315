// C++ code

const uint8_t PIR_PIN = 2;
const uint8_t BTN_PIN = 3;
const uint8_t LED_PIN = 12;
const uint8_t BTN_LED_PIN = 9;

uint8_t pirValue = LOW;
uint8_t ledValue = LOW;
uint8_t btnLedValue = LOW;

void setup()
{
  pinMode(PIR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BTN_PIN, INPUT_PULLUP);
  pinMode(BTN_LED_PIN, OUTPUT);

  // Definte interrupts
  attachInterrupt(0, pirInterrupt, CHANGE);
  attachInterrupt(1, btnInterrupt, RISING);
  
  Serial.begin(9600);
}

void loop()
{

  
}


void pirInterrupt()
{
  // Triggered as motion detected
  pirValue = digitalRead(PIR_PIN);
  ledValue = pirValue;
  
  digitalWrite(LED_PIN, ledValue);
  
  // Write to serial monitor
  Serial.print("PIR value: ");
  Serial.print(pirValue);
  Serial.print(" LED value : ");
  Serial.println(digitalRead(LED_PIN));
  
}


void btnInterrupt()
{
  // Triggered as button clicked
  
  // Toggle the LED state and write this to the LED
  btnLedValue = !btnLedValue;
  digitalWrite(BTN_LED_PIN, btnLedValue);
  
  // Write to serial monitor
  Serial.print("Button clicked!");
  Serial.print(" LED value : ");
  Serial.println(digitalRead(BTN_LED_PIN));
  
}