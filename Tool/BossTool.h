#pragma once


// CBossTool ��ȭ �����Դϴ�.

class CBossTool : public CDialog
{
	DECLARE_DYNAMIC(CBossTool)

public:
	CBossTool(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CBossTool();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BOSSTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
