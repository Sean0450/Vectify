#pragma once

#include <string_view>

#include "Model/GeometryObject.h"
#include "Model/GeometryObjectsFactory.h"
#include "Model/ModelOfDocument.h"
#include "Model/Regexpr.h"
#include "Model/Rgba.h"
#include "View/Painter.h"


enum class LineSegmentPoints
{
  startPoint,
  endPoint
};

////////////////////////////////////////////////////////////////////////////////
//
/*Реализация геометрического объекта отрезок. Может быть создан лишь из двух точек,
сохраняет свою начальную и конечную точку в полях.*/
//
////////////////////////////////////////////////////////////////////////////////
class LineSegment : public GeometryObject
{
private:
  ModelOfDocument * m_documentModel;
  Point m_startPoint;
  Point m_endPoint;
  int m_width = 3;
  Rgba m_color;
  static constexpr std::string_view m_objectName = "LineSegment";


public:
  //-----------------------------------------------------------------------------
  //Конструктор, создает объект при наличии начальное и конечной точки, а также модели документа.
  //--
  LineSegment(ModelOfDocument & model, const Point & startPoint, const Point & endPOint);
  virtual std::vector<std::shared_ptr<ControlPoint>> GetControlPoints() override;

  //-----------------------------------------------------------------------------
  //Изменяет начальную точку отрезка.
  //--
  void SetStartPoint(const Point & p);
  //-----------------------------------------------------------------------------
  //Изменяет конечную точку отрезка.
  //--
  void SetEndPoint(const Point & p);
  //-----------------------------------------------------------------------------
  //Сообщает об изменении контрольных точек объекта
  //--
  void ControlPointChanged() const noexcept { m_documentModel->ControlPointChanged(); }

  //-----------------------------------------------------------------------------
  //Получить начальную точку отрезка.
  //--
  Point GetStartPoint() const noexcept { return m_startPoint; };

  //-----------------------------------------------------------------------------
  //Получить конечную точку отрезка
  //--
  Point GetEndPoint() const noexcept { return m_endPoint; };
  virtual bool PointBelongsObject(const Point & p);
  virtual void Render(Painter & painter, RenderType type);
  virtual const std::string ToString() noexcept override
  {
    return std::string(m_objectName) + m_startPoint.ToString() + m_endPoint.ToString();
  }
  //-----------------------------------------------------------------------------
  //Разделяет входную строку на начальную и конечные точки. Возвращает объект отрезка.
  //--
  static std::shared_ptr<GeometryObject> FromString(const std::string & points, ModelOfDocument & model)
  {
    auto it = std::sregex_iterator(points.cbegin(), points.cend(), Regex::pointsSeparation);
    auto startPoint = Point::FromString(it->str());
    it++;
    auto endPoint = Point::FromString(it->str());
    if (startPoint.has_value() and endPoint.has_value())
    {
      return std::make_shared<LineSegment>(model, startPoint.value(), endPoint.value());
    }
    return nullptr;
  }
  //-----------------------------------------------------------------------------
  //Получить имя объекта.
  //--
  static constexpr std::string_view GetObjectName() noexcept { return m_objectName; }
};
