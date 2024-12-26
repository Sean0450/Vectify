#pragma once

#include <regex>

/// Определяем регулярные выражения для разбиения строчек файла на составные части объекта.
namespace Regex
{
static const std::regex objectNameSeparation("\\s"); ///<Разделяет строку на имя объекта и набор точек
static const std::regex pointsSeparation("\\{-?\\d+(\\.\\d+)?..\\d+(\\.\\d+)?\\}"); ///<Разделяет строку из набора точек на точки
static const std::regex pointsValuesSeparation("-?\\d+(\\.\\d+)?"); ///<Разделяет точку на координаты Х, У
} // namespace Regex
