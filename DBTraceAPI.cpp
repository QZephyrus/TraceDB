#include "DBTraceAPI.h"

using namespace std;

#define DB_RET_OK 1
#define DB_RET_FALL 2
#define DB_RET_CREATE_DB_ERROR 3
#define DB_RET_CREATE_TB_ERROR 4
#define DB_RET_ADD_ERROR 5
#define DB_RET_NULL 6
#define DB_RET_DEVICE_ERROR 7
#define DB_RET_PERSON_ERROR 8
#define DB_RET_ERORR 9

#define MemoryMonth 3

DBTraceAPI::DBTraceAPI(){   
    database="TraceDB";
}

DBTraceAPI::~DBTraceAPI(){   
}

int DBTraceAPI::DBInitialize(){
    
}

int DBTraceAPI::DBConnect(){
    bool flag_connect=true;
    flag_connect=DB.connect(localhost,user,passwd);
    if(flag_connect){
        return DB_RET_OK;
    }else{
        return DB_RET_FALL;
    }
}

int DBTraceAPI::DBCreateDB(){
    if(DB.createDB(database)==false){
        return DB_RET_CREATE_DB_ERROR;
    }
    DB.useDB(database);
    bool flag_createTB=true;
    flag_createTB=DBCreateRelatTB();
    if(flag_createTB==DB_RET_OK){
        return DB_RET_OK;
    }else{
        return DB_RET_CREATE_TB_ERROR;
    }
}

int DBTraceAPI::DBCreateRelatTB(){
    bool flag_state =true;
    bool flag_success =true;
    DB.autoCommitOff();
    flag_state=DB.createTB("Device_Person","DeviceID varchar(255) NOT NULL,PersonID int NULL,PersonModule tinyint NULL, PRIMARY KEY (DeviceID)");
    if(flag_state==false){
        flag_success=false;
    }
    flag_state=DB.createTB("Device","DeviceID varchar(255) NOT NULL,TableName char(11) NULL,TraceID int UNSIGNED NOT NULL, PRIMARY KEY (DeviceID)");
    if(flag_state==false){
        flag_success=false;
    }
    flag_state=DB.createTB("Person","PersonID int NOT NULL,PersonModule tinyint NULL,TableName char(11) NULL,TraceID int UNSIGNED NOT NULL, PRIMARY KEY (PersonID)");
    if(flag_state==false){
        flag_success=false;
    }
    flag_state=DB.createTB("Map","MapID int NOT NULL AUTO_INCREMENT,MapMark bigint NULL,BCONID bigint NULL,PRIMARY KEY (MapID)");
    if(flag_state==false){
        flag_success=false;
    }
    flag_state=DB.createTB("BCON","BCONID bigint NOT NULL,BCONX float NULL,BCONY float NULL,BCONFloor char(4) NULL,PRIMARY KEY (BCONID)");
    if(flag_state==false){
        flag_success=false;
    }
    flag_state=DB.createTB("MapMark","MapMarkID int NOT NULL AUTO_INCREMENT,MapMark bigint NOT NULL,PRIMARY KEY (MapMarkID)");
    if(flag_state==false){
        flag_success=false;
    }
    flag_state=DB.createTB("Trace","TableID int UNSIGNED NOT NULL AUTO_INCREMENT,TableName char(11) NULL,Year int NULL,Month int NULL,PRIMARY KEY (TableID)");
    if(flag_state==false){
        flag_success=false;
    }
    if(flag_success==true){
        DB.commit();
        //DB.autoCommitOn();
        return DB_RET_OK;
    }else
    {
        DB.rollback();
        //DB.autoCommitOn();
        return DB_RET_FALL;
    }
}

int DBTraceAPI::DBCreateTable(DBTrace trace){
    bool flag_create=true;
    bool flag_add=true;
    bool flag_temp=true;
    if(trace.time.month<10){
        table="Trace"+to_string(trace.time.year)+"0"+to_string(trace.time.month);
    }else{
        table="Trace"+to_string(trace.time.year)+to_string(trace.time.month);
    }
    flag_create=DB.createTB(table,"TraceID int UNSIGNED NOT NULL AUTO_INCREMENT,PersonID bigint NULL,PersonModule tinyint NULL,DeviceID varchar(255) NULL,X float NULL,Y float NULL,Floor char(4) NULL,MapMark bigint NULL,Time datetime NULL,PRIMARY KEY (TraceID)");
    if(flag_create==true){
        DB.autoCommitOff();
        for(int i=0;i<MemoryMonth;i++){
            value=table+", "+to_string(trace.time.year)+", "+to_string(trace.time.month+i);
            flag_temp=DB.insertItem("Trace",value);
            if(flag_temp==false){
                flag_add=false;
            }
        }
        if(flag_add==true){
            DB.commit();
            return DB_RET_OK;
        }else{
            DB.rollback();
            return DB_RET_ADD_ERROR;
        }
    }else{
        return DB_RET_CREATE_TB_ERROR;
    }
}

int DBTraceAPI::DBAddDevice(DBDeviceData deviceData){
    bool flag_insert_device=true;
    bool flag_insert_relat=true;
    DB.autoCommitOff();
    table="Device";
    value="\""+deviceData.DeviceID+"\"";
    flag_insert_device=DB.insertItem(table,value);
    table="Device_Person";
    value="\""+deviceData.DeviceID+"\", "+to_string(deviceData.PersonID)+", "+to_string(deviceData.PersonModule);
    flag_insert_relat=DB.insertItem(table,value);
    if(flag_insert_device&&flag_insert_relat){
        DB.commit();
        return DB_RET_OK;
    }else{
        DB.rollback();
        return DB_RET_FALL;
    }
}

int DBTraceAPI::DBAddSomeDevice(vector<DBDeviceData> deviceData){
    bool flag_insert=true;
    int row=deviceData.size();
    if(row==0){
        return DB_RET_NULL;
    }
    DB.autoCommitOff();
    for(int i=0;i<row;i++){
        table="Device";
        value="\""+deviceData[i].DeviceID+"\"";
        if(DB.insertItem(table,value)==false){
            flag_insert=false;
        }
        table="Device_Person";
        value="\""+deviceData[i].DeviceID+"\", "+to_string(deviceData[i].PersonID)+", "+to_string(deviceData[i].PersonModule);
        if(DB.insertItem(table,value)==false){
            flag_insert=false;
        }
    }
    if(flag_insert){
        DB.commit();
        return DB_RET_OK;
    }else{
        DB.rollback();
        return DB_RET_FALL;
    }
}

int DBTraceAPI::DBUpdateDevice(DBDeviceData deviceData){
    bool flag_updata=true;
    table="Device_Person";
    value="PersonID="+to_string(deviceData.PersonID)+", PersonModule="+to_string(deviceData.PersonModule);
    limits="DeviceID="+deviceData.DeviceID;
    flag_updata=DB.updateItem(table,value,limits);
    if(flag_updata){
        return DB_RET_OK;
    }else{
        return DB_RET_FALL;
    }
}

int DBTraceAPI::DBUpdateSomeDevice(vector<DBDeviceData> deviceData){
    bool flag_updata=true;
    int row=deviceData.size();
    if(row==0){
        return DB_RET_NULL;
    }
    DB.autoCommitOff();
    table="Device_Person";
    for(int i=0;i<row;i++){
        value="PersonID="+to_string(deviceData[i].PersonID)+", PersonModule="+to_string(deviceData[i].PersonModule);
        limits="DeviceID="+deviceData[i].DeviceID;
        if(DB.updateItem(table,value,limits)==false){
            flag_updata==false;
        }
    }
    if(flag_updata){
        DB.commit();
        return DB_RET_OK;
    }else{
        DB.rollback();
        return DB_RET_FALL;
    }
}

int DBTraceAPI::DBAddMap(Map map){
    bool flag_add=true;
    table="Map";
    value=to_string(map.MapMark)+", "+to_string(map.BCONID);
    flag_add=DB.insertItem(table,value);
    if(flag_add){
        return DB_RET_OK;
    }else{
        return DB_RET_FALL;
    }
}

int DBTraceAPI::DBAddSomeMap(vector<Map> map){
    bool flag_add=true;
    int row=map.size();
    if(row==0){
        return DB_RET_NULL;
    }
    DB.autoCommitOff();
    table="Map";
    for(int i=0;i<row;i++){
        value=to_string(map[i].MapMark)+", "+to_string(map[i].BCONID);
        if(DB.insertItem(table,value)==false){
            flag_add=false;
        }
    }
    if(flag_add){
        DB.commit();
        return DB_RET_OK;
    }else{
        DB.rollback();
        return DB_RET_FALL;
    }
}

int DBTraceAPI::DBAddBCON(BCON bcon){
    bool flag_add=true;
    table="BCON";
    value=to_string(bcon.BCONID)+", "+to_string(bcon.BCONX)+", "+to_string(bcon.BCONY)+", \""+bcon.Floor+"\"";
    flag_add=DB.insertItem(table,value);
    if(flag_add){
        return DB_RET_OK;
    }else{
        return DB_RET_FALL;
    }
}

int DBTraceAPI::DBAddSomeBCON(vector<BCON> bcon){
    bool flag_add=true;
    int row=bcon.size();
    if(row==0){
        return DB_RET_NULL;
    }
    DB.autoCommitOff();
    table="BCON";
    for(int i=0;i<row;i++){
        value=to_string(bcon[i].BCONID)+", "+to_string(bcon[i].BCONX)+", "+to_string(bcon[i].BCONY)+", \""+bcon[i].Floor+"\"";
        if(DB.insertItem(table,value)==false){
            flag_add=false;
        }
    }
    if(flag_add){
        DB.commit();
        return DB_RET_OK;
    }else{
        DB.rollback();
        return DB_RET_FALL;
    }
}

int DBTraceAPI::DBAddTrace(DBTrace trace){
    int result;
    table="Trace";
    value="TableName";
    limits="Year="+to_string(trace.time.year)+" AND Month="+to_string(trace.time.month);
    vector<vector<string>> ret=DB.selectItem(table,value,limits);
    if(ret.size()==0){
        result=DBCreateTable(trace);
        if(result==DB_RET_OK){
            DBAddTrace(trace);
        }else{
            return result;
        }
    }else if(ret.size==1){
        bool flag_insert=true;
        table=ret[0][0];
        value=to_string(trace.PersonID)+", "+to_string(trace.PersonModule)+", \""+trace.DeviceID+"\", "+to_string(trace.X)+", "+to_string(trace.Y)+", \""+trace.Floor+"\", "+to_string(trace.MapMark)+", \""+trace.time.todatatime()+"\"";
        flag_insert=DB.insertItem(table,value);
        if(flag_insert){
            return DB_RET_OK;
        }else{
            return DB_RET_FALL;
        }
    }
}

int DBTraceAPI::DBAddSomeTrace(vector<DBTrace> trace){
    int row=trace.size();
    if(row==0){
        return DB_RET_NULL;
    }
    bool flag_add=true;
    DB.autoCommitOff();
    for(int i=0;i<row;i++){
        if(DBAddTrace(trace[i])!=DB_RET_OK){
            flag_add=false;
        }
    }
    if(flag_add){
        DB.commit();
        return DB_RET_OK;
    }else{
        DB.rollback();
        return DB_RET_FALL;
    }
}

int DBTraceAPI::DBSearchDevice(string DeviceID,DBTrace *pTrace){
    table="Device";
    value="TableName,TraceID";
    limits="DeviceID="+DeviceID;
    vector<vector<string>> ret=DB.selectItem(table,value,limits);
    if(ret.size()==0){
        return DB_RET_DEVICE_ERROR;
    }else if(ret.size()==1){
        table=ret[0][0];
        value="*";
        limits="TraceID="+ret[0][1];
        vector<vector<string>> temp=DB.selectItem(table,value,limits);
        if(temp.size()==0){
            return DB_RET_NULL;
        }
        DBTrace trace;
        trace.readTrace(temp);
        *pTrace=trace;
        return DB_RET_OK;
    }
}

int DBTraceAPI::DBSearchSomeDevice(vector<string> DeviceID,vector<DBTrace>&Trace){
    for(int i=0;i<DeviceID.size();i++){
        DBTrace *tempTrace=nullptr;
        DBSearchDevice(DeviceID[i],tempTrace);
        if(tempTrace!=nullptr){
            Trace.push_back(*tempTrace);
        }
    }
    if(Trace.size()==0){
        return DB_RET_NULL;
    }else{
        return DB_RET_OK;
    }
}

int DBTraceAPI::DBSearchAllDevice(vector<DBTrace>&Traces){
    vector<vector<string>> tablename;
    table="Device";
    value="TableName,TraceID";
    limits="TraceID IS NOT NULL";
    tablename=DB.selectItem(table,value,limits);
    int rows=tablename.size();
    if(rows==0){
        return DB_RET_DEVICE_ERROR;
    }
    for(int i=0;i<rows;i++){
        table=tablename[i][0];
        value="*";
        limits="TraceID="+tablename[i][1];
        vector<vector<string>> temp=DB.selectItem(table,value,limits);
        DBTrace trace;
        trace.readTrace(temp);
        Traces.push_back(trace);
    }
    if(Traces.size()==0){
        return DB_RET_NULL;
    }else{
        return DB_RET_OK;
    }
}

int DBTraceAPI::DBSearchPerson(int PersonID,DBTrace *pTrace){
    table="Person";
    value="TableName,TraceID";
    limits="PersonID="+to_string(PersonID);

    vector<vector<string>> ret=DB.selectItem(table,value,limits);
    if(ret.size()==0){
        return DB_RET_PERSON_ERROR;
    }else if(ret.size()==1){
        table=ret[0][0];
        value="*";
        limits="TraceID="+ret[0][1];
        vector<vector<string>> temp=DB.selectItem(table,value,limits);
        if(temp.size()==0){
            return DB_RET_NULL;
        }
        DBTrace trace;
        trace.readTrace(temp);
        *pTrace=trace;
        return DB_RET_OK;
    }
}

int DBTraceAPI::DBSearchSomePerson(vector<int> PersonID,vector<DBTrace>&Trace){
    for(int i=0;i<PersonID.size();i++){
        DBTrace *tempTrace;
        DBSearchPerson(PersonID[i],tempTrace);
        if(tempTrace!=nullptr){
            Trace.push_back(*tempTrace);
        }
    }
    if(Trace.size()==0){
        return DB_RET_NULL;
    }else{
        return DB_RET_OK;
    }
}

int DBTraceAPI::DBSearchAllPerson (vector<DBTrace>&Traces){
    vector<vector<string>> tablename;
    table="Person";
    value="TableName,TraceID";
    limits="TraceID IS NOT NULL";
    tablename=DB.selectItem(table,value,limits);
    int rows=tablename.size();
    if(rows==0){
        return DB_RET_PERSON_ERROR;
    }
    for(int i=0;i<rows;i++){
        table=tablename[i][0];
        value="*";
        limits="TraceID="+tablename[i][1];
        vector<vector<string>> temp=DB.selectItem(table,value,limits);
        DBTrace trace;
        trace.readTrace(temp);
        Traces.push_back(trace);
    }
    if(Traces.size()==0){
        return DB_RET_NULL;
    }else{
        return DB_RET_OK;
    }
}

int DBTraceAPI::DBSearchPersonTrace(int PersonID,Time timeBegin,Time timeEnd,vector<DBTrace>&Traces){
    string tracetable1,tracetable2;
    table="Trace";
    value="TableName";
    limits="(Year="+to_string(timeBegin.year)+" AND Month="+to_string(timeBegin.month)+") OR (Year="+to_string(timeEnd.year)+" AND Month="+to_string(timeEnd.month)+")";
    vector<vector<string>> ret=DB.selectItem(table,value,limits);
    int rows=ret.size();
    if(rows==0){
        return DB_RET_NULL;
    }
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
        if(Traces.size()==0){
            return DB_RET_NULL;
        }else{
            return DB_RET_OK;
        }
    }else{
        return DB_RET_ERORR;
    }
}

int DBTraceAPI::DBSearchDeviceTrace(string DeviceID,Time timeBegin,Time timeEnd,vector<DBTrace>&Traces){
    string tracetable1,tracetable2;
    table="Trace";
    value="TableName";
    limits="(Year="+to_string(timeBegin.year)+" AND Month="+to_string(timeBegin.month)+") OR (Year="+to_string(timeEnd.year)+" AND Month="+to_string(timeEnd.month)+")";
    vector<vector<string>> ret=DB.selectItem(table,value,limits);
    int rows=ret.size();
    if(rows==0){
        return DB_RET_NULL;
    }
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
        if(Traces.size()==0){
            return DB_RET_NULL;
        }else{
            return DB_RET_OK;
        }
    }else{
        return DB_RET_ERORR;
    }
}

int DBTraceAPI::DBSearchDeviceID(vector<string>&DeviceID){
    table="Device";
    value="DeviceID";
    vector<vector<string>> ret=DB.selectItem(table,value);
    if(ret.size()==0){
        return DB_RET_NULL;
    }
    for(int i=0;i<ret.size();i++){
        DeviceID.push_back(ret[i][0]);
    }
    return DB_RET_OK;
}

int DBTraceAPI::DBDeleteTrace(DBTrace trace){
    table="Trace";
    trace.time.getdatatime();
    value="TableName";
    limits="Year="+to_string(trace.time.year)+" AND Month="+to_string(trace.time.month);
    vector<vector<string>> ret=DB.selectItem(table,value,limits);
    if(ret.size()==0){
        return DB_RET_NULL;
    }
    table=ret[0][0];
    limits="TraceID="+to_string(trace.TraceID);
    if(DB.deleteItem(table,value)){
        return DB_RET_OK;
    }else{
        return DB_RET_FALL;
    }
}

int DBTraceAPI::DBDeleteDevice(string DeviceID){
    table="Device";
    limits="DeviceID="+DeviceID;
    DB.autoCommitOff();
    bool flag_delete=true;
    if(DB.deleteItem(table,limits)==false){
        flag_delete=false;
    }
    table="Device_Person";
    if(DB.deleteItem(table,limits)==false){
        flag_delete=false;
    }
    if(flag_delete==true){
        DB.commit();
        return DB_RET_OK;
    }else{
        DB.rollback();
        return DB_RET_FALL;
    }
}

int DBTraceAPI::DBDeleteMap(int MapMark){
    table="Map";
    limits="MapMark="+to_string(MapMark);
    if(DB.deleteItem(table,limits)){
        return DB_RET_OK;
    }else{
        return DB_RET_FALL;
    }
}

int DBTraceAPI::DBUpdateTrace(DBTrace traceOld,DBTrace traceNew){
    table="Trace";
    traceOld.time.getdatatime();
    value="TableName";
    limits="Year="+to_string(traceOld.time.year)+" AND Month="+to_string(traceOld.time.month);
    vector<vector<string>> ret=DB.selectItem(table,value,limits);
    if(ret.size()==0){
        return DB_RET_NULL;
    }
    table=ret[0][0];
    value="PersonID="+to_string(traceNew.PersonID)+", PersonModule="+to_string(traceNew.PersonModule)+", DeviceID=\""+traceNew.DeviceID+"\", X="+to_string(traceNew.X)+", Y="+to_string(traceNew.Y)+", Floor=\""+traceNew.Floor+"\", MapMark="+to_string(traceNew.MapMark)+", time=\""+traceNew.time.todatatime()+"\"";
    limits="TraceID="+to_string(traceOld.TraceID);
    if(DB.updateItem(table,value,limits)){
        return DB_RET_OK;
    }else{
        return DB_RET_FALL;
    }
}

int DBTraceAPI::DBClearTable(){
    table="Trace";
    value="TableName";
    vector<vector<string>> ret=DB.selectItem(table,value);
    if(ret.size()==0){
        return DB_RET_NULL;
    }
    DB.autoCommitOff();
    bool flag_delete=true;
    for(int i=0;i<ret.size();i++){
        if(DB.deleteTB(ret[i][0])==false){
            flag_delete=false;
        }
    }
    if(flag_delete){
        DB.commit();
        return DB_RET_OK;
    }else{
        DB.rollback();
        return DB_RET_FALL;
    }
}

int DBTraceAPI::DBMapCount(int PersonID,int MapMark,Time timeBegin,Time timeEnd,DBMapData *pMapData){
    vector<DBTrace> Traces;
    int flagOld=0;
    int flagNew=0;
    DBMapData MapData;
    MapData.initPersonData(PersonID,MapMark);
    int res=DBSearchPersonTrace(PersonID,timeBegin,timeEnd,Traces);
    if(res==DB_RET_OK){
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
                CountStayTime(Traces[i].time,Traces[i-1].time,MapData.StayTime);
            }
            flagOld=flagNew;
        }
        *pMapData=MapData;
        return DB_RET_OK;
    }else{
        return DB_RET_FALL;
    }
}

void CountStayTime(Time timeBegin,Time timeEnd,Time&result){
    int flag=0;
    result.Day=result.Day+timeEnd.Day-timeBegin.Day;
    result.hour=result.hour+timeEnd.hour-timeBegin.hour;
    result.minute=result.minute+timeEnd.minute-timeBegin.minute;
    result.second=result.second+timeEnd.second-timeBegin.second;
    if(result.second<0){
        result.minute--;
        result.second=result.second+60;
    }else if (result.second>=60){
        result.second=result.second-60;
        result.minute++;
    }
    if(result.minute<0){
        result.hour--;
        result.minute=result.minute+60;
    }else if (result.minute>=60){
        result.minute=result.minute-60;
        result.hour++;
    }
    if(result.hour<0){
        result.Day--;
        result.hour=result.hour+24;
    }else if (result.hour>=24){
        result.hour=result.hour-24;
        result.Day++;
    }
}

int DBTraceAPI::DBMapPersonCount(int PersonID, Time timeBegin,Time timeEnd,vector<DBMapData>&MapData){
    vector<DBTrace> Traces;
    int flag=0;
    int res=DBSearchPersonTrace(PersonID,timeBegin,timeEnd,Traces);
    if(res==DB_RET_OK){
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
                    CountStayTime(Traces[i].time,Traces[i-1].time,tempMapData.StayTime);
                }
                flagOld=flagNew;
            }
            MapData.push_back(tempMapData);
        }
        return DB_RET_OK;
    }else{
        return DB_RET_FALL;
    }
    
}

int DBTraceAPI::DBMapMarkCount(int MapMark,Time timeBegin,Time timeEnd,vector<DBMapData>&MapData){
    table="Person";
    value="PersonID";
    vector<vector<string>> ret=DB.selectItem(table,value);
    if(ret.size()==0){
        return DB_RET_PERSON_ERROR;
    }
    DBMapData * tempMapData;
    int resultcode[ret.size()];
    for(int i=0;i<ret.size();i++){
        resultcode[i]=DBMapCount(atoi(ret[i][0].c_str),MapMark,timeBegin,timeEnd,tempMapData);
        MapData.push_back(*tempMapData);
    }
    return DB_RET_OK;
}