void calculateSpeed(float omega , float angle , float Vtranslational)     //Omega rad/s      Vtranslational  m/s
{
  angle+=DegreeToRadian(robotYaw);
  if(angle < 0)
    angle += 2*pi; 

  mydata.omega = omega;
  mydata.theta = angle;
  
  if(Vtranslational > maxWheelRPM)
    Vtranslational = maxWheelRPM;
    
  mydata.velocity = Vtranslational;
    
  ETUpperLower.sendData();  
}

float OmegaControlMPU(int yaw,float tolerence)
{
  float omegacontrol=0;
  float error = ppidOmega->required - yaw;

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
  return omegacontrol;
}
