/*
* Arduino Wireless Communication Tutorial
*     Example 1 - Transmitter Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>
#include <I2Cdev.h>
#include <MPU6050.h>

MPU6050 mpu;


RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";

void setup() {
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  pinMode(6,INPUT);
  Wire.begin();
  mpu.initialize();
}

void loop() {
 
  if(digitalRead(6)==1){
     const char text[] = "top";
    radio.write(&text, sizeof(text));
  }


  int16_t ax, ay, az;
  mpu.getMotion6(&ax, &ay, &az, 0, 0, 0);
  Serial.print("X Ekseni: ");
  float x=(float)ax / 16384.0;
  float y=(float)ay / 16384.0;
  float z=(float)az / 16384.0;
  Serial.print(x);
  Serial.print("   Y Ekseni: ");
  Serial.print(y);
  Serial.print("   Z Ekseni: ");
  Serial.println(z);

  if(x<-0.6){
    const char text[] = "left";
    radio.write(&text, sizeof(text));
  }
  else if(x>0.4){
    const char text[] = "right";
    radio.write(&text, sizeof(text));
  }

  if(y<-0.4){
    const char text[] = "bottom";
    radio.write(&text, sizeof(text));
  }
  else if(y>0.4){
    const char text[] = "top";
    radio.write(&text, sizeof(text));
  }
  
  delay(100);
}
