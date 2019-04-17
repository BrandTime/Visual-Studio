#include "Player.h"
#include <algorithm>
#include <iomanip>

// ���û��Ƿ�������ye
bool SayYes( );

int Player::AddWinCount( ){         // ��ʤ��Ŀ����1
    return ++this->m_winCount;             // ��ʤ��������1
}

void Player::SetName(std::string name){             // ������ҵ�����
    this->m_name = name;
}

std::string Player::GetName( ) {                 // ��ȡ��ҵ�����
    return this->m_name;                // ��ҵ�����
}


int Player::GetWinCount( ) {             // ��ȡ��ҵķ���
    return this->m_winCount;               // ��ȡ��ҵķ���
}


void Player::ShowCharacter( ) {      // ��ʾ��ҵ��Ը�
    if(this->m_character == Honest)
        cout <<"��ʵ�Ƚ�" <<endl;
    else
        cout <<"����̰��" <<endl;
}

SelectType Player::GetSelect( ) {        // ��ȡ��ҵĳ�ȭ��Ϣ
    return this->m_select;
}

bool Player::GetCharacter( ) {           // ��ȡ��ҵ��Ը���Ϣ
    return this->m_character;
}

void Player::ShowSelect( ) {         // ��ʾ��ҵĳ�ȭ��Ϣ
    switch((int)this->m_select)
    {
    case ROCK:
        cout <<"������" <<setw(10)<<this->GetName( ) <<" ��ȭ��ʯͷ" <<std::endl;
        break;
    case SCISSOR:
        std::cout <<"������" <<std::setw(10)<<this->GetName( ) <<" ��ȭ������" <<std::endl;
        break;
    case CLOTH:
        std::cout <<"������" <<std::setw(10)<<this->GetName( ) <<"��ȭ������" <<std::endl;
        break;
    case NULLOUT:
        std::cout <<"������" <<std::setw(10)<<this->GetName( ) <<"ѡ�񲻳�" <<std::endl;
        break;
    }

}


bool Player::SelectCharacter( ) {       // �޸�������Ը�
    std::cout <<std::endl;
    std::cout <<"******************************************" <<std::endl;
    std::cout <<"**�������Ƿ�ͬ����һ����ʵ����Ҳμ���Ϸ**" <<std::endl;
    std::cout <<"**��ʵ����ҳ���ȭ�ᱻ��Ϸ��Ϊ�������..**" <<std::endl;
    std::cout <<"******************************************" <<std::endl;
    if(SayYes( ) == true)
        this->m_character = Honest;     // ��ʵ�����
    else
        this->m_character = Funny;      // ���������
    return this->m_character;
}

int Player::AddTotalCount( ) {      // ��ʤ�ܼ�
    this->m_totalCount += this->m_winCount;

    return this->m_totalCount;
}


int Player::GetTotalCount( ) {
    return this->m_totalCount;
}
