
// Voronoi-VisualView.cpp : implementation of the CVoronoiVisualView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Voronoi-Visual.h"
#endif

#include "Voronoi-VisualDoc.h"
#include "Voronoi-VisualView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CVoronoiVisualView

IMPLEMENT_DYNCREATE(CVoronoiVisualView, CView)

BEGIN_MESSAGE_MAP(CVoronoiVisualView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_OPT_START, &CVoronoiVisualView::OnOptStart)
END_MESSAGE_MAP()

// CVoronoiVisualView construction/destruction

CVoronoiVisualView::CVoronoiVisualView() noexcept
{
	// TODO: add construction code here
	v_systemPtr = new Voronoi(50, 30, 10,this);

}

CVoronoiVisualView::~CVoronoiVisualView()
{
	delete v_systemPtr;
}

BOOL CVoronoiVisualView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CVoronoiVisualView drawing

void CVoronoiVisualView::OnDraw(CDC* pDC)
{
	CVoronoiVisualDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	CBrush brush;
	brush.CreateSolidBrush(RGB(255, 0, 0));
	pDC->SelectObject(&brush);
	double coef = 40;
	int r = 6;
	for (Vector2* site : v_systemPtr->set_Sites_Ptrs)
	{
		int x = (int)(site->x*coef + 0.5);
		int y = (int)(site->y*coef + 0.5);
		pDC->Ellipse(x - r, y - r, x + r, y + r);
	}
	CPen pen(PS_SOLID, 2, RGB(0, 0, 0));
	pDC->SelectObject(&pen);
	for (Edge* edge : v_systemPtr->set_Edge_Ptrs)
	{
		int x1 = (int)(edge->e1.x*coef + 0.5);
		int y1 = (int)(edge->e1.y*coef + 0.5);
		int x2 = (int)(edge->e2.x*coef + 0.5);
		int y2 = (int)(edge->e2.y*coef + 0.5);
		pDC->MoveTo(x1, y1);
		pDC->LineTo(x2, y2);
	}

}


// CVoronoiVisualView printing

BOOL CVoronoiVisualView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CVoronoiVisualView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CVoronoiVisualView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CVoronoiVisualView diagnostics

#ifdef _DEBUG
void CVoronoiVisualView::AssertValid() const
{
	CView::AssertValid();
}

void CVoronoiVisualView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CVoronoiVisualDoc* CVoronoiVisualView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CVoronoiVisualDoc)));
	return (CVoronoiVisualDoc*)m_pDocument;
}
#endif //_DEBUG


// CVoronoiVisualView message handlers
UINT StartSM(LPVOID lpParam)
{
	CVoronoiVisualView *pview = (CVoronoiVisualView *)lpParam;
	pview->v_systemPtr->restart();
	return 1;
}

void CVoronoiVisualView::OnOptStart()
{
	// TODO: Add your command handler code here
	
	CWinThread*	m_pThread;
	m_pThread = nullptr;
	m_pThread = AfxBeginThread(StartSM, this);
}

