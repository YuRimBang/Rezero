#pragma once

#define		PORT					3389	
#define		HOST				"localhost"
#define		USER					"root"
#define		PASSWORD		"password"
#define		DB					"SecureManageprogramDB"


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
