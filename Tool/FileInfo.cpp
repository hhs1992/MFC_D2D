#include "stdafx.h"
#include "FileInfo.h"


CFileInfo::CFileInfo()
{
}


CFileInfo::~CFileInfo()
{
}

CString CFileInfo::ConvertRelativePath(CString strFullPath)
{
	TCHAR szRelativePath[MAX_STR] = L"";

	TCHAR szCurrentPath[MAX_STR] = L"";

	GetCurrentDirectory(MAX_STR, szCurrentPath);

	PathRelativePathTo(szRelativePath, szCurrentPath, FILE_ATTRIBUTE_DIRECTORY,
		strFullPath.GetString(), FILE_ATTRIBUTE_DIRECTORY);

	return CString(szRelativePath);
}

void CFileInfo::DirInfoExtraction(const wstring & wstrPath, list<IMGPATH*>& rPathInfoLst)
{
	wstring wstrFilePath = wstrPath + L"\\*.*";

	// CFileFind: ���� �� ��� ��� ���õ� ��ɵ��� �����ϴ� MFC�� Ŭ����.
	CFileFind	find;

	// ���� ��ο��� ù��° ������ Ž��.
	find.FindFile(wstrFilePath.c_str());

	int iContinue = 1;

	while (iContinue)
	{
		// ���� ��� �ȿ��� ���� ���� Ž��.
		iContinue = find.FindNextFile();

		// IsDots: ���� ã�� �����̸��� .�̳� ..���� Ȯ���ϴ� �Լ�. .�̳� ..�̶�� true�� ��ȯ.
		if (find.IsDots())
			continue;

		// IsDirectory: ã�� �̸��� ���ϸ��� �ƴ� �������̶�� true�� ��ȯ.
		else if (find.IsDirectory())
		{
			// GetFilePath: ���� find��ü�� �����ϰ� �ִ� ��θ� ��ȯ.
			DirInfoExtraction(wstring(find.GetFilePath()), rPathInfoLst); // ��� ȣ��
		}
		else // find��ü�� ã���� ���ϸ��� ��
		{
			// ã�� ������ �������ִ� �ý��� �����̶�� �ǳʶپ��!
			if (find.IsSystem())
				continue;

			IMGPATH* pImgPath = new IMGPATH;
			TCHAR szCurPath[MAX_STR] = L"";

			// \87��\Framework87\Texture\Stage\PLAYER\Attack\AKIHA_AKI01_000.png
			lstrcpy(szCurPath, find.GetFilePath().GetString());

			// ���ϸ�� Ȯ���ڸ� �߶󳽴�.
			// \87��\Framework87\Texture\Stage\PLAYER\Attack
			PathRemoveFileSpec(szCurPath);

			// ���� ���� ���� ������ ������ ��´�.
			pImgPath->iCount = DirFileCount(szCurPath);

			// GetFileTitle: ��� �󿡼� ������ ���ϸ� ������ �Լ�.
			// wstrTextureName = AKIHA_AKI01_000;
			wstring wstrTextureName = find.GetFileTitle().GetString();

			// substr(����, ��): ���۰� ���� �ش��ϴ� ���ڿ��� ������ �Լ�.
			// wstrTextureName = AKIHA_AKI01_00%d.png;
			wstrTextureName = wstrTextureName.substr(0, wstrTextureName.length() - 1) + L"%d.png";

			TCHAR szFullPath[MAX_STR] = L"";

			// PathCombine(dst, src1, src2): src1�� src2�� ������ �ϼ��� ��θ� dst�� ����.
			// src1�� src2 ���̿� \�� \\�� �ڵ� ����.
			// szFullPath: \87��\Framework87\Texture\Stage\PLAYER\Attack\AKIHA_AKI01_00%d.png;
			PathCombine(szFullPath, szCurPath, wstrTextureName.c_str());

			// ��� ��� ��ȯ.
			// pImgPath->wstrPath: ..\Texture\Stage\PLAYER\Attack\AKIHA_AKI01_00%d.png;
			pImgPath->wstrPath = ConvertRelativePath(szFullPath);

			// PathFindFileName: ��� �� ���ϸ��� ã�ų� ���� �������� ã�� �Լ�.
			pImgPath->wstrStateKey = PathFindFileName(szCurPath);

			PathRemoveFileSpec(szCurPath);
			pImgPath->wstrObjKey = PathFindFileName(szCurPath);

			rPathInfoLst.push_back(pImgPath);
			iContinue = 0;
		}

	}
}

int CFileInfo::DirFileCount(const wstring & wstrPath)
{
	wstring wstrFilePath = wstrPath + L"\\*.*";

	CFileFind find;

	// Ž�� ����.
	find.FindFile(wstrFilePath.c_str());

	int iFileCnt = 0;
	int iContinue = 1;

	while (iContinue)
	{
		iContinue = find.FindNextFile();

		if (find.IsDots())
			continue;
		else if (find.IsDirectory())
			continue;
		else if (find.IsSystem())
			continue;

		++iFileCnt;
	}

	return iFileCnt;
}
