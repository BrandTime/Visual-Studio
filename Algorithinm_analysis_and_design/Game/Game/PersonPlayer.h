#ifndef PERSONPLAYER_H_INCLUDED
#define PERSONPLAYER_H_INCLUDED
#include "Player.h"

class PersonPlayer : public Player{
public :
    PersonPlayer( ):Player( ){}
    virtual ~PersonPlayer( ){ }       
    void InitPlayer( );         // 玩家信息初始化
    SelectType Select( );// 玩家选择自己的出拳
protected:
    bool CheckSelect(char temp);            // 看用户输入是否合法
};
#endif // PERSONPLAYER_H_INCLUDED
