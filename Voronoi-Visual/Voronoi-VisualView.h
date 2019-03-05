
// Voronoi-VisualView.h : interface of the CVoronoiVisualView class
//

#pragma once
#include "Voronoi.h"
#include "Voronoi-VisualDoc.h"
class CVoronoiVisualView : public CView
{
protected: // create from serialization only
	CVoronoiVisualView() noexcept;
	DECLARE_DYNCREATE(CVoronoiVisualView)

// Attributes
public:
	CVoronoiVisualDoc* GetDocument() const;
	Voronoi *v_systemPtr;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CVoronoiVisualView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnOptStart();
};

#ifndef _DEBUG  // debug version in Voronoi-VisualView.cpp
inline CVoronoiVisualDoc* CVoronoiVisualView::GetDocument() const
   { return reinterpret_cast<CVoronoiVisualDoc*>(m_pDocument); }
#endif

