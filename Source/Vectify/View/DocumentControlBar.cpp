#pragma once

#include "View/DocumentControlBar.h"


DocumentControlBar::DocumentControlBar(QWidget * parent)
  : QWidget(parent)
{
  QHBoxLayout * toplayout = new QHBoxLayout(this);

  m_createDocument = new QPushButton(this);
  m_createDocument->setIcon(style()->standardIcon(QStyle::SP_FileIcon));
  m_createDocument->setToolTip(resources::createDocumentToolTip);
  QObject::connect(m_createDocument, &QPushButton::clicked, this, &DocumentControlBar::CreateButtonClicked);
  toplayout->addWidget(m_createDocument);

  m_saveDocument = new QPushButton(this);
  m_saveDocument->setIcon(style()->standardIcon(QStyle::SP_DialogSaveButton));
  m_saveDocument->setToolTip(resources::saveDocumentToolTip);
  QObject::connect(m_saveDocument, &QPushButton::clicked, this, &DocumentControlBar::SaveButtonClicked);
  m_saveDocument->setEnabled(false);
  toplayout->addWidget(m_saveDocument);

  m_openDocument = new QPushButton(this);
  m_openDocument->setIcon(style()->standardIcon(QStyle::SP_DriveHDIcon));
  m_openDocument->setToolTip(resources::openDocumentToolTip);
  QObject::connect(m_openDocument, &QPushButton::clicked, this, &DocumentControlBar::OpenButtonClicked);
  toplayout->addWidget(m_openDocument);

  m_exportToBitmap = new QPushButton(this);
  m_exportToBitmap->setIcon(style()->standardIcon(QStyle::SP_DialogResetButton));
  m_exportToBitmap->setToolTip(resources::exportToBitmapToolTip);
  QObject::connect(m_exportToBitmap, &QPushButton::clicked, this, &DocumentControlBar::ExportButtonClicked);
  toplayout->addWidget(m_exportToBitmap);

  // Реализация не будет добавлена
  m_exportToBitmap->setEnabled(false);

  m_undo = new QPushButton(this);
  m_undo->setIcon(style()->standardIcon(QStyle::SP_ArrowBack));
  m_undo->setToolTip(resources::undoToolTip);
  QObject::connect(m_undo, &QPushButton::clicked, this, &DocumentControlBar::UndoButtonClicked);
  m_undo->setEnabled(false);
  toplayout->addWidget(m_undo);

  m_redo = new QPushButton(this);
  m_redo->setIcon(style()->standardIcon(QStyle::SP_ArrowForward));
  m_redo->setToolTip(resources::doToolTip);
  QObject::connect(m_redo, &QPushButton::clicked, this, &DocumentControlBar::RedoButtonClicked);
  m_redo->setEnabled(false);
  toplayout->addWidget(m_redo);
}

void DocumentControlBar::SetObserver(std::weak_ptr<DocumentControlBarObserver> observer)
{
  m_observer = std::move(observer);
}


void DocumentControlBar::CreateButtonClicked()
{
  if (auto observer = m_observer.lock())
  {
    observer->OnCreateDocumentButtonClicked();
    emit OperationPerformed();
  }
}

void DocumentControlBar::SaveButtonClicked()
{
  if (auto observer = m_observer.lock())
  {
    observer->OnSaveDocumentButtonClicked();
  }
}

void DocumentControlBar::OpenButtonClicked()
{
  if (auto observer = m_observer.lock())
  {
    observer->OnLoadDocumentButtonClicked();
    emit OperationPerformed();
  }
}

void DocumentControlBar::ExportButtonClicked()
{
  if (auto observer = m_observer.lock())
  {
    observer->OnExportButtonClicked();
  }
}

void DocumentControlBar::UndoButtonClicked()
{
  if (auto observer = m_observer.lock())
  {
    observer->OnUndoButtonClicked();
    emit OperationPerformed();
  }
}

void DocumentControlBar::RedoButtonClicked()
{
  if (auto observer = m_observer.lock())
  {
    observer->OnRedoButtonClicked();
    emit OperationPerformed();
  }
}
