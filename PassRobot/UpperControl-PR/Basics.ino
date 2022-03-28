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

void resetXY()
{
  pEncoderX->Count = 0;
  pEncoderY->Count = 0;
  shiftX = 0;
  shiftY = 0;
  pBot->X_pos = 0;
  pBot->Y_pos = 0;
  pBot->prev_X = 0;
  pBot->prev_Y = 0;
  pBot->X_pos1 = 0;
  pBot->Y_pos1 = 0;
  BotY = 0;
  BotX = 0;
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


void returnCountX()
{
  if(digitalRead(pEncoderX->channel2))
    {
      pEncoderX->Count--;  ////for 3 wheel drive

//      pEncoderX->Count++;  ////for 4 wheel drive
    }
  else
    {
       pEncoderX->Count++;  ////for 3 wheel drive   

//         pEncoderX->Count--;  ////for 4 wheel drive
    }
}

void returnCountY()
{
  if(digitalRead(pEncoderY->channel2))
    {
      pEncoderY->Count++;  ////for 3 wheel drive

//      pEncoderY->Count--;  ////for 4 wheel drive
    }
  else
    {
      pEncoderY->Count--;  ////for 3 wheel drive      

//      pEncoderY->Count++;  ////for 4 wheel drive
    }
}
