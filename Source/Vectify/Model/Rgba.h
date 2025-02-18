﻿#pragma once

#include <stdint.h>


////////////////////////////////////////////////////////////////////////////////
//
/*Реализация цвета в системе RGB. Используется для сохранения цвета геомертического
объекта в модели.*/
//
////////////////////////////////////////////////////////////////////////////////
class Rgba
{
public:
  //-----------------------------------------------------------------------------
  //Конструктор по умолчанию.
  //--
  constexpr Rgba() noexcept = default;

  //-----------------------------------------------------------------------------
  //Конструктор, принимает значения цветов в диапазоне [0-255]
  //--
  constexpr Rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a) noexcept
    : m_red(r)
    , m_green(g)
    , m_blue(b)
    , m_alpha(a){};
  //-----------------------------------------------------------------------------
  //Получить значение красного.
  //--
  constexpr uint8_t red() const noexcept { return m_red; };
  //-----------------------------------------------------------------------------
  //Получить значение зеленого.
  //--
  constexpr uint8_t green() const noexcept { return m_green; };

  //-----------------------------------------------------------------------------
  //Получить значение голубого.
  //--
  constexpr uint8_t blue() const noexcept { return m_blue; };

  //-----------------------------------------------------------------------------
  //Получить коэффициент прозрачности.
  //--
  constexpr uint8_t alpha() const noexcept { return m_alpha; };

private:
  uint8_t m_red = 0x00;
  uint8_t m_green = 0x00;
  uint8_t m_blue = 0x00;
  uint8_t m_alpha = 0xFF;
};
