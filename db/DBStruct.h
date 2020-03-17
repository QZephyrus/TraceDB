#pragma once

#include<string>
#include<vector>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include<iostream>
using namespace std;
using std::string;
using std::vector;
using namespace boost::posix_time;
using namespace boost::gregorian;


//定义双重vector构成的存储string类型的表，定义为string_table
typedef vector<vector<string>> string_table;

//定义类DBTrace，用来存储轨迹信息
class DBTrace
{
    public:
        DBTrace(){};
        DBTrace(int PerID,short PerModule,string DevID,float XF,float YF,string FloorF,int MMark,string t,string TBName,int TID):PersonID(PerID),PersonModule(PerModule),DeviceID(DevID),X(XF),Y(YF),Floor(FloorF),MapMark(MMark),time(t),TableName(TBName),TraceID(TID){};
        DBTrace(int PerID,short PerModule,string DevID,float XF,float YF,string FloorF,int MMark,string t):PersonID(PerID),PersonModule(PerModule),DeviceID(DevID),X(XF),Y(YF),Floor(FloorF),MapMark(MMark),time(t){};
        void setValue(int TraID,int PerID,short PerModule,string DevID,float XF,float YF,string FloorF,int MMark,string t){
            TraceID=TraID;
            PersonID=PerID;
            PersonModule=PerModule;
            DeviceID=DevID;
            X=XF;
            Y=YF;
            Floor=FloorF;
            MapMark=MMark;
            time=t;
        };
        void setValue(int PerID,short PerModule,string DevID,float XF,float YF,string FloorF,int MMark,string t){
            PersonID=PerID;
            PersonModule=PerModule;
            DeviceID=DevID;
            X=XF;
            Y=YF;
            Floor=FloorF;
            MapMark=MMark;
            time=t;
        };
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
        DBTrace read(vector<string> ret){
            DBTrace temp;
            temp.TraceID=atoi(ret[0].c_str());
            temp.PersonID=atoi(ret[1].c_str());
            temp.PersonModule=atoi(ret[2].c_str());
            temp.DeviceID=ret[3];
            temp.X=atof(ret[4].c_str());
            temp.Y=atof(ret[5].c_str());
            temp.Floor=ret[6];
            temp.MapMark=atof(ret[7].c_str());
            temp.time=ret[8];
            return temp;
        }

        DBTrace readTrace(string_table ret){
            DBTrace temp=read(ret[0]);
            return temp;
        }
        
        //用于从双重vector构成的string表（string_table）获取多条的轨迹信息并且返回一个用vector<DBTrace>存储的轨迹链
        vector<DBTrace> readTraces(string_table ret){
            vector<DBTrace> Trace;
            DBTrace trace;
            ptime tick,now;
            time_duration diff;
            tick=microsec_clock::local_time();
            for(auto &v:ret){
                trace=read(v);
                Trace.push_back(trace);
            }
            now=microsec_clock::local_time();
            diff=now-tick;	
	        cout<<"use "<<diff.total_milliseconds()<<" ms"<<endl;
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
        int PersonModule;
        int MapMark;
        int Enter;
        int Out;
        int rate;
        time_duration StayTime;
        //构造函数用于初始化数据
        DBMapData(int PerID,int PerMod,int MMark):PersonID(PerID),PersonModule(PerMod),MapMark(MMark),Enter(0),Out(0),rate(0),StayTime(time_from_string("2020-02-01 00:00:00")-time_from_string("2020-02-01 00:00:00")){}
        DBMapData():Enter(0),Out(0),rate(0),StayTime(time_from_string("2020-02-01 00:00:00")-time_from_string("2020-02-01 00:00:00")){}
        void initData(int PerID,int PerMod,int MMark){
            PersonID=PerID;
            PersonModule=PerMod;
            MapMark=MMark;
            Enter=0;
            Out=0;
            rate=0;
            StayTime=time_from_string("2020-02-01 00:00:00")-time_from_string("2020-02-01 00:00:00");
        }
};



