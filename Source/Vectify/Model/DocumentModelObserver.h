﻿#pragma once

#include "Model/GeometryObject.h"


////////////////////////////////////////////////////////////////////////////////
//
//Наблюдатель за изменениями в модели документа.
//
////////////////////////////////////////////////////////////////////////////////
class DocumentModelObserver
{
public:
  //-----------------------------------------------------------------------------
  //Виртуальный деструктор абстрактного класса.
  //--
  virtual ~DocumentModelObserver() = default;
  //-----------------------------------------------------------------------------
  //Уведомляет контроллер о создании нового объекта.
  //--
  virtual void GeometryObjectCreated(std::shared_ptr<GeometryObject> object) = 0;

  //-----------------------------------------------------------------------------
  //Уведомляет контроллер об удалении объекта.
  //--
  virtual void GeometryObjectDeleted(std::shared_ptr<GeometryObject> object) = 0;

  //-----------------------------------------------------------------------------
  //Уведомляет контроллер об изменении контрольных точек объекта.
  //--
  virtual void GeometryObjectControlPointChanged() = 0;
};