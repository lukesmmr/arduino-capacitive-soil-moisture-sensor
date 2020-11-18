
/* Soil Moisture Sensor w/ active buzzer, RGB LED & Liquid Crystal LCD
 * If plant sensor moisture percentage drops below 30 buzzer
 * will ring and LED turns red. If not buzzer is idle on off
 * and LED is green. When moisture alarm is on/off LCD will show
 * custom messages.
 * 
 * Requires: Capacitive soil moisture sensor v1.2, active buzzer, breadboard, 
 * arduino uno (or similar), RGB LED, Liquid Crystal LCD, connector cables
 */

 // include the library code:
#include <LiquidCrystal.h>

const int dry = 916;
const int wet = 762;
const int speakerPin = 10;

const int redPin= 6;
const int greenPin = 7;
const int bluePin = 8;

String plantNeedsWaterMsg = "Please give me";
String plantNeedsWaterMsg2 = "more water!    ";
String plantIsHappyMsg = "I have enough";
String plantIsHappyMsg2 = "water, thanks!   ";

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  Serial.begin(9600);
  
  pinMode(speakerPin,OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  
  lcd.begin(16, 2);
  // set the cursor to the top left
  lcd.setCursor(0, 0);
}

void loop() {
  
  const int sensorInput = analogRead(A0);
  // map percentage
  const int percent = map(sensorInput, wet, dry, 100, 0);
  if (percent >= 30) {
    // turn active speaker off
    digitalWrite(speakerPin, LOW);
    // turn LED green
    setRGBColor(0,255,0);
    lcd.setCursor(0, 0);
    lcd.print(plantIsHappyMsg);
    lcd.setCursor(0, 1);
    lcd.print(plantIsHappyMsg2);
  } else {
    // turn active speak on
    digitalWrite(speakerPin, HIGH);
    // turn LED red
    setRGBColor(255,0,0);
    lcd.setCursor(0, 0);
    lcd.print(plantNeedsWaterMsg);
    lcd.setCursor(0, 1);
    lcd.print(plantNeedsWaterMsg2);
  }
  // repeat every 500ms
  delay(500);
}

/**
 * RGB Color Setter
 * @param {int} redValue
 * @param {int} greenValue
 * @param {int} blueValue
 */
void setRGBColor(int redValue, int greenValue, int blueValue) {
   analogWrite(redPin, redValue);
   analogWrite(greenPin, greenValue);
   analogWrite(bluePin, blueValue);
}