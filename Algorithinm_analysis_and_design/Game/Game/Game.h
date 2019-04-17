#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include "Gaming.h"
#include "PersonPlayer.h"
#include "ComputerPlayer.h"

class Game{
public:         
    Game( ):m_person( ), m_computer( ){
        this->m_gameCount = 0;
        this->m_timeCount = 0;
    }   
    virtual ~Game( ){ };          
    void InitGame( );            // ��ʼ����Ϸ��Ϣ
    int Menu( );                // ��Ϸ�˵�
    void Help( );                // ������Ϣ
    void PlayGame( );            // ������Ϸ�ĺ���
    void EndGame( );             // ��Ϸ����
    int DisResult( );         // ��ʾ�������
    void ShowResult( );      //
    void Gaming( );         // ������Ϸ���й���
protected :         
    void InitComPuter( );               // ��ʼ�������ĵ���
    void InitPerson( );              // ��ʼ����ʵ�ĵ���
    void Delay( );
    void Stop( );
    void Lording( );
    
    PersonPlayer m_person;              // �����Ϣ
    ComputerPlayer m_computer;          // ������Ϣ
    int m_gameCount;                    // ��Ϸ����
    int m_timeCount;                  //   �غϴ���
};
#endif // GAME_H_INCLUDED
