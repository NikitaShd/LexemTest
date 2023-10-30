#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(4);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
   int i = 0;
   ui->listWidget->clear();

   auto list =  analuzer.startAnalaze(ui->textEdit->toPlainText());
     ui->tableWidget->setRowCount(list.length());
   for (auto lex : list) {

       ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString::number(lex.striceNum)));
       ui->tableWidget->setItem(i,1,new QTableWidgetItem(lex.name));
       ui->tableWidget->setItem(i,2,new QTableWidgetItem(analuzer.getName(lex.lexClass)));
       ui->tableWidget->setItem(i,3,new QTableWidgetItem(lex.value));
       ui->listWidget->addItem(QString("%1 | %2 | %3 | %4").arg(lex.striceNum, 4,10).arg(lex.name, -14).arg(analuzer.getName(lex.lexClass), 30).arg(lex.value, 14));

      i++;
   }
}


void MainWindow::on_textEdit_textChanged()
{
    int i = 0;
    ui->listWidget->clear();

    auto list =  analuzer.startAnalaze(ui->textEdit->toPlainText());
      ui->tableWidget->setRowCount(list.length());
    for (auto lex : list) {

        ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString::number(lex.striceNum)));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(lex.name));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(analuzer.getName(lex.lexClass)));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(lex.value));
        ui->listWidget->addItem(QString("%1 | %2 | %3 | %4").arg(lex.striceNum, 4,10).arg(lex.name, -14).arg(analuzer.getName(lex.lexClass), 30).arg(lex.value, 14));

       i++;
    }
}

