#include <iostream>
#include <string>
#include <stdbool.h>
#include <stdio.h>
#include <mysql/my_global.h>
#include <mysql/mysql.h>
//#include <wiringPi.h>
//#include "RCSwitch.h"
//#include "Transmit.h"
//#define TX_PIN 4

void finnish_with_error(MYSQL *con){
    fprintf(stderr, "%s\n", mysql_error(con));
    mysql_close(con);
    exit(1);
}
int currentState[8], dbState[8];
int main(){
    MYSQL *con = mysql_init(NULL);
    mysql_options(con, MYSQL_SET_CHARSET_NAME, "utf8");
    if (con == NULL){
        fprintf(stderr, "%s\n", mysql_error(con));
        exit(1);
    }

    if (mysql_real_connect(con, "localhost", "rcswitch", "rcswitch", "rcswitch", 0, NULL, 0) == NULL){
        finnish_with_error(con);
    }

    if (mysql_query(con, "SELECT * FROM sockets")){
        finnish_with_error(con);
    }

    MYSQL_RES *result = mysql_store_result(con);

    if(result == NULL){
        finnish_with_error(con);
    }

    int num_fields = mysql_num_fields(result);

    MYSQL_ROW row;
    int i = 0;
    while ((row = mysql_fetch_row(result))){
        
        dbState[i] = std::stoi(row[4]);
        printf("\n");
        i++;
    }
    mysql_free_result(result);

    mysql_close(con);
    exit(0);
    return 0;

}






//    wiringPiSetup();
//    pinMode(1, OUTPUT);
//    digitalWrite(1, HIGH);
//    pinMode(1, PWM_OUTPUT);
//    while(1){
//      for(int i=0; i<512; i++){
//         pwmWrite(1, i);
//         delay(2);
//      }
//      for(int i=512; i>0;i--){
//         pwmWrite(1, i);
//         delay(2);
//      }
//    }
   
    //RCSwitch mySwitch = RCSwitch();
    //mySwitch.enableTransmit(TX_PIN);
    //mySwitch.setProtocol(4);
    //mySwitch.setPulseLength(200);  //(362);
    //printf(mySwitch);
    //mySwitch.send(5600599,25);
    //delay(1000);
    //mySwitch.send(5600605,25);
    //delay(1000);
    //pinMode(tx, OUTPUT);
    //digitalWrite(tx, LOW);
    //sendAon();
    //delay(1000);
    //sendAoff();
