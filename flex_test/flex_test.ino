int potPin = A1;
int potVal = 0;
int ledPin = 9;
int potMin;

int jumpSwitchPin = 2;
int jumpLedPin = 3;

int stopSwitchPin = 4;
int stopLedPin = 5;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);

  pinMode(jumpSwitchPin, INPUT);
  pinMode(jumpLedPin, OUTPUT);

  pinMode(stopSwitchPin, INPUT);
  pinMode(stopLedPin, OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  potVal = analogRead(potPin);
  Serial.println(potVal);

  int jumpSwitchState = !digitalRead(jumpSwitchPin);

  if (jumpSwitchState) {
    digitalWrite(jumpLedPin, HIGH);
  } else {
    digitalWrite(jumpLedPin, LOW);
  }

  int stopSwitchState = !digitalRead(stopSwitchPin);

  if (stopSwitchState) {
    digitalWrite(stopLedPin, HIGH);
  } else {
    digitalWrite(stopLedPin, LOW);
  }

//  if (!potMin) {
//    potMin = potVal;
//  }
//  
//  potVal = map(potVal, potMin, potMin + 200, 0, 255);
//  analogWrite(ledPin, 255 - potVal);
//  delay(2);
//
//  Serial.println(potVal);
}
