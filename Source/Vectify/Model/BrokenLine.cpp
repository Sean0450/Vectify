#pragma once

#include "Model/BrokenLineControlPoint.h"


BrokenLine::BrokenLine(ModelOfDocument & model, const std::vector<Point> & points)
  : m_documentModel(&model)
  , m_points(points)
{
}

std::vector<std::shared_ptr<ControlPoint>> BrokenLine::GetControlPoints()
{
  std::vector<std::shared_ptr<ControlPoint>> points;
  for (auto i = 0; i < m_points.size(); ++i)
  {
    points.emplace_back(std::make_shared<BrokenLineControlPoint>(*this, i));
  }
  return points;
}

Point BrokenLine::GetPoint(int index) const
{
  assert(index < m_points.size());
  return m_points[index];
}

void BrokenLine::SetPoint(const Point & p, int index)
{
  assert(index < m_points.size());
  m_points[index] = p;
}

bool BrokenLine::PointBelongsObject(const Point & p)
{
  return std::ranges::adjacent_find(m_points, [&p](const Point & first, const Point & second)
                                    { return PointOnLine(first, second, p); }) != m_points.end();
}

void BrokenLine::Render(Painter & painter, RenderType type)
{
  painter.DrawBrokenLine(m_points, LineTypes::SolidLine, m_width, m_color);
}

//-----------------------------------------------------------------------------
//Записывывает фунцию создания ломанных в map, находящийся в фабрике объектов
//--
[[maybe_unused]] static bool _ = std::invoke(
  []()
  {
    GeometryObjectsFactory::get().RegistFunction(BrokenLine::GetObjectName(), &BrokenLine::FromString);
    return true;
  });
