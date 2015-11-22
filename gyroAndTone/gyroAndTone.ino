#include <Wire.h>

#define CTRL_REG1 0x20
#define CTRL_REG2 0x21
#define CTRL_REG3 0x22
#define CTRL_REG4 0x23

const int piezoPin = 7;

//Note: All the code for reading the gyro values were taken from
//this site: http://learn.parallax.com/KickStart/27911

//Dividing by 114 reduces noise
const int noiseReductionNumber = 114;


int Addr = 105;                 // I2C address of gyro
int x, y, z;

void setup()
{
  Wire.begin();
  Serial.begin(9600);
  writeI2C(CTRL_REG1, 0x1F);    // Turn on all axes, disable power down
  writeI2C(CTRL_REG3, 0x08);    // Enable control ready signal
  writeI2C(CTRL_REG4, 0x80);    // Set scale (500 deg/sec)
  delay(100);                   // Wait to synchronize 
}

void loop()
{
  getGyroValues();              // Get new values
  
  Serial.print(x); 
  
  Serial.print(",");
  Serial.print(y);
  
  Serial.print(",");
  Serial.println(z);

  tone(piezoPin, 80 + abs(x) + abs(y) + abs(z));
  delay(150);
}

void getGyroValues()
{
  byte MSB, LSB;

  MSB = readI2C(0x29);
  LSB = readI2C(0x28);
  x = ((MSB << 8) | LSB) / noiseReductionNumber;

  MSB = readI2C(0x2B);
  LSB = readI2C(0x2A);
  y = ((MSB << 8) | LSB) / noiseReductionNumber;

  MSB = readI2C(0x2D);
  LSB = readI2C(0x2C);
  z = ((MSB << 8) | LSB) / noiseReductionNumber;
}

int readI2C(byte regAddr)
{
    Wire.beginTransmission(Addr);
    Wire.write(regAddr);                // Register address to read
    Wire.endTransmission();             // Terminate request
    Wire.requestFrom(Addr, 1);          // Read a byte
    while(!Wire.available()) { };       // Wait for receipt
    return(Wire.read());                // Get result
}

void writeI2C(byte regAddr, byte val)
{
    Wire.beginTransmission(Addr);
    Wire.write(regAddr);
    Wire.write(val);
    Wire.endTransmission();
}
