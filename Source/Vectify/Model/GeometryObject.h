﻿#pragma once

#include <iostream>
#include <vector>

#include "Model/ControlPoint.h"


///Способы отрисовки объектов.
enum class RenderType
{
  DefaultRender, ///< Классический, сплошная линия
  PhantomRender  ///<Пунктирная линия
};

class Painter;

////////////////////////////////////////////////////////////////////////////////
//
/*Базовый абстрактный класс для реализации всех геометрических объектов*/
//
////////////////////////////////////////////////////////////////////////////////
class GeometryObject
{
public:
  //-----------------------------------------------------------------------------
  //Виртуальный деструктор базового класса.
  //--
  virtual ~GeometryObject() = default;
  //-----------------------------------------------------------------------------
  //Создает и возвращает все контрольные точки обхекта.
  //--
  virtual std::vector<std::shared_ptr<ControlPoint>> GetControlPoints() = 0;
  //-----------------------------------------------------------------------------
  //Проверяет принадлежность точки объекту через подсчеты координат.
  //--
  virtual bool PointBelongsObject(const Point & p) = 0;
  //-----------------------------------------------------------------------------
  //Способ отрисовки геометрического объекта.
  //--
  virtual void Render(Painter & painter, RenderType type) = 0;
  //-----------------------------------------------------------------------------
  //Переводит объект в строку.
  //--
  virtual const std::string ToString() noexcept = 0;
};