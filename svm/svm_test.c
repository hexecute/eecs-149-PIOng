//Based off code from here:
//https://github.com/Seeed-Studio/IMU_10DOF/blob/master/examples/IMU_10DOF_Test/IMU_10DOF_Test.ino

//Plus a tiny bit of inspiration from this:
//http://www.instructables.com/id/Guide-to-gyro-and-accelerometer-with-Arduino-inclu/

//And from here:
//http://www.geekmomprojects.com/gyroscopes-and-accelerometers-on-a-chip/

#include "Wire.h"
#include "I2Cdev.h"
#include "MPU9250.h"

static float forehand[ 30 ] = {
-5.25,
-2.14,
-2.47,
36.38,
50.46,
24.12,
1.60653426691,
1.0443168107,
-1.02926656983,
-86.9682368345,
626.811839195,
-186.969748739,
-6.07982927551,
3.13156646304,
-11.469749861,
-133.337042673,
120.776724241,
-90.7193676414,
-1.53967904896,
1.1946461492,
-1.56264360755,
-254.2036633,
-616.626075757,
-12.8100311632,
-4.65,
-2.34,
-3.12,
-9.68,
32.89,
39.28,
};

static float drive[ 30 ] = {
-0.45,
-10.71,
-3.9,
3.23,
-3.47,
-46.48,
-0.470813212259,
-9.48840676812,
-4.66663848521,
107.479993289,
-117.012193597,
-126.672533461,
2.26477041946,
-21.5133333523,
-1.4776744926,
88.4697588697,
5.2776016115,
-55.4063724691,
-0.581141259371,
-7.93894033404,
-4.06835177701,
-45.0491805292,
94.0942960477,
405.40743997,
-0.08,
-10.57,
-3.45,
15.16,
-50.26,
-69.2,
};

MPU9250 chip;
I2Cdev I2C_M;

int a_xyz[3];
int g_xyz[3];
int m_xyz[3];

String logger[20];

unsigned long recordedTime;
unsigned long startingTime;
unsigned long t2,t1;

float data[ 30 ];
int n = 0, head = 0;

void (*reset)() = 0;

bool is_class( float *stroke, float *vector )
{
  int i;
  float sum = 0.0;
  
  for (i = 0; i < 45; i++)
    sum = sum + stroke[i] * vector[i];
  
  return sum > 0;
}

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
  
  chip.getMotion9(&(a_xyz[0]), &(a_xyz[1]), &(a_xyz[2]), &(g_xyz[0]), &(g_xyz[1]), &(g_xyz[2]), &(m_xyz[0]), &(m_xyz[1]), &(m_xyz[2]));

  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  while (Serial.readString() != "s")
  {
  chip.getMotion9(&(a_xyz[0]), &(a_xyz[1]), &(a_xyz[2]), &(g_xyz[0]), &(g_xyz[1]), &(g_xyz[2]), &(m_xyz[0]), &(m_xyz[1]), &(m_xyz[2]));
    /*
    getFilteredAccelData();
    getPseudoVelocity();
    getFilteredGyroData();
    
    Serial.print("I");
    Serial.print(",");
    Serial.print(0);
    Serial.print(",");
    Serial.print(180);
    Serial.print(",");   
    Serial.println(atan2(sqrt(sq(a_xyz[0])) + sq(a_xyz[1]), a_xyz[2]) * RAD2DEG);
    */

    recordedTime = millis();
  }
  startingTime = millis();
  t1 = millis();

  int i;
  for (i = 0; i < 30; i++)
    data[ i ] = 0;

  head = 0;
  n = 0;
}


void loop()
{
  int type = 0;

  recordedTime = millis();

  unsigned long timestamp = (recordedTime-startingTime);
  //Serial.println( timestamp );

  chip.getMotion6(&(a_xyz[0]), &(a_xyz[1]), &(a_xyz[2]), &(g_xyz[0]), &(g_xyz[1]), &(g_xyz[2]));

  data[ head ] = data[ head ] + a_xyz[0] / 16384;
  data[ head + 1 ] = data[ head + 1 ] + a_xyz[1] / 16384;
  data[ head + 2 ] = data[ head + 2 ] + a_xyz[2] / 16384;
  data[ head + 3 ] = data[ head + 3 ] + g_xyz[0] * 250 / 32768;
  data[ head + 4 ] = data[ head + 4 ] + g_xyz[1] * 250 / 32768;
  data[ head + 5 ] = data[ head + 5 ] + g_xyz[2] * 250 / 32768;
  n++;

  // Move onto next 5th time segment
  if ( timestamp > 600 )
  {
    // Update startingTime as soon as possible
    startingTime = millis();
    Serial.print("---");

    data[ head ] = data[ head ] / n;
    data[ head + 1 ] = data[ head + 1 ] / n;
    data[ head + 2 ] = data[ head + 2 ] / n;
    data[ head + 3 ] = data[ head + 3 ] / n;
    data[ head + 4 ] = data[ head + 4 ] / n;
    data[ head + 5 ] = data[ head + 5 ] / n;

    // Update n, head
    n = 0;
    if (head == 24)
      head = 0;
    else
      head = head + 6;

    // Classification
    if (is_class( data, forehand ))
      // type = type + 2;
      Serial.print( "forehand " );
    else
      Serial.print( "backhand " );
    if (is_class( data, drive ))
      // type = type + 1;
      Serial.println( "drive" );
    else
      Serial.println( "chop" );

    // Serial.println(type);

    data[ head ] = 0;
    data[ head + 1 ] = 0;
    data[ head + 2 ] = 0;
    data[ head + 3 ] = 0;
    data[ head + 4 ] = 0;
    data[ head + 5 ] = 0;
  }
}
