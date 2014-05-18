#include "photoeffects.hpp"

using namespace cv;
int filmGrain(InputArray src, OutputArray dst, int grainValue, int seed)
{
    CV_Assert(!src.empty());
    CV_Assert(src.type() == CV_8UC1 || src.type() == CV_8UC3);

    Mat image=src.getMat();
    RNG rng=RNG(seed);
    Mat noise;
    noise.create(image.size(), CV_8UC1);
    rng.fill(noise, RNG::UNIFORM, 0, grainValue);
    dst.create(src.size(), src.type());
    Mat dstMat=dst.getMat();
    if(src.type()==CV_8UC3)
    {
        cvtColor(noise, noise, CV_GRAY2RGB);
    }
    dstMat=image+noise;
    return 0;
}
