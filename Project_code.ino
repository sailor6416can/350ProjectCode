#include <Servo.h> //Servo motor library
#include <Stepper.h> //Stepper motor library

const int stepsPerRevolution = 200; // steps per revolution of our stepper

Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11); //create an instance of the stepper library
int sensorPin = 6;
int pinState; //the state of the bump switch
int stepper_position = 0;
//int servoPos = 0;    // variable to store the servo position
//int stepsPerLevel = 0; 
int powerLevel = 0; //power setting of the device
int userPowerLevel = 0;
int upButton = 5; // increase power pin
int downButton = 4; //decrease power pin
int fireButton = 3; //fire pin

    myservo.attach(7);  // attaches the servo on pin 9 to the servo object

    pinMode(upButton, INPUT); //takes the input of the up button
    pinMode(downButton, INPUT); //takes the input of the down button
    pinMode(fireButton, INPUT); //takes the input of the fire button
    pinMode(sensorPin, INPUT); // takes the input of bump switch sensor
    Serial.begin(9600);
    // set the speed at 60 rpm:
	myStepper.setSpeed(60);
	// initialize the serial port:
	Serial.begin(9600);

bool bumpSwitch(){
  pinState = digitalRead(sensorPin);
  if(pinState == true){
      return true;
    }else{
      return false;
    }
    return false;
}

void launch(){
    for (pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 180 degrees
        //    // in steps of 1 degree
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(15);                       // waits 15ms for the servo to reach the position
    }
}

pinState = digitalRead(sensorPin);
void setup(){
    
    while(bumpSwitch() == false){
        //bump switch is not pressed
        Serial.println("clockwise");
	    myStepper.step(stepsPerRevolution);
        delay(50);
        pinState = digitalRead(sensorPin);
    }
    powerLevel = 15;
    //consider doing an initialization sequence for the servo
}

void loop() {
    if(userPowerLevel == powerLevel && powerLevel <= 15 && powerLevel >= 0){
        launch();
    }
  if(((userPowerLevel > powerLevel) || (userPowerLevel > powerLevel)) && powerLevel <= 15 && powerLevel >= 0){
        powerLevel = userPowerLevel;
    }

}