#pragma once

#include "Model/GeometryObjectsFactory.h"


bool GeometryObjectsFactory::RegistFunction(
  const std::string_view name,
  std::function<std::shared_ptr<GeometryObject>(const std::string &, ModelOfDocument &)> function)
{
  assert(!name.empty());
  assert(function);
  assert(!m_functions.contains(name));
  m_functions[name] = std::move(function);
  return true;
}

std::shared_ptr<GeometryObject> GeometryObjectsFactory::CreateObject(const std::string_view name, const std::string & suffix,
                                                                     ModelOfDocument & model)
{
  if (m_functions.find(name) != m_functions.end())
  {
    return m_functions[name](suffix, model);
  }
  return nullptr;
}
