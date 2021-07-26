// C++ code

const uint8_t PIR_PIN = 2;
const uint8_t BTN_PIN = 3;
const uint8_t SW_PIN = 4;

const uint8_t BTN_LED_PIN = 9; // RED LED
const uint8_t SW_LED_PIN = 10; // BLUE LED
const uint8_t TMR_LED_PIN = 11; // ORANGE LED
const uint8_t PIR_LED_PIN = 12; // GREEN LED

byte m, s, b = 0;
byte mPrev, sPrev = 0;

uint8_t btnLedValue = LOW;
uint8_t tmrLedValue = LOW;

void setup()
{
  // Set PIN modes
  pinMode(PIR_PIN, INPUT);
  pinMode(BTN_PIN, INPUT_PULLUP);
  pinMode(SW_PIN, INPUT);
  pinMode(BTN_LED_PIN, OUTPUT);
  pinMode(SW_LED_PIN, OUTPUT);
  pinMode(TMR_LED_PIN, OUTPUT);
  pinMode(PIR_LED_PIN, OUTPUT);

  // Enable interrupts on port D
  PCICR |= 0b00000100;
  // Enabled intterrupts on pins 2, 3 & 4
  PCMSK2 |= 0b00011100;
  
  // Setup timer interrupt
  noInterrupts();
  // Clear registers
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 =0;
  
  // Set timer compare to blink every 4 seconds
  OCR1A = 62499;
  
  // Set CS12, CS11 and CS10 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (0 << CS11) | (1 << CS10);
  
  // Enable time compare interrupt
  TIMSK1 |= (1 << OCIE1A);
  
  // Turn on CTC mode to reset timer
  TCCR1B |= (1 << WGM12);
  
  interrupts();
  
  // Launch serial monitor
  Serial.begin(9600);
}

void loop()
{

  
}

// Port level interrupt
ISR(PCINT2_vect)
{
  // Retrieve PIN values
  m = PIND & B00000100;
  s = PIND & B00010000;
  b = PIND & B00001000;
  
  
  // If motion sensor has changed
  if (m != mPrev)
  {
   	// Update LED to current sensor state
    digitalWrite(PIR_LED_PIN, m);

    // Write to serial monitor     
    if (m == LOW)
    {
      Serial.print("Motion stopped. ");
    }
    else
    {
      Serial.print("Motion detected. ");
    }
    
    Serial.print("LED value: ");
    Serial.println(digitalRead(PIR_LED_PIN));
    
    // Update motion sensor previous state
    mPrev = m;
  }
  
  // If switch has changed
  if (s != sPrev)
  {
	// Update LED to current sensor state
    digitalWrite(SW_LED_PIN, s);  
    
    // Write to serial monitor    
    if (s == LOW)
    {
      Serial.print("Switched turned off. ");
    }
    else
    {
      Serial.print("Switch turned on. ");
    }

    Serial.print(" LED value : ");
    Serial.println(digitalRead(SW_LED_PIN));
    
    // Update switch previous state
    sPrev = s;
  }  
  
  // If button was pressed (not released)
  if (b != LOW)
  {
    // Toggle the LED state and write this to the LED
    btnLedValue = !btnLedValue;
    digitalWrite(BTN_LED_PIN, btnLedValue);

    // Write to serial monitor
    Serial.print("Button clicked! LED value: ");
    Serial.println(digitalRead(BTN_LED_PIN));
  }
}

// Timer interrupt
ISR(TIMER1_COMPA_vect)
{
  // Toggle the LED state and write this to the LED
  tmrLedValue = !tmrLedValue;
  digitalWrite(TMR_LED_PIN, tmrLedValue);
  
  Serial.print("Timer counted 4 seconds. LED value: ");
  Serial.println(digitalRead(TMR_LED_PIN));
}