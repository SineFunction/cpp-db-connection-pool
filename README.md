# cpp-db-connection-pool
一个简单的、线程安全的数据库连接池，适用于 C++ 应用。
# 参考链接

https://www.bilibili.com/video/BV1Fr4y1s7w4/?spm_id_from=333.337.search-card.all.click&vd_source=b5c731995684cc8bcb769bc76f57f45a

# MySQL中数据库的创建
    CREATE DATABASE IF NOT EXISTS testdb;
## 数据库表的创建

    CREATE TABLE users (
    id INT PRIMARY KEY AUTO_INCREMENT,
    name VARCHAR(50) NOT NULL,
    email VARCHAR(100),
    age INT,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
    );
