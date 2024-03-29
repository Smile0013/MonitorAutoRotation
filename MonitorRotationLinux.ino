#include <Keyboard.h> // The main library for sending keystrokes to pc
#include <Wire.h> // This library allows you to communicate with I2C devices.

const int MPU_ADDR = 0x68; // I2C address of the MPU-6050. If AD0 pin is set to HIGH, the I2C address will be 0x69.

int16_t rAccelerometerX, rAccelerometerY, rAccelerometerZ; // variables for accelerometer raw data
int16_t rGyroX, rGyroY, rGyroZ; // variables for gyro raw data
int16_t rTemperature; // variables for temperature data

// orientation of screen
int orientation;
int oldOrientation;

// as I use croatian keyboard and library is for american / reprisents -
// enter the name of your sscreen
String screenName = "eDP";   //HDMI/A/0

// how fast movment needs to be for screen to rotate
int16_t systemSensitivity = 10000;
// direction of sensor spin 1 cv, -1 ccv
int rotetionalModifier = 1;

void setup() {
  // initialise all librarys
  Keyboard.begin();
  Wire.begin();
  
  Wire.beginTransmission(MPU_ADDR); // Begins a transmission to the I2C slave (GY-521 board)
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0); // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  
  // set orientation of the screen to normal
  orientation = 0;
  oldOrientation = orientation;
}

void loop() {
  
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 7*2, true);
  
  rAccelerometerX = Wire.read()<<8 | Wire.read();
  rAccelerometerY = Wire.read()<<8 | Wire.read();
  rAccelerometerZ = Wire.read()<<8 | Wire.read();
  rTemperature = Wire.read()<<8 | Wire.read();
  rGyroX = Wire.read()<<8 | Wire.read();
  rGyroY = Wire.read()<<8 | Wire.read();
  rGyroZ = Wire.read()<<8 | Wire.read();

  if (rGyroZ > systemSensitivity){
    orientation += rotetionalModifier;
  }
  if (rGyroZ < (-1 * systemSensitivity)){
    orientation += -1 * rotetionalModifier;
  }
  
  // orientation correction
  if (orientation < 0){ // loop orientation from min value to max value
    orientation = 3;
  }
  if (orientation > 3){ // loop orientation from max value to min value
    orientation = 0;
  }

  // rotate screen to corect orientation
  if (orientation != oldOrientation){
    screen_rotate(orientation);
    oldOrientation = orientation;
  }
  
}

void screen_rotate(int direction) {

  // open terminal for Linux
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press('t');
  delay(200);
  Keyboard.releaseAll();
  delay(150);
  
  // print command for rotating screen
  Keyboard.print("xrandr //output "); // replace // with -- for american keyboard
  delay(5);
  Keyboard.print(screenName);
  delay(5);
  Keyboard.print(" //rotate "); // replace // with -- for american keyboard

  // select direction of orientation
  if (direction == 0){  // return to normal
    Keyboard.print("normal");
  }
  if (direction == 1){  // rotate left
    Keyboard.print("left");
  }
  if (direction == 2){  // invert picture
    Keyboard.print("inverted");
  }
  if (direction == 3){  // rotate right
    Keyboard.print("right");
  }
  delay(5);

  // press enter
  Keyboard.press(KEY_KP_ENTER);
  delay(10);
  Keyboard.releaseAll();

  // print command for closing terminal linux
  Keyboard.print("exit");
  delay(10);

  // press enter
  Keyboard.press(KEY_KP_ENTER);
  delay(10);
  Keyboard.releaseAll();

  
  delay(1500);
}
