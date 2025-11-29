#pragma once

#include "Figure.h"
#include <cmath>
#include <array>
#include <memory>

template <Scalar T>
class Triangle : public Figure<T>
{
private:
    std::array<std::unique_ptr<Point<T>>, 3> points;

public:
    Triangle()
    {
        points[0] = std::make_unique<Point<T>>(0, 0);
        points[1] = std::make_unique<Point<T>>(1, 0);
        points[2] = std::make_unique<Point<T>>(0.5, std::sqrt(3) / 2);
    }

    Triangle(const Point<T> &A, const Point<T> &B, const Point<T> &C)
    {
        points[0] = std::make_unique<Point<T>>(A);
        points[1] = std::make_unique<Point<T>>(B);
        points[2] = std::make_unique<Point<T>>(C);
    }

    Triangle(const Triangle &other)
    {
        for (int i = 0; i < 3; ++i)
        {
            points[i] = std::make_unique<Point<T>>(*other.points[i]);
        }
    }

    Triangle &operator=(const Triangle &other)
    {
        if (this != &other)
        {
            for (int i = 0; i < 3; ++i)
            {
                points[i] = std::make_unique<Point<T>>(*other.points[i]);
            }
        }
        return *this;
    }

    Triangle(Triangle &&other) noexcept = default;
    Triangle &operator=(Triangle &&other) noexcept = default;

    Point<T> center() const override
    {
        T sumX = 0, sumY = 0;
        for (const auto &point : points)
        {
            sumX += point->x();
            sumY += point->y();
        }
        return Point<T>(sumX / 3, sumY / 3);
    }

    operator double() const override
    {
        T a = std::hypot(points[1]->x() - points[0]->x(),
                         points[1]->y() - points[0]->y());
        T b = std::hypot(points[2]->x() - points[1]->x(),
                         points[2]->y() - points[1]->y());
        T c = std::hypot(points[0]->x() - points[2]->x(),
                         points[0]->y() - points[2]->y());

        T s = (a + b + c) / 2;
        return std::sqrt(s * (s - a) * (s - b) * (s - c));
    }

    bool equals(const Figure<T> &other) const override
    {
        const Triangle *otherTriangle = dynamic_cast<const Triangle *>(&other);
        if (!otherTriangle)
            return false;

        for (int i = 0; i < 3; ++i)
        {
            if (*points[i] != *otherTriangle->points[i])
            {
                return false;
            }
        }
        return true;
    }

protected:
    void print(std::ostream &os) const override
    {
        os << "Triangle: ";
        for (const auto &point : points)
        {
            os << *point << " ";
        }
    }

    void read(std::istream &is) override
    {
        Point<T> A, B, C;
        is >> A >> B >> C;
        points[0] = std::make_unique<Point<T>>(A);
        points[1] = std::make_unique<Point<T>>(B);
        points[2] = std::make_unique<Point<T>>(C);
    }
};