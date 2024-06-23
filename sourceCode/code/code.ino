/* 
  Code help from
  Ultrasonic = https://howtomechatronics.com/tutorials/arduino/ultrasonic-sensor-hc-sr04/
  Reed Switch = https://lastminuteengineers.com/reed-switch-arduino-tutorial/
*/
//Need Library

//Ultrasonic Sensor Values for Front of Car
const int redF = 100;
const int yellowF = 345;
const int greenF = 2500;

//Ultrasonic Sensor Values for Side of Car
const int redS = 10;
const int yellowS = 20;
const int greenS = 30;

//Ultrasonic Module pre-setup (Front of Car)
const int trigPinF = 3;  //Defines pin number
const int echoPinF = 2;  //Defines pin number
long durationF;          //Travel time, this is a Long variable
int distanceF;           //Integer variable for the distance

//Ultrasonic Module pre-setup (Side of Car)
const int trigPinS = 5;  //Defines pin number
const int echoPinS = 4;  //Defines pin number
long durationS;          //Travel time, this is a Long variable
int distanceS;           //Integer variable for the distance

//Reed Switch pre-setup
const int reedPin = 12;  // Defines pin number
int reedPinValue;        //Store the value of the switch
int reedActive;

//LED Strip pre-setup Front of car
const int redLightF = 9;
const int yellowLightF = 10;
const int greenLightF = 11;

//LED Strip pre-setup Side of car
const int redLightS = 6;
const int yellowLightS = 7;
const int greenLightS = 8;

void setup() {
  pinMode(trigPinF, OUTPUT);      // Sets trigPin as a Output
  pinMode(echoPinF, INPUT);       // Sets echoPin as a Input
  pinMode(trigPinS, OUTPUT);      // Sets trigPin as a Output
  pinMode(echoPinS, INPUT);       // Sets echoPin as a Input
  pinMode(reedPin, OUTPUT);       //Set reedpin as an Output
  pinMode(LED_BUILTIN, OUTPUT);   //use for indicator of reed sensor state
  pinMode(redLightF, OUTPUT);     //Set redLight as a Output
  pinMode(yellowLightF, OUTPUT);  //Set yellowLight as a Output
  pinMode(greenLightF, OUTPUT);   //Set greeLight as a Output

  Serial.begin(9600);
}

void loop() {
  rrss();
  rusmf();
  rusms();

  if (reedActive == 0) {
    if (distanceF <= redF) {
      digitalWrite(redLightF, HIGH);
      digitalWrite(yellowLightF, LOW);
      digitalWrite(greenLightF, LOW);
            Serial.print("DistanceF: ");
  Serial.println(distanceF);
    } else if (distanceF > redF && distanceF <= yellowF) {
      digitalWrite(redLightF, LOW);
      digitalWrite(yellowLightF, HIGH);
      digitalWrite(greenLightF, LOW);
            Serial.print("DistanceF: ");
  Serial.println(distanceF);
    } else {
      digitalWrite(redLightF, LOW);
      digitalWrite(yellowLightF, LOW);
      digitalWrite(greenLightF, HIGH);
            Serial.print("DistanceF: ");
  Serial.println(distanceF);
    }

    if (distanceS <= redS) {
      while (distanceS <= redS) {
        digitalWrite(redLightS, HIGH);
        digitalWrite(yellowLightS, LOW);
        digitalWrite(greenLightS, LOW);
        delay(100);
        digitalWrite(redLightS, LOW);
        digitalWrite(yellowLightS, LOW);
        digitalWrite(greenLightS, LOW);
        delay(100);
        rusms();
      }
    }
  } else {
    digitalWrite(redLightF, LOW);
    digitalWrite(yellowLightF, LOW);
    digitalWrite(greenLightF, LOW);
  }  //end of if reedAcitve
}  //end of void loop

void rusmf() {
  //Read Ultrasonic Module for Front of Car
  digitalWrite(trigPinF, LOW);          //Clears the trigPin
  delayMicroseconds(2);                 //Wait for 2 Micro seconds
  digitalWrite(trigPinF, HIGH);         //Set TrigPin to HIGH
  delayMicroseconds(10);                //Wait for 10 Micro Seconds
  digitalWrite(trigPinF, LOW);          //Set TrigPin back to LOW
  durationF = pulseIn(echoPinF, HIGH);  //Reads the echoPin, returns the sound wave travel time in microseconds
  distanceF = durationF * 0.034 / 2;    //Calculating the distance
  //End of Read Ultrasonic Module
  delay(2);  //This is need to what for pulseIN to get done
}

void rusms() {
  //Read Ultrasonic Module for Side of Car
  digitalWrite(trigPinS, LOW);          //Clears the trigPin
  delayMicroseconds(2);                 //Wait for 2 Micro seconds
  digitalWrite(trigPinS, HIGH);         //Set TrigPin to HIGH
  delayMicroseconds(10);                //Wait for 10 Micro Seconds
  digitalWrite(trigPinS, LOW);          //Set TrigPin back to LOW
  durationS = pulseIn(echoPinS, HIGH);  //Reads the echoPin, returns the sound wave travel time in microseconds
  distanceS = durationS * 0.034 / 2;    //Calculating the distance
  //End of Read Ultrasonic Module
  delay(2);  //This is need to what for pulseIN to get done
}

void rrss() {
  //Read Reed Switch
  reedPinValue = digitalRead(reedPin);
  if (reedPinValue == HIGH) {  //Serial.println("Switch closed");
    reedActive = 1;
  } else {  //Serial.println("Switch opened");
    reedActive = 0;
  }
  //End of Read Reed Switch
}