#pragma once

#include"DataBase.h"
#include"DBStruct.h"


class DBTraceAPI
{
    private:
        DataBase DB;//用于调用数据库操作接口

        string localhost;//数据库地址默认localhost
        string user;//登录数据库用户名默认root
        string passwd;//登录数据库密码默认zenos
        string database;//在操作时调用数据库名默认TraceDB

        string table;//在SQL操作时调用的表
        string value;//在SQL操作时需要获取的值或插入的值
        string limits;//在SQL操作时的限制条件

        //enum tablename{DeviceID,Map,blue,white,black};

    public:
        DBTraceAPI();
        DBTraceAPI(string host,string username,string password,string databasename);
        ~DBTraceAPI();
        int DBInitialize(string host,string username,string password,string databasename);
        int DBConnect();
        int DBCreateDB();
        int DBCreateRelatTB();
        int DBCreateTable(DBTrace trace);

        int DBAddDevice(DBDeviceData deviceData);
        int DBAddSomeDevice(vector<DBDeviceData> deviceData);

        int DBAddPerson(DBDeviceData deviceData);
        int DBAddSomePerson(vector<DBDeviceData> deviceData);

        int DBUpdateDevice(string DeviceID,string TableName,int TraceID);
        int DBUpdatePerson(int PersonID,string TableName,int TraceID);

        int DBUpdateDeviceRelat(DBDeviceData deviceData);
        int DBUpdateSomeDeviceRelat(vector<DBDeviceData> deviceData);

        int DBAddMap(Map map);
        int DBAddSomeMap(vector<Map> map);
        int DBAddBCON(BCON bcon);
        int DBAddSomeBCON(vector<BCON> bcon);
        int DBAddMapMark(int mapMark);
        int DBAddSomeMapMark(vector<int> mapMark);

        int DBAddTrace(DBTrace trace);
        int DBAddSomeTrace(vector<DBTrace> trace);
        
        int DBSearchDevice(string DeviceID,DBTrace&pTrace);
        int DBSearchSomeDevice(vector<string> DeviceID,vector<DBTrace>&Trace);
        int DBSearchAllDevice(vector<DBTrace>&Traces);
        int DBSearchPerson(int PersonID,DBTrace&pTrace);
        int DBSearchSomePerson(vector<int> PersonID,vector<DBTrace>&Trace);
        int DBSearchAllPerson (vector<DBTrace>&Traces);
        int DBSearchPersonTrace(int PersonID,ptime timeBegin,ptime timeEnd,vector<DBTrace>&Traces);
        int DBSearchDeviceTrace(string DeviceID,ptime timeBegin,ptime timeEnd,vector<DBTrace>&Traces);

        int DBSearchDeviceID(vector<string>&DeviceID);
        int DBDeleteTrace(DBTrace trace);
        int DBDeleteDevice(string DeviceID);
        int DBDeleteMap(int MapMark);
        int DBUpdateTrace(DBTrace traceOld,DBTrace traceNew);
        int DBClearTable();
        
        int DBMapCount(int PersonID,int MapMark,ptime timeBegin,ptime timeEnd,DBMapData&MapData);
        int DBMapPersonCount(int PersonID, ptime timeBegin,ptime timeEnd,vector<DBMapData>&MapData);
        int DBMapMarkCount(int MapMark,ptime timeBegin,ptime timeEnd,vector<DBMapData>&MapData);
        int DBDeleteDB();
};