void calculateIK(float Omega , float angle , float Vt)     //Omega rad/s      Vtranslational  m/s
{  
  for(int i=0;i<N;++i)
  {
    pWheel[i]->translationSpeed = Vt * sin(angle - DegreeToRadian(pWheel[i]->angle));
    pWheel[i]->angularSpeed = Omega * RadiusOmniDrive;
    pWheel[i]->Speed = pWheel[i]->translationSpeed + pWheel[i]->angularSpeed;
    pWheel[i]->rpm = VelocityToRPM(pWheel[i]->Speed); 

    pPIDMotor[i]->prevRequired = pPIDMotor[i]->required;
    pPIDMotor[i]->required = pWheel[i]->rpm;
    
    if(pPIDMotor[i]->required == 0)
          zeroCntr ++;
  }
      softBrake = 1;
      if(zeroCntr == 4) 
      {
        softBrake = 0;
        zeroCntr = 0;
      }
      
}
