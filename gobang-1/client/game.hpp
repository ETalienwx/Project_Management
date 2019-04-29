#pragma once

#include <iostream>
#include <rpc_client.hpp>
#include <chrono>
#include <stdlib.h>//atoi
#include <string>
#include <fstream>
#include "codec.h"

using namespace std;
using namespace std::chrono_literals;
using namespace rest_rpc;
using namespace rest_rpc::rpc_service;

uint32_t Register(const string &ip, const int &port, string &name, string &passwd, uint32_t &id)
{
    cout << "请输入昵称 : ";
    cin >> name;
    cout << "请输入密码 : ";
    cin >> passwd;
    string passwd_;
    cout << "请确认密码 : ";
    cin >> passwd_;
    if(passwd != passwd_)
    {
        cout << "两次密码不匹配呦！再检查一下吧！" << endl;
        return 1;
    }
    try {
        rpc_client client(ip, port);
        bool r = client.connect();
        if (!r) {
            std::cout << "连接超时" << std::endl;
            return 2;
        }
		id = client.call<uint32_t>("RpcRegister", name, passwd);
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
uint32_t Login(const string &ip, const int &port)
{
    uint32_t id;
    string passwd;
    cout << "请输入你的登录id : ";
    cin >> id;
    cout << "请输入登录密码 : ";
    cin >> passwd;
    uint32_t result = 0;
    try {
        rpc_client client(ip, port);
        bool r = client.connect();
        if (!r) {
            std::cout << "连接超时" << std::endl;
            return 3;
        }
		result = client.call<uint32_t>("RpcLogin", id, passwd);
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    return result;
}
bool PushIdInMatchPool(string &ip, int &port, uint32_t &id)//把id放到匹配池里
{
    try {
        rpc_client client(ip, port);
        bool r = client.connect();
        if (!r) {
            std::cout << "连接超时" << std::endl;
            return 3;
        }
		return client.call<bool>("RpcPushIdInMatchPool", id);
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}
int CheckReady(string &ip, int &port, uint32_t id)
{
    try {
        rpc_client client(ip, port);
        bool r = client.connect();
        if (!r) {
            std::cout << "连接超时" << std::endl;
            return 3;
        }
		return client.call<int>("RpcPlayerReady", id);
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}
bool Match(string &ip, int &port, uint32_t &id)//真正的匹配
{
    PushIdInMatchPool(ip,port,id);//把id先放到匹配池里
    //周期性的检测状态
    while(1)
    {
        int ready = CheckReady(ip, port, id);
        if(ready == 3)
        {
            return true;
        }
        else if(ready == 1)
        {
            return false;
        }
        else//等于2，继续匹配
        {
            sleep(1);
        }
    }
}
void GetBoard(string &ip, int &port, uint32_t &id, string &board)
{
    try {
        rpc_client client(ip, port);
        bool r = client.connect();
        if (!r) {
            std::cout << "连接超时" << std::endl;
            return 3;
        }
		board = client.call<string>("RpcBoard", id);
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

}
void ShowBoard(string &board)
{
    for(auto i = 0; i < board.size(); i++)
    {
        cout << '|' << board[i] << '|' << endl;
    }
}
void PlayGame(uint32_t id)
{
    cout << "匹配成功，开始游戏！" << endl;
}
void Game(string &ip, int &port, uint32_t &id)//登录成功会来到游戏界面
{
    int select = 0;
    volatile bool quit = false;
    while(!quit)
    {
        cout << "**************************************" << endl;
        cout << "***      1.匹配         2.退出     ***" << endl;
        cout << "**************************************" << endl;
        cout << "请选择操作 : ";
        cin >> select;
        switch(select)
        {
            case 1:
                {
                    if(Match(ip,port,id)){//匹配成功进入游戏
                        PlayGame();
                    }
                    else{//匹配失败提示玩家匹配失败
                        cout << "哎呦！匹配失败啦！再试一次吧！" << endl;
                    }
                }
                break;
            case 2:
                quit = true;
                break;
            default:
                cout << "哎呦！你的选择有误，再试一次吧！" << endl;
                break;
        }
    }
}












