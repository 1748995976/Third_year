#include "stdafx.h"
#include "Global.h"
#include "TCPRdtSender.h"
#include "NetworkService.h"


TCPRdtSender::TCPRdtSender() :nextSeqNum(0), base(0),repeatNum(0)
{
	sendPacket = new Packet[WINDOWSIZE];//���ﻺ�������СΪ���ڴ�С
}


TCPRdtSender::~TCPRdtSender()
{
	delete[]  sendPacket;
}



bool TCPRdtSender::getWaitingState() {
	return nextSeqNum == (base + WINDOWSIZE) % SEQSIZE;
}

bool TCPRdtSender::isInWindow(int seqNum) {
	if (base < (base + WINDOWSIZE) % SEQSIZE)
	{
		return seqNum > base && seqNum <= (base + WINDOWSIZE) % SEQSIZE;
	}
	else
	{
		return seqNum > base || seqNum <= (base + WINDOWSIZE) % SEQSIZE;
	}
}


bool TCPRdtSender::send(const Message &message) {
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

void TCPRdtSender::receive(const Packet &ackPkt) {
	//���У����Ƿ���ȷ
	int checkSum = pUtils->calculateCheckSum(ackPkt);

	if (checkSum != ackPkt.checksum)
	{
		pUtils->printPacket("���յ�ack�𻵣�У��Ͳ����", ackPkt);
		return;
	}
	//���У�����ȷ������ȷ�����=���ͷ��ѷ��Ͳ��ȴ�ȷ�ϵ����ݰ����
	if (isInWindow(ackPkt.acknum)) {
		base = ackPkt.acknum % SEQSIZE;
		pUtils->printPacket("���ͷ���ȷ�յ�ȷ��", ackPkt);
		if (base == nextSeqNum) {
			pns->stopTimer(SENDER, 0);//�رն�ʱ��
		}
		else {//����������ʱ��
			pns->stopTimer(SENDER, 0);
			pns->startTimer(SENDER, Configuration::TIME_OUT, 0);
		}
		repeatNum = 0;
		std::cout << "\n[SENDER]�յ�ack�����������ƶ���";
		printSlideWindow();
		std::cout << std::endl;
	}
	else if(ackPkt.acknum == base){
		repeatNum = repeatNum + 1;
		if(repeatNum == 3) {
			//�����ش�
			std::cout << "\n[SENDER]�յ�������������ack�������ش�\n";
			pns->sendToNetworkLayer(RECEIVER, sendPacket[base % WINDOWSIZE]);

			pns->stopTimer(SENDER, 0);
			pns->startTimer(SENDER, Configuration::TIME_OUT, 0);

			repeatNum = 0;
		}
	}
}

void TCPRdtSender::timeoutHandler(int seqNum) {
	//Ψһһ����ʱ��,���迼��seqNum
	pUtils->printPacket("���ͷ���ʱ��ʱ�䵽���ط�����δȷ�ϵı���", sendPacket[base % WINDOWSIZE]);
	if (nextSeqNum == base)
		return;
	else {
		pns->stopTimer(SENDER, 0);										//���ȹرն�ʱ��
		pns->startTimer(SENDER, Configuration::TIME_OUT, 0);			//�����������ͷ���ʱ�� 
	
			pns->sendToNetworkLayer(RECEIVER, sendPacket[base % WINDOWSIZE]);			//���·������ݰ�
			pUtils->printPacket("���·��ͱ���", sendPacket[base % WINDOWSIZE]);
		
	}
}

void TCPRdtSender::printSlideWindow()
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