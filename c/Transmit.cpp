#include "Transmit.h"
#include <wiringPi.h>

int numTx = 10;
void transmit(int pin, bool state){
  long del = micros();
  if(state){
    digitalWrite(pin, HIGH);
    while((micros() - del) < 200){
    }      //pause
    del = micros();
    digitalWrite(pin, LOW);
    while((micros() - del) < 400){
    }      //pulse
  }
  else{
    digitalWrite(pin, HIGH);
    while((micros() - del) < 400){
    }      //pause
    del = micros();
    digitalWrite(pin, LOW);
    while((micros() - del) < 200){
    }       //pulse
  }
}

void sendAon(int tx){
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
void sendAoff(int tx){
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


void sendBon(int tx){
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
void sendBoff(int tx){
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

void sendCon(int tx){
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
void sendCoff(int tx){
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
