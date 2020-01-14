#include "stdafx.h"
#include "Global.h"
#include "SRRdtSender.h"
#include "NetworkService.h"


SRRdtSender::SRRdtSender() :nextSeqNum(0), base(0)
{
	sendPacket = new Packet[WINDOWSIZE];//这里缓存数组大小为窗口大小
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
	if (getWaitingState()) { //发送方处于等待确认状态，窗口已满
		return false;
	}
	int mapSeqNum = nextSeqNum % WINDOWSIZE;//将nextSeqNum映射到WINDOWSIZE大小的缓存数组
	sendPacket[mapSeqNum].acknum = -1; //忽略该字段
	sendPacket[mapSeqNum].seqnum = nextSeqNum;
	sendPacket[mapSeqNum].checksum = 0;
	flag[mapSeqNum] = false;

	memcpy(sendPacket[mapSeqNum].payload, message.data, sizeof(message.data));
	sendPacket[mapSeqNum].checksum = pUtils->calculateCheckSum(sendPacket[mapSeqNum]);
	pUtils->printPacket("发送方发送报文", sendPacket[mapSeqNum]);

	//显示滑动窗口
	std::cout << "\n[SENDER]发送前窗口：";
	printSlideWindow();

	pns->startTimer(SENDER, Configuration::TIME_OUT, mapSeqNum);			//启动发送方定时器
	pns->sendToNetworkLayer(RECEIVER, sendPacket[mapSeqNum]);//调用模拟网络环境的sendToNetworkLayer，通过网络层发送到对方

	nextSeqNum = (nextSeqNum + 1) % SEQSIZE;//下一次发送的序号

		//显示滑动窗口
	std::cout << "[SENDER]发送后窗口：";
	printSlideWindow();
	std::cout << std::endl;

	return true;
}

void SRRdtSender::receive(const Packet &ackPkt) {
	//检查校验和是否正确
	int checkSum = pUtils->calculateCheckSum(ackPkt);

	if (checkSum != ackPkt.checksum)
	{
		pUtils->printPacket("接收的ack损坏，校验和不相等", ackPkt);
		return;
	}
	//如果校验和正确，并且确认序号=发送方已发送并等待确认的数据包序号
	if (isInWindow(ackPkt.acknum)) {
		flag[ackPkt.acknum % WINDOWSIZE] = true;
		std::cout << "\n[SENDER]收到ack，滑动窗口内元素状态变化：";
		printSlideWindow();
		std::cout << std::endl;
		for (int i = base; i != nextSeqNum;i = (i + 1) % SEQSIZE) {
			if (flag[i % WINDOWSIZE]) {
				std::cout << "\n[SENDER]收到ack，滑动窗口移动前：";
				printSlideWindow();
				std::cout << std::endl;
				flag[i % WINDOWSIZE] = false;
				base = (i + 1) % SEQSIZE;
				std::cout << "\n[SENDER]收到ack，滑动窗口移动后：";
				printSlideWindow();
				std::cout << std::endl;
			}
			else
				break;
		}
		pUtils->printPacket("发送方正确收到确认", ackPkt);
		pns->stopTimer(SENDER, ackPkt.acknum % WINDOWSIZE);//关闭定时器
	}
}

void SRRdtSender::timeoutHandler(int seqNum) {
	//唯一一个定时器,无需考虑seqNum
	pUtils->printPacket("发送方定时器时间到，重发未确认的报文", sendPacket[seqNum]);
	if (nextSeqNum == base)
		return;
	else {
		pns->stopTimer(SENDER, seqNum);										//首先关闭定时器
		pns->startTimer(SENDER, Configuration::TIME_OUT, seqNum);			//重新启动发送方定时器 
		pns->sendToNetworkLayer(RECEIVER, sendPacket[seqNum]);			//重新发送数据包
		pUtils->printPacket("重新发送报文", sendPacket[seqNum]);
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
			std::cout << "√";
		if (i == (base + WINDOWSIZE - 1) % SEQSIZE)
			std::cout << "]";
		std::cout << " ";
	}
	std::cout << std::endl;
}
