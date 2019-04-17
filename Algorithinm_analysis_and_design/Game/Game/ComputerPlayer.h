#ifndef COMPUTERPLAYER_H_INCLUDED
#define COMPUTERPLAYER_H_INCLUDED
#include "Player.h"

class ComputerPlayer : public Player{
public :
    ComputerPlayer( ):Player( ) { }
    virtual ~ComputerPlayer( ){ }; 
    void InitPlayer( );      
    SelectType Select( );     
};

#endif // COMPUTERPLAYER_H_INCLUDED
