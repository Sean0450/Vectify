#pragma once

#include <ranges>

#include <assert.h>

#include "Model/GeometryObject.h"
#include "Model/GeometryObjectsFactory.h"
#include "Model/ModelOfDocument.h"
#include "Model/Rgba.h"
#include "View/Painter.h"


////////////////////////////////////////////////////////////////////////////////
//
/*Реализация геометрического объекта "ломанная". Точки ломанной хранятся в векторе.
В классе реализованы методы работы с точками и метод чтения строки из файла.*/
//
////////////////////////////////////////////////////////////////////////////////
class BrokenLine : public GeometryObject
{
  std::vector<Point> m_points;
  ModelOfDocument * m_documentModel;
  int m_width = 3;
  Rgba m_color;
  static constexpr std::string_view m_objectName = "BrokenLine";

public:
  //-----------------------------------------------------------------------------
  //Конструктор, принимает набор точек и ссылку модель документа.
  //--
  BrokenLine(ModelOfDocument & model, const std::vector<Point> & points);
  virtual std::vector<std::shared_ptr<ControlPoint>> GetControlPoints() override;
  virtual bool PointBelongsObject(const Point & p) override;
  virtual void Render(Painter & painter, RenderType type) override;
  virtual const std::string ToString() noexcept override
  {
    std::string string = std::string(m_objectName);
    for (auto && it : m_points)
    {
      string += it.ToString();
    }
    return string;
  };

  //-----------------------------------------------------------------------------
  //Сообщает об изменении контрольных точек объекта
  //--
  void ControlPointChanged() const noexcept { m_documentModel->ControlPointChanged(); }
  //-----------------------------------------------------------------------------
  //Возвращает точку из вектора по индексу.
  //--
  Point GetPoint(int index) const;
  //-----------------------------------------------------------------------------
  //Устанавливае точку по индексу.
  //--
  void SetPoint(const Point & p, int index);
  //-----------------------------------------------------------------------------
  //Получить имя объекта.
  //--
  static constexpr std::string_view GetObjectName() noexcept { return m_objectName; }
  //-----------------------------------------------------------------------------
  //Разделяет входную строку на наборы точек и возвращает объект ломанной.
  //--
  static std::shared_ptr<GeometryObject> FromString(const std::string & points, ModelOfDocument & model)
  {
    std::vector<Point> brokenLinePoints;
    for (auto it = std::sregex_iterator(points.cbegin(), points.cend(), Regex::pointsSeparation); it != std::sregex_iterator();
         ++it)
    {
      auto point = Point::FromString(it->str());
      if (point.has_value())
      {
        brokenLinePoints.emplace_back(point.value());
      }
    }
    if (!brokenLinePoints.empty())
    {
      return std::make_shared<BrokenLine>(model, brokenLinePoints);
    }
    return nullptr;
  }
};
