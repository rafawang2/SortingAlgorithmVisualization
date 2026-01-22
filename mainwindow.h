#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QButtonGroup>
#include "canvas.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

enum class SortType {
    Bubble,
    Insertion,
    Selection,
    Shell,
    Merge,
    Quick,
    Heap
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_insert_clicked();

    void on_pushButton_random_clicked();

    void on_pushButton_skip_clicked();

private:
    Ui::MainWindow *ui;
    Canvas* sorter_canva;
    SortType sorttype = SortType::Bubble;
    CSorter sorter;
    QButtonGroup* sortGroup;
    vector<int> SplitQString(QString str, QString sep);
    void GenerateRandomVector(int n, int min, int max);
};
#endif // MAINWINDOW_H
