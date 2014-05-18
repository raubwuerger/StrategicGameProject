
// HoIScenarioDesignerView.cpp : implementation of the CHoIScenarioDesignerView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "HoIScenarioDesigner.h"
#endif

#include "HoIScenarioDesignerDoc.h"
#include "HoIScenarioDesignerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHoIScenarioDesignerView

IMPLEMENT_DYNCREATE(CHoIScenarioDesignerView, CView)

BEGIN_MESSAGE_MAP(CHoIScenarioDesignerView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CHoIScenarioDesignerView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CHoIScenarioDesignerView construction/destruction

CHoIScenarioDesignerView::CHoIScenarioDesignerView()
{
	// TODO: add construction code here

}

CHoIScenarioDesignerView::~CHoIScenarioDesignerView()
{
}

BOOL CHoIScenarioDesignerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CHoIScenarioDesignerView drawing

void CHoIScenarioDesignerView::OnDraw(CDC* /*pDC*/)
{
	CHoIScenarioDesignerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CHoIScenarioDesignerView printing


void CHoIScenarioDesignerView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CHoIScenarioDesignerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CHoIScenarioDesignerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CHoIScenarioDesignerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CHoIScenarioDesignerView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CHoIScenarioDesignerView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CHoIScenarioDesignerView diagnostics

#ifdef _DEBUG
void CHoIScenarioDesignerView::AssertValid() const
{
	CView::AssertValid();
}

void CHoIScenarioDesignerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CHoIScenarioDesignerDoc* CHoIScenarioDesignerView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHoIScenarioDesignerDoc)));
	return (CHoIScenarioDesignerDoc*)m_pDocument;
}
#endif //_DEBUG


// CHoIScenarioDesignerView message handlers
