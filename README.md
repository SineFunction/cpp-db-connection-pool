# cpp-db-connection-pool
一个简单的、线程安全的数据库连接池，适用于 C++ 应用。
# 参考链接
    https://www.bilibili.com/video/BV1Fr4y1s7w4/?spm_id_from=333.337.search-card.all.click&vd_source=b5c731995684cc8bcb769bc76f57f45a

# MySQL中数据库表的创建
    # 创建数据库 testdb
    CREATE DATABASE IF NOT EXISTS testdb;

    # 选择数据库 testdb
    USE testdb;

    # 创建 users 表
    CREATE TABLE users (
        id INT PRIMARY KEY AUTO_INCREMENT, -- 自增主键，确保唯一且不重复
        name VARCHAR(50) NOT NULL,         -- 用户名，不允许为空
        email VARCHAR(100),                -- 邮箱
        age INT,                            -- 年龄
        created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP -- 记录创建时间，默认为当前时间
    );

    # 每次运行结束后都要在数据库testdb目录下进行删除操作
    delete from users;
