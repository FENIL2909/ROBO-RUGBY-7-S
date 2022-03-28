enum {Grip, Up, Down, Throw};
int actState = Grip;
int aaa = digitalRead(rstButton);
void actuation(float Xfac, float Yfac)
{
  digitalWrite(gripperUp, HIGH);
  digitalWrite(gripperDown, HIGH);
  digitalWrite(throwBall, HIGH);
  readIR = digitalRead(IRpin);
  
  
  switch(actState)
  {
      case Grip:
            if(!aaa)
            {
              actuationFlag = 0;
            }
            if(actuationFlag == 0)
            {
              calculateSpeed(-omegacontrol, DegreeToRadian(150),200);
              if(!readIR)
               {
                 calculateSpeed(-omegacontrol, 0,0);
                 digitalWrite(MotorPin1, LOW);
                 digitalWrite(MotorPin2, HIGH);
                 digitalWrite(MotorPWM, HIGH);
                 actState= Up;
                 Tgrip = millis();
               }
            }
            else
            {
              calculateSpeed(-omegacontrol,0,0);
            }
            
            
            
      break;

      case Up:
            if(millis() - Tgrip > 3000)   //////Time required to grip and start going up
            {
              digitalWrite(gripperUp, LOW);
              traceLine(BotX, BotY, BotX - Xfac, BotY - Yfac, 200, STOP, constant, 5);
              if(abs(prevBotX - BotX ) < 0.1 && abs(prevBotY - BotY) < 0.1)
              {
                calculateSpeed(-omegacontrol,0,0);
                digitalWrite(MotorPin1, HIGH);
                digitalWrite(MotorPin2, LOW);
                digitalWrite(MotorPWM, HIGH); 
                Tdrop = millis();
                actState = Down;
              }
            }
      break;

      case Down:
             if(millis() - Tdrop > 500)
             {
              digitalWrite(MotorPin1, LOW);
              digitalWrite(MotorPin2, LOW);
              digitalWrite(MotorPWM, LOW);
              digitalWrite(gripperDown, LOW);
              Tthrow = millis(); 
              actState = Throw;
             }
      break;

      case Throw:
             if(millis() - Tthrow > 3000 )
             {
              digitalWrite(throwBall, LOW);
              actuationFlag = 1;
              actState = Grip;
             }
      break;
      
           
  }
}

