#include <Servo.h> //Servo motor library
#include <Stepper.h> //Stepper motor library
#include "Arduino_SensorKit.h" //OLED Screen library

const int stepsPerRevolution = 200; // steps per revolution of our stepper

Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11); //create an instance of the stepper library
int sensorPin = 6; //bump switch pin position
int servo_position = 0; 
//int servoPos = 0;    // variable to store the servo position
//int stepsPerLevel = 0; 
int powerLevel = 0; //power setting of the device
int userPowerLevel = 0;
int upButton = 5; // increase power pin
int downButton = 4; //decrease power pin
int fireButton = 3; //fire pin

Servo myservo;

bool bumpSwitch(){
	int pinState; //the state of the bump switch
  pinState = digitalRead(sensorPin);
  if(pinState == true){
      return true;
    }else{
      return false;
    }
    return false;
}

bool upSwitch(){
	int pinState; //the state of the bump switch
  pinState = digitalRead(sensorPin);
  if(pinState == true){
      return true;
    }else{
      return false;
    }
    return false;
}

bool downSwitch(){
	int pinState; //the state of the bump switch
  pinState = digitalRead(sensorPin);
  if(pinState == true){
      return true;
    }else{
      return false;
    }
    return false;
}

bool fireSwitch(){
	int pinState; //the state of the bump switch
  	pinState = digitalRead(fireButton);
	
	if(pinState == true){
		return true;
	}else{
		return false;
	}
	return false;
}

void launch(){

    for (servo_position = 0; servo_position <= 90; servo_position += 1) { // goes from 0 degrees to 180 degrees
        //    // in steps of 1 degree
        myservo.write(servo_position);              // tell servo to go to position in variable 'pos'
        delay(15);                       // waits 15ms for the servo to reach the position
    }
}

void setup(){

    pinMode(upButton, INPUT); //takes the input of the up button
    pinMode(downButton, INPUT); //takes the input of the down button
    pinMode(fireButton, INPUT); //takes the input of the fire button
    pinMode(sensorPin, INPUT); // takes the input of bump switch sensor
    Serial.begin(9600);
    // set the speed at 60 rpm:
	myStepper.setSpeed(60);
	// initialize the serial port:
	Serial.begin(9600);
  myservo.attach(7);  // attaches the servo on pin 7 to the servo object

    while(bumpSwitch() == false){
        //bump switch is not pressed
        Serial.println("clockwise"); //moves trigger system towards stepper
	      myStepper.step(20);
        delay(15);
    }
	myStepper.step(-20);//moves trigger system away from stepper (to slightly move away from bump switch)
	powerLevel = 15;
    //consider doing an initialization sequence for the servo
	Oled.begin();
  Oled.setFlipMode(true); // Sets the rotation of the screen
}

void loop() {

	int random_value = analogRead(A0);   //read value from A0
	
	if(userPowerLevel == powerLevel && powerLevel <= 15 && powerLevel >= 0 && fireSwitch() == true){
		Oled.print(powerLevel);
		Oled.print("Launch!");
		launch();
    Serial.println("launch");
	}
	
	if(upSwitch() == true){
		userPowerLevel++;
		Oled.setFont(u8x8_font_chroma48medium8_r); 
  	Oled.setCursor(0, 33);    // Set the Coordinates 
  	Oled.print("Power Value:");
		Oled.print(userPowerLevel); // Print the Values  
    Oled.refreshDisplay();    // Update the Display
    Serial.println("up switch"); 
		delay(1000);
	}
	
	if(downSwitch() == true){
		userPowerLevel--;
		Oled.setFont(u8x8_font_chroma48medium8_r); 
  		Oled.setCursor(0, 33);    // Set the Coordinates 
  		Oled.print("Analog Value:");
		Oled.print(userPowerLevel); // Print the Values
    Oled.refreshDisplay();    // Update the Display 
    Serial.println("down switch"); 
		delay(1000);
	}
	
	if((userPowerLevel > powerLevel) && powerLevel <= 15 && powerLevel >= 0){
		int n = userPowerLevel - powerLevel;
		Serial.println("clockwise"); //moves the trigger system backwards
		myStepper.step(n*433);
        	powerLevel = userPowerLevel;
          Serial.println("increaseing power"); 
  	}

	if((userPowerLevel < powerLevel) && powerLevel <= 15 && powerLevel >= 0){
		int n = powerLevel - userPowerLevel;
		Serial.println("counterclockwise"); //moves the trigger system forward
		myStepper.step(-n*433);
        	powerLevel = userPowerLevel;
          Serial.println("decreaseing power"); 
	}

}
