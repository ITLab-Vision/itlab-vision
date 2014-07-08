#include "photoeffects.hpp"
#include <opencv2/core/internal.hpp>
using namespace cv;

class FadeColorInvoker
{
public:
    FadeColorInvoker(Mat& src, Mat& dst, int A,int B,int C,int maxDistance)
        : src_(src),
          dst_(dst),
          A_(A),B_(B),C_(C),maxDistance(maxDistance),
          cols_(dst.cols) {}

    void operator()(const BlockedRange& rowsRange) const
    {
        Mat srcStripe = src_.rowRange(rowsRange.begin(), rowsRange.end());
        Mat dstStripe = dst_.rowRange(rowsRange.begin(), rowsRange.end());
        int numRows = srcStripe.rows;
        int startRowNum=rowsRange.begin();
        int nChannels=src_.channels();
        for (int i = 0; i < numRows; i++)
        {
            int distance=A_*(startRowNum+i)-B_+C_;
            uchar* dstRow = (uchar*)dstStripe.row(i).data;
            uchar* srcRow = (uchar*)srcStripe.row(i).data;
            for (int j = 0; j < cols_; j ++)
            {
                distance+=B_;
                //change pixels only in the direction of the perpendicular
                if(distance>0)
                {
                    for(int n=0;n<nChannels;n++)
                    {
                        int channelValue=*(srcRow+n);
                        channelValue*=(maxDistance-distance);
                        channelValue+=255*distance;
                        channelValue/=maxDistance;
                        *(dstRow+n)=channelValue;
                    }
                }
                else
                {
                    for(int n=0;n<nChannels;n++)
                    {
                        *(dstRow+n)=*(srcRow+n);
                    }
                }
            srcRow+=nChannels;
            dstRow+=nChannels;
            }

        }
    }

private:
    Mat& src_;
    Mat& dst_;
    int cols_;
    //line
    int A_,B_,C_;
    int maxDistance;
    FadeColorInvoker& operator=(const FadeColorInvoker&);
};
Point findFarthestPoint(Point vector, Mat& image)
{
    int a,b;
    if(vector.x<=0)
    {
        a=0;
    }
    else
    {
        a=1;
    }

    if(vector.y<=0)
    {
        b=0;
    }
    else
    {
        b=1;
    }

    return Point(a*image.cols, b*image.rows);
}

int fadeColor(InputArray src, OutputArray dst,
              Point startPoint, Point endPoint)
{

    CV_Assert(!src.empty());
    Mat image=src.getMat();
    CV_Assert(image.type() == CV_8UC1 || image.type() == CV_8UC3);
    CV_Assert(startPoint.x>=0 && startPoint.x<image.cols);
    CV_Assert(endPoint.x>=0 && endPoint.x<image.cols);
    CV_Assert(startPoint.y>=0 && startPoint.y<image.rows);
    CV_Assert(endPoint.y>=0 && endPoint.y<image.rows);
    CV_Assert(startPoint!=endPoint);
    // perpendicular to the line
    Point perpendicular;
    perpendicular.x=endPoint.x-startPoint.x;
    perpendicular.y=endPoint.y-startPoint.y;
    //line equation: A*x+By+C=0

    int A=perpendicular.y;
    int B=perpendicular.x;
    int C=-startPoint.y*A-B*startPoint.x;
    //find the most distant point from the line
    Point farthestPoint=findFarthestPoint(perpendicular, image);

    int maxDistance=abs(A*farthestPoint.y+B*farthestPoint.x+C);
    dst.create(image.size(),image.type());
    Mat dstMat;
    dstMat=dst.getMat();
    //image.copyTo(dstMat);
    parallel_for(BlockedRange(0, image.rows), FadeColorInvoker(image,dstMat, A,B,C,maxDistance));
    //dstMat.copyTo(dst);
    return 0;
}
