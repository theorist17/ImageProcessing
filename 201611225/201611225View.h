
// 201611225View.h : interface of the CMy201611225View class
//

#pragma once
#include "Jpegfile.h"

class CMy201611225View : public CView
{
protected: // create from serialization only
	CMy201611225View();
	DECLARE_DYNCREATE(CMy201611225View)

// Attributes
public:
	CMy201611225Doc* GetDocument() const;

	// Bitmap info
	RGBQUAD** rgbBuffer; // double pointer to image
	int imgHeight;
	int imgWidth;
	BITMAPINFOHEADER bmpInfo;
	BITMAPFILEHEADER bmpHeader;
	int viewType;

	// RGB to HSI
	float** hueBuffer;
	float** satuBuffer;
	float** intenBuffer;

	// JPEG

	// Intensity histogram
	int intenHisto[256];

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
	virtual ~CMy201611225View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnImageloadBmp();
	afx_msg void OnTransformRgbtohsi();
	afx_msg void OnImageloadJpeg();
	BYTE* LoadJpegFromOpenFile(FILE* fp, BITMAPINFOHEADER* pbh, UINT* pWidth, UINT* pHeight);
	afx_msg void OnTransformHistogramequalization();
};

#ifndef _DEBUG  // debug version in 201611225View.cpp
inline CMy201611225Doc* CMy201611225View::GetDocument() const
   { return reinterpret_cast<CMy201611225Doc*>(m_pDocument); }
#endif

