#pragma once

#include "Model/ModelOfDocument.h"


void ModelOfDocument::AddObject(std::shared_ptr<GeometryObject> object)
{
  assert(object != nullptr);
  m_geometryObjects.emplace_back(object);
  m_modelChanged = true;
  if (auto observer = m_observer.lock())
  {
    observer->GeometryObjectCreated(object);
  }
}

void ModelOfDocument::RemoveObject(std::shared_ptr<GeometryObject> object)
{
  std::erase(m_geometryObjects, object);
  m_modelChanged = true;
  if (auto observer = m_observer.lock())
  {
    observer->GeometryObjectDeleted(object);
  }
}

void ModelOfDocument::SetObserver(std::weak_ptr<DocumentModelObserver> observer)
{
  m_observer = std::move(observer);
}

void ModelOfDocument::SetChanged(bool changed)
{
  m_modelChanged = changed;
}

void ModelOfDocument::RenderModel(Painter & painter)
{
  for (auto && it : m_geometryObjects)
  {
    it->Render(painter, RenderType::DefaultRender);
  }
}

void ModelOfDocument::ControlPointChanged()
{
  m_modelChanged = true;
  if (auto observer = m_observer.lock())
  {
    observer->GeometryObjectControlPointChanged();
  }
}

std::shared_ptr<GeometryObject> GetObjectAtPoint(const Point & p, ModelOfDocument & model)
{
  for (auto && it : model.GetObjects())
  {
    if (it->PointBelongsObject(p))
    {
      return it;
    }
  }
  return nullptr;
}
