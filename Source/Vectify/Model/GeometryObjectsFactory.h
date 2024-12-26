#pragma once

#include <functional>
#include <map>
#include <regex>

#include <assert.h>

#include "Model/GeometryObject.h"
#include "Model/ModelOfDocument.h"


////////////////////////////////////////////////////////////////////////////////
//
/// Фабрика для создания геометрических объектов при чтении их из файла.
//
////////////////////////////////////////////////////////////////////////////////
struct GeometryObjectsFactory
{
  //-----------------------------------------------------------------------------
  //Создает статический объект для последующего обращения к нему при производстве геометрических объектов.
  //--
  static GeometryObjectsFactory & get()
  {
    static GeometryObjectsFactory object;
    return object;
  }

  //-----------------------------------------------------------------------------
  //Записывает функции для создания геометрических объектов в map, ключом служит название создаваемого функцикй объекта.
  //--
  bool RegistFunction(const std::string_view name,
                      std::function<std::shared_ptr<GeometryObject>(const std::string &, ModelOfDocument &)> function);

  //-----------------------------------------------------------------------------
  //Примает на вход строку и в зависимости от значения вызывает нужную функцию из map.
  //--
  std::shared_ptr<GeometryObject> CreateObject(const std::string_view name, const std::string & suffix, ModelOfDocument & model);

private:
  std::map<std::string_view, std::function<std::shared_ptr<GeometryObject>(const std::string &, ModelOfDocument &)>> m_functions;
};
