#pragma once

#include "Controller/BrokenLineDrawingProcess.h"


BrokenLineDrawingProcess::BrokenLineDrawingProcess(ModelOfDocument & model, UndoRedo & undoRedoManager)
  : m_documentModel(&model)
  , m_undoRedoManager(&undoRedoManager)
{
}

void BrokenLineDrawingProcess::Apply()
{
  m_undoRedoManager->AddCommand(std::make_shared<AddObjectCommand>(m_builder.CreateBrokenLine(), *m_documentModel));
  m_builder.ClearBuilder();
}

void BrokenLineDrawingProcess::Cancel()
{
    m_canApply = false;
}

void BrokenLineDrawingProcess::MouseClicked(const Point& p)
{
    m_builder.AddPoint(p);
}

void BrokenLineDrawingProcess::MouseMoved(const Point & p)
{
  if (!m_builder.IsBuilderEmpty())
  {
    m_builder.SetPhantomPoint(p);
  }
}

void BrokenLineDrawingProcess::MouseReleased(const Point & p)
{
}

void BrokenLineDrawingProcess::KeyPressed(Button button)
{
  if (button == Button::Enter)
  {
    Apply();
  }
}

void BrokenLineDrawingProcess::Render(Painter & painter)
{
  if (!m_builder.IsBuilderEmpty())
  {
    m_builder.RenderBuilder(painter, LineTypes::SolidLine);
  }
}