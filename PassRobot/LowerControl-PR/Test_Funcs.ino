void set_rpm(float rpm)
{
//   pPIDMotor[0]->required = -rpm;
//   pPIDMotor[1]->required = rpm;
//   pPIDMotor[2]->required = rpm;
//   pPIDMotor[3]->required = rpm;
   pPIDMotor[0]->required = rpm;
   pPIDMotor[1]->required = 0;
   pPIDMotor[2]->required = - rpm;

   pPIDMotor[0]->prevRequired = pPIDMotor[0]->required;
   pPIDMotor[1]->prevRequired = pPIDMotor[1]->required;
   pPIDMotor[2]->prevRequired = pPIDMotor[2]->required;

}

void motorTest(float pWM)
{
//  for(int i=0;i<2;i++)
//  {
    digitalWrite(pMotor[0]->direction1,LOW);
    digitalWrite(pMotor[0]->direction2,HIGH);
    pwm.pinDuty(pMotor[0]->pwmPin,pWM);
     digitalWrite(pMotor[1]->direction1,LOW);
    digitalWrite(pMotor[1]->direction2,HIGH);
    pwm.pinDuty(pMotor[1]->pwmPin,pWM);
     digitalWrite(pMotor[2]->direction1,LOW);
    digitalWrite(pMotor[2]->direction2,HIGH);
    pwm.pinDuty(pMotor[2]->pwmPin,pWM);
//  }
}

void plotRPM()
{
  SerialX.print(abs(pEncoder[0]->rpm));
  SerialX.print(" ");
  SerialX.print(abs(pEncoder[1]->rpm));
  SerialX.print(" ");
  SerialX.println(abs(pEncoder[2]->rpm));
  SerialX.print(" ");
//  SerialX.println(0);
}

void printrpm()
{
  SerialX.println(String((int)pEncoder[0]->rpm)+"  "+String((int)pEncoder[1]->rpm)+"  "+String((int)pEncoder[2]->rpm));
}

void printCount()
{
  SerialX.println(String((int)pEncoder[0]->Count)+"  "+String((int)pEncoder[1]->Count)+"  "+String((int)pEncoder[2]->Count));
}

void setSlowly(int rpm, int d_rpm)
{
   pPIDMotor[0]->required += d_rpm;
   pPIDMotor[1]->required += -d_rpm;
   pPIDMotor[2]->required += -d_rpm;
//   pPIDMotor[3]->required += d_rpm;
   
   if(abs(pPIDMotor[0]->required)>=rpm)
     {
       pPIDMotor[0]->required = rpm;
       pPIDMotor[1]->required = -rpm;
       pPIDMotor[2]->required = -rpm;
//       pPIDMotor[3]->required = rpm;  
     }
    delay(100);   
}
