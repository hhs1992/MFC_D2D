// BossTool.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "BossTool.h"
#include "afxdialogex.h"

#include "MainFrm.h"
#include "ToolView.h"


// CBossTool ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CBossTool, CDialog)

CBossTool::CBossTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_BOSSTOOL, pParent)
	, m_byRoom(0)
{

}

CBossTool::~CBossTool()
{
}

void CBossTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_byRoom);
}


BEGIN_MESSAGE_MAP(CBossTool, CDialog)
	ON_EN_CHANGE(IDC_EDIT1, &CBossTool::OnEnChangeRoom)
	ON_BN_CLICKED(IDC_BUTTON1, &CBossTool::OnBnClickedClear)
	ON_BN_CLICKED(IDC_BUTTON1, &CBossTool::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON8, &CBossTool::OnBnClickedClear)
	ON_BN_CLICKED(IDC_BUTTON11, &CBossTool::OnBnClickedLoad)
	ON_BN_CLICKED(IDC_BUTTON12, &CBossTool::OnBnClickedSave)
	ON_WM_SYSCOMMAND()
	ON_BN_CLICKED(IDC_BUTTON3, &CBossTool::OnBnClickedCancel)
END_MESSAGE_MAP()


// CBossTool �޽��� ó�����Դϴ�.


void CBossTool::OnEnChangeRoom()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialog::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	UpdateData(TRUE);
	UpdateData(FALSE);
}






void CBossTool::OnBnClickedClear()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);

	CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CToolView* pMainView = dynamic_cast<CToolView*>(pMainFrm->m_MainSplit.GetPane(0, 1));

	CDark::GetInstance()->Release();
	pMainView->Invalidate(FALSE);

	UpdateData(FALSE);
}


void CBossTool::OnBnClickedLoad()
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
			AfxMessageBox(L"Dark Load Failed!!");
			return;
		}

		CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
		CToolView* pMainView = dynamic_cast<CToolView*>(pMainFrm->m_MainSplit.GetPane(0, 1));

		/* �ʱ�ȭ */
		CDark::GetInstance()->Release();
		vector<INFO*>& vecDark = CDark::GetInstance()->GetvecDark();

		INFO tInfo = {};
		DWORD dwByte = 0;

		while (true)
		{
			ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, nullptr);

			if (0 == dwByte)
			{
				AfxMessageBox(L"Dark Load Success!!");
				break;
			}

			INFO* pInfo = new INFO(tInfo);
			vecDark.push_back(pInfo);
		}

		CloseHandle(hFile);
		pMainView->Invalidate(FALSE);
	}

	UpdateData(FALSE);
}


void CBossTool::OnBnClickedSave()
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
			AfxMessageBox(L"Dark Save Failed!!");
			return;
		}

		vector<INFO*>& vecDark = CDark::GetInstance()->GetvecDark();

		DWORD dwByte = 0;

		for (auto& pInfo : vecDark)
			WriteFile(hFile, pInfo, sizeof(INFO), &dwByte, nullptr);
		CloseHandle(hFile);
	}

	AfxMessageBox(L"Dark Save Success");
	UpdateData(FALSE);
}


void CBossTool::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	if (nID == SC_CLOSE) {
		CMainFrame* pMainFrame = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
		CToolView*	pMainView = dynamic_cast<CToolView*>(pMainFrame->m_MainSplit.GetPane(0, 1));

		pMainView->m_bOnBossTool = false;
	}

	CDialog::OnSysCommand(nID, lParam);
}


void CBossTool::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);

	CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CToolView* pMainView = dynamic_cast<CToolView*>(pMainFrm->m_MainSplit.GetPane(0, 1));

	if (CDark::GetInstance()->GetvecDark().empty() == false)
	{
		CDark::GetInstance()->GetvecDark().pop_back();
		pMainView->Invalidate(FALSE);
	}

	UpdateData(FALSE);
}
