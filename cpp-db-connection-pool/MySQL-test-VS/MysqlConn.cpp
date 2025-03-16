#include "MysqlConn.h"
//#include "ConnectionPool.h"
MysqlConn::MysqlConn()
{
    m_conn = mysql_init(nullptr);
    mysql_set_character_set(m_conn, "utf8");
}

MysqlConn::~MysqlConn()
{
    if (m_conn != nullptr)
    {
        mysql_close(m_conn);
    }
    freeResult();
}

bool MysqlConn::connect(std::string user, std::string passwd, std::string dbName, std::string ip, unsigned short port)
{
    //mysql_real_connect会返回一个地址，和第一个参数的地址相同，代表成功连接到mysql服务器
    MYSQL* ptr = mysql_real_connect(m_conn, ip.c_str(), user.c_str(), passwd.c_str(), dbName.c_str(), port, nullptr, 0);
    //以下三行是deepseek给的
    if (!ptr) {
        std::cerr << "Database connection failed: " << mysql_error(m_conn) << std::endl;
    }
    return ptr != nullptr;
}

bool MysqlConn::update(std::string sql)
{
    if (mysql_query(m_conn, sql.c_str()))
    {
        return false;
    }
    return true;
}

bool MysqlConn::query(std::string sql)
{
    freeResult();
    if (mysql_query(m_conn, sql.c_str())) {
        return false;
    }
    //保存结果集
    m_result = mysql_store_result(m_conn);
    return true;
}

bool MysqlConn::next()
{
    //对结果集进行遍历
    if (m_result != nullptr) {
        //保存结果集
        m_row = mysql_fetch_row(m_result);
        if (m_row != nullptr) {
            return true;
        }
    }
    return false;
}

std::string MysqlConn::value(int index)
{
    int rowCount = mysql_num_fields(m_result);
    if (index >= rowCount || index < 0) {//查询index是否是一个有效值
        return std::string();
    }
    char* val = m_row[index];
    unsigned long length = mysql_fetch_lengths(m_result)[index];
    //避免std::string遇到\0截断，导致数据不完整
    return std::string(val, length);
}

bool MysqlConn::transaction()
{
    return mysql_autocommit(m_conn, false);
}

bool MysqlConn::commit()
{
    return mysql_commit(m_conn);
}

bool MysqlConn::rollback()
{
    return mysql_rollback(m_conn);
}

void MysqlConn::refreshAliveTime()
{
    m_alivetime = std::chrono::steady_clock::now();
}

long long MysqlConn::getAliveTime()
{
    std::chrono::nanoseconds res = std::chrono::steady_clock::now() - m_alivetime;
    std::chrono::milliseconds millsec = std::chrono::duration_cast<std::chrono::milliseconds>(res);
    return millsec.count();
}

void MysqlConn::freeResult()
{
    if (m_result != nullptr) {
        mysql_free_result(m_result);
        m_result = nullptr;
    }
}