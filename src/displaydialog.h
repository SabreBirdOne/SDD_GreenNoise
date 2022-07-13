#ifndef DISPLAYDIALOG_H
#define DISPLAYDIALOG_H

#include <QDialog>
#include <QMainWindow>

namespace Ui {
class displayDialog;
}

class displayDialog : public QDialog
{
    Q_OBJECT

public:
    explicit displayDialog(QMainWindow *parent);
    ~displayDialog();

private slots:
    void on_backButton_clicked();

private:
    Ui::displayDialog *ui;
    QMainWindow *parentWindow;
};

#endif // DISPLAYDIALOG_H
