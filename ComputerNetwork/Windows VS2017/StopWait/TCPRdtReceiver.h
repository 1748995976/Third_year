#ifndef TCP_RDT_RECEIVER_H
#define TCP_RDT_RECEIVER_H
#include "RdtReceiver.h"
class TCPRdtReceiver :public RdtReceiver
{
private:
	Packet lastAckPkt;				//上次发送的确认报文
	Packet *receivePacket; //已发送并等待Ack的数据包
	int base;
	bool flag[WINDOWSIZE];
	bool isInWindow(int seqNum);

public:
	TCPRdtReceiver();
	virtual ~TCPRdtReceiver();

public:
	void printSlideWindow();
	void receive(const Packet &packet);	//接收报文，将被NetworkService调用
};

#endif