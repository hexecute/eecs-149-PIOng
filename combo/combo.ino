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

int16_t ax, ay, az;
int16_t gx, gy, gz;
int16_t mx, my, mz;

float a_xyz[3];
float g_xyz[3];
float m_xyz[3];

int peter_a_xyz[3];
int peter_g_xyz[3];

String logger[20];
int i = 0;
boolean stillLogging = true;

unsigned long recordedTime;
unsigned long startingTime;
unsigned long t2,t1;

boolean stateFD = false;
boolean stateFC = false;
boolean stateBD = false;
boolean stateBC = false;

float data[ 30 ];
int n = 0, head = 0;

boolean doingShitFromOmar;
boolean doingShitFromPeter;
boolean doingShitFromKevin;

float currPseudoPowerLevel[3];

void (*reset)() = 0;

bool is_class( float *stroke, float *vector )
{
  int i;
  float sum = 0.0;
  
  for (i = 0; i < 45; i++)
  {
    sum = sum + stroke[i] * vector[i];
  }
  
  return sum > 0;
}

void setup()
{
  doingShitFromOmar = false;
  doingShitFromPeter = false;
  doingShitFromKevin = false;
  
  // join I2C bus (I2Cdev library doesn't do this automatically)
  Wire.begin();

  // initialize serial communication
  Serial.begin(9600);
  Serial.setTimeout(1);
  
  Serial.println("Initializing chip...");
  chip.initialize();
  Serial.println("Done initializing chip!");
  
  Serial.println(chip.testConnection() ? "Connection successful" : "Connection failed");

  String serialInput = Serial.readString();
  while ((serialInput != "o") && (serialInput != "p") && (serialInput != "k"))
  {
    serialInput = Serial.readString();
  }
  Serial.print("done.  starting with: ");
  Serial.println(serialInput);
  
  if (serialInput == "o")
  {
    doingShitFromOmar = true;
    doingShitFromPeter = false;
    doingShitFromKevin = false;
  }
  else if (serialInput == "p")
  {
    doingShitFromOmar = false;
    doingShitFromPeter = true;
    doingShitFromKevin = false;
  }
  else if (serialInput == "k")
  {
    doingShitFromOmar = false;
    doingShitFromPeter = false;
    doingShitFromKevin = true;
  }

  if (doingShitFromOmar)
  {
    startingTime = millis();
    
    getRawData();
  
    pinMode(10, OUTPUT);
    pinMode(11, OUTPUT);
    pinMode(12, OUTPUT);
    
    recordedTime = millis();
    startingTime = millis();
    t1 = millis();
  }

  if (doingShitFromPeter)
  {
    recordedTime = millis();
    startingTime = millis();
    t1 = millis();
  
    int i;
    for (i = 0; i < 30; i++)
      data[ i ] = 0;
  
    head = 0;
    n = 0;
  }

  if (doingShitFromKevin)
  {
    recordedTime = millis();
  
    getRawAccelData();
    getRawGyroData();
    
    while (Serial.readString() != "s")
    {
      getFilteredAccelData();
      getPseudoPowerLevel();
      getFilteredGyroData();
  
      recordedTime = millis();
    }
  }
}

void loop()
{
  String serialInput = Serial.readString();
  if (serialInput == "r")
  {
    reset();
  }
  if (serialInput == "o")
  {
    doingShitFromOmar = true;
    doingShitFromPeter = false;
    doingShitFromKevin = false;
  }
  else if (serialInput == "p")
  {
    doingShitFromOmar = false;
    doingShitFromPeter = true;
    doingShitFromKevin = false;
  }
  else if (serialInput == "k")
  {
    doingShitFromOmar = false;
    doingShitFromPeter = false;
    doingShitFromKevin = true;
  }

  if (doingShitFromOmar)
  { 
    if(stillLogging)
    {
      getRawData();
      recordedTime = millis();
    }
  
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
      digitalWrite(11, HIGH);
      digitalWrite(12, HIGH);
      
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

  if (doingShitFromPeter)
  {
    recordedTime = millis();
  
    unsigned long timestamp = (recordedTime - startingTime);
  
    chip.getMotion6(&(peter_a_xyz[0]), &(peter_a_xyz[1]), &(peter_a_xyz[2]), &(peter_g_xyz[0]), &(peter_g_xyz[1]), &(peter_g_xyz[2]));
  
    data[ head ] = data[ head ] + peter_a_xyz[0] / 16384;
    data[ head + 1 ] = data[ head + 1 ] + peter_a_xyz[1] / 16384;
    data[ head + 2 ] = data[ head + 2 ] + peter_a_xyz[2] / 16384;
    data[ head + 3 ] = data[ head + 3 ] + peter_g_xyz[0] * 250 / 32768;
    data[ head + 4 ] = data[ head + 4 ] + peter_g_xyz[1] * 250 / 32768;
    data[ head + 5 ] = data[ head + 5 ] + peter_g_xyz[2] * 250 / 32768;
    n++;
  
    // Move onto next 5th time segment
    if ( timestamp > 600 )
    {

      float data_in_order[30];

      // Update startingTime as soon as possible
      startingTime = millis();
      Serial.print("-");
  
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
        Serial.print( "forehand " );
      else
        Serial.print( "backhand " );
      if (is_class( data_in_order, drive ))
        Serial.println( "drive" );
      else
        Serial.println( "chop" );
  
      data[ head ] = 0;
      data[ head + 1 ] = 0;
      data[ head + 2 ] = 0;
      data[ head + 3 ] = 0;
      data[ head + 4 ] = 0;
      data[ head + 5 ] = 0;
    }
  }

  if (doingShitFromKevin)
  {
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
