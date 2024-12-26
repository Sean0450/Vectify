#pragma once

#include <iostream>
#include <optional>

#include "Regexpr.h"


struct Point
{
  double m_x = 0;
  double m_y = 0;
  Point() = default;
  Point(double nx, double ny) noexcept
    : m_x(nx)
    , m_y(ny){};
  const std::string ToString() noexcept { return " {" + std::to_string(m_x) + ", " + std::to_string(m_y) + "} "; }
  static std::optional<Point> FromString(const std::string & point) noexcept
  {
    auto startIterator = std::sregex_iterator(point.cbegin(), point.cend(), Regex::pointsValuesSeparation);
    auto x = std::stod(startIterator->str());
    startIterator++;
    auto y = std::stod(startIterator->str());
    return Point(x, y);
  }
};

int DistanceBetween(const Point & fpoint, const Point & spoint);

Point MiddlePoint(const Point & p, const Point & sp);

bool PointOnLine(const Point & startPoint, const Point & endPoint, const Point & checkPoint);
