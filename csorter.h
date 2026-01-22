#ifndef CSORTER_H
#define CSORTER_H

#include <QWidget>
#include <QPainter>
#include <QApplication>
#include <windows.h>
#include <algorithm>
#include <vector>
using std::vector;

class CSorter
{
private:
    int bar_width = 20;
    int bar_unit_height = 5;
    int offset_x = 10;
    int offset_y = 500;
    int delay_time = 1;
    int draw_idx_i = -1;
    int draw_idx_j = -1;
    int draw_idx_found = -1;
    int draw_finish_idx = -1;
    QPen WhitePen = QPen(Qt::white);
    QPen RedPen = QPen(Qt::red);
    QPen BluePen = QPen(Qt::blue);
    QPen GreenPen = QPen(Qt::green);
    QBrush RedBrush = QBrush(Qt::red);
    QBrush BlackBrush = QBrush(Qt::black);
    QBrush BlueBrush = QBrush(Qt::blue);
    QBrush GreenBrush = QBrush(Qt::green);
    QBrush PurpleBrush = QBrush(QColor(255, 0, 255, 255));
    QFont font = QFont("Arial", bar_width/2);

    // Recursive & private method
    void merge(int l, int m, int r);
    void MergeSortRecursive(int l, int r);
    int partition(int l, int r);
    void QuickSortRecursive(int l, int r);
    void heapify(int parent, int heap_size);
    void BuildHeap(int heap_size);

    int find_min_offset_x(int w, int n);

public:
    bool is_sorting = false;
    bool sort_complete = false;
    bool no_delay = false;
    vector<int> datas;
    QWidget* canva;
    CSorter();
    CSorter(QWidget* canva);
    void DelayAndUpdate(QWidget* canva, int delay_time);
    void DrawDatas(QPainter& painter);
    void DrawSingleColorBar(QPainter& painter, QPen& pen, QBrush& brush, int idx);
    void Swap(int& a, int& b);
    void SetData(vector<int> datas);
    void EndofSort();
    void BubbleSort();
    void InsertionSort();
    void SelectionSort();
    void ShellSort();
    void MergeSort();
    void QuickSort();
    void HeapSort();
};

#endif // CSORTER_H
