#ifndef MIDIEVENT_H
#define MIDIEVENT_H
#include <vector>
#include <stdlib.h>
#include <iostream>


class MidiEvent
{
public:
    MidiEvent();
    MidiEvent(double deltatime, std::vector< unsigned char > *message);
    MidiEvent(double _deltatime, int _note, int _velocity, bool _on);

    //Getters
    int getNote();
    double getTimeStamp();
    //Setters
    void substractTime(double t);
private:
    int note;
    int velocity;
    bool on;
    double timestamp;
};

#endif // MIDIMESSAGE_H
