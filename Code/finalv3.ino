#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif
#include <SparkFunMPU9250-DMP.h>

MPU9250_DMP imu;
#define PIN 5
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);

#define BMP_SCK  (13)
#define BMP_MISO (12)
#define BMP_MOSI (11)
#define BMP_CS   (10)
Adafruit_BMP280 bmp; // I2C
//Adafruit_BMP280 bmp(BMP_CS); // hardware SPI
//Adafruit_BMP280 bmp(BMP_CS, BMP_MOSI, BMP_MISO,BMP_SCK);
unsigned long previousmillis = millis();
static float z = -10;
void setup() {
  Serial.begin(9600);
  //checking if the barometer was detected
  if (!bmp.begin()) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
  }
  //turning on the leds at the bottom of the height and time columns
  strip.setPixelColor(0, strip.Color(255, 0, 0));
  strip.show();
  strip.setPixelColor(5, strip.Color(255, 255, 0));
  strip.show();
  //initializing the countdown LEDs
  for (int i = 6; i < 10; i++) {
    strip.setPixelColor(i, strip.Color(255, 255, 255));
    strip.show();
  }
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
  strip.begin();
  strip.setBrightness(50);
  strip.show();
  imu.begin();
  imu.dmpBegin(DMP_FEATURE_TAP, 10);
  unsigned short xThresh = 0;   // Disable x-axis tap
  unsigned short yThresh = 0;   // Disable y-axis tap
  unsigned short zThresh = 100; // Set z-axis tap thresh to 100 mg/ms
  unsigned char taps = 1;       // Set minimum taps to 1
  unsigned short tapTime = 100; // Set tap time to 100ms
  unsigned short tapMulti = 1000;// Set multi-tap time to 1s
  imu.dmpSetTap(xThresh, yThresh, zThresh, taps, tapTime, tapMulti);

}

void loop() {
  //start the timer
  unsigned long currentmillis = millis();
  double y = bmp.readAltitude(1013.25);
  //initialize the height
  if (z == -10)
  {
    z = y;
  }
  if ( imu.fifoAvailable() )
  {
    // DMP FIFO must be updated in order to update tap data
    imu.dmpUpdateFifo();
    // Check for new tap data by polling tapAvailable
    //Once tapped reset the timer and re-initialize the height
    if ( imu.tapAvailable() )
    {

      // If a new tap happened, get the direction and count
      // by reading getTapDir and getTapCount
      unsigned char tapDir = imu.getTapDir();
      // unsigned char tapCnt = imu.getTapCount();
      if (tapDir == TAP_Z_DOWN || tapDir == TAP_Z_UP) {
        previousmillis = currentmillis;
        for (int i = 6; i < 10; i++) {
          strip.setPixelColor(i, strip.Color(255, 255, 255));
          strip.show();
        }
        z = y;
      }
    }
  }
  //the following if statements turn the LEDs on depending on the height of the device relative to the initial height
  if (y > z + 1)
  {
    strip.setPixelColor(1, strip.Color(255, 255, 0));
    strip.show();
  }
  else {
    strip.setPixelColor(1, 0);
    strip.show();
  }
  if (y > z + 2)
  {
    strip.setPixelColor(2, strip.Color(255, 255, 255));
    strip.show();
  }
  else {
    strip.setPixelColor(2, 0);
    strip.show();
  }
  if (y > z + 3)
  { strip.setPixelColor(3, strip.Color(0, 0, 255));
    strip.show();
  }
  else {
    strip.setPixelColor(3, 0);
    strip.show();
  }
  if (y > z + 4)
  {
    strip.setPixelColor(4, strip.Color(0, 255, 0));
    strip.show();
  }
  else {
    strip.setPixelColor(4, 0);
    strip.show();
  }
  //the following if statements turn the LEDs off depending on the time since the initial time
  if (currentmillis - previousmillis >=  60000)
  { strip.setPixelColor(9, 0);
    strip.show();
  }
  if (currentmillis - previousmillis >= 2 * 60000)
  { strip.setPixelColor(8, 0);
    strip.show();
  }
  if (currentmillis - previousmillis >= 3 * 60000)
  { strip.setPixelColor(7, 0);
    strip.show();
  } if (currentmillis - previousmillis >= 4 * 60000)
  { strip.setPixelColor(6, 0);
    strip.show();
  }
}
