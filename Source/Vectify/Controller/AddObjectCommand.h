#pragma once

#include "Controller/Command.h"


////////////////////////////////////////////////////////////////////////////////
//
//Команда добавления геометрического объекта в модель. Запоминает добавляемый объект.
//
////////////////////////////////////////////////////////////////////////////////
class AddObjectCommand : public Command
{
private:
  std::shared_ptr<GeometryObject> m_object;
  ModelOfDocument * m_documentModel;

public:
  //-----------------------------------------------------------------------------
  //Создает команду на основании объекта и ссылки на модель документа.
  //--
  AddObjectCommand(std::shared_ptr<GeometryObject> object, ModelOfDocument & model);
  virtual void Execute() override;
  virtual void UnExecute() override;
};
