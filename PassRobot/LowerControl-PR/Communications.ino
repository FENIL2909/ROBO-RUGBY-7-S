uint8_t zeroCntr = 0;

void getUpperData(){
   while(ET.receiveData()>0)
   {  
    angularV = mydata.omega;
     linearV = mydata.velocity;
     angleTheta = mydata.theta;

     if(ledCntr < 10)
      redLEDoff;
    else if(ledCntr >= 10 && ledCntr < 20 )
      redLEDon;
    else
      ledCntr = 0;
    ledCntr++;

    
   }   
//   angularV = 0;
//   angleTheta = 0;
//   linearV = 200;
    calculateIK(angularV, angleTheta, linearV);

    
}
