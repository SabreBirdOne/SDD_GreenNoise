#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    editWindow=new EditDialog(this);
    displayWindow= new displayDialog(this);

    editWindow->setDisplayWindow(displayWindow);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete editWindow;
}

void MainWindow::showDisplayWindow(){
    this->hide();
    this->editWindow->hide();
    this->displayWindow->show();
}

void MainWindow::showEditWindow(){
    this->hide();
    this->displayWindow->hide();
    this->editWindow->show();
}

void MainWindow::showMainWindow(){
    this->show();
    this->displayWindow->hide();
    this->editWindow->show();
}

void MainWindow::on_importButton_clicked()
{/*
    //read in a file
    newDocument();
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file");
    if (fileName.isEmpty())
        return;
    QFile file(fileName);
    currentFile = fileName;
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream in(&file);
    textEdit= in.readAll();
    file.close();
*/

    //show the editWindow
    this->showEditWindow();

}


void MainWindow::on_searchBar_returnPressed()
{
    newDocument();
    QString fileName=ui->searchBar->text();
    fileName.append(".txt");
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream in(&file);
    textEdit= in.readAll();
    file.close();
}

//clear both currentFile and textEdit
void MainWindow::newDocument()
{
    currentFile.clear();
    textEdit.clear();
}


void MainWindow::on_importButton_2_clicked()
{
    newDocument();
    /*
    QString fileName=ui->searchBar->text();
    //fileName.append(".txt");
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream in(&file);
    textEdit= in.readAll();
    file.close();
    */
    this->showDisplayWindow();
}

