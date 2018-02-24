#define ledPin 9
const int FLEX_PIN1 = A0;
const int FLEX_PIN2 = A1;
const float VCC = 4.98; // Measured voltage of Ardunio 5V line
const float R_DIV = 47500.0; // Measured resistance of 3.3k resistor
const float STRAIGHT_RESISTANCE = 37300.0; // resistance when straight
const float BEND_RESISTANCE = 90000.0; // resistance at 90 deg

int state = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(38400);
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(FLEX_PIN1, INPUT);
  pinMode(FLEX_PIN2, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    state = Serial.read() - 48;
  }
  //Serial.println(state);
  if (state == 1) {
    digitalWrite(5, HIGH);
  }
  else if (state == 0) {
    digitalWrite(5, LOW);
  }

  if (state == 2) {
    digitalWrite(3, HIGH);
  }
  else if (state == 0) {
    digitalWrite(3, LOW);
  }
  int flexADC1 = analogRead(FLEX_PIN1);
  int flexADC2 = analogRead(FLEX_PIN2);
  float flexV1 = flexADC1 * VCC / 1023.0;
  float flexR1 = R_DIV * (VCC / flexV1 - 1.0);
  float flexV2 = flexADC2 * VCC / 1023.0;
  float flexR2 = R_DIV * (VCC / flexV2 - 1.0);
  //Serial.println("Resistance: " + String(flexR) + " ohms");

  // Use the calculated resistance to estimate the sensor's
  // bend angle:
  float angle1 = map(flexR1, STRAIGHT_RESISTANCE, BEND_RESISTANCE,
                     0, 90.0);
  float angle2 = map(flexR2, STRAIGHT_RESISTANCE, BEND_RESISTANCE,
                     0, 90.0);
  //Serial.println("Bend: " + String(angle) + " degrees");
  //Serial.println();
  //Serial.println(String(angle1));
  //Serial.println(String(angle2));

  if (angle1 > 220) {
    Serial.write('4');
  }


  else if (angle2 > 160) {
    Serial.write('5');
  }

  else {
    Serial.write('3');
  }

}

