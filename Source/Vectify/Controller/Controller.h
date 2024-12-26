#pragma once

#include <vector>

#include "Controller/BrokenLineDrawingProcess.h"
#include "Controller/DefaultProcess.h"
#include "Controller/LineSegmentDrawingProcess.h"
#include "Model/Document.h"
#include "Model/DocumentModelObserver.h"
#include "Model/Regexpr.h"
#include "View/DocumentControlBarObserver.h"
#include "View/FiguresToolBarObserver.h"
#include "View/PropertiesToolBarObserver.h"
#include "View/View.h"
#include "View/WorkAreaWidgetObserver.h"


////////////////////////////////////////////////////////////////////////////////
//
/*Основной класс для связи не взаимодействующих друг с другом частей программы.
За счет наследования получает события из view части, обрабатывает, сохраняет 
результат в модельную часть. Обработка событий осуществляется за счет процессов.*/
//
////////////////////////////////////////////////////////////////////////////////
class Controller : public std::enable_shared_from_this<Controller>,
                   public DocumentControlBarObserver,
                   public PropertiesToolBarObserver,
                   public FiguresToolBarObserver,
                   public WorkAreaWidgetObserver,
                   public DocumentModelObserver
{
  //-----------------------------------------------------------------------------
  //Благодаря этой структуре создание объекта контроллера не через метод Create становится невозможным.
  //--
  struct Private
  {
    explicit Private() = default;
  };
  std::shared_ptr<View> m_view;
  std::shared_ptr<Document> m_document;
  std::unique_ptr<Process> m_activeProcess;
  UndoRedo m_undoRedoManager;

public:
  //-----------------------------------------------------------------------------
  //Конструктор контроллера из Private структуры и указателя на view.
  //--
  Controller(Private, std::shared_ptr<View> view);

  //-----------------------------------------------------------------------------
  //Основная функция создания объектов контроллера.
  //--
  static std::shared_ptr<Controller> Create(std::shared_ptr<View> view);

  virtual void OnLineSegmentClicked() override;
  virtual void OnBrokenLineClicked() override;
  virtual void OnCentralPointRectangleClicked() override;
  virtual void OnAnglesRectangleClicked() override;
  virtual void OnDefaultProcess() override;
  virtual void RenderEvent(Painter & painter) override;

  virtual void OnCreateDocumentButtonClicked() override;
  virtual void OnSaveDocumentButtonClicked() override;
  virtual void OnLoadDocumentButtonClicked() override;
  virtual void OnExportButtonClicked() override;
  virtual void OnUndoButtonClicked() override;
  virtual void OnRedoButtonClicked() override;

  virtual void OnSelectSolidLineButtonClicked() override;
  virtual void OnSelectDasheLineButtonClicked() override;
  virtual void OnSetDefaultPropertiesButtonClicked() override;

  virtual void OnMouseMove(const Point & p) override;
  virtual void OnMousePressed(const Point & p) override;
  virtual void OnMouseReleased(const Point & p) override;
  virtual void OnKeyPressed(Button button) override;
  virtual void OnWheelMove() override;

  virtual void GeometryObjectCreated(std::shared_ptr<GeometryObject> object) override;
  virtual void GeometryObjectDeleted(std::shared_ptr<GeometryObject> object) override;
  virtual void GeometryObjectControlPointChanged() override;
};
