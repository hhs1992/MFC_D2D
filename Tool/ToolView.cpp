
// ToolView.cpp : CToolView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "Tool.h"
#endif

#include "MainFrm.h"
#include "ToolDoc.h"
#include "ToolView.h"

#include "MiniView.h"
#include "Terrain.h"
#include "MyForm.h"
#include "MapTool.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

HWND g_hWnd;

// CToolView

IMPLEMENT_DYNCREATE(CToolView, CScrollView)

BEGIN_MESSAGE_MAP(CToolView, CScrollView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// CToolView ����/�Ҹ�

CToolView::CToolView()
	: m_bIsMapTool(false)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CToolView::~CToolView()
{
	CSubTile::GetInstance()->DestroyInstance();
	CTerrain::GetInstance()->DestroyInstance();

	CTextureMgr::GetInstance()->DestroyInstance();
	CDevice::GetInstance()->DestroyInstance();
}

BOOL CToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CScrollView::PreCreateWindow(cs);
}

// CToolView �׸���

void CToolView::OnDraw(CDC* /*pDC*/)
{
	CToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CDevice::GetInstance()->Render_Begin();

	
	CTerrain::GetInstance()->Render();
	CSubTile::GetInstance()->Render();
	
	CDevice::GetInstance()->Render_End();

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}


// CToolView �μ�

BOOL CToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CToolView ����

#ifdef _DEBUG
void CToolView::AssertValid() const
{
	CView::AssertValid();
}

void CToolView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CToolDoc* CToolView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CToolDoc)));
	return (CToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CToolView �޽��� ó����


void CToolView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	// ��ũ�� �� �߰�
	SetScrollSizes(MM_TEXT, CSize(TILECX * TILEX_NORMAL, TILECY * TILEX_NORMAL));

	g_hWnd = m_hWnd;

	CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetMainWnd());

	RECT rcMainWnd = {};
	pMainFrm->GetWindowRect(&rcMainWnd);

	SetRect(&rcMainWnd, 0, 0, rcMainWnd.right - rcMainWnd.left, rcMainWnd.bottom - rcMainWnd.top);

	RECT rcView = {};

	GetClientRect(&rcView);

	int iRowFrm = rcMainWnd.right - rcView.right;
	int iColFrm = rcMainWnd.bottom - rcView.bottom;

	pMainFrm->SetWindowPos(nullptr, 0, 0, WINCX + iRowFrm, WINCY + iColFrm, SWP_NOZORDER);

	if (FAILED(CDevice::GetInstance()->InitDevice()))
	{
		AfxMessageBox(L"Device Init Failed!!!");
		return;
	}

	// �ͷ��� �ʱ�ȭ
	CTerrain::GetInstance()->Initialize();
	CTerrain::GetInstance()->SetMainView(this);

	// ���� Ÿ�� �ʱ�ȭ
	CSubTile::GetInstance()->Initialize();
	CSubTile::GetInstance()->SetMainView(this);
}


void CToolView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.


	UpdateData(TRUE);

	// �̴Ϻ並 ����
	//CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetMainWnd());
	CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CMyForm* pMyForm = dynamic_cast<CMyForm*>(pMainFrm->m_SecondSplit.GetPane(1, 0));

	// ���콺�� ��ũ�Ѱ� �߰�
	point.x += GetScrollPos(0);
	point.y += GetScrollPos(1);

	/* OnTileTool */
	if (m_bIsMapTool)
	{

		// Ÿ�� DrawID ����
		int iDrawID = pMyForm->m_MapTool.m_iDrawID;

		/* Ÿ�Ͽɼ� ����(�̵��Ұ� ����) */
		BYTE byOption = 0;

		if (pMyForm->m_MapTool.m_CheckMove.GetCheck() == TRUE)
			byOption = 1;
		else
			byOption = 0;

		/* Room Number ���� */
		BYTE byRoomNum = 0;
		byRoomNum = pMyForm->m_MapTool.m_byTileRoomNum;

		CTerrain::GetInstance()->TileChange(D3DXVECTOR3((float)point.x, (float)point.y, 0.f), iDrawID, byOption, byRoomNum);

		// Invalidate: WM_PAINT�� WM_ERASEBKGND �޽����� �߻�.
		Invalidate(FALSE);


		CMiniView* pMiniView = dynamic_cast<CMiniView*>(pMainFrm->m_SecondSplit.GetPane(0, 0));
		pMiniView->Invalidate(FALSE);

	}
	else if (m_bOnSubTileTool)
	{
		int iIndex = CTerrain::GetInstance()->GetTileIndex(D3DXVECTOR3((float)point.x, (float)point.y, 0.f));

		// Ÿ�� �ε������� ����� ����
		if (iIndex < 0 || (size_t)iIndex > CTerrain::GetInstance()->GetVecTile().size())
			return;

		D3DXVECTOR3 vPos = CTerrain::GetInstance()->GetTilePos(iIndex);

		int iDrawID = pMyForm->m_SubTileTool.m_iDrawID;
		CSubTile::GetInstance()->AddSubTile(vPos, iDrawID);
		Invalidate(FALSE);
	}

	UpdateData(FALSE);

	CScrollView::OnLButtonDown(nFlags, point);

}


void CToolView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CScrollView::OnMouseMove(nFlags, point);

	/* ���콺 ������ �� Ÿ������ ����ϴ� �Լ� */

	UpdateData(TRUE);

	CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CMyForm* pMyForm = dynamic_cast<CMyForm*>(pMainFrm->m_SecondSplit.GetPane(1, 0));


	if (m_bIsMapTool)
	{

		// ���콺�� ��ũ�Ѱ� �߰�
		point.x += GetScrollPos(0);
		point.y += GetScrollPos(1);

		int iTileIndex = 0;

		iTileIndex = CTerrain::GetInstance()->GetTileIndex(D3DXVECTOR3((float)point.x, (float)point.y, 0.f));

		vector<TILE*>& vecTile = CTerrain::GetInstance()->GetVecTile();

		// �ε����� �������� ����� return
		if (iTileIndex < 0 || (size_t)iTileIndex > vecTile.size())
			return;

		pMyForm->m_MapTool.UpdateData(TRUE);
		pMyForm->m_MapTool.m_byCursorIndex = iTileIndex;
		pMyForm->m_MapTool.m_byCursorDrawID = vecTile[iTileIndex]->byDrawID;
		pMyForm->m_MapTool.m_byTileOption = vecTile[iTileIndex]->byOption;
		pMyForm->m_MapTool.m_byCursorRoomNum = vecTile[iTileIndex]->byRoomNum;
		pMyForm->m_MapTool.UpdateData(FALSE);
	}

	UpdateData(FALSE);
}


void CToolView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	UpdateData(TRUE);

	if (m_bOnSubTileTool)
	{
		int iIndex = CTerrain::GetInstance()->GetTileIndex(D3DXVECTOR3((float)point.x, (float)point.y, 0.f));

		// Ÿ�� �ε������� ����� ����
		if (iIndex < 0 || (size_t)iIndex > CTerrain::GetInstance()->GetVecTile().size())
			return;

		// Ÿ�� �ε����� ���͸� �޾ƿ´�.
		D3DXVECTOR3 vTilePos = CTerrain::GetInstance()->GetTilePos(iIndex);

		vector<TILE*> vecTile = CSubTile::GetInstance()->GetSubTile();

		auto& iter_find = vecTile.begin();

		for (; iter_find != vecTile.end();)
		{
			if ((*iter_find)->vPos == vTilePos)
			{
				SafeDelete(*iter_find);
				iter_find = vecTile.erase(iter_find);
				Invalidate(FALSE);
			}
			else
				++iter_find;
		}
	}
	UpdateData(FALSE);

	CScrollView::OnRButtonDown(nFlags, point);
}
