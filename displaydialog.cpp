#include "displaydialog.h"
#include "ui_displaydialog.h"

displayDialog::displayDialog(QMainWindow *parent) :
    QDialog(parent),
    ui(new Ui::displayDialog)
{
    ui->setupUi(this);
    parentWindow=parent;
}

displayDialog::~displayDialog()
{
    delete ui;
}

void displayDialog::on_backButton_clicked()
{
    this->hide();
    parentWindow->show();
}
