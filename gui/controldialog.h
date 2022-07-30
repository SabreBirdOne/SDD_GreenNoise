#ifndef CONTROLDIALOG_H
#define CONTROLDIALOG_H

#include <QDialog>
#include <QMainWindow>
#include "displaydialog.h"
#include "editdialog.h"

namespace Ui {
class controlDialog;
}

class controlDialog : public QDialog
{
    Q_OBJECT

public:
    explicit controlDialog(QMainWindow *parentWindow,
    displayDialog * displayWindow,
    EditDialog  * editWindow);
    ~controlDialog();

private slots:
    void on_backButton_clicked();

    void on_practiceButton_clicked();

    void on_editButton_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::controlDialog *ui;
    QMainWindow *parentWindow;
    displayDialog * displayWindow;
    EditDialog * editWindow;
    QString fileName;
    QString textEdit;
};

#endif // CONTROLDIALOG_H
