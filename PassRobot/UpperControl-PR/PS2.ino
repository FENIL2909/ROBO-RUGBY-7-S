//__________________________________________________Global Variables____________________________________________
double xSquare_leftdistance = 0, ySquare_leftdistance = 0, xSquare_rightdistance = 0, ySquare_rightdistance = 0;
double xCircle_rightdistance = 0, yCircle_rightdistance = 0, xCircle_leftdistance = 0, yCircle_leftdistance = 0;
double LeftAnalogTheta = 0, RightAnalogTheta = 0;
double LeftAnalogDistance = 0, RightAnalogDistance = 0;
uint8_t ps2release_count = 0;
uint8_t ps2receiveflag = 1;
uint8_t rx = 0,ry = 0,lx = 0,ly = 0;
//_______________________________________________________________________________________________________________

//____________________________________________________Functions__________________________________________________

void scalePS2value(){

      ySquare_leftdistance=(basePS2_Y-ly)/basePS2_Y;
      xSquare_leftdistance=(lx-128)/128.0;
      ySquare_rightdistance=(basePS2_Y-ry)/basePS2_Y;
      xSquare_rightdistance=(rx-128)/128.0;
      if(xSquare_leftdistance==0 && ySquare_leftdistance==0){
      xCircle_leftdistance=0;
      yCircle_leftdistance=0; 
      }
      else{
      xCircle_leftdistance= xSquare_leftdistance *sqrt(pow(xSquare_leftdistance,2)+pow(ySquare_leftdistance,2)-(pow(xSquare_leftdistance,2)*pow(ySquare_leftdistance,2)))/sqrt(pow(xSquare_leftdistance,2)+pow(ySquare_leftdistance,2));
      yCircle_leftdistance= ySquare_leftdistance *sqrt(pow(xSquare_leftdistance,2)+pow(ySquare_leftdistance,2)-(pow(xSquare_leftdistance,2)*pow(ySquare_leftdistance,2)))/sqrt(pow(xSquare_leftdistance,2)+pow(ySquare_leftdistance,2));
      }
      if(xSquare_rightdistance == 0 && ySquare_rightdistance ==0){
      xCircle_rightdistance = 0;
      yCircle_rightdistance = 0; 
      }
      else{
      xCircle_rightdistance = xSquare_rightdistance *sqrt(pow(xSquare_rightdistance,2)+pow(ySquare_rightdistance,2)-(pow(xSquare_rightdistance,2)*pow(ySquare_rightdistance,2)))/sqrt(pow(xSquare_rightdistance,2)+pow(ySquare_rightdistance,2));
      yCircle_rightdistance = ySquare_rightdistance *sqrt(pow(xSquare_rightdistance,2)+pow(ySquare_rightdistance,2)-(pow(xSquare_rightdistance,2)*pow(ySquare_rightdistance,2)))/sqrt(pow(xSquare_rightdistance,2)+pow(ySquare_rightdistance,2));
      }
      
      LeftAnalogDistance = sqrt((xCircle_leftdistance)*(xCircle_leftdistance)+(yCircle_leftdistance)*(yCircle_leftdistance));
      LeftAnalogTheta = atan2(yCircle_leftdistance,xCircle_leftdistance)*(180.0/3.1415926);
      LeftAnalogTheta = (int(LeftAnalogTheta)+360)%360;
      RightAnalogDistance = sqrt((xCircle_rightdistance)*(xCircle_rightdistance)+(yCircle_rightdistance)*(yCircle_rightdistance));
      RightAnalogTheta = atan2(yCircle_rightdistance,xCircle_rightdistance)*(180.0/3.1415926);
      RightAnalogTheta = (int(RightAnalogTheta)+360)%360;

      
      if(LeftAnalogDistance == 0.00){
        LeftAnalogTheta = 0;
      }
      if(RightAnalogDistance==0.00){
        RightAnalogTheta=0;
      }
      
} 
void operateManually()
{
  
  receivePS2data();
  scalePS2value();
  PS2executePressed();
  
  uint16_t orientationAngle = 0;
  float omegaSpeed = 1.8;     
  
      if(((RightAnalogTheta < 90)&&(RightAnalogTheta >= 0))||((RightAnalogTheta < 360)&&(RightAnalogTheta > 270)))
      {
        calculateSpeed(-RightAnalogDistance*omegaSpeed,DegreeToRadian((LeftAnalogTheta- orientationAngle)),LeftAnalogDistance* speeed); 
      }
      if((RightAnalogTheta<270)&&(RightAnalogTheta>90))
      {
        calculateSpeed(RightAnalogDistance*omegaSpeed,DegreeToRadian((LeftAnalogTheta- orientationAngle)),LeftAnalogDistance* speeed);  
      }
      if(LeftAnalogDistance<=0.01 && RightAnalogDistance<=0.01)
      {
        brakeWheels();
      }
      Serial.println(LeftAnalogDistance);
}  

void receivePS2data()
{

    ps2x.last_buttons=ps2x.buttons;
    while(ET_ps2.receiveData()>0)
    {
      //delay(10);
      ps2x.buttons=data.ps2data;
      rx=data.Rx;
      ry=data.Ry;
      lx=data.Lx;
      ly=data.Ly;
    }
  
}


///////////////////////////////////////////////////////////////////                            PS2 ENDED                            ///////////////////////////////////////////

 
void PS2executePressed()
{    
    ps2release_count++;
    if(ps2release_count >3)         
     { 
//        if(ps2x.ButtonPressed(PSB_L2))  
//        {
//        }   
//        if(ps2x.ButtonPressed(PSB_R2))  
//        {
//        }
//        if(ps2x.ButtonPressed(PSB_PAD_DOWN)) 
//        {
//        }
//        if(ps2x.ButtonPressed(PSB_PAD_UP))  
//        {
//        }
//        if(ps2x.ButtonPressed(PSB_SELECT))
//        { 
//        }
        if(ps2x.ButtonPressed(PSB_START))
        {   
                flagStop = 0;
        }
        if(ps2x.ButtonPressed(PSB_TRIANGLE))  
        {  
                printLCD(String(BotX) + "Y: " , String(BotY) + "   "+String(robotYaw));
        }  
        if(ps2x.ButtonPressed(PSB_CIRCLE)) 
        {   
               flagStop = 1;   
        }
//        if(ps2x.ButtonPressed(PSB_CROSS))  
//        {
//        }
//        if(ps2x.ButtonPressed(PSB_SQUARE)) 
//        {      
//        }
//        if(ps2x.ButtonPressed(PSB_L1))
//        { 
//        }
//        if(ps2x.ButtonPressed(PSB_PAD_LEFT))
//        {
//        }
//        if(ps2x.ButtonPressed(PSB_R1))
//        {
//        }
//        if(ps2x.ButtonPressed(PSB_PAD_RIGHT))
//        {   
//        } 
////     delay(50);   
     }
}
