#ifndef PERSONPLAYER_H_INCLUDED
#define PERSONPLAYER_H_INCLUDED
#include "Player.h"

class PersonPlayer : public Player{
public :
    PersonPlayer( ):Player( ){}
    virtual ~PersonPlayer( ){ }       
    void InitPlayer( );         // �����Ϣ��ʼ��
    SelectType Select( );// ���ѡ���Լ��ĳ�ȭ
protected:
    bool CheckSelect(char temp);            // ���û������Ƿ�Ϸ�
};
#endif // PERSONPLAYER_H_INCLUDED
