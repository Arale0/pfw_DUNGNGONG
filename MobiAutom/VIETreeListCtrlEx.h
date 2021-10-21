#pragma once
#include "..\..\__AIGGlobal\Windows\VIEControls\VIETreeListCtrl.h"

class CVIETreeListCtrlEx: public CVIETreeListCtrl
{
public:


public:
	CVIETreeListCtrlEx(void);
	~CVIETreeListCtrlEx(void);
	
	void		GetItemPath(LPWSTR szBuff, HTREEITEM hItem);
	void		GetClassPath(LPWSTR szBuff,HTREEITEM hItem);
	CStringW	GetItemPath(HTREEITEM hItem);

	void		RemoveChildbyText(HTREEITEM hItem,LPWSTR lpszText);
	void		RemoveAllChild(HTREEITEM hItem);

	void              CopyItem            (HTREEITEM hDest,HTREEITEM hSrc);
	void              CopySubtree         (HTREEITEM hDest,HTREEITEM hSrc);
	HTREEITEM         InsertItemAndSubtree(HTREEITEM hDest,HTREEITEM hSrc);
protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
public:
	DECLARE_MESSAGE_MAP()

};
