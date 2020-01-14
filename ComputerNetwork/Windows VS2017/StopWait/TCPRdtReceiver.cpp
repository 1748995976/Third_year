#include "stdafx.h"
#include "Global.h"
#include "TCPRdtReceiver.h"


TCPRdtReceiver::TCPRdtReceiver() :base(0), receivePacket(new Packet[WINDOWSIZE])
{
	lastAckPkt.acknum = -1; //��ʼ״̬�£��ϴη��͵�ȷ�ϰ���ȷ�����Ϊ-1��ʹ�õ���һ�����ܵ����ݰ�����ʱ��ȷ�ϱ��ĵ�ȷ�Ϻ�Ϊ-1
	lastAckPkt.checksum = 0;
	lastAckPkt.seqnum = -1;	//���Ը��ֶ�
	for (int i = 0; i < Configuration::PAYLOAD_SIZE;i++) {
		lastAckPkt.payload[i] = '.';
	}
	lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
	for (int i = 0;i < WINDOWSIZE;i++)
		flag[i] = false;
}


TCPRdtReceiver::~TCPRdtReceiver()
{
	delete[] receivePacket;
}

bool TCPRdtReceiver::isInWindow(int seqNum) {
	if (base < (base + WINDOWSIZE) % SEQSIZE)
	{
		return seqNum >= base && seqNum < (base + WINDOWSIZE) % SEQSIZE;
	}
	else
	{
		return seqNum >= base || seqNum < (base + WINDOWSIZE) % SEQSIZE;
	}
}

void TCPRdtReceiver::receive(const Packet &packet) {
	//���У����Ƿ���ȷ
	int checkSum = pUtils->calculateCheckSum(packet);

	//���У�����ȷ��ͬʱ�յ����ĵ�����ڽ��շ�����������
	if ((checkSum == packet.checksum) && isInWindow(packet.seqnum)) {
		pUtils->printPacket("���շ���ȷ�յ����������ڷ��ͷ��ı���", packet);
		receivePacket[packet.seqnum % WINDOWSIZE] = packet;
		flag[packet.seqnum % WINDOWSIZE] = true;

		while (flag[base % WINDOWSIZE]) {
			//ȡ��Message�����ϵݽ���Ӧ�ò�
			Message msg;
			memcpy(msg.data, receivePacket[base % WINDOWSIZE].payload, sizeof(receivePacket[base % WINDOWSIZE].payload));
			pns->delivertoAppLayer(RECEIVER, msg);
			pUtils->printPacket("�ݽ��ϲ�:", receivePacket[base % WINDOWSIZE]);
			flag[base % WINDOWSIZE] = false;
			base = (base + 1) % SEQSIZE;
		}

		lastAckPkt.acknum = base; //ȷ����ŵ�������δȷ�ϵı������
		lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
		pUtils->printPacket("���շ����ͻ���������ȷ�ϱ���", lastAckPkt);
		pns->sendToNetworkLayer(SENDER, lastAckPkt);	//����ģ�����绷����sendToNetworkLayer��ͨ������㷢��ȷ�ϱ��ĵ��Է�

		std::cout << "\n[RECEIVERER]�ύ���ݣ����������ƶ���";
		printSlideWindow();
		std::cout << std::endl;
	}
	else {
		if (checkSum != packet.checksum) {
			pUtils->printPacket("���շ�û����ȷ�յ����ͷ��ı���,����У�����", packet);
			lastAckPkt.acknum = base; //ȷ����ŵ����յ��ı������
			lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
			pUtils->printPacket("���շ����ͻ���������ȷ�ϱ���", lastAckPkt);
			pns->sendToNetworkLayer(SENDER, lastAckPkt);	//����ģ�����绷����sendToNetworkLayer��ͨ������㷢��ȷ�ϱ��ĵ��Է�
		}
		else {
			//���У�����ȷ��ͬʱ�յ����ĵ�����ڽ��շ���������֮ǰ
			pUtils->printPacket("���շ���ȷ�յ���������֮ǰ���ͷ��ı���", packet);
			lastAckPkt.acknum = base; //ȷ����ŵ����յ��ı������
			lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
			pUtils->printPacket("���շ����ͻ�������֮ǰȷ�ϱ���", lastAckPkt);
			pns->sendToNetworkLayer(SENDER, lastAckPkt);	//����ģ�����绷����sendToNetworkLayer��ͨ������㷢��ȷ�ϱ��ĵ��Է�
		}
	}
}

void TCPRdtReceiver::printSlideWindow()
{
	int i;
	for (i = 0; i < SEQSIZE; i++)
	{
		if (i == base)
			std::cout << "[";
		std::cout << i;
		if (flag[i % WINDOWSIZE] && isInWindow(i))
			std::cout << "��";//����Ѿ��յ��ı���
		if (i == (base + WINDOWSIZE - 1) % SEQSIZE)
			std::cout << "]";
		std::cout << " ";
	}
	std::cout << std::endl;
}