#pragma once

#include "View/Painter.h"
#include "View/ViewPort.h"


Painter::Painter(QPainter & painter, ViewPort & viewPort)
  : m_painter(&painter)
  , m_viewPort(&viewPort)
{
}

void Painter::DrawLineSegment(const Point & startPoint, const Point & endPoint)
{
  m_painter->drawLine(m_viewPort->FromModel(startPoint), m_viewPort->FromModel(endPoint));
}

void Painter::SetPen(LineTypes lineType, int width, Rgba customColor)
{
  QColor color(customColor.red(), customColor.green(), customColor.blue(), customColor.alpha());
  switch (lineType)
  {
    case LineTypes::SolidLine:
    {
      m_painter->setPen(QPen(color, width, Qt::PenStyle::SolidLine));
      break;
    }
    case LineTypes::DashLine:
    {
      m_painter->setPen(QPen(color, width, Qt::PenStyle::DashLine));
      break;
    }
    default:
      break;
  }
}

void Painter::DrawControlPoints(const Point & point)
{
  m_painter->setPen(QPen(Qt::red, 7, Qt::PenStyle::SolidLine));
  m_painter->drawPoint(m_viewPort->FromModel(point));
}

void Painter::DrawBrokenLine(const std::vector<Point> & points, LineTypes type, int width, Rgba color)
{
  SetPen(type, width, color);
  if (points.size() > 1)
  {
    for (auto i = 0; i < points.size() - 1; ++i)
    {
      m_painter->drawLine(m_viewPort->FromModel(points[i]), m_viewPort->FromModel(points[i + 1]));
    }
  }
  else
  {
    m_painter->drawPoint(m_viewPort->FromModel(points.back()));
  }
}
