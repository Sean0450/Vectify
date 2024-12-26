#pragma once

#include <QtWidgets>


/*В пространстве имен определены функции диалогов для обработки следующих событий :
Выбор каталога сохранения документа, выбор каталога загрузки документа, вывод сообщения о битых файлах, вывод сообщения о ненайденном файле.
*/
namespace Dialoges
{
const std::string SelectFileDialoge();
const std::string OpenFileDialoge();
void ShowBrokenFileMessage();
void ShowFileNotFound(const std::string & path);
} // namespace Dialoges
