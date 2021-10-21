#pragma once
#include "GActivity.h"

#define iunknown	99
#define max_len		3
class CGKhaoCo : public CGActivity
{
public:
	CGKhaoCo();
	virtual ~CGKhaoCo();
	int  Process();

	BOOL archaeologypop();
	BOOL IsPickUpBtn();
	BOOL IsPassWnd();

	BOOL CheckAllBoxClue(CUIArchaeologyPoint *pInstance, CUE_Transform *p);
	BOOL IsEmptyClueInArchaeologyWith(CUIArchaeologyPoint *pInstance, int iBox, int iChild, CUE_Transform *p = NULL, BOOL bLineFirst = FALSE);
	BOOL IsEmptyClueInAnalysWith(CUIArchaeologyPoint *pInstance, int iBox, int iChild, CUE_Transform *p = NULL);

	BOOL CollectClue(int iSTT);

	CUIArchaeologyClue *get_Clue(CUE_Transform *p);

	int set_Num(int iSTT);

	void ShowArchaeologyWindow();
	void UpdatePass();

	BOOL m_bFinished;
	BOOL m_bEmpty;

	int m_iPass[max_len];
};

