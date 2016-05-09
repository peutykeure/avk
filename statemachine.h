#ifndef STATEMACHINE_H
#define STATEMACHINE_H
#include "midievent.h"

#include <vector>
#include <stdlib.h>

class MidiAnalyzer;

class StateMachine
{
public:
    StateMachine();
    StateMachine(std::vector<MidiEvent*> sequence,std::string nom);
    StateMachine(StateMachine* stateMachine);
    //StateMachine(String nom, int aNotes);
    bool updateMachine(MidiEvent* message);
    bool checkTimes();
    void clearTimes();
    void resetMachine();
    void createClone();

    //Getters
    std::string getName();
    std::vector<MidiEvent*> getSequence();
    std::vector<MidiEvent*> getSequenceBuffer();

    
    //Setters
    void setMidiAnalyzer(MidiAnalyzer* midiAnalyzer);


private:
    double authorizedTime = 0.15; //timeDelta servira à définir combien de différences dans les temps on autorise
    double timeBeforeRestart = 25; //sert à définir combien d'autres notes on autorise (qui n'appartiennent pas à la séquence)
    std::string name = ""; //Le nom de la séquence 
    std::vector<MidiEvent*> mySequence;
    std::vector<MidiEvent*> sequenceBuffer;
    MidiAnalyzer* mAnalyzer;
    bool isCopy = false;

};

#endif // STATEMACHINE_H
