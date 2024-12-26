#pragma once

#include "Model/Document.h"


void Document::Save()
{
  if (m_path.empty())
  {
    m_path = Dialoges::SelectFileDialoge();
  }
  std::ofstream outFile(m_path);
  if (outFile.is_open())
  {
    for (auto && it : m_modelOfDocument.GetObjects())
    {
      outFile << it->ToString() << std::endl;
    }
    outFile.close();
  }
  else
  {
    Dialoges::ShowFileNotFound(m_path);
    m_path.clear();
  }
  m_modelOfDocument.SetChanged(false);
}
