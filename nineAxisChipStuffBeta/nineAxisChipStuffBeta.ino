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

boolean state1 = false;


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
  
  getRawAccelData();
  getRawGyroData();

  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  while (Serial.readString() != "s")
  {
    getFilteredAccelData();
    getPseudoVelocity();
    getFilteredGyroData();
    
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
  startingTime = millis();
  t1 = millis();
  
}

void loop()
{
  String input = Serial.readString();
  if (input == "r")
  {
    reset();
  }
  else if (input == "l")
  {
    /*logger[i] = String("Reading:" +
      String(a_xyz[0]) + "," +
      String(a_xyz[1]) + "," +
      String(a_xyz[2]) + "," +
      String(g_xyz[0]) + "," +
      String(g_xyz[1]) + "," +
      String(g_xyz[2]) + "," +
      String(mx) + "," +
      String(my) + "," +
      String(mz) 
      );
      */
      logger[i] = String("Reading Time:" + String((recordedTime-startingTime)/ 1000.0));
      
    //Serial.println(logger[i]);
    //Serial.println(a_xyz[0] + "lol");
    //Serial.println("lalala");
    i++;
    if(i==9) input = "e";
      
  }
  else if (input == "e")
  {
    stillLogging = !stillLogging;
    i=0;
    while(i<10){
    Serial.println(logger[i]);
    i++;
    }
  }
  if(stillLogging){
  //getFilteredAccelData();
  //getPseudoVelocity();
  //getFilteredGyroData(); 

  getRawAccelData();
  getRawGyroData();
  recordedTime = millis();
  
  
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
    state1 = true;
    }else{
      t1=millis();
      }
      */
  //Mid region
  //Attempting basic classifier considering only the mid region from the STL formula  
  /*
  if(!state1 && az> 0.65 and ay> 0.2 and ax>0.3){
    t2 = millis()/1000.0;
    state1 = true;
    digitalWrite(13, HIGH);
    }
  if (state1 && t2-(millis()/1000.0)>3.0){
    state1 = false;
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

  if state1 and state2, and condition

*/
  
 }

//Mid region

  //Attempting basic classifier considering only the mid region from the STL formula  
  getRawAccelData();
  if(!state1 && az> 0.65 and ay> 0.2 and ax>0.3){
    t2 = millis()/1000.0;
    state1 = true;
    digitalWrite(13, HIGH);
    }
  if (state1 && (millis()/1000.0)-t2>2.0){
    state1 = false;
    digitalWrite(13, LOW);
   }
  
  /*
  //chip.getMotion9(&ax, &ay, &az, &gx, &gy, &gz, &mx, &my, &mz);
  recordedTime = millis();
  Serial.print(recordedTime / 1000.0);
  Serial.print(",");
  Serial.print(ax);
  Serial.print(",");
  Serial.print(ay);
  Serial.print(",");
  Serial.print(az);
  Serial.print(",");
  Serial.print(gx);
  Serial.print(",");
  Serial.print(gy);
  Serial.print(",");
  Serial.print(gz);
  Serial.print(",");
  Serial.print(mx);
  Serial.print(",");
  Serial.print(my);
  Serial.print(",");
  Serial.println(mz);
  */
  
  /*
  Serial.print(currPseudoVelocity[0]);
  Serial.print(",");
  Serial.print(currPseudoVelocity[1]);
  Serial.print(",");
  Serial.print(currPseudoVelocity[2]);
  Serial.print(",");
  Serial.print(g_xyz[0]);
  Serial.print(",");
  Serial.print(g_xyz[1]);
  Serial.print(",");
  Serial.print(g_xyz[2]);
  Serial.print(",");
  Serial.println(recordedTime / 1000.0);
  */
  //delay(80);
}

void getRawAccelData()
{
  chip.getMotion9(&ax, &ay, &az, &gx, &gy, &gz, &mx, &my, &mz);
  
  a_xyz[0] = (float) ax / 16384;
  a_xyz[1] = (float) ay / 16384;
  a_xyz[2] = (float) az / 16384;
}

void getRawGyroData()
{
  chip.getMotion9(&ax, &ay, &az, &gx, &gy, &gz, &mx, &my, &mz);
  
  g_xyz[0] = (float) gx * 250 / 32768;
  g_xyz[1] = (float) gy * 250 / 32768;
  g_xyz[2] = (float) gz * 250 / 32768;
}

void getFilteredAccelData()
{
  float a_lastFilteredData[3];
  a_lastFilteredData[0] = a_xyz[0];
  a_lastFilteredData[1] = a_xyz[1];
  a_lastFilteredData[2] = a_xyz[2];
  
  getRawAccelData();
  
  
  a_xyz[0] = lowPassFilter(a_xyz[0], 0.1, a_lastFilteredData[0]);
  a_xyz[1] = lowPassFilter(a_xyz[1], 0.1, a_lastFilteredData[1]);
  a_xyz[2] = lowPassFilter(a_xyz[2], 0.1, a_lastFilteredData[2]);
}

void getFilteredGyroData()
{
  float g_lastFilteredData[3];
  g_lastFilteredData[0] = g_xyz[0];
  g_lastFilteredData[1] = g_xyz[1];
  g_lastFilteredData[2] = g_xyz[2];
  
  getRawGyroData();
  
  g_xyz[0] = (0.98 * lowPassFilter(g_xyz[0], 0.01, g_lastFilteredData[0]) * 0.15) + (0.02 * a_xyz[0]);
  g_xyz[1] = (0.98 * lowPassFilter(g_xyz[1], 0.01, g_lastFilteredData[1]) * 0.15) + (0.02 * a_xyz[1]);
  g_xyz[2] = (0.98 * lowPassFilter(g_xyz[2], 0.01, g_lastFilteredData[2]) * 0.15) + (0.02 * a_xyz[2]) - 0.02;
}

void getPseudoVelocity()
{
  float a_lastFilteredData[3];
  a_lastFilteredData[0] = a_xyz[0];
  a_lastFilteredData[1] = a_xyz[1];
  a_lastFilteredData[2] = a_xyz[2];
  
  getFilteredAccelData();
  
  currPseudoVelocity[0] = a_xyz[0] - a_lastFilteredData[0];
  currPseudoVelocity[1] = a_xyz[1] - a_lastFilteredData[1];
  currPseudoVelocity[2] = a_xyz[2] - a_lastFilteredData[2];
}

float lowPassFilter(float rawData, float filterValue, float lastFilteredData)
{
  return (rawData * filterValue) + (lastFilteredData * (1 - filterValue));  
}
 