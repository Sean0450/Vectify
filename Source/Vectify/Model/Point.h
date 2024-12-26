#pragma once

#include <iostream>
#include <optional>

#include "Model/Regexpr.h"


////////////////////////////////////////////////////////////////////////////////
//
/// Реализация точки в модельных координатах.
//
////////////////////////////////////////////////////////////////////////////////
struct Point
{
  double m_x = 0;
  double m_y = 0;
  //-----------------------------------------------------------------------------
  //Создание пустой точки.
  //--
  Point() = default;
  //-----------------------------------------------------------------------------
  //Создание точки из двух координат. Тип double используется для правильного подсчета масштабирования.
  //--
  Point(double nx, double ny) noexcept
    : m_x(nx)
    , m_y(ny){};
  //-----------------------------------------------------------------------------
  //Переводит точку в строку.
  //--
  const std::string ToString() noexcept { return " {" + std::to_string(m_x) + ", " + std::to_string(m_y) + "} "; }
  //-----------------------------------------------------------------------------
  //Получает на вход строку и по возможности возвращает точку.
  //--
  static std::optional<Point> FromString(const std::string & point) noexcept
  {
    auto startIterator = std::sregex_iterator(point.cbegin(), point.cend(), Regex::pointsValuesSeparation);
    auto x = std::stod(startIterator->str());
    startIterator++;
    auto y = std::stod(startIterator->str());
    return Point(x, y);
  }
};

//-----------------------------------------------------------------------------
//Возвращает расстояние между точками в пикселях.
//--
int DistanceBetween(const Point & fpoint, const Point & spoint);

//-----------------------------------------------------------------------------
//Возвращает среднюю точку, между двумя, переданными в параметрах.
//--
Point MiddlePoint(const Point & p, const Point & sp);

//-----------------------------------------------------------------------------
//Проверяет, находится ли точка между двумя, переданными в параметрах.
//--
bool PointOnLine(const Point & startPoint, const Point & endPoint, const Point & checkPoint);
