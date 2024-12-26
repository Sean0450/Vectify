#pragma once

#include <iostream>
#include <vector>

#include "Controller/Command.h"


////////////////////////////////////////////////////////////////////////////////
//
/*Класс необходим для одновременного хранения нескольких команд на исполнение.
Например, удалвение нескольких выделенных объектов.*/
//
////////////////////////////////////////////////////////////////////////////////
class CommandList : public Command
{
  std::vector<std::shared_ptr<Command>> m_commands;

public:
  //-----------------------------------------------------------------------------
  //Добавление новой команды в список.
  //--
  void AddCommand(std::shared_ptr<Command>);
  virtual void Execute();
  virtual void UnExecute();
};
