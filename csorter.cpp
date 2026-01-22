#include "csorter.h"

CSorter::CSorter() {
    datas = {};
}
CSorter::CSorter(QWidget* canva) {
    this->canva = canva;
    offset_y = canva->height() - bar_width*2;
}
void CSorter::DelayAndUpdate(QWidget* canva, int delay_time) {
    canva->update();
    if (no_delay) return;
    QApplication::processEvents();
    Sleep(delay_time);
}
void CSorter::DrawDatas(QPainter& painter) {
    int n = datas.size();
    for (int i=0; i<n; ++i) {
        DrawSingleColorBar(painter, WhitePen, BlackBrush, i);
    }
    if (sort_complete) {
        for (int i=0; i<=draw_finish_idx; ++i) {
            DrawSingleColorBar(painter, WhitePen, GreenBrush, i);
        }
        return;
    }
    DrawSingleColorBar(painter, WhitePen, RedBrush, draw_idx_i);
    DrawSingleColorBar(painter, WhitePen, BlueBrush, draw_idx_j);
    DrawSingleColorBar(painter, WhitePen, PurpleBrush, draw_idx_found);
}
void CSorter::DrawSingleColorBar(QPainter& painter, QPen& pen, QBrush& brush, int idx) {
    if (idx >= datas.size() || idx < 0)
        return;
    int num = datas[idx];
    int h = num*bar_unit_height;
    int x = offset_x + idx*bar_width;
    int y = offset_y - h;
    painter.setPen(pen);
    painter.setBrush(brush);
    painter.drawRect(QRect(x, y, bar_width, h));

    painter.setFont(font);
    QRect textRect(x, offset_y+5, bar_width, bar_width/2);
    painter.drawText(textRect,Qt::AlignCenter, QString("%1").arg(datas[idx]));
}

void CSorter::Swap(int &a, int &b) {
    std::swap(a, b);
    DelayAndUpdate(canva, delay_time);
}

int CSorter::find_min_offset_x(int w, int n) {
    if (n % 2 == 1) {
        // n 為奇數
        int inv2 = (n + 1) / 2;
        int x = (w * inv2) % n;

        if (x == 0)
            x = n;   // 下一個最近的解

        return x;
    } else {
        // n 為偶數
        if (w % 2 != 0) {
            return -1;  // 明確表示「無解」
        }

        int mod = n / 2;
        int x = (w / 2) % mod;

        if (x == 0)
            x = mod;

        return x;
    }
}

void CSorter::SetData(vector<int> datas) {
    this->datas = datas;

    if (datas.empty()) {
        bar_width = 0;
        return;
    }

    int n = datas.size();
    offset_x = find_min_offset_x(canva->width(), n);
    bar_width = (canva->width() - 2*offset_x) / n;

    int maxVal = *std::max_element(datas.begin(), datas.end());
    int margin = canva->height() - offset_y;
    bar_unit_height = (canva->height() - 2*margin)/maxVal;
    // if (bar_unit_height == 0) bar_unit_height = 1;
    qDebug() << canva->height();
    qDebug() << bar_unit_height;


    draw_idx_i = -1;
    draw_idx_j = -1;
    draw_idx_found = -1;
    is_sorting = false;
    sort_complete = false;
    no_delay = false;
}


void CSorter::EndofSort() {
    draw_idx_i = -1;
    draw_idx_j = -1;
    draw_idx_found = -1;
    DelayAndUpdate(canva, delay_time);
    sort_complete = true;
    is_sorting = false;
    draw_finish_idx = 0;
    int n = datas.size();
    while (draw_finish_idx <= n) {
        DelayAndUpdate(canva, delay_time);
        ++draw_finish_idx;
    }
}

void CSorter::BubbleSort() {
    is_sorting = true;
    int n = this->datas.size();
    bool flag;
    for (int i=n-1; i>=1; --i) {
        draw_idx_i = i;
        flag = false;
        for (int j=0; j<i; ++j) {
            draw_idx_j = j;
            if (datas[j] > datas[j+1]) {
                draw_idx_found = j+1;
                Swap(datas[j], datas[j+1]);
                flag = true;
            }
        }
        if (!flag) {
            break;
        }
    }
    EndofSort();
}

void CSorter::InsertionSort() {
    is_sorting = true;
    int n = datas.size();
    for (int i=1; i<n; ++i) {
        draw_idx_i = i;
        int j = i-1;
        int k = datas[i];
        while (j>=0 && datas[j] > k) {
            draw_idx_j = j;
            datas[j+1] = datas[j];
            --j;
            DelayAndUpdate(canva, delay_time);
        }
        datas[j+1] = k;
        draw_idx_found = j+1;
        DelayAndUpdate(canva, delay_time);
        draw_idx_found = -1;
    }
    EndofSort();
}

void CSorter::SelectionSort() {
    is_sorting = true;
    int n = datas.size();
    for (int i=0; i<n; ++i) {
        draw_idx_i = i;
        draw_idx_found = -1;
        int min_idx = i;
        for (int j=i+1; j<n; ++j) {
            draw_idx_j = j;
            if (datas[min_idx]>datas[j]) {
                min_idx = j;
                draw_idx_found = min_idx;
            }
            DelayAndUpdate(canva, delay_time);
        }
        if (min_idx!=i) {
            Swap(datas[i], datas[min_idx]);
        }
    }
    EndofSort();
}

void CSorter::ShellSort() {
    is_sorting = true;
    int n = datas.size();
    for (int gap = n/2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; ++i) {
            draw_idx_i = i;
            int temp = datas[i];
            int j = i;
            while (j >= gap && datas[j-gap] > temp) {
                draw_idx_j = j-gap;
                datas[j] = datas[j-gap];
                j -= gap;
                DelayAndUpdate(canva, delay_time);
            }
            datas[j] = temp;
            draw_idx_found = j;
            DelayAndUpdate(canva, delay_time);
            draw_idx_found = -1;
        }
    }
    EndofSort();
}

void CSorter::merge(int l, int m, int r) {
    draw_idx_i = -1;
    draw_idx_j = -1;
    draw_idx_found = -1;

    int n1 = m-l+1; // l~m
    int n2 = r-m;   // m+1~r

    // copy sub data
    vector<int> v1(n1);
    vector<int> v2(n2);
    for (int i=0; i<n1; ++i) {
        v1[i] = datas[l+i];
    }
    for (int i=0; i<n2; ++i) {
        v2[i] = datas[m+1+i];
    }

    // merge v1 & v2
    int p=0, q=0;
    int k = l;
    while (p<n1 && q<n2) {
        if (v1[p] < v2[q]) {
            datas[k] = v1[p];
            ++p;
            ++k;
        }
        else {
            datas[k] = v2[q];
            ++q;
            ++k;
        }
        draw_idx_i = l + p;
        draw_idx_j = m + 1 + q;
        draw_idx_found = k;
        DelayAndUpdate(canva, delay_time);
    }
    while (p<n1) {
        datas[k] = v1[p];
        ++p;
        ++k;
        draw_idx_i = l + p;
        draw_idx_found = k;
        DelayAndUpdate(canva, delay_time);
    }
    while (q<n2) {
        datas[k] = v2[q];
        ++q;
        ++k;
        draw_idx_j = m + 1 + q;
        draw_idx_found = k;
        DelayAndUpdate(canva, delay_time);
    }
    draw_idx_i = -1;
    draw_idx_j = -1;
    draw_idx_found = -1;
}

void CSorter::MergeSortRecursive(int l, int r) {
    if (l>=r) return;
    int m = (l+r)/2;
    MergeSortRecursive(l, m);
    MergeSortRecursive(m+1, r);
    merge(l, m, r);
}

void CSorter::MergeSort() {
    is_sorting = true;
    MergeSortRecursive(0, datas.size()-1);
    EndofSort();
}

int CSorter::partition(int l, int r) {
    int x = datas[r];   // pivot_value
    int i = l-1;
    for (int j=l; j<r; ++j) {
        draw_idx_j = j;
        draw_idx_i = i;
        if (datas[j] <= x) {
            ++i;
            draw_idx_i = i;
            Swap(datas[i], datas[j]);
        }
    }
    int pivot = i+1;
    draw_idx_found = pivot;
    Swap(datas[r], datas[pivot]);
    draw_idx_found = -1;
    draw_idx_i = -1;
    draw_idx_j = -1;
    return pivot;
}

void CSorter::QuickSortRecursive(int l, int r) {
    if (l>=r)
        return;
    int p = partition(l, r);
    QuickSortRecursive(l, p-1);
    QuickSortRecursive(p+1, r);
}

void CSorter::QuickSort() {
    is_sorting = true;
    QuickSortRecursive(0, datas.size()-1);
    EndofSort();
}

void CSorter::heapify(int parent, int heap_size) {
    int Lchild = 2*parent+1;
    int Rchild = 2*parent+2;
    int max = parent;
    draw_idx_i = parent;
    if (Lchild < heap_size && datas[Lchild] > datas[max]) {
        max = Lchild;
        draw_idx_j = max;
    }
    if (Rchild < heap_size && datas[Rchild] > datas[max]) {
        max = Rchild;
        draw_idx_j = max;
    }
    draw_idx_found = max;

    // max有變過->繼續往下調整
    if (max != parent) {
        Swap(datas[max], datas[parent]);
        heapify(max, heap_size);
    }
}

void CSorter::BuildHeap(int heap_size) {
    // 對所有non-leaf做 heapify
    for (int parent=(heap_size-1)/2; parent>=0; parent--) {
        heapify(parent, heap_size);
    }
}

void CSorter::HeapSort() {
    is_sorting = true;
    int n = datas.size();
    BuildHeap(n);
    for (int i=n-1; i>=1; --i) {
        // 最大的丟到datas最後面
        Swap(datas[i], datas[0]);
        heapify(0, i);
    }
    EndofSort();
}

