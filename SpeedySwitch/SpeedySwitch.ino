
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <avr/pgmspace.h>
#include <math.h>
#include <EEPROM.h>

#define BUTTONPIN 5
#define LEDPIN 7
#define VBATPIN A1

static bool button_state = false;
boolean button_latched = false;

uint16_t highscore = 0;

int consoleState = 0;

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

unsigned long elaspedTime = millis();


void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  getHighscore();
  display.display();

  pinMode(BUTTONPIN, INPUT_PULLUP);
  pinMode(LEDPIN, OUTPUT);
  display.clearDisplay();

  while (millis() - elaspedTime < 100);

}

void loop() {
    elaspedTime = millis();

    button_state = (digitalRead(BUTTONPIN) == LOW);

    if(consoleState == 0){
      menu_init();
      menu_display();
      menu_input_handle();
    } else {
      display.clearDisplay();
      free_click_mode();
    }
}

void getHighscore() {
  EEPROM.get(0, highscore);
}

void updateHighscore(uint16_t currentRunScore) {
  if (currentRunScore > highscore) {
    EEPROM.write(0, currentRunScore);
    highscore = currentRunScore;
  }
}
