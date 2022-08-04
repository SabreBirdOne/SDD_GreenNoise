#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QFile>
#include <QMessageBox>
#include <QFileDialog>
#include "editdialog.h"
#include "displaydialog.h"
#include "controldialog.h"
#include "add_dialog.h"

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

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
namespace std { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void showDisplayWindow();
    void showEditWindow();
    void showMainWindow();

private slots:
    void on_importButton_clicked();

    void on_searchBar_returnPressed();

    void newDocument();

    void on_importButton_2_clicked();

    void on_addButton_clicked();

    void showControlWindow();

    void showAddWindow();

    void addToSongList(QString name);

private:
    Ui::MainWindow *ui;

    QString currentFile;
    QString textEdit;

    EditDialog *editWindow;
    displayDialog *displayWindow;
    controlDialog *controlWindow;

    add_Dialog * add;
};
#endif // MAINWINDOW_H
