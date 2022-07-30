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
    controlWindow=new controlDialog(this,displayWindow,editWindow);
    add=new add_Dialog(this,displayWindow);
    /*
    for(int i=0;i<10;i++){
        QString name="song";
        name.append(QString("%1").arg(i+1));
        ui->songList->setSortingEnabled(false);
        QListWidgetItem *item = new QListWidgetItem(name);
        ui->songList->addItem(item);
    }
    connect(ui->songList,&QListWidget::itemDoubleClicked,controlWindow,&controlDialog::show);
    */
}

MainWindow::~MainWindow()
{
    delete ui;
    delete editWindow;
}

void MainWindow::showDisplayWindow(){
    this->displayWindow->setSong(textEdit);
    this->hide();
    this->editWindow->hide();
    this->displayWindow->show();
}

void MainWindow::showEditWindow(){
    this->editWindow->setSong(textEdit);
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
{
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

    this->fileName=fileName;
    this->addToSongList(fileName);

    this->showEditWindow();

}


void MainWindow::on_searchBar_returnPressed()
{
    newDocument();
    QString fileName=ui->searchBar->text();
    fileName.append(".txt");
    this->fileName=fileName;
    QFile file("C:/Users/li148/Documents/RPI/summer/SDD/Re-Chorder/"+fileName);
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream in(&file);
    textEdit= in.readAll();
    file.close();

    this->fileName=fileName;
    this->addToSongList(fileName);

    this->showEditWindow();
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

    QString fileName=ui->searchBar->text();
    fileName.append(".txt");
    this->fileName=fileName;
    QFile file("C:/Users/li148/Documents/RPI/summer/SDD/Re-Chorder"+fileName);
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream in(&file);
    textEdit= in.readAll();
    file.close();

    this->fileName=fileName;
    this->addToSongList(fileName);

    //back end
    SongListDataWriterTxt writer;
    writer.writeDataFromString(fileName.toStdString(),textEdit.toStdString());
    SongListDataParserTxt parser;
    parser.parse(fileName.toStdString());

    this->showDisplayWindow();
}

void MainWindow::showAddWindow(){
    this->add->show();
}

void MainWindow::addToSongList(QString songName){
    QString name=songName;
    ui->songList->setSortingEnabled(false);
    QListWidgetItem *item = new QListWidgetItem(name);
    ui->songList->addItem(item);
    //connect(ui->songList,&QListWidget::itemDoubleClicked,controlWindow,&controlDialog::show);
    ui->songList->update();
}

void MainWindow::on_addButton_clicked()
{
    this->newDocument();
    this->showAddWindow();

    QString name="song1";
    ui->songList->setSortingEnabled(false);
    QListWidgetItem *item = new QListWidgetItem(name);
    ui->songList->addItem(item);

    ui->songList->update();
}
void MainWindow::showControlWindow(){
    this->controlWindow->show();
}

void MainWindow::on_practiceButton_clicked()
{
    showDisplayWindow();
}

void MainWindow::on_pushButton_4_clicked()
{
    QListWidgetItem *it = ui->songList->takeItem(ui->songList->currentRow());
    delete it;
}


void MainWindow::on_pushButton_3_clicked()
{
    showEditWindow();
}


void MainWindow::on_pushButton_clicked()
{
    showEditWindow();
}


void MainWindow::on_pushButton_2_clicked()
{
    QListWidgetItem *it = ui->songList->takeItem(ui->songList->currentRow());
    delete it;
}

