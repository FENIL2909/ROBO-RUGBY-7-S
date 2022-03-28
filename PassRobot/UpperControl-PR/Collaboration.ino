//void collaborate(float constX, float constY)
//{
//  ppidCollaborateX->required = agentTR.x - (abs(agentTR.x)/agentTR.x)*constX;
//  ppidCollaborateX->required = agentTR.y - (abs(agentTR.y)/agentTR.y)*constY;
//  ppidOmega->required = agentPR.yaw;
//
//  float vX = ppidCollaborateX->pidControl(BotX);
//  float vY = ppidCollaborateX->pidControl(BotY);
//
//  float vBot = sqrt(vX*vX + vY*vY);
//  float angleMove = atan2(vY,vX);
//
//  calculateSpeed(-omegacontrol,angleMove,vBot);
//}
