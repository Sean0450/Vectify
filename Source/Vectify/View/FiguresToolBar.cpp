#pragma once

#include "View/FiguresToolBar.h"

FiguresToolBar::FiguresToolBar(QWidget * parent)
  : QWidget(parent)
{
  QVBoxLayout * verticalLayout = new QVBoxLayout(this);
  m_lineSegment = new QPushButton(this);
  m_lineSegment->setIcon(style()->standardIcon(QStyle::SP_TitleBarMinButton));
  //TODO Add LineSegment Icon
  m_lineSegment->setToolTip(resources::lineSegmentName);
  m_lineSegment->setCheckable(true);
  QObject::connect(m_lineSegment, &QPushButton::clicked, this, &FiguresToolBar::SelectLineSegment);
  verticalLayout->addWidget(m_lineSegment);

  m_brokenLine = new QPushButton(this);
  m_brokenLine->setIcon(style()->standardIcon(QStyle::SP_DialogCloseButton));
  // TODO Add BrokenLine Icon
  m_brokenLine->setToolTip(resources::brokenLineName);
  m_brokenLine->setCheckable(true);
  QObject::connect(m_brokenLine, &QPushButton::clicked, this, &FiguresToolBar::SelectBrokenLine);
  verticalLayout->addWidget(m_brokenLine);

  m_rectangle = new QPushButton(this);
  m_rectMenu = new QMenu(m_rectangle);
  m_rectMenu->addAction(resources::rectangleByCenter)->setCheckable(true);
  m_rectMenu->addAction(resources::rectangleByTwoAngles)->setCheckable(true);
  m_rectangle->setIcon(style()->standardIcon(QStyle::SP_DesktopIcon));
  //TODO Add Rectangle Icon
  m_rectangle->setToolTip(resources::rectangleName);
  m_rectangle->setMenu(m_rectMenu);
  m_rectangle->setEnabled(false);
  QObject::connect(m_rectMenu->actions().at(0), &QAction::triggered, this, &FiguresToolBar::SelectRectangleDrawbyCenter);
  QObject::connect(m_rectMenu->actions().at(1), &QAction::triggered, this, &FiguresToolBar::SelectRectangleDrawbyAngles);
  verticalLayout->addWidget(m_rectangle);
}

void FiguresToolBar::SetObserver(std::weak_ptr<FiguresToolBarObserver> observer)
{
  m_observer = std::move(observer);
}

void FiguresToolBar::SelectLineSegment(bool checked)
{
  if (checked)
  {
    UnCheckAllButtons();
    m_lineSegment->setChecked(true);
    if (auto observer = m_observer.lock())
    {
      observer->OnLineSegmentClicked();
    }
  }
  else
  {
    SelectDefaultProcess();
  }
}

void FiguresToolBar::SelectBrokenLine(bool checked)
{
  if (checked)
  {
    UnCheckAllButtons();
    m_brokenLine->setChecked(true);
    if (auto observer = m_observer.lock())
    {
      observer->OnBrokenLineClicked();
    }
  }
  else
  {
    SelectDefaultProcess();
  }
}

void FiguresToolBar::SelectRectangleDrawbyCenter(bool checked)
{
  if (checked)
  {
    UnCheckAllButtons();
    m_rectMenu->actions().at(0)->setChecked(true);
    if (auto observer = m_observer.lock())
    {
      observer->OnCentralPointRectangleClicked();
    }
  }
  else
  {
    SelectDefaultProcess();
  }
}

void FiguresToolBar::SelectRectangleDrawbyAngles(bool checked)
{
  if (checked)
  {
    UnCheckAllButtons();
    m_rectMenu->actions().at(1)->setChecked(true);
    if (auto observer = m_observer.lock())
    {
      observer->OnAnglesRectangleClicked();
    }
  }
  else
  {
    SelectDefaultProcess();
  }
}

void FiguresToolBar::UnCheckAllButtons()
{
  m_lineSegment->setChecked(false);
  m_brokenLine->setChecked(false);
  m_rectMenu->actions().at(0)->setChecked(false);
  m_rectMenu->actions().at(1)->setChecked(false);
}

void FiguresToolBar::SelectDefaultProcess()
{
  if (auto observer = m_observer.lock())
  {
    observer->OnDefaultProcess();
  }
}
