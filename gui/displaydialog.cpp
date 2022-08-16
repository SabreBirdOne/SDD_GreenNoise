#include "displaydialog.h"
#include "ui_displaydialog.h"
#include <QTimer>

displayDialog::displayDialog(QMainWindow *parent) :
    QDialog(parent),
    ui(new Ui::displayDialog)
{
    ui->setupUi(this);
    parentWindow=parent;
    timer = new QTimer(this);
    timer->start(1000);
    //int remaining = timer->remainingTime();
    //timer->stop();
    //timer->setInterval(remaining);
    tempo=100/60;
}

displayDialog::~displayDialog()
{
    delete ui;
}

void displayDialog::setSong(QString song){
    this->song=song;
    //ui->textBrowser->setText(song);
}

void displayDialog::on_backButton_clicked()
{
    this->hide();
    //ui->textBrowser->clear();
    parentWindow->show();
}

void displayDialog::setChord(std::vector<PianoChord> chord_sequence){
    this->chord_sequence=chord_sequence;
}

int displayDialog::difficulty(PianoChordSpecific chord1, PianoChordSpecific chord2)
{
  int difficulty = 0;
  int num_iterations = (chord1.notes.size() < chord2.notes.size()) ? chord1.notes.size() : chord2.notes.size();
  for (int i = 0; i < num_iterations; i++)
  {
    difficulty += pow(2, abs(chord1.notes[i] - chord2.notes[i]));
  }
  difficulty += abs((int)chord1.notes.size() - (int)chord2.notes.size());
  return difficulty;
}

std::string displayDialog::findEasiestPath(std::vector<PianoChord> chord_sequence, int starting_chord)
{
  //center the leftmost note of the last chord around C3
  int center_note = 27;
  int best = chord_sequence[0].chord_list[0].notes[0];
  int best_index = 0;
  for (unsigned int i = 1; i < chord_sequence[starting_chord].chord_list.size(); i++)
  {
    if (abs(chord_sequence[0].chord_list[i].notes[0] - center_note) < abs(best - center_note))
    {
      best = chord_sequence[0].chord_list[i].notes[0];
      best_index = i;
    }
  }
  int prev_specific_chord_index = chord_sequence[0].getSpecificChordIndex();
  chord_sequence[0].setSpecificChord(best_index);
  for (unsigned int i = 1; i < chord_sequence.size(); i++)
  {
    chord_sequence[i].setSpecificChord(0);
    int min_difficulty = difficulty(chord_sequence[i-1].getSpecificChord(), chord_sequence[i].getSpecificChord());
    int min_difficulty_index = 0;
    for (unsigned int j = 1; j < chord_sequence[i].chord_list.size(); j++)
    {
      chord_sequence[i].setSpecificChord(j);
      int new_difficulty = difficulty(chord_sequence[i-1].getSpecificChord(), chord_sequence[i].getSpecificChord());
      if (new_difficulty < min_difficulty)
      {
        min_difficulty = difficulty(chord_sequence[i-1].getSpecificChord(), chord_sequence[i].getSpecificChord());
        min_difficulty_index = j;
      }
    }
    chord_sequence[i].setSpecificChord(min_difficulty_index);
    chord_sequence[i-1].setSpecificChord(prev_specific_chord_index);
    prev_specific_chord_index = chord_sequence[i].getSpecificChordIndex();
  }
  chord_sequence[chord_sequence.size()-1].setSpecificChord(prev_specific_chord_index);
  //return std::make_pair(0, chord_sequence);
  std::string return_string = "";
  for (unsigned int i = 0; i < chord_sequence.size(); i++)
  {
    return_string += chord_sequence[i].getName() + ":";
    for (unsigned int j = 0; j < 15 - chord_sequence[i].getName().size(); j++)
    {
      return_string += " ";
    }
    return_string += chord_sequence[i].getChord() + "\n";
  }
  return return_string;
}

void displayDialog::algo(){
    song=QString::fromStdString(findEasiestPath(chord_sequence,0));
    ui->textBrowser->setText(song);
}

void displayDialog::on_pushButton_clicked()
{
    current_time=ui->textBrowser_2->toPlainText().toInt();
    if(current_time==0){
        ui->textBrowser->clear();
    }
    current_time+=1;
    ui->textBrowser_2->setText(QString::number(current_time));
    ui->textBrowser->append(results[current_time-1]);
    if(current_time==results.size()-1){
        ui->textBrowser->setText(song);
        //int remaining = timer->remainingTime();
        timer->stop();
        //timer->setInterval(remaining);
        ui->textBrowser_2->setText(QString::number(0));
        current_time=0;
    }
    if(current_time>60){
        //int remaining = timer->remainingTime();
        timer->stop();
        //timer->setInterval(remaining);
        ui->textBrowser_2->setText(QString::number(0));
        current_time=0;
    }
}


void displayDialog::on_pushButton_2_clicked()
{
    ui->textBrowser_2->setText(QString::number(0));
    //int remaining = timer->remainingTime();
    timer->stop();
    //timer->setInterval(remaining);
    current_time=0;
}


void displayDialog::on_pushButton_3_clicked()
{   results = song.split('\n');
    timer->destroyed();
    timer = new QTimer(this);
    timer->start(1000);
    connect(timer, &QTimer::timeout, this, &displayDialog::on_pushButton_clicked);
    timer->start();
}

