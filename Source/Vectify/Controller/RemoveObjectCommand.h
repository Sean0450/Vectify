#pragma once

#include "COntroller/AddObjectCommand.h"


////////////////////////////////////////////////////////////////////////////////
//
//Команда удаления геометрического объекта из модели. Реализация завязана на добавлении (композиция).
//
////////////////////////////////////////////////////////////////////////////////
class RemoveObjectCommand : public Command
{
  std::shared_ptr<AddObjectCommand> m_addObjectCommand;

public:
  //-----------------------------------------------------------------------------
  //Создает команду на основании объекта и ссылки на модель документа.
  //--
  RemoveObjectCommand(std::shared_ptr<GeometryObject> object, ModelOfDocument & model);
  virtual void Execute() override;
  virtual void UnExecute() override;
};
