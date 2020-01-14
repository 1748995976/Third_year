#ifndef TCP_RDT_RECEIVER_H
#define TCP_RDT_RECEIVER_H
#include "RdtReceiver.h"
class TCPRdtReceiver :public RdtReceiver
{
private:
	Packet lastAckPkt;				//�ϴη��͵�ȷ�ϱ���
	Packet *receivePacket; //�ѷ��Ͳ��ȴ�Ack�����ݰ�
	int base;
	bool flag[WINDOWSIZE];
	bool isInWindow(int seqNum);

public:
	TCPRdtReceiver();
	virtual ~TCPRdtReceiver();

public:
	void printSlideWindow();
	void receive(const Packet &packet);	//���ձ��ģ�����NetworkService����
};

#endif