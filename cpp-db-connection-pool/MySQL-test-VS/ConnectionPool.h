#pragma once
#include<queue>
#include "MysqlConn.h"
#include<mutex>
#include<condition_variable>

class ConnectionPool
{
public:
    static ConnectionPool* getConnectPool();
    ConnectionPool(const ConnectionPool& obj) = delete;
    ConnectionPool& operator = (const ConnectionPool& obj) = delete;
    std::shared_ptr<MysqlConn> getConnection();
    ~ConnectionPool();
private:
    ConnectionPool();
    bool parseJsonFile();

    //产生连接
    void produceConnection();

    //回收连接
    void recycleConnection();

    //添加连接
    void addConnection();

    std::string m_ip;
    std::string m_user;
    std::string m_passwd;
    std::string m_dbName;
    unsigned short m_port;
    int m_minSize;
    int m_maxSize;
    int m_timeout;
    int m_maxIdleTime;
    std::queue<MysqlConn*> m_connectionQ;
    std::mutex m_mutexQ;
    std::condition_variable m_cond;
};