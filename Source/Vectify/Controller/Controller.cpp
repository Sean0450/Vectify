#pragma once

#include "Controller/Controller.h"


Controller::Controller(Private, std::shared_ptr<View> view)
  : m_view(std::move(view))
{
  m_document = std::make_shared<Document>();
  m_activeProcess = std::make_unique<DefaultProcess>(m_document->GetModelOfDocument(), m_undoRedoManager);
}

std::shared_ptr<Controller> Controller::Create(std::shared_ptr<View> view)
{
  auto controller = std::make_shared<Controller>(Private(), view);

  //При создании shared_ptr не сразу становится enabled_shared, из-за чего weak_from_this() вёл себя не так, как ожидалось
  controller->m_document->GetModelOfDocument().SetObserver(controller->weak_from_this());
  return controller;
}

void Controller::OnLineSegmentClicked()
{
  m_activeProcess = std::make_unique<LineSegmentDrawingProcess>(m_document->GetModelOfDocument(), m_undoRedoManager);
}

void Controller::OnBrokenLineClicked()
{
  m_activeProcess = std::make_unique<BrokenLineDrawingProcess>(m_document->GetModelOfDocument(), m_undoRedoManager);
}

void Controller::OnCentralPointRectangleClicked()
{
}

void Controller::OnAnglesRectangleClicked()
{
}

void Controller::OnDefaultProcess()
{
  m_activeProcess = std::make_unique<DefaultProcess>(m_document->GetModelOfDocument(), m_undoRedoManager);
  m_view->ResetAllButtons();
}

void Controller::OnCreateDocumentButtonClicked()
{
  m_document = std::make_shared<Document>();
  m_document->GetModelOfDocument().SetObserver(weak_from_this());
  m_undoRedoManager.Clear();
  m_view->SetEnabledUndoRedo(m_undoRedoManager.UndoHasValue(), m_undoRedoManager.RedoHasValue());
  OnDefaultProcess();
  m_view->SetNeedRepaint();
}

void Controller::OnLoadDocumentButtonClicked()
{
  if (m_document->GetPath().empty())
  {
    m_document->SetPath(Dialoges::OpenFileDialoge());
  }
  std::ifstream file(m_document->GetPath());
  std::smatch separator;
  std::string line;
  bool allObjectsReaded = true;
  if (file.is_open())
  {
    while (std::getline(file, line))
    {
      if (std::regex_search(line, separator, Regex::objectNameSeparation))
      {
        if (auto object = GeometryObjectsFactory::get().CreateObject(std::string(separator.prefix()),
                                                                     std::string(separator.suffix()),
                                                                     m_document->GetModelOfDocument()))
        {
          m_document->GetModelOfDocument().AddObject(object);
        }
      }
      else
      {
        allObjectsReaded = false;
      }
    }
    if (!allObjectsReaded)
    {
      Dialoges::ShowBrokenFileMessage();
    }
    else
    {
      m_undoRedoManager.Clear();
      m_view->SetEnabledUndoRedo(m_undoRedoManager.UndoHasValue(), m_undoRedoManager.RedoHasValue());
      m_view->SetNeedRepaint();
    }
  }
  else {
      Dialoges::ShowFileNotFound(m_document->GetPath());
      m_document->SetPath("");
  }
}

void Controller::OnSaveDocumentButtonClicked()
{
  if (m_document->GetModelOfDocument().Changed())
  {
    m_document->Save();
    m_view->SetEnabledSave(false);
  }
}

void Controller::OnExportButtonClicked()
{
}

void Controller::OnUndoButtonClicked()
{
  m_undoRedoManager.Undo();
  m_view->SetNeedRepaint();
}

void Controller::OnRedoButtonClicked()
{
  m_undoRedoManager.Redo();
  m_view->SetNeedRepaint();
}

void Controller::OnSelectSolidLineButtonClicked()
{
}

void Controller::OnSelectDasheLineButtonClicked()
{
}

void Controller::OnSetDefaultPropertiesButtonClicked()
{
}

void Controller::OnMouseMove(const Point & p)
{
  if (m_activeProcess->CanApply())
  {
    m_activeProcess->MouseMoved(p);
    m_view->SetNeedRepaint();
  }
}

void Controller::OnMousePressed(const Point & p)
{
  if (m_activeProcess->CanApply())
  {
    m_activeProcess->MouseClicked(p);
    m_view->SetNeedRepaint();
  }
}

void Controller::OnMouseReleased(const Point & p)
{
  if (m_activeProcess->CanApply())
  {
    m_activeProcess->MouseReleased(p);
    m_view->SetNeedRepaint();
  }
}

void Controller::OnKeyPressed(Button button)
{
  if (m_activeProcess->CanApply())
  {
    m_activeProcess->KeyPressed(button);
  }
  if (button == Button::Esc)
  {
    OnDefaultProcess();
  }
  m_view->SetNeedRepaint();
}

void Controller::OnWheelMove()
{
}

void Controller::GeometryObjectCreated(std::shared_ptr<GeometryObject> object)
{
  m_view->SetEnabledUndoRedo(m_undoRedoManager.UndoHasValue(), m_undoRedoManager.RedoHasValue());
  m_view->SetEnabledSave(true);
}

void Controller::GeometryObjectDeleted(std::shared_ptr<GeometryObject> object)
{
  if (auto process = dynamic_cast<DefaultProcess *>(m_activeProcess.get()))
  {
    process->ResetSelectedObjects();
  }
  m_view->SetEnabledUndoRedo(m_undoRedoManager.UndoHasValue(), m_undoRedoManager.RedoHasValue());
  m_view->SetEnabledSave(true);
}

void Controller::GeometryObjectControlPointChanged()
{
  m_view->SetEnabledUndoRedo(m_undoRedoManager.UndoHasValue(), m_undoRedoManager.RedoHasValue());
  m_view->SetEnabledSave(true);
}

void Controller::RenderEvent(Painter & painter)
{
  m_document->GetModelOfDocument().RenderModel(painter);
  m_activeProcess->Render(painter);
}
