﻿#pragma once

#include <QtWidgets>

#include "View/DocumentControlBarObserver.h"
#include "View/Resources.h"


////////////////////////////////////////////////////////////////////////////////
//
/*В классе создаются и размещаются на layout все кнопки для работы с документом.
Список кнопок: Отменить, повторить, сохранить, открыть, создать новый, экспортировать в пиксельное изображение.*/
//
////////////////////////////////////////////////////////////////////////////////
class DocumentControlBar : public QWidget
{
  Q_OBJECT
  QPushButton * m_undo = nullptr;
  QPushButton * m_redo = nullptr;
  QPushButton * m_saveDocument = nullptr;
  QPushButton * m_openDocument = nullptr;
  QPushButton * m_createDocument = nullptr;
  QPushButton * m_exportToBitmap = nullptr;
  std::weak_ptr<DocumentControlBarObserver> m_observer;

public:

//-----------------------------------------------------------------------------
/*
 Конструтор. 
 Создание и размещение всех кнопок для работы с документом, установка параметров отображения кнопок.
 */
//---
  DocumentControlBar(QWidget * parent = nullptr);

//-----------------------------------------------------------------------------
//Устанавливает наблюдателя.
//---
  void SetObserver(std::weak_ptr<DocumentControlBarObserver> observer);

//-----------------------------------------------------------------------------
//Устанавливает параметр отображения кнопок отменить/повторить.
//---
  void SetEnabledUndoRedo(bool undoStatus, bool redoStatus) noexcept
  {
    m_undo->setEnabled(undoStatus);
    m_redo->setEnabled(redoStatus);
  };

//-----------------------------------------------------------------------------
//Устанавливает параметр отображения кнопки сохранить.
//---
  void SetEnabledSaveButton(bool state) noexcept { m_saveDocument->setEnabled(state); }

signals:
//-----------------------------------------------------------------------------
//Сигнал отправлаяется на рабочую область, при нажатии кнопок отменить/повторить.
//---
  void OperationPerformed();
private slots:

//-----------------------------------------------------------------------------
//Сообщает наблюдателю о нажатии кнопки отменить. Отправляет сигнал о нажатии на рабочую область.
//---
  void UndoButtonClicked();

//-----------------------------------------------------------------------------
//Сообщает наблюдателю о нажатии кнопки повторить. Отправляет сигнал о нажатии на рабочую область.
//---
  void RedoButtonClicked();

//-----------------------------------------------------------------------------
//Сообщает наблюдателю о нажатии кнопки создать документ. Отправляет сигнал о нажатии на рабочую область.
//---
  void CreateButtonClicked();

//-----------------------------------------------------------------------------
//Сообщает наблюдателю о нажатии кнопки сохранить.
//---
  void SaveButtonClicked();

//-----------------------------------------------------------------------------
//Сообщает наблюдателю о нажатии кнопки открыть. Отправляет сигнал о нажатии на рабочую область.
//---
  void OpenButtonClicked();

//-----------------------------------------------------------------------------
//Сообщает наблюдателю о нажатии кнопки экспортировать в растровый формат.
//---
  void ExportButtonClicked();
};
