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

char lastCommand;

void setup(){

  pinMode(leftLedPin, OUTPUT);
  pinMode(rightLedPin, OUTPUT);

  pinMode(jumpSwitchPin, INPUT);
  pinMode(jumpLedPin, OUTPUT);

  pinMode(stopSwitchPin, INPUT);
  pinMode(stopLedPin, OUTPUT);  
  
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
    delay(500);
    digitalWrite(leftLedPin, LOW);
  }

  int rightVal = analogRead(rightFlexPin);
  bool rightActive = (rightVal >= rightFlexMin);

  if (rightActive) {
    digitalWrite(rightLedPin, HIGH);
    delay(500);
    digitalWrite(rightLedPin, LOW);
  }

  char command = "S";

  if (rightActive && leftActive) {
    command = "J";
  } else if (rightActive) {
    command = "R";
  } else if (leftActive) {
    command = "L";
  }

  if (command !== lastCommand) {
    Serial.println(command);
    lastCommand = command;
  }

  digitalWrite(blinkPin, LOW);
     
  delay(20);                             //  take a break
}
