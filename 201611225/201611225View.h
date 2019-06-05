
// 201611225View.h : interface of the CMy201611225View class
//

#pragma once
#include "Jpegfile.h"
#include <algorithm>
#include <sstream>
#include <cmath>
#include "opencv2/opencv.hpp"
#include <map>
#include <deque>

using namespace cv;

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#ifndef BLOCK_SIZE
#define BLOCK_SIZE 16
#endif

#ifndef WINDOW_SIZE
#define WINDOW_SIZE 8
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

	// View type flag
	int viewType;

	// Bitmap info
	RGBQUAD** rgbBuffer; // double pointer to image
	int imgHeight;
	int imgWidth;
	BITMAPINFOHEADER bmpInfo;
	BITMAPFILEHEADER bmpHeader;

	// RGB to HSI
	float** hueBuffer;
	float** satuBuffer;
	float** intenBuffer;

	// JPEG

	// Grayscale
	int** intensity;
	int** intenNext;

	// Histogram equlization
	int intenHisto[256];
	int intenEqual[256];
	int intenSum[256];
	int intenEquisum[256];
	
	// Bitscale
	int** binary;
	int** label;
	int** randcolor;
	int*** ccacolor;

	// Scaling using interpolation
	RGBQUAD** scaled;
	int scaledHeight;
	int scaledWidth;

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
	afx_msg void OnConnectivity8();
	afx_msg void OnScalingBilinearinterpolation();
	BYTE bilinear_interpolation(BYTE image[2][2], float EWweight, float NSweight);
	afx_msg void OnScalingBsplineinterpolation();
	BYTE bspline_interpolation(BYTE image[4][4], float EWweight, float NSweight);
};

#ifndef _DEBUG  // debug version in 201611225View.cpp
inline CMy201611225Doc* CMy201611225View::GetDocument() const
   { return reinterpret_cast<CMy201611225Doc*>(m_pDocument); }
#endif

