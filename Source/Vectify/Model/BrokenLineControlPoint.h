#pragma once

#include "Model/BrokenLine.h"
#include "Model/ControlPoint.h"


////////////////////////////////////////////////////////////////////////////////
//
/*Реализация котрольной точки ломанной. Контрольных точек создается столько,
сколько вершин у ломанной (сколько значений в векторе точек). */
//
////////////////////////////////////////////////////////////////////////////////
class BrokenLineControlPoint : public ControlPoint
{
  BrokenLine * m_brokenLine;
  int m_index = -1;

public:
  //-----------------------------------------------------------------------------
  //Конструктор, принимает ссылку на ломанную и индекс создаваемой точки.
  //--
  BrokenLineControlPoint(BrokenLine & brokenLine, int index);
  virtual void SetPosition(const Point & p) override;
  virtual void ControlPointChanged() const noexcept { m_brokenLine->ControlPointChanged(); };
  virtual Point GetPosition() const;
};
