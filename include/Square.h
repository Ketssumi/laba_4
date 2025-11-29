#pragma once

#include "Figure.h"
#include <cmath>
#include <array>
#include <memory>

template <Scalar T>
class Square : public Figure<T>
{
private:
  std::array<std::unique_ptr<Point<T>>, 4> points;

public:
  Square()
  {
    points[0] = std::make_unique<Point<T>>(0, 0);
    points[1] = std::make_unique<Point<T>>(1, 0);
    points[2] = std::make_unique<Point<T>>(1, 1);
    points[3] = std::make_unique<Point<T>>(0, 1);
  }

  Square(const Point<T> &A, const Point<T> &B, const Point<T> &C, const Point<T> &D)
  {
    points[0] = std::make_unique<Point<T>>(A);
    points[1] = std::make_unique<Point<T>>(B);
    points[2] = std::make_unique<Point<T>>(C);
    points[3] = std::make_unique<Point<T>>(D);
  }

  Square(const Square &other)
  {
    for (int i = 0; i < 4; ++i)
    {
      points[i] = std::make_unique<Point<T>>(*other.points[i]);
    }
  }

  Square &operator=(const Square &other)
  {
    if (this != &other)
    {
      for (int i = 0; i < 4; ++i)
      {
        points[i] = std::make_unique<Point<T>>(*other.points[i]);
      }
    }
    return *this;
  }

  Square(Square &&other) noexcept = default;
  Square &operator=(Square &&other) noexcept = default;

  Point<T> center() const override
  {
    T sumX = 0, sumY = 0;
    for (const auto &point : points)
    {
      sumX += point->x();
      sumY += point->y();
    }
    return Point<T>(sumX / 4, sumY / 4);
  }

  operator double() const override
  {
    T area = 0;
    for (int i = 0; i < 4; ++i)
    {
      int j = (i + 1) % 4;
      area += points[i]->x() * points[j]->y() - points[j]->x() * points[i]->y();
    }
    return std::abs(area) / 2;
  }

  bool equals(const Figure<T> &other) const override
  {
    const Square *otherSquare = dynamic_cast<const Square *>(&other);
    if (!otherSquare)
      return false;

    for (int i = 0; i < 4; ++i)
    {
      if (*points[i] != *otherSquare->points[i])
      {
        return false;
      }
    }
    return true;
  }

protected:
  void print(std::ostream &os) const override
  {
    os << "Square: ";
    for (const auto &point : points)
    {
      os << *point << " ";
    }
  }

  void read(std::istream &is) override
  {
    Point<T> A, B, C, D;
    is >> A >> B >> C >> D;
    points[0] = std::make_unique<Point<T>>(A);
    points[1] = std::make_unique<Point<T>>(B);
    points[2] = std::make_unique<Point<T>>(C);
    points[3] = std::make_unique<Point<T>>(D);
  }
};