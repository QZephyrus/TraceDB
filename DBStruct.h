#pragma once

#include<string>
#include<vector>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
using std::string;
using namespace boost::posix_time;
using namespace boost::gregorian;

/*typedef struct Time
{
    short year;
    short month;
    short Day;
    short hour;
    short minute;
    short second;
    string datatime;
    void getdatatime(){
        year=atoi(datatime.substr(0,3).c_str());
        month=atoi(datatime.substr(5,6).c_str());
        Day=atoi(datatime.substr(8,9).c_str());
        hour=atoi(datatime.substr(11,12).c_str());
        minute=atoi(datatime.substr(14,15).c_str());
        second=atoi(datatime.substr(17,18).c_str());
    }
    string todatatime(){
        datatime=to_string(year)+"-"+to_string(month)+"-"+to_string(Day)+" "+to_string(hour)+":"+to_string(minute)+":"+to_string(second);
        return datatime;
    }
}Time;*/

//定义双重vector构成的存储string类型的表，定义为string_table
typedef vector<vector<string>> string_table;

//定义类DBTrace，用来存储轨迹信息
class DBTrace
{
    public:
	    int PersonID;
	    short PersonModule;
        string DeviceID;
        float X;
        float Y;
        string Floor;
        int MapMark;
        string time;
        string TableName;
        int TraceID;

        //用于从双重vector构成的string表（string_table）获取单条的轨迹信息并且保存自身
        void readTrace(string_table ret){
            TraceID=atoi(ret[0][0].c_str());
            PersonID=atoi(ret[0][1].c_str());
            PersonModule=atoi(ret[0][2].c_str());
            DeviceID=ret[0][3];
            X=atof(ret[0][4].c_str());
            Y=atof(ret[0][5].c_str());
            Floor=ret[0][6];
            MapMark=atof(ret[0][7].c_str());
            time=ret[0][8];
        }
        //用于从双重vector构成的string表（string_table）获取多条的轨迹信息并且返回一个用vector<DBTrace>存储的轨迹链
        vector<DBTrace> readTraces(string_table ret){
            int rows=ret.size();
            vector<DBTrace> Trace;
            DBTrace trace;
            for(int i=0;i<rows;i++){
                trace.TraceID=atoi(ret[i][0].c_str());
                trace.PersonID=atoi(ret[i][1].c_str());
                trace.PersonModule=atoi(ret[i][2].c_str());
                trace.DeviceID=ret[i][3];
                trace.X=atof(ret[i][4].c_str());
                trace.Y=atof(ret[i][5].c_str());
                trace.Floor=ret[i][6];
                trace.MapMark=atof(ret[i][7].c_str());
                trace.time=ret[i][8];
                Trace.push_back(trace);
            }
            return Trace;
        }
};

//自定义类用于存储设备和人员之间的绑定关系，已便于更新设备信息和人员信息
class DBDeviceData
{
    public:
	    int PersonID;
	    short PersonModule;
        string DeviceID;
};

//自定义Map类用于存储围栏信息和其对应的BCONID
class Map
{
    public:
        int MapID;
        int MapMark;
        int BCONID;
};

//自定义BCON类用于存储BCON的位置信息
class BCON
{
    public:
        int BCONID;
        float BCONX;
        float BCONY;
        string Floor;
};

//自定义DBMaoData类用于统计进出围栏次数和在围栏内持续时间
class DBMapData
{
    public:
	    int PersonID;
        int MapMark;
        int Enter;
        int Out;
        time_duration StayTime;
        //构造函数用于初始化数据
        DBMapData(int PerID,int MMark){
            PersonID=PerID;
            MapMark=MMark;
            Enter=0;
            Out=0;
        }
        DBMapData(){
            Enter=0;
            Out=0;
        }
};



