#include "midianalyzer.h"
#include "midievent.h"

MidiAnalyzer::MidiAnalyzer()
{ 

    //Initialize server
}

void MidiAnalyzer::startListening(){
    // RtMidiIn constructor
    try {
      midiIn = new RtMidiIn();
    }
    catch ( RtMidiError &error ) {
      error.printMessage();
      exit( EXIT_FAILURE );
    }
    // Check inputs.
    unsigned int nPorts = midiIn->getPortCount();
    std::cout << "\nThere are " << nPorts << " MIDI input sources available.\n";
    std::string portName;
    for ( unsigned int i=0; i<nPorts; i++ ) {
      try {
        portName = midiIn->getPortName(i);
      }
      catch ( RtMidiError &error ) {
        error.printMessage();
      }
      std::cout << "  Input Port #" << i+1 << ": " << portName << '\n';
    }


    // RtMidiOut constructor
    try {
      midiOut = new RtMidiOut();
    }
    catch ( RtMidiError &error ) {
      error.printMessage();
      exit( EXIT_FAILURE );
    }
    // Check outputs.
    nPorts = midiOut->getPortCount();
    std::cout << "\nThere are " << nPorts << " MIDI output ports available.\n";
    for ( unsigned int i=0; i<nPorts; i++ ) {
      try {
        portName = midiOut->getPortName(i);
      }
      catch (RtMidiError &error) {
        error.printMessage();
      }
      std::cout << "  Output Port #" << i+1 << ": " << portName << '\n';
    }

    
    midiOut->openPort(1);

    //TODO : offer user possibility to choose port - eventually possibility to set midi ports to != clients
    midiIn->openPort(1);

    midiIn->ignoreTypes(false, false, false);
    midiIn->setCallback(&mycallback,(void*)this);

    std::cout << "\nReading MIDI input ... \n";

    char input;
    std::cin.get(input);
}

void MidiAnalyzer::mycallback(double deltatime, std::vector< unsigned char > *message, void *userData)
{

     reinterpret_cast<MidiAnalyzer*> (userData)->receivedMessage(deltatime,message);
}



void MidiAnalyzer::receivedMessage(double deltatime, std::vector< unsigned char > *message){
    midiOut->sendMessage(message);
    //incrémenter une clock gnale pour ne pas faire les calculs dans les machines.
    myClock += deltatime;
    std::cout << "Message recu :" << message->at(0) << std::endl;
    if((int)message->at(0) == 0xFA){//Check if note is on

        std::cout << "TOP KEK" << std::endl;
        //Create MidiEvent object here with midi data
        MidiEvent* midiEvent = new MidiEvent(myClock,message);


    }else{ //If note off

    }
}
