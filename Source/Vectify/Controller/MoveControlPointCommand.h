#pragma once

#include "Controller/Command.h"
#include "Model/ControlPoint.h"


////////////////////////////////////////////////////////////////////////////////
//
//Команда перемещения контрольной точки объекта. Сохраняет начальную и предыдущие положения точки.
//
////////////////////////////////////////////////////////////////////////////////
class MoveControlPointCommand : public Command
{
  std::shared_ptr<ControlPoint> m_controlPoint;
  Point m_startPoint;
  Point m_previousPoint;

public:
  //-----------------------------------------------------------------------------
  //Создает команду на основании объекта и позиции контрольной точки.
  //--
  MoveControlPointCommand(std::shared_ptr<ControlPoint> point, const Point & p);
  virtual void Execute();
  virtual void UnExecute();
};
