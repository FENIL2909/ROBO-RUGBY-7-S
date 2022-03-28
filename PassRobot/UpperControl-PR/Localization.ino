
//

//____________________Functions___________________________
void handleXY(void)
{
    del_yaw = robotYaw - prev_yaw;
    prev_yaw = robotYaw;
    
    if(del_yaw>180)
    del_yaw-=360;
    if(del_yaw<-180)
    del_yaw+=360;
    
    pBot->prev_X = pBot->X_pos1;    
    pBot->X_pos1 = (pEncoderX->Count * 2 * pi * RadiusXYWheel / pEncoderX->ppr); //cm   
    pBot->del_x = pBot->X_pos1 - pBot->prev_X ;//+ DegreeToRadian(del_yaw)*4.5;  
    
    pBot->prev_Y = pBot->Y_pos1;  
    pBot->Y_pos1 = (pEncoderY->Count * 2 * pi * RadiusXYWheel / pEncoderY->ppr); //cm
    pBot->del_y = pBot->Y_pos1 - pBot->prev_Y ;//- DegreeToRadian(del_yaw)*4.5;
    
    float r = dist(0,0,pBot->del_x,pBot->del_y);

    float Theta = the(pBot->del_y,pBot->del_x,robotYaw + 225);
    
    prevBotX = BotX;
    prevBotY = BotY;
    
    BotX = BotX + r*(cos(Theta));
    BotY = BotY + r*(sin(Theta));
//
//    Serial.print(String(robotYaw)+ " ");
//Serial.print(BotX);
//Serial.print("   ");
//Serial.print(BotY);
//Serial.println("   ");
//Serial.println(RadianToDegree(Theta));

    printLCD(String(BotX) + "Y: " , String(BotY) + "   "+String(robotYaw));
//     printLCD("", String(robotYaw));

}
float the(float del_y,float del_x,int botYaw)
{
//  botYaw = int(botYaw*10);
//  botYaw = float(botYaw)/10.0;
  return (atan2(del_y,del_x) - DegreeToRadian(botYaw));
}
