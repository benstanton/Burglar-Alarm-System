// test arduino program for communication between python and arduino

#include <Arduino.h>


#define motionPin 12

int motionSensorState = 1;
int acknowledgedReq = 0;
int firstContact = 0;
char serialChar = ' ';
int access = false;
unsigned long reqTime = 0;

// F: first time setup
// R: request scan
// a: access granted
// T: stop scanning

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  Serial.begin(9600);
  while(!Serial){} // waiting for serial comms to be ready  
  
  // establishing first contact & response
  while (!firstContact){
    Serial.print('F');
    delay(300);

    //check response
    if (Serial.available() > 0){
      serialChar = Serial.read();
      if (serialChar == 'f'){
        firstContact = true;
      }
    }
  }
  
}

void loop() {

  if (motionSensorState && !acknowledgedReq && !access){
    Serial.print('R'); //request facial scan
    delay(300);

    //long short long
    digitalWrite(LED_BUILTIN, HIGH);
    delay(2000);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(2000);
    digitalWrite(LED_BUILTIN, LOW);
    delay(2000);

    //check response
    if (Serial.available() > 0){
      serialChar = Serial.read();

      if (serialChar == 'r'){
        acknowledgedReq = true;
        reqTime = millis();
      }

      //long short long 
      digitalWrite(LED_BUILTIN, HIGH);
      delay(2000);
      digitalWrite(LED_BUILTIN, LOW);
      delay(500);
      digitalWrite(LED_BUILTIN, HIGH);
      delay(2000);
      digitalWrite(LED_BUILTIN, LOW);
      delay(2000);  
    }
  }

  // do stuff

  //if a request has been acknowledged
  if (acknowledgedReq){
    //read char
    serialChar = Serial.read();

    // check for accses
    if (serialChar = 'a'){
      access = true;

      //high low high low
      digitalWrite(LED_BUILTIN, HIGH);
      delay(500);
      digitalWrite(LED_BUILTIN, LOW);
      delay(500);
      digitalWrite(LED_BUILTIN, HIGH);
      delay(500);
      digitalWrite(LED_BUILTIN, LOW);
      delay(500);  
    }

    // if access granted or 10 sec timeout
    if (reqTime > (millis()+10000) || access){

      // send terminate char
      Serial.print('T');

      // read char
      if (Serial.available() > 0){
        serialChar = Serial.read();

        // if py acknowledges termination, end ackReq reset reqTime        
        if (serialChar = 't'){
            acknowledgedReq = false;
            reqTime = 0;

            digitalWrite(LED_BUILTIN, HIGH);
            delay(500);
            digitalWrite(LED_BUILTIN, LOW);
            delay(500);
            digitalWrite(LED_BUILTIN, HIGH);
            delay(500);
            digitalWrite(LED_BUILTIN, LOW);
            delay(500);  
        }
      }
    }
  }
}