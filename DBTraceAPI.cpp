#include "DBTraceAPI.h"

using namespace std;

#define DB_RET_OK 1
#define DB_RET_FALL 2
#define DB_RET_CREAT_ERROR 3
#define DB_RET_ADD_ERROR 4
#define DB_RET_ERORR 5
#define DB_RET_DEVICE_ ERROR 6
#define DB_RET_NULL 7
#define DB_RET_PERSON_ ERROR 8
#define DB_RET_TIME_ERROR 9
#define DB_RET_TABLE_ERROR 10
#define DB_RET_TRACE_ERROR 11
#define DB_RET_MAP_ERROR 12
#define DB_RET_TRACEOLD_ERROR 13
#define DB_RET_TRACENEW_ERROR 14
#define DB_RET_MapMark_ERROR 15
#define MemoryMonth 3

DBTraceAPI::DBTraceAPI(){   
    database="TraceDB";
}


DBTraceAPI::~DBTraceAPI(){   
}

int DBTraceAPI::DBInitialize(){
    
}

int DBTraceAPI::DBConnect(){
    judge_flag=DB.connect(localhost,user,passwd);
    if(judge_flag){
        result_flag=DB_RET_OK;
        return result_flag;
    }else{
        result_flag=DB_RET_FALL;
        return result_flag;
    }
}

int DBTraceAPI::DBCreateDB(){
    DB.createDB(database);
    DB.useDB(database);
    DB.createTB("Device_Person","DeviceID varchar(255) NOT NULL,PersonID int NULL,PersonModule tinyint NULL, PRIMARY KEY (DeviceID)");
    DB.createTB("Map","MapID int NOT NULL AUTO_INCREMENT,MapMark bigint NULL,BCONID bigint NULL,PRIMARY KEY (MapID)");
    DB.createTB("BCON","BCONID bigint NOT NULL,BCONX float NULL,BCONY float NULL,BCONFloor char(4) NULL,PRIMARY KEY (BCONID)");
    DB.createTB("Trace","TableID int UNSIGNED NOT NULL AUTO_INCREMENT,TableName char(11) NULL,Year int NULL,Month int NULL,PRIMARY KEY (TableID)");
    DB.createTB("Device","DeviceID varchar(255) NOT NULL,TableName char(11) NULL,TraceID int UNSIGNED NOT NULL, PRIMARY KEY (DeviceID)");
    DB.createTB("Person","PersonID int NOT NULL,PersonModule tinyint NULL,TableName char(11) NULL,TraceID int UNSIGNED NOT NULL, PRIMARY KEY (PersonID)");
    DB.createTB("MapMark","MapMarkID int NOT NULL AUTO_INCREMENT,MapMark bigint NOT NULL,PRIMARY KEY (MapMarkID)");
}

int DBTraceAPI::DBCreateTable(DBTrace trace){
    if(trace.time.month<10){
        table="Trace"+to_string(trace.time.year)+"0"+to_string(trace.time.month);
    }else{
        table="Trace"+to_string(trace.time.year)+to_string(trace.time.month);
    }
    DB.createTB(table,"TraceID int UNSIGNED NOT NULL AUTO_INCREMENT,PersonID bigint NULL,PersonModule tinyint NULL,DeviceID varchar(255) NULL,X float NULL,Y float NULL,Floor char(4) NULL,MapMark bigint NULL,Time datetime NULL,PRIMARY KEY (TraceID)");
    for(int i=0;i<MemoryMonth;i++){
        value=table+", "+to_string(trace.time.year)+", "+to_string(trace.time.month+i);
        DB.insertItem("Trace",value);
    }
}

int DBTraceAPI::DBAddDevice(DBDeviceData deviceData){
    table="Device";
    value="\""+deviceData.DeviceID+"\"";
    DB.insertItem(table,value);
    table="Device_Person";
    value="\""+deviceData.DeviceID+"\", "+to_string(deviceData.PersonID)+", "+to_string(deviceData.PersonModule);
    DB.insertItem(table,value);
}

int DBTraceAPI::DBUpdateDevice(DBDeviceData deviceData){
    table="Device_Person";
    value="PersonID="+to_string(deviceData.PersonID)+", PersonModule="+to_string(deviceData.PersonModule);
    limits="DeviceID="+deviceData.DeviceID;
    DB.updateItem(table,value,limits);
}

int DBTraceAPI::DBAddMap(Map map){
    table="Map";
    value=to_string(map.MapMark)+", "+to_string(map.BCONID);
    DB.insertItem(table,value);
}

int DBTraceAPI::DBAddBCON(BCON bcon){
    table="BCON";
    value=to_string(bcon.BCONID)+", "+to_string(bcon.BCONX)+", "+to_string(bcon.BCONY)+", \""+bcon.Floor+"\"";
    DB.insertItem(table,value);
}

int DBTraceAPI::DBAddTrace(DBTrace trace){
    table="Trace";
    value="TableName";
    limits="Year="+to_string(trace.time.year)+" AND Month="+to_string(trace.time.month);
    vector<vector<string>> ret=DB.selectItem(table,value,limits);
    if(ret.size()==0){
        DBCreateTable(trace);
        DBAddTrace(trace);
    }else if(ret.size==1){
        table=ret[0][0];
        value=to_string(trace.PersonID)+", "+to_string(trace.PersonModule)+", \""+trace.DeviceID+"\", "+to_string(trace.X)+", "+to_string(trace.Y)+", \""+trace.Floor+"\", "+to_string(trace.MapMark)+", \""+trace.time.todatatime()+"\"";
        DB.insertItem(table,value);
    }
}

int DBTraceAPI::DBSearchDevice(string DeviceID,DBTrace *pTrace){
    table="Device";
    value="TableName,TraceID";
    limits="DeviceID="+DeviceID;

    vector<vector<string>> ret=DB.selectItem(table,value,limits);
    if(ret.size()==0){
        
    }else if(ret.size()==1){
        table=ret[0][0];
        value="*";
        limits="TraceID="+ret[0][1];
        vector<vector<string>> temp=DB.selectItem(table,value,limits);
        DBTrace trace;
        trace.readTrace(temp);
        *pTrace=trace;
    }
}

int DBTraceAPI::DBSearchSomeDevice(vector<string> DeviceID,vector<DBTrace>&Trace){
    for(int i=0;i<DeviceID.size();i++){
        DBTrace *tempTrace;
        DBSearchDevice(DeviceID[i],tempTrace);
        Trace.push_back(*tempTrace);
    }
}

int DBTraceAPI::DBSearchAllDevice(vector<DBTrace>&Traces){
    vector<vector<string>> tablename;
    table="Device";
    value="TableName,TraceID";
    limits="TraceID IS NOT NULL";
    tablename=DB.selectItem(table,value,limits);
    int rows=tablename.size();
    for(int i=0;i<rows;i++){
        table=tablename[i][0];
        value="*";
        limits="TraceID="+tablename[i][1];
        vector<vector<string>> temp=DB.selectItem(table,value,limits);
        DBTrace trace;
        trace.readTrace(temp);
        Traces.push_back(trace);
    }
}

int DBTraceAPI::DBSearchPerson(int PersonID,DBTrace *pTrace){
    table="Person";
    value="TableName,TraceID";
    limits="DeviceID="+to_string(PersonID);

    vector<vector<string>> ret=DB.selectItem(table,value,limits);
    if(ret.size()==0){
        
    }else if(ret.size()==1){
        table=ret[0][0];
        value="*";
        limits="TraceID="+ret[0][1];
        vector<vector<string>> temp=DB.selectItem(table,value,limits);
        DBTrace trace;
        trace.readTrace(temp);
        *pTrace=trace;
    }
}

int DBTraceAPI::DBSearchSomePerson(vector<int> PersonID,vector<DBTrace>&Trace){
    for(int i=0;i<PersonID.size();i++){
        DBTrace *tempTrace;
        DBSearchPerson(PersonID[i],tempTrace);
        Trace.push_back(*tempTrace);
    }
}

int DBTraceAPI::DBSearchAllPerson (vector<DBTrace>&Traces){
    vector<vector<string>> tablename;
    table="Person";
    value="TableName,TraceID";
    limits="TraceID IS NOT NULL";
    tablename=DB.selectItem(table,value,limits);
    int rows=tablename.size();
    for(int i=0;i<rows;i++){
        table=tablename[i][0];
        value="*";
        limits="TraceID="+tablename[i][1];
        vector<vector<string>> temp=DB.selectItem(table,value,limits);
        DBTrace trace;
        trace.readTrace(temp);
        Traces.push_back(trace);
    }
}

int DBTraceAPI::DBSearchPersonTrace(int PersonID,Time timeBegin,Time timeEnd,vector<DBTrace>&Traces){
    string tracetable1,tracetable2;
    table="Trace";
    value="TableName";
    limits="(Year="+to_string(timeBegin.year)+" AND Month="+to_string(timeBegin.month)+") OR (Year="+to_string(timeEnd.year)+" AND Month="+to_string(timeEnd.month)+")";
    vector<vector<string>> ret=DB.selectItem(table,value,limits);
    int rows=ret.size();
    vector<vector<string>> temp;
    if(rows==1 || rows==2){
        table=ret[0][0];
        value="*";
        limits="PersonID="+to_string(PersonID)+" AND Time>"+timeBegin.todatatime()+" AND Time<"+timeEnd.todatatime();
        temp=DB.selectItem(table,value,limits);
        DBTrace trace;
        Traces=trace.readTraces(temp);
        if(rows==2 && ret[0][0]!=ret[1][0]){
            table=ret[1][0];
            value="*";
            limits="PersonID="+to_string(PersonID)+" AND Time>"+timeBegin.todatatime()+" AND Time<"+timeEnd.todatatime();
            temp=DB.selectItem(table,value,limits);
            DBTrace trace; 
            Traces.insert(Traces.end,trace.readTraces(temp).begin,trace.readTraces(temp).end);
        }
    }
}

int DBTraceAPI::DBSearchDeviceTrace(string DeviceID,Time timeBegin,Time timeEnd,vector<DBTrace>&Traces){
    string tracetable1,tracetable2;
    table="Trace";
    value="TableName";
    limits="(Year="+to_string(timeBegin.year)+" AND Month="+to_string(timeBegin.month)+") OR (Year="+to_string(timeEnd.year)+" AND Month="+to_string(timeEnd.month)+")";
    vector<vector<string>> ret=DB.selectItem(table,value,limits);
    int rows=ret.size();
    vector<vector<string>> temp;
    if(rows==1 || rows==2){
        table=ret[0][0];
        value="*";
        limits="DeviceID="+DeviceID+" AND Time>"+timeBegin.todatatime()+" AND Time<"+timeEnd.todatatime();
        temp=DB.selectItem(table,value,limits);
        DBTrace trace;
        Traces=trace.readTraces(temp);
        if(rows==2 && ret[0][0]!=ret[1][0]){
            table=ret[1][0];
            value="*";
            limits="DeviceID="+DeviceID+" AND Time>"+timeBegin.todatatime()+" AND Time<"+timeEnd.todatatime();
            temp=DB.selectItem(table,value,limits);
            DBTrace trace; 
            Traces.insert(Traces.end,trace.readTraces(temp).begin,trace.readTraces(temp).end);
        }
    }
}

int DBTraceAPI::DBSearchDeviceID(vector<string>&DeviceID){
    table="Device";
    value="DeviceID";
    vector<vector<string>> ret=DB.selectItem(table,value);
    for(int i=0;i<ret.size();i++){
        DeviceID.push_back(ret[i][0]);
    }
}

int DBTraceAPI::DBDeleteTrace(DBTrace trace){
    table="Trace";
    trace.time.getdatatime();
    value="TableName";
    limits="Year="+to_string(trace.time.year)+" AND Month="+to_string(trace.time.month);
    vector<vector<string>> ret=DB.selectItem(table,value,limits);
    table=ret[0][0];
    limits="TraceID="+to_string(trace.TraceID);
    DB.deleteItem(table,limits);
}

int DBTraceAPI::DBDeleteDevice(string DeviceID){
    table="Device";
    limits="DeviceID="+DeviceID;
    DB.deleteItem(table,limits);
    table="Device_Person";
    DB.deleteItem(table,limits);
}

int DBTraceAPI::DBDeleteMap(int MapMark){
    table="Map";
    limits="MapMark="+to_string(MapMark);
    DB.deleteItem(table,limits);
}

int DBTraceAPI::DBUpdateTrace(DBTrace traceOld,DBTrace traceNew){
    table="Trace";
    traceOld.time.getdatatime();
    value="TableName";
    limits="Year="+to_string(traceOld.time.year)+" AND Month="+to_string(traceOld.time.month);
    vector<vector<string>> ret=DB.selectItem(table,value,limits);
    table=ret[0][0];
    value="PersonID="+to_string(traceNew.PersonID)+", PersonModule="+to_string(traceNew.PersonModule)+", DeviceID=\""+traceNew.DeviceID+"\", X="+to_string(traceNew.X)+", Y="+to_string(traceNew.Y)+", Floor=\""+traceNew.Floor+"\", MapMark="+to_string(traceNew.MapMark)+", time=\""+traceNew.time.todatatime()+"\"";
    limits="TraceID="+to_string(traceOld.TraceID);
    DB.updateItem(table,value,limits);
}

int DBTraceAPI::DBClearTable(){
    table="Trace";
    value="TableName";
    vector<vector<string>> ret=DB.selectItem(table,value);
    for(int i=0;i<ret.size();i++){
        DB.deleteTB(ret[i][0]);
    }
}

int DBTraceAPI::DBMapCount(int PersonID,int MapMark,Time timeBegin,Time timeEnd,DBMapData *pMapData){
    vector<DBTrace> Traces;
    int flagOld=0;
    int flagNew=0;
    DBMapData MapData;
    MapData.initPersonData(PersonID,MapMark);
    DBSearchPersonTrace(PersonID,timeBegin,timeEnd,Traces);
    for(int i=0;i<Traces.size();i++){
        if(Traces[i].MapMark==MapMark){
            flagNew=1;
        }else{
            flagNew=0;
        }
        if(flagNew==1 && flagOld==0){
            MapData.Enter++;
        }else if (flagNew==0 && flagOld==1)
        {
            MapData.Out++;
        }else if (flagNew==1 && flagOld==1)
        {
            Time temp=CountStayTime(Traces[i].time,Traces[i-1].time);
            MapData.StayTime.second+=temp.second;
            MapData.StayTime.minute+=temp.minute;
            MapData.StayTime.hour+=temp.hour;
            if(MapData.StayTime.second>=60){
                MapData.StayTime.second=MapData.StayTime.second-60;
                MapData.StayTime.minute++;
            }
            if(MapData.StayTime.minute>=60){
                MapData.StayTime.minute=MapData.StayTime.minute-60;
                MapData.StayTime.hour++;
            }
        }
        flagOld=flagNew;
    }
    *pMapData=MapData;
}

Time CountStayTime(Time timeBegin,Time timeEnd){
    int flag=0;
    Time result;
    result.hour=result.hour+timeEnd.hour-timeBegin.hour;
    result.minute=result.minute+timeEnd.minute-timeBegin.minute;
    result.second=result.second+timeEnd.second-timeBegin.second;
    if(result.second<0){
        result.minute--;
        result.second=result.second+60;
    }
    if(result.minute<0){
        result.hour--;
        result.minute=result.minute+60;
    }
    return result;
}

int DBTraceAPI::DBMapPersonCount(int PersonID, Time timeBegin,Time timeEnd,vector<DBMapData>&MapData){
    vector<DBTrace> Traces;
    int flag=0;
    DBSearchPersonTrace(PersonID,timeBegin,timeEnd,Traces);
    table="MapMark";
    value="MapMark";
    vector<vector<string>> ret=DB.selectItem(table,value);
    DBMapData tempMapData;
    for(int i=0;i<ret.size();i++){
        int flagOld=0;
        int flagNew=0;
        int MapMark=atoi(ret[i][0].c_str());
        tempMapData.initPersonData(PersonID,MapMark);
        for(int i=0;i<Traces.size();i++){
            if(Traces[i].MapMark==MapMark){
                flagNew=1;
            }else{
              flagNew=0;
            }
            if(flagNew==1 && flagOld==0){
               tempMapData.Enter++;
            }else if (flagNew==0 && flagOld==1)
            {
               tempMapData.Out++;
            }else if (flagNew==1 && flagOld==1)
            {
                Time temp=CountStayTime(Traces[i].time,Traces[i-1].time);
                tempMapData.StayTime.second+=temp.second;
                tempMapData.StayTime.minute+=temp.minute;
                tempMapData.StayTime.hour+=temp.hour;
                if(tempMapData.StayTime.second>=60){
                   tempMapData.StayTime.second=tempMapData.StayTime.second-60;
                   tempMapData.StayTime.minute++;
                }
                if(tempMapData.StayTime.minute>=60){
                    tempMapData.StayTime.minute=tempMapData.StayTime.minute-60;
                    tempMapData.StayTime.hour++;
                }
            }
            flagOld=flagNew;
        }
        MapData.push_back(tempMapData);
    }
}

int DBTraceAPI::DBMapMarkCount(int MapMark,Time timeBegin,Time timeEnd,vector<DBMapData>&MapData){
    table="Person";
    value="PersonID";
    vector<vector<string>> ret=DB.selectItem(table,value);
    DBMapData * tempMapData;
    for(int i=0;i<ret.size();i++){
        DBMapCount(atoi(ret[i][0].c_str),MapMark,timeBegin,timeEnd,tempMapData);
        MapData.push_back(*tempMapData);
    }
}