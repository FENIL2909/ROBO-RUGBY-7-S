// 
//
//void FiniteStateMachine3()
//{
//
//  float BallX = -160.0;
//  float BallY = (200.0) * arena;
////  int ultrasonicDist = ultrasonic.distanceInCentimeters();
////  printLCD("X:" + String(BotX) + String ("YW:")  + String (robotYaw), "Y:"  + String(BotY)); //+ String ("  US:")  + String (ultrasonicDist) + String ("  "));
////  Serial.println("X:" + String(BotX) + String ("YW:")  + String (robotYaw)+ "Y:"  + String(BotY));
//
//  switch (state)
//  {
//      case TowardsStart :
//      fsmFlag = traceLine(BotX, BotY, -60.0 , 60 , 200, speedMode, STOP, 10);
//      if (!fsmFlag)
//      {
//        state = BallPlacing;
//        timer = millis();
//      }
//      break;
//
//      case BallPlacing :
//      
//      calculateSpeed(-omegacontrol, 0, 0);
//      if ( (millis() - timer) >= 1000)
//      {
////        ppidOmega->required = -90;
//        state = BallPlacing2;
//        timer = millis();
//      }
//      break;
//
//      case BallPlacing2 :
//      
//      calculateSpeed(-omegacontrol, 0, 0);
//      if ( (millis() - timer) >= 1000)
//      {
////        ppidOmega->required = -90;
//        state = TowardsKick;
//        timer = millis();
//      }
//      break;
//
//    case TowardsKick:
////      ppidOmega->required = -90;
//      fsmFlag = traceLine(BotX, BotY, -307.5  , 875 , 200, speedMode, STOP, 10);
//      if (!fsmFlag)
//      {
//        state = kicking;
//        timer = millis();
//      }
//      break;
//    case kicking:
//      calculateSpeed(-omegacontrol, 0, 0);
//      if ( (millis() - timer) >= 1000) 
//      {
////        ppidOmega->required = 0;
//        state = BackToRecieving;
//        timer = millis();
//      }
//      break;
//
//    case BackToRecieving:
//      fsmFlag = traceLine(BotX, BotY, -100 , 875 , 200, speedMode, STOP, 10);
//      
//      if (!fsmFlag)
//      {
////        ppidOmega->reqired = 0; 
//        state = stoppp;
//      }
//      break;
//    case stoppp:
//
//      calculateSpeed(-omegacontrol, 0, 0);
//
//      break;
//}
//}
