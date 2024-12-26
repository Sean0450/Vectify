#pragma once

#include <vector>

#include "Controller/CommandsList.h"
#include "Controller/MoveControlPointCommand.h"
#include "Controller/Process.h"
#include "Controller/RemoveObjectCommand.h"


////////////////////////////////////////////////////////////////////////////////
//
/*Реализация процесса по умолчанию. При клике по области выделяет объект, делая
возможным перемещение его контрольных точек при нажатии клавиши Delete удаляет 
выделенные объекты.*/
//
////////////////////////////////////////////////////////////////////////////////
class DefaultProcess : public Process
{
  ModelOfDocument * m_documentModel;
  UndoRedo * m_undoRedoManager;
  std::vector<std::shared_ptr<GeometryObject>> m_selectedObjects;
  Point m_startSelectionPoint;
  std::shared_ptr<ControlPoint> m_savedControlPoint;
  Point m_controlPointStartPosition;

public:
  //-----------------------------------------------------------------------------
  //Конструктор, принимает модель документа и менеджера событий.
  //--
  DefaultProcess(ModelOfDocument & documentModel, UndoRedo & undoRedoManager);
  virtual void Apply() override;
  virtual bool CanApply() const noexcept override { return true; };
  virtual void Cancel() override;
  virtual void MouseClicked(const Point & p) override;
  virtual void MouseMoved(const Point & p) override;
  virtual void MouseReleased(const Point & p) override;
  virtual void Render(Painter & painter) override;
  virtual void KeyPressed(Button button) override;

  //-----------------------------------------------------------------------------
  //При использовании менеджера событий, очищает вектор выделенных объектов.
  //--
  void ResetSelectedObjects() noexcept { m_selectedObjects.clear(); }
};
