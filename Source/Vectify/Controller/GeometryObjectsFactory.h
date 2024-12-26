#pragma once

#include <functional>
#include <map>
#include <regex>

#include <assert.h>

#include "GeometryObject.h"
#include "ModelOfDocument.h"

struct GeometryObjectsFactory
{
  static GeometryObjectsFactory & get()
  {
    static GeometryObjectsFactory object;
    return object;
  }
  bool RegistFunction(
    const std::string_view name,
    std::function<std::shared_ptr<GeometryObject>(const std::string &, ModelOfDocument &)> function);
  std::shared_ptr<GeometryObject> CreateObject(const std::string_view name, const std::string & suffix, ModelOfDocument & model);

private:
  std::map<std::string_view, std::function<std::shared_ptr<GeometryObject>(const std::string &, ModelOfDocument &)>>
    m_functions;
};
