// FilePath.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "FilePath.h"
#include "afxdialogex.h"
#include "FileInfo.h"

// CFilePath ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CFilePath, CDialog)

CFilePath::CFilePath(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_FILEPATH, pParent)
{

}

CFilePath::~CFilePath()
{
	for_each(m_PathInfoLst.begin(), m_PathInfoLst.end(), SafeDelete<IMGPATH*>);
	m_PathInfoLst.clear();
}

void CFilePath::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_ListBox);
}


BEGIN_MESSAGE_MAP(CFilePath, CDialog)
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_BUTTON1, &CFilePath::OnBnClickedSave)
	ON_BN_CLICKED(IDC_BUTTON8, &CFilePath::OnBnClickedLoad)
END_MESSAGE_MAP()


// CFilePath �޽��� ó�����Դϴ�.


void CFilePath::OnDropFiles(HDROP hDropInfo)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CDialog::OnDropFiles(hDropInfo);

	UpdateData(TRUE);

	int iCount = DragQueryFile(hDropInfo, -1, nullptr, 0);

	TCHAR szFullPath[MAX_STR] = L"";

	for (int i = 0; i < iCount; ++i)
	{
		DragQueryFile(hDropInfo, i, szFullPath, MAX_STR);
		CFileInfo::DirInfoExtraction(szFullPath, m_PathInfoLst);
	}

	m_ListBox.ResetContent();

	wstring wstrCombine = L"";
	TCHAR szCount[MIN_STR] = L"";

	for (auto& pImgPath : m_PathInfoLst)
	{
		// _itow_s: ���� -> ���ڿ��� ��ȯ.
		_itow_s(pImgPath->iCount, szCount, 10); // ���� 10������ ��ȯ.


		wstrCombine = pImgPath->wstrObjKey + L"|" + pImgPath->wstrStateKey +
			L"|" + szCount + L"|" + pImgPath->wstrPath;

		m_ListBox.AddString(wstrCombine.c_str());
	}

	UpdateData(FALSE);
}


void CFilePath::OnBnClickedSave()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.


	wofstream fout;

	fout.open(L"../Data/ImgPath.txt");

	if (fout.fail())
	{
		AfxMessageBox(L"ImgPath Save Failed");
		return;
	}

	for (auto& pImgPath : m_PathInfoLst)
	{
		fout << pImgPath->wstrObjKey << L"|" << pImgPath->wstrStateKey << L"|"
			<< pImgPath->iCount << L"|" << pImgPath->wstrPath << endl;
	}

	fout.close();

	// WinExec: �������� �⺻ ���α׷��� ����.
	WinExec("notepad.exe ../Data/ImgPath.txt", SW_SHOW);
}


void CFilePath::OnBnClickedLoad()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	//UpdateData(TRUE);

	//wifstream fin;

	//fin.open(L"../Data/ImgPath.txt");

	//if (fin.fail())
	//{
	//	AfxMessageBox(L"ImgPath Load Failed");
	//	return;
	//}

	//// �ҷ����� ���� ��� ������ ����!
	//for_each(m_PathInfoLst.begin(), m_PathInfoLst.end(), SafeDelete<IMGPATH*>);
	//m_PathInfoLst.clear();

	//m_ListBox.ResetContent();

	//TCHAR szObjKey[MAX_STR] = L"";
	//TCHAR szStateKey[MAX_STR] = L"";
	//TCHAR szCount[MIN_STR] = L"";
	//TCHAR szPath[MAX_STR] = L"";

	//wstring strCombine = L"";

	//while (true)
	//{
	//	// ������('|') ������ ��� �о����.
	//	fin.getline(szObjKey, MAX_STR, '|');
	//	fin.getline(szStateKey, MAX_STR, '|');
	//	fin.getline(szCount, MIN_STR, '|');
	//	fin.getline(szPath, MAX_STR);

	//	// eof: ���� �����ڰ� eof�ڸ��� �Ѿ�� true ��ȯ.
	//	if (fin.eof())
	//		break;

	//	strCombine = wstring(szObjKey) + L"|" + szStateKey + L"|" + szCount + L"|"
	//		+ szPath;

	//	m_ListBox.AddString(strCombine.c_str());

	//	IMGPATH* pImgPath = new IMGPATH;

	//	pImgPath->wstrObjKey = szObjKey;
	//	pImgPath->wstrStateKey = szStateKey;
	//	pImgPath->wstrPath = szPath;

	//	// _ttoi: ���ڿ� -> ������ ��ȯ.
	//	pImgPath->iCount = _ttoi(szCount);

	//	m_PathInfoLst.push_back(pImgPath);
	//}

	//UpdateData(FALSE);
}
