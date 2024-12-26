#pragma once

#include "Controller/AddObjectCommand.h"


AddObjectCommand::AddObjectCommand(std::shared_ptr<GeometryObject> object, ModelOfDocument & model)
  : m_object(std::move(object))
  , m_documentModel(&model)
{
}

void AddObjectCommand::Execute()
{
  m_documentModel->AddObject(m_object);
}
void AddObjectCommand::UnExecute()
{
  m_documentModel->RemoveObject(m_object);
}
