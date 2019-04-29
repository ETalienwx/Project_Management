#pragma once

#include <iostream>
#include <unordered_map>
#include <string>
#include "Log.hpp"
#include "Player.hpp"

#define DEFAULT_ID 10000

using namespace std;

class PlayerManager
{
    private:
        unordered_map<uint32_t, Player> player_set;
        uint32_t assign_id;//起始id
    public:
        PlayerManager()
            :assign_id(DEFAULT_ID)
        {

        }
        uint32_t InsertPlayer(string &name, string &passwd)//对应注册
        {
            uint32_t id_ = assign_id++;
            Player p(name, passwd, id_);
            player_set.insert({id_, p});
            LOG(INFO, "Insert this player done...");
            return id_;
        }
        uint32_t SearchPlayer(uint32_t id, string &passwd)//对应登录
        {
            unordered_map<uint32_t,Player>::iterator it = player_set.find(id);
            if(it == player_set.end())
            {
                LOG(WARNING, "Search player error.This player is not register.");
                return 1;
            }
            //找到这个id的用户了
            Player &p = it->second;
            if(p.Passwd() != passwd)
            {
                LOG(WARNING, "Player passwd error.");
                return 2;
            }
            //密码相同可以登录
            p.Online();
            LOG(INFO, "Player online success!");
            return id;
        }
     //   void SignalPlayer(uint32_t one,uint32_t two)
     //   {
     //       player_set[one].Signal();
     //       player_set[two].Signal();
     //   }
        void SetPlayerStatus(uint32_t &one,uint32_t &two)
        {
            player_set[one].Playing();
            player_set[two].Playing();
        }
        void SetPlayerRoom(uint32_t &room_id, uint32_t &one, uint32_t &two)
        {
            player_set[one].SetRoom(room_id);
            player_set[two].SetRoom(room_id);
        }
        uint32_t GetPlayerRoomId(uint32_t &id)
        {
            return player_set[id].Room();
        }
        void SetMatching(uint32_t id)
        {
            player_set[id].Matching();
        }
     //   bool PlayerWait(uint32_t id)
     //   {
     //       if(ETIMEDOUT == player_set[id].Wait())
     //       {
     //           return false;
     //       }
     //       return true;
     //   }
        int GetRate(uint32_t id)//获取胜率
        {
            return player_set[id].Rate();
        }
        int Ready(uint32_t id)
        {
            return player_set[id].Status();//返回用户的状态，看是不是游戏中
        }
        ~PlayerManager()
        {
        }
};

















