// motor.h



#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif
class motor {
private:
	// Motor R1 connections
	const int enA = 4;
	const int in1 = 26;
	const int in2 = 27;
	// Motor R2 connections

	const int enB = 5;
	const int in3 = 28;
	const int in4 = 29;

	// Motor L1 connections
	const int enA_L = 3;
	const int in3_L = 24;
	const int in4_L = 25;

	// Motor L2 connections
	const int enB_L = 2;
	const int in1_L = 23;
	const int in2_L = 22;

 //Motor FL
  const int enB_Fl = 8;
  const int in1_F1 = 32;
  const int in2_F1 = 33;
//Motor FR
  const int enB_FR = 7;
  const int in1_FR = 30;
  const int in2_FR = 31;

  

	// ultrasonic 1 - R
	const int trigPin_1 = 23;
	const int echoPin_1 = 22;

	// ultrasonic 2 - L
	const int trigPin_2 = 13;
	const int echoPin_2 = 12;

public:
	void setup();

	void directionControl_left() ;
	void directionControl_right() ;

	void directionControl_forward() ;
	void directionControl_backward() ;



  
	double ultra_output_1() ;
	double ultra_output_2() ;

	void move_to_right(double cm_1,bool stop,bool step_done, double ratio) ;
	void move_to_left(double cm_2, bool stop, bool step_done, double ratio) ;

	void speedControl(int ratio) ;
  void leftspeedControl(int speed);
  void rightspeedControl(int speed);

};
