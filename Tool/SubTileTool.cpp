// SubTileTool.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "SubTileTool.h"
#include "afxdialogex.h"

#include "MainFrm.h"
#include "ToolView.h"
// CSubTileTool ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CSubTileTool, CDialog)

CSubTileTool::CSubTileTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_SUBTILETOOL, pParent),
	m_pImage(nullptr)
{

}

CSubTileTool::~CSubTileTool()
{
	Release();
}

void CSubTileTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PICTURE2, m_PictureCtrl);
	DDX_Control(pDX, IDC_LIST1, m_SubTileBox);
}


BEGIN_MESSAGE_MAP(CSubTileTool, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_BUTTON5, &CSubTileTool::OnBnClickedSubTileListSave)
	ON_BN_CLICKED(IDC_BUTTON2, &CSubTileTool::OnBnClickedSubTileListLoad)
	ON_LBN_SELCHANGE(IDC_LIST1, &CSubTileTool::OnLbnSelectSubTileBox)
END_MESSAGE_MAP()


// CSubTileTool �޽��� ó�����Դϴ�.


void CSubTileTool::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	if (nID == SC_CLOSE)
	{
		CMainFrame* pMainFrame = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
		CToolView*	pMainView = dynamic_cast<CToolView*>(pMainFrame->m_MainSplit.GetPane(0, 1));

		pMainView->m_bOnSubTileTool = false;
	}

	CDialog::OnSysCommand(nID, lParam);
}


void CSubTileTool::OnDropFiles(HDROP hDropInfo)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	UpdateData(TRUE);

	//m_TileBox.ResetContent();
	TCHAR szFilePath[MAX_STR] = L"";

	int iFileCnt = DragQueryFile(hDropInfo, -1, nullptr, 0);
	TCHAR szFileName[MAX_STR] = L"";

	for (int i = 0; i < iFileCnt; ++i)
	{
		DragQueryFile(hDropInfo, i, szFilePath, MAX_STR);

		CString strRelativePath = CFileInfo::ConvertRelativePath(szFilePath);

		CString strFileName = PathFindFileName(strRelativePath.GetString());

		lstrcpy(szFileName, strFileName.GetString());	// ��� ���
		PathRemoveExtension(szFileName);	// ���ϸ�

		strFileName = szFileName;

		auto iter_find = m_mapTilePath.find(strFileName);

		if (m_mapTilePath.end() == iter_find)
		{
			m_mapTilePath.insert({ strFileName, szFilePath });
			m_SubTileBox.AddString(szFileName);
		}
	}

	// �ʿ� �̹��� �̸�, ��� ��� ����


	UpdateData(FALSE);


	CDialog::OnDropFiles(hDropInfo);
}


void CSubTileTool::Release()
{
	if (m_pImage)
	{
		m_pImage->Destroy();
		delete m_pImage;
		m_pImage = nullptr;
	}
}


void CSubTileTool::OnBnClickedSubTileListSave()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
		CString strGetPath = Dlg.GetPathName();
		const TCHAR* pGetPath = strGetPath.GetString();

		HANDLE hFile = CreateFile(pGetPath, GENERIC_WRITE, 0, 0,
			CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

		if (INVALID_HANDLE_VALUE == hFile)
		{
			AfxMessageBox(L"TileList Save Failed!!");
			return;
		}

		DWORD dwByte = 0;

		for (auto& MyPair : m_mapTilePath)
		{
			const TCHAR* pKey = MyPair.first.GetString();
			int iKeyLength = MyPair.first.GetLength() + 1;
			const TCHAR* pPath = MyPair.second.GetString();
			int iPathLength = MyPair.second.GetLength() + 1;


			WriteFile(hFile, &iKeyLength, sizeof(int), &dwByte, nullptr);
			WriteFile(hFile, pKey, sizeof(TCHAR) * iKeyLength, &dwByte, nullptr);
			WriteFile(hFile, &iPathLength, sizeof(int), &dwByte, nullptr);
			WriteFile(hFile, pPath, sizeof(TCHAR) * iPathLength, &dwByte, nullptr);
		}

		CloseHandle(hFile);
	}

	AfxMessageBox(L"TileList Save Success");
	UpdateData(FALSE);
}


void CSubTileTool::OnBnClickedSubTileListLoad()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	HANDLE hFile = CreateFile(L"../Data/SubTileList.dat", GENERIC_READ, 0, 0,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		AfxMessageBox(L"TileList Load Failed!!");
		/*return;*/
	}

	int i = 0;

	DWORD dwByte = 0;
	TCHAR* pKey = L"";
	TCHAR* pPath = L"";
	int iLength = 0;

	while (true)
	{
		ReadFile(hFile, &iLength, sizeof(int), &dwByte, nullptr);
		pKey = new TCHAR[iLength];
		ReadFile(hFile, pKey, sizeof(TCHAR) * iLength, &dwByte, nullptr);

		ReadFile(hFile, &iLength, sizeof(int), &dwByte, nullptr);
		pPath = new TCHAR[iLength];
		ReadFile(hFile, pPath, sizeof(TCHAR) * iLength, &dwByte, nullptr);

		if (dwByte == 0)
		{
			delete pKey;
			pKey = nullptr;

			delete pPath;
			pPath = nullptr;

			break;
		}

		m_mapTilePath.insert({ pKey, pPath });
		m_SubTileBox.AddString(pKey);
	}
}


void CSubTileTool::OnLbnSelectSubTileBox()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);

	int iSelect = m_SubTileBox.GetCurSel();

	if (LB_ERR == iSelect)
		return;

	CString strSelectName;
	m_SubTileBox.GetText(iSelect, strSelectName);


	// �̹��� ����
	auto& iter_find = m_mapTilePath.find(strSelectName);

	if (m_pImage)
	{
		m_pImage->Destroy();
		delete m_pImage;
		m_pImage = nullptr;
	}

	m_pImage = new CImage;
	m_pImage->Load(iter_find->second);
	m_PictureCtrl.SetBitmap(*m_pImage);

	// DrawID ����
	int i = 0;

	for (; i < strSelectName.GetLength(); ++i)
	{
		if (0 != isdigit(strSelectName[i]))
			break;
	}

	strSelectName.Delete(0, i);
	m_iDrawID = _tstoi(strSelectName);

	UpdateData(FALSE);
}
