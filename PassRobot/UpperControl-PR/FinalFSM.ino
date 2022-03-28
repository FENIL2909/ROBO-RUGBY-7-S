//float BallNumber[N] = {1,2,3,4,5};
int  N = 0;
float throwX = -100;
float throwY = 180 * arena;
float kickX = 170;
float kickY = 60 * arena;
int counter=0,counterxy=0;
float resetAngle=0.0;
long int timer , timerbuzz =0;;
float anglegoal;
//float prevDistLeft;
//float distDiff = prevDistLeft - distLeft ;
bool flag11=0, flag12=0;
void FinalFSM()
{

  float BallX = -165.0;
  float BallY = (200.0) * arena;
  
  switch (state)
  {
      case WaitForArenaSelect :      
             if (ps2x.ButtonPressed(PSB_R2))
             {
                  arena = RED;
                  state = WaitForRef;
                  printLCD("Arena :         ", "RED              ");
             }
             else if (ps2x.ButtonPressed(PSB_L2))
             {
                  arena = BLUE;
                  state = WaitForRef;
                  printLCD("Arena :", "BLUE");
             }
              BotX = -51.5;
              BotY = 44.64*arena;  
              BallX = -165.0;
              BallY = (200.0) * arena;
      break;
      
      
      case WaitForRef :
              if (ps2x.ButtonPressed(PSB_TRIANGLE))
             {
                  printLCD("To the        ", "Wall           ");
                  buzzOn;
                  state = towardsWallReset;
                  timerbuzz = millis;
             }
             
      break;

      
      case towardsWallReset:
            fsmFlag = traceLine(BotX, BotY, BallX, BallY, 150, speedMode, STOP, 5);
            if(millis - timerbuzz>1500)
               buzzOff;
            if (!fsmFlag)
            {
              //        BallX = -180;
              //        BallY = 129 * arena;
              state = touchWall2;
              printLCD("Resetting         ", "On Wall           ");
            }
      break;

     
      case touchWall2:
            calculateSpeed(-omegacontrol, pi, 70);
            printLCD(String(counter),"    ");
            if (abs(BotX - prevBotX) <= 0.5)
            {
                counter++;
                if (counter >= 200)
                {
                      state = SignalToPick;
                      counter = 0;
                      BotX = -171.5;
                      countYaw = 0;
                      printLCD("SignalToPick", "                   ");
                }
            }
            else
            {
                counter = 0;
            }
      break;


      case SignalToPick:
           calculateSpeed(-omegacontrol,0,0);
           if(agentPR.stateChange == 1)
          {   
              printLCD("Go Fetch        ", "My Boy          ");
              state = TowardsBall;
              agentPR.stateChange = 0;
          }
      break;

      case TowardsBall:
            BallX = BotX - 5 ;
            BallY = (129 - 27 * N) * arena ;
            anglegoal = Angle(BotX, BotY, BallX, BallY);
            calculateSpeed(-omegacontrol, anglegoal, 150);
            // fsmFlag = traceLine(BotX, BotY, BallX, BallY, 150, speedMode, STOP, 5);
            if (BotY * arena < 131 - 27 * N)
            {
                  calculateSpeed(-0, 0, 0);
                  state = gripBall;
                  timer = millis();
                  printLCD("Gripping         ", "Ball           ");
            }
      break;

    case gripBall:
          calculateSpeed(-omegacontrol, 0, 0);
          if ( (millis() - timer) >= 2000)
                state = towardsStart;
      break;

    case towardsStart:
          fsmFlag = traceLine(BotX, BotY, -80, 80*arena , 150, speedMode, STOP, 5);
          if (!fsmFlag)
          {      
                printLCD("Heading TO   ", "Start Zone    ");
                state = StartReset;
                timer = millis();
                resetAngle = 0;
                flag11=0;
                flag12=0;
          }
     break;


    case StartReset:
          printLCD(String(counter)+"           ",String(counterxy)+"             ");
          calculateSpeed(-omegacontrol,resetAngle, 100);
          if(abs(BotX-prevBotX)<=0.5 && abs(BotY-prevBotY)<=0.5 && flag11 && flag12)
          {
            counterxy++;
              if (counterxy >= 100)
              {
                    counter = 0;
                    counterxy = 10;
                    state = WaitForPassSignal;
                    BotX = -51.5;
                    BotY = 44.64*arena;
                    flag11 = 0;
                    flag12 = 0;
                    printLCD("WaitForPassSignal","                        ");
              }
          }
          else if(abs(BotX-prevBotX)<=0.5 && !flag11 )
          {
              counter++;
              if (counter >= 100)
              {
                    counter = 0;
                    resetAngle=(pi/2-0.4)*arena*(-1);
                    flag11=1;
              }
          }
          else if(abs(BotY-prevBotY)<=0.5 && flag11)
          {
              counter++;
              if (counter >= 100)
              {
                    counter = 0;
                    resetAngle = (pi/4)*arena*(-1);
                    flag12=1;
              }
          }
          else   
          {
              counter = 0;
              counterxy=0;
          }   
    break;      
              
                
    case WaitForPassSignal:
          calculateSpeed(-omegacontrol,0,0);
          if(agentPR.stateChange == 2)
          {   
              delay(2000);
              N++;
              state = towardsWallReset;
              agentTR.stateChange = 4;
              ETAgentPR_TR.sendData();
          }
    

}
}
