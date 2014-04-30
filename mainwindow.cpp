#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    pEngine = new ColumnGeneratorThread(this);

    connect(ui->widget, SIGNAL(numSelectionChangedSignal(QList<quint8>)), pEngine, SLOT(updateNumbers(QList<quint8>)));
    connect(pEngine, SIGNAL(generatorErrorSignal(QString)), ui->statusBar, SLOT(showMessage(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}
