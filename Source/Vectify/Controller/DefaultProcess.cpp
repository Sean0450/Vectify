#pragma once

#include "Controller/DefaultProcess.h"


DefaultProcess::DefaultProcess(ModelOfDocument & documentModel, UndoRedo & undoRedoManager)
  : m_documentModel(&documentModel)
  , m_undoRedoManager(&undoRedoManager)
{
}

//Процессу по умолчанию не нужно подтверждение построения
void DefaultProcess::Apply()
{
}

void DefaultProcess::Cancel()
{
}

void DefaultProcess::MouseClicked(const Point & p)
{
  m_startSelectionPoint = p;
  if (auto object = GetObjectAtPoint(p, *m_documentModel))
  {
    if (std::find(m_selectedObjects.begin(), m_selectedObjects.end(), object) != m_selectedObjects.end())
    {
      for (auto && it : object->GetControlPoints())
      {
        if (DistanceBetween(it->GetPosition(), p) < DrawingConstants::delta)
        {
          m_savedControlPoint = std::move(it);
          m_controlPointStartPosition = m_savedControlPoint->GetPosition();
          return;
        }
      }
    }
    else
    {
      if (!m_selectedObjects.empty())
      {
        for (auto && it : m_selectedObjects.front()->GetControlPoints())
        {
          if (DistanceBetween(it->GetPosition(), p) < DrawingConstants::delta)
          {
            m_savedControlPoint = std::move(it);
            m_controlPointStartPosition = m_savedControlPoint->GetPosition();
            return;
          }
        }
      }
    }
  }
  else
  {
    m_selectedObjects.clear();
  }
}

void DefaultProcess::MouseMoved(const Point & p)
{
  if (m_savedControlPoint != nullptr)
  {
    m_savedControlPoint->SetPosition(p);
  }
}

void DefaultProcess::MouseReleased(const Point & p)
{
  if (m_savedControlPoint != nullptr &&
      DistanceBetween(m_controlPointStartPosition, m_savedControlPoint->GetPosition()) > DrawingConstants::delta)
  {
    m_undoRedoManager->AddCommand(std::make_shared<MoveControlPointCommand>(m_savedControlPoint, m_controlPointStartPosition));

    //Без освобождения указателя пораждаются пустые комманды перемещения контрольной точки
    m_savedControlPoint.reset();
  }
  if (DistanceBetween(m_startSelectionPoint, p) < DrawingConstants::minFrameRadius)
  {
    if (auto object = GetObjectAtPoint(MiddlePoint(m_startSelectionPoint, p), *m_documentModel))
    {
      m_selectedObjects = std::vector<std::shared_ptr<GeometryObject>>{object};
    }
  }
  else
  {
    //Здесь будет реализация выделения рамкой
  }
}

void DefaultProcess::Render(Painter & painter)
{
  for (auto && it : m_selectedObjects)
  {
    for (auto && pointsIterator : it->GetControlPoints())
    {
      painter.DrawControlPoints(pointsIterator->GetPosition());
    }
  }
}

void DefaultProcess::KeyPressed(Button button)
{
  switch (button)
  {
    case Button::Delete:
    {
      auto removeObjectCommandsList = std::make_shared<CommandList>();
      for (auto && it : m_selectedObjects)
      {
        removeObjectCommandsList->AddCommand(std::make_shared<RemoveObjectCommand>(it, *m_documentModel));
      }
      m_undoRedoManager->AddCommand(removeObjectCommandsList);
      m_selectedObjects.clear();
    }
    default:
      break;
  }
}
