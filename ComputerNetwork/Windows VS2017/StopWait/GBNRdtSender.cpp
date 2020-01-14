#include "stdafx.h"
#include "Global.h"
#include "GBNRdtSender.h"
#include "NetworkService.h"


GBNRdtSender::GBNRdtSender() :nextSeqNum(0),base(0)
{
	sendPacket = new Packet[WINDOWSIZE];//���ﻺ�������СΪ���ڴ�С
}


GBNRdtSender::~GBNRdtSender()
{
	delete[]  sendPacket;
}



bool GBNRdtSender::getWaitingState() {
	return nextSeqNum == (base + WINDOWSIZE) % SEQSIZE;
}

bool GBNRdtSender::isInWindow(int seqNum) {
	if (base < (base + WINDOWSIZE) % SEQSIZE)
	{
		return seqNum >= base && seqNum < (base + WINDOWSIZE) % SEQSIZE;
	}
	else
	{
		return seqNum >= base || seqNum < (base + WINDOWSIZE) % SEQSIZE;
	}
}


bool GBNRdtSender::send(const Message &message) {
	if (getWaitingState()) { //���ͷ����ڵȴ�ȷ��״̬����������
		return false;
	}
	int mapSeqNum = nextSeqNum % WINDOWSIZE;//��nextSeqNumӳ�䵽WINDOWSIZE��С�Ļ�������
	sendPacket[mapSeqNum].acknum = -1; //���Ը��ֶ�
	sendPacket[mapSeqNum].seqnum = nextSeqNum;
	sendPacket[mapSeqNum].checksum = 0;

	memcpy(sendPacket[mapSeqNum].payload, message.data, sizeof(message.data));
	sendPacket[mapSeqNum].checksum = pUtils->calculateCheckSum(sendPacket[mapSeqNum]);
	pUtils->printPacket("���ͷ����ͱ���", sendPacket[mapSeqNum]);

	//��ʾ��������
	std::cout << "\n[SENDER]����ǰ���ڣ�";
	printSlideWindow();

	if (base == nextSeqNum) {
		pns->startTimer(SENDER, Configuration::TIME_OUT, 0);			//�������ͷ���ʱ��
	}
	pns->sendToNetworkLayer(RECEIVER, sendPacket[mapSeqNum]);//����ģ�����绷����sendToNetworkLayer��ͨ������㷢�͵��Է�

	nextSeqNum = (nextSeqNum + 1) % SEQSIZE;//��һ�η��͵����

		//��ʾ��������
	std::cout << "[SENDER]���ͺ󴰿ڣ�";
	printSlideWindow();
	std::cout << std::endl;
																	
	return true;
}

void GBNRdtSender::receive(const Packet &ackPkt) {
	//���У����Ƿ���ȷ
	int checkSum = pUtils->calculateCheckSum(ackPkt);

	if (checkSum != ackPkt.checksum)
	{
		pUtils->printPacket("���յ�ack�𻵣�У��Ͳ����", ackPkt);
		return;
	}
	//���У�����ȷ������ȷ�����=���ͷ��ѷ��Ͳ��ȴ�ȷ�ϵ����ݰ����
	if (isInWindow(ackPkt.acknum)) {
		base = (ackPkt.acknum+1) % SEQSIZE;
		pUtils->printPacket("���ͷ���ȷ�յ�ȷ��", ackPkt);
		if (base == nextSeqNum) {
			pns->stopTimer(SENDER, 0);//�رն�ʱ��
		}
		else {//����������ʱ��
			pns->stopTimer(SENDER, 0);
			pns->startTimer(SENDER, Configuration::TIME_OUT, 0);
		}
		std::cout << "\n[SENDER]�յ�ack�����������ƶ���";
		printSlideWindow();
		std::cout << std::endl;
	}
}

void GBNRdtSender::timeoutHandler(int seqNum) {
	//Ψһһ����ʱ��,���迼��seqNum
	pUtils->printPacket("���ͷ���ʱ��ʱ�䵽���ط�����δȷ�ϵı���", sendPacket[base % WINDOWSIZE]);
	if (nextSeqNum == base)
		return;
	else {
		pns->stopTimer(SENDER, 0);										//���ȹرն�ʱ��
		pns->startTimer(SENDER, Configuration::TIME_OUT, 0);			//�����������ͷ���ʱ�� 
		for (int i = base; i != nextSeqNum; i = (i + 1) % SEQSIZE)
		{
			pns->sendToNetworkLayer(RECEIVER, sendPacket[i % WINDOWSIZE]);			//���·������ݰ�
			pUtils->printPacket("���·��ͱ���", sendPacket[i % WINDOWSIZE]);
		}
	}
}

void GBNRdtSender::printSlideWindow()
{
	int i;
	for (i = 0; i < SEQSIZE; i++)
	{
		if (i == base)
			std::cout << "[";
		std::cout << i;
		if (i == nextSeqNum)
			std::cout << "*";
		if (i == (base + WINDOWSIZE - 1) % SEQSIZE)
			std::cout << "]";
		std::cout << " ";
	}
	std::cout << std::endl;
}
