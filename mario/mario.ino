//  Variables
int pulsePin = 2;                 // Pulse Sensor purple wire connected to analog pin 0
int blinkPin = 13;                // pin to blink led at each beat
int fadePin = 5;                  // pin to do fancy classy fading blink at each beat
int fadeRate = 0;                 // used to fade LED on with PWM on fadePin

// Flex variables
int leftFlexMin = 850;
int leftFlexPin = A1;
int leftLedPin = 3;

int rightFlexMin = 850;
int rightFlexPin = A0;
int rightLedPin = 5;

// Buttons
int jumpSwitchPin = 2;
int jumpLedPin = 3;

int stopSwitchPin = 4;
int stopLedPin = 5;

int lastCommand = 0;

void setup(){

  pinMode(leftLedPin, OUTPUT);
  pinMode(rightLedPin, OUTPUT);

  pinMode(jumpSwitchPin, INPUT);
  pinMode(jumpLedPin, OUTPUT);

  pinMode(stopSwitchPin, INPUT);
  pinMode(stopLedPin, OUTPUT);

  rightFlexMin = analogRead(rightFlexPin) + 50;
  leftFlexMin = analogRead(leftFlexMin) + 50;
  
  pinMode(blinkPin,OUTPUT);         // pin that will blink to your heartbeat!
  pinMode(fadePin,OUTPUT);          // pin that will fade to your heartbeat!
  Serial.begin(115200);             // we agree to talk fast!
}


//  Where the Magic Happens
void loop(){
  // left & right handler
  int leftVal = analogRead(leftFlexPin);
  int leftActive = (leftVal >= leftFlexMin);

  if (leftVal >= leftFlexMin) {
    digitalWrite(leftLedPin, HIGH);
  } else {
    digitalWrite(leftLedPin, LOW);
  }

  int rightVal = analogRead(rightFlexPin);
  bool rightActive = (rightVal >= rightFlexMin);

  if (rightActive) {
    digitalWrite(rightLedPin, HIGH);
  } else {
    digitalWrite(rightLedPin, LOW);
  }

  int command = 0;

  if (rightActive && leftActive) {
    command = 3;
  } else if (rightActive) {
    command = 1;
  } else if (leftActive) {
    command = 2;
  }

  if (command != lastCommand) {
    Serial.println("C" + command);
    lastCommand = command;
  }

  digitalWrite(blinkPin, LOW);
     
  delay(20);                             //  take a break
}
