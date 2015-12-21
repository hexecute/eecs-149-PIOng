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

PU9250 chip;
I2Cdev I2C_M;

int a_xyz[3];
int g_xyz[3];
int m_xyz[3];

String logger[20];

unsigned long recordedTime;
unsigned long startingTime;

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
  // Unity wait
  while (Serial.readString() != "s");
  startingTime =  millis();

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

  chip.getMotion6( &(a_xyz[0]), &(a_xyz[1]), &(a_xyz[2]), &(g_xyz[0]),
                   &(g_xyz[1]), &(g_xyz[2]) );

  data[ head ] = data[ head ] + a_xyz[0] / 16384;
  data[ head + 1 ] = data[ head + 1 ] + a_xyz[1] / 16384;
  data[ head + 2 ] = data[ head + 2 ] + a_xyz[2] / 16384;
  data[ head + 3 ] = data[ head + 3 ] + g_xyz[0] * 250 / 32768;
  data[ head + 4 ] = data[ head + 4 ] + g_xyz[1] * 250 / 32768;
  data[ head + 5 ] = data[ head + 5 ] + g_xyz[2] * 250 / 32768;
  n++;

  // Move onto next 5th time segment (1 time segment = 3 seconds)
  if ( timestamp > 600 )
  {

    float data_in_order[ 30 ];

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

    // Shuffle circular buffer into the correct order
    // Unfortunately, for loops are slow so....
    data_in_order[0] = data[ head ];
    data_in_order[1] = data[ (head + 1) % 30 ];
    data_in_order[2] = data[ (head + 2) % 30 ];
    data_in_order[3] = data[ (head + 3) % 30 ];
    data_in_order[4] = data[ (head + 4) % 30 ];
    data_in_order[5] = data[ (head + 5) % 30 ];
    data_in_order[6] = data[ (head + 6) % 30 ];
    data_in_order[7] = data[ (head + 7) % 30 ];
    data_in_order[8] = data[ (head + 8) % 30 ];
    data_in_order[9] = data[ (head + 9) % 30 ];
    data_in_order[10] = data[ (head + 10) % 30 ];
    data_in_order[11] = data[ (head + 11) % 30 ];
    data_in_order[12] = data[ (head + 12) % 30 ];
    data_in_order[13] = data[ (head + 13) % 30 ];
    data_in_order[14] = data[ (head + 14) % 30 ];
    data_in_order[15] = data[ (head + 15) % 30 ];
    data_in_order[16] = data[ (head + 16) % 30 ];
    data_in_order[17] = data[ (head + 17) % 30 ];
    data_in_order[18] = data[ (head + 18) % 30 ];
    data_in_order[19] = data[ (head + 19) % 30 ];
    data_in_order[20] = data[ (head + 20) % 30 ];
    data_in_order[21] = data[ (head + 21) % 30 ];
    data_in_order[22] = data[ (head + 22) % 30 ];
    data_in_order[23] = data[ (head + 23) % 30 ];
    data_in_order[24] = data[ (head + 24) % 30 ];
    data_in_order[25] = data[ (head + 25) % 30 ];
    data_in_order[26] = data[ (head + 26) % 30 ];
    data_in_order[27] = data[ (head + 27) % 30 ];
    data_in_order[28] = data[ (head + 28) % 30 ];
    data_in_order[29] = data[ (head + 29) % 30 ];

    // Classification
    if (is_class( data_in_order, forehand ))
      // type = type + 2;
      Serial.print( "Forehand " );
    else
      Serial.print( "Backhand " );
    if (is_class( data_in_order, drive ))
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
