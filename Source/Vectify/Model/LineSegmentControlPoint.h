#pragma once

#include "Model/ControlPoint.h"
#include "Model/LineSegment.h"


////////////////////////////////////////////////////////////////////////////////
//
/*Реализация котрольной точки отрезка. Всего на отрезок создаются 2 контрольных точки:
на начальную точку, на конечную точку.*/
//
////////////////////////////////////////////////////////////////////////////////
class LineSegmentControlPoint : public ControlPoint
{
  LineSegment * m_lineSegment = nullptr;
  LineSegmentPoints m_point;

public:
  //-----------------------------------------------------------------------------
  //Конструктор, принимает ссылку на отрезок и позицию контрольной точки.
  //--
  LineSegmentControlPoint(LineSegment & lineSegment, LineSegmentPoints point);
  virtual void SetPosition(const Point & point);
  virtual void ControlPointChanged() const noexcept { m_lineSegment->ControlPointChanged(); };
  virtual Point GetPosition() const;
};
