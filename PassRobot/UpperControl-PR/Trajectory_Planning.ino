bool traceLine(float x1, float y1, float x2, float y2, float vel, int SpeedMode, int Gmode, float tolerance)
{
  float xd = BotX, yd = BotY, cd = 0, c = 0;
  float m = 0, md = 0;
  float perpendicularDist;
  int sign;

  if (x2 - x1 == 0)
  {
    perpendicularDist = dist(BotX, 0, x2, 0);
    xd = x2; yd = BotY;
  }
  else if (y2 - y1 == 0)
  {
    perpendicularDist = dist(0, BotY, 0, y2);
    yd = y2; xd = BotX;
  }
  else
  {
    m = (y2 - y1) / (x2 - x1);
    c = y2 - m * x2;
    md = -1 / m;
    cd = BotY + BotX / m;
    xd = m * (cd - c) / (1 + m * m);
    yd = md * xd + cd;
    perpendicularDist = dist(BotX, BotY, xd, yd);
  }

  float perpendicularVel = fabs(ppidDistance->pidControl(perpendicularDist));

  float angleFix = Angle(xd, yd, x2, y2);
  float angleGoal = Angle(BotX, BotY, x2, y2);

  float distLeft = dist(x2, y2, BotX, BotY);
  float distMax = dist(x1, y1, x2, y2);
  float normalizedDist = (distMax - distLeft) / distMax;
  float angleMove = 0.0;



  maxSpeed = vel;
  sign = fabs(angleGoal - angleFix) / (angleGoal - angleFix);
  if (fabs(angleGoal - angleFix) > pi)
    sign *= -1;

  speedMode = SpeedMode;
  vel = controlBotSpeed(normalizedDist);

  angleMove = angleFix  + sign * atan2(perpendicularVel, vel);

  if (distLeft <= tolerance)
  {
    if (Gmode == STOP)
      calculateSpeed(-omegacontrol, angleFix, 0);
    return 0;
  }
  calculateSpeed(-omegacontrol, angleMove, sqrt(vel * vel + perpendicularVel * perpendicularVel));

  return 1;
}


bool traceCircle(float h, float k, float finalPointX, float finalPointY, float radius, int mode , float vel, float Gmode, float tolerance)
{
  float angleMove;
  float distLeft = dist(finalPointX, finalPointY, BotX, BotY);
  float distDiff = distLeft - prevDistLeft ;
  prevDistLeft = distLeft;
  ppidCircle->required = radius;

//  printLCD("prev:" + String(prevDistLeft) + String ("New")  + String (distLeft), "Diff"  + String(distDiff));
//  
//  if (distDiff < 0)
//  {
//    if (Gmode == STOP)
//      calculateSpeed(-omegacontrol, 0, 0);
//    return 0;
//  }
//  else
  {
    angleMove = atan2(-(BotX - h), (BotY - k));
    if (angleMove < 0)
      angleMove = 2 * pi + angleMove;
  
    float perpendicularDist = dist(BotX, BotY, h, k);
    float perpendicularVel = ppidCircle->pidControl(perpendicularDist);
  
    if (mode == antiClockwise)
      angleMove = angleMove + pi - atan2(perpendicularVel, vel);
    else
      angleMove = angleMove + atan2(perpendicularVel, vel);
    calculateSpeed(-omegacontrol, angleMove, sqrt(vel * vel + perpendicularVel * perpendicularVel));
  }
  return 1;
}
