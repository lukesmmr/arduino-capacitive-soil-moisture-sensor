
/* Soil Moisture Sensor w/ active buzzer & RGB LED
 * If plant sensor moisture percentage drops below 30 buzzer
 * will ring and LED turns red. If not buzzer is idle on off
 * and LED is green. 
 * 
 * Requires: capacitive soil moisture sensor v1.2, active buzzer, 
 * bread board, arduino uno (or similar), RGB LED, connector cables
 */

const int dry = 916;
const int wet = 762;
const int speakerPin = 11;

const int redPin= 5;
const int greenPin = 6;
const int bluePin = 7;

void setup() {
  Serial.begin(9600);
  pinMode(speakerPin,OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  
  const int sensorInput = analogRead(A0);
  // map percentage
  const int percent = map(sensorInput, wet, dry, 100, 0);

  // log percent to serial monitor
  Serial.print(percent);
  Serial.println("%");

  if (percent >= 30) {
    // turn active speaker off
    digitalWrite(speakerPin, LOW);
    // turn LED green
    setRGBColor(0,255,0);
  } else {
    // turn active speak on
    digitalWrite(speakerPin, HIGH);
    // turn LED red
    setRGBColor(255,0,0);
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