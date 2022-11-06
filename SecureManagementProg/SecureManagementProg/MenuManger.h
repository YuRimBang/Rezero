#pragma once

#define		PORT					3389	
#define		HOST				"localhost"
#define		USER					"root"
#define		PASSWORD		"password"
#define		DB					"SecureManageprogramDB"


enum SEARCH	//검색조건
{
	WHOLE,						//통합검색
	BANK,						//은행
	NONBANK_DEPOSIT,	//비은행예금취급기관
	STOCK,						//증권회사
	INSURANCE,				//보험회사
	GOVERMENT,				//정부기관
	OTHER,						//기타
	SECURE					//보안프로그램
};
