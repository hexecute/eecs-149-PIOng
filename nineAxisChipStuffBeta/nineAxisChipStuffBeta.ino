//Based off code from here:
//https://github.com/Seeed-Studio/IMU_10DOF/blob/master/examples/IMU_10DOF_Test/IMU_10DOF_Test.ino

//Plus a tiny bit of inspiration from this:
//http://www.instructables.com/id/Guide-to-gyro-and-accelerometer-with-Arduino-inclu/

//And from here:
//http://www.geekmomprojects.com/gyroscopes-and-accelerometers-on-a-chip/

#include "Wire.h"
#include "I2Cdev.h"
#include "MPU9250.h"

MPU9250 chip;
I2Cdev I2C_M;

int16_t ax, ay, az;
int16_t gx, gy, gz;
int16_t mx, my, mz;

float a_xyz[3];
float g_xyz[3];
float m_xyz[3];

String logger[20];
int i=0;
boolean stillLogging = true;

float currPseudoVelocity[3];
float RAD2DEG = 180 / PI;
unsigned long recordedTime;
unsigned long startingTime;
unsigned long t2,t1;

boolean stateFD = false;
boolean stateFC = false;
boolean stateBD = false;
boolean stateBC = false;


void (*reset)() = 0;

void setup()
{
  // join I2C bus (I2Cdev library doesn't do this automatically)
  Wire.begin();

  // initialize serial communication
  Serial.begin(9600);
  Serial.setTimeout(1);
  
  Serial.println("Initializing chip...");
  chip.initialize();
  Serial.println("Done initializing chip!");
  
  Serial.println(chip.testConnection() ? "Connection successful" : "Connection failed");
  startingTime = millis();
  
  getRawData();

  pinMode(13, OUTPUT);

  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  
  digitalWrite(13, LOW);
  //digitalWrite(10, HIGH);
  
  
  
  /*
  while (Serial.readString() != "s")
  {
    
    Serial.print("I");
    Serial.print(",");
    //Serial.print(atan2(a_xyz[1], sqrt(sq(a_xyz[0])) + sq(a_xyz[2])) * RAD2DEG);
    Serial.print(0);
    Serial.print(",");        
    //Serial.print(atan2(a_xyz[0], sqrt(sq(a_xyz[0])) + sq(a_xyz[2])) * RAD2DEG);
    Serial.print(180);
    Serial.print(",");   
    Serial.println(atan2(sqrt(sq(a_xyz[0])) + sq(a_xyz[1]), a_xyz[2]) * RAD2DEG);
    //Serial.println(0);


    recordedTime = millis();
  }
  */
  recordedTime = millis();
  startingTime = millis();
  t1 = millis();
  
}

void loop()
{
  /*String input = Serial.readString();
  if (input == "r")
  {
    reset();
  }
  */
  
  if(stillLogging){
  //getFilteredAccelData();
  //getPseudoVelocity();
  //getFilteredGyroData(); 

  getRawData();
  recordedTime = millis();
  
  /*
  Serial.print((recordedTime-startingTime) / 1000.0);
  Serial.print(",");
  Serial.print(a_xyz[0]);
  Serial.print(",");
  Serial.print(a_xyz[1]);
  Serial.print(",");
  Serial.print(a_xyz[2]);
  Serial.print(",");
  Serial.print(g_xyz[0]);
  Serial.print(",");
  Serial.print(g_xyz[1]);
  Serial.print(",");
  Serial.print(g_xyz[2]);
  Serial.print(",");
  Serial.print(mx);
  Serial.print(",");
  Serial.print(my);
  Serial.print(",");
  Serial.println(mz);
*/


  //Starting realtime check for forehand drive..
  /*
  param preMidTime = 1.49
  param midTime_1 = 1.55
  param midTime_2 = 1.94
  param postMidTime = 1.99

  # define region
  preMid := ay[t]<1.0
  mid := az[t]> 0.65 and ay[t]> 0 and ax[t]>0
  postMid := ay[t]< 0 and ax[t]<0
  
  
  # counter property  
  
  preMidProperty := ev_[0, preMidTime] preMid
  midProperty := ev_[ midTime_1, midTime_2 ] mid
  postMidProperty := ev_[postMidTime, Tmax] postMid
    
  */
  
  //check pre region
  //if at time t1
  /*if(ay<1.0 && t1 - millis()<threshold){ 
    stateFD = true;
    }else{
      t1=millis();
      }
      */
  //Mid region
  //Attempting basic classifier considering only the mid region from the STL formula  
  /*
  if(!stateFD && az> 0.65 and ay> 0.2 and ax>0.3){
    t2 = millis()/1000.0;
    stateFD = true;
    digitalWrite(13, HIGH);
    }
  if (stateFD && t2-(millis()/1000.0)>3.0){
    stateFD = false;
    digitalWrite(13, LOW);
   }
   */
    
  /*
  t2 = current time
  if at time t2-t1>threshold()
else t1 = current time
  */
  //Post region
  /*

  if stateFD and state2, and condition

*/
  
 }

//Mid region

  //Attempting basic classifier considering only the mid region from the STL formula  
  getRawData();
  //FD
  
  if(!stateFD && !stateFC && !stateBD && !stateBC && a_xyz[0]> 0.3 && a_xyz[1]<0.2 && a_xyz[2]> 0.65){
    t2 = millis()/1000.0;
    stateFD = true;
    delay(20);
    getRawData();
    if(a_xyz[0]> 0.3 && a_xyz[1]<0.2 && a_xyz[2]> 0.65)
    digitalWrite(10, HIGH);
    
    }
  //BD
  if(!stateFD && !stateFC && !stateBD && !stateBC && a_xyz[0]> 0.2 && a_xyz[1]>0.65 && a_xyz[2]< 0){
    t2 = millis()/1000.0;
    stateBD = true;
    digitalWrite(11, HIGH);
    }
    
  //BC  
  if(!stateFD && !stateFC && !stateBD && !stateBC && a_xyz[0]< 0 && a_xyz[1]<-1.3 && a_xyz[2]> 0.85){
    t2 = millis()/1000.0;
    stateBC = true;
    //delay(15);
    //getRawData();
    //if(a_xyz[0]< 0 && a_xyz[1]<-1.3 && a_xyz[2]> 0.85){
    digitalWrite(11, HIGH);
    digitalWrite(12, HIGH);
    //}
    
  }
  
  //FC  
  if(!stateFD && !stateFC && !stateBD && !stateBC && a_xyz[0]> 0.15 && a_xyz[1]<-1.2 && a_xyz[2]> -0.4 && a_xyz[2]< 0){
    t2 = millis()/1000.0;
    stateFC = true;
    digitalWrite(12, HIGH);
  }

  //RESET STATES AND LIGHT  
  if ((stateFD||stateFC||stateBD||stateBC) && (millis()/1000.0)-t2>2.0){
    stateFD = false;
    stateFC = false;
    stateBD = false;
    stateBC = false;
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
   }
  
  
}

void getRawData()
{
  chip.getMotion9(&ax, &ay, &az, &gx, &gy, &gz, &mx, &my, &mz);
  
  a_xyz[0] = (float) ax / 16384;
  a_xyz[1] = (float) ay / 16384;
  a_xyz[2] = (float) az / 16384;
  g_xyz[0] = (float) gx * 250 / 32768;
  g_xyz[1] = (float) gy * 250 / 32768;
  g_xyz[2] = (float) gz * 250 / 32768;
}
