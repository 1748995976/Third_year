#ifndef SR_RDT_RECEIVER_H
#define SR_RDT_RECEIVER_H
#include "RdtReceiver.h"
class SRRdtReceiver :public RdtReceiver
{
private:
	Packet lastAckPkt;				//�ϴη��͵�ȷ�ϱ���
	Packet *receivePacket; //�ѽ��ܵ����ݰ�����
	int base;
	bool flag[WINDOWSIZE];
	bool isInWindow(int seqNum);

public:
	SRRdtReceiver();
	virtual ~SRRdtReceiver();

public:
	void printSlideWindow();
	void receive(const Packet &packet);	//���ձ��ģ�����NetworkService����
};

#endif