//Multipurpose______________
#include <iostream>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <sstream>
#include <ctime>
//--------------------------
//SQL_______________________
#include <mysql/my_global.h>
#include <mysql/mysql.h>
//--------------------------
//GPIO_Stuffs_______________
#include <wiringPi.h>
#include "RCSwitch.h"
#include "Transmit.h"
//--------------------------
//Needed for socket_________
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
//--------------------------

#define TX_PIN 4

using namespace std;

class MySocket{
public:
    MySocket(int id, string name, bool state, int type, int seqon = 0, int seqoff = 0, string note = "", bool active = 1);

    void toggle(RCSwitch * rcSwitch);
    bool getState() const;
    string getName() const;
    string getJson() const;
private:
    int _id;
    string _name;
    bool _state;
    int _type;
    int _seqon;
    int _seqoff;
    string _note;
    bool _active;
};

MySocket::MySocket(int id, string name, bool state, int type, int seqon, int seqoff, string note, bool active):
    _id(id),
    _name(name),
    _state(state),
    _type(type),
    _seqon(seqon),
    _seqoff(seqoff),
    _note(note),
    _active(active){}
void MySocket::toggle(RCSwitch * rcSwitch){
    if(_state){
        if(_type == 1){
            switch(stoi(_note)){
                case 1:
                    sendAoff(rcSwitch->getTransmitPin());
                    break;
                case 2:
                    sendBoff(rcSwitch->getTransmitPin());
                    break;
                case 3:
                    sendCoff(rcSwitch->getTransmitPin());
                    break;
                default:
                    break;
            }
          
            //ABC dvs. custom-funktion
        }else if(_type == 2){
            rcSwitch->send(_seqoff, 24);
        }
        
    }else{
        if(_type == 1){
            switch(stoi(_note)){
                case 1:
                    sendAon(rcSwitch->getTransmitPin());
                    break;
                case 2:
                    sendBon(rcSwitch->getTransmitPin());
                    break;
                case 3:
                    sendCon(rcSwitch->getTransmitPin());
                    break;
                default:
                    break;
            }
        
        }else if(_type == 2){
            rcSwitch->send(_seqon, 24);
        }

    }

    _state = !_state;
}
bool MySocket::getState() const{
    return _state;
}
string MySocket::getName() const{
    return _name;
}

string MySocket::getJson() const{
    stringstream ss;
    ss << "{\"active\": " << (int)_active << ", \"name\": \"" <<  _name << "\" ,\"id\": " <<  _id << "}";

    return ss.str();
}

//SQL error____________________________________
void finnish_with_error(MYSQL *con){
    fprintf(stderr, "%s\n", mysql_error(con));
    mysql_close(con);
    exit(1);
}
//---------------------------------------------
//Socket error_________________________________
void *connection_handler(void *socket_desc);
//---------------------------------------------
//String conversion____________________________
char* UTF8toISO8859_1(char * in);
//---------------------------------------------
//Print a tidy timestamp_______________________
void printTimeStamp();
//---------------------------------------------


vector<MySocket> mySockets;
RCSwitch mySwitch = RCSwitch();
int main(int argc, char* argv[]){
    
    // Initiate the pin to use RCSwitch librar
    wiringPiSetup();

    pinMode(TX_PIN, OUTPUT);
    digitalWrite(TX_PIN, LOW);
    mySwitch.enableTransmit(TX_PIN);
    mySwitch.setProtocol(1);
    
    //-----------------------------------------

    //Initiate a connection to database
    MYSQL *con = mysql_init(NULL);
    mysql_options(con, MYSQL_SET_CHARSET_NAME, "utf8");
    if (con == NULL){
        fprintf(stderr, "%s\n", mysql_error(con));
        exit(1);
    }
    if (mysql_real_connect(con, "localhost", "rcswitch", "rcswitch", "rcswitch", 0, NULL, 0) == NULL){
        finnish_with_error(con);
    }
    //-----------------------------------------

    //Query to the database
    if (mysql_query(con, "SELECT * FROM sockets")){
        finnish_with_error(con);
    }
    MYSQL_RES *result = mysql_store_result(con);
    if(result == NULL){
        finnish_with_error(con);
    }
    /*//Avkommentera detta om du behöver antalet kollumner
    int num_fields = mysql_num_fields(result);
    cout << "num_fields: " << num_fields << "\n";
    //-----------------------------------------*/
    
    //Collecting the data from the table
    
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result))){
        mySockets.push_back(MySocket(stoi(row[0]), row[1], (row[4][0] == '1')?1:0, stoi(row[2]),stoi(row[3]), stoi(row[5]), row[6], (row[7][0] == '1')?1:0));
        
        //dbState[i] = stoi(row[4]);
    }
    //closing the connection
    mysql_free_result(result);

    mysql_close(con);
    
    //------------------------------------------


    //Socket_stuff_starts_here__________________
    int socket_desc , client_sock , c , *new_sock;
    struct sockaddr_in server , client;

    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printTimeStamp();
        printf("Could not create socket");
    }
    printTimeStamp();
    puts("Socket created");

    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( 9999 );

    //Bind
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        //print the error message
        printTimeStamp();
        perror("bind failed. Error");
        return 1;
    }
    printTimeStamp();
    puts("bind done");

    //Listen
    listen(socket_desc , 3);

     //Accept and incoming connection
    printTimeStamp();
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);
    while( (client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) )
    {
        printTimeStamp();
        cout << "<" << inet_ntoa(client.sin_addr) << "> ";
        puts("Connection accepted");

        pthread_t sniffer_thread;
        int *new_sock = (int*) malloc(sizeof(int));
        *new_sock = client_sock;
        printTimeStamp();
        cout << "<" << inet_ntoa(client.sin_addr) << "> ";
        if( pthread_create( &sniffer_thread , NULL ,  connection_handler , (void*) new_sock) < 0)
        {
            printTimeStamp();
            perror("could not create thread");
            return 1;
        }

        //Now join the thread , so that we dont terminate before the thread
        pthread_join( sniffer_thread , NULL);
        printTimeStamp();
        cout << "<" << inet_ntoa(client.sin_addr) << "> ";
        puts("Handler assigned");
        pthread_kill( sniffer_thread, 0);
    }

    if (client_sock < 0)
    {
        printTimeStamp();
        perror("accept failed");
        return 1;
    }
    

    return 0;

}


void *connection_handler(void *socket_desc)
{
    //Get the socket descriptor
    int sock = *(int*)socket_desc;
    int read_size;
    char* message , client_message[2000];
    //const time_t rawtime = time(0);
    //Send some messages to the client
    //message = "Greetings! I am your connection handler\n";
    //write(sock , message , strlen(message));

    //message = "Now type something and i shall repeat what you type \n";
    //write(sock , message , strlen(message));

    //Receive a message from client
    while( (read_size = recv(sock , client_message , 2000 , 0)) > 0 )
    {
        //char timeBuffer[30];
        

        //strftime(timeBuffer, sizeof(timeBuffer), "%d-%m-%Y %H:%M:%S", localtime(&rawtime));
        //cout << timeBuffer << "\n" << client_message << "\n";
        
        cout << client_message << "\n";
        if(client_message[0] == 'q'){
            stringstream ss;
            ss << "{";
            for(int  i = 0; i < mySockets.size(); i++){
                ss << "\"" << i+1 << "\":" << mySockets[i].getJson();
                if(i < mySockets.size() -1){
                    ss << ",";
                }
            }
            
            ss << "}\n";
            const char* tmp = ss.str().c_str();
            //message = "{\"1\":{\"active\":1,\"name\":\"Byrå sovrum\",\"pin\":18},\"3\":{\"active\":1,\"name\":\"Snglampa\",\"pin\":17},\"2\":{\"active\":1,\"name\":\"Fnstersovrum\",\"pin\":4},\"5\":{\"active\":1,\"name\":\"Fnstervardagsrum\",\"pin\":22},\"4\":{\"active\":0,\"name\":\"Inaktiv\",\"pin\":27},\"7\":{\"active\":0,\"name\":\"test\",\"pin\":26},\"6\":{\"active\":1,\"name\":\"Vitrinsp\",\"pin\":25}}\n";
            write(sock , tmp , strlen(tmp));
        }else if(client_message[0] == '!'){
            
            stringstream ss;
            
            for(int i = 0; i < mySockets.size(); i++){
                ss << mySockets[i].getState();
            }
            ss << "\n";
            const char* tmp = ss.str().c_str();

            write(sock , tmp , strlen(tmp));
        }else if (stoi(client_message)-1 >= 0 && stoi(client_message)-1 < mySockets.size()){
            
            mySockets[stoi(client_message)-1].toggle(&mySwitch);
            const char *tmp = "\n";
            write(sock , tmp , strlen(tmp));
        }else{
            
            const char * tmp = "unknown\n";
            write(sock , tmp, strlen(tmp));
        }

        client_message[0] = '\0';
        
        //cout << client_message << "\n\n";
        //Send the message back to client
        //write(sock , client_message , strlen(client_message));
    }

    if(read_size == 0)
    {
        //puts("Client disconnected");
        fflush(stdout);
    }
    else if(read_size == -1)
    {
        perror("recv failed");

    }

    //Free the socket pointer
    close(sock);
    free(socket_desc);
    //cout << "Time spent: " << time(0) - rawtime << "\n";
    return 0;
}

char* UTF8toISO8859_1(char * in)
{
    std::string out;
    if (in == NULL)
        return strdup(out.c_str());

    unsigned int codepoint;
    while (*in != 0)
    {
        unsigned char ch = static_cast<unsigned char>(*in);
        if (ch <= 0x7f)
            codepoint = ch;
        else if (ch <= 0xbf)
            codepoint = (codepoint << 6) | (ch & 0x3f);
        else if (ch <= 0xdf)
            codepoint = ch & 0x1f;
        else if (ch <= 0xef)
            codepoint = ch & 0x0f;
        else
            codepoint = ch & 0x07;
        ++in;
        if (((*in & 0xc0) != 0x80) && (codepoint <= 0x10ffff))
        {
            if (codepoint <= 255)
            {
                out.append(1, static_cast<char>(codepoint));
            }
            else
            {
                // do whatever you want for out-of-bounds characters
            }
        }
    }
    return strdup(out.c_str());
}

void printTimeStamp(){
    const time_t rawtime = time(0);
    char timeBuffer[30];
    strftime(timeBuffer, sizeof(timeBuffer), "%d-%m-%Y %H:%M:%S", localtime(&rawtime));
    cout << "[" << timeBuffer << "]";
}