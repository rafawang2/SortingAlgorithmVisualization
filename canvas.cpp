#include "canvas.h"
Canvas::Canvas(QWidget *parent)
    : QWidget(parent)
{
    setStyleSheet("background-color: white;");
}

void Canvas::setSorter(CSorter* sorter)
{
    this->sorter = sorter;
}

void Canvas::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 白色邊框
    QPen pen(Qt::white);
    painter.setPen(pen);
    painter.drawRect(rect().adjusted(0, 0, -1, -1)); // -1 是避免畫出外框超出 widget

    sorter->DrawDatas(painter);
}
