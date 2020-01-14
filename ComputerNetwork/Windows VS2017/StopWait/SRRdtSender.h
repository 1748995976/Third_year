#ifndef SR_RDT_SENDER_H
#define SR_RDT_SENDER_H
#include "RdtSender.h"
class SRRdtSender :public RdtSender
{
private:
	int base;
	int nextSeqNum;	// ��һ��������� 
	Packet *sendPacket; //�ѷ��Ͳ��ȴ�Ack�����ݰ�
	bool flag[WINDOWSIZE];//��־λ

public:

	bool getWaitingState();
	bool send(const Message &message);						//����Ӧ�ò�������Message����NetworkServiceSimulator����,������ͷ��ɹ��ؽ�Message���͵�����㣬����true;�����Ϊ���ͷ����ڵȴ���ȷȷ��״̬���ܾ�����Message���򷵻�false
	void receive(const Packet &ackPkt);						//����ȷ��Ack������NetworkServiceSimulator����	
	void timeoutHandler(int seqNum);					//Timeout handler������NetworkServiceSimulator����
	void printSlideWindow();
	bool isInWindow(int seqNum);

public:
	SRRdtSender();
	virtual ~SRRdtSender();
};

#endif

