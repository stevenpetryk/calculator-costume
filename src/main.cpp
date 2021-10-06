#include <Arduino.h>
#include <Keypad.h>
#include "expression.h"

const byte ROWS = 2;
const byte COLS = 2;
char keys[ROWS][COLS] = {
    {'A', 'C'},
    {'B', 'D'},
};
byte rowPins[ROWS] = {6, 5};
byte colPins[COLS] = {10, 9};

unsigned long loopCount;
unsigned long startTime;
String msg;

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup()
{
  Serial.begin(9600);
  loopCount = 0;
  startTime = millis();
  msg = "";
}

void loop()
{
  loopCount++;
  if ((millis() - startTime) > 5000)
  {
    startTime = millis();
    loopCount = 0;
  }

  if (keypad.getKeys())
  {
    for (int i = 0; i < LIST_MAX; i++) // Scan the whole key list.
    {
      if (keypad.key[i].stateChanged) // Only find keys that have changed state.
      {
        switch (keypad.key[i].kstate)
        {
        case PRESSED:
          Serial.println(keypad.key[i].kchar);
          break;
        case HOLD:
          msg = " HOLD.";
          break;
        case RELEASED:
          msg = " RELEASED.";
          break;
        case IDLE:
          msg = " IDLE.";
        }

        // Serial.print(keypad.key[i].kchar);
        // Serial.println(msg);
      }
    }
  }
}

// #include <FastLED.h>

// // How many leds in your strip?
// #define SIDE_LEN 16
// #define NUM_LEDS (SIDE_LEN * SIDE_LEN)

// #define DATA_PIN 6
// // #define CLOCK_PIN 13

// // Define the array of leds
// CRGB leds[NUM_LEDS];

// void setup()
// {
//   FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
//   FastLED.setMaxPowerInVoltsAndMilliamps(5, 2000);
// }

// int pixelAt(int x, int y)
// {
//   y += 3;
//   x += 3;
//   if (y % 2 == 1)
//   {
//     return y * SIDE_LEN + (SIDE_LEN - 1 - x);
//   }
//   return y * SIDE_LEN + x;
// }

// int prevX = -1;
// int prevY = -1;

// void loop()
// {
//   FastLED.clear();

//   // Draw the letter A
//   leds[pixelAt(0, 0)] = 0x111111;
//   leds[pixelAt(0, 1)] = 0x111111;
//   leds[pixelAt(0, 2)] = 0x111111;
//   leds[pixelAt(0, 3)] = 0x111111;
//   leds[pixelAt(0, 4)] = 0x111111;
//   leds[pixelAt(0, 5)] = 0x111111;
//   leds[pixelAt(1, 6)] = 0x111111;
//   leds[pixelAt(2, 6)] = 0x111111;
//   leds[pixelAt(3, 5)] = 0x111111;
//   leds[pixelAt(3, 4)] = 0x111111;
//   leds[pixelAt(3, 3)] = 0x111111;
//   leds[pixelAt(3, 2)] = 0x111111;
//   leds[pixelAt(3, 1)] = 0x111111;
//   leds[pixelAt(3, 0)] = 0x111111;
//   leds[pixelAt(1, 3)] = 0x111111;
//   leds[pixelAt(2, 3)] = 0x111111;

//   leds->maximizeBrightness(10);

//   FastLED.show();
//   while (true)
//   {
//     delay(1000);
//   }
// }
