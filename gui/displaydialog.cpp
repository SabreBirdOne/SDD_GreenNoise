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

void displayDialog::setSong(QString song){
    this->song=song;
    ui->textBrowser->setText(song);
}

void displayDialog::on_backButton_clicked()
{
    this->hide();
    ui->textBrowser->clear();
    parentWindow->show();
}

void displayDialog::setChord(std::vector<PianoChord> chord_sequence){
    this->chord_sequence=chord_sequence;
}

