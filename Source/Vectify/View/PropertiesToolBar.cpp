#pragma once

#include <View/PropertiesToolbar.h>


PropertiesToolBar::PropertiesToolBar(QWidget * parent)
  : QWidget(parent)
{
  QHBoxLayout * verticallayout = new QHBoxLayout(this);

  m_openColorsPanelButton = new QPushButton(this);
  m_openColorsPanelButton->setText(resources::selectColorLabel);
  QObject::connect(m_openColorsPanelButton, &QPushButton::clicked, this, &PropertiesToolBar::OpenColorsPanel);
  // m_openColorsPanelButton->setEnabled(false);
  verticallayout->addWidget(m_openColorsPanelButton);

  m_lineStyle = new QPushButton(this);
  //TODO Add m_lineStyle icons
  m_lineStyle->setText(resources::selectStyleLabel);
  m_styleMenu = new QMenu(m_lineStyle);

  QAction * addSolidLine = new QAction(m_styleMenu);
  addSolidLine->setText(resources::solidLineSegment);
  addSolidLine->setCheckable(true);
  m_styleMenu->addAction(addSolidLine);

  QAction * addDasheLine = new QAction(m_styleMenu);
  addDasheLine->setText(resources::dashLineSegment);
  addDasheLine->setCheckable(true);
  m_styleMenu->addAction(addDasheLine);

  m_lineStyle->setMenu(m_styleMenu);
  m_lineStyle->setEnabled(false);
  QObject::connect(addSolidLine, &QAction::triggered, this,
                   [this, addDasheLine] { PropertiesToolBar::SelectSolidLine(addDasheLine); });
  QObject::connect(addDasheLine, &QAction::triggered, this,
                   [this, addSolidLine] { PropertiesToolBar::SelectDasheLine(addSolidLine); });
  verticallayout->addWidget(m_lineStyle);

  QHBoxLayout * horizontallayout = new QHBoxLayout(this);
  QLabel * widthLabel = new QLabel(resources::setWidthLabel);
  m_widthLineEdit = new QLineEdit(this);
  m_widthLineEdit->setEnabled(false);
  QObject::connect(m_widthLineEdit, &QLineEdit::textChanged, this, &PropertiesToolBar::SetNewWidth);
  widthLabel->setBuddy(m_widthLineEdit);
  horizontallayout->addWidget(widthLabel);
  horizontallayout->addWidget(m_widthLineEdit);
  verticallayout->addLayout(horizontallayout);

  m_setBaseProperties = new QPushButton(this);
  m_setBaseProperties->setText(resources::defaultProperties);
  QObject::connect(m_setBaseProperties, &QPushButton::clicked, this, &PropertiesToolBar::OnDefaltPropertiesButtonClicked);
  m_setBaseProperties->setEnabled(false);
  verticallayout->addWidget(m_setBaseProperties);
  verticallayout->addStretch(1);
}

void PropertiesToolBar::SetObserver(std::weak_ptr<PropertiesToolBarObserver> observer)
{
  m_observer = std::move(observer);
}

void PropertiesToolBar::OpenColorsPanel()
{
  QColorDialog colorPanel(this);
  colorPanel.exec();
}

void PropertiesToolBar::SelectSolidLine(QAction * action)
{
  action->setChecked(false);
  if (auto observer = m_observer.lock())
  {
    observer->OnSelectSolidLineButtonClicked();
  }
}

void PropertiesToolBar::SelectDasheLine(QAction * action)
{
  action->setChecked(false);
  if (auto observer = m_observer.lock())
  {
    observer->OnSelectDasheLineButtonClicked();
  }
}

void PropertiesToolBar::SetNewWidth()
{
}

void PropertiesToolBar::OnDefaltPropertiesButtonClicked()
{
  if (auto observer = m_observer.lock())
  {
    observer->OnSetDefaultPropertiesButtonClicked();
  }
}
