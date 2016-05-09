#ifndef MIDIANALYZER_H
#define MIDIANALYZER_H
#include <vector>
#include <stdlib.h>
#include "RtMidi.h"

class MidiAnalyzer
{
public:
    MidiAnalyzer();
    static void mycallback(double deltatime, std::vector< unsigned char > *message, void *userData);
    void receivedMessage(double deltatime, std::vector< unsigned char > *message);
    int getName();
    void startListening();

private:
    //MyServer *myServer;
    RtMidiIn *midiIn;
    RtMidiOut *midiOut;
    double myClock = 0;

};

#endif // MIDIANALYZER_H
