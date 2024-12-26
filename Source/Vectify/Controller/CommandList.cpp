#pragma once

#include "Controller/CommandsList.h"


void CommandList::Execute()
{
  for (auto && it : m_commands)
  {
    it->Execute();
  }
}

void CommandList::UnExecute()
{
  for (auto && it : m_commands)
  {
    it->UnExecute();
  }
}

void CommandList::AddCommand(std::shared_ptr<Command> command)
{
  m_commands.emplace_back(command);
}
