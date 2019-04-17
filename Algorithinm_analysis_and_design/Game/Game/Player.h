#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
#include <iostream>
#include "Gaming.h"
#include <string>
#define Funny false     // ����������ǻ����ȭ��
#define Honest true     // ��ʵ����Ҳ������ȭ, ��˳�ʵ�����������˴������Ϣ�ǻᱻ���ѵ�
using namespace std;
// �����
class Player{
public:
    Player( ) {
        this->m_name = "NULLNAME";
        this->m_winCount = 0;
        this->m_totalCount = 0;
    }  
    virtual ~Player( ){ }          
    virtual void InitPlayer( ) = 0;          // �����Ϣ��ʼ��
    void SetName(std::string name);             // ������ҵ�����
    string GetName( );                 // ��ȡ��ҵ�����
    SelectType GetSelect( );        // ��ȡ��ҵĳ�ȭ��Ϣ
    bool GetCharacter( );           // ��ȡ��ҵ��Ը���Ϣ
    int GetWinCount( );             // ��ȡ��ҵķ���
    void ShowSelect( );         // ��ʾ��ҵĳ�ȭ��Ϣ
    bool SelectCharacter( );        // �޸�������Ը�
    void ShowCharacter( );      // ��ʾ��ҵ��Ը�
    virtual SelectType Select( ) = 0;              // ѡ��
    int AddWinCount( );         // ��ʤ��Ŀ����1
    int AddTotalCount( );      // ��ʤ�ܼ�
    int GetTotalCount( );
protected :   
    string m_name;         // ��ҵ�����
    SelectType m_select;        // ��ҵ�ѡ����Ϣ
    int m_winCount;             // ��ҵĻ�ʤ��Ŀ������
    int m_totalCount;           // ����ܼ�
    bool m_character;             // ����Ƿ�Ὺ��Ц[����Ц������ǻ����ȭ��]
};
#endif // PLAYER_H_INCLUDED
