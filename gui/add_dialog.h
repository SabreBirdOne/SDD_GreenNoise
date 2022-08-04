#ifndef ADD_DIALOG_H
#define ADD_DIALOG_H

#include <QDialog>
#include "displaydialog.h"
#include <QMainWindow>

#include "piano_chord.h"
#include "song_data.h"
#include "song_list_entry.h"
#include "song_list_data_parser_txt.h"
#include "song_list_data_writer_txt.h"
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <unistd.h>
#include <utility>
#include <math.h>
#include <list>
#include <unordered_map>

namespace Ui {
class add_Dialog;
}

class add_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit add_Dialog(QMainWindow * parent,displayDialog *displayWindow);
    QString getSongName();
    QString getText();
    ~add_Dialog();


private slots:
    void on_saveButton_clicked();

    void on_backButton_clicked();

private:
    Ui::add_Dialog *ui;
    QMainWindow * parentWindow;
    displayDialog *displayWindow;
    QString textEdit;
    QString songName;
};

#endif // ADD_DIALOG_H
