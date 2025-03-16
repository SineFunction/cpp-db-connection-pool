#pragma once
#include<iostream>
#include<mysql.h>
#include<chrono>//时钟对应的头文件
class MysqlConn
{
public:
    //初始化数据库连接
    MysqlConn();

    //释放数据库连接
    ~MysqlConn();

    //连接数据库
    bool connect(std::string user, std::string passwd, std::string dbName, std::string ip, unsigned short port = 3306);

    //更新数据库
    bool update(std::string sql);

    //查询数据库
    bool query(std::string sql);

    //遍历查询得到的结果集
    bool next();

    //得到结果集中的字段值
    std::string value(int index);

    //事务操作
    bool transaction();

    //提交事务
    bool commit();

    //事务回滚
    bool rollback();

    //刷新起始的空闲时间点
    void refreshAliveTime();

    //计算存活的总时长
    long long getAliveTime();

private:
    void freeResult();

    MYSQL* m_conn = nullptr;//在析构函数里释放
    MYSQL_RES* m_result = nullptr;//结果集
    MYSQL_ROW m_row = nullptr;//结果集里面的数据

    std::chrono::steady_clock::time_point m_alivetime;
};