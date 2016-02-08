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

// Volatile Variables, used in the interrupt service routine!
volatile int BPM;                   // int that holds raw Analog in 0. updated every 2mS
volatile int Signal;                // holds the incoming raw data
volatile int IBI = 600;             // int that holds the time interval between beats! Must be seeded! 
volatile boolean Pulse = false;     // "True" when User's live heartbeat is detected. "False" when not a "live beat". 
volatile boolean QS = false;        // becomes true when Arduoino finds a beat.

// Regards Serial OutPut  -- Set This Up to your needs
static boolean serialVisual = true;   // Set to 'false' by Default.  Re-set to 'true' to see Arduino Serial Monitor ASCII Visual Pulse 


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
  interruptSetup();                 // sets up to read Pulse Sensor signal every 2mS 
   // IF YOU ARE POWERING The Pulse Sensor AT VOLTAGE LESS THAN THE BOARD VOLTAGE, 
   // UN-COMMENT THE NEXT LINE AND APPLY THAT VOLTAGE TO THE A-REF PIN
//   analogReference(EXTERNAL);   
}


//  Where the Magic Happens
void loop(){
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

  // left & right handler
  int leftVal = analogRead(leftFlexPin);
//  Serial.println(leftVal);

  if (leftVal >= leftFlexMin) {
    digitalWrite(leftLedPin, HIGH);
    delay(500);
    digitalWrite(leftLedPin, LOW);
  }

  int rightVal = analogRead(rightFlexPin);
//  Serial.println(rightVal);

  if (rightVal >= rightFlexMin) {
    digitalWrite(rightLedPin, HIGH);
    delay(500);
    digitalWrite(rightLedPin, LOW);
  }
  
    serialOutput() ;       
    
  if (QS == true){     // A Heartbeat Was Found
                       // BPM and IBI have been Determined
                       // Quantified Self "QS" true when arduino finds a heartbeat
        digitalWrite(blinkPin,HIGH);     // Blink LED, we got a beat. 
        fadeRate = 255;         // Makes the LED Fade Effect Happen
                                // Set 'fadeRate' Variable to 255 to fade LED with pulse
        serialOutputWhenBeatHappens();   // A Beat Happened, Output that to serial.     
        QS = false;                      // reset the Quantified Self flag for next time    
  }

  digitalWrite(blinkPin, LOW);
     
  delay(20);                             //  take a break
}
