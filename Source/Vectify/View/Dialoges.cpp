#pragma once

#include "View/Dialoges.h"

//-----------------------------------------------------------------------------
//Отображает диалог для сохранения файла на запись.
//---
const std::string Dialoges::SelectFileDialoge()
{
  auto path = QFileDialog::getSaveFileName(0, "Save Document", "Doc", "*.txt");
  if (!path.isEmpty())
  {
    return std::string(path.toLocal8Bit());
  }
  return "";
}

//-----------------------------------------------------------------------------
//Отображает диалог для выбора файла на чтение.
//---
const std::string Dialoges::OpenFileDialoge()
{
  auto path = QFileDialog::getOpenFileName(0, "Save Document");
  if (!path.isEmpty())
  {
    return std::string(path.toLocal8Bit());
  }
  return "";
}

//-----------------------------------------------------------------------------
//Выводит сообщение об ошибке чтения файла.
//---
void Dialoges::ShowBrokenFileMessage()
{
  QMessageBox * messageBox = new QMessageBox(0);
  messageBox->setText(QString::fromStdString("File was broken, not all objects were readed"));
  messageBox->exec();
}

//-----------------------------------------------------------------------------
//Выводит сообщение о ненайденном файле.
//---
void Dialoges::ShowFileNotFound(const std::string & path)
{
  QMessageBox * messageBox = new QMessageBox(0);
  messageBox->setText(QString::fromStdString("File by this path: " + path + " can't be opened"));
  messageBox->exec();
}
