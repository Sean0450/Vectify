#pragma once

#include "Model/BrokenLineControlPoint.h"


BrokenLineControlPoint::BrokenLineControlPoint(BrokenLine & brokenLine, int index)
  : m_brokenLine(&brokenLine)
  , m_index(index)
{
}

Point BrokenLineControlPoint::GetPosition() const
{
  return m_brokenLine->GetPoint(m_index);
}

void BrokenLineControlPoint::SetPosition(const Point & p)
{
  m_brokenLine->SetPoint(p, m_index);
  ControlPointChanged();
}
