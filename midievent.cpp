#include "midievent.h"

MidiEvent::MidiEvent()
{

}

MidiEvent::MidiEvent(double _deltatime, int _note, int _velocity, bool _on){
    timestamp = _deltatime;
    note = _note;
    velocity = _velocity;
    on = _on;
}

MidiEvent::MidiEvent(double deltatime, std::vector< unsigned char > *message){
    std::cout << "New MidiEvent:" << std::endl;
    std::cout << "     note: " << (int)message->at(1)  << std::endl;
    std::cout << "     velocity: " << (int)message->at(2)  << std::endl;
    std::cout << "     on (144=on): " << (int)message->at(0)  << std::endl;
    std::cout << "     time since last event: " << deltatime  << std::endl;
	
	note = (int)message->at(1);
	velocity = (int)message->at(2);
	timestamp = deltatime;
	if((int)message->at(0) == 144){
        on = true;
	}else if((int)message->at(0) == 128){
        on = false;
	}

}

int MidiEvent::getNote(){
	return note;
}

double MidiEvent::getTimeStamp(){
    return timestamp;
}

void MidiEvent::substractTime(double t){
    timestamp -= t;
    if (timestamp < 0) {
        timestamp = 0;
    } 
}
