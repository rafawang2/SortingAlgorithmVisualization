#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QPainter>
#include "csorter.h"

class Canvas : public QWidget
{
    Q_OBJECT
public:
    explicit Canvas(QWidget *parent = nullptr);


    CSorter* sorter;
    void setSorter(CSorter* sorter);

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif
