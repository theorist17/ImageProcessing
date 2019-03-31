
// 201611225View.cpp : implementation of the CMy201611225View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "201611225.h"
#endif

#include "201611225Doc.h"
#include "201611225View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy201611225View

IMPLEMENT_DYNCREATE(CMy201611225View, CView)

BEGIN_MESSAGE_MAP(CMy201611225View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_IMAGELOAD_BMP, &CMy201611225View::OnImageloadBmp)
	ON_COMMAND(ID_TRANSFORM_RGBTOHSI, &CMy201611225View::OnTransformRgbtohsi)
	ON_COMMAND(ID_IMAGELOAD_JPEG, &CMy201611225View::OnImageloadJpeg)
END_MESSAGE_MAP()

// CMy201611225View construction/destruction

CMy201611225View::CMy201611225View()
{
	// TODO: add construction code here
	rgbBuffer = nullptr;
}

CMy201611225View::~CMy201611225View()
{
	if (rgbBuffer != nullptr)
	{
		for (int i = 0; i < imgHeight; i++)
			delete[] rgbBuffer[i];
		delete[] rgbBuffer;
	}
}

BOOL CMy201611225View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMy201611225View drawing

void CMy201611225View::OnDraw(CDC* pDC)
{
	CMy201611225Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// draw image to the view
	if (rgbBuffer != NULL)
	{
		for (int i = 0; i < imgHeight; i++)
		{
			for (int j = 0; j < imgWidth; j++)
			{
				POINT p; // setting position of output pixel
				p.x = j;
				p.y = i;

				pDC->SetPixel(p, RGB(rgbBuffer[i][j].rgbRed, rgbBuffer[i][j].rgbGreen, rgbBuffer[i][j].rgbBlue));

				if (viewType == 2)
				{
					p.x = j + imgWidth + 10;
					p.y = i;
					pDC->SetPixel(p, RGB(hueBuffer[i][j], hueBuffer[i][j], hueBuffer[i][j]));

					p.x = j + imgWidth + 10;
					p.y = i + imgWidth + 10;
					pDC->SetPixel(p, RGB(satuBuffer[i][j], satuBuffer[i][j], satuBuffer[i][j]));

					p.x = j;
					p.y = i + imgWidth + 10;
					pDC->SetPixel(p, RGB(intenBuffer[i][j], intenBuffer[i][j], intenBuffer[i][j]));

				}
				
			}
		}
	}



}


// CMy201611225View printing

BOOL CMy201611225View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMy201611225View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMy201611225View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CMy201611225View diagnostics

#ifdef _DEBUG
void CMy201611225View::AssertValid() const
{
	CView::AssertValid();
}

void CMy201611225View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy201611225Doc* CMy201611225View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy201611225Doc)));
	return (CMy201611225Doc*)m_pDocument;
}
#endif //_DEBUG


// CMy201611225View message handlers


void CMy201611225View::OnImageloadBmp()
{
	// get target image file path by opening file dialogue
	CFileDialog dlg(TRUE, ".bmp", NULL, NULL, "Bitmap File (*.bmp)[*.bmp||");
	if (IDOK != dlg.DoModal())
		return;
	CString filename = dlg.GetPathName();
	if (rgbBuffer != NULL) // unallocate memory containing previous image
	{
		for (int i = 0; i < imgHeight; i++)
			delete[] rgbBuffer[i];
		delete[] rgbBuffer;
	}

	// open file and get image information
	CFile file;
	file.Open(filename, CFile::modeRead);
	file.Read(&bmpHeader, sizeof(BITMAPFILEHEADER));
	file.Read(&bmpInfo, sizeof(BITMAPINFOHEADER));
	imgWidth = bmpInfo.biWidth;
	imgHeight = bmpInfo.biHeight;

	// assign image to the 2-dimensional array buffer
	rgbBuffer = new RGBQUAD*[imgHeight];
	for (int i = 0; i < imgHeight; i++)
		rgbBuffer[i] = new RGBQUAD[imgWidth];

	// modular operation to check if the width of image is multiple of 4
	// a BMP file must have the width of 4x bytes
	// calculate if 3*m_width is the multiple of 4, becasue each pixel require 3 bytes (RGB)
	// b4byte is a boolean, which is true when it is the multiple of 4
	// upbyte represent the number of remainder bytes
	bool b4byte = false;
	int upbyte = 0;
	if ((imgWidth * 3) % 4 == 0)
	{
		b4byte = true;
		upbyte = 0;
	}
	else
	{
		b4byte = false;
		upbyte = 4 - (imgWidth * 3) % 4;
	}

	// read pixel data from the file
	BYTE data[3];
	for (int i = 0; i < imgHeight; i++)
	{
		for (int j = 0; j < imgWidth; j++) {
			file.Read(&data, 3);
			rgbBuffer[imgHeight - i - 1][j].rgbBlue = data[0]; // inverse the order of vertical data
			rgbBuffer[imgHeight - i - 1][j].rgbGreen = data[1];
			rgbBuffer[imgHeight - i - 1][j].rgbRed = data[2];
		}

		// if the image width isn't the multiply of 4, read the remaining bytes (trash value)
		if (b4byte == false)
		{
			file.Read(&data, upbyte);
		}
	}

	file.Close();
	Invalidate(TRUE); // invalidate view
}

void CMy201611225View::OnTransformRgbtohsi()
{
	if (rgbBuffer == NULL)
	{
		OnImageloadBmp(); // if empty rgbBuffer, call loading bitmap image
	}

	// assign memory to variables
	hueBuffer = new float*[imgHeight];
	satuBuffer = new float*[imgHeight];
	intenBuffer = new float*[imgHeight];

	for (int i = 0; i < imgHeight; i++)
	{
		hueBuffer[i] = new float[imgWidth];
		satuBuffer[i] = new float[imgWidth];
		intenBuffer[i] = new float[imgWidth];
	}

	// transform RGB to HSI
	for (int i = 0; i < imgHeight; i++)
	{
		for (int j = 0; j < imgWidth; j++)
		{
			float r = rgbBuffer[i][j].rgbRed;
			float g = rgbBuffer[i][j].rgbGreen;
			float b = rgbBuffer[i][j].rgbBlue;

			intenBuffer[i][j] = (r + g + b) / (float)(3 * 255); //intensity
			float total = r + g + b;

			r = r / total; g = g / total; b = b / total;
			satuBuffer[i][j] = 1 - 3 * (r > g ? (g > b ? b : g) : (r > b ? b : r));
			if (r == g&&g == b) {
				hueBuffer[i][j] = 0; satuBuffer[i][j] = 0;
			}
			else
			{
				total = (0.5*(r - g + r - b) / sqrt((r - g)*(r - g) + (r - b)*(g - b)));
				hueBuffer[i][j] = acos((double)total);
				if (b > g) {
					hueBuffer[i][j] = 6.28 - hueBuffer[i][j];
				}
			}

		}
	}

	// normalize the range of output value, setting to [0, 255]
	for (int i = 0; i < imgHeight; i++)
	{
		for (int j = 0; j < imgWidth; j++) {
			hueBuffer[i][j] = hueBuffer[i][j] * 255 / (3.14 * 2);
			satuBuffer[i][j] = satuBuffer[i][j] * 255;
			intenBuffer[i][j] = intenBuffer[i][j] * 255;
		}
	}

	viewType = 2;
	Invalidate(FALSE);
}

void CMy201611225View::OnImageloadJpeg()
{
	CFileDialog dlg(TRUE, ".jpg", NULL, NULL, "Jpeg File (*.jpg)|*.jpg||");
	if (IDOK != dlg.DoModal())
		return;
	CString filename = dlg.GetPathName();
	if (rgbBuffer != NULL) // unallocate memory containing previous image
	{
		for (int i = 0; i < imgHeight; i++)
			delete[] rgbBuffer[i];
		delete[] rgbBuffer;
	}

	FILE* fp = fopen(filename, "rb");
	BITMAPINFOHEADER pbh;
	UINT w, h;
	BYTE* pbuf = LoadJpegFromOpenFile(fp, &pbh, &w, &h);
	imgWidth = (int)w;
	imgHeight = (int)h;

	// assign image to the 2-dimensional array buffer
	rgbBuffer = new RGBQUAD*[imgHeight];
	for (int i = 0; i < imgHeight; i++)
		rgbBuffer[i] = new RGBQUAD[imgWidth];

	int dw = WIDTHBYTES(imgWidth * 24);
	for (int i = 0; i < imgHeight; i++)
	{
		for (int j = 0; j < imgWidth; j++)
		{
			rgbBuffer[imgHeight - i - 1][j].rgbBlue = pbuf[i*dw + j * 3 + 0];
			rgbBuffer[imgHeight - i - 1][j].rgbGreen = pbuf[i*dw + j * 3 + 1];
			rgbBuffer[imgHeight - i - 1][j].rgbRed = pbuf[i*dw + j * 3 + 2];

		}
	}
	delete[] pbuf;
	fclose(fp);
	Invalidate(TRUE);

}


BYTE* CMy201611225View::LoadJpegFromOpenFile(FILE* fp, BITMAPINFOHEADER* pbh, UINT* pWidth, UINT* pHeight)
{
	// Get JPEG info from file
	if (pWidth == NULL || pHeight == NULL)
		return NULL;
	BYTE* tmp = JpegFile::OpenFileToRGB(fp, pWidth, pHeight);
	if (!tmp)
		return NULL;
	JpegFile::BGRFromRGB(tmp, *pWidth, *pHeight);

	UINT dw;
	BYTE *pbuf = JpegFile::MakeDwordAlignedBuf(tmp, *pWidth, *pHeight, &dw);
	delete[] tmp;

	if (!pbuf)
		return NULL;
	JpegFile::VertFlipBuf(pbuf, dw, *pHeight);
	pbh->biSize = sizeof(BITMAPINFOHEADER);
	pbh->biWidth = *pWidth;
	pbh->biHeight = *pHeight;
	pbh->biPlanes = 1;
	pbh->biBitCount = 24;
	pbh->biCompression = BI_RGB;
	pbh->biSizeImage = 0;
	pbh->biXPelsPerMeter = 0;
	pbh->biYPelsPerMeter = 0;
	pbh->biClrUsed = 0;
	pbh->biClrImportant = 0;
	return pbuf;
}
