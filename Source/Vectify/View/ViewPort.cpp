#pragma once

#include "View/ViewPort.h"


void ViewPort::Setdx(double x)
{
  m_offset.setX(x);
}

void ViewPort::Setdy(double y)
{
  m_offset.setY(y);
}

void ViewPort::SetScale(double scale)
{
  m_scale = scale;
}

void ViewPort::ZoomIn()
{
  if (m_scale < 1.9)
  {
    m_scale *= m_scale_coefficient;
  }
}

void ViewPort::ZoomOut()
{
  if (m_scale > 0.6)
  {
    m_scale /= m_scale_coefficient;
  }
}

Point ViewPort::ToModel(const QPoint & pos)
{
  return Point((pos.x() - m_offset.x() * m_scale), (pos.y() - m_offset.y() * m_scale));
}

QPoint ViewPort::FromModel(const Point & pos)
{
  return QPoint(((pos.m_x + m_offset.x()) / m_scale), ((pos.m_y + m_offset.y()) / m_scale));
}
