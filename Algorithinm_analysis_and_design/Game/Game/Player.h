#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
#include <iostream>
#include "Gaming.h"
#include <string>
#define Funny false     // 滑稽的玩家是会出空拳的
#define Honest true     // 诚实的玩家不会出空拳, 因此诚实的玩家如果出了错误的信息是会被提醒的
using namespace std;
// 玩家类
class Player{
public:
    Player( ) {
        this->m_name = "NULLNAME";
        this->m_winCount = 0;
        this->m_totalCount = 0;
    }  
    virtual ~Player( ){ }          
    virtual void InitPlayer( ) = 0;          // 玩家信息初始化
    void SetName(std::string name);             // 更改玩家的姓名
    string GetName( );                 // 获取玩家的姓名
    SelectType GetSelect( );        // 获取玩家的出拳信息
    bool GetCharacter( );           // 获取玩家的性格信息
    int GetWinCount( );             // 获取玩家的分数
    void ShowSelect( );         // 显示玩家的出拳信息
    bool SelectCharacter( );        // 修改任务的性格
    void ShowCharacter( );      // 显示玩家的性格
    virtual SelectType Select( ) = 0;              // 选择
    int AddWinCount( );         // 获胜数目增加1
    int AddTotalCount( );      // 获胜总计
    int GetTotalCount( );
protected :   
    string m_name;         // 玩家的姓名
    SelectType m_select;        // 玩家的选择信息
    int m_winCount;             // 玩家的获胜数目计数器
    int m_totalCount;           // 玩家总计
    bool m_character;             // 玩家是否会开玩笑[开玩笑的玩家是会出空拳的]
};
#endif // PLAYER_H_INCLUDED
