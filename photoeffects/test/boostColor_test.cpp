#include "photoeffects.hpp"
#include "test_utils.hpp"
#include <gtest/gtest.h>

using namespace cv;

TEST(photoeffects, BoostColorTest)
{
    Mat image(10, 10, CV_32FC3), dst;

    image = Mat::zeros(10, 10, CV_32FC3);

    EXPECT_EQ(0, boostColor(image, dst, 0.5f));
}

TEST(photoeffects, BoostColorRegressionTest)
{
    string input = "./testdata/boostColor_test.png";
    string expectedOutput = "./testdata/boostColor_test_result.png";

    Mat image = imread(input, CV_LOAD_IMAGE_COLOR);
    Mat rightDst = imread(expectedOutput, CV_LOAD_IMAGE_COLOR);

    if (image.empty())
        FAIL() << "Can't read " + input + " image";
    if (rightDst.empty())
        FAIL() << "Can't read " + expectedOutput + " image";

    Mat dst;
    EXPECT_EQ(0, boostColor(image, dst, 0.5f));

    Mat diff = abs(rightDst - dst);
    Mat mask = diff.reshape(1) > 1;
    EXPECT_EQ(0, countNonZero(mask));
}

TEST(photoeffects, BoostColorTestBadIntensity)
{
    Mat image(10, 10, CV_32FC3), dst;

    EXPECT_ERROR(CV_StsAssert, boostColor(image, dst, -1.0f));
    EXPECT_ERROR(CV_StsAssert, boostColor(image, dst, 2.0f));
}

TEST(photoeffects, BoostColorTestBadImage)
{
    Mat image(10, 10, CV_8UC1), dst;

    EXPECT_ERROR(CV_StsAssert, boostColor(image, dst, 0.5f));
}
