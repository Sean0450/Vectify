#pragma once

#include "Controller/LineSegmentDrawingProcess.h"

#include "View/Painter.h"


LineSegmentDrawingProcess::LineSegmentDrawingProcess(ModelOfDocument & model, UndoRedo & manager)
  : m_documentModel(&model)
  , m_undoRedoManager(&manager)
{
}

//На процесс создания отрезка не требуются функции для подтверждения построения
void LineSegmentDrawingProcess::Apply()
{
}

void LineSegmentDrawingProcess::Cancel()
{
}
void LineSegmentDrawingProcess::MouseClicked(const Point & p)
{
  if (m_lineSegment == nullptr)
  {
    m_lineSegment = std::make_shared<LineSegment>(*m_documentModel, p, p);
  }
  else
  {
    if (DistanceBetween(m_lineSegment->GetStartPoint(), p) > DrawingConstants::delta)
    {
      m_lineSegment->SetEndPoint(p);
      m_undoRedoManager->AddCommand(std::make_shared<AddObjectCommand>(m_lineSegment, *m_documentModel));
      m_lineSegment.reset();
    }
  }
}

void LineSegmentDrawingProcess::MouseMoved(const Point & p)
{
  if (m_lineSegment != nullptr)
  {
    m_lineSegment->SetEndPoint(p);
  }
}

void LineSegmentDrawingProcess::MouseReleased(const Point & p)
{
}

void LineSegmentDrawingProcess::Render(Painter & painter)
{
  if (m_lineSegment != nullptr)
  {
    m_lineSegment->Render(painter, RenderType::PhantomRender);
  }
}

void LineSegmentDrawingProcess::KeyPressed(Button button)
{
}
