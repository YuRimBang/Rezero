#pragma once


enum SEARCH	//�˻�����
{
	WHOLE,						//���հ˻�
	BANK,						//����
	NONBANK_DEPOSIT,	//�����࿹����ޱ��
	STOCK,						//����ȸ��
	INSURANCE,				//����ȸ��
	GOVERMENT,				//���α��
	OTHER,						//��Ÿ
	SECURE					//�������α׷�
};

#define MSG_SECUREINIT			(WM_USER + 100)