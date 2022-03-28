long long int ps2Delay = 0;
int LEDcounter= 0;

void serialEvent()
{
//  while(ETAgentPR.receiveData());
//  if(collabFlag)
//    collaborate(0,0);
//  ETAgentTR.sendData();
}
void serialEvent1()
{
  //do something
}
void serialEvent2()
{
  while(ETMpu.receiveData()>0)
    robotYaw = mympu.robotYaw-initialRobotYaw;

  if( robotYaw >180)
    robotYaw -=360;
  else if( robotYaw < -180)
    robotYaw +=360;
    
  robotYaw = robotYaw - constError;
  omegacontrol = OmegaControlMPU(robotYaw,2);
  handleXY();
}
void serialEvent3()
{
    receivePS3data(); 
}

void sendPlotData()
{
  myplot.x = BotX;
  myplot.y = BotY;

  ETPlot.sendData();
  BluetoothSerial2.flush();
}

