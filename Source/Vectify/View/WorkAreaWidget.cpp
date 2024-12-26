#pragma once

#include "View/WorkAreaWidget.h"


WorkAreaWidget::WorkAreaWidget(QWidget * parent, DocumentControlBar & toolBar)
  : QWidget(parent)
{
  m_mouseMoveState = &m_defaultState;

  //TODO Сделать InputEvent от View к Controller, чтобы правильно настроить взамодействие между всеми частями приложения!
  QObject::connect(&toolBar, &DocumentControlBar::OperationPerformed, this, &WorkAreaWidget::PostEventProcessing);
  setFocusPolicy(Qt::StrongFocus);
}

void WorkAreaWidget::SetObserver(std::weak_ptr<WorkAreaWidgetObserver> observer)
{
  m_observer = std::move(observer);
}

void WorkAreaWidget::paintEvent(QPaintEvent * pEvent)
{
  QPainter m_painter(this);
  m_painter.translate(m_viewPort.GetScale() * m_viewPort.Getdx() - m_previousTranslate.x(),
                      m_viewPort.GetScale() * m_viewPort.Getdy() - m_previousTranslate.y());

  //Необходимо запоминать предыдущее значение translate, для правильного отображения точек на рабочей области
  m_previousTranslate.setX(m_viewPort.Getdx());
  m_previousTranslate.setY(m_viewPort.Getdy());
  Painter myPainter(m_painter, m_viewPort);
  if (auto observer = m_observer.lock())
  {
    observer->RenderEvent(myPainter);
  }
}

void WorkAreaWidget::mouseMoveEvent(QMouseEvent * mouseEvent)
{
  m_mouseMoveState->MouseMove(*this, mouseEvent->pos());
  repaint();
  QWidget::mouseMoveEvent(mouseEvent);
}

void WorkAreaWidget::mousePressEvent(QMouseEvent * mouseEvent)
{
  if (mouseEvent->buttons() == Qt::RightButton)
  {
    m_mouseMoveState = &m_moveViewPortState;
    m_moveViewPortState.SetPrevious(mouseEvent->pos());
  }
  else
  {
    m_mouseMoveState = &m_defaultState;
  }
  if (auto observer = m_observer.lock())
  {
    observer->OnMousePressed(m_viewPort.ToModel(mouseEvent->pos()));
    PostEventProcessing();
  }
  QWidget::mousePressEvent(mouseEvent);
}

void WorkAreaWidget::mouseReleaseEvent(QMouseEvent * mouseEvent)
{
  m_mouseMoveState = &m_defaultState;
  if (auto observer = m_observer.lock())
  {
    observer->OnMouseReleased(m_viewPort.ToModel(mouseEvent->pos()));
    PostEventProcessing();
  }
  QWidget::mouseReleaseEvent(mouseEvent);
}

void WorkAreaWidget::keyPressEvent(QKeyEvent * keyEvent)
{
  std::optional<Button> m_clickedButton;
  switch (keyEvent->key())
  {
    case Qt::Key_Delete:
    {
      m_clickedButton = Button::Delete;
      break;
    }
    case Qt::Key_Escape:
    {
      m_clickedButton = Button::Esc;
      break;
    }
    case Qt::Key_Return:
    {
      m_clickedButton = Button::Enter;
      break;
    }
    default:
      break;
  }
  auto observer = m_observer.lock();
  if (observer != nullptr && m_clickedButton.has_value())
  {
    observer->OnKeyPressed(m_clickedButton.value());
  }
  QWidget::keyPressEvent(keyEvent);
  PostEventProcessing();
}

void WorkAreaWidget::wheelEvent(QWheelEvent * wheelMoveEvent)
{
  double previousScale = m_viewPort.GetScale();
  if (wheelMoveEvent->angleDelta().y() != 0)
  {
    if (wheelMoveEvent->angleDelta().y() < 0)
    {
      m_viewPort.ZoomIn();
    }
    else
    {
      m_viewPort.ZoomOut();
    }
  }

  //Трансформация координат для плавного масштабирования при движении колесика мышки
  double dx = wheelMoveEvent->position().x() * (1.0 / previousScale - 1.0 / m_viewPort.GetScale());
  double dy = wheelMoveEvent->position().y() * (1.0 / previousScale - 1.0 / m_viewPort.GetScale());
  m_viewPort.Setdx(m_viewPort.Getdx() + dx);
  m_viewPort.Setdy(m_viewPort.Getdy() + dy);
  if (auto observer = m_observer.lock())
  {
    observer->OnWheelMove();
    repaint();
  }
  QWidget::wheelEvent(wheelMoveEvent);
}

void WorkAreaWidget::SetNeedRepaint()
{
  m_needRepaint = true;
}

void WorkAreaWidget::PostEventProcessing()
{
  if (m_needRepaint)
  {
    repaint();
    m_needRepaint = false;
  }
}

void WorkAreaWidget::ViewPortMoveState::MouseMove(WorkAreaWidget & workArea, QPoint position)
{
  double dx = position.x() - m_lastClickedPosition.x();
  double dy = position.y() - m_lastClickedPosition.y();
  workArea.m_viewPort.Setdx(workArea.m_viewPort.Getdx() - dx * workArea.m_viewPort.GetScale());
  workArea.m_viewPort.Setdy(workArea.m_viewPort.Getdy() - dy * workArea.m_viewPort.GetScale());
  m_lastClickedPosition = position;
}

void WorkAreaWidget::ViewPortMoveState::SetPrevious(const QPoint & point)
{
  m_lastClickedPosition = point;
}

void WorkAreaWidget::DefaultState::MouseMove(WorkAreaWidget & workArea, QPoint position)
{
  if (auto observer = workArea.m_observer.lock())
  {
    observer->OnMouseMove(workArea.m_viewPort.ToModel(position));
  }
}
