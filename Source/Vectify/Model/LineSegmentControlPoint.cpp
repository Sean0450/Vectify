#pragma once

#include "Model/LineSegmentControlPoint.h"


LineSegmentControlPoint::LineSegmentControlPoint(LineSegment & lineSegment, LineSegmentPoints point)
  : m_lineSegment(&lineSegment)
  , m_point(point)
{
}

Point LineSegmentControlPoint::GetPosition() const
{
  if (m_point == LineSegmentPoints::startPoint)
  {
    return m_lineSegment->GetStartPoint();
  }
  else
  {
    return m_lineSegment->GetEndPoint();
  }
}

void LineSegmentControlPoint::SetPosition(const Point & point)
{
  if (m_point == LineSegmentPoints::startPoint)
  {
    m_lineSegment->SetStartPoint(point);
  }
  else
  {
    m_lineSegment->SetEndPoint(point);
  }
  ControlPointChanged();
}
