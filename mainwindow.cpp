#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
   int i = 0;
   ui->listWidget->clear();
   for (auto lex : analuzer.startAnalaze(ui->textEdit->toPlainText())) {
      if(lex.lexClass != LexAnaluzet::NUUL)
      ui->listWidget->addItem(QString::number(lex.striceNum) + " | " + QString(lex.name) + " | " + analuzer.getName(lex.lexClass) + " | " + QString(lex.value));
      i++;
   }
}

