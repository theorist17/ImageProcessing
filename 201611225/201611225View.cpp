
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
	ON_COMMAND(ID_TRANSFORM_HISTOGRAMEQUALIZATION, &CMy201611225View::OnTransformHistogramequalization)
	ON_COMMAND(ID_GAUSSIANFILTERING_3, &CMy201611225View::OnGaussianfiltering3)
	ON_COMMAND(ID_MEDIANFILTERING_3, &CMy201611225View::OnMedianfiltering3)
	ON_COMMAND(ID_AVERAGEFILTERING_3, &CMy201611225View::OnAveragefiltering3)
	ON_COMMAND(ID_GAUSSIANFILTERING_5, &CMy201611225View::OnGaussianfiltering5)
	ON_COMMAND(ID_MEDIANFILTERING_5, &CMy201611225View::OnMedianfiltering5)
	ON_COMMAND(ID_AVERAGEFILTERING_5, &CMy201611225View::OnAveragefiltering5)
	ON_COMMAND(ID_GAUSSIANFILTERING_7, &CMy201611225View::OnGaussianfiltering7)
	ON_COMMAND(ID_MEDIANFILTERING_7, &CMy201611225View::OnMedianfiltering7)
	ON_COMMAND(ID_AVERAGEFILTERING_7, &CMy201611225View::OnAveragefiltering7)
	ON_COMMAND(ID_IMAGELOAD_AVI, &CMy201611225View::OnImageloadAvi)
	ON_COMMAND(ID_MOTION_3SS, &CMy201611225View::OnMotion3ss)
END_MESSAGE_MAP()

// CMy201611225View construction/destruction

CMy201611225View::CMy201611225View()
{
	// TODO: add construction code here
	rgbBuffer = nullptr;
	intensity = nullptr;
	intenNext = nullptr;
}

CMy201611225View::~CMy201611225View()
{
	if (rgbBuffer != nullptr)  
	{
		for (int i = 0; i < imgHeight; i++)
			delete[] rgbBuffer[i];
		delete[] rgbBuffer;
	}

	if (intensity != nullptr)
	{
		for (int i = 0; i < imgHeight; i++)
			delete[] intensity[i];
		delete[] intensity;
	}

	if (intenNext != nullptr)
	{
		for (int i = 0; i < imgHeight; i++)
			delete[] intenNext[i];
		delete[] intenNext;
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
	
	if (viewType == 4) {
		//FILE* fp = fopen("C:\\Users\\theorist\\Documents\\Visual Studio 2015\\Projects\\201611225\\Fig0503 (original_pattern).jpg", "rb");
		//BITMAPINFOHEADER pbh;
		//UINT w, h;
		//BYTE* pbuf = LoadJpegFromOpenFile(fp, &pbh, &w, &h);
		//imgWidth = (int)w;
		//imgHeight = (int)h;

		//// assign image to the 2-dimensional array buffer
		//RGBQUAD** rgbBuff;
		//rgbBuff = new RGBQUAD*[imgHeight];
		//for (int i = 0; i < imgHeight; i++)
		//	rgbBuff[i] = new RGBQUAD[imgWidth];

		//int dw = WIDTHBYTES(imgWidth * 24);
		//for (int i = 0; i < imgHeight; i++)
		//{
		//	for (int j = 0; j < imgWidth; j++)
		//	{
		//		rgbBuff[imgHeight - i - 1][j].rgbBlue = pbuf[i*dw + j * 3 + 0];
		//		rgbBuff[imgHeight - i - 1][j].rgbGreen = pbuf[i*dw + j * 3 + 1];
		//		rgbBuff[imgHeight - i - 1][j].rgbRed = pbuf[i*dw + j * 3 + 2];
		//	}
		//}
		//for (int i = 0; i < imgHeight; i++)
		//{
		//	for (int j = 0; j < imgWidth; j++)
		//	{
		//		intensity[i][j] = (rgbBuff[i][j].rgbBlue + rgbBuff[i][j].rgbGreen + rgbBuff[i][j].rgbRed) / 3;
		//	}
		//}
		//delete[] pbuf;
		//fclose(fp);
	}
	// draw image to the view

	int diff = 0;
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
				else if (viewType == 3) 
				{
					p.x = j + imgWidth + 10;
					p.y = i;
					pDC->SetPixel(p, RGB(intensity[i][j], intensity[i][j], intensity[i][j]));

				}
				else if (viewType == 4)
				{
					p.x = j + imgWidth + 10;
					p.y = i;
					pDC->SetPixel(p, RGB(intenNext[i][j], intenNext[i][j], intenNext[i][j]));
/*
					p.x = j + 2 * imgWidth + 20;
					p.y = i;
					pDC->SetPixel(p, RGB(intensity[i][j], intensity[i][j], intensity[i][j]));*/

					p.x = j + 2 * imgWidth + 20;
					p.y = i;
					pDC->SetPixel(p, RGB(intensity[i][j] - intenNext[i][j], intensity[i][j] - intenNext[i][j], intensity[i][j] - intenNext[i][j]));
					diff += (intensity[i][j] - intenNext[i][j]);
				}
			}
		}
	}

	
	if (viewType == 4 && diff != 0) {
		diff = diff;
	}
	if (viewType == 3) {
		//plot histogram
		
		double maxHist = 0.0, maxEqual = 0.0, maxSum = 0.0, maxEquisum = 0.0;
		for (int i = 0; i < 256; i++) {
			if (intenHisto[i] > maxHist)
				maxHist = intenHisto[i];
			if (intenEqual[i] > maxEqual)
				maxEqual = intenEqual[i];
			if (intenSum[i] > maxSum)
				maxSum = intenSum[i];
			if (intenEquisum[i] > maxEquisum)
				maxEquisum = intenEquisum[i];
		}
		for (int i = 0; i < 256; i++)
		{
			pDC->MoveTo(imgWidth*2 + 20 + i, 100);
			pDC->LineTo(imgWidth * 2 + 20 + i, 100 - intenHisto[i] / maxHist * 100);
		}
		pDC->MoveTo(imgWidth * 2 + 20, 100);
		pDC->LineTo(imgWidth * 2 + 20 + 256, 100);
		for (int i = 0; i < 256; i++)
		{
			pDC->MoveTo(imgWidth * 2 + 20 + i, 210);
			pDC->LineTo(imgWidth * 2 + 20 + i, 210 - intenEqual[i] / maxEqual * 100);
		}
		pDC->MoveTo(imgWidth * 2 + 20, 210);
		pDC->LineTo(imgWidth * 2 + 20 + 256, 210);
		for (int i = 0; i < 256; i++)
		{
			pDC->MoveTo(imgWidth * 2 + 20 + i, 320);
			pDC->LineTo(imgWidth * 2 + 20 + i, 320 - intenSum[i] / maxSum * 100);
		}
		pDC->MoveTo(imgWidth * 2 + 20, 320);
		pDC->LineTo(imgWidth * 2 + 20 + 256, 320);
		for (int i = 0; i < 256; i++)
		{
			pDC->MoveTo(imgWidth * 2 + 20 + i, 430);
			pDC->LineTo(imgWidth * 2 + 20 + i, 430 - intenEquisum[i] / maxEquisum * 100);
		}
		pDC->MoveTo(imgWidth * 2 + 20, 430);
		pDC->LineTo(imgWidth * 2 + 20 + 256, 430);
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
	if (intensity != NULL)
	{
		for (int i = 0; i < imgHeight; i++)
			delete[] intensity[i];
		delete[] intensity;
	}

	if (intenNext != NULL)
	{
		for (int i = 0; i < imgHeight; i++)
			delete[] intenNext[i];
		delete[] intenNext;
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
	viewType = 1;
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

			r = r / total; 
			g = g / total; 
			b = b / total;
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
	if (intensity != NULL)
	{
		for (int i = 0; i < imgHeight; i++)
			delete[] intensity[i];
		delete[] intensity;
	}

	if (intenNext != NULL)
	{
		for (int i = 0; i < imgHeight; i++)
			delete[] intenNext[i];
		delete[] intenNext;
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
	viewType = 1;
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


void CMy201611225View::OnTransformHistogramequalization()
{

	if (intensity != NULL)
	{
		for (int i = 0; i < imgHeight; i++)
			delete[] intensity[i];
		delete[] intensity;
	}

	intensity = new int*[imgHeight];
	for (int i = 0; i < imgWidth; i++)
	{
		intensity[i] = new int[imgWidth];
	}

	
	// intensity histogram
	for (int i = 0; i < 256; i++)
	{
		intenHisto[i] = 0;
		intenEqual[i] = 0;
		intenSum[i] = 0;
	}
	for (int i = 0; i < imgHeight; i++) 
	{
		for (int j = 0; j < imgWidth; j++) 
		{
			intensity[i][j] = (rgbBuffer[i][j].rgbBlue + rgbBuffer[i][j].rgbGreen + rgbBuffer[i][j].rgbRed)/3;
			intenHisto[intensity[i][j]]++;
		}
	}

	// histogram equalization

	int sum = 0;
	double scale_factor = 255.0 / (imgHeight*imgWidth);
	for (int i = 0; i < 256; i++)
	{
		sum += intenHisto[i];
		intenSum[i] = (sum * scale_factor) + 0.5;
	}

	for (int i = 0; i < imgHeight; i++)
	{
		for (int j = 0; j < imgWidth; j++)
		{
			intensity[i][j] = intenSum[intensity[i][j]];
			intenEqual[intensity[i][j]]++;
		}
	}

	sum = 0;
	for (int i = 0; i < 256; i++)
	{
		sum += intenEqual[i];
		intenEquisum[i] = (sum * scale_factor) + 0.5;
	}

	viewType = 3;
	Invalidate(TRUE);

}

void CMy201611225View::ReadIntensity()
{
	intensity = new int*[imgHeight];
	for (int i = 0; i < imgWidth; i++)
	{
		intensity[i] = new int[imgWidth];
	}
	intenNext = new int*[imgHeight];
	for (int i = 0; i < imgWidth; i++)
	{
		intenNext[i] = new int[imgWidth];
	}

	for (int i = 0; i < imgHeight; i++)
	{
		for (int j = 0; j < imgWidth; j++)
		{
			intensity[i][j] = (rgbBuffer[i][j].rgbBlue + rgbBuffer[i][j].rgbGreen + rgbBuffer[i][j].rgbRed) / 3;
			intenNext[i][j] = 0;
		}
	}
}

void CMy201611225View::OnGaussianfiltering3()
{
	ReadIntensity();

	for (int i = 1; i < imgHeight - 1; i++)
	{
		for (int j = 1; j < imgWidth - 1; j++)
		{
			intenNext[i][j] =
				intensity[i - 1][j - 1] * (1.0/16) +
				intensity[i - 1][j] * (1.0 / 8) +
				intensity[i - 1][j + 1] * (1.0 / 16) +
				intensity[i][j - 1] * (1.0 / 8) +
				intensity[i][j] * (1.0 / 4) +
				intensity[i][j + 1] * (1.0 / 8) +
				intensity[i + 1][j - 1] * (1.0 / 16) +
				intensity[i + 1][j] * (1.0 / 8) +
				intensity[i + 1][j + 1] * (1.0 / 16);
		}
	}

	viewType = 4;
	Invalidate(TRUE);
}


void CMy201611225View::OnMedianfiltering3()
{
	ReadIntensity();

	for (int i = 1; i < imgHeight - 1; i++)
	{
		for (int j = 1; j < imgWidth - 1; j++)
		{
			int arr[9] = { intensity[i-1][j-1], intensity[i-1][j], intensity[i-1][j+1],
						intensity[i][j-1], intensity[i][j], intensity[i][j+1],
						intensity[i+1][j-1], intensity[i+1][j], intensity[i+1][j+1] };
			std::sort(arr, arr + 9);
			intenNext[i][j] = arr[4];
		}
	}

	viewType = 4;
	Invalidate(TRUE);
}


void CMy201611225View::OnAveragefiltering3()
{
	ReadIntensity();

	for (int i = 1; i < imgHeight - 1; i++)
	{
		for (int j = 1; j < imgWidth - 1; j++)
		{
			intenNext[i][j] =
				( intensity[i - 1][j - 1] +
				intensity[i - 1][j] +
				intensity[i - 1][j + 1] +
				intensity[i][j - 1] +
				intensity[i][j] +
				intensity[i][j + 1] +
				intensity[i + 1][j - 1] +
				intensity[i + 1][j] +
				intensity[i + 1][j + 1] )/9;
		}
	}

	viewType = 4;
	Invalidate(TRUE);
}


void CMy201611225View::OnGaussianfiltering5()
{
	ReadIntensity();

	for (int i = 2; i < imgHeight - 2; i++)
	{
		for (int j = 2; j < imgWidth - 2; j++)
		{
			intenNext[i][j] =
				(intensity[i - 2][j - 2] * 1+
				intensity[i - 2][j - 1] * 4+
				intensity[i - 2][j] * 7+
				intensity[i - 2][j + 1] *4 +
				intensity[i - 2][j + 2] * 1+
				intensity[i - 1][j - 2] *4+
				intensity[i - 1][j - 1] *16+
				intensity[i - 1][j] *26+
				intensity[i - 1][j + 1]*16 +
				intensity[i - 1][j + 2]*4 +
				intensity[i][j - 2]*7 +
				intensity[i][j - 1]*26 +
				intensity[i][j] *41+
				intensity[i][j + 1]*26 +
				intensity[i][j + 2]*7 +
				intensity[i + 1][j - 2] *4+
				intensity[i + 1][j - 1] *16+
				intensity[i + 1][j] *26+
				intensity[i + 1][j + 1]*16 +
				intensity[i + 1][j + 2] *4+
				intensity[i + 2][j - 2] *1+
				intensity[i + 2][j - 1] *4+
				intensity[i + 2][j]*7 +
				intensity[i + 2][j + 1]*4 +
				intensity[i + 2][j + 2]*1)/273.0;
		}
	}

	viewType = 4;
	Invalidate(TRUE);
}


void CMy201611225View::OnMedianfiltering5()
{
	ReadIntensity();

	for (int i = 2; i < imgHeight - 2; i++)
	{
		for (int j = 2; j < imgWidth - 2; j++)
		{
			int arr[25] = { intensity[i - 2][j - 2],
				intensity[i - 2][j - 1],
				intensity[i - 2][j],
				intensity[i - 2][j + 1],
				intensity[i - 2][j + 2],
				intensity[i - 1][j - 2],
				intensity[i - 1][j - 1],
				intensity[i - 1][j],
				intensity[i - 1][j + 1],
				intensity[i - 1][j + 2],
				intensity[i][j - 2],
				intensity[i][j - 1],
				intensity[i][j],
				intensity[i][j + 1],
				intensity[i][j + 2],
				intensity[i + 1][j - 2],
				intensity[i + 1][j - 1],
				intensity[i + 1][j],
				intensity[i + 1][j + 1],
				intensity[i + 1][j + 2],
				intensity[i + 2][j - 2],
				intensity[i + 2][j - 1],
				intensity[i + 2][j],
				intensity[i + 2][j + 1],
				intensity[i + 2][j + 2] };
			std::sort(arr, arr + 25);
			intenNext[i][j] = arr[12];
		}
	}

	viewType = 4;
	Invalidate(TRUE);
}


void CMy201611225View::OnAveragefiltering5()
{
	ReadIntensity();

	for (int i = 2; i < imgHeight - 2; i++)
	{
		for (int j = 2; j < imgWidth - 2; j++)
		{
			intenNext[i][j] =
				(intensity[i - 2][j - 2] +
					intensity[i - 2][j - 1] +
					intensity[i - 2][j] +
					intensity[i - 2][j + 1] +
					intensity[i - 2][j + 2] +
					intensity[i - 1][j - 2] +
					intensity[i - 1][j - 1] +
					intensity[i - 1][j] +
					intensity[i - 1][j + 1] +
					intensity[i - 1][j + 2] +
					intensity[i][j - 2] +
					intensity[i][j - 1] +
					intensity[i][j] +
					intensity[i][j + 1] +
					intensity[i][j + 2] +
					intensity[i + 1][j - 2] +
					intensity[i + 1][j - 1] +
					intensity[i + 1][j] +
					intensity[i + 1][j + 1] +
					intensity[i + 1][j + 2] +
					intensity[i + 2][j - 2] +
					intensity[i + 2][j - 1] +
					intensity[i + 2][j] +
					intensity[i + 2][j + 1] +
					intensity[i + 2][j + 2]) / 25.0;
		}
	}

	viewType = 4;
	Invalidate(TRUE);
}


void CMy201611225View::OnGaussianfiltering7()
{
	ReadIntensity();

	for (int i = 3; i < imgHeight - 3; i++)
	{
		for (int j = 3; j < imgWidth - 3; j++)
		{
			intenNext[i][j] =
				(
					intensity[i - 3][j - 3] * 0+
					intensity[i - 3][j - 2] * 0+
					intensity[i - 3][j - 1] *1+
					intensity[i - 3][j] *2+
					intensity[i - 3][j + 1] *1+
					intensity[i - 3][j + 2] *0+
					intensity[i - 3][j + 3] *0+
					intensity[i - 2][j - 3] *0+
					intensity[i - 2][j - 2] *3+
					intensity[i - 2][j - 1] *13+
					intensity[i - 2][j] *22+
					intensity[i - 2][j + 1] *13+
					intensity[i - 2][j + 2] *3+
					intensity[i - 2][j + 3] *0+
					intensity[i - 1][j - 3] *1+
					intensity[i - 1][j - 2] *13+
					intensity[i - 1][j - 1] *59+
					intensity[i - 1][j] *97+
					intensity[i - 1][j + 1] *59+
					intensity[i - 1][j + 2] *13+
					intensity[i - 1][j + 3] *1+
					intensity[i][j - 3] *2+
					intensity[i][j - 2] *22+
					intensity[i][j - 1] *97+
					intensity[i][j] *159+
					intensity[i][j + 1] *97+
					intensity[i][j + 2] *22+
					intensity[i][j + 3] *2+
					intensity[i + 1][j - 3] *1+
					intensity[i + 1][j - 2] *13+
					intensity[i + 1][j - 1] *59+
					intensity[i + 1][j] *97+
					intensity[i + 1][j + 1] *59+
					intensity[i + 1][j + 2] *13+
					intensity[i + 1][j + 3] *1+
					intensity[i + 2][j - 3] *0+
					intensity[i + 2][j - 2] *3+
					intensity[i + 2][j - 1] *13+
					intensity[i + 2][j] *22+
					intensity[i + 2][j + 1] *13+
					intensity[i + 2][j + 2] *3+
					intensity[i + 2][j + 3] *0+
					intensity[i + 3][j - 3] *0+
					intensity[i + 3][j - 2] *0+
					intensity[i + 3][j - 1] *1+
					intensity[i + 3][j] *2+
					intensity[i + 3][j + 1] *1+
					intensity[i + 3][j + 2] *0+
					intensity[i + 3][j + 3]*0
					)/1003.0;
		}
	}

	viewType = 4;
	Invalidate(TRUE);
}


void CMy201611225View::OnMedianfiltering7()
{
	ReadIntensity();

	for (int i = 3; i < imgHeight - 3; i++)
	{
		for (int j = 3; j < imgWidth - 3; j++)
		{
			int arr[49] = {
				intensity[i - 3][j - 3],
				intensity[i - 3][j - 2],
				intensity[i - 3][j - 1],
				intensity[i - 3][j],
				intensity[i - 3][j + 1],
				intensity[i - 3][j + 2],
				intensity[i - 3][j + 3],
				intensity[i - 2][j - 3],
				intensity[i - 2][j - 2],
				intensity[i - 2][j - 1],
				intensity[i - 2][j],
				intensity[i - 2][j + 1],
				intensity[i - 2][j + 2],
				intensity[i - 2][j + 3],
				intensity[i - 1][j - 3],
				intensity[i - 1][j - 2],
				intensity[i - 1][j - 1],
				intensity[i - 1][j],
				intensity[i - 1][j + 1],
				intensity[i - 1][j + 2],
				intensity[i - 1][j + 3],
				intensity[i][j - 3],
				intensity[i][j - 2],
				intensity[i][j - 1],
				intensity[i][j],
				intensity[i][j + 1],
				intensity[i][j + 2],
				intensity[i][j + 3],
				intensity[i + 1][j - 3],
				intensity[i + 1][j - 2],
				intensity[i + 1][j - 1],
				intensity[i + 1][j],
				intensity[i + 1][j + 1],
				intensity[i + 1][j + 2],
				intensity[i + 1][j + 3],
				intensity[i + 2][j - 3],
				intensity[i + 2][j - 2],
				intensity[i + 2][j - 1],
				intensity[i + 2][j],
				intensity[i + 2][j + 1],
				intensity[i + 2][j + 2],
				intensity[i + 2][j + 3],
				intensity[i + 3][j - 3],
				intensity[i + 3][j - 2],
				intensity[i + 3][j - 1],
				intensity[i + 3][j],
				intensity[i + 3][j + 1],
				intensity[i + 3][j + 2],
				intensity[i + 3][j + 3]
			};
			
			std::sort(arr, arr + 49);
			intenNext[i][j] = arr[24];
		}
	}

	viewType = 4;
	Invalidate(TRUE);
}


void CMy201611225View::OnAveragefiltering7()
{
	ReadIntensity();

	for (int i = 3; i < imgHeight - 3; i++)
	{
		for (int j = 3; j < imgWidth - 3; j++)
		{
			intenNext[i][j] =
				(
					intensity[i - 3][j - 3] +
					intensity[i - 3][j - 2] +
					intensity[i - 3][j - 1] +
					intensity[i - 3][j] +
					intensity[i - 3][j + 1] +
					intensity[i - 3][j + 2] +
					intensity[i - 3][j + 3] +
					intensity[i - 2][j - 3] +
					intensity[i - 2][j - 2] +
					intensity[i - 2][j - 1] +
					intensity[i - 2][j] +
					intensity[i - 2][j + 1] +
					intensity[i - 2][j + 2] +
					intensity[i - 2][j + 3] +
					intensity[i - 1][j - 3] +
					intensity[i - 1][j - 2] +
					intensity[i - 1][j - 1] +
					intensity[i - 1][j] +
					intensity[i - 1][j + 1] +
					intensity[i - 1][j + 2] +
					intensity[i - 1][j + 3] +
					intensity[i][j - 3] +
					intensity[i][j - 2] +
					intensity[i][j - 1] +
					intensity[i][j] +
					intensity[i][j + 1] +
					intensity[i][j + 2] +
					intensity[i][j + 3] +
					intensity[i + 1][j - 3] +
					intensity[i + 1][j - 2] +
					intensity[i + 1][j - 1] +
					intensity[i + 1][j] +
					intensity[i + 1][j + 1] +
					intensity[i + 1][j + 2] +
					intensity[i + 1][j + 3] +
					intensity[i + 2][j - 3] +
					intensity[i + 2][j - 2] +
					intensity[i + 2][j - 1] +
					intensity[i + 2][j] +
					intensity[i + 2][j + 1] +
					intensity[i + 2][j + 2] +
					intensity[i + 2][j + 3] +
					intensity[i + 3][j - 3]+
					intensity[i + 3][j - 2]+
					intensity[i + 3][j - 1]+
					intensity[i + 3][j]+
					intensity[i + 3][j + 1]+
					intensity[i + 3][j + 2]+
					intensity[i + 3][j + 3]
					) / 49.0;
		}
	}

	viewType = 4;
	Invalidate(TRUE);
}

void CMy201611225View::FilterCreation(double GKernel[][5])
{
	// intialising standard deviation to 1.0 
	double sigma = 1.0;
	double r, s = 2.0 * sigma * sigma;

	// sum is for normalization 
	double sum = 0.0;

	// generating 5x5 kernel 
	for (int x = -2; x <= 2; x++) {
		for (int y = -2; y <= 2; y++) {
			r = sqrt(x * x + y * y);
			GKernel[x + 2][y + 2] = (exp(-(r * r) / s)) / (M_PI * s);
			sum += GKernel[x + 2][y + 2];
		}
	}

	// normalising the Kernel 
	for (int i = 0; i < 5; ++i)
		for (int j = 0; j < 5; ++j)
			GKernel[i][j] /= sum;

	/*double GKernel[5][5];
	FilterCreation(GKernel);

	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < 5; ++j)
			cout << GKernel[i][j] << "\t";
		cout << endl;
	}*/
}


void CMy201611225View::OnImageloadAvi()
{
	// Pop up dialog to select avi file
	CFileDialog dlg(TRUE, ".avi", NULL, NULL, "AVI File (*.avi)|*.avi||");
	if (IDOK != dlg.DoModal())
		return;

	// Get file path
	CString cfilename = dlg.GetPathName();
	CT2CA strAtl(cfilename);
	String filename(strAtl);

	// Load avi file
	cv::VideoCapture Capture;
	Capture.open(filename); 

	// Guard if file error
	if (!Capture.isOpened())
		AfxMessageBox("Error Video");

	for (;;)
	{
		// Read each frame
		Mat frame;
		Capture >> frame;

		// End loop if no more frame
		if (frame.data == nullptr)
			break;

		// Create window to output frame
		imshow("video", frame);
		
		// Wait for 30ms, break if key interrupt
		if (waitKey(30) >= 0)
			break;
	}

	AfxMessageBox("Completed");

}


void CMy201611225View::OnMotion3ss()
{
	// Pop up dialog to select avi file
	CFileDialog dlg(TRUE, ".avi", NULL, NULL, "AVI File (*.avi)|*.avi||");
	if (IDOK != dlg.DoModal())
		return;

	// Get file path
	CString cfilename = dlg.GetPathName();
	CT2CA strAtl(cfilename);
	String filename(strAtl);

	// Load avi file
	cv::VideoCapture Capture;
	Capture.open(filename);

	// Guard if file error
	if (!Capture.isOpened())
		AfxMessageBox("Error Video");

	Mat curr, prev, show, cout, pout;
	Capture >> curr;
	int block_rows = curr.rows / BLOCK_SIZE;
	int block_cols = curr.cols / BLOCK_SIZE;
	curr.copyTo(prev);

	// Coordinate of block to track
	int tbx = block_rows/2, tby = 0, tbdone = 0;

	for (int frame = 0; ; frame++)
	{
		// End loop if no more frame
		if (curr.data == nullptr)
			break;

		if (frame % FRAME_INTERVAL == 0) {
			// Initialize matrix
			curr.copyTo(show);
			//curr.copyTo(cout);
			//curr.copyTo(pout);
			tbdone = 0;

			// Three step search
			for (int y = 0; y < block_rows; y++) {
				for (int x = 0; x < block_cols; x++) {

					// Coordinate of center pixel (tail)
					int Tx = x * BLOCK_SIZE + BLOCK_SIZE / 2;
					int Ty = y * BLOCK_SIZE + BLOCK_SIZE / 2;

					// Find best dx, dy
					int bestdx = 0, bestdy = 0;
					Mat diff;
					Rect block(x * BLOCK_SIZE, y * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE);
					cv::absdiff(curr(block), prev(block), diff);
					double minSAD = cv::sum(diff)[0];
					for (int step = 1, w = WINDOW_SIZE/2; step <= 3; step++, w = w >> 1) {
						int centerdx = bestdx, centerdy = bestdy;
						for (int dy = -w; dy <= w; dy += w) {
							if (minSAD == 0) break;
							for (int dx = -w; dx <= w; dx += w) { 
								if (minSAD == 0) break; // perfect match found
								if (dx == 0 && dy == 0) // center point
									continue;

								// Bound check block coordinates
								int X = y + centerdy + dy;
								int Y = x + centerdx + dx;
								if (Y < 0 || Y >= block_cols || X < 0 || X >= block_rows)
									continue;
								
								// Get block coordinate in search window 
								Rect BLOCK(Y * BLOCK_SIZE, X * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE);
								cv::absdiff(curr(block), prev(BLOCK), diff);
								double SAD = cv::sum(diff)[0]; // Sum of abosulute difference
								if (SAD < minSAD) {
									minSAD = SAD;
									bestdx = centerdx + dx;
									bestdy = centerdy + dy;
								}
							}
						}
					}
					
					// Coordinate of head pixel
					int Hx = Tx + bestdx * (BLOCK_SIZE / WINDOW_SIZE) / 2;
					int Hy = Ty + bestdy * (BLOCK_SIZE / WINDOW_SIZE) / 2;

					// Draw grid of motion field
					cv::line(show, CvPoint(Tx, Ty), CvPoint(Hx, Hy), CvScalar(0, 0, 255, 0), 1, 8, 0);
					/*if (bestdx != 0||bestdy!=0) {
						Tx -= BLOCK_SIZE / 2;
						Ty -= BLOCK_SIZE / 2;
						cv::rectangle(cout, CvPoint(Tx, Ty), CvPoint(Tx + BLOCK_SIZE, Ty + BLOCK_SIZE), CvScalar(255, 0, 0, 0), 1, 8, 0);
						cv::rectangle(pout, CvPoint(Tx + bestdx * BLOCK_SIZE, Ty + bestdy * BLOCK_SIZE),
							CvPoint(Tx + (bestdx + 1) * BLOCK_SIZE, Ty + (bestdy+1) * BLOCK_SIZE), CvScalar(0, 0, 255, 0), 1, 8, 0);
						cv::imshow("current", cout);
						cv::imshow("previous", pout);
						curr.copyTo(cout);
						prev.copyTo(pout);

						cv::imshow("Motion field", show);
						cv::waitKey(3000);
					}*/

					// Track coordinate of block
					if (tbx == x && tby == y && tbdone == 0) {
						tbx += bestdx;	tby += bestdy;
						tbdone == 1;
					}
				}
			}

			// Draw circle for block being tracked
			cv::circle(show, CvPoint(tbx* BLOCK_SIZE, tby* BLOCK_SIZE), 8, CvScalar(0, 0, 255, 0), 1, 8, 0);

			// Draw frame by frame 
			cv::imshow("Motion field", show);

			// Save current frame
			curr.copyTo(prev);
		}
		
		// Wait for 30ms, break if key interrupt
		if (waitKey(300) >= 0)
			break;		

		// Read each frame
		Capture >> curr;
	}
	Capture.release();
	cv::destroyAllWindows();
	AfxMessageBox("Completed");
}
