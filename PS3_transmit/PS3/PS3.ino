/*
 Example sketch for the PS3 Bluetooth library - developed by Kristian Lauszus
 For more information visit my blog: http://blog.tkjelectronics.dk/ or
 send me an e-mail:  kristianl@tkjelectronics.com
 */

#include <PS3BT.h>
#include <usbhub.h>
#include <EasyTransfer.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

#define baseLeft_Y 120.0
#define baseLeft_X 126.0

#define baseRight_Y 127.0
#define baseRight_X 128.0

#define BluetoothSerial Serial2

USB Usb;
//USBHub Hub1(&Usb); // Some dongles have a hub inside

BTD Btd(&Usb); // You have to create the Bluetooth Dongle instance like so
/* You can create the instance of the class in two ways */
PS3BT PS3(&Btd); // This will just create the instance
//PS3BT PS3(&Btd, 0x00, 0x15, 0x83, 0x3D, 0x0A, 0x57); // This will also store the bluetooth address - this can be obtained from the dongle when running the sketch

bool printTemperature, printAngle;

struct PS3_data {
  int ps3data;
  int LD;
  int LT;
  int RD;
  int RT;
};
PS3_data data;

enum value {noData, leftx, upx, rightx, downx, selectx, psx, startx, squarex, trianglex, circlex, crossx, l1x, l2x, l3x, r1x, r2x, r3x};
value PS3Val = noData;

EasyTransfer ET_ps3;
double xSquare_leftdistance = 0, ySquare_leftdistance = 0, xSquare_rightdistance = 0, ySquare_rightdistance = 0, xCircle_leftdistance = 0, yCircle_leftdistance = 0, xCircle_rightdistance = 0, yCircle_rightdistance = 0;
double LeftAnalogTheta = 0, RightAnalogTheta = 0;
float LeftAnalogDistance = 0, RightAnalogDistance = 0;
const float pi = 3.14159;

void setup() {
  Serial.begin(115200);
  BluetoothSerial.begin(115200);
  ET_ps3.begin(details(data),&BluetoothSerial);
  
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nPS3 Bluetooth Library Started"));
}

void loop() {
  Usb.Task();
  ps3_funcs();
  
  
  if (PS3.PS3Connected || PS3.PS3NavigationConnected)
  {
    mapping();
  
    data.ps3data = PS3Val;
    data.LD = LeftAnalogDistance;
    data.LT = LeftAnalogTheta;
    data.RD = RightAnalogDistance;
    data.RT = RightAnalogTheta;
    ET_ps3.sendData();
    BluetoothSerial.flush();
  Serial.println(String(LeftAnalogDistance)+"   "+String(LeftAnalogTheta)+ "  "+String(RightAnalogDistance)+ " "+String(RightAnalogTheta)+" "+String(PS3Val)); 
  
  }
}
