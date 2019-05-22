
// 201611225View.h : interface of the CMy201611225View class
//

#pragma once
#include "Jpegfile.h"
#include <algorithm>
#include <sstream>
#include <cmath>
#include "opencv2/opencv.hpp"

using namespace cv;

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#ifndef BLOCK_SIZE
#define BLOCK_SIZE 8
#endif

#ifndef WINDOW_SIZE
#define WINDOW_SIZE 16
#endif

#ifndef FRAME_INTERVAL
#define FRAME_INTERVAL 1
#endif


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

	// Grayscale
	int** intensity;
	int** intenNext;
	
	// Bitscale
	int** binary;
	int** label;
	int labels;
	int** colors;

	int intenHisto[256];
	int intenEqual[256];
	int intenSum[256];
	int intenEquisum[256];


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
	void ReadIntensity();
	void ReadBinary();
	afx_msg void OnGaussianfiltering3();
	afx_msg void OnMedianfiltering3();
	afx_msg void OnAveragefiltering3();
	afx_msg void OnGaussianfiltering5();
	afx_msg void OnMedianfiltering5();
	afx_msg void OnAveragefiltering5();
	afx_msg void OnGaussianfiltering7();
	afx_msg void OnMedianfiltering7();
	afx_msg void OnAveragefiltering7();
	void FilterCreation(double GKernel[][5]);

	afx_msg void OnImageloadAvi();
	afx_msg void OnMotion3ss();
	afx_msg void OnConnectivity4();
};

#ifndef _DEBUG  // debug version in 201611225View.cpp
inline CMy201611225Doc* CMy201611225View::GetDocument() const
   { return reinterpret_cast<CMy201611225Doc*>(m_pDocument); }
#endif

