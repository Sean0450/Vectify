#pragma once

#include <vector>
#include <QPainter>

#include "Model/Rgba.h"


class ViewPort;
struct Point;

enum class LineTypes
{
  SolidLine,
  DashLine
};

class Painter
{
  QPainter * m_painter;
  ViewPort * m_viewPort;

public:
  Painter(QPainter & painter, ViewPort & viewPort);
  void DrawLineSegment(const Point & startPoint, const Point & endPoint);
  void SetPen(LineTypes lineType, int width, Rgba customColor);
  void DrawControlPoints(const Point & point);
  void DrawBrokenLine(const std::vector<Point> & points, LineTypes type, int width, Rgba color);
};
