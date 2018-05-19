// Reads serial messages from MaxMSP 
// use pins 2 to 13 for 2-wire actuators (motors, solenoids, etc...)
// use pins 44 to 46 for servo control
// NOTE: this code was made for Arduino MEGA, so you may need to change pins 44~46 on other Arduinos
// Tiago Ângelo 2018 - www.github.com/Sonoscopia/Phobos_workshop/
// you are free to use this code however you wish (but note that it uses the Servo library by Michael Margolis)

#include <Servo.h>
Servo servo1, servo2, servo3; 
byte pos1[2], pos2[2], pos3[2]; //store current servo position and previous position

byte input[2]; 

void setup() {
  Serial.begin(115200); // enable serial communication
  Serial.println("ready");
  
  for(int i = 2; i < 11; i++) // set pins for 2-wire actuators
  {
    pinMode(i, OUTPUT);
  }
  
  servo1.attach(44); // set pins for servos
  servo2.attach(45);
  servo3.attach(46);
}

void loop() {
    // read incoming serial messages
    bool reading = false; 
    byte count = 0; 
    while( Serial.available() > 1){ 
      reading = true; 
      input[count] = Serial.parseInt(); 
      //Serial.println(Serial.parseInt());
      count++;
      delay(1);
    }
    // if there was a serial message received do something
    if(reading)
    {
      /*Serial.print(input[0]);
      Serial.print(" ");
      Serial.println(input[1]);*/   
      switch(input[0])
      {
        // control servos
        case 44:
          pos1[0] = input[1];
          if(pos1[0] != pos1[1]) // if position value changes 
          {
            servo1.write(input[1]); // move servo to given position 
            pos1[1] = pos1[0]; // and update previous position
          }
          break; 

        case 45:
          pos2[0] = input[1];
          if(pos2[0] != pos2[1])
          {
            servo2.write(input[1]);
            pos2[1] = pos2[0];
          }
          break;

        case 46:
          pos3[0] = input[1];
          if(pos3[0] != pos3[1])
          {
            servo3.write(input[1]);
            pos3[1] = pos3[0];
          }
          break;

        // control 2-wire actuators
        default:
          if(input[0] > 1 && input[0] < 14) // using pins 2 to 13
          {
            analogWrite(input[0], input[1] * 2); // send values from 0 (0V) to 255 (5V)
          }
          break; 
      }
    }
} 

