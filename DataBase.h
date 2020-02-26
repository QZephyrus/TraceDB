#pragma once

#include"mysql/mysql.h"
#include<string>
#include<vector>
#include<iostream>

using std::string;
using std::vector;

class DataBase
{
    private:
        MYSQL *sql;
        MYSQL_RES *res;
        MYSQL_ROW row;
        bool connect_flag;
        void showres();
    public:
        DataBase();
        DataBase(MYSQL *mysql);
        ~DataBase();
        bool connect(const string host,const string user,const string passwd);
        bool connect(const string host,const string user,const string passwd,const string database);
        void disconnect();
        bool showDB();
        bool createDB(const string &database);
        bool useDB(const string &database);
        bool autoCommitOff();
        bool autoCommitOn();
        bool commit();
        bool rollback();
        bool deleteDB(const string &database);
        bool deleteTB(const string &table);
        bool clearTB(const string &table);
        bool showTB();
        bool createTB(const string &table,const string &elements);
        vector<vector<string>> selectItem(const string &table,const string &value);
        vector<vector<string>> selectItem(const string &table, const string &value, const string &limits);
        vector<vector<string>> selectItem(const string &sentence);
        bool insertItem(const string &table,const string &value);
        bool insertItem(const string &table,const string &value,const string &col);
        bool deleteItem(const string &table, const string &value);
	    bool updateItem(const string &table, const string &value, const string &limits);
	    bool query(const string &command);
};