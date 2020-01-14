// StopWait.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Global.h"
#include "RdtSender.h"
#include "RdtReceiver.h"
#include "StopWaitRdtSender.h"
#include "StopWaitRdtReceiver.h"
#include "GBNRdtSender.h"
#include "GBNRdtReceiver.h"
#include "SRRdtSender.h"
#include "SRRdtReceiver.h"
#include "TCPRdtSender.h"
#include "TCPRdtReceiver.h"

//int main(int argc, char* argv[])
//{
//	RdtSender *ps = new StopWaitRdtSender();
//	RdtReceiver * pr = new StopWaitRdtReceiver();
////	pns->setRunMode(0);  //VERBOSģʽ
//	pns->setRunMode(1);  //����ģʽ
//	pns->init();
//	pns->setRtdSender(ps);
//	pns->setRtdReceiver(pr);
//	pns->setInputFile("D:\\ComputerNetwork\\Windows VS2017\\input.txt");
//	pns->setOutputFile("D:\\ComputerNetwork\\Windows VS2017\\output.txt");
//
//	pns->start();
//
//	delete ps;
//	delete pr;
//	delete pUtils;									//ָ��Ψһ�Ĺ�����ʵ����ֻ��main��������ǰdelete
//	delete pns;										//ָ��Ψһ��ģ�����绷����ʵ����ֻ��main��������ǰdelete
//	
//	return 0;
//}

//int main(int argc, char* argv[])
//{
//	RdtSender *ps = new GBNRdtSender();
//	RdtReceiver * pr = new GBNRdtReceiver();
//	//	pns->setRunMode(0);  //VERBOSģʽ
//	pns->setRunMode(1);  //����ģʽ
//	pns->init();
//	pns->setRtdSender(ps);
//	pns->setRtdReceiver(pr);
//	pns->setInputFile("D:\\ComputerNetwork\\Windows VS2017\\input.txt");
//	pns->setOutputFile("D:\\ComputerNetwork\\Windows VS2017\\output.txt");
//
//	pns->start();
//
//	delete ps;
//	delete pr;
//	delete pUtils;									//ָ��Ψһ�Ĺ�����ʵ����ֻ��main��������ǰdelete
//	delete pns;										//ָ��Ψһ��ģ�����绷����ʵ����ֻ��main��������ǰdelete
//
//	return 0;
//}

//int main(int argc, char* argv[])
//{
//	RdtSender *ps = new SRRdtSender();
//	RdtReceiver * pr = new SRRdtReceiver();
//	//pns->setRunMode(0);  //VERBOSģʽ
//	pns->setRunMode(1);  //����ģʽ
//	pns->init();
//	pns->setRtdSender(ps);
//	pns->setRtdReceiver(pr);
//	pns->setInputFile("D:\\ComputerNetwork\\Windows VS2017\\input.txt");
//	pns->setOutputFile("D:\\ComputerNetwork\\Windows VS2017\\output.txt");
//
//	pns->start();
//
//	delete ps;
//	delete pr;
//	delete pUtils;									//ָ��Ψһ�Ĺ�����ʵ����ֻ��main��������ǰdelete
//	delete pns;										//ָ��Ψһ��ģ�����绷����ʵ����ֻ��main��������ǰdelete
//
//	return 0;
//}

int main(int argc, char* argv[])
{
	RdtSender *ps = new TCPRdtSender();
	RdtReceiver * pr = new TCPRdtReceiver();
	//pns->setRunMode(0);  //VERBOSģʽ
	pns->setRunMode(1);  //����ģʽ
	pns->init();
	pns->setRtdSender(ps);
	pns->setRtdReceiver(pr);
	pns->setInputFile("D:\\ComputerNetwork\\Windows VS2017\\input.txt");
	pns->setOutputFile("D:\\ComputerNetwork\\Windows VS2017\\output.txt");

	pns->start();

	delete ps;
	delete pr;
	delete pUtils;									//ָ��Ψһ�Ĺ�����ʵ����ֻ��main��������ǰdelete
	delete pns;										//ָ��Ψһ��ģ�����绷����ʵ����ֻ��main��������ǰdelete

	return 0;
}

