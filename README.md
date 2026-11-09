4-Bit Binary Counter: AVR Port Manipulation
📌 Project Overview
This project implements a 4-bit binary click counter using an Arduino Uno, a push button, and four LEDs. Each time the push button is connected and clicked, the counter increments from 0 up to 15, displaying the corresponding 4-bit binary number directly on the LEDs using AVR port manipulation.   
875d89ba-8fa4-4280-ad60-b93118212e9b
+ 1

🎯 Objectives
Build a 4-bit binary click counter (0 to 15).   
875d89ba-8fa4-4280-ad60-b93118212e9b

Display binary values using four LEDs connected to Pins 8–11.   
875d89ba-8fa4-4280-ad60-b93118212e9b

Read button input using the PINB register.   
875d89ba-8fa4-4280-ad60-b93118212e9b

Configure pin directions using the DDRB register.   
875d89ba-8fa4-4280-ad60-b93118212e9b

Control LEDs using a single PORTB register write.   
875d89ba-8fa4-4280-ad60-b93118212e9b

Use the Arduino's internal pull-up resistor for the push button on Pin 12.   
875d89ba-8fa4-4280-ad60-b93118212e9b

🛠️ Components Required
Arduino Uno   
875d89ba-8fa4-4280-ad60-b93118212e9b

1 × Push Button (connected between Pin 12 and GND)   
875d89ba-8fa4-4280-ad60-b93118212e9b

4 × LEDs (connected to Pins 8, 9, 10, 11)   
875d89ba-8fa4-4280-ad60-b93118212e9b

4 × 220Ω Resistors

Jumper Wires

Breadboard

🔌 Pin Configuration
Component	Arduino Pin	Register Bit
LED 1	D8	PB0
LED 2	D9	PB1
LED 3	D10	PB2
LED 4	D11	PB3
Push Button	D12	PB4
⚙️ Working Principle
Pins 8–11 are configured as OUTPUT and Pin 12 as INPUT via the DDRB register.

The internal pull-up resistor is enabled for Pin 12 using PORTB.

The button state is continuously monitored through the PINB register.   
875d89ba-8fa4-4280-ad60-b93118212e9b

A 50 ms delay is implemented for simple button debouncing.   
875d89ba-8fa4-4280-ad60-b93118212e9b

Each valid button press increments the counter (0–15) and updates the LEDs via a PORTB register write.   
875d89ba-8fa4-4280-ad60-b93118212e9b

💻 Code (sketch.ino)
C++
void setup() {
  // Pin 8-11 as OUTPUT, Pin 12 as INPUT
  DDRB |= (1 << DDB0) | (1 << DDB1) | (1 << DDB2) | (1 << DDB3);
  DDRB &= ~(1 << DDB4); 

  // Enable internal pull-up resistor on Pin 12 (PB4)
  PORTB |= (1 << PORTB4);

  Serial.begin(9600);
}

void loop() {
  static uint8_t counter = 0;          
  static bool lastButtonState = HIGH;   

  bool currentButtonState = (PINB & (1 << PINB4));

  if (lastButtonState == HIGH && currentButtonState == LOW) {
    delay(50); // Simple debouncing

    counter = (counter + 1) % 16; // Increment counter 0 to 15

    // Write counter value to PORTB lower 4 bits
    PORTB = (PORTB & 0xF0) | (counter & 0x0F);

    Serial.print("Counter: ");
    Serial.println(counter);
  }

  lastButtonState = currentButtonState;
}
📚 Registers Used
DDRB – Data Direction Register B   
f50605ed-3ebf-4cb3-9b49-5bffc99e5bbf

PORTB – Port B Data Register   
f50605ed-3ebf-4cb3-9b49-5bffc99e5bbf

PINB – Port B Input Register   
f50605ed-3ebf-4cb3-9b49-5bffc99e5bbf

👩‍💻 Project Information
Platform: Wokwi Simulator   
https://wokwi.com/projects/480009282197612545

Project Type: Embedded Systems / AVR Register Manipulation

Language: C++
