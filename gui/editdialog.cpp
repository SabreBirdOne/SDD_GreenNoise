#include "editdialog.h"
#include "ui_editdialog.h"


EditDialog::EditDialog(QMainWindow *parent) :
    QDialog(parent),
    ui(new Ui::EditDialog)
{
    ui->setupUi(this);
    parentWindow=parent;
}

EditDialog::~EditDialog()
{
    delete ui;
}

void EditDialog::setDisplayWindow(displayDialog *display){
    displayWindow=display;
}

void EditDialog::setSong(QString song){
    this->song=song;
    ui->textBrowser->setText(song);
}

void EditDialog::on_backButton_clicked()
{
    this->hide();
    ui->textBrowser->clear();
    parentWindow->show();
}


void EditDialog::on_practiceButton_clicked()
{
    this->hide();
    displayWindow->setSong(this->song);
    displayWindow->show();
}


void EditDialog::on_descriptionButton_clicked()
{
    ;
}

