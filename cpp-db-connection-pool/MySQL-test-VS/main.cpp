#include<iostream>
#include<memory>
#include "MysqlConn.h"
#include "ConnectionPool.h"

//1.单线程 使用/不使用连接池

//2.多线程 使用/不使用连接池
void op1(int begin, int end)
{
    for (int i = begin; i <= end; i++) {
        MysqlConn conn;
        conn.connect("root", "321aaabc", "testdb", "127.0.0.1");
        char sql[1024] = { 0 };
        sprintf(sql, "insert into users (id,name,email,age) values(%d,'Bob','123456&gmail.com',33)", i);
        conn.update(sql);
    }
}

void op2(ConnectionPool* pool,int begin, int end)
{
    for (int i = begin; i <= end; i++) {
        std::shared_ptr<MysqlConn> conn = pool->getConnection();
        char sql[1024] = { 0 };
        //"insert into users (id,name,email,age) values(2,'Box','1234567@gmail.com',22)"
        sprintf(sql, "insert into users (id,name,email,age) values(%d,'Bob','123456&gmail.com',33)",i);
        conn->update(sql);
    }
}

void test1()
{
#if 1
    //非连接池，单线程，用时:61704816500纳秒,61704毫秒
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    op1(0, 5000);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    auto length = end - begin;
    std::cout << "非连接池，单线程，用时:" << length.count() << "纳秒," << length.count() / 1000000 << "毫秒" << std::endl;

#else
    //连接池，单线程，用时:22103682300纳秒,22103毫秒
    ConnectionPool* pool = ConnectionPool::getConnectPool();
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    op2(pool,1, 5000);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    auto length = end - begin;
    std::cout << "连接池，单线程，用时:" << length.count() << "纳秒," << length.count() / 1000000 << "毫秒" << std::endl;

#endif

}

void test2()
{
#if 1
    //非连接池，多线程，用时:10109008800纳秒,10109毫秒
    MysqlConn conn;
    conn.connect("root", "321aaabc", "testdb", "127.0.0.1");
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    std::thread t1(op1, 1, 1000);
    std::thread t2(op1, 1001, 2000);
    std::thread t3(op1, 2001, 3000);
    std::thread t4(op1, 3001, 4000);
    std::thread t5(op1, 4001, 5000);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    auto length = end - begin;
    std::cout << "非连接池，多线程，用时:" << length.count() << "纳秒," << length.count() / 1000000 << "毫秒" << std::endl;
#else
    //连接池，多线程，用时:6114508500纳秒,6114毫秒
    ConnectionPool* pool = ConnectionPool::getConnectPool();
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    std::thread t1(op2,pool, 1, 1000);
    std::thread t2(op2,pool, 1001, 2000);
    std::thread t3(op2,pool, 2001, 3000);
    std::thread t4(op2,pool, 3001, 4000);
    std::thread t5(op2,pool, 4001, 5000);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    auto length = end - begin;
    std::cout << "连接池，多线程，用时:" << length.count() << "纳秒," << length.count() / 1000000 << "毫秒" << std::endl;
#endif
}

int query()
{
    MysqlConn conn;
    conn.connect("root", "321aaabc", "testdb", "127.0.0.1");
    std::string sql = "insert into users (id,name,email,age) values(2,'Box','1234567@gmail.com',22)";
    bool flag = conn.update(sql);
    std::cout << "flag value:" << flag << std::endl;

    sql = "select * from users";
    conn.query(sql);
    while (conn.next()) {
        std::cout << conn.value(0) << ","
            << conn.value(1) << ","
            << conn.value(2) << ","
            << conn.value(3) << ","
            << conn.value(4) << "," << std::endl;
    }
    return 0;
}
int main()
{
    SetConsoleOutputCP(CP_UTF8);
    //test1();
    test2();
    return 0;
}