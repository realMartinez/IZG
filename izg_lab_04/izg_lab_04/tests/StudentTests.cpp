#include <gtest/gtest.h>


#include <Student.h>
#include <Student.cpp> //Extremely dirty trick, DON'T DO THIS EVER!! I was just lazy to create a library out of Student.cpp/h.

void compareMatrices(const osg::Matrix& m1, const osg::Matrix& m2, const std::string& function)
{
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            EXPECT_NEAR(m1(i, j), m2(i, j), 1e-5) << function << ", i = " << i << ", j = " << j;
        }

    }
}

TEST(MatricesTest, getTranslationMatrix)
{
    osg::Vec3d translation(1, 0, 0);

    compareMatrices(getTranslationMatrix(translation), osg::Matrix::translate(translation), "getTranslationMatrix");

    translation = { 0, 1, 0 };
    compareMatrices(getTranslationMatrix(translation), osg::Matrix::translate(translation), "getTranslationMatrix");

    translation = { 0, 0, 1 };
    compareMatrices(getTranslationMatrix(translation), osg::Matrix::translate(translation), "getTranslationMatrix");

    translation = { 0, 10, 1 };
    compareMatrices(getTranslationMatrix(translation), osg::Matrix::translate(translation), "getTranslationMatrix");

    translation = { 15, 0, 1 };
    compareMatrices(getTranslationMatrix(translation), osg::Matrix::translate(translation), "getTranslationMatrix");
}

TEST(MatricesTest, getScaleMatrix)
{
    osg::Vec3d scale(1, 0, 0);

    compareMatrices(getScaleMatrix(scale), osg::Matrix::scale(scale), "getScaleMatrix");

    scale = { 0, 1, 0 };
    compareMatrices(getScaleMatrix(scale), osg::Matrix::scale(scale), "getScaleMatrix");

    scale = { 0, 0, 1 };
    compareMatrices(getScaleMatrix(scale), osg::Matrix::scale(scale), "getScaleMatrix");

    scale = { 0, 2, 1 };
    compareMatrices(getScaleMatrix(scale), osg::Matrix::scale(scale), "getScaleMatrix");

    scale = { 10, 0, 1 };
    compareMatrices(getScaleMatrix(scale), osg::Matrix::scale(scale), "getScaleMatrix");
}

TEST(MatricesTest, RotationMatrixTest)
{
    double angle = osg::DegreesToRadians(45.0);

    const osg::Vec3d xAxis(1, 0, 0);
    const osg::Vec3d yAxis(0, 1, 0);
    const osg::Vec3d zAxis(0, 0, 1);

    auto mine = rotateAroundX(angle);
    auto osg = osg::Matrix::rotate(angle, xAxis);
    
    compareMatrices(rotateAroundX(angle), osg::Matrix::rotate(angle, xAxis), "rotateAroundX");
    compareMatrices(rotateAroundY(angle), osg::Matrix::rotate(angle, yAxis), "rotateAroundY");
    compareMatrices(rotateAroundZ(angle), osg::Matrix::rotate(angle, zAxis), "rotateAroundZ");


    angle = osg::DegreesToRadians(0.0);
    compareMatrices(rotateAroundX(angle), osg::Matrix::rotate(angle, xAxis), "rotateAroundX");
    compareMatrices(rotateAroundY(angle), osg::Matrix::rotate(angle, yAxis), "rotateAroundY");
    compareMatrices(rotateAroundZ(angle), osg::Matrix::rotate(angle, zAxis), "rotateAroundZ");


    angle = osg::DegreesToRadians(-15.0);
    compareMatrices(rotateAroundX(angle), osg::Matrix::rotate(angle, xAxis), "rotateAroundX");
    compareMatrices(rotateAroundY(angle), osg::Matrix::rotate(angle, yAxis), "rotateAroundY");
    compareMatrices(rotateAroundZ(angle), osg::Matrix::rotate(angle, zAxis), "rotateAroundZ");
}

TEST(AngleTest, angleBetweenVectors)
{
    double angle = osg::DegreesToRadians(45.0);
    const osg::Vec3d zAxis(0, 0, 1);

    osg::Vec3 in(1, 0, 0);
    osg::Vec3 rotated = in * osg::Matrix::rotate(angle, zAxis);

    EXPECT_NEAR(angleBetweenVectors(in, rotated), angle, 1e-7);

    in = { 10, 0, 0 };
    rotated = { in * osg::Matrix::rotate(angle, zAxis) };
    EXPECT_NEAR(angleBetweenVectors(in, rotated), angle, 1e-7);

    angle = osg::DegreesToRadians(0.0);
    in = { 1, 0, 0 };
    rotated = { in * osg::Matrix::rotate(angle, zAxis) };
    EXPECT_NEAR(angleBetweenVectors(in, rotated), angle, 1e-7);
}

TEST(RotationBetweenVectors, getRotationMatrix)
{
    osg::Vec3d from(1, 0, 0);
    osg::Vec3d to(0, 1, 0);

    compareMatrices(getRotationMatrix(from, to), osg::Matrix::rotate(from, to), "getRotationMatrix");

    from = { 1,0,0 };
    to = { 1,1,0 };
    compareMatrices(getRotationMatrix(from, to), osg::Matrix::rotate(from, to), "getRotationMatrix");

    from = { 0,1,0 };
    to = { -1,0,0 };
    compareMatrices(getRotationMatrix(from, to), osg::Matrix::rotate(from, to), "getRotationMatrix");

    from = { 0,1,0 };
    to = { 1,0,0 };
    compareMatrices(getRotationMatrix(from, to), osg::Matrix::rotate(from, to), "getRotationMatrix");
}
