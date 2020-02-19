#include"DataBase.h"
#include"DBStruct.h"
using namespace std;

class DBTraceAPI
{
    private:
        DataBase DB;
        string localhost;
        string user;
        string passwd;
        string database;
        string table;
        string value;
        string limits;
    public:
        DBTraceAPI();
        ~DBTraceAPI();
        int DBInitialize();
        int DBConnect();
        int DBCreateDB();
        int DBCreateRelatTB();
        int DBCreateTable(DBTrace trace);
        int DBAddDevice(DBDeviceData deviceData);
        int DBAddSomeDevice(vector<DBDeviceData> deviceData);
        int DBUpdateDevice(DBDeviceData deviceData);
        int DBUpdateSomeDevice(vector<DBDeviceData> deviceData);
        int DBAddMap(Map map);
        int DBAddSomeMap(vector<Map> map);
        int DBAddBCON(BCON bcon);
        int DBAddSomeBCON(vector<BCON> bcon);
        int DBAddTrace(DBTrace trace);
        int DBAddSomeTrace(vector<DBTrace> trace);
        int DBSearchDevice(string DeviceID,DBTrace *pTrace);
        int DBSearchSomeDevice(vector<string> DeviceID,vector<DBTrace>&Trace);
        int DBSearchAllDevice(vector<DBTrace>&Traces);
        int DBSearchPerson(int PersonID,DBTrace *pTrace);
        int DBSearchSomePerson(vector<int> PersonID,vector<DBTrace>&Trace);
        int DBSearchAllPerson (vector<DBTrace>&Traces);
        int DBSearchPersonTrace(int PersonID,Time timeBegin,Time timeEnd,vector<DBTrace>&Traces);
        int DBSearchDeviceTrace(string DeviceID,Time timeBegin,Time timeEnd,vector<DBTrace>&Traces);
        int DBSearchDeviceID(vector<string>&DeviceID);
        int DBDeleteTrace(DBTrace trace);
        int DBDeleteDevice(string DeviceID);
        int DBDeleteMap(int MapMark);
        int DBUpdateTrace(DBTrace traceOld,DBTrace traceNew);
        int DBClearTable();
        int DBMapCount(int PersonID,int MapMark,Time timeBegin,Time timeEnd,DBMapData *pMapData);
        int DBMapPersonCount(int PersonID, Time timeBegin,Time timeEnd,vector<DBMapData>&MapData);
        int DBMapMarkCount(int MapMark,Time timeBegin,Time timeEnd,vector<DBMapData>&MapData);

};