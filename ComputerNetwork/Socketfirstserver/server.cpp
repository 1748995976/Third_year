#include "server.h"
#include "parsemessage.h"
#include <thread>
#include <WS2tcpip.h>
#include <mainwindow.h>
#include <QMainWindow>
#include <iostream>
#include <fstream>

using std::string;
using std::cout;
using std::endl;
using std::ifstream;
using std::ios;
using std::to_string;

#define BUFSIZE 4096
#define FILENAMESIZE 100
#define FILENAMESIZE_2 50

webserver::webserver()
{
    port = 80;
    filename = "D:/ComputerNetwork/html/";
    ip = "127.0.0.1";
    isnend = true;
}

void webserver::start()
{
    if (WSAStartup(MAKEWORD(2, 2), &wsaData))
    {
        send_message("Failed to load Winsock\n");
    }
    if (wsaData.wVersion != 0x0202)
    {
        send_message("Version Error\n");
        WSACleanup();
    }
    isnend = true;
    monSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (monSocket == SOCKET_ERROR) {
        send_message("monitor Socket() error:" + to_string(WSAGetLastError()) + "\n");
    }
    memset(&sockaddr, 0, sizeof(sockaddr));
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(port);
//    unsigned long ulip;
//    inet_pton(AF_INET,ip.data(),&ulip);
//    sockaddr.sin_addr.S_un.S_addr = htonl(ulip);
    sockaddr.sin_addr.S_un.S_addr = inet_addr(ip.data());
    //开始绑定
    if (::bind(monSocket, (LPSOCKADDR)&sockaddr, sizeof(sockaddr)) == SOCKET_ERROR) {
       send_message("Bind() error:" +to_string(WSAGetLastError()) + "\n");
    }
    //开始监听
    if (listen(monSocket, 10) == SOCKET_ERROR) {
        send_message("Listen() error:" +to_string(WSAGetLastError()) + "\n");
    }
    else {
        send_message("Start monitor port:" +to_string(port) + "\n");
    }
    //开启线程
//   std::thread t(&webserver::start_thread, this);
   t = new class thread(&webserver::start_thread, this);
   (*t).detach();
}

void webserver::accept_conn()//此处加const关键字会出错
{
    //等待客户请求的到来
    SOCKET *sockConn = new SOCKET();
    sockaddr_in addr_client;
    memset(&addr_client, 0, sizeof(addr_client));
    int addr_client_len = sizeof(addr_client);
    *sockConn = accept(monSocket, (LPSOCKADDR)&addr_client, &addr_client_len);
    if (*sockConn == SOCKET_ERROR) {
        return ;
    }
    //收到连接,打印点分十进制IP地址
    char ip_address[25];
    inet_ntop(AF_INET, &addr_client.sin_addr, ip_address, sizeof(ip_address));
    string a = "Accept a connection:" +string(ip_address) + "\n";

    std::thread t2(&webserver::start_thread2, this, sockConn,a);
    t2.detach();
}
void webserver::set_isnend(bool _isnend)
{
    isnend = _isnend;
}
bool webserver::get_isnend(){
    return isnend;
}
void webserver::set_port(int _port)
{
    port = _port;
}

void webserver::set_filename(string _filename)
{
    filename = _filename;
}

void webserver::send_message(string value ){
    emit valueChanged(QString::fromStdString(value));
}

void webserver::end()
{
    isnend = false;
    delete t;
    closesocket(monSocket);
}

webserver::~webserver()
{
}

void webserver::parse_get_mes(char *buffer, char * filename, int len) {
    char *check = buffer;
    if (!memcmp(check, "GET", 3)) {
        while (true){
            if ((*check) == '/') {
                break;
            }else
                check++;
        }
    }
    for (int i = 0;;i++) {
        if (i >= len) {
            send_message("Filename is too long!\n");
            return;
        }
        filename[i] = *check;
        check++;
        if (*check == ' ') {
            filename[i + 1] = '\0';
            return;
        }
    }
    return;
}

bool webserver::sendfile(SOCKET &socket, string newfilename) {
    ifstream infile(newfilename, ios::in | ios::binary);
    if (!infile) {
        send_message("Fopen() error\n");
        send_message("Can't find file " + newfilename + "\n");
        string filename_404 = "D:/ComputerNetwork/html/index.html";
        infile.open(filename_404, ios::in | ios::binary);
        char temp[1024];
        while (true) {
            memset(temp, '\0', 1024);
            infile.read(temp, 1024);
            send(socket, temp, infile.gcount(), 0);
            if (infile.eof())
                break;
        }
        infile.close();
        return false;
    }
    else {
        send_message("Open file: " + newfilename + " successfully!\n");
        char temp[1024];
        while (true) {
            memset(temp, '\0', 1024);
            infile.read(temp, 1024);
            send(socket, temp, infile.gcount(), 0);
            if (infile.eof())
                break;
        }
        infile.close();
    }
    return true;
}

void webserver::start_thread2(SOCKET *sockConn,string a)
{
    m.lock();
    send_message(a);
    char data[BUFSIZE];
    memset(data, 0, sizeof(data));

    if (recv(*sockConn, data, sizeof(data), 0) == SOCKET_ERROR) {
        send_message("Recv() failed:" +to_string(WSAGetLastError()) + "\n");
    }
    else {
        send_message(string(data));
    }

    char	filename_2[FILENAMESIZE_2];
    parse_get_mes(data, filename_2, FILENAMESIZE_2);

    string response = "HTTP/1.1 200 OK\r\n";
    response = response + "\r\n";
    send(*sockConn, response.data(), response.size(), 0);

    string newfilename = filename + filename_2;
    sendfile(*sockConn, newfilename);

    closesocket(*sockConn);
    free(sockConn);
    m.unlock();
}

void webserver::start_thread(){
    while(this->get_isnend()){
        this->accept_conn();
    }
}

void webserver::set_ip(string _ip)
{
    ip = _ip;
}
string webserver::get_ip()
{
    return ip;
}
