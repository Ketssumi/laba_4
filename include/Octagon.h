#pragma once

#include "Figure.h"
#include <cmath>
#include <numbers>
#include <array>
#include <memory>

template <Scalar T>
class Octagon : public Figure<T>
{
private:
    std::array<std::unique_ptr<Point<T>>, 8> points;

public:
    Octagon()
    {
        for (int i = 0; i < 8; ++i)
        {
            T angle = 2 * static_cast<T>(std::numbers::pi) * i / 8;
            T x = std::cos(angle);
            T y = std::sin(angle);
            points[i] = std::make_unique<Point<T>>(x, y);
        }
    }

    Octagon(const std::array<Point<T>, 8> &vertices)
    {
        for (int i = 0; i < 8; ++i)
        {
            points[i] = std::make_unique<Point<T>>(vertices[i]);
        }
    }

    Octagon(const Octagon &other)
    {
        for (int i = 0; i < 8; ++i)
        {
            points[i] = std::make_unique<Point<T>>(*other.points[i]);
        }
    }

    Octagon &operator=(const Octagon &other)
    {
        if (this != &other)
        {
            for (int i = 0; i < 8; ++i)
            {
                points[i] = std::make_unique<Point<T>>(*other.points[i]);
            }
        }
        return *this;
    }

    Octagon(Octagon &&other) noexcept = default;
    Octagon &operator=(Octagon &&other) noexcept = default;

    Point<T> center() const override
    {
        T sumX = 0, sumY = 0;
        for (const auto &point : points)
        {
            sumX += point->x();
            sumY += point->y();
        }
        return Point<T>(sumX / 8, sumY / 8);
    }

    operator double() const override
    {
        T area = 0;
        for (int i = 0; i < 8; ++i)
        {
            int j = (i + 1) % 8;
            area += points[i]->x() * points[j]->y() - points[j]->x() * points[i]->y();
        }
        return std::abs(area) / 2;
    }

    bool equals(const Figure<T> &other) const override
    {
        const Octagon *otherOctagon = dynamic_cast<const Octagon *>(&other);
        if (!otherOctagon)
            return false;

        for (int i = 0; i < 8; ++i)
        {
            if (*points[i] != *otherOctagon->points[i])
            {
                return false;
            }
        }
        return true;
    }

protected:
    void print(std::ostream &os) const override
    {
        os << "Octagon: ";
        for (const auto &point : points)
        {
            os << *point << " ";
        }
    }

    void read(std::istream &is) override
    {
        for (int i = 0; i < 8; ++i)
        {
            Point<T> p;
            is >> p;
            points[i] = std::make_unique<Point<T>>(p);
        }
    }
};