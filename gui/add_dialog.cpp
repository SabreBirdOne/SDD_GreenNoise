#include "add_dialog.h"
#include "ui_add_dialog.h"

#define MAX_REACH 17

add_Dialog::add_Dialog(QMainWindow * main,displayDialog *display) :
    ui(new Ui::add_Dialog)
{
    ui->setupUi(this);
    parentWindow=main;
    displayWindow=display;
}

add_Dialog::~add_Dialog()
{
    delete ui;
}


void add_Dialog::on_saveButton_clicked()
{
    QString name=ui->nameEdit->toPlainText();
    this->songName=name;
    QString description=ui->descriptionEdit->toPlainText();
    QString chord=ui->textEdit_3->toPlainText();
    chord.append("end");
    textEdit=name.append("\n")+description.append("|\n")+chord;

    //call back end

    //pass data to diaplay window
    displayWindow->setSong(textEdit);
    displayWindow->show();

    //pass data to mainwindow

    ui->nameEdit->clear();
    ui->descriptionEdit->clear();
    ui->textEdit_3->clear();
    this->hide();

}


void add_Dialog::on_backButton_clicked()
{
    parentWindow->show();
    ui->nameEdit->clear();
    ui->descriptionEdit->clear();
    ui->textEdit_3->clear();
    this->hide();
}

QString add_Dialog::getSongName(){
    return this->songName;
}

QString add_Dialog::getText(){
    return this->textEdit;
}



