#include "controldialog.h"
#include "ui_controldialog.h"
#include <QListWidgetItem>

controlDialog::controlDialog(QMainWindow *parent,
                             displayDialog * display,
                             EditDialog  * edit) :
    QDialog(parent),
    ui(new Ui::controlDialog)
{
    ui->setupUi(this);
    parentWindow=parent;
    displayWindow=display;
    editWindow=edit;
}

controlDialog::~controlDialog()
{
    delete ui;
}

void controlDialog::on_backButton_clicked()
{
    parentWindow->show();
    this->hide();
}


void controlDialog::on_practiceButton_clicked()
{
    displayWindow->show();
    //displayWindow->setSong();
    this->hide();
}


void controlDialog::on_editButton_clicked()
{
    editWindow->show();
    this->hide();
}


void controlDialog::on_pushButton_4_clicked()
{    parentWindow->show();
     this->hide();
}

