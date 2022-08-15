#ifndef DISPLAYDIALOG_H
#define DISPLAYDIALOG_H

#include <QDialog>
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
class displayDialog;
}

class displayDialog : public QDialog
{
    Q_OBJECT

public:
    explicit displayDialog(QMainWindow *parent);
    void setSong(QString song);
    void setChord(std::vector<PianoChord> chord_sequence);
    std::string findEasiestPath(std::vector<PianoChord> chord_sequence, int starting_chord);
    int difficulty(PianoChordSpecific chord1, PianoChordSpecific chord2);
    void algo();

    ~displayDialog();

private slots:
    void on_backButton_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::displayDialog *ui;
    std::vector<PianoChord> chord_sequence;
    QMainWindow *parentWindow;
    QString fileName;
    QString song;
    int current_time;//seconds
    QTimer *timer;
    double tempo; //beats/second
    QStringList results;
};

#endif // DISPLAYDIALOG_H
