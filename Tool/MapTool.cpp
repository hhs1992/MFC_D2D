// MapTool.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "MapTool.h"
#include "afxdialogex.h"

#include "MainFrm.h"
#include "ToolView.h"
#include "Terrain.h"

// CMapTool ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CMapTool, CDialog)

CMapTool::CMapTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_MAPTOOL, pParent), m_iDrawID(0), m_pImage(nullptr)
	, m_strTileNum(_T(""))
	, m_byCursorIndex(0)
	, m_byCursorDrawID(0)
	, m_byTileOption(0)
	, m_byCursorRoomNum(0)
	, m_byTileRoomNum(0)
	, m_iTileX(0)
	, m_iTileY(0)
	, m_strStageName(_T(""))
{

}

CMapTool::~CMapTool()
{
	Release();
}

void CMapTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_TileBox);
	DDX_Control(pDX, IDC_PICTURE, m_PictureCtrl);
	DDX_Control(pDX, IDC_CHECK1, m_CheckMove);
	DDX_Text(pDX, IDC_EDIT1, m_strTileNum);
	DDX_Text(pDX, IDC_EDIT3, m_byCursorIndex);
	DDX_Text(pDX, IDC_EDIT4, m_byCursorDrawID);
	DDX_Text(pDX, IDC_EDIT6, m_byTileOption);
	DDX_Text(pDX, IDC_EDIT5, m_byCursorRoomNum);
	DDX_Text(pDX, IDC_EDIT2, m_byTileRoomNum);
	DDX_Text(pDX, IDC_EDIT7, m_iTileX);
	DDX_Text(pDX, IDC_EDIT9, m_iTileY);
	DDX_Control(pDX, IDC_LIST3, m_StageListBox);
	DDX_Text(pDX, IDC_EDIT10, m_strStageName);
}


BEGIN_MESSAGE_MAP(CMapTool, CDialog)

	ON_WM_DROPFILES()
	ON_LBN_SELCHANGE(IDC_LIST1, &CMapTool::OnLbnSelectTileBox)
	ON_WM_SYSCOMMAND()
	ON_BN_CLICKED(IDC_BUTTON1, &CMapTool::OnBnClickedSaveTile)
	ON_BN_CLICKED(IDC_BUTTON2, &CMapTool::OnBnClickedLoadTile)
	ON_BN_CLICKED(IDC_BUTTON3, &CMapTool::OnBnClickedTileListSave)
	ON_BN_CLICKED(IDC_BUTTON4, &CMapTool::OnBnClickedTileListLoad)
	ON_EN_CHANGE(IDC_EDIT1, &CMapTool::OnEnChangeFindTileNum)
	ON_EN_CHANGE(IDC_EDIT2, &CMapTool::OnEnChangeRoomNumber)
	ON_BN_CLICKED(IDC_BUTTON9, &CMapTool::OnBnClickedMapSet)
END_MESSAGE_MAP()


// CMapTool �޽��� ó�����Դϴ�.


void CMapTool::Release()
{
	if (m_pImage)
	{
		m_pImage->Destroy();

		delete m_pImage;
		m_pImage = nullptr;
	}
}

void CMapTool::TileListLoad()
{
	// ����Ʈ �ڽ� �ڵ� �ε�
	HANDLE hFile = CreateFile(L"../Data/TileList.dat", GENERIC_READ, 0, 0,
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
		m_TileBox.AddString(pKey);
	}
}

BOOL CMapTool::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	// �⺻������ �̵�����
	m_CheckMove.SetCheck(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CMapTool::OnDropFiles(HDROP hDropInfo)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CDialog::OnDropFiles(hDropInfo);

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
			m_mapTilePath.insert({ strFileName, strRelativePath });
			m_TileBox.AddString(szFileName);
		}
	}

	// �ʿ� �̹��� �̸�, ��� ��� ����


	UpdateData(FALSE);
}


void CMapTool::OnLbnSelectTileBox()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);

	int iSelect = m_TileBox.GetCurSel();

	if (LB_ERR == iSelect)
		return;

	CString strSelectName;
	m_TileBox.GetText(iSelect, strSelectName);


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


void CMapTool::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	if (nID == SC_CLOSE)
	{
		CMainFrame* pMainFrame = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
		CToolView*	pMainView = dynamic_cast<CToolView*>(pMainFrame->m_MainSplit.GetPane(0, 1));

		pMainView->m_bIsMapTool = false;
	}

	CDialog::OnSysCommand(nID, lParam);
}


void CMapTool::OnBnClickedSaveTile()
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
			AfxMessageBox(L"Tile Save Failed!!");
			return;
		}

		vector<TILE*>& vecTile = CTerrain::GetInstance()->GetVecTile();

		DWORD dwByte = 0;

		for (auto& pTile : vecTile)
			WriteFile(hFile, pTile, sizeof(TILE), &dwByte, nullptr);

		CloseHandle(hFile);
	}

	UpdateData(FALSE);
}


void CMapTool::OnBnClickedLoadTile()
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
			AfxMessageBox(L"Tile Load Failed!!");
			return;
		}

		CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
		CToolView* pMainView = dynamic_cast<CToolView*>(pMainFrm->m_MainSplit.GetPane(0, 1));
		

		CTerrain::GetInstance()->Release();
		vector<TILE*>& vecTile = CTerrain::GetInstance()->GetVecTile();

		TILE tTile = {};
		DWORD dwByte = 0;

		while (true)
		{
			ReadFile(hFile, &tTile, sizeof(TILE), &dwByte, nullptr);

			if (0 == dwByte)
				break;

			TILE* pTile = new TILE(tTile);
			vecTile.push_back(pTile);
		}

		CloseHandle(hFile);
		pMainView->Invalidate(FALSE);
	}

	UpdateData(FALSE);
}


void CMapTool::OnBnClickedTileListSave()
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


void CMapTool::OnBnClickedTileListLoad()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	// Ÿ�� ����Ʈ �ҷ�����
	TileListLoad();
}


void CMapTool::OnEnChangeFindTileNum()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialog::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);

	// Tile + �Էµ� Num

	CString strTile = L"Tile" + m_strTileNum;

	auto& iter_find = m_mapTilePath.find(strTile);

	// ������ ����
	if (iter_find == m_mapTilePath.end())
		return;

	// ������ �˻�
	int iFindIndex = m_TileBox.FindString(0, strTile);

	// Ž���� �����ϸ�
	if (iFindIndex == LB_ERR)
		return;

	m_TileBox.SetCurSel(iFindIndex);

	// DrawID ����
	m_iDrawID = _wtoi(m_strTileNum);

	// �̹��� ����
	if (m_pImage)
	{
		m_pImage->Destroy();
		delete m_pImage;
		m_pImage = nullptr;
	}

	m_pImage = new CImage;
	m_pImage->Load(iter_find->second);
	m_PictureCtrl.SetBitmap(*m_pImage);

	UpdateData(FALSE);
}



void CMapTool::OnEnChangeRoomNumber()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialog::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	UpdateData(TRUE);


	UpdateData(FALSE);
}


void CMapTool::OnBnClickedMapSet()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);

	//m_StageListBox.AddString(m_strStageName);

	UpdateData(FALSE);
}
