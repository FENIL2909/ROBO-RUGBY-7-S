//__________________________________________________Global Variables____________________________________________

double LeftAnalogTheta = 0, RightAnalogTheta = 0;
double LeftAnalogDistance = 0, RightAnalogDistance = 0;

//_______________________________________________________________________________________________________________

//____________________________________________________Functions__________________________________________________

void operateManually()
{
  uint16_t orientationAngle = 0;
  float omegaSpeed = 1.8;     
  
      
      if(LeftAnalogDistance<=0.01 && RightAnalogDistance<=0.01)
      {
        brakeWheels();
      }
      else if(((RightAnalogTheta < 90)&&(RightAnalogTheta >= 0))||((RightAnalogTheta < 360)&&(RightAnalogTheta > 270)))
      {
        calculateSpeed(-RightAnalogDistance*omegaSpeed,DegreeToRadian((LeftAnalogTheta- orientationAngle)),LeftAnalogDistance* manualSpeed); 
        ppidOmega->required = robotYaw;        
      }
      else if((RightAnalogTheta<270)&&(RightAnalogTheta>90))
      {
        calculateSpeed(RightAnalogDistance*omegaSpeed,DegreeToRadian((LeftAnalogTheta- orientationAngle)),LeftAnalogDistance* manualSpeed); 
        ppidOmega->required = robotYaw;
         
      }
      else
      {
        calculateSpeed(-omegacontrol,DegreeToRadian((LeftAnalogTheta- orientationAngle)),LeftAnalogDistance* manualSpeed); 
      }

      Serial.println(String(LeftAnalogDistance)+"   "+String(LeftAnalogTheta)+ "  "+String(RightAnalogDistance)+ " "+String(RightAnalogTheta)+"  "+String(PS3Button));
      if(PS3Button)
      Serial.println("Pressed");
}  

void receivePS3data(){

    while(ET_ps3.receiveData()>0)
    {
      PS3Button = data.ps3data;
      LeftAnalogDistance = data.LD;
      LeftAnalogTheta = data.LT;
      RightAnalogDistance = data.RD;
      RightAnalogTheta = data.RT;  
    }  

    
}


///////////////////////////////////////////////////////////////////                            PS2 ENDED                            ///////////////////////////////////////////

