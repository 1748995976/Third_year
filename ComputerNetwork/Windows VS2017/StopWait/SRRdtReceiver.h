#ifndef SR_RDT_RECEIVER_H
#define SR_RDT_RECEIVER_H
#include "RdtReceiver.h"
class SRRdtReceiver :public RdtReceiver
{
private:
	Packet lastAckPkt;				//上次发送的确认报文
	Packet *receivePacket; //已接受的数据包缓存
	int base;
	bool flag[WINDOWSIZE];
	bool isInWindow(int seqNum);

public:
	SRRdtReceiver();
	virtual ~SRRdtReceiver();

public:
	void printSlideWindow();
	void receive(const Packet &packet);	//接收报文，将被NetworkService调用
};

#endif