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

enum INTERNET
{
	CHROME,
	EXPLORE,
	MICOROSOFT_EDGE,
	WHALE
};

#define MSG_SECUREINIT			(WM_USER + 100)