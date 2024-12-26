#pragma once

#include "Controller/UndoRedo.h"


void UndoRedo::AddCommand(std::shared_ptr<Command> command)
{
  m_undo.emplace_back(command);
  m_redo.clear();
  command->Execute();
}

void UndoRedo::Undo()
{
  if (!m_undo.empty())
  {
    auto command = std::move(m_undo.back());
    m_undo.pop_back();
    m_redo.emplace_back(command);
    command->UnExecute();
  }
}

void UndoRedo::Redo()
{
  if (!m_redo.empty())
  {
    auto command = std::move(m_redo.back());
    m_redo.pop_back();
    m_undo.emplace_back(command);
    command->Execute();
  }
}
