void calculateSpeed(float omega , float angle , float Vtranslational)     //Omega rad/s      Vtranslational  m/s
{
  angle += DegreeToRadian(robotYaw);
  if(angle < 0)
    angle += 2*pi; 

  ppidRoller->required = angle;
  
//  float deviation = angle - botTheta; 
//  float opposeMagnitude, opposeAngle;
//  
//  if(abs(deviation)>=DegreeToRadian(10)  && !botStop && Vtranslational>100)
//  {  
//    opposeMagnitude = ppidRoller->pidControl(botTheta);
//    opposeAngle = atan2(opposeMagnitude,Vtranslational);
//     
//    angle = angle + opposeAngle; 
//    Vtranslational = sqrt(Vtranslational*Vtranslational + opposeMagnitude*opposeMagnitude); 
//   
//  }
  
  mydata.omega = omega;
  mydata.theta = angle;
  
  if(Vtranslational > 375)
    Vtranslational = 375;
    
  mydata.velocity = Vtranslational;
  
  ETUpperLower.sendData();  
//  UpperLowerSerial.flush();
}

float OmegaControlMPU(int yaw,float tolerence)
{
  float omegacontrol=0;
  float error = ppidOmega->required - yaw;
  if( error  >180)       
  {
    error -=360;
    yaw +=360;
  }
  else if( error < -180)
  {
    error +=360;
    yaw -=360;
  }
  if(abs(error) < tolerence)
    {
      omegacontrol = 0;
      redLEDon;
    }
  else
    {
      omegacontrol = ppidOmega->pidControl(yaw);
      redLEDoff;
    }
//    printLCD("error:" + String(error) + "req: " , String(ppidOmega->required));
    
  return omegacontrol;
}
