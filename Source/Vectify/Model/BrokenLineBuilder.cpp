#pragma once

#include "Model/BrokenLineBuilder.h"


void BrokenLineBuilder::AddPoint(const Point & p)
{
  m_intermediatePoints.emplace_back(p);

  //Маленькая хитрость, благодаря которой фантомная точка не будет рисовать лишний отрезок, если мы не передвигали мышку, а просто кликнули по области
  m_phantomPoint = p;
}

BrokenLineBuilder::BrokenLineBuilder(ModelOfDocument & model)
  : m_documentModel(&model)
{
}

void BrokenLineBuilder::RenderBuilder(Painter & painter, LineTypes lineType)
{
  painter.DrawBrokenLine(m_intermediatePoints, lineType, m_width, m_color);
  if (DistanceBetween(m_phantomPoint, m_intermediatePoints.back()) > DrawingConstants::delta)
  {
    painter.SetPen(LineTypes::DashLine, m_width, m_color);
    painter.DrawLineSegment(m_intermediatePoints.back(), m_phantomPoint);
  }
}

std::shared_ptr<BrokenLine> BrokenLineBuilder::CreateBrokenLine()
{
  if (!m_intermediatePoints.empty())
  {
    return std::make_shared<BrokenLine>(*m_documentModel, m_intermediatePoints);
  }
  return nullptr;
}
