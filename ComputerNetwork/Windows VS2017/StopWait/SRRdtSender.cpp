#include "stdafx.h"
#include "Global.h"
#include "SRRdtSender.h"
#include "NetworkService.h"


SRRdtSender::SRRdtSender() :nextSeqNum(0), base(0)
{
	sendPacket = new Packet[WINDOWSIZE];//���ﻺ�������СΪ���ڴ�С
	for (int i = 0;i < WINDOWSIZE;i++)
		flag[i] = false;
}


SRRdtSender::~SRRdtSender()
{
	delete[]  sendPacket;
}



bool SRRdtSender::getWaitingState() {
	return nextSeqNum == (base + WINDOWSIZE) % SEQSIZE;
}

bool SRRdtSender::isInWindow(int seqNum) {
	if (base < (base + WINDOWSIZE) % SEQSIZE)
	{
		return seqNum >= base && seqNum < (base + WINDOWSIZE) % SEQSIZE;
	}
	else
	{
		return seqNum >= base || seqNum < (base + WINDOWSIZE) % SEQSIZE;
	}
}

bool SRRdtSender::send(const Message &message) {
	if (getWaitingState()) { //���ͷ����ڵȴ�ȷ��״̬����������
		return false;
	}
	int mapSeqNum = nextSeqNum % WINDOWSIZE;//��nextSeqNumӳ�䵽WINDOWSIZE��С�Ļ�������
	sendPacket[mapSeqNum].acknum = -1; //���Ը��ֶ�
	sendPacket[mapSeqNum].seqnum = nextSeqNum;
	sendPacket[mapSeqNum].checksum = 0;
	flag[mapSeqNum] = false;

	memcpy(sendPacket[mapSeqNum].payload, message.data, sizeof(message.data));
	sendPacket[mapSeqNum].checksum = pUtils->calculateCheckSum(sendPacket[mapSeqNum]);
	pUtils->printPacket("���ͷ����ͱ���", sendPacket[mapSeqNum]);

	//��ʾ��������
	std::cout << "\n[SENDER]����ǰ���ڣ�";
	printSlideWindow();

	pns->startTimer(SENDER, Configuration::TIME_OUT, mapSeqNum);			//�������ͷ���ʱ��
	pns->sendToNetworkLayer(RECEIVER, sendPacket[mapSeqNum]);//����ģ�����绷����sendToNetworkLayer��ͨ������㷢�͵��Է�

	nextSeqNum = (nextSeqNum + 1) % SEQSIZE;//��һ�η��͵����

		//��ʾ��������
	std::cout << "[SENDER]���ͺ󴰿ڣ�";
	printSlideWindow();
	std::cout << std::endl;

	return true;
}

void SRRdtSender::receive(const Packet &ackPkt) {
	//���У����Ƿ���ȷ
	int checkSum = pUtils->calculateCheckSum(ackPkt);

	if (checkSum != ackPkt.checksum)
	{
		pUtils->printPacket("���յ�ack�𻵣�У��Ͳ����", ackPkt);
		return;
	}
	//���У�����ȷ������ȷ�����=���ͷ��ѷ��Ͳ��ȴ�ȷ�ϵ����ݰ����
	if (isInWindow(ackPkt.acknum)) {
		flag[ackPkt.acknum % WINDOWSIZE] = true;
		std::cout << "\n[SENDER]�յ�ack������������Ԫ��״̬�仯��";
		printSlideWindow();
		std::cout << std::endl;
		for (int i = base; i != nextSeqNum;i = (i + 1) % SEQSIZE) {
			if (flag[i % WINDOWSIZE]) {
				std::cout << "\n[SENDER]�յ�ack�����������ƶ�ǰ��";
				printSlideWindow();
				std::cout << std::endl;
				flag[i % WINDOWSIZE] = false;
				base = (i + 1) % SEQSIZE;
				std::cout << "\n[SENDER]�յ�ack�����������ƶ���";
				printSlideWindow();
				std::cout << std::endl;
			}
			else
				break;
		}
		pUtils->printPacket("���ͷ���ȷ�յ�ȷ��", ackPkt);
		pns->stopTimer(SENDER, ackPkt.acknum % WINDOWSIZE);//�رն�ʱ��
	}
}

void SRRdtSender::timeoutHandler(int seqNum) {
	//Ψһһ����ʱ��,���迼��seqNum
	pUtils->printPacket("���ͷ���ʱ��ʱ�䵽���ط�δȷ�ϵı���", sendPacket[seqNum]);
	if (nextSeqNum == base)
		return;
	else {
		pns->stopTimer(SENDER, seqNum);										//���ȹرն�ʱ��
		pns->startTimer(SENDER, Configuration::TIME_OUT, seqNum);			//�����������ͷ���ʱ�� 
		pns->sendToNetworkLayer(RECEIVER, sendPacket[seqNum]);			//���·������ݰ�
		pUtils->printPacket("���·��ͱ���", sendPacket[seqNum]);
	}
}

void SRRdtSender::printSlideWindow()
{
	int i;
	for (i = 0; i < SEQSIZE; i++)
	{
		if (i == base)
			std::cout << "[";
		std::cout << i;
		if (i == nextSeqNum)
			std::cout << "*";
		if (isInWindow(i) && flag[i % WINDOWSIZE])
			std::cout << "��";
		if (i == (base + WINDOWSIZE - 1) % SEQSIZE)
			std::cout << "]";
		std::cout << " ";
	}
	std::cout << std::endl;
}
