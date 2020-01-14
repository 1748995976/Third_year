#ifndef SERVER_H
#define SERVER_H

#include <WinSock2.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <QObject>
#include <thread>
#include <mutex>

using std::string;
using std::cout;
using std::endl;
using std::thread;

class webserver:public QObject
{
     Q_OBJECT
private:
    WSADATA  wsaData;
    int port = 80;
    SOCKET monSocket;
    sockaddr_in sockaddr;
    string filename = "D:/ComputerNetwork/html";
    bool isnend = true;
    string ip;
    class thread* t;//线程
    std::mutex m;//s锁

public:
    void accept_conn();
    webserver();
    void set_isnend(bool _isend);
    bool get_isnend();
    void set_port(int _port);
    void set_filename(string _filename);
    void start();
    void end();
    void set_ip(string _ip);
    string get_ip();
    ~webserver();

public :
    void send_message(string value );

signals: //信号
    void valueChanged(QString newValue);

public:
    void parse_get_mes(char *buffer,char * filename, int len);

    bool sendfile(SOCKET &socket, string filename);

    void start_thread2(SOCKET *sockConn,string a);

    void start_thread();
};

#endif
