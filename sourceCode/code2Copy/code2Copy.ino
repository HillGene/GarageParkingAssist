/* 
  Code help from
  16x4 Character LCD Display = https://lastminuteengineers.com/arduino-1602-character-lcd-tutorial/
  Reed Switch = https://lastminuteengineers.com/reed-switch-arduino-tutorial/
  Ultrasonic = https://howtomechatronics.com/tutorials/arduino/ultrasonic-sensor-hc-sr04/
*/

//Library
#include <LiquidCrystal.h>

/* Pin Out Notes for 16x4 Character LCD Display
02 = VO (Display Contrast Pin) connected to Arduino Pin 2(PWM). Control contrast without a 10k potentiometer
03 = A (Anode LED) connected to Arduion Pin 3(PWM). Contol backlight brightness.
23 = RS (Register Select Pin)
25 = R/W (read/write Pin)
27 = E (Enable Pin)
29 = Data Pin 0
31 = Data Pin 1
33 = Data Pin 2
35 = Data Pin 3
37 = Data Pin 4
39 = Data Pin 5
41 = Data Pin 6
43 = Data Pin 7
*/

LiquidCrystal lcd(23, 25, 27, 29, 31, 33, 35, 37, 39, 41, 43); /* For 8-bit mode */
int backLight = 3;
int conlight = 2;

//Ultrasonic Sensor Values for Front of Car
const int redF = 100;     //Value for Red Light to turn on (Value in cm)
const int yellowF = 345;  //Value for Yellow Light to turn on (Value in cm)
const int greenF = 2500;  //Value for Green Light to turn on (Value in cm)
const int trigPinF = 3;   //Defines pin number
const int echoPinF = 2;   //Defines pin number
long durationF;           //Travel time, this is a Long variable
int distanceF;            //Integer variable for the distance

//Ultrasonic Sensor Values for Side of Car
const int redS = 10;     //Value for Red Light to turn on (Value in cm)
const int yellowS = 20;  //Value for Yellow Light to turn on (Value in cm)
const int greenS = 30;   //Value for Green Light to turn on (Value in cm)
const int trigPinS = 5;  //Defines pin number
const int echoPinS = 4;  //Defines pin number
long durationS;          //Travel time, this is a Long variable
int distanceS;           //Integer variable for the distance

//Reed Switch pre-setup
const int reedPin = 44;  //Defines pin number of Reed Switch
int reedPinValue;        //Store the value of the switch
int reedActive;          //Store the value of if ths Reed Switch is Active. Closed

//LED Strip Light Tower
const int redLightF = 4;
const int yellowLightF = 5;
const int greenLightF = 6;
const int blueLightS = 7;

void setup() {
  //LCD Setup
  lcd.begin(16, 4);             //Initialize Display
  lcd.clear();                  //Clear Display
  pinMode(backLight, OUTPUT);   //Setup pinMode for Displays Backlight.
  pinMode(conlight, OUTPUT);    //Setup pinMode for Contrast
  analogWrite(backLight, 255);  //Set Backlight
  analogWrite(conlight, 80);    //Set Contrast
  lcd.setCursor(3, 0);
  lcd.print("Welcome to");
  lcd.setCursor(0, 1);
  lcd.print("Garage Assistant");

  //pinMode Setup
  pinMode(trigPinF, OUTPUT);   //Set trigPin as a Output
  pinMode(echoPinF, INPUT);    //Set echoPin as a Input
  pinMode(trigPinS, OUTPUT);   //Set trigPin as a Output
  pinMode(echoPinS, INPUT);    //Set echoPin as a Input
  pinMode(reedPin, OUTPUT);    //Set reedpin as an Output
  pinMode(redLightF, OUTPUT);  //Set Red Light on LED Strip Light Tower
  pinMode(yellowLightF, OUTPUT); //Set Yellow Light on LED Strip Light Tower
  pinMode(greenLightF, OUTPUT); //Set Green Light on LED Strip Light Tower
  pinMode(blueLightS, OUTPUT); //Set Blue Light on LED Strip Light Tower
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
        digitalWrite(blueLightS, HIGH);
        delay(100);
        digitalWrite(blueLightS, LOW);
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
  delay(2);  //This is need to wait for pulseIN to get done
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