#pragma once

#include "View/View.h"

#include "View/DocumentControlBar.h"
#include "View/FiguresToolBar.h"
#include "View/PropertiesToolbar.h"
#include "View/WorkAreaWidget.h"


View::View(QWidget * parent)
  : QMainWindow(parent)
{
  m_ui.setupUi(this);

  auto centralWidget = new QWidget(m_ui.centralWidget);
  auto horizontalLayout = new QHBoxLayout(centralWidget);
  auto verticalLayout = new QVBoxLayout(centralWidget);

  m_doc = new DocumentControlBar(this);
  m_ui.mainToolBar->addWidget(m_doc);

  m_propertiesToolBar = new PropertiesToolBar(this);
  m_ui.mainToolBar->addSeparator();
  m_ui.mainToolBar->addWidget(m_propertiesToolBar);

  m_figuresToolBar = new FiguresToolBar(this);
  verticalLayout->addWidget(m_figuresToolBar);
  verticalLayout->addStretch();

  m_workArea = new WorkAreaWidget(this, *m_doc);
  horizontalLayout->addLayout(verticalLayout);
  horizontalLayout->addWidget(m_workArea, 1);
  centralWidget->setLayout(horizontalLayout);
  setCentralWidget(centralWidget);
}

DocumentControlBar * View::GetDocumentControlBar()
{
  return m_doc;
}

FiguresToolBar * View::GetFiguresToolBar()
{
  return m_figuresToolBar;
}

PropertiesToolBar * View::GetPropertiesToolBar()
{
  return m_propertiesToolBar;
}

WorkAreaWidget * View::GetWorkArea()
{
  return m_workArea;
}

void View::SetNeedRepaint()
{
  m_workArea->SetNeedRepaint();
}

void View::SetEnabledUndoRedo(bool undoStatus, bool redoStatus)
{
  m_doc->SetEnabledUndoRedo(undoStatus, redoStatus);
}

void View::SetEnabledSave(bool state)
{
  m_doc->SetEnabledSaveButton(state);
}

void View::ResetAllButtons()
{
  m_figuresToolBar->UnCheckAllButtons();
}
