#pragma once


// CTriggerTool ��ȭ �����Դϴ�.

class CTriggerTool : public CDialog
{
	DECLARE_DYNAMIC(CTriggerTool)

public:
	CTriggerTool(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CTriggerTool();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TRIGGERTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
