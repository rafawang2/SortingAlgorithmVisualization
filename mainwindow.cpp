#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sorter_canva = new Canvas(this);
    sorter_canva->move(0, 100);
    sorter_canva->setMinimumSize(this->width() - 200, this->height()-100);
    sorter_canva->setMaximumSize(this->width() - 200, this->height()-100);
    sorter = CSorter(sorter_canva);
    sorter_canva->setSorter(&sorter);

    sortGroup = new QButtonGroup(this);
    sortGroup->addButton(ui->radioButton_BubbleSort,    int(SortType::Bubble));
    sortGroup->addButton(ui->radioButton_InsertionSort, int(SortType::Insertion));
    sortGroup->addButton(ui->radioButton_SelectionSort, int(SortType::Selection));
    sortGroup->addButton(ui->radioButton_ShellSort,     int(SortType::Shell));
    sortGroup->addButton(ui->radioButton_MergeSort,     int(SortType::Merge));
    sortGroup->addButton(ui->radioButton_QuickSort,     int(SortType::Quick));
    sortGroup->addButton(ui->radioButton_HeapSort,      int(SortType::Heap));
}

MainWindow::~MainWindow()
{
    delete ui;
}

vector<int> MainWindow::SplitQString(QString str, QString sep) {
    str = str.trimmed();
    vector<int> input_datas = {};
    int nPos = 0;
    for (auto token : QStringTokenizer(str, sep)) {
        input_datas.push_back(token.toInt());
    }
    return input_datas;
}

void MainWindow::GenerateRandomVector(int n, int min, int max) {
    if (n <= 0) {
        n = 50;
    }
    if (min > max) {
        int tmp = min;
        min = max;
        max = tmp;
    }

    srand(time(nullptr)); // Seed the random number generator
    QString str = "";
    for (int i=0; i<n; i++) {
        int x = rand() % (max - min + 1) + min;
        str += QString("%1 ").arg(x);
    }
    ui->lineEdit_input->setText(str);
}
void MainWindow::on_pushButton_insert_clicked()
{
    if (sorter.is_sorting)
        return;

    auto checked = sortGroup->checkedButton();
    if (!checked)
        return;

    SortType sorttype = static_cast<SortType>(sortGroup->id(checked));

    sorter.SetData(SplitQString(ui->lineEdit_input->text(), " "));

    switch (sorttype) {
    case SortType::Bubble:    sorter.BubbleSort();    break;
    case SortType::Insertion: sorter.InsertionSort(); break;
    case SortType::Selection: sorter.SelectionSort(); break;
    case SortType::Shell:     sorter.ShellSort();     break;
    case SortType::Merge:     sorter.MergeSort();     break;
    case SortType::Quick:     sorter.QuickSort();     break;
    case SortType::Heap:      sorter.HeapSort();      break;
    }
}


void MainWindow::on_pushButton_random_clicked()
{
    int n = 50;
    int min = 1;
    int max = 50;
    QString min_str = ui->lineEdit_minRandomVal->text();
    QString max_str = ui->lineEdit_maxRandomVal->text();
    QString nums_str = ui->lineEdit_RandomNums->text();
    if (min_str != "") min = min_str.toInt();
    if (max_str != "") max = max_str.toInt();
    if (nums_str != "") n = nums_str.toInt();

    GenerateRandomVector(n, min, max);
}


void MainWindow::on_pushButton_skip_clicked()
{
    sorter.no_delay = true;
}

