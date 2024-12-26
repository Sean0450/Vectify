#pragma once

#include "Model/BrokenLine.h"
#include "Model/DrawingConstants.h"


////////////////////////////////////////////////////////////////////////////////
//
/*Класс представляет собой реализацию паттерна строитель, для создания ломанной.
Принимает на вход точки, сохраняет их в вектор, при завершении процесса построения, возвращает объект ломанной.*/
//
////////////////////////////////////////////////////////////////////////////////
class BrokenLineBuilder
{
  std::vector<Point> m_intermediatePoints;
  ModelOfDocument * m_documentModel;
  Point m_phantomPoint;
  int m_width = 3;
  Rgba m_color;

public:
  //-----------------------------------------------------------------------------
  //При создании принимает один параметр - модель документа.
  //--
  BrokenLineBuilder(ModelOfDocument & model);

  //-----------------------------------------------------------------------------
  //Возвращает последнюю точку в векторе.
  //--
  const Point GetLastSavedPoint() const noexcept
  {
    assert(!m_intermediatePoints.empty());
    return m_intermediatePoints.back();
  }

  //-----------------------------------------------------------------------------
  //Проверка на пустоту вектора точек.
  //--
  const bool IsBuilderEmpty() const noexcept { return m_intermediatePoints.empty(); }

  //-----------------------------------------------------------------------------
  //Удалить все точки.
  //--
  void ClearBuilder() noexcept { m_intermediatePoints.clear(); }

  //-----------------------------------------------------------------------------
  //Запоминает положение курсора мыши.
  //--
  void SetPhantomPoint(const Point & p) noexcept { m_phantomPoint = p; }

  //-----------------------------------------------------------------------------
  //Добавляет точку в вектор.
  //--
  void AddPoint(const Point & p);

  //-----------------------------------------------------------------------------
  //Отрисовка промежуточной версии ломанной.
  //--
  void RenderBuilder(Painter & painter, LineTypes linetype);

  //-----------------------------------------------------------------------------
  //Возвращает объект ломанной.
  //--
  std::shared_ptr<BrokenLine> CreateBrokenLine();
};
