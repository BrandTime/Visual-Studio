#include <stdlib.h>
#include <time.h>
#include "ComputerPlayer.h"

bool SayYes( );

void ComputerPlayer::InitPlayer( ){
    this->m_select = NULLOUT;
    this->m_winCount = 0;

    std::cout <<std::endl;
    std::cout <<"******************************************" <<std::endl;
    std::cout <<"*请问你是否同意一个诚实的电脑加入您的游戏*" <<std::endl;
    std::cout <<"***诚实的电脑出空拳会被游戏认为是误操作***" <<std::endl;
    std::cout <<"******************************************" <<std::endl;
    if(SayYes( ) == true) {
        this->m_character = Honest;     // 诚实的玩家
        this->SetName("Honnest");      // 设置电脑姓名
    }
    else{
        this->m_character = Funny;      // 滑稽的玩家
        this->SetName("Funny");
    }
}

SelectType ComputerPlayer::Select( ){
	int SIZE = ((this->m_character == Funny) ? 4 : 3);
    srand(time(NULL));
    this->m_select = (SelectType)(rand( ) % SIZE + 1);
    return this->m_select;
}
