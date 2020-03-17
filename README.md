# TraceDB
mysql 版本5.7.29

boost 版本1.65.1

安装命令

boost安装
ubantu18.04使用下面指令默认安装boost 1.65.1
sudo apt-get install libboost-dev

mysql安装
sudo apt-get install mysql-server
apt-get isntall mysql-client
sudo apt-get install libmysqlclient-dev
还需对安装后的数据库进行账户密码的设置
本代码采用的mysql数据库用户名为root，密码为zenos
mysql输入下列指令，以允许GROUP BY的使用
set @@sql_mode='STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION';