#pragma once


// CSubTileTool ��ȭ �����Դϴ�.

class CSubTileTool : public CDialog
{
	DECLARE_DYNAMIC(CSubTileTool)

public:
	CSubTileTool(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CSubTileTool();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SUBTILETOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
