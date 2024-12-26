#pragma once

#include "Model/LineSegment.h"

#include "Model/LineSegmentControlPoint.h"


LineSegment::LineSegment(ModelOfDocument & model, const Point & startPoint, const Point & endPoint)
  : m_documentModel(&model)
  , m_startPoint(startPoint)
  , m_endPoint(endPoint)
{
}

std::vector<std::shared_ptr<ControlPoint>> LineSegment::GetControlPoints()
{
  std::vector<std::shared_ptr<ControlPoint>> points;
  points.emplace_back(std::make_shared<LineSegmentControlPoint>(*this, LineSegmentPoints::startPoint));
  points.emplace_back(std::make_shared<LineSegmentControlPoint>(*this, LineSegmentPoints::endPoint));
  return points;
}

void LineSegment::SetStartPoint(const Point & p)
{
  m_startPoint = p;
}

void LineSegment::SetEndPoint(const Point & p)
{
  m_endPoint = p;
}

void LineSegment::Render(Painter & painter, RenderType type)
{
  switch (type)
  {
    case RenderType::PhantomRender:
    {
      painter.SetPen(LineTypes::DashLine, m_width, m_color);
      break;
    }
    case RenderType::DefaultRender:
    {
      painter.SetPen(LineTypes::SolidLine, m_width, m_color);
      break;
    }
  }
  painter.DrawLineSegment(m_startPoint, m_endPoint);
}

bool LineSegment::PointBelongsObject(const Point & p)
{
  return PointOnLine(m_startPoint, m_endPoint, p);
}


//-----------------------------------------------------------------------------
//Записывывает фунцию создания отрезков в map, находящийся в фабрике объектов
//--
[[maybe_unused]] static bool _ = std::invoke(
  []()
  {
    GeometryObjectsFactory::get().RegistFunction(LineSegment::GetObjectName(), &LineSegment::FromString);
    return true;
  });
