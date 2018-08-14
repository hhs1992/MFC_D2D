// TriggerTool.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "TriggerTool.h"
#include "afxdialogex.h"

#include "MainFrm.h"
#include "ToolView.h"

// CTriggerTool ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CTriggerTool, CDialog)

CTriggerTool::CTriggerTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_TRIGGERTOOL, pParent)
	, m_byRoomNumer(0)
	, m_byCursorRoomNum(0)
{

}

CTriggerTool::~CTriggerTool()
{
}

void CTriggerTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_byRoomNumer);
	DDX_Text(pDX, IDC_EDIT2, m_byCursorRoomNum);
}


BEGIN_MESSAGE_MAP(CTriggerTool, CDialog)
	ON_WM_SYSCOMMAND()
	ON_BN_CLICKED(IDC_BUTTON2, &CTriggerTool::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON3, &CTriggerTool::OnBnClickedClear)
	ON_BN_CLICKED(IDC_BUTTON2, &CTriggerTool::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON8, &CTriggerTool::OnBnClickedLoad)
	ON_BN_CLICKED(IDC_BUTTON1, &CTriggerTool::OnBnClickedSave)
END_MESSAGE_MAP()


// CTriggerTool �޽��� ó�����Դϴ�.


void CTriggerTool::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	if (nID == SC_CLOSE) {
		CMainFrame* pMainFrame = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
		CToolView*	pMainView = dynamic_cast<CToolView*>(pMainFrame->m_MainSplit.GetPane(0, 1));

		pMainView->m_bOnTriggerTool = false;
	}

	CDialog::OnSysCommand(nID, lParam);
}




void CTriggerTool::OnBnClickedClear()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);

	CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CToolView* pMainView = dynamic_cast<CToolView*>(pMainFrm->m_MainSplit.GetPane(0, 1));

	CTriggerMgr::GetInstance()->Release();
	pMainView->Invalidate(FALSE);

	UpdateData(FALSE);
}


void CTriggerTool::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);

	CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CToolView* pMainView = dynamic_cast<CToolView*>(pMainFrm->m_MainSplit.GetPane(0, 1));

	if (CTriggerMgr::GetInstance()->GetVecTrigger().empty() == false)
	{
		CTriggerMgr::GetInstance()->GetVecTrigger().pop_back();
		pMainView->Invalidate(FALSE);
	}

	UpdateData(FALSE);
}


void CTriggerTool::OnBnClickedLoad()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);

	CFileDialog Dlg(TRUE, L"dat", L"*.dat", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"Data Files(*.dat)|*.dat||", this);

	TCHAR szPath[MAX_STR] = L"";

	GetCurrentDirectory(MAX_STR, szPath);
	PathRemoveFileSpec(szPath);
	lstrcat(szPath, L"\\Data");

	Dlg.m_ofn.lpstrInitialDir = szPath;

	if (IDOK == Dlg.DoModal())
	{
		HANDLE hFile = CreateFile(Dlg.GetPathName().GetString(), GENERIC_READ, 0, 0,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

		if (INVALID_HANDLE_VALUE == hFile)
		{
			AfxMessageBox(L"Trigger Load Failed!!");
			return;
		}

		CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
		CToolView* pMainView = dynamic_cast<CToolView*>(pMainFrm->m_MainSplit.GetPane(0, 1));

		/* �ʱ�ȭ */
		CTriggerMgr::GetInstance()->Release();
		vector<INFO*>& vecTrigger = CTriggerMgr::GetInstance()->GetVecTrigger();

		INFO tInfo = {};
		DWORD dwByte = 0;

		while (true)
		{
			ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, nullptr);

			if (0 == dwByte)
			{
				AfxMessageBox(L"Trigger Load Success!!");
				break;
			}

			INFO* pInfo = new INFO(tInfo);
			vecTrigger.push_back(pInfo);
		}

		CloseHandle(hFile);
		pMainView->Invalidate(FALSE);
	}

	UpdateData(FALSE);

}


void CTriggerTool::OnBnClickedSave()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);

	CFileDialog Dlg(FALSE, L"dat", L"*.dat", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"Data Files(*.dat)|*.dat||", this);

	TCHAR szPath[MAX_STR] = L"";

	GetCurrentDirectory(MAX_STR, szPath);
	CFileInfo::ConvertRelativePath(szPath);
	PathRemoveFileSpec(szPath);
	lstrcat(szPath, L"\\Data");

	Dlg.m_ofn.lpstrInitialDir = szPath;

	if (IDOK == Dlg.DoModal())
	{
		HANDLE hFile = CreateFile(Dlg.GetPathName().GetString(), GENERIC_WRITE, 0, 0,
			CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

		if (INVALID_HANDLE_VALUE == hFile)
		{
			AfxMessageBox(L"Trigger Save Failed!!");
			return;
		}

		vector<INFO*>& vecTrigger = CTriggerMgr::GetInstance()->GetVecTrigger();

		DWORD dwByte = 0;

		for (auto& pInfo : vecTrigger)
			WriteFile(hFile, pInfo, sizeof(INFO), &dwByte, nullptr);

		CloseHandle(hFile);
	}

	AfxMessageBox(L"Trigger Save Success");
	UpdateData(FALSE);
}
