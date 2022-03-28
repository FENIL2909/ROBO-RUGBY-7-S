//__________________Global Variables______________________
int dataIN = 0, siZE = 5;
float dX = 0, dY = 0, avgBT = 0, prevavgBT = 0, prevbotTheta = 0, dR = 0, prevdR = 0, t1 =0, t2 = 0, dT = 0;
float alpha = 0.9, movingbT[5] = {0}, vBot = 0; 
//________________________________________________________

//____________________Functions___________________________
void calculatebotTheta()
{
    dX = (BotX - prevBotX);
    dY = (BotY - prevBotY);
    dR = sqrt(BotX*BotX + BotY*BotY);
    
    
    if(abs(dR - prevdR) > 0.1)
    {     
        t1 = millis();
        prevbotTheta = botTheta;
        botTheta = atan2(dY,dX) + DegreeToRadian(ppidOmega->required);
        
        if(botTheta < 0)
          botTheta = botTheta + 2*pi;
          
        movingbT[dataIN] = botTheta;
        dataIN++;

        if(dataIN>siZE)
          dataIN = 0;
        
        prevavgBT = avgBT;
        avgBT = (movingbT[0] + movingbT[1] + movingbT[2] + movingbT[3] + movingbT[4])/5.0;

        botTheta = prevavgBT + alpha*(prevbotTheta - prevavgBT);
        prevdR = dR;

        botStop = 0;
        
        dT = -t2 + t1;
        vBot = sqrt(dX*dX + dY*dY)/dT;
       
    }
    else if(dX == 0 && dY == 0)
    {
      botTheta = 0;
      botStop = 1;
    }
    t2 = millis();
     printLCD("vBot: "+String(vBot*1000), "theta: "+String(botTheta*180/pi));
     
} 
float controlBotSpeed(float normalizedDist)
{
  if(speedMode == accelerate)
    return maxSpeed*(1/(1+exp(-5*(normalizedDist-0.5)))) + minSpeed;
  else if(speedMode == decelerate)
    return maxSpeed*(1/(1+exp(5*(normalizedDist-0.5)))) + minSpeed;
  else if(speedMode == accdec)
  {
    if(normalizedDist <= 0.5)
      return maxSpeed*(1/(1+exp(-5*(30*normalizedDist-1)))) + minSpeed; //20 steepness
      return maxSpeed*(1/(1+exp(5*(12.5*normalizedDist-8.9)))) + minSpeed;  
  }
      return maxSpeed;
}
float trapiziumdecelration(float dist,float vel,float stoppingdist )
{
  
  float minV = 0.0;
  if(dist<stoppingdist)
  {
   if(finalVelo<150)
   minV = 38;
   else if(finalVelo > 250)
   minV = 10;
   else
   minV = (250-vel)*30/100 + 10;
   
   finalVelo = (250-minV)*dist/stoppingdist + minV ;
   }
   else 
   finalVelo = vel;
   
   return finalVelo;
   
}
