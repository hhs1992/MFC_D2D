// MonsterTool.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "MonsterTool.h"
#include "afxdialogex.h"

#include "MainFrm.h"
#include "ToolView.h"
// CMonsterTool ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CMonsterTool, CDialog)

CMonsterTool::CMonsterTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_MONSTERTOOL, pParent)
	, m_fAttSpd(0)
	, m_fBulletSpd(0)
{

}

CMonsterTool::~CMonsterTool()
{
}

void CMonsterTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RADIO1, m_RadioType[0]);
	DDX_Control(pDX, IDC_RADIO2, m_RadioType[1]);
	DDX_Control(pDX, IDC_RADIO3, m_RadioType[2]);
	DDX_Control(pDX, IDC_LIST1, m_ListBox);
	DDX_Control(pDX, IDC_LIST2, m_SetBox);
	DDX_Text(pDX, IDC_EDIT1, m_fAttSpd);
	DDX_Text(pDX, IDC_EDIT8, m_fBulletSpd);
}


BEGIN_MESSAGE_MAP(CMonsterTool, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CMonsterTool::OnBnClickedSetBtn)
	ON_WM_SYSCOMMAND()
	ON_WM_DROPFILES()
END_MESSAGE_MAP()


// CMonsterTool �޽��� ó�����Դϴ�.

BOOL CMonsterTool::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	// ���� �ʱ�ȭ
	m_RadioType[0].SetCheck(TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CMonsterTool::Release()
{
}

void CMonsterTool::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	if (nID == SC_CLOSE)
	{
		CMainFrame* pMainFrame = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
		CToolView*	pMainView = dynamic_cast<CToolView*>(pMainFrame->m_MainSplit.GetPane(0, 1));

		pMainView->m_bOnMonsterTool = false;
	}

	CDialog::OnSysCommand(nID, lParam);
}


void CMonsterTool::OnBnClickedSetBtn()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CMonsterTool::OnDropFiles(HDROP hDropInfo)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CDialog::OnDropFiles(hDropInfo);
}


