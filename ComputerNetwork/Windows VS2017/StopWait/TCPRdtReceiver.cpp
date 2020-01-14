#include "stdafx.h"
#include "Global.h"
#include "TCPRdtReceiver.h"


TCPRdtReceiver::TCPRdtReceiver() :base(0), receivePacket(new Packet[WINDOWSIZE])
{
	lastAckPkt.acknum = -1; //初始状态下，上次发送的确认包的确认序号为-1，使得当第一个接受的数据包出错时该确认报文的确认号为-1
	lastAckPkt.checksum = 0;
	lastAckPkt.seqnum = -1;	//忽略该字段
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
	//检查校验和是否正确
	int checkSum = pUtils->calculateCheckSum(packet);

	//如果校验和正确，同时收到报文的序号在接收方滑动窗口内
	if ((checkSum == packet.checksum) && isInWindow(packet.seqnum)) {
		pUtils->printPacket("接收方正确收到滑动窗口内发送方的报文", packet);
		receivePacket[packet.seqnum % WINDOWSIZE] = packet;
		flag[packet.seqnum % WINDOWSIZE] = true;

		while (flag[base % WINDOWSIZE]) {
			//取出Message，向上递交给应用层
			Message msg;
			memcpy(msg.data, receivePacket[base % WINDOWSIZE].payload, sizeof(receivePacket[base % WINDOWSIZE].payload));
			pns->delivertoAppLayer(RECEIVER, msg);
			pUtils->printPacket("递交上层:", receivePacket[base % WINDOWSIZE]);
			flag[base % WINDOWSIZE] = false;
			base = (base + 1) % SEQSIZE;
		}

		lastAckPkt.acknum = base; //确认序号等于最早未确认的报文序号
		lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
		pUtils->printPacket("接收方发送滑动窗口内确认报文", lastAckPkt);
		pns->sendToNetworkLayer(SENDER, lastAckPkt);	//调用模拟网络环境的sendToNetworkLayer，通过网络层发送确认报文到对方

		std::cout << "\n[RECEIVERER]提交数据，滑动窗口移动：";
		printSlideWindow();
		std::cout << std::endl;
	}
	else {
		if (checkSum != packet.checksum) {
			pUtils->printPacket("接收方没有正确收到发送方的报文,数据校验错误", packet);
			lastAckPkt.acknum = base; //确认序号等于收到的报文序号
			lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
			pUtils->printPacket("接收方发送滑动窗口内确认报文", lastAckPkt);
			pns->sendToNetworkLayer(SENDER, lastAckPkt);	//调用模拟网络环境的sendToNetworkLayer，通过网络层发送确认报文到对方
		}
		else {
			//如果校验和正确，同时收到报文的序号在接收方滑动窗口之前
			pUtils->printPacket("接收方正确收到滑动窗口之前发送方的报文", packet);
			lastAckPkt.acknum = base; //确认序号等于收到的报文序号
			lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
			pUtils->printPacket("接收方发送滑动窗口之前确认报文", lastAckPkt);
			pns->sendToNetworkLayer(SENDER, lastAckPkt);	//调用模拟网络环境的sendToNetworkLayer，通过网络层发送确认报文到对方
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
			std::cout << "√";//标记已经收到的报文
		if (i == (base + WINDOWSIZE - 1) % SEQSIZE)
			std::cout << "]";
		std::cout << " ";
	}
	std::cout << std::endl;
}