#include "StdAfx.h"
#include "VIETreeListCtrlEx.h"
#include "..\..\__AIGGlobal\Windows\Utils.h"
#include "..\..\__AIGGlobal\Windows\Log.h"

CVIETreeListCtrlEx::CVIETreeListCtrlEx(void)
{
	//m_pDragImgList = NULL;
}

CVIETreeListCtrlEx::~CVIETreeListCtrlEx(void)
{
}
void CVIETreeListCtrlEx::GetItemPath(LPWSTR szBuff, HTREEITEM hItem)
{
	if(hItem && hItem != GetRootItem())
	{
		CString szText; szText = GetItemText(hItem,0);

		GetItemPath(szBuff, GetParentItem(hItem));

		wcscat(szBuff, L".");
		// Cắt bớt ký tự dấu chấm đầu tiên
		if(wcslen(szBuff)==1)

			szBuff[wcslen(szBuff)-1]='\0';

		wcscat(szBuff, szText.GetBuffer());		
	}
}
void CVIETreeListCtrlEx::GetClassPath(LPWSTR szBuff,HTREEITEM hItem)
{
	if(hItem /*&& hItem != GetRootItem()*/)
	{
		CStringArray lsArray;

		if(CUtils::SplitString(GetItemText(hItem),L":",lsArray)>0)
		{
			CString szText; szText =lsArray[0];

			GetClassPath(szBuff, GetParentItem(hItem));

			wcscat(szBuff, L".");
			// Cắt bớt ký tự dấu chấm đầu tiên
			if(wcslen(szBuff)==1)

				szBuff[wcslen(szBuff)-1]='\0';

			wcscat(szBuff, szText.GetBuffer());		
		}
	}
}
CStringW CVIETreeListCtrlEx::GetItemPath(HTREEITEM hItem)
{
	WCHAR szPath[1024]={0};

	GetItemPath(szPath,hItem);

	return CStringW(szPath);
}

void CVIETreeListCtrlEx::RemoveChildbyText(HTREEITEM hItem,LPWSTR lpszText)
{
	HTREEITEM hChild = GetChildItem(hItem);

	while(hChild)
	{
		HTREEITEM hNextChild;

		if(wcscmp(lpszText,GetItemText(hChild))==0)
		{
			hNextChild= GetNextItem(hChild, TVGN_NEXT);

			DeleteItem(hChild);
		}
		else
			hNextChild = GetNextItem(hChild, TVGN_NEXT);		

		hChild = hNextChild;
	}
}
void CVIETreeListCtrlEx::RemoveAllChild(HTREEITEM hItem)
{
	HTREEITEM hChild = GetChildItem(hItem);

	while(hChild)
	{
		HTREEITEM hNextChild = GetNextItem(hChild, TVGN_NEXT);
		DeleteItem(hChild);
		hChild = hNextChild;
	}
}
LRESULT CVIETreeListCtrlEx::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: Add your specialized code here and/or call the base class
	if (message == WM_SHOWWINDOW){
		switch (wParam){
			case SW_HIDE:
				if (m_pPanelCtrl) m_pPanelCtrl->ShowWindow(wParam);
				break;
			case SW_SHOW:
			case SW_SHOWNORMAL:
				if (m_pPanelCtrl) m_pPanelCtrl->ShowWindow(wParam);
				break;
		}

	}
	return CVIETreeListCtrl::WindowProc(message, wParam, lParam);
}
BEGIN_MESSAGE_MAP(CVIETreeListCtrlEx, CVIETreeListCtrl)
END_MESSAGE_MAP()



void CVIETreeListCtrlEx::CopyItem(HTREEITEM hDest,HTREEITEM hSrc)
{

	for (int i = 0; i < GetColumnCount(); ++i){
		SetItemText(hDest,i,GetItemText(hSrc,i));
		if (i > 1) SetItemEditable(hDest,i);
	}
	Expand(hDest,TVE_EXPAND);
}

//

void CVIETreeListCtrlEx::CopySubtree(HTREEITEM hDest,HTREEITEM hSrc)
{
	if(!hDest || !hSrc) return;

	HTREEITEM hChildSrc = GetChildItem(hSrc);
	while (hChildSrc)
	{
		TV_ITEM tvSrc;
		tvSrc.mask  = TVIF_IMAGE | TVIF_SELECTEDIMAGE;
		tvSrc.hItem = hChildSrc;
		if (!GetItem(&tvSrc)) return;
		HTREEITEM   hChildDest = InsertItem(L"dest child",tvSrc.iImage,tvSrc.iSelectedImage,hDest);
		CopySubtree(hChildDest,hChildSrc);
		CopyItem   (hChildDest,hChildSrc);

		hChildSrc = GetNextSiblingItem(hChildSrc);
	}
}

//

HTREEITEM CVIETreeListCtrlEx::InsertItemAndSubtree(HTREEITEM hDest,HTREEITEM hSrc)
{
	if(!hDest || !hSrc) return NULL;
	TV_ITEM tvSrc;
	tvSrc.mask  = TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	tvSrc.hItem = hSrc;
	if(!GetItem(&tvSrc)) return NULL;
	HTREEITEM hNew = InsertItem(L"new",tvSrc.iImage,tvSrc.iSelectedImage,hDest);
	if(!hNew) return NULL;

	CopySubtree(hNew,hSrc);                                   // start with subtree so that item is correctly expanded
	CopyItem   (hNew,hSrc);
	return hNew;
}