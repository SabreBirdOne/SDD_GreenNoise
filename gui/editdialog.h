#ifndef EDITDIALOG_H
#define EDITDIALOG_H

#include <QMainWindow>
#include <QDialog>

namespace Ui {
class EditDialog;
}

class EditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditDialog(QMainWindow *parent);
    void setDisplayWindow(QDialog *display);
    ~EditDialog();

private slots:
    void on_backButton_clicked();

    void on_practiceButton_clicked();

private:
    Ui::EditDialog *ui;
    QMainWindow *parentWindow;
    QDialog * displayWindow;
};

#endif // EDITDIALOG_H
