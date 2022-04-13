#ifndef CX_IMAGE_PROC_HH_
#define CX_IMAGE_PROC_HH_

#include <iostream>
#include <vector>
#include<string.h>
using namespace std;


struct Border {
	int seq_num;
	int border_type;
};

struct Pixel {
	unsigned char red;
	unsigned char blue;
	unsigned char green;
	unsigned char alpha;

	Pixel() {
		red = 0;
		green = 0;
		blue = 0;
		alpha = 0;
	}

	Pixel(unsigned char r, unsigned char g, unsigned char b) {
		red = r;
		green = g;
		blue = b;
		alpha = 255;
	}
	void setPixel(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
		red = r;
		green = g;
		blue = b;
		alpha = a;
	}
};

/*
struct TreeNode {
TreeNode *parent;
Border border;
TreeNode *first_child;
TreeNode *next_sibling;

TreeNode(Border b) {
border = b;
}
};
*/

//struct for storing information on the current border, the first child, next sibling, and the parent.
struct Node {
	int parent;
	int first_child;
	int next_sibling;
	Border border;
	Node(int p, int fc, int ns) {
		parent = p;
		first_child = fc;
		next_sibling = ns;
	}
	void reset() {
		parent = -1;
		first_child = -1;
		next_sibling = -1;
	}
};

class  IMG2DLib
{
public:
	IMG2DLib();
	~IMG2DLib();

	struct Point {
		int x;
		int y;

		Point() {
		}

		Point(int r, int c) {
			x = c;
			y = r;
		}

		void setPoint(int r, int c) {
			x = c;
			y = r;
		}

		bool samePoint(Point p) {
			return y == p.y && x == p.x;
		}
	};

	struct Mat {
		unsigned char* imgdata;
		int imageW;
		int imageH;
		int channels;

		Mat() {
			imgdata = NULL;
			imageW = 0;
			imageH = 0;
			channels = 1;
		}

		Mat(unsigned char* data, int w, int h, int c) {
			imgdata = data;
			imageW = w;
			imageH = h;
			channels = c;
		}

		Mat(int w, int h, int c) {
			int dataLen = w * h * c;
			imgdata = (unsigned char*)malloc(dataLen * sizeof(unsigned char));
			memset(imgdata, 0, dataLen);
			imageW = w;
			imageH = h;
			channels = c;
		}

		Mat(int w, int h, int c, unsigned char val) {
			int dataLen = w * h * c;
			imgdata = (unsigned char*)malloc(dataLen * sizeof(unsigned char));
			memset(imgdata, val, dataLen);
			imageW = w;
			imageH = h;
			channels = c;
		}

		Mat(int w, int h, int c, unsigned char* img_data) {
			int dataLen = w * h * c;
			imgdata = (unsigned char*)malloc(dataLen * sizeof(unsigned char));
			memcpy(imgdata, img_data, dataLen);
			imageW = w;
			imageH = h;
			channels = c;
		}

		void release()
		{
			if (imgdata)
			{
				free(imgdata);
				imgdata = NULL;
				imageW = 0;
				imageH = 0;
				channels = 1;
			}
		}
		~Mat()
		{
		}
	};

public:
	static vector<vector<Point>> getContours(Mat inputImage);
	static void colorToGray(Mat& colorImage);
	static void colorToGray(Mat& inputImage, int contrastValue, int brightValue, int setWhiteVal);
	static void GrayToBinary(Mat& grayImage, int value);
	static void flipUpDown(Mat& image);
	static void flipRightLeft(Mat& image);
	static void reversalImgae(Mat& image);
	static void DitheringImage(Mat& grayImage, int value);
	static void blurImgae(Mat& image, int size);
	static void medianBlurImgae(Mat& image, int size);
	static void medianBlurBinaryImgae(Mat& image, int size);
};

class MatPotrace
{
public:
	struct PointF {
		float x;
		float y;

		PointF() {
			x = 0.;
			y = 0.;
		}

		PointF(float x_, float y_) {
			x = x_;
			y = y_;
		}

		bool samePoint(PointF p) {
			return y == p.y && x == p.x;
		}

		PointF operator+(const PointF& p) const { return PointF(x + p.x, y + p.y); }
		PointF operator-(const PointF& p) const { return PointF(x - p.x, y - p.y); }
		PointF operator*(const double f) const { return PointF(x * f, y * f); }
		PointF operator/(const double f) const { return PointF(x / f, y / f); }
	};

	typedef std::vector<PointF> PolygonF;

	struct Polygon
	{
		PolygonF boundary;
		std::vector<PolygonF> holes;
	};

	MatPotrace();

	bool trace(const IMG2DLib::Mat& image);

	std::vector<Polygon> polygons() const;

	void setAlphaMax(double alphaMax);
	void setTurdSize(int turdSize);
	void setCurveTolerance(double tolerance);
	void setThreshold(int threshold);
	void setBezierPrecision(int precision);

private:
	double m_alphaMax;
	int m_turdSize;
	double m_curveTolerance;
	int m_threshold;
	int m_bezierPrecision;


	std::vector<Polygon> m_meshDefs;
};

#endif