#include <Adafruit_NeoPixel.h>

#define NUM_OF_PIXELS 12
#define LEDPIN 7
#define MICPIN A1

// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_OF_PIXELS, LEDPIN, NEO_GRB + NEO_KHZ800);

const int sampleWindow = 50; // Sample window width in mS (50 ms = 20Hz)
unsigned int sample;

void setup()
{
    Serial.begin(9600);
    strip.begin();
    strip.show(); // Initialize all pixels to 'off'
}

void loop()
{
    float MaximumBrightness = 255;
    float SpeedFactor = 0.001; // I don't actually know what would look good
    float StepDelay = 10; // ms for a step delay on the lights
    float red, green, blue;
    float intensity = getVolume();
    Serial.println(intensity);

    // Now set every LED to that color
    for (int ledNumber=0; ledNumber<NUM_OF_PIXELS; ledNumber++)
    {
        strip.setPixelColor(ledNumber,
                            map(intensity, 0, MaximumBrightness, 0, MaximumBrightness), //red
                            map((MaximumBrightness-intensity)*(MaximumBrightness-intensity), 100, MaximumBrightness*MaximumBrightness, 0, MaximumBrightness/5), //green
                            map(sin((intensity/MaximumBrightness)*3.14)*MaximumBrightness, 0, MaximumBrightness, 0, MaximumBrightness/2)); //blue
    }
    strip.show();
    delay(StepDelay);
}

float getVolume()
{
    unsigned long startMillis= millis();  // Start of sample window
    unsigned int peakToPeak = 0;   // peak-to-peak level
    unsigned int signalMax = 0;
    unsigned int signalMin = 1024;

   // collect data for 'sampleWindow' ms
   while (millis() - startMillis < sampleWindow)
   {
        sample = analogRead(MICPIN);
        if (sample < 1024)  // toss out spurious readings
        {
            if (sample > signalMax)
            {
                signalMax = sample;  // save just the max levels
            }
            else if (sample < signalMin)
            {
                signalMin = sample;  // save just the min levels
            }
        }
   }

   peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude
   //map(value, fromLow, fromHigh, toLow, toHigh)
   return map (peakToPeak, 0, 700, 0, 255);
}

