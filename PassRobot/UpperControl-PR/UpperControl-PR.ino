#include <LiquidCrystal.h>
#include <UltrasonicSensor.h>
#include <EasyTransfer.h>
#include <TimerOne.h>
#include <Servo.h>
#include <Wire.h>
#include <Adafruit_MCP4725.h>
Adafruit_MCP4725 dac;
UltrasonicSensor ultrasonic(53 , 51);
enum {BLUE = 1, RED = -1};
int arena = RED ;
const int rs = 8, en = 9, d4 = 10, d5 = 11, d6 = 12, d7 = 13;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

EasyTransfer ETUpperLower, ETMpu, ETPlot, ETAgentPR_TR;//, ETAgentTR;

struct DATASTRUCT {
  float omega;
  float velocity;
  float theta;
};
DATASTRUCT mydata;

struct MPU {
  float robotYaw;
};
MPU mympu;
bool flagStop=0;
long int countYaw = 0;    
float initialRobotYaw;

struct PLOT {
  float x;
  float y;
};
PLOT myplot;

struct MULTIAGENT {
      int stateChange;
};
MULTIAGENT agentPR, agentTR;

#define UpperLowerSerial Serial2
#define MPUSerial  Serial2
#define BluetoothSerial Serial3
#define BluetoothSerial2 Serial1
#define CollabSerial Serial1

#define pi 3.141592653589
#define temperature  27

#define DegreeToRadian(x) x*0.0174532
#define RadianToDegree(x) x*57.295779

#define RadiusXYWheel   2.9 //centimetre
#define maxWheelRPM 400
#define RadiusOmniDrive 37.5  //centimetre
#define RadiusOmniWheel 5.0 //centimetre
 
#define VelocityToRPM(x) x*60/(2*pi*RadiusOmniWheel) //vel in cm/s
#define RPMToVelocity(x) (2*pi*RadiusOmniWheel*x)/60


#define redLEDoff digitalWrite(A4,LOW);
#define redLEDon digitalWrite(A4,HIGH);
#define yellowLEDon digitalWrite(A6, HIGH)
#define yellowLEDoff digitalWrite(A6, LOW)
#define greenLEDon digitalWrite(A5, LOW)
#define greenLEDoff digitalWrite(A5, HIGH)
#define buzzOn digitalWrite(A7,HIGH)
#define buzzOff digitalWrite(A7,LOW)

////////////////////////////////actuation//////////////////////////////
#define IRpin A15
#define MotorPin1 53
#define MotorPin2 47
#define MotorPWM 51
#define gripperUp A12
#define gripperDown A11
#define throwBall A10
#define rstButton 7

int actuationFlag = 0;
int readIR = 0;
int actuationCounter = 0;
float Tup = 0;
float Tgrip = 0;
float Tdrop = 0;
float Tthrow = 0;
float Tdown = 0;

////////////////////////////////////////////////////////////////////

class Encoder
{
  public:
    int channel1;
    int channel2;
    int ppr;
    volatile long long int Count;
    volatile long long int prevCount;
    int rpm;

    Encoder(int ch1, int ch2, int ppR) {
      channel1 = ch1;
      channel2 = ch2;
      ppr = ppR;
      Count = 0;
      prevCount = 0;
      rpm = 0;
      pinMode(channel1, INPUT_PULLUP);
      pinMode(channel2, INPUT_PULLUP);
    }
};
Encoder xencoder(2, 4, 1000);
Encoder *pEncoderX = &xencoder;

Encoder yencoder(3, 5, 1000);
Encoder *pEncoderY = &yencoder;




/*********************************************************************************************************************************************/
/*********************************************************** Autonomous Bot **********************************************************************************/
class Auto_Bot {
  public:
    volatile float X_pos;
    volatile float Y_pos;
    volatile float X_pos1;
    volatile float Y_pos1;
    volatile float del_x;
    volatile float del_y;
    float Angle;
    float vel;
    float Omega;
    volatile float prev_X;
    volatile float prev_Y;
    Auto_Bot() {
      X_pos = 0;
      Y_pos = 0;
      X_pos1 = 0;
      Y_pos1 = 0;
      del_x = 0;
      del_y = 0;
      Angle = 0;
      prev_X = 0;
      prev_Y = 0;
      vel = 0;
    }
};

Auto_Bot fourWheelDrive;
Auto_Bot *pBot = &fourWheelDrive;

class PID {
  public:
    float Kp;
    float Kd;
    float Ki;
    float Kp_old;
    float Kd_old;
    float Ki_old;
    float maxControl;
    float minControl;

    float required;
    float prevRequired;
    float error;
    float prevError;
    float derivativeError;
    float integralError;
    void initPID(float kp, float kd, float ki, float req, float minV, float maxV);
    float pidControl(float actual);

};

PID pidDistance;
PID *ppidDistance = &pidDistance;

PID pidOmega;
PID *ppidOmega = &pidOmega;

PID pidCircle;
PID *ppidCircle = &pidCircle;

PID pidRoller;
PID *ppidRoller = &pidRoller;

PID pidCollaborateX;
PID *ppidCollaborateX = &pidCollaborateX;

PID pidCollaborateY;
PID *ppidCollaborateY = &pidCollaborateY;


float prevDistLeft = 1000;

enum {forward, backward, stopp};

class Motor {
  public:
    int direction1;
    int direction2;
    int pwmPin;

    Motor(int dir1, int dir2, int pwmP) {
      direction1 = dir1;
      direction2 = dir2;
      pwmPin = pwmP;

      pinMode(direction1, OUTPUT);
      pinMode(pwmPin, OUTPUT);
      pinMode(direction2, OUTPUT);
      digitalWrite(direction1, LOW);
      digitalWrite(direction2, LOW);
    }

    void actuateMotor(int pwmm, uint8_t directionn)   //forward, backward, stopp
    {
      if (directionn != stopp)
      {
        digitalWrite(direction1, !directionn);
        digitalWrite(direction2, directionn);
      }
      else
      {
        digitalWrite(direction1, HIGH);
        digitalWrite(direction2, HIGH);
      }

      analogWrite(pwmPin, pwmm);
    }
};
float finalVelo = 0.0;
//////////////////////////////////////////////////  PS2 ///////////////////////////////////////////////////////////////
#define __AVR__
#include <PS2X_lib.h>

#include <SPI.h>
#define PS3
#define basePS2_Y 128.0
#define wirelessdelay 0
#ifdef PS3
#define wirelessdelay 50
#define basePS2_Y 127.0
#endif

PS2X ps2x;
EasyTransfer ET_ps2;

struct PS2_data {
  int32_t ps2data;
  uint8_t Rx;
  uint8_t Ry;
  uint8_t Lx;
  uint8_t Ly;
};
PS2_data data;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


enum {STOP, CONTINUE};
enum {clockwise = 1 , antiClockwise = -1};
enum {accelerate, decelerate, constant, accdec};
enum {waitForCommand , ballAhead, touchWall, nearBall, grip, towardsThrowing, throwing, towardsFence, towardsKick, nearKick, readyToKick,pointOfKick ,kick, forNextBall, towardsNextBall};
enum {TowardsStart = 0 , BallPlacing,BallPlacing2,TowardsKick  , kicking , BackToRecieving , stoppp};
enum {WaitForArenaSelect ,WaitForRef ,towardsWallReset,touchWall2,SignalToPick,TowardsBall,gripBall,towardsStart,StartReset,WaitForPassSignal};
uint8_t state = WaitForArenaSelect;
int speedMode = constant;
long long int timerPS2=0;

bool botStop = 0, collabFlag = 0;
bool fsmFlag;

float  shiftX = 0, shiftY = 0;//(- 582, 735.0)  ( - 565.5, 690.0 )  (-51.5,44.64)
float minSpeed = 0, maxSpeed = 0;
float BotX = shiftX, BotY = shiftY, prevBotX = 0, prevBotY = 0;
float botTheta = 0;
float robotYaw = 0.0, omegacontrol = 0.0, speeed = 0;
float del_yaw = 0.0, prev_yaw = 0.0;

void setup() {
  
  dac.begin(0x60);
  dac.setVoltage(1350,true);

  pinMode(A4, OUTPUT);
  pinMode(A5, OUTPUT);
  pinMode(A6, OUTPUT);
  pinMode(A7, OUTPUT);

  pinMode(IRpin, INPUT);
  pinMode(rstButton, INPUT_PULLUP);
  pinMode(gripperUp, OUTPUT);
  pinMode(gripperDown, OUTPUT);
  pinMode(throwBall, OUTPUT);
  pinMode(MotorPin1,OUTPUT);
  pinMode(MotorPin2,OUTPUT);
  pinMode(MotorPWM,OUTPUT);


  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

//  ultrasonic.setTemperature(temperature);


  Serial.begin(9600);

  UpperLowerSerial.begin(115200);
  ETUpperLower.begin(details(mydata), &UpperLowerSerial);


  MPUSerial.begin(115200);
  ETMpu.begin(details(mympu), &MPUSerial);

  BluetoothSerial.begin(38400);
  ET_ps2.begin(details(data), &BluetoothSerial);

//   BluetoothSerial2.begin(38400);
//    ETPlot.begin(details(myplot), &BluetoothSerial2);
  //
    CollabSerial.begin(115200);
    ETAgentPR_TR.begin(details(agentTR), &CollabSerial);
//    ETAgentTR.begin(details(agentTR), &CollabSerial);

  mydata = {0, 0, 0};
  mympu = {0};
  agentPR = {1};
  agentTR = {0};

  ETUpperLower.sendData();

  attachInterrupt(digitalPinToInterrupt(pEncoderX->channel1), returnCountX, RISING);
  attachInterrupt(digitalPinToInterrupt(pEncoderY->channel1), returnCountY, RISING);

  interrupts();
  //  ETAgentPR.sendData();

  // p d i req min max
  ppidOmega->initPID(0.275,6, 0, 0, -2, 2);//0.275,0.45
  ppidDistance->initPID(5.0, 0, 0, 0, -200, 200);
  ppidCircle->initPID(5.0, 0, 0, 0, -200, 200);
  ppidRoller->initPID(250, 200, 0, 0, -200, 200);
  ppidCollaborateX->initPID(0, 0, 0, 0, -375, 375);
  ppidCollaborateY->initPID(0, 0, 0, 0, -375, 375);

  Serial.println("Setup");
  minSpeed = 100;
  maxSpeed = 300;
  redLEDon;

  
}

int aa = 0;
bool directionFlag = 1;

void loop()
{
//actuation(10, 200);

//digitalWrite(A10 , HIGH);
//digitalWrite(A11 , HIGH);
//digitalWrite(A12 , HIGH);
//aa = digitalRead(rstButton);
//
//if(!aa)
//{
//  digitalWrite(A10 , LOW);
//}


//  
//  redLEDon;
//  if(!digitalRead(rstButton) && !actuationFlag)
//  {
//    actuationCounter++;
//    if(actuationCounter > 35)
//    {
//      actuationFlag = 1;
//      actuationCounter = 0;
//      aa = millis();
//      directionFlag = !directionFlag;
//    }
//  }
//  if(actuationFlag == 1)
//  {
//    if(millis() - aa < 250)
//    {
//      digitalWrite(MotorPin1,directionFlag);
//      digitalWrite(MotorPin2,!directionFlag);
//      digitalWrite(MotorPWM,HIGH);
//    }
//    else
//    {
//      actuationFlag = 0;
//      if(directionFlag)
//      {
//        digitalWrite(MotorPin1,0);
//        digitalWrite(MotorPin2,0);
//        digitalWrite(MotorPWM,0);  
//      }
//    }
//  }
    
 
   
  
  //x 10
  //y 130
  readIR = digitalRead(A15);
  digitalWrite(A10,HIGH);
  digitalWrite(A11,HIGH);
  digitalWrite(A12,HIGH);
  handleXY();
  if(actuationFlag == 0)
  {
    calculateSpeed(-omegacontrol,DegreeToRadian(150),200);
    if(!readIR)
    {
      calculateSpeed(-omegacontrol,0,0);
      actuationFlag = 1;
    }
  }
  else if(actuationFlag == 1)
  {
    digitalWrite(51,HIGH);
    digitalWrite(53,LOW);
    digitalWrite(47,HIGH);
    aa ++;
    if(aa > 200)
    {
     digitalWrite(A12, LOW); 
     Tup = millis();
     actuationFlag = 2;
    }
  }
  else if(actuationFlag == 2)
  {
    if(millis() - Tup > 2000)
    {
      
      traceLine(BotX, BotY, BotX + 10, BotY - 140, 200, STOP, constant, 5);
      if(abs(prevBotX - BotX) < 0.1 && abs(prevBotY - BotY) < 0.1)
      {
        actuationCounter ++;
        if(actuationCounter > 100)
        {
        actuationFlag = 3;
        Tdrop = millis();
        }
      }
    }
  }
  else if(actuationFlag == 3)
  {
    calculateSpeed(-omegacontrol,0,0);
    digitalWrite(51,HIGH);
    digitalWrite(53,HIGH);
    digitalWrite(47,LOW);
    if(millis() - Tdrop > 500) 
    {
      digitalWrite(51,LOW);
      digitalWrite(53,LOW);
      digitalWrite(47,LOW);
      digitalWrite(A11, LOW);
      Tdown = millis();
      actuationFlag = 4;
    }
  }
  else if(actuationFlag == 4)
  {
    if(millis() - Tdown > 5000)
    {
      digitalWrite(A10, LOW);
      actuationFlag = 5;
    }
  }
  else
  {
    calculateSpeed(-omegacontrol,0,0);
  }

//  traceCircle(100, 0, 0, 0, 100, antiClockwise , 250, STOP,0);  
//    calculateSpeed(-omegacontrol,0,0);
//FinalFSM(); 
//ETAgentPR_TR.sendData();
}
