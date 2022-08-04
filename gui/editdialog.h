#ifndef EDITDIALOG_H
#define EDITDIALOG_H

#include <QMainWindow>
#include <QDialog>
#include "displaydialog.h"

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
class EditDialog;
}

class EditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditDialog(QMainWindow *parent);
    void setDisplayWindow(displayDialog *display);
    void setSong(QString song);
    ~EditDialog();

private slots:
    void on_backButton_clicked();

    void on_practiceButton_clicked();

    void on_descriptionButton_clicked();

private:
    Ui::EditDialog *ui;
    QMainWindow *parentWindow;
    displayDialog * displayWindow;
    QString song;
};

#endif // EDITDIALOG_H
