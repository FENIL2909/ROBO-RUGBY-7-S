void serialEvent1()
{
  while(ETAgentPR_TR.receiveData());
       agentPR.stateChange = agentTR.stateChange;
//  
//  ETAgentPR.sendData();
}
//void serialEvent1()
//{
//  //do something
//}
void serialEvent2()
{
  countYaw++;
  while(ETMpu.receiveData())
   robotYaw=mympu.robotYaw;
  if(countYaw==3)
  {
    initialRobotYaw = mympu.robotYaw;
  }
  robotYaw=mympu.robotYaw-initialRobotYaw;
 
  if( robotYaw >180)
    robotYaw -=360;
  else if( robotYaw < -180)
    robotYaw +=360;
 
   omegacontrol = OmegaControlMPU(robotYaw,2);

   
}
void serialEvent3()
{
    if(millis()-timerPS2>50)
  {
    receivePS2data(); 
    PS2executePressed();

    timerPS2 = millis();
  } 
}
void sendPlotData()
{
  myplot.x = robotYaw;
  myplot.y = BotY;

  ETPlot.sendData();
  BluetoothSerial2.flush();
}
