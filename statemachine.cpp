#include "statemachine.h"
#include "midianalyzer.h"

StateMachine::StateMachine()
{
}

StateMachine::StateMachine(std::vector<MidiEvent*> sequence,std::string nom){
	mySequence = sequence;
	name = nom;
}

StateMachine::StateMachine(StateMachine* stateMachine){
    mySequence = stateMachine->getSequence();
    name = stateMachine->getName();
    sequenceBuffer = stateMachine->getSequenceBuffer();
    isCopy = true;
}

bool StateMachine::updateMachine(MidiEvent* message){
	bool result = false;

    //Comparer ce MidiEvent avec le MidiEvent correspondant à sequenceBuffer.size() dans mySequence
	if(message->getNote() == mySequence[sequenceBuffer.size()]->getNote()){
        std::cout<<"Event matched with " << name << " steps confirmed : "<< sequenceBuffer.size() + 1 <<std::endl;
        //Instancier une copie de la machine avant de modifier sequenceBuffer.
        createClone();

        //Si il est bon on ajoute le message dans le sequenceBuffer
		sequenceBuffer.push_back(message);

        //si sequenceBuffer.size() == mySequence.size() -> lancer checkTimes() (on a trouvé assez de notes)
		if(sequenceBuffer.size() == mySequence.size()){
			result = checkTimes();
		}
    }else if(sequenceBuffer.size() != 0){

        //Si ça fait trop longtemps, on détruit la machine / ou bien on la vide.
		if(message->getTimeStamp() - sequenceBuffer[sequenceBuffer.size()]->getTimeStamp() > timeBeforeRestart){
            if(!isCopy){
                resetMachine();
            }else{
                mAnalyzer->removeMachine(this);
            }
    	}
	}
    return result;
}

void StateMachine::createClone(){
    StateMachine* clone = new StateMachine(this);
    mAnalyzer->addMachine(clone);
}

void StateMachine::resetMachine(){
    sequenceBuffer.clear();
}

bool StateMachine::checkTimes(){
    //Comparer les heures d'arrivées de mySequence et de sequenceBuffer. en prenant en compte deltaTime
    //Si on est bon renvoyer true sinon false
    std::cout<<"about to check times"<<std::endl;
    bool result = true;
    double stepTime;
    double normalizedTime;
    //remove delay
    double timeDelay = sequenceBuffer[0]->getTimeStamp();
    for(int i = 0 ; i<sequenceBuffer.size();i++){
        sequenceBuffer[i]->substractTime(timeDelay);
    }

    double estimatedMusicalTime = sequenceBuffer[1]->getTimeStamp() / mySequence[1]->getTimeStamp();

    for(int i = 1; i< mySequence.size(); i++){
        stepTime = sequenceBuffer[i]->getTimeStamp();
        normalizedTime = mySequence[i]->getTimeStamp();
        std::cout<<"checkTimes i : " << i << "\n stepTime =" << stepTime<< "\n wanted Time = " << normalizedTime << "\n estimated tempo :" << estimatedMusicalTime << std::endl;

        if (!(stepTime< normalizedTime * estimatedMusicalTime + authorizedTime && stepTime > normalizedTime*estimatedMusicalTime - authorizedTime)){
            std::cout<<"result = false. i : " << i << std::endl;
            result = false;
        }else{
            estimatedMusicalTime = (estimatedMusicalTime*i + (stepTime / normalizedTime)) / (i+1);
        }
    }
    resetMachine();
    return result;
}

std::string StateMachine::getName(){
	return name;
}


std::vector<MidiEvent*> StateMachine::getSequence(){
    return mySequence;
}

std::vector<MidiEvent*> StateMachine::getSequenceBuffer(){
    return sequenceBuffer;
}

void StateMachine::setMidiAnalyzer(MidiAnalyzer* midiAnalyzer){
    mAnalyzer = midiAnalyzer;
}
