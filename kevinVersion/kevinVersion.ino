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

float currPseudoPowerLevel[3];

unsigned long recordedTime;

void (*reset)() = 0;

void setup()
{
  // join I2C bus (I2Cdev library doesn't do this automatically)
  Wire.begin();

  // initialize serial communication
  Serial.begin(9600);
  Serial.setTimeout(150);
  
  Serial.println("Initializing chip...");
  chip.initialize();
  Serial.println("Done initializing chip!");
  
  Serial.println(chip.testConnection() ? "Connection successful" : "Connection failed");
  recordedTime = millis();
  
  getRawAccelData();
  getRawGyroData();
  
  while (Serial.readString() != "s")
  {
    getFilteredAccelData();
    getPseudoPowerLevel();
    getFilteredGyroData();
    
    Serial.print("I");
    Serial.print(",");
    Serial.print(atan2(a_xyz[1], sqrt(sq(a_xyz[0])) + sq(a_xyz[2])) * (180.0 / PI));
    //Serial.print(0);
    Serial.print(",");        
    Serial.print(atan2(a_xyz[0], sqrt(sq(a_xyz[0])) + sq(a_xyz[2])) * (180.0 / PI));
    //Serial.print(180);
    Serial.print(",");   
    Serial.println(atan2(sqrt(sq(a_xyz[0]) + sq(a_xyz[1])), a_xyz[2]) * (180.0 / PI));
    //Serial.println(0);


    recordedTime = millis();
  }
  
}

void loop()
{
  if (Serial.readString() == "r")
  {
    reset();
  }
  
  getFilteredAccelData();
  getPseudoPowerLevel();
  getFilteredGyroData(); 

  recordedTime = millis();

  Serial.print(currPseudoPowerLevel[0]);
  Serial.print(",");
  Serial.print(currPseudoPowerLevel[1]);
  Serial.print(",");
  Serial.print(currPseudoPowerLevel[2]);
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
  Serial.println(recordedTime / 1000.0);
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

void getPseudoPowerLevel()
{
  float a_lastFilteredData[3];
  a_lastFilteredData[0] = a_xyz[0];
  a_lastFilteredData[1] = a_xyz[1];
  a_lastFilteredData[2] = a_xyz[2];
  
  getFilteredAccelData();
  
  currPseudoPowerLevel[0] = a_xyz[0] - a_lastFilteredData[0];
  currPseudoPowerLevel[1] = a_xyz[1] - a_lastFilteredData[1];
  currPseudoPowerLevel[2] = a_xyz[2] - a_lastFilteredData[2];
}

float lowPassFilter(float rawData, float filterValue, float lastFilteredData)
{
  return (rawData * filterValue) + (lastFilteredData * (1 - filterValue));  
}
