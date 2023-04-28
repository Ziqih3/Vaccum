#include "motor.h"
using namespace std;
void motor::setup() {

	pinMode(enA, OUTPUT);
	pinMode(enB, OUTPUT);
	pinMode(in1, OUTPUT);
	pinMode(in2, OUTPUT);
	pinMode(in3, OUTPUT);
	pinMode(in4, OUTPUT);

	pinMode(enA_L, OUTPUT);
	pinMode(enB_L, OUTPUT);
	pinMode(in1_L, OUTPUT);
	pinMode(in2_L, OUTPUT);
	pinMode(in3_L, OUTPUT);
	pinMode(in4_L, OUTPUT);
 
  pinMode(enB_Fl, OUTPUT);
  pinMode(in1_F1, OUTPUT);
  pinMode(in2_F1, OUTPUT);
  pinMode(enB_FR, OUTPUT);
  pinMode(in1_FR, OUTPUT);
  pinMode(in2_FR, OUTPUT);


  digitalWrite(in1_F1, LOW);
  digitalWrite(in2_F1, LOW);
  digitalWrite(in1_FR, LOW);
  digitalWrite(in2_FR, LOW);

	digitalWrite(in1, LOW);
	digitalWrite(in2, LOW);
	digitalWrite(in3, LOW);
	digitalWrite(in4, LOW);


	digitalWrite(in1_L, LOW);
	digitalWrite(in2_L, LOW);
	digitalWrite(in3_L, LOW);
	digitalWrite(in4_L, LOW);

	// setup ultrasonic R
	pinMode(trigPin_1, OUTPUT);
	pinMode(echoPin_1, INPUT);

	// setup ultrasonic L
	pinMode(trigPin_2, OUTPUT);
	pinMode(echoPin_2, INPUT);
};


// control omni-wheels spinning direction
void motor::directionControl_left() {
	
	  // R1 & L2 are same
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3_L, LOW);
  digitalWrite(in4_L, HIGH);
  // R2 & L1 are same
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  digitalWrite(in1_L, LOW);
  digitalWrite(in2_L, HIGH);

    digitalWrite(in1_F1, HIGH);
  digitalWrite(in2_F1, LOW);
  digitalWrite(in1_FR, HIGH);
  digitalWrite(in2_FR, LOW);
	

};



void motor::directionControl_right() {
  // R1 & L2 are same
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3_L, HIGH);
  digitalWrite(in4_L, LOW);

  // R2 & L1 are same
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  digitalWrite(in1_L, HIGH);
  digitalWrite(in2_L, LOW);

    digitalWrite(in1_F1, HIGH);
  digitalWrite(in2_F1, LOW);
  digitalWrite(in1_FR, HIGH);
  digitalWrite(in2_FR, LOW);
};



void motor::directionControl_forward() {

	digitalWrite(in1, HIGH);
	digitalWrite(in2, LOW);
	digitalWrite(in3, LOW);
	digitalWrite(in4, HIGH);

	digitalWrite(in3_L, HIGH);
	digitalWrite(in4_L, LOW);
	digitalWrite(in1_L, LOW);
	digitalWrite(in2_L, HIGH);
  
  digitalWrite(in1_F1, HIGH);
  digitalWrite(in2_F1, LOW);
  digitalWrite(in1_FR, HIGH);
  digitalWrite(in2_FR, LOW);
  
};

void motor::directionControl_backward() {

	digitalWrite(in1, LOW);
	digitalWrite(in2, HIGH);
	digitalWrite(in3, HIGH);
	digitalWrite(in4, LOW);

	digitalWrite(in3_L, LOW);
	digitalWrite(in4_L, HIGH);
	digitalWrite(in1_L, HIGH);
	digitalWrite(in2_L, LOW);
};

double motor::ultra_output_1() {
	// The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
	// Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
	digitalWrite(trigPin_1, LOW);
	delayMicroseconds(2);
	digitalWrite(trigPin_1, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigPin_1, LOW);
	double duration = pulseIn(echoPin_1, HIGH);
	// convert the time into a distance
	return duration / (29) / 2;;
};


double motor::ultra_output_2() {
	// The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
	// Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
	digitalWrite(trigPin_2, LOW);
	delayMicroseconds(2);
	digitalWrite(trigPin_2, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigPin_2, LOW);
	//duration = pulseIn(echoPin_2, HIGH);
	double duration = pulseIn(echoPin_2, HIGH);

	// convert the time into a distance
	return duration / 29 / 2;
};


void motor::move_to_right(double cm_1, bool stop, bool step_done, double ratio) {
	if (cm_1 >= 30) {
		directionControl_right();
		speedControl(125);

		Serial.print("Moving Right; ");
	}
	else if (cm_1 < 30 && cm_1 >= 5) {
		// map from distance to 0 and 255
		double speed = map(cm_1, 5, 30, 0, 128);
		
		directionControl_right();
		speedControl(speed);

		Serial.print("Moving Right; ");

	}
	else {
		speedControl(0);
		Serial.print("STOPPED; ");
		stop = true;
		step_done = false;
	}
};

void motor::move_to_left(double cm_2, bool stop, bool step_done,double ratio) {
	if (cm_2 >= 30) {
		ratio = 255;
		speedControl(ratio);
		directionControl_left();
		Serial.print("Moving Left; ");
	}
	else if (cm_2 < 30 && cm_2 >= 5) {
		// map from distance to 0 and 255
		ratio = map(cm_2, 5, 30, 0, 128);
		speedControl(ratio);
		directionControl_left();
		Serial.print("Moving Left; ");

	}
	else {
		speedControl(0);
		step_done = 1;
		stop = 1;
		Serial.print("STOPPED; ");
	}

};

void motor::speedControl(int speed) {

	analogWrite(enA, speed);  //enA R2 r2 80
	analogWrite(enB, speed);  //enB R1

	analogWrite(enA_L, speed);  //enA_L L1

	analogWrite(enB_L, speed);  //enA_L L2
  analogWrite(enB_Fl,speed);
  analogWrite(enB_FR,speed);

}
void motor::leftspeedControl(int speed) {
  analogWrite(enA, 255);  //enA R2  80
  analogWrite(enB, 255);  //enB R1

  analogWrite(enA_L, 255);  //enA_L L1

  analogWrite(enB_L, 255);  //enA_L L2
  
  analogWrite(enB_Fl, 0);  //enA_L L1

  analogWrite(enB_FR, 0);  //enA_L L2
}

 void motor::rightspeedControl(int speed){
  analogWrite(enA, 225);  //enA R2  80
  analogWrite(enB, 120);  //enB R1

  analogWrite(enA_L, 255);  //enA_L L1

  analogWrite(enB_L, 120);  //enA_L L2
  
  analogWrite(enB_Fl, 110);  //enA_L L1

  analogWrite(enB_FR, 150);  //enA_L L2
}
