#pragma once

#include "Controller/RemoveObjectCommand.h"


RemoveObjectCommand::RemoveObjectCommand(std::shared_ptr<GeometryObject> object, ModelOfDocument & model)
{
  m_addObjectCommand = std::make_shared<AddObjectCommand>(object, model);
}

void RemoveObjectCommand::Execute()
{
  m_addObjectCommand->UnExecute();
}

void RemoveObjectCommand::UnExecute()
{
  m_addObjectCommand->Execute();
}
