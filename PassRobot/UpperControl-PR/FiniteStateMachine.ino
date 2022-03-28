//
//void FiniteStateMachine()
//{
//
//  float BallX = -160.0;
//  float BallY = (200.0) * arena;
////  int ultrasonicDist = ultrasonic.distanceInCentimeters();
//  printLCD("X:" + String(BotX) + String ("YW:")  + String (robotYaw), "Y:"  + String(BotY));// + String ("  US:")  + String (ultrasonicDist) + String ("  "));
//  
//  
//  switch (state)
//  {
//    case waitForCommand:
//      calculateSpeed(0, 0, 0);
//      //      delay(2000);
//      state = ballAhead;
//      if (ps2x.ButtonPressed(PSB_R1))
//      {
//      }
//      break;
//
//    case ballAhead:
//      fsmFlag = traceLine(BotX, BotY, BallX, BallY, 150, speedMode, STOP, 5);
//
//      if (!fsmFlag)
//      {
//        //        BallX = -180;
//        //        BallY = 129 * arena;
//        state = touchWall;
//      }
//      break;
//
//    case touchWall:
//      calculateSpeed(-omegacontrol, pi, 50);
//      if (abs(BotX - prevBotX) <= 0.5)
//      {
//        counter++;
//        if (counter == 100)
//        {
//          state = TowardsBall;
//          counter = 0;
//          BotX = -169;
//        }
//      }
//      else
//      {
//        counter = 0;
//      }
//      break;
//
//    case TowardsBall:
//      BallX = BotX - 10 ;
//      BallY = (129 - 27 * N) * arena ;
//      anglegoal = Angle(BotX, BotY, BallX, BallY);
//      calculateSpeed(-omegacontrol, anglegoal, 100);
//      //      fsmFlag = traceLine(BotX, BotY, BallX, BallY, 150, speedMode, STOP, 5);
//      if (BotY * arena < 131 - 27 * N)
//      {
//        calculateSpeed(-0, 0, 0);
//        state = grip;
//        timer = millis();
//      }
//      break;
//
//    case grip:
//      calculateSpeed(-omegacontrol, 0, 0);
//      if ( (millis() - timer) >= 2000)
//        state = towardsThrowing;
//      break;
//
//    case towardsThrowing:
//      fsmFlag = traceLine(BotX, BotY, throwX, throwY, 150, speedMode, STOP, 5);
//      if (!fsmFlag)
//      {
//        state = throwing;
//        timer = millis();
//      }
//      break;
//
//    case throwing :
//      calculateSpeed(-omegacontrol, 0, 0);
//      if ( (millis() - timer) >= 2000)
//      {
//        state = towardsFence;
//        ppidOmega->required = -90 * arena;
//        timer = millis();
//      }
//      break;
//
//    case towardsFence :
//      fsmFlag = traceLine(BotX, BotY, -130 , 309 * arena , 150, speedMode, STOP, 10);
//      if (!fsmFlag)
//      {
//        calculateSpeed(-omegacontrol, 0, 0);
//      }
//
//      if ( (millis() - timer) >= 7000)
//      {
//        state = towardsKick;
//        timer = millis();
//      }
//      break;
//
//    case towardsKick :
//      fsmFlag = traceCircle(-20, 309 * arena, 80, 309 * arena, 100, clockwise * arena, 150, STOP, 15);
//      if (!fsmFlag)
//        //        calculateSpeed(-omegacontrol, 0, 0);
//        state = nearKick;
//      break;
//
//    case nearKick:
//      fsmFlag = traceLine(BotX, BotY, 80 , 200 * arena , 150, speedMode, STOP, 10);
//      if (!fsmFlag)
//      {
//        state = readyToKick;
//      }
//      break;
//
//    case readyToKick:
//      fsmFlag = traceCircle(160, 200 * arena, 160 , 120 * arena, 80, antiClockwise * arena, 150, STOP, 15);
//      if (!fsmFlag)
//      {
////        calculateSpeed(-omegacontrol, 0, 0);
//        //        BotY = ultrasonicDist;
//        state = pointOfKick;
//      }
//
//      break;
//
//    case pointOfKick:
//      traceLine(BotX, BotY, 160 , 120 * arena , 150, speedMode, STOP, 10);
//      if (!fsmFlag)
//      {
//        state = kick;
//      }
//      break;
//    case kick:
//      calculateSpeed(-omegacontrol, 0, 0);
////      BotY = ultrasonicDist + 30;
//      if ( (millis() - timer) >= 5000)
//      {
//
//
//        state = forNextBall;
//        timer = millis();
//      }
//      break;
//
//    case forNextBall:
//      fsmFlag = traceLine(BotX, BotY, 80 , 309 * arena , 150, speedMode, STOP, 10);
//      ppidOmega->required = 0 * arena;
//      if (!fsmFlag)
//      {
//        state = towardsNextBall;
//      }
//      break;
//
//    case towardsNextBall:
//      fsmFlag = traceCircle(-20, 309 * arena, -130, 309 * arena, 100, antiClockwise * arena, 150, STOP, 15);
//      if (!fsmFlag)
//      {
//        state = ballAhead;
//        N = N + 1;
//      }
//      break;
//
//
//  }
//}
