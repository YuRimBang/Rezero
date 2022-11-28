#pragma once


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

enum INTERNET
{
	CHROME,
	EXPLORE,
	MICOROSOFT_EDGE,
	WHALE
};

#define MSG_SECUREINIT			(WM_USER + 100)