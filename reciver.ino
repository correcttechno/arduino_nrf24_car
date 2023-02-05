/*
* Arduino Wireless Communication Tutorial
*       Example 1 - Receiver Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  pinMode(3,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(9,OUTPUT);

      digitalWrite(3,0);
      digitalWrite(5,0);
      digitalWrite(6,0);
      digitalWrite(9,0);
}

void loop() {
  if (radio.available()) {
    char text[32] = "";
    radio.read(&text, sizeof(text));
    Serial.println(text);
    
    if(String(text)=="top"){
      digitalWrite(3,1);
      digitalWrite(5,0);
      digitalWrite(6,1);
      digitalWrite(9,0);
    }
    else if(String(text)=="bottom"){
      digitalWrite(3,0);
      digitalWrite(5,1);
      digitalWrite(6,0);
      digitalWrite(9,1);
    }

    else if(String(text)=="left"){
      digitalWrite(3,0);
      digitalWrite(5,1);
      digitalWrite(6,1);
      digitalWrite(9,0);
    }
    
    else if(String(text)=="right"){
      digitalWrite(3,1);
      digitalWrite(5,0);
      digitalWrite(6,0);
      digitalWrite(9,1);
   }   
    delay(100);
  }

  digitalWrite(3,0);
  digitalWrite(5,0);
  digitalWrite(6,0);
  digitalWrite(9,0);
  
}
