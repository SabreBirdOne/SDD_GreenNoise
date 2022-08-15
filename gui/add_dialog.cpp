#include "add_dialog.h"
#include "ui_add_Dialog.h"

#define MAX_REACH 17

add_Dialog::add_Dialog(QMainWindow * main,displayDialog *display) :
    ui(new Ui::add_Dialog)
{
    ui->setupUi(this);
    parentWindow=main;
    displayWindow=display;
    sle=NULL;
}

add_Dialog::~add_Dialog()
{
    delete ui;
}


void add_Dialog::on_saveButton_clicked()
{
    QString name=ui->nameEdit->toPlainText();
    this->songName=name;
    QString description=ui->descriptionEdit->toPlainText();
    QString chord=ui->textEdit_3->toPlainText();
    //chord.append("end");
    textEdit=name.append("\n")+description.append("\n")+chord;
    name.append(".txt");
    this->songName=name;

    //call back end
    std::cout<<"back end starts now"<<std::endl;

    //pass data to diaplay window
    std::vector<PianoChord> chord_sequence;
    QStringList Lines = chord.split('\n');

    for (int i = 0; i < Lines.size(); i++) {
        chord_sequence.push_back(PianoChord(Lines[i].toStdString()));
        std::cout<<"temp_chord L["<<i<<"]: "<<Lines[i].toStdString()<<std::endl;
    }

    for (unsigned int i = 0; i < chord_sequence.size(); i++)
    {
      std::cout << "Creating chord list for " << chord_sequence[i].getName() << "..." << std::endl;
      chord_sequence[i].makeChordList(10, 44, MAX_REACH);
      std::cout << chord_sequence[i].getName() << ": Chord list created!" << std::endl;
    }

    std::list<PianoChord> chords (chord_sequence.begin(), chord_sequence.end());
    SongData song_data (chords);

    for (ChordContainer::const_iterator itr = song_data.getChordSet().begin();
      itr != song_data.getChordSet().end(); itr++){

      for (unsigned int i = 0; i < (itr->getBaseChord()).size(); i++)
      {
        std::string note = intToNote((itr->getBaseChord())[i]);
        note = note.substr(0, note.size() - 1);
        note += (note.size() == 1) ? " " : "";
      }
    }
    SongListEntry sle (song_data);

    for (ChordContainer::const_iterator itr = sle.getSongData().getChordSet().begin();
        itr != sle.getSongData().getChordSet().end(); itr++){

        for (unsigned int i = 0; i < (itr->getBaseChord()).size(); i++)
        {
          std::string note = intToNote((itr->getBaseChord())[i]);
          note = note.substr(0, note.size() - 1);
          note += (note.size() == 1) ? " " : "";
        }

      }


    QTextStream * stream = new QTextStream(&description , QIODevice::ReadOnly);
    QString line1 =  stream->readLine();
    QString line2 =  stream->readLine();
    QString line3 =  stream->readLine();
    QString line4 =  stream->readLine();

    sle.editMetaData("SONG NAME", songName.toStdString());
    sle.editMetaData("COMPOSER", line1.toStdString());
    sle.editMetaData("ALBUM", line2.toStdString());
    sle.editMetaData("DATE ADDED TO LIST", line3.toStdString());
    sle.editMetaData("EXTRA INFO", line4.toStdString());


    SongListDataParserTxt parser;
    SongListEntry parsed_sle = parser.parse(songName.toStdString());

    SongListDataWriterTxt writer;
    writer.writeData(songName.toStdString(), parsed_sle);

    this->sle=&parsed_sle;
    std::cout<<"parsed_sle created in add_dialog"<<std::endl;
    displayWindow->setSong(textEdit);
    displayWindow->setChord(chord_sequence);
    std::cout<<"chord_sequence passes to display_dialog"<<std::endl;
    displayWindow->algo();
    displayWindow->show();

    //pass data to mainwindow

    ui->nameEdit->clear();
    ui->descriptionEdit->clear();
    ui->textEdit_3->clear();
    this->hide();

}


void add_Dialog::on_backButton_clicked()
{
    parentWindow->show();
    ui->nameEdit->clear();
    ui->descriptionEdit->clear();
    ui->textEdit_3->clear();
    this->hide();
}

QString add_Dialog::getSongName(){
    return this->songName;
}

QString add_Dialog::getText(){
    return this->textEdit;
}

SongListEntry* add_Dialog::getSle(){
    return this->sle;
};

