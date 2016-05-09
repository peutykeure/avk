#include "midianalyzer.h"
#include <QApplication>
#include <QtCore>
#include <stdlib.h>
#include <vector>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MidiAnalyzer* analyzer = new MidiAnalyzer();

    analyzer->startListening();

    return a.exec();
}

