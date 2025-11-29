#include <gtest/gtest.h>
#include <sstream>
#include <memory>
#include "Array.h"
#include "Triangle.h"
#include "Square.h"
#include "Octagon.h"

// Тест для Triangle
TEST(TriangleTest, CreationAndArea)
{
    Triangle<double> triangle;

    EXPECT_GT(static_cast<double>(triangle), 0);

    Point<double> center = triangle.center();
    EXPECT_DOUBLE_EQ(center.x(), 0.5);
    EXPECT_NEAR(center.y(), std::sqrt(3) / 6, 1e-10);
}

TEST(TriangleTest, InputOutput)
{
    Triangle<double> triangle;
    std::stringstream ss;

    ss << "0 0 1 0 0.5 0.866";
    ss >> triangle;

    EXPECT_NEAR(static_cast<double>(triangle), 0.433, 0.001);
}

TEST(TriangleTest, Equality)
{
    Triangle<double> t1;
    Triangle<double> t2;

    EXPECT_TRUE(t1.equals(t2));

    Triangle<double> t3(Point<double>(0, 0), Point<double>(2, 0), Point<double>(1, 1));
    EXPECT_FALSE(t1.equals(t3));
}

// Тест для Square
TEST(SquareTest, CreationAndArea)
{
    Square<double> square;

    EXPECT_DOUBLE_EQ(static_cast<double>(square), 1.0);

    Point<double> center = square.center();
    EXPECT_DOUBLE_EQ(center.x(), 0.5);
    EXPECT_DOUBLE_EQ(center.y(), 0.5);
}

TEST(SquareTest, InputOutput)
{
    Square<double> square;
    std::stringstream ss;

    ss << "0 0 2 0 2 2 0 2";
    ss >> square;

    EXPECT_DOUBLE_EQ(static_cast<double>(square), 4.0);
}

TEST(SquareTest, Equality)
{
    Square<double> s1;
    Square<double> s2;

    EXPECT_TRUE(s1.equals(s2));

    Square<double> s3(Point<double>(0, 0), Point<double>(2, 0),
                      Point<double>(2, 2), Point<double>(0, 2));
    EXPECT_FALSE(s1.equals(s3));
}

// Тест для Octagon
TEST(OctagonTest, CreationAndArea)
{
    Octagon<double> octagon;

    EXPECT_GT(static_cast<double>(octagon), 0);

    Point<double> center = octagon.center();
    EXPECT_NEAR(center.x(), 0, 1e-10);
    EXPECT_NEAR(center.y(), 0, 1e-10);
}

TEST(OctagonTest, InputOutput)
{
    Octagon<double> octagon;
    std::stringstream ss;

    ss << "1 0 0.707 0.707 0 1 -0.707 0.707 -1 0 -0.707 -0.707 0 -1 0.707 -0.707";
    ss >> octagon;

    EXPECT_NEAR(static_cast<double>(octagon), 2.828, 0.001);
}

// Тест с разными скалярными типами
TEST(TemplateTest, DifferentScalarTypes)
{
    // Тест с int
    Triangle<int> triangle_int(Point<int>(0, 0), Point<int>(1, 0), Point<int>(0, 1));
    EXPECT_GE(static_cast<double>(triangle_int), 0);

    // Тест с float
    Triangle<float> triangle_float(Point<float>(0, 0), Point<float>(1, 0), Point<float>(0, 1));
    EXPECT_GE(static_cast<double>(triangle_float), 0);

    // Тест с double
    Triangle<double> triangle_double(Point<double>(0, 0), Point<double>(1, 0), Point<double>(0, 1));
    EXPECT_GE(static_cast<double>(triangle_double), 0);
}

// Тест с различными входными данными
TEST(VariousInputTest, DifferentTriangles)
{
    // Остроугольный треугольник
    {
        Triangle<double> triangle;
        std::stringstream ss("0 0 3 0 1 2");
        ss >> triangle;
        EXPECT_GT(static_cast<double>(triangle), 0);
    }

    // Тупоугольный треугольник
    {
        Triangle<double> triangle;
        std::stringstream ss("0 0 2 0 0.5 1");
        ss >> triangle;
        EXPECT_GT(static_cast<double>(triangle), 0);
    }

    // Прямоугольный треугольник
    {
        Triangle<double> triangle;
        std::stringstream ss("0 0 3 0 0 4");
        ss >> triangle;
        EXPECT_DOUBLE_EQ(static_cast<double>(triangle), 6.0);
    }
}

TEST(VariousInputTest, DifferentSquares)
{
    // Квадрат со стороной 1
    {
        Square<double> square;
        std::stringstream ss("0 0 1 0 1 1 0 1");
        ss >> square;
        EXPECT_DOUBLE_EQ(static_cast<double>(square), 1.0);
    }

    // Квадрат со стороной 3
    {
        Square<double> square;
        std::stringstream ss("0 0 3 0 3 3 0 3");
        ss >> square;
        EXPECT_DOUBLE_EQ(static_cast<double>(square), 9.0);
    }

    // Повернутый квадрат
    {
        Square<double> square;
        std::stringstream ss("1 0 0 1 -1 0 0 -1");
        ss >> square;
        EXPECT_NEAR(static_cast<double>(square), 2.0, 0.001);
    }
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}