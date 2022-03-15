#ifndef CX_IMAGE_PROC_HH_
#define CX_IMAGE_PROC_HH_

#include <iostream>
#include <vector>
using namespace std;


struct Border {
        int seq_num;
        int border_type;
};

struct Pixel {
        unsigned char red;
        unsigned char blue;
        unsigned char green;

        Pixel() {
                red = 0;
                green = 0;
                blue = 0;
        }

        Pixel(unsigned char r, unsigned char g, unsigned char b) {
                red = r;
                green = g;
                blue = b;
        }
        void setPixel(unsigned char r, unsigned char g, unsigned char b) {
                red = r;
                green = g;
                blue = b;
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
        static void flipUpDown(IMG2DLib::Mat& image);
        static void flipRightLeft(IMG2DLib::Mat& image);
        static void reversalImgae(IMG2DLib::Mat& image);
        static void DitheringImage(Mat& grayImage, int value);
};

#endif // CX_IMAGE_PROC_HH_