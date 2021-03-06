#include <iostream>
#include <rpc_server.h>
#include "Hall.hpp"

using namespace std;
using namespace rest_rpc;
using namespace rpc_service;

//#include "qps.h"
//
//struct dummy{
//	int add(connection* conn, int a, int b) { return a + b; }
//};
//
//std::string translate(connection* conn, const std::string& orignal) {
//	std::string temp = orignal;
//	for (auto& c : temp) { 
//		c = std::toupper(c); 
//	}
//	return temp;
//}
//
//void hello(connection* conn, const std::string& str) {
//	std::cout << "hello " << str << std::endl;
//}
//
//struct person {
//	int id;
//	std::string name;
//	int age;
//
//	MSGPACK_DEFINE(id, name, age);
//};
//
//std::string get_person_name(connection* conn, const person& p) {
//	return p.name;
//}
//
//person get_person(connection* conn) {
//	return { 1, "tom", 20 };
//}
//
//void upload(connection* conn, const std::string& filename, const std::string& content) {
//	std::cout << content.size() << std::endl;
//	std::ofstream file(filename, std::ios::binary);
//	file.write(content.data(), content.size());
//}
//
//std::string download(connection* conn, const std::string& filename) {
//	std::ifstream file(filename, std::ios::binary);
//	if (!file) {
//		return "";
//	}
//
//	file.seekg(0, std::ios::end);
//	size_t file_len = file.tellg();
//	file.seekg(0, std::ios::beg);
//	std::string content;
//	content.resize(file_len);
//	file.read(&content[0], file_len);
//	std::cout << file_len << std::endl;
//
//	return content;
//}
//
//qps g_qps;
//
//std::string get_name(connection* conn, const person& p) {
//	g_qps.increase();
//	return p.name;
//}

Hall GameHall;

uint32_t RpcRegister(connection* conn, string name,string passwd)
{
    cout << "Get a register request. Name is: "<< name <<" Passwd is: "<< passwd<<endl;
    return GameHall.Register(name, passwd);
}
uint32_t RpcLogin(connection* conn, uint32_t id, string passwd)
{
    return GameHall.Login(id, passwd);
}
bool RpcPushIdInMatchPool(connection* conn, uint32_t id)
{
    return GameHall.PushIdInMatchPool(id);
}
int RpcPlayerReady(connection* conn, uint32_t id)
{
    return GameHall.IsPlayerReady(id);
}
string RpcBoard(connection* conn, uint32_t id)
{
    return GameHall.GetPlayerBoard(id);
}
uint32_t RpcPlayerRoomId(connection* conn, uint32_t id)
{
    return GameHall.GetPlayerRoomId(id);
}
char RpcPlayerPiece(connection* conn, uint32_t room_id, uint32_t id)
{
    return GameHall.GetPlayerPiece(room_id, id);
}
int main() {
    rpc_server server(9000, 4);

    LOG(INFO, "Server init complete!");

    server.register_handler("RpcRegister", RpcRegister);
    server.register_handler("RpcLogin", RpcLogin);
    server.register_handler("RpcPushIdInMatchPool", RpcPushIdInMatchPool);
    server.register_handler("RpcPlayerReady", RpcPlayerReady);
   // server.register_handler("RpcBoard", RpcBoard);
   // server.register_handler("RpcPlayerRoomId", RpcPlayerRoomId);
   // server.register_handler("RpcPlayerPiece", RpcPlayerPiece);

    LOG(INFO, "Register all function...done");
    LOG(INFO, "Server start...done");
    GameHall.InitHall();

    server.run();

	std::string str;
	std::cin >> str;
}
