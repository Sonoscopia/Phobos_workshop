#include <Servo.h>
Servo servo1, servo2, servo3; 
byte pos1[2], pos2[2], pos3[2]; //store current servo position and previous position

byte input[2]; 

void setup() {
  Serial.begin(115200);
  Serial.println("ready");
  for(int i = 2; i < 11; i++)
  {
    pinMode(i, OUTPUT);
  }
  servo1.attach(44);
  servo2.attach(45);
  servo3.attach(46);
}

void loop() {
    bool reading = false; 
    byte count = 0; 
    while( Serial.available() > 1){ 
      reading = true; 
      input[count] = Serial.parseInt(); 
      //Serial.println(Serial.parseInt());
      count++;
      delay(1);
    }
    if(reading)
    {
      /*Serial.print(input[0]);
      Serial.print(" ");
      Serial.println(input[1]);*/   
      switch(input[0])
      {
        case 44:
          pos1[0] = input[1];
          if(pos1[0] != pos1[1])
          {
            servo1.write(input[1]);
            pos1[1] = pos1[0];
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

        default:
          if(input[0] > 1 && input[0] < 14)
          {
            analogWrite(input[0], input[1] * 2);
          }
          break; 
      }
    }
} 

