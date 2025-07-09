#include <Adafruit_NeoPixel.h>

const int DIN_PIN = 10;
const int LED_COUNT = 98;

Adafruit_NeoPixel pixels(LED_COUNT, DIN_PIN, NEO_BRG + NEO_KHZ800);

void setup() {
  pixels.begin();
  pixels.clear();
  pixels.setBrightness(0);
  pixels.show();
}

uint32_t white = pixels.Color(128, 128, 128);
uint32_t red = pixels.Color(128, 0, 0);
uint32_t orange = pixels.Color(128, 40, 0);
uint32_t yellow = pixels.Color(128, 80, 0);
uint32_t green = pixels.Color(0, 128, 0);
uint32_t cyan = pixels.Color(0, 128, 128);
uint32_t blue = pixels.Color(0, 0, 128);
uint32_t purple = pixels.Color(128, 0, 128);

uint32_t rainbow_color[] = {red, orange, yellow, green, cyan, blue, purple};
int rainbow_index[] = {6, 5, 4, 3, 2, 1, 0};

// function declarations
void led_chase(uint32_t color1, uint32_t color2, uint32_t duration);  // durations in milliseconds
void led_blink(uint32_t color1, uint32_t color2, uint32_t duration);
void led_breathe(uint32_t color, uint32_t duration);
void led_flag();

void loop() {
  delay(3000);
  
  /* DEMO */
  led_chase(blue, orange, 6000);
  delay(1000);

  led_blink(green, cyan, 5000);
  delay(1000);

  led_breathe(red, 2000);
  led_breathe(yellow, 2000);
  delay(1000);


  /* TRAP THE LOOP */
  led_flag();
  while (true) { delay(1000); }
}

void led_chase(uint32_t color1, uint32_t color2, uint32_t duration) {
  uint32_t step_ms = duration < LED_COUNT ? 1 : duration / LED_COUNT;
  pixels.setBrightness(200);
  for (int i = 0; i < LED_COUNT; i++) {
    pixels.clear();

    pixels.setPixelColor((i-22) % LED_COUNT, color1);
    pixels.setPixelColor((i-21) % LED_COUNT, color1);
    pixels.setPixelColor((i-20) % LED_COUNT, color1);

    pixels.setPixelColor((i-2) % LED_COUNT, color2);
    pixels.setPixelColor((i-1) % LED_COUNT, color2);
    pixels.setPixelColor((i-0) % LED_COUNT, color2);
    pixels.show();
    delay(step_ms);
  }
  pixels.clear();
}

void led_breathe(uint32_t color, uint32_t duration) {
  uint32_t step_ms = duration < 2*LED_COUNT ? 1 : duration / LED_COUNT;
  pixels.clear();
    
  for (int k = 0; k < 150; k++){
    pixels.setBrightness(k);
    pixels.fill(color);
    pixels.show();
    delay(step_ms);
  }
    
  for (int k = 150; k > 0; k--){
    pixels.setBrightness(k);
    pixels.fill(color);
    pixels.show();
    delay(step_ms);
  }
  
  pixels.clear();
}

void led_blink(uint32_t color1, uint32_t color2, uint32_t duration) {
  uint32_t step_ms = duration < 100 ? 100 : duration;
  pixels.setBrightness(150);

  for (int i = 0; i < LED_COUNT; i++) {
    if (i%2) {
      pixels.setPixelColor(i, color1);
      pixels.show();
    }
  }
  delay(step_ms);
  pixels.clear();
  
  for (int i = 0; i < LED_COUNT; i++) {
    if ((i+1)%2) {
      pixels.setPixelColor(i, color2);
      pixels.show();
    }
  }
  delay(step_ms);
  pixels.clear();
}

void led_flag() {
  uint32_t stars_cnt = LED_COUNT / 3;
  stars_cnt = stars_cnt % 2 ? stars_cnt++ : stars_cnt;

  pixels.setBrightness(100);

  for (int j = 0; j + 1 < LED_COUNT - stars_cnt; j+=2) {
    if ((j / 2) % 2) {
      pixels.setPixelColor(j, red);
      pixels.setPixelColor(j+1, red);
    } else {
      pixels.setPixelColor(j, white);
      pixels.setPixelColor(j+1, white);      
    }
    pixels.show();
  }

  for (int j = LED_COUNT - stars_cnt; j < LED_COUNT; j++) {
    if (j % 2) {
      pixels.setPixelColor(j, white);
    } else {
      pixels.setPixelColor(j, blue);
    }
    pixels.show();
  }

}
