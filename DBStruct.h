#include<string>

using std::string;

typedef struct Time
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
};

typedef struct DBTrace
{
	int PersonID;
	short PersonModule;
    string DeviceID;
    float X;
    float Y;
    string Floor;
    int MapMark;
    Time time;
    int TraceID;
    void readTrace(vector<vector<string>> ret){
        TraceID=atoi(ret[0][0].c_str());
        PersonID=atoi(ret[0][1].c_str());
        PersonModule=atoi(ret[0][2].c_str());
        DeviceID=ret[0][3];
        X=atof(ret[0][4].c_str());
        Y=atof(ret[0][5].c_str());
        Floor=ret[0][6];
        MapMark=atof(ret[0][7].c_str());
        time.datatime=ret[0][8];
    }
    vector<DBTrace> readTraces(vector<vector<string>> ret){
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
            trace.time.datatime=ret[i][8];
            Trace.push_back(trace);
        }
        return Trace;
    }
};

typedef struct DBDeviceData
{
	int PersonID;
	short PersonModule;
    string DeviceID;
};

typedef struct Map
{
    int MapID;
    int MapMark;
    int BCONID;
};

typedef struct BCON
{
    int BCONID;
    float BCONX;
    float BCONY;
    string Floor;
};

typedef struct DBMapData
{
	int PersonID;
    int MapMark;
    int Enter;
    int Out;
    Time StayTime;
    void initPersonData(int PerID,int MMark){
        PersonID=PerID;
        MapMark=MMark;
        Enter=0;
        Out=0;
        StayTime.year=0;
        StayTime.month=0;
        StayTime.Day=0;
        StayTime.hour=0;
        StayTime.minute=0;
        StayTime.second=0;
    }
};



