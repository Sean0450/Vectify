﻿#pragma once

#include <algorithm>
#include <iostream>
#include <vector>

#include <assert.h>

#include "Model/DocumentModelObserver.h"
#include "Model/GeometryObject.h"


////////////////////////////////////////////////////////////////////////////////
//
/*В классе документа содержатся все созданные объекты, а также наблюдатель за моделью.
Реализованы функции для работы с вектором обхектов: добавить, удалить, изменить, проверить на пустоту.
При изменении в модели документа, возмодится флаг, который позднее используется в контроллере.*/
//
////////////////////////////////////////////////////////////////////////////////
class ModelOfDocument
{
  std::vector<std::shared_ptr<GeometryObject>> m_geometryObjects;
  std::weak_ptr<DocumentModelObserver> m_observer;
  bool m_modelChanged = false;

public:
  //-----------------------------------------------------------------------------
  //Добавляем новый объект в модель.
  //--
  void AddObject(std::shared_ptr<GeometryObject> object);

  //-----------------------------------------------------------------------------
  //Удаляем конкретный объект из модели.
  //--
  void RemoveObject(std::shared_ptr<GeometryObject> object);

  //-----------------------------------------------------------------------------
  //Устанавливаем наблюдателя за моделью.
  //--
  void SetObserver(std::weak_ptr<DocumentModelObserver> observer);

  //-----------------------------------------------------------------------------
  //Уведомлляем контроллера об изменении одного из объектов модели.
  //--
  void ControlPointChanged();

  //-----------------------------------------------------------------------------
  //Устанавливаем значение флага.
  //--
  void SetChanged(bool changed);

  //-----------------------------------------------------------------------------
  //Отрисовка модели. Вызываем конкретную реализацию метода render для каждого объекта.
  //--
  void RenderModel(Painter & painter);

  //-----------------------------------------------------------------------------
  //Проверяем, изменилась модель или нет.
  //--
  bool Changed() const noexcept { return m_modelChanged; };

  //-----------------------------------------------------------------------------
  //Получаем все объекты из модели.
  //--
  const std::vector<std::shared_ptr<GeometryObject>> & GetObjects() const noexcept { return m_geometryObjects; }

  //-----------------------------------------------------------------------------
  //Проверяем: пустая ли модель?
  //--
  bool Empty() const noexcept { return m_geometryObjects.empty(); }
};

//-----------------------------------------------------------------------------
//Свободная функция, проверяющая, находится ли на кликнутой области объект из модели.
//--
std::shared_ptr<GeometryObject> GetObjectAtPoint(const Point & p, ModelOfDocument & model);
