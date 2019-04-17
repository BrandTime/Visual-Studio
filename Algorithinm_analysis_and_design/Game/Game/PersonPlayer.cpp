#include "PersonPlayer.h"

bool SayYes( );

void PersonPlayer::InitPlayer( ) {         // 玩家信息初始化
    std::cout <<"请输入您的姓名:";
    std::cin >>this->m_name;            // 输入玩家姓名

    this->m_select = NULLOUT;
    this->m_winCount = 0;
}


SelectType PersonPlayer::Select( ){
    bool reponse = true;
    char temp;
    do{
        std::cout <<std::endl;
        if(reponse == false)
            std::cout <<"作为一个诚实的玩家, 您刚才一定是疏忽了" <<std::endl;
        std::cout <<"请" <<this->m_name <<"选择出拳" <<std::endl;         // 信息提示
        std::cout <<"R|r|1[石头] OR S|s|2[布] OR C|c|3[布]" <<std::endl;
        std::cin >>temp;
        reponse = false;
    }while(this->CheckSelect(temp) == false);      // 只要输入的结果不合法就一直输入

    if(temp == '1' || temp == 'R' || temp == 'r')
        this->m_select = ROCK;          // 玩家出了石头
    else if(temp == 'S' || temp == 's' || temp == '2')
        this->m_select = SCISSOR;           // 玩家出了剪刀
    else if(temp == 'C' || temp == 'c' || temp == '3')
        this->m_select = CLOTH;         // 玩家出了布
    else if(this->m_character == Funny)
        this->m_select = NULLOUT;       // 滑稽的玩家出了空拳
    return this->m_select;
}


bool PersonPlayer::CheckSelect(char temp) {            // 获取用户的选择
    if(this->m_character == Honest       // 诚实的玩家输入必须合法
       && temp != 'R' && temp != 'r' && temp != '1'
       && temp != 'S' && temp != 's' && temp != '2'
       && temp != 'C' && temp != 'c' && temp != '3') {
        return false;
    }
	else               // 滑稽的玩家输入随意值均可
        return true;
}
