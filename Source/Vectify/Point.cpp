#pragma once

#include "Model/Point.h"


int DistanceBetween(const Point & fpoint, const Point & spoint)
{
  return std::hypot(fpoint.m_x - spoint.m_x, fpoint.m_y - spoint.m_y);
}

Point MiddlePoint(const Point & p, const Point & sp)
{
  return Point((p.m_x + sp.m_x) / 2, (p.m_y + sp.m_y) / 2);
}

bool PointOnLine(const Point & startPoint, const Point & endPoint, const Point & checkPoint)
{
  if (std::sqrt(std::pow(checkPoint.m_x - startPoint.m_x, 2) + std::pow(checkPoint.m_y - startPoint.m_y, 2)) +
        std::sqrt(std::pow(endPoint.m_x - checkPoint.m_x, 2) + std::pow(endPoint.m_y - checkPoint.m_y, 2)) -
        std::sqrt(std::pow(endPoint.m_x - startPoint.m_x, 2) + std::pow(endPoint.m_y - startPoint.m_y, 2)) <
      1)
  {
    return true;
  }
  return false;
}