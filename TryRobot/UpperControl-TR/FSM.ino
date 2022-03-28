int fsmFlag = 1, buzzCount=0, fsmCount = 0;
void finiteStateMachine()
{
//  if(fsmState != receiveBall) printLCD(String(BotX)+" "+String(BotY),String(robotYaw));
  if(ps2Flag)
  {  
    if(PS3Button == r1x)
    {
       fsmState = manualDrive;
       lcd.clear();  
    }
    if(PS3Button == selectx )
    {
       lcd.clear();
//       printLCD(String(BotX)+" "+String(BotY),String(robotYaw));
    }
  }
  switch(fsmState)
  {
    case arenaSelect:
    if(ps2Flag)
    {    
      if(PS3Button == r2x)
        {
            arenaFlag=RED;

            BotX = arenaFlag*shiftX;
            BotY = shiftY;
            fsmState = waitForRefree;
//            printLCD("RED ARENA"," ");
           } 
        if(PS3Button == l2x)
        {
              arenaFlag=BLUE;
            
              BotX = arenaFlag*shiftX;
              BotY = shiftY;
              fsmState = waitForRefree;
//              printLCD("BLUE ARENA"," ");
        }
    }         
    break;
    
    case waitForRefree:
//         printLCD("Waiting for signal","");
         if(ps2Flag)
         {
           if(PS3Button == trianglex)
           { 
             lcd.clear();
             initTask(receiveX,receiveY);
             fsmState = receiveBall;
             
             counter = 0;
             resetAngle = (pi - pi*arenaFlag)/2;
  //           printLCD("Go to receive spot"," ");
           }
         }
    break;

    case receiveBall:
//          printLCD(String(counterxy)+" "+String(counter),String(RadianToDegree(resetAngle)));
          if(buzzCount<500)
          {
            buzzOn;
            buzzCount++;
          }
          else
          {
            buzzOff;
          }
          if(fsmFlag)
            fsmFlag = planPath(startX,startY,goalX,goalY,200);
//          printLCD("PREPARE FOR RX"," ");
          if(!fsmFlag)
          {
           if(resetFlag)
            resetFlag = cornerReset(960*arenaFlag,42,receiveZone);
           if(!resetFlag)
           {
            calculateSpeed(0,0,0);
            fsmState = Collaborate;
            planState = checkCollision;
           }
          }
    break;

    case Collaborate:
//          collaborate(150,0);
//          if(!collaborate)
           selectTrySpot();           
    break;

    case placeBall:
          fsmFlag = planPath(startX,startY,goalX,goalY,600);
//          printLCD(String(goalX)+" "+String(goalY),"Place Ball");
          if(!fsmFlag)
          {
            fsmState = resetState;
            fsmFlag=1;
            
            planState = checkCollision;
          }
           
    break;

    case resetState:
////         printLCD("EXCUSE ME     ","RESETING     ");
//         fsmCount ++;
//         if(fsmFlag == 1)
//          {
//            fsmFlag = yawReset();
//          
////            printLCD(" oh yeah    ",String(robotYaw));
//          }
//         else if(fsmFlag == -1)
//          {
//            fsmFlag = resetXandY();
//          }
//         else
//         {
//           fsmState = variableState;
//           fsmCount = 0;
////          printLCD("Select Strategy     ","");
//         }


//       printLCD(" "," Reset");
       if(fsmFlag  == 1)
        fsmFlag = yawReset();  
       if (fsmFlag == -1)
       {
        if(digitalRead(proximityPin))
        {
         fsmFlag = 3;
//         printLCD("","I'm Still here");
        }
        else
        {
         fsmFlag = 4;
//          printLCD("","I'm not Still here");
        }       
       } 
       else if(fsmFlag == 3)
       {
//        calculateSpeed(-omegacontrol,0,100);
        traceLine(BotX,BotY,BotX+(arenaFlag*10),BotY + 5,100,0,0,constant,STOP,2);
        
        if(!digitalRead(proximityPin))
        fsmFlag=2;
       }
       else if(fsmFlag == 4)
       {
//        calculateSpeed(-omegacontrol,pi,100);
         traceLine(BotX,BotY,BotX-(arenaFlag*10),BotY + 5,100,0,0,constant,STOP,2);
       
        if(digitalRead(proximityPin))
        fsmFlag=2;
       }
       else if(fsmFlag == 2)
       {
          BotX = goalX;
          calculateSpeed(0,0,0);
          fsmState = variableState; 
//          printLCD("","           Gotchaaa");
       }
         
    break;     

    case variableState:
//              printLCD("","variable          ");
              calculateSpeed(0,0,0);
             if(ps2Flag)
             {
               if(PS3Button == trianglex)
               {
                   initTask(receiveX,receiveY);
                   fsmState = receiveBall;
                   resetAngle = (pi - pi*arenaFlag)/2;
                   resetFlag = 1;
                   fsmFlag = 1; 
               }
               if(PS3Button == circlex)
               {
                   initTask(kickingX,kickingY);
                   fsmState = kickBall;
                   fsmFlag = 1;
               }
               if(PS3Button == squarex)
               {
                  initTask(shiftX+25,shiftY+25 );
                  fsmState = goHome;
                  resetAngle = (pi + pi*arenaFlag)/2;
                  resetFlag = 1;
                  fsmFlag = 1;
               }
               if(PS3Button == selectx)
               {
                  lcd.clear();
  //                printLCD(String(BotX)+" "+String(BotY),String(robotYaw));
               }
            }
           
     break;
    case goHome:
          fsmFlag = planPath(startX,startY,goalX,goalY,200);
          if(!fsmFlag)
          { 
           if(resetFlag)
           resetFlag = cornerReset(arenaFlag*39,42,startZone)  ;
           if(!resetFlag)
           { 
             if(ps2Flag)
             {
              if(PS3Button == circlex)
              {
                  lcd.clear();
                  fsmState = kickBall;
                  initTask(kickingX,kickingY);
                  planState = checkCollision;              
              }
             }
             
           } 
          }
          
    break;

    case kickBall:
//            printLCD("KICKING      ","");
            fsmFlag = planPath(startX,startY,goalX,goalY,200);

            if(!fsmFlag)
            {  
              fsmState = variableState;
//              printLCD("Select Strategy        ","");
              planState = checkCollision;
            }
            
    break;

    case manualDrive:
//          printLCD("MANUAL         ","");
          operateManually();
    break;
  }
}

void selectTrySpot()
{
  if(ps2Flag)
  {
    if(PS3Button == leftx)
    {
       lcd.clear();
       initTask(trySpotX[0],trySpotY[0]);
       fsmState = placeBall;
  //     printLCD("TRY SPOT 0","");  
    }
    if(PS3Button == upx)
    {
       lcd.clear();
       initTask(trySpotX[1],trySpotY[1]); 
       fsmState = placeBall;
  //     printLCD("TRY SPOT 1","");
     
    }
    if(PS3Button == rightx)
    {
       lcd.clear();
       initTask(trySpotX[2],trySpotY[2]);
       fsmState = placeBall;
  //     printLCD("TRY SPOT 2",""); 
    }
    if(PS3Button == downx)
    {
       lcd.clear();
       initTask(trySpotX[3],trySpotY[3]);
       fsmState = placeBall;
  //     printLCD("TRY SPOT 3",""); 
    }
    if(PS3Button == l1x)
    {
       lcd.clear();
       initTask(trySpotX[4],trySpotY[4]-15);
       fsmState = placeBall;
  //     printLCD("TRY SPOT 4","");
    }
  }
}
