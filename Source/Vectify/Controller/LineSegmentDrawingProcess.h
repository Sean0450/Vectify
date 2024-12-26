#pragma once

#include "Controller/AddObjectCommand.h"
#include "Controller/Process.h"
#include "Model/LineSegment.h"


////////////////////////////////////////////////////////////////////////////////
//
//Реализация процесса построения отрезка.
//
////////////////////////////////////////////////////////////////////////////////
class LineSegmentDrawingProcess : public Process
{
private:
  ModelOfDocument * m_documentModel;
  UndoRedo * m_undoRedoManager;
  std::shared_ptr<LineSegment> m_lineSegment;

public:
  //-----------------------------------------------------------------------------
  //Объект процесса принимает на вход модель документа и менеджер событий.
  //--
  LineSegmentDrawingProcess(ModelOfDocument & model, UndoRedo & manager);
  virtual void Apply() override;
  virtual bool CanApply() const noexcept override { return true; };
  virtual void Cancel() override;
  virtual void MouseClicked(const Point & p) override;
  virtual void MouseMoved(const Point & p) override;
  virtual void MouseReleased(const Point & p) override;
  virtual void KeyPressed(Button button) override;
  virtual void Render(Painter & painter) override;
};
