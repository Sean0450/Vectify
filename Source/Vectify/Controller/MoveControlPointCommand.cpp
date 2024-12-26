#pragma once

#include <Controller/MoveControlPointCommand.h>


MoveControlPointCommand::MoveControlPointCommand(std::shared_ptr<ControlPoint> point, const Point & p)
  : m_controlPoint(std::move(point))
  , m_previousPoint(p)
{
  m_startPoint = m_controlPoint->GetPosition();
}

void MoveControlPointCommand::Execute()
{
  m_controlPoint->SetPosition(m_startPoint);
}

void MoveControlPointCommand::UnExecute()
{
  m_controlPoint->SetPosition(m_previousPoint);
}
