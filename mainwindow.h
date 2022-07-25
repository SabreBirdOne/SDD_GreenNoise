#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QFile>
#include <QMessageBox>
#include <QFileDialog>
#include "editdialog.h"
#include "displaydialog.h"
/*
#include "piano_chord.h"
#include "piano_chord_specific.h"
#include "search.cpp"
*/
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

private:
    Ui::MainWindow *ui;

    QString currentFile;
    QString textEdit;

    EditDialog *editWindow;
    displayDialog *displayWindow;
};
#endif // MAINWINDOW_H
