﻿#pragma once

#include <fstream>
#include <iostream>
#include <regex>

#include "ModelOfDocument.h"
#include "View/Dialoges.h"

////////////////////////////////////////////////////////////////////////////////
//
/*В классе документа содержится путь к файлу, скоторым пользователь работает в данный момент, 
содержится модель документа, хранящая в себе все созданные объекты.*/
//
////////////////////////////////////////////////////////////////////////////////
class Document
{
  std::string m_path;
  ModelOfDocument m_modelOfDocument;

public:
  //-----------------------------------------------------------------------------
  //Сохраняет данные из модели в файл. Если не удалось - выводит диалог с текстом ошибки.
  //--
  void Save();

  //-----------------------------------------------------------------------------
  //Получить модель документа.
  //--
  ModelOfDocument & GetModelOfDocument() noexcept { return m_modelOfDocument; };

  //-----------------------------------------------------------------------------
  //Получить путь к файлу.
  //--
  const std::string & GetPath() const noexcept { return m_path; }

    //-----------------------------------------------------------------------------
  //Установить путь к файлу.
  //--
  void SetPath(const std::string & path) noexcept { m_path = std::move(path); }
};
