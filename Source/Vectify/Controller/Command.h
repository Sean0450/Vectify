﻿#pragma once

#include "Model/GeometryObject.h"
#include "Model/ModelOfDocument.h"


////////////////////////////////////////////////////////////////////////////////
//
/*Абстрактный класс команды, записываемой в менеджер событий.*/
//
////////////////////////////////////////////////////////////////////////////////
class Command
{
public:
  //-----------------------------------------------------------------------------
  //Виртуальный деструктор базового класса.
  //--
  virtual ~Command() = default;
  //-----------------------------------------------------------------------------
  //Исполнение функционала команды.
  //--
  virtual void Execute() = 0;
  //-----------------------------------------------------------------------------
  //Отменяет исполнение команды.
  //--
  virtual void UnExecute() = 0;
};