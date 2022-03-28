//void FiniteStateMachine2()
//{
//
//  float BallX = -160.0;
//  float BallY = (200.0) * arena;
////  int ultrasonicDist = ultrasonic.distanceInCentimeters();
////  printLCD("X:" + String(BotX) + String ("YW:")  + String (robotYaw), "Y:"  + String(BotY)); //+ String ("  US:")  + String (ultrasonicDist) + String ("  "));
//
//
//  switch (state)
//  {
//    case waitForCommand:
//      calculateSpeed(0, 0, 0);
//      //      delay(2000);
//      state = towardsKick;
//      if (ps2x.ButtonPressed(PSB_R1))
//      {
//      }
//      break;
//
//    case towardsKick :
//      fsmFlag = traceLine(BotX, BotY, -51.5 , 400 * arena , 200, speedMode, STOP, 10);
//      if (!fsmFlag)
//        state = nearKick;
//      
//      break;
//
//    case nearKick:
////      ppidOmega->required = -90 * arena;
//      fsmFlag = traceLine(BotX, BotY, 120 , 200 * arena , 200, speedMode, STOP, 10);
//      if (!fsmFlag)
//      {
//        state = kick;
//        timer = millis();
//      }
//      break;
//    case kick:
//      calculateSpeed(-omegacontrol, 0, 0);
//      if ( (millis() - timer) >= 5000)
//      {
//        ppidOmega->required = 0;
//        state = forNextBall;
//        timer = millis();
//      }
//      break;
//
//    case forNextBall:
//      fsmFlag = traceLine(BotX, BotY, -51.5 , 400 * arena , 200, speedMode, STOP, 10);
//      if (!fsmFlag)
//        state = ballAhead;
//      break;
//
//    case ballAhead:
//      fsmFlag = traceLine(BotX, BotY, BallX, BallY, 200, speedMode, STOP, 5);
//
//      if (!fsmFlag)
//      {
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
//          state = nearBall;
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
//    case nearBall:
//      BallX = BotX - 10 ;
//      BallY = (129 - 27 ) * arena ;
//      anglegoal = Angle(BotX, BotY, BallX, BallY);
//      calculateSpeed(-omegacontrol, anglegoal, 100);
//      if (BotY * arena < 131 - 27 )
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
//      fsmFlag = traceLine(BotX, BotY, throwX, throwY, 200, speedMode, STOP, 5);
//      if (!fsmFlag)
//      {
//        state = throwing;
//      }
//      break;
//
//    case throwing :
//      calculateSpeed(-omegacontrol, 0, 0);
//
//      break;
//  }
//}
