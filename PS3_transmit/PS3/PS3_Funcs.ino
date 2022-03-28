int prevVal = 0;
int currVal = 0;
int counterVal = 0;
void mapping()
{
    if (PS3.PS3Connected || PS3.PS3NavigationConnected) {
      ySquare_leftdistance=(baseLeft_Y-PS3.getAnalogHat(LeftHatY))/baseLeft_Y;
      xSquare_leftdistance=(PS3.getAnalogHat(LeftHatX)-baseLeft_X)/baseLeft_X;
      ySquare_rightdistance=(baseRight_Y-PS3.getAnalogHat(RightHatY))/baseRight_Y;
      xSquare_rightdistance=(PS3.getAnalogHat(RightHatX)-baseRight_X)/baseRight_X;

     if(xSquare_leftdistance==0 && ySquare_leftdistance==0)
     {
      xCircle_leftdistance=0;
      yCircle_leftdistance=0; 
     }
     else
     {
      xCircle_leftdistance= xSquare_leftdistance *sqrt(pow(xSquare_leftdistance,2)+pow(ySquare_leftdistance,2)-(pow(xSquare_leftdistance,2)*pow(ySquare_leftdistance,2)))/sqrt(pow(xSquare_leftdistance,2)+pow(ySquare_leftdistance,2));
      yCircle_leftdistance= ySquare_leftdistance *sqrt(pow(xSquare_leftdistance,2)+pow(ySquare_leftdistance,2)-(pow(xSquare_leftdistance,2)*pow(ySquare_leftdistance,2)))/sqrt(pow(xSquare_leftdistance,2)+pow(ySquare_leftdistance,2));
     }
     
     if(xSquare_rightdistance==0 && ySquare_rightdistance==0)
     {
      xCircle_rightdistance=0;
      yCircle_rightdistance=0; 
     }
     else
     {
      xCircle_rightdistance= xSquare_rightdistance *sqrt(pow(xSquare_rightdistance,2)+pow(ySquare_rightdistance,2)-(pow(xSquare_rightdistance,2)*pow(ySquare_rightdistance,2)))/sqrt(pow(xSquare_rightdistance,2)+pow(ySquare_rightdistance,2));
      yCircle_rightdistance= ySquare_rightdistance *sqrt(pow(xSquare_rightdistance,2)+pow(ySquare_rightdistance,2)-(pow(xSquare_rightdistance,2)*pow(ySquare_rightdistance,2)))/sqrt(pow(xSquare_rightdistance,2)+pow(ySquare_rightdistance,2));
     }
      
     LeftAnalogDistance=sqrt((xCircle_leftdistance)*(xCircle_leftdistance)+(yCircle_leftdistance)*(yCircle_leftdistance));
     LeftAnalogTheta=atan2(yCircle_leftdistance,xCircle_leftdistance)*(180.0/3.14);
     LeftAnalogTheta=(int(LeftAnalogTheta)+360)%360;
      
     RightAnalogDistance=sqrt((xCircle_rightdistance)*(xCircle_rightdistance)+(yCircle_rightdistance)*(yCircle_rightdistance));
     RightAnalogTheta=atan2(yCircle_rightdistance,xCircle_rightdistance)*(180.0/3.14);
     RightAnalogTheta=(int(RightAnalogTheta)+360)%360;

     if(LeftAnalogDistance <= 0.04)
        LeftAnalogTheta=0;
     if(RightAnalogDistance <= 0.04)
        RightAnalogTheta=0;

//     Serial.println(String(LeftAnalogDistance)+"   "+String(LeftAnalogTheta)+ "  "+String(RightAnalogDistance)+ " "+String(RightAnalogTheta)); 
}  
}

void ps3_funcs()
{
  if (PS3.PS3Connected || PS3.PS3NavigationConnected) {
    // Analog button values can be read from almost all buttons
    prevVal = PS3Val;
    if (PS3.getAnalogButton(L2))
     {
      counterVal = 0;
      PS3Val = l2x;
     }
     
    if (PS3.getAnalogButton(R2))
     {
      counterVal = 0;
      PS3Val = r2x;
     }
     
    if (PS3.getButtonClick(PS))
     {
      counterVal = 0;
      PS3Val = psx;
     }
 
    if (PS3.getButtonClick(TRIANGLE))
     {
       counterVal = 0;
       PS3Val = trianglex;      
//     PS3.setRumbleOn(RumbleLow);
     }
      if (PS3.getButtonClick(CIRCLE)) 
      { 
        counterVal = 0;
        PS3Val = circlex;
//      PS3.setRumbleOn(RumbleHigh);
      }
      if (PS3.getButtonClick(CROSS))
        {
          counterVal = 0;
          PS3Val = crossx;
        }
      if (PS3.getButtonClick(SQUARE))
        {
          counterVal = 0;
          PS3Val = squarex;
        }

      if (PS3.getButtonClick(UP)) 
        {
          counterVal = 0;
          PS3Val = upx;
        }
      if (PS3.getButtonClick(RIGHT))
        {
          counterVal = 0;
          PS3Val = rightx;
        }
      if (PS3.getButtonClick(DOWN)) 
        {
          counterVal = 0;
          PS3Val = downx;
        }
      if (PS3.getButtonClick(LEFT)) 
        {
          counterVal = 0;
          PS3Val = leftx;
        }


      if (PS3.getButtonClick(L1))
        {
          counterVal = 0;
          PS3Val = l1x;
        }
      if (PS3.getButtonClick(L3))
        {
          counterVal = 0;
          PS3Val = l3x;
        }
      if (PS3.getButtonClick(R1))
        {
          counterVal = 0;
          PS3Val = r1x;
        }
      if (PS3.getButtonClick(R3))
       {
        counterVal = 0;
        PS3Val = r3x;
       }
      if (PS3.getButtonClick(SELECT))
       {
        counterVal = 0;
        PS3Val = selectx;
//      PS3.printStatusString();
       }
      if (PS3.getButtonClick(START))
       {
        counterVal = 0;
        PS3Val = startx; 
//      printAngle = !printAngle;
       }
      
       currVal = PS3Val;
       if(currVal == prevVal)
       {
        counterVal ++;
        if(counterVal == 100)
        {
          PS3Val = 0;
          counterVal = 0;
        }
       }
      
      
    

  }
}

