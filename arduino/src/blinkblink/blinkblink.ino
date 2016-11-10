
#include <RCSwitch.h>

// RCSwitch configuration
RCSwitch mySwitch = RCSwitch();
int numTx = 10;
int tx = 2;
int inputA = 3;
int inputB = 4;
int inputC = 5;
int input1 = 6;
int input2 = 7;
int input3 = 8;
int pins[] = {3,4,5,6,7,8};
boolean switchStatus[] = {false, false, false, false, false, false};
boolean pinValues[] = {false, false, false, false, false, false};
int pulseTime = 0;


/**
 * Setup
 */
void setup() {
  pinMode(tx,OUTPUT);
  for(int i=0; i<=5; i++){
    pinMode(pins[i], INPUT);
    switchStatus[i] = digitalRead(pins[i]);
  }
  digitalWrite(tx, LOW);
  mySwitch.enableTransmit( tx );
  mySwitch.setPulseLength(362);
}

/**
 * Loop
 */
void loop() {
  for(int i=0; i<=5; i++){
    pinValues[i] = digitalRead(pins[i]);
    if(pinValues[i] != switchStatus[i]){
      transmitChannel(i, pinValues[i]);
      switchStatus[i] = !switchStatus[i];
    }
  }
/*  if(digitalRead(inputA) == 1){
    //toggle('a');
    delay(200);
  }
  if(digitalRead(inputB) == 1){
    //toggle('b');
    delay(200);
  }
  if(digitalRead(inputC) == 1){
    //toggle('c');
    delay(200);
  }
  if(digitalRead(input1) == 1){
    //toggle('1');
    delay(200);
  }
  if(digitalRead(input2) == 1){
    //toggle('2');
    delay(200);
  }
  if(digitalRead(input3) == 1){
    //toggle('3');
    delay(200);
  }
  */
//  sendAon();
//  delay(2000);
//  sendBon();
//  delay(200);
//  sendCon();
//  delay(200);
//  send1on();
//  delay(200);
//  send2on();
//  delay(200);
//  send3on();
//  delay(200);
//  sendAoff();
//  delay(2000);
//  sendBoff();
//  delay(200);
//  sendCoff();
//  delay(200);
//  send1off();
//  delay(200);
//  send2off();
//  delay(200);
//  send3off();
//  delay(200);
}

void transmit(int pin, boolean state){
  long del = micros();
  if(state){
    digitalWrite(pin, HIGH);
    while((micros() - del) < 200){
    }      //pause
    del = micros();
    digitalWrite(pin, LOW);
    while((micros() - del) < 425){
    }      //pulse
  }
  else{
    digitalWrite(pin, HIGH);
    while((micros() - del) < 475){
    }      //pause
    del = micros();
    digitalWrite(pin, LOW);
    while((micros() - del) < 150){
    }       //pulse
  }
}

void transmitChannel(int ch, boolean mode){
  switch (ch){
    case 0:
      if(mode){
        sendAon();
      }else{
        sendAoff();
      }
      break;
    case 1:
      if(mode){
        sendBon();
      }else{
        sendBoff();
      }
      break;
    case 2:
      if(mode){
        sendCon();
      }else{
        sendCoff();
      }
      break;
    case 3:
      if(mode){
        send1on();
      }else{
        send1off();
      }
      break;
    case 4:
      if(mode){
        send2on();
      }else{
        send2off();
      }
      break;
    case 5:
      if(mode){
        send3on();
      }else{
        send3off();
      }
      break;
    default:
      break;
  }
}
  
void sendAon(){
  for(int i=0;i<numTx;i++){
    transmit(tx,0); //1
    transmit(tx,0); //2
    transmit(tx,1); //3
    transmit(tx,0); //4
    transmit(tx,1); //5
    transmit(tx,0); //6
    transmit(tx,1); //7
    transmit(tx,0); //8
    transmit(tx,1); //9
    transmit(tx,0); //10
    transmit(tx,1); //11
    transmit(tx,1); //12
    transmit(tx,1); //13
    transmit(tx,0); //14
    transmit(tx,1); //15
    transmit(tx,0); //16
    transmit(tx,1); //17
    transmit(tx,0); //18
    transmit(tx,1); //19
    transmit(tx,0); //20
    transmit(tx,1); //21
    transmit(tx,0); //22
    transmit(tx,1); //23
    transmit(tx,1); //24
    transmit(tx,1); //25?
    digitalWrite(tx, LOW);
    delayMicroseconds(4500);
  }
}
void sendAoff(){
  for(int i=0;i<numTx;i++){
    transmit(tx,0); //1
    transmit(tx,0); //2
    transmit(tx,1); //3
    transmit(tx,0); //4
    transmit(tx,1); //5
    transmit(tx,0); //6
    transmit(tx,1); //7
    transmit(tx,0); //8
    transmit(tx,1); //9
    transmit(tx,0); //10
    transmit(tx,1); //11
    transmit(tx,1); //12
    transmit(tx,1); //13
    transmit(tx,0); //14
    transmit(tx,1); //15
    transmit(tx,0); //16
    transmit(tx,1); //17
    transmit(tx,0); //18
    transmit(tx,1); //19
    transmit(tx,0); //20
    transmit(tx,1); //21
    transmit(tx,1); //22
    transmit(tx,1); //23
    transmit(tx,0); //24
    transmit(tx,1); //25?
    digitalWrite(tx, LOW);
    delayMicroseconds(4500);
  }
}

void sendBon(){
  for(int i=0;i<numTx;i++){
    transmit(tx,0); //1
    transmit(tx,0); //2
    transmit(tx,1); //3
    transmit(tx,0); //4
    transmit(tx,1); //5
    transmit(tx,0); //6
    transmit(tx,1); //7
    transmit(tx,0); //8
    transmit(tx,1); //9
    transmit(tx,0); //10
    transmit(tx,1); //11
    transmit(tx,0); //12
    transmit(tx,1); //13
    transmit(tx,1); //14
    transmit(tx,1); //15
    transmit(tx,0); //16
    transmit(tx,1); //17
    transmit(tx,0); //18
    transmit(tx,1); //19
    transmit(tx,0); //20
    transmit(tx,1); //21
    transmit(tx,0); //22
    transmit(tx,1); //23
    transmit(tx,1); //24
    transmit(tx,1); //25?
    digitalWrite(tx, LOW);
    delayMicroseconds(4500);
  }
}
void sendBoff(){
  for(int i=0;i<numTx;i++){
    transmit(tx,0); //1
    transmit(tx,0); //2
    transmit(tx,1); //3
    transmit(tx,0); //4
    transmit(tx,1); //5
    transmit(tx,0); //6
    transmit(tx,1); //7
    transmit(tx,0); //8
    transmit(tx,1); //9
    transmit(tx,0); //10
    transmit(tx,1); //11
    transmit(tx,0); //12
    transmit(tx,1); //13
    transmit(tx,1); //14
    transmit(tx,1); //15
    transmit(tx,0); //16
    transmit(tx,1); //17
    transmit(tx,0); //18
    transmit(tx,1); //19
    transmit(tx,0); //20
    transmit(tx,1); //21
    transmit(tx,1); //22
    transmit(tx,1); //23
    transmit(tx,0); //24
    transmit(tx,1); //25?
    digitalWrite(tx, LOW);
    delayMicroseconds(4500);
  }
}
void sendCon(){
  for(int i=0;i<numTx;i++){
    transmit(tx,0); //1
    transmit(tx,0); //2
    transmit(tx,1); //3
    transmit(tx,0); //4
    transmit(tx,1); //5
    transmit(tx,0); //6
    transmit(tx,1); //7
    transmit(tx,0); //8
    transmit(tx,1); //9
    transmit(tx,0); //10
    transmit(tx,1); //11
    transmit(tx,0); //12
    transmit(tx,1); //13
    transmit(tx,0); //14
    transmit(tx,1); //15
    transmit(tx,1); //16
    transmit(tx,1); //17
    transmit(tx,0); //18
    transmit(tx,1); //19
    transmit(tx,0); //20
    transmit(tx,1); //21
    transmit(tx,0); //22
    transmit(tx,1); //23
    transmit(tx,1); //24
    transmit(tx,1); //25?
    digitalWrite(tx, LOW);
    delayMicroseconds(4500);
  }
}
void sendCoff(){
  for(int i=0;i<numTx;i++){
    transmit(tx,0); //1
    transmit(tx,0); //2
    transmit(tx,1); //3
    transmit(tx,0); //4
    transmit(tx,1); //5
    transmit(tx,0); //6
    transmit(tx,1); //7
    transmit(tx,0); //8
    transmit(tx,1); //9
    transmit(tx,0); //10
    transmit(tx,1); //11
    transmit(tx,0); //12
    transmit(tx,1); //13
    transmit(tx,0); //14
    transmit(tx,1); //15
    transmit(tx,1); //16
    transmit(tx,1); //17
    transmit(tx,0); //18
    transmit(tx,1); //19
    transmit(tx,0); //20
    transmit(tx,1); //21
    transmit(tx,1); //22
    transmit(tx,1); //23
    transmit(tx,0); //24
    transmit(tx,1); //25?
    digitalWrite(tx, LOW);
    delayMicroseconds(4500);
  }
}

void send1on(){
mySwitch.send(1381717,24);
}

void send1off(){
mySwitch.send(1381716,24);
}

void send2on(){
mySwitch.send(1394005,24);
}

void send2off(){
mySwitch.send(1394004,24);
}

void send3on(){
mySwitch.send(1397077,24);
}

void send3off(){
mySwitch.send(1397076,24);
}

void toggle(char channel){
  switch (channel) {
    case 'a':
      if (switchStatus[0]){
        sendAoff();
        switchStatus[0] = false;
      }else{
        sendAon();
        switchStatus[0] = true;
      }
      break;
    case 'b':
      if (switchStatus[1]){
        sendBoff();
        switchStatus[1] = false;
      }else{
        sendBon();
        switchStatus[1] = true;
      }
      break;
    case 'c':
      if (switchStatus[2]){
        sendCoff();
        switchStatus[2] = false;
      }else{
        sendCon();
        switchStatus[2] = true;
      }
      break;
    case '1':
      if (switchStatus[3]){
        send1off();
        switchStatus[3] = false;
      }else{
        send1on();
        switchStatus[3] = true;
      }
      break;
    case '2':
      if (switchStatus[4]){
        send2off();
        switchStatus[4] = false;
      }else{
        send2on();
        switchStatus[4] = true;
      }
      break;
    case '3':
      if (switchStatus[5]){
        send3off();
        switchStatus[5] = false;
      }else{
        send3on();
        switchStatus[5] = true;
      }
      break;
    default:
      break;
   }
}
  
