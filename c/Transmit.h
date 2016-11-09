#ifndef Transmit_h_
#define Transmit_h_

void transmit(int pin, bool state);

void sendAon(int tx);
void sendAoff(int tx);
void sendBon(int tx);
void sendBoff(int tx);
void sendCon(int tx);
void sendCoff(int tx);

#endif
