//__________________________________________________Global Variables____________________________________________
int followFlag = 1, traceFlag=1, flag11 = 0, flag12 = 0;
int counterYaw = 0, counterYaw1 = 0, counterxy = 0,counter = 0;
//____________________________________________________Functions___________________________________________________
float dist(float x1,float y1,float x2,float y2)
{
  return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

float Angle(float x1,float y1,float x2,float y2)
{
  float angle=atan2(y2-y1,x2-x1);
  if(angle<0)
  return 2*pi + angle;
  else
  return angle;
}

void printLCD(String data1, String data2)
{
  lcd.setCursor(0,0); // Sets the cursor to col 0 and row 0
  lcd.print(data1);
  lcd.setCursor(0,1); // Sets the cursor to col 1 and row 0
  lcd.print(data2);
}

void brakeWheels(){
  mydata.velocity = 0;
  mydata.omega = -omegacontrol;
}

int yawReset()
{
   traceLine(goalX,goalY,goalX,goalY+55,140,0,0,constant,CONTINUE,0.1);
   counterYaw1 ++;
  
   if(counterYaw1>=100)
   { 
    if(abs(prevBotX-BotX)<0.1 && abs(prevBotY-BotY)<0.1)
      counterYaw++;
    else 
      counterYaw=0;
    
    if(counterYaw>=200)
    {
      initialRobotYaw+=robotYaw;
      
      counterYaw1=0;
      counterYaw=0;
      
      BotY = 579.5; //567.5
      return -1;
    }
   } 
   return 1;
}

int cornerReset(float resetX, float resetY , int zone)
{
  counterYaw1++;
  calculateSpeed(-omegacontrol,resetAngle, 120+50*flag11*flag12);
  if(counterYaw1>=100)
  { 
    if(abs(BotX-prevBotX)<=0.5 && abs(BotY-prevBotY)<=0.5 && flag11 && flag12)
    {
      counterxy++;
        if (counterxy >= 100)
        {
              counter = 0;
              counterxy = 0;
              BotX = resetX;
              BotY = resetY;
              flag11 = 0;
              flag12 = 0;
              initialRobotYaw+=robotYaw;
              counterYaw1 = 0;
              return 0;
        }
     }
     else if(abs(BotX-prevBotX)<=0.5 && !flag11 )
     {
         counter++;
         if (counter >= 100)
         {
           counter = 0;
           resetAngle = 3*pi/2;
           counterxy = 0;
           flag11=1;
           return 1;
         }
     }
     else if(abs(BotY-prevBotY)<=0.5 && flag11)
     {
         counter++;
         if (counter >= 100)
         {
              counter = 0;
              counterxy = 0;
               resetAngle = 3*pi/2 + (pi/4)*arenaFlag*zone;
               flag12=1;
               return 1;
         }
     }
     else  
     {
         counter = 0;
         counterxy=0;
         return 1;
     }   
   }
   else
    return 1;
}

void initTask(float x2,float y2)
{
  startX = BotX;
  startY = BotY;

  goalX = arenaFlag*x2;
  goalY = y2;
}
//_______________________________INTERRUPTS______________________________________________
void returnCountX()
{
  if(digitalRead(pEncoderX->channel2))
    pEncoderX->Count++;
  else
    pEncoderX->Count--; 
}

void returnCountY()
{
  if(digitalRead(pEncoderY->channel2))
    pEncoderY->Count--;
  else
    pEncoderY->Count++;
}
