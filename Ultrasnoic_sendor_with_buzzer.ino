// Defines the sensor pins
const int echoPin = 9;
const int triggerPin = 10;
const int buzzerPin = 8;
const int pin_switch = 2;
const int pin_LED = 6;
const int buzzerTime = 15;

// variable used for the key press
volatile boolean keyPressed = false;

// variable used to control the LED
boolean LEDstatus = LOW;

// variable used for the debounce
unsigned long timeNewKeyPress = 0;
unsigned long timeLastKeyPress = 0;
unsigned int timeDebounce = 10;
  
// defines variables
long timetofly;
int distance;
  
void setup() {
  pinMode(triggerPin, OUTPUT); // Sets trigger to Output
  pinMode(echoPin, INPUT); // Set echo to Input
  pinMode(pin_switch, INPUT);
  pinMode(pin_LED, OUTPUT);
  digitalWrite(pin_LED,LOW);
  attachInterrupt(digitalPinToInterrupt(pin_switch), keyIsPressed, RISING);
  pinMode (buzzerPin, OUTPUT);
  Serial.begin(9600); // Starts the serial communication
}
  
void loop() {
  // Clears the triggerPin
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  
  // Sets the triggerPin on HIGH state for 10 micro seconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  
  // Reads the echoPin, returns the travel time in microseconds
  timetofly= pulseIn(echoPin, HIGH);
  
  // Calculating the distance (Time to Fly Calculation)
  distance= timetofly*0.034/2;
  
  // Prints the distance on the Serial Monitor in CM
  Serial.print("Distance: ");
  Serial.println(distance);

  if (keyPressed){
    keyPressed = false;
    timeNewKeyPress = millis();
    
    if ( timeNewKeyPress - timeLastKeyPress >= timeDebounce){
      if (LEDstatus == LOW) { LEDstatus = HIGH; } else { LEDstatus = LOW; }   
        digitalWrite(pin_LED, LEDstatus);
    }
    timeLastKeyPress = timeNewKeyPress;
  }


  /*
  Serial.print("LEDstatus=");
  Serial.println(LEDstatus);
  Serial.print("keyPressed=");
  Serial.println(keyPressed);
  */
  if(distance<=50 && LEDstatus==HIGH){
    for(int i=1;i<=buzzerTime*5;i++){
      digitalWrite (buzzerPin, HIGH);
      delay (100);
      digitalWrite (buzzerPin, LOW);
      delay (100);
      if (keyPressed==true) {
        keyPressed=false;
        digitalWrite(pin_LED, LOW);
        Serial.println("break");
        break;
      }
    }
  }
}

void keyIsPressed()
{
   Serial.println("button pressed");
   keyPressed = true;
}
