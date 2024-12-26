#pragma once

#include "Controller/AddObjectCommand.h"
#include "Controller/Process.h"
#include "Model/BrokenLineBuilder.h"


////////////////////////////////////////////////////////////////////////////////
//
/// Процесс отрисовки геометрического объекта ломанная.
//
////////////////////////////////////////////////////////////////////////////////
class BrokenLineDrawingProcess : public Process
{
  ModelOfDocument * m_documentModel;
  UndoRedo * m_undoRedoManager;
  bool m_canApply = true;
  BrokenLineBuilder m_builder{*m_documentModel};

public:
  //-----------------------------------------------------------------------------
  //Объект процесса принимает на вход модель документа и менеджера событий.
  //--
  BrokenLineDrawingProcess(ModelOfDocument & model, UndoRedo & undoRedoManager);
  virtual void Apply() override;
  virtual bool CanApply() const noexcept override { return m_canApply; };
  virtual void Cancel() override;
  virtual void MouseClicked(const Point & p) override;
  virtual void MouseMoved(const Point & p) override;
  virtual void MouseReleased(const Point & p) override;
  virtual void KeyPressed(Button button) override;
  virtual void Render(Painter & painter) override;
};
