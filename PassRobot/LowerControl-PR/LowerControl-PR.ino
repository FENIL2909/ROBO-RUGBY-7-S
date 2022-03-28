
#include <EasyTransfer.h>
#include <DueTimer.h>
#include <DuePWM.h>

#define SerialX SerialUSB


#define N 3
#define TimerEncoder Timer1
#define UpperLowerSerial Serial3
#define PWM_FREQ1 2500
#define EncoderTime 0.1

#define maxMotRPM 460
#define maxWheelRPM 460
#define maxPWM 255
#define baserpm 0
#define RPMToVelocity(x) (2*pi*RadiusOmniWheel*x)/60
#define maxRobotVelocity 1.2*RMPToVelocity(maxWheelRPM)


#define pi 3.141592653589
#define DegreeToRadian(x) x*0.0174532  
#define RadianToDegree(x) x*57.295779

#define RadiusOmniDrive  29.5 //centimetre
#define RadiusOmniWheel 7.5 //centimetre
#define VelocityToRPM(x) x*60/(2*pi*RadiusOmniWheel) //vel in cm/s

#define Angle1 0   //1.57079  //90       //90+0
#define Angle2 120  //3.66519  //210      //90+120
#define Angle3 240  //5.75958  //330      //90+240
//#define Angle4 315  //

#define redLEDon digitalWrite(A10,HIGH)
#define redLEDoff digitalWrite(A10,LOW)

DuePWM pwm(PWM_FREQ1, 3000);

EasyTransfer ET;

struct DATASTRUCT {
  float omega;
  float velocity;
  float theta;
};
DATASTRUCT mydata;

class Wheel {
  public:
    float translationSpeed;
    float angularSpeed;
    int angle;
    float maxRPM;
    float Speed;
    float rpm;
    int prevRPM;
};

Wheel Wheel1 = {0.0, 0.0, Angle1, maxWheelRPM, 0, 0, 0 }; 
Wheel Wheel2 = {0.0, 0.0, Angle2, maxWheelRPM, 0, 0, 0 }; 
Wheel Wheel3 = {0.0, 0.0, Angle3, maxWheelRPM, 0, 0, 0 }; 
//Wheel Wheel4 = {0.0, 0.0, Angle4, maxWheelRPM, 0, 0, 0 }; 

//Wheel *pWheel[4] = {&Wheel1, &Wheel2, &Wheel3, &Wheel4};
Wheel *pWheel[3] = {&Wheel1, &Wheel2, &Wheel3};
class Encoder
{
  public:
    int channel1;
    int channel2;
    int ppr;
    volatile long long int Count;
    volatile long long int prevCount;
    int rpm;
    float gearRatio;
    void initEncoder() {
      pinMode(channel1, INPUT);
      pinMode(channel2, INPUT);
    }
};

Encoder encoder1 = {48, 50, 135, 0, 0, 0, 1.0} ,   *pEncoder1 = &encoder1;
Encoder encoder2 = {53, 52, 135, 0, 0, 0, 1.0} ,   *pEncoder2 = &encoder2;
Encoder encoder3 = {51, 47, 135, 0, 0, 0, 1.0} ,   *pEncoder3 = &encoder3;
//Encoder encoder4 = {45, 43, 135, 0, 0, 0, 1.0} ,   *pEncoder4 = &encoder4;

//Encoder *pEncoder[N] = {&encoder1, &encoder2, &encoder3, &encoder4};
Encoder *pEncoder[N] = {&encoder1, &encoder2, &encoder3};

void returnCount1();
void returnCount2();
void returnCount3();
//void returnCount4();

class Motor {
  public:
    int direction1;
    int direction2;
    int pwmPin;

    void initMotor() {
      pinMode(direction1, OUTPUT);
      pinMode(pwmPin, OUTPUT);
      pinMode(direction2, OUTPUT);
      digitalWrite(direction1, LOW);
      digitalWrite(direction2, LOW);
    }
};


//Motor motor1 = {25,23, 8};
//Motor motor2 = {27,29, 7};   
//Motor motor3 = {33,35, 6};
//Motor motor4 = {39,37, 9};
Motor motor1 = {39,37, 9};
Motor motor2 = {35,33, 8};   
Motor motor3 = {29,27, 7};
//Motor *pMotor[N] = {&motor1, &motor2, &motor3, &motor4};
Motor *pMotor[N] = {&motor1, &motor2, &motor3};
/*********************************************************************************************************************************************/
/******************************************************       PID          ***************************************************************************************/

class PID {
  public:
    float Kp;
    float Kd;
    float Ki;
    float maxControl;
    float minControl;
    
    float required;
    float prevRequired;
    float error;
    float prevError;
    float derivativeError;
    float integralError;
    float prev_integralError;
    void initPID(float kp, float kd, float ki, float req, float minV, float maxV);
    float pidControl(float actual);

};

PID PIDMotor1;
PID *pPIDMotor1 = &PIDMotor1;

PID PIDMotor2;
PID *pPIDMotor2 = &PIDMotor2;

PID PIDMotor3;
PID *pPIDMotor3 = &PIDMotor3;

//PID PIDMotor4;
//PID *pPIDMotor4 = &PIDMotor4;

//PID *pPIDMotor[N] = {&PIDMotor1, &PIDMotor2, &PIDMotor3, &PIDMotor4};
PID *pPIDMotor[N] = {&PIDMotor1, &PIDMotor2, &PIDMotor3};


//////////////////////////////////////////////////Global variables****************************************************
float output[N];
int softBrake = 1, directionChange = 0;

void setup() {
  
  pinMode(A10,OUTPUT);
  redLEDon;
  UpperLowerSerial.begin(115200);
  ET.begin(details(mydata), &UpperLowerSerial);
  
  for (int i = 0; i < N; ++i)
    pMotor[i]->initMotor();

  pwm.setFreq1(PWM_FREQ1);

  for (int i = 0; i < N; ++i)
    pwm.pinFreq1(pMotor[i]->pwmPin);

  for (int i = 0; i < N; ++i)
    pEncoder[i]->initEncoder();

  attachInterrupt(pEncoder1->channel1, returnCount1, RISING);
  attachInterrupt(pEncoder2->channel1, returnCount2, RISING);
  attachInterrupt(pEncoder3->channel1, returnCount3, RISING);
//  attachInterrupt(pEncoder4->channel1, returnCount4, RISING);

  TimerEncoder.attachInterrupt(timerHandler);
  TimerEncoder.start(1000000 * EncoderTime);

  pPIDMotor1->initPID(1.5, 0.0, 0, 0, -baserpm, maxMotRPM - baserpm);//4.2 1.2
  pPIDMotor2->initPID(1.5, 0.0, 0, 0, -baserpm, maxMotRPM - baserpm);//1.1 
  pPIDMotor3->initPID(1.5, 0.0, 0, 0, -baserpm, maxMotRPM - baserpm);//2.0
//  pPIDMotor4->initPID(2.0, 0.0, 0, 0, -baserpm, maxMotRPM - baserpm);//1.1

}

float linearV =0, angularV =0, angleTheta =0 ;
int ledCntr=0;
void loop() 
{ 
getUpperData();
//printCount();
//set_rpm(300);
//motorTest(150);
//plotRPM();
}


void timerHandler()
{
  for(int i = 0; i < N; ++i)
    pEncoder[i]->rpm = ((pEncoder[i]->Count - pEncoder[i]->prevCount) * 60.0) / (EncoderTime * pEncoder[i]->gearRatio * pEncoder[i]->ppr);

  for(int i = 0; i < N; ++i)
    pEncoder[i]->prevCount = pEncoder[i]->Count;

  for(int i = 0; i < N; ++i)
  {
    if(pPIDMotor[i]->required * pPIDMotor[i]->prevRequired > 0 && !directionChange)
      output[i] = baserpm + pPIDMotor[i]->pidControl(pEncoder[i]->rpm);
    else if(pPIDMotor[i]->required * pPIDMotor[i]->prevRequired == 0)
    {
      softBrake = 0;
      output[i] = 0;
    }
    else
    {
      pPIDMotor[i]->prevRequired = pPIDMotor[i]->required;
      softBrake = 1;
      output[i] = 0;
      if(abs(pEncoder[i]->rpm) < 5)//
      directionChange = 1;
      else
        directionChange = 0;
    }
  }
  
  for(int i = 0; i < N; ++i)
    driveMotorReq(output[i], pPIDMotor[i], pMotor[i], maxMotRPM);
}
