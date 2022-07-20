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

void EditDialog::setDisplayWindow(QDialog *display){
    displayWindow=display;
}

void EditDialog::on_backButton_clicked()
{
    this->hide();
    parentWindow->show();
}


void EditDialog::on_practiceButton_clicked()
{
    this->hide();
    displayWindow->show();
}

