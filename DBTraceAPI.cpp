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

//定义每张具体轨迹表存储的月份
#define MemoryMonth 3



//构造函数，保存默认的数据库连接信息
DBTraceAPI::DBTraceAPI(){  
    localhost="localhost";
    user="root";
    passwd="zenos"; 
    database="TraceDB";
}
//构造函数，构造时不使用默认参数
DBTraceAPI::DBTraceAPI(string host,string username,string password,string databasename){
    localhost=host;
    user=username;
    passwd=password;
    database=databasename;
}

DBTraceAPI::~DBTraceAPI(){   
}
//初始化，初始化数据库信息
int DBTraceAPI::DBInitialize(string host,string username,string password,string databasename){
    localhost=host;
    user=username;
    passwd=password;
    database=databasename;
    return DB_RET_OK;
}
//建立数据库连接
int DBTraceAPI::DBConnect(){
    bool flag_connect=true;
    flag_connect=DB.connect(localhost,user,passwd);
    //判断数据库是否连接成功
    if(flag_connect){
        return DB_RET_OK;
    }else{
        return DB_RET_FALL;
    }
}
//创建数据库以及基础关联表格
int DBTraceAPI::DBCreateDB(){
    //判断数据库是否创建成功
    if(DB.createDB(database)==false){
        return DB_RET_CREATE_DB_ERROR;
    }
    DB.useDB(database);
    //判断数据库关联基础表格是否创建成功
    int flag_createTB;
    flag_createTB=DBCreateRelatTB();
    if(flag_createTB==DB_RET_OK){
        return DB_RET_OK;
    }else{
        return DB_RET_CREATE_TB_ERROR;
    }
}
//创建数据库基础关联表格
int DBTraceAPI::DBCreateRelatTB(){
    //通过两个flag判断在创建表的过程中是否出现错误，若出现错误flag_success为false，并且事件回滚到创建表之前
    bool flag_state =true;
    bool flag_success =true;
    DB.autoCommitOff();
    //创建设备人员关系表
    flag_state=DB.createTB("Device_Person","DeviceID varchar(255) NOT NULL,PersonID int NULL,PersonModule tinyint NULL, PRIMARY KEY (DeviceID)");
    if(flag_state==false){
        flag_success=false;
    }
    //创建设备表
    flag_state=DB.createTB("Device","DeviceID varchar(255) NOT NULL,TableName char(11) NULL,TraceID int UNSIGNED NULL, PRIMARY KEY (DeviceID)");
    if(flag_state==false){
        flag_success=false;
    }
    //创建人员表
    flag_state=DB.createTB("Person","PersonID int NOT NULL,PersonModule tinyint NULL,TableName char(11) NULL,TraceID int UNSIGNED NULL, PRIMARY KEY (PersonID)");
    if(flag_state==false){
        flag_success=false;
    }
    //创建围栏BCON关系表
    flag_state=DB.createTB("Map","MapID int NOT NULL AUTO_INCREMENT,MapMark bigint NULL,BCONID bigint NULL,PRIMARY KEY (MapID)");
    if(flag_state==false){
        flag_success=false;
    }
    //创建BCON表
    flag_state=DB.createTB("BCON","BCONID bigint NOT NULL,BCONX float NULL,BCONY float NULL,BCONFloor char(4) NULL,PRIMARY KEY (BCONID)");
    if(flag_state==false){
        flag_success=false;
    }
    //创建围栏表
    flag_state=DB.createTB("MapMark","MapMarkID int NOT NULL AUTO_INCREMENT,MapMark bigint NOT NULL,PRIMARY KEY (MapMarkID)");
    if(flag_state==false){
        flag_success=false;
    }
    //创建轨迹表（存储所有具体轨迹表名等信息）
    flag_state=DB.createTB("Trace","TableID int UNSIGNED NOT NULL AUTO_INCREMENT,TableName char(11) NULL,YearMonth int NULL,PRIMARY KEY (TableID)");
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
//创建具体轨迹表
int DBTraceAPI::DBCreateTable(DBTrace trace){
    
    DB.useDB(database);
    bool flag_create=true;
    bool flag_add=true;
    bool flag_temp=true;
    DB.autoCommitOff();
    //根据轨迹合成表名如Trace202002
    table="Trace"+trace.time.substr(0,4)+trace.time.substr(5,2);
    flag_create=DB.createTB(table,"TraceID int UNSIGNED NOT NULL AUTO_INCREMENT,PersonID bigint NULL,PersonModule tinyint NULL,DeviceID varchar(255) NULL,X float NULL,Y float NULL,Floor char(4) NULL,MapMark bigint NULL,Time datetime NULL,PRIMARY KEY (TraceID)");
    if(flag_create==true){
        int year=atoi(trace.time.substr(0,4).c_str());
        int month=atoi(trace.time.substr(5,2).c_str());
        string yearmonth;
        //将新建的表存入相关月份（一张表对应几个月）
        for(int i=0;i<MemoryMonth;i++){
            if((month+i)>12){
                yearmonth=to_string((year+1)*100+(month+i-12));
            }else{
                yearmonth=to_string((year)*100+(month+i));
            }
            value="null,'"+table+"', "+yearmonth;
            flag_temp=DB.insertItem("Trace",value);
            if(flag_temp==false){
                flag_add=false;
                break;
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
//添加设备以及其初始设备人员关系
int DBTraceAPI::DBAddDevice(DBDeviceData deviceData){
    DB.useDB(database);
    bool flag_insert_device=true;
    bool flag_insert_relat=true;
    DB.autoCommitOff();
    //将新设备注册到设备表中
    table="Device";
    value="'"+deviceData.DeviceID+"',null,null";
    flag_insert_device=DB.insertItem(table,value);
    //将新设备和对应人员关系更新到关系表中
    table="Device_Person";
    value="'"+deviceData.DeviceID+"', "+to_string(deviceData.PersonID)+", "+to_string(deviceData.PersonModule);
    flag_insert_relat=DB.insertItem(table,value);
    if(flag_insert_device&&flag_insert_relat){
        DB.commit();
        return DB_RET_OK;
    }else{
        DB.rollback();
        return DB_RET_FALL;
    }
}
//设备批量添加设备
int DBTraceAPI::DBAddSomeDevice(vector<DBDeviceData> deviceData){
    DB.useDB(database);
    bool flag_insert=true;
    //获得批量输入设备行数
    int row=deviceData.size();
    if(row==0){
        return DB_RET_NULL;
    }
    DB.autoCommitOff();
    for(int i=0;i<row;i++){
        //将设备添加到设备表中
        table="Device";
        value="'"+deviceData[i].DeviceID+"',null,null";
        if(DB.insertItem(table,value)==false){
            flag_insert=false;
            break;
        }
        //将设备与人员关系添加到关系表中
        table="Device_Person";
        value="'"+deviceData[i].DeviceID+"', "+to_string(deviceData[i].PersonID)+", "+to_string(deviceData[i].PersonModule);
        if(DB.insertItem(table,value)==false){
            flag_insert=false;
            break;
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
//添加人员
int DBTraceAPI::DBAddPerson(DBDeviceData deviceData){
    DB.useDB(database);
    bool flag_insert_person=true;
    //将新设备注册到设备表中
    table="Person";
    value=to_string(deviceData.PersonID)+", "+to_string(deviceData.PersonModule)+",null,null";
    flag_insert_person=DB.insertItem(table,value);
    if(flag_insert_person){
        return DB_RET_OK;
    }else{
        return DB_RET_FALL;
    }
}
//设备批量添加人员
int DBTraceAPI::DBAddSomePerson(vector<DBDeviceData> deviceData){
    DB.useDB(database);
    bool flag_insert=true;
    //获得批量输入设备行数
    int row=deviceData.size();
    if(row==0){
        return DB_RET_NULL;
    }
    DB.autoCommitOff();
    for(int i=0;i<row;i++){
        //将设备添加到设备表中
        table="Person";
        value=to_string(deviceData[i].PersonID)+", "+to_string(deviceData[i].PersonModule)+",null,null";
        if(DB.insertItem(table,value)==false){
            flag_insert=false;
            break;
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
//更新设备和人员关系
int DBTraceAPI::DBUpdateDeviceRelat(DBDeviceData deviceData){
    DB.useDB(database);
    bool flag_updata=true;
    table="Device_Person";
    value="PersonID="+to_string(deviceData.PersonID)+", PersonModule="+to_string(deviceData.PersonModule);
    limits="DeviceID='"+deviceData.DeviceID+"'";
    flag_updata=DB.updateItem(table,value,limits);
    if(flag_updata){
        return DB_RET_OK;
    }else{
        return DB_RET_FALL;
    }
}
//批量更新设备和人员关系
int DBTraceAPI::DBUpdateSomeDeviceRelat(vector<DBDeviceData> deviceData){
    DB.useDB(database);
    bool flag_updata=true;
    int row=deviceData.size();
    if(row==0){
        return DB_RET_NULL;
    }
    DB.autoCommitOff();
    table="Device_Person";
    for(int i=0;i<row;i++){
        value="PersonID="+to_string(deviceData[i].PersonID)+", PersonModule="+to_string(deviceData[i].PersonModule);
        limits="DeviceID='"+deviceData[i].DeviceID+"'";
        if(DB.updateItem(table,value,limits)==false){
            flag_updata=false;
            break;
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
//添加单条围栏与BCON关联信息
int DBTraceAPI::DBAddMap(Map map){
    DB.useDB(database);
    bool flag_add=true;
    table="Map";
    value="null,"+to_string(map.MapMark)+", "+to_string(map.BCONID);
    flag_add=DB.insertItem(table,value);
    if(flag_add){
        return DB_RET_OK;
    }else{
        return DB_RET_FALL;
    }
}
//添加多条围栏与BCON关联信息
int DBTraceAPI::DBAddSomeMap(vector<Map> map){
    DB.useDB(database);
    bool flag_add=true;
    //读取需要添加的围栏信息
    int row=map.size();
    if(row==0){
        return DB_RET_NULL;
    }
    DB.autoCommitOff();
    table="Map";
    for(int i=0;i<row;i++){
        value="null,"+to_string(map[i].MapMark)+", "+to_string(map[i].BCONID);
        if(DB.insertItem(table,value)==false){
            flag_add=false;
            break;
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
//添加一条BCON信息
int DBTraceAPI::DBAddBCON(BCON bcon){
    DB.useDB(database);
    bool flag_add=true;
    table="BCON";
    value=to_string(bcon.BCONID)+", "+to_string(bcon.BCONX)+", "+to_string(bcon.BCONY)+", '"+bcon.Floor+"'";
    flag_add=DB.insertItem(table,value);
    if(flag_add){
        return DB_RET_OK;
    }else{
        return DB_RET_FALL;
    }
}
//添加多条BCON信息
int DBTraceAPI::DBAddSomeBCON(vector<BCON> bcon){
    DB.useDB(database);
    bool flag_add=true;
    //读取需要添加的BCON信息
    int row=bcon.size();
    if(row==0){
        return DB_RET_NULL;
    }
    DB.autoCommitOff();
    table="BCON";
    for(int i=0;i<row;i++){
        value=to_string(bcon[i].BCONID)+", "+to_string(bcon[i].BCONX)+", "+to_string(bcon[i].BCONY)+", '"+bcon[i].Floor+"'";
        if(DB.insertItem(table,value)==false){
            flag_add=false;
            break;
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
//添加单条围栏信息
int DBTraceAPI::DBAddMapMark(int mapMark){
    DB.useDB(database);
    bool flag_add=true;
    table="MapMark";
    value="null,"+to_string(mapMark);
    flag_add=DB.insertItem(table,value);
    if(flag_add){
        return DB_RET_OK;
    }else{
        return DB_RET_FALL;
    }
}
//添加多条围栏信息
int DBTraceAPI::DBAddSomeMapMark(vector<int> mapMark){
    DB.useDB(database);
    bool flag_add=true;
    //读取需要添加的BCON信息
    int row=mapMark.size();
    if(row==0){
        return DB_RET_NULL;
    }
    DB.autoCommitOff();
    table="MapMark";
    for(int i=0;i<row;i++){
        value="null,"+to_string(mapMark[i]);
        if(DB.insertItem(table,value)==false){
            flag_add=false;
            break;
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
//更新设备最新轨迹的位置到设备表
int DBTraceAPI::DBUpdateDevice(string DeviceID,string TableName,int TraceID){
    DB.useDB(database);
    bool flag_updata=true;
    table="Device";
    value="TableName='"+TableName+"', TraceID="+to_string(TraceID);
    limits="DeviceID='"+DeviceID+"'";
    flag_updata=DB.updateItem(table,value,limits);
    if(flag_updata){
        return DB_RET_OK;
    }else{
        return DB_RET_FALL;
    }
}
//更新设备最新轨迹的位置到人员表
int DBTraceAPI::DBUpdatePerson(int PersonID,string TableName,int TraceID){
    DB.useDB(database);
    bool flag_updata=true;
    table="Person";
    value="TableName='"+TableName+"', TraceID="+to_string(TraceID);
    limits="PersonID="+to_string(PersonID);
    flag_updata=DB.updateItem(table,value,limits);
    if(flag_updata){
        return DB_RET_OK;
    }else{
        return DB_RET_FALL;
    }
}
//添加单条轨迹信息
int DBTraceAPI::DBAddTrace(DBTrace trace){
    DB.useDB(database);
    int result;
    table="Trace";
    value="TableName";
    //保存轨迹的年月信息以搜索相关表
    limits="YearMonth="+trace.time.substr(0,4)+trace.time.substr(5,2);
    string_table ret=DB.selectItem(table,value,limits);
    //判断是否有存储轨迹的相关表，如果没有这创建新表并且重新调用添加函数，有则直接进行存储
    if(ret.size()==0){
        result=DBCreateTable(trace);
        if(result==DB_RET_OK){
            table="Trace"+trace.time.substr(0,4)+trace.time.substr(5,2);
        }else{
            return result;
        }
    }else if(ret.size()==1){
        table=ret[0][0];    
    }else{
        return DB_RET_ERORR;
    }
    bool flag_insert=true;
    int TraceID;
    DB.autoCommitOff();
    string tableName=table;
    value="null,"+to_string(trace.PersonID)+", "+to_string(trace.PersonModule)+", '"+trace.DeviceID+"', "+to_string(trace.X)+", "+to_string(trace.Y)+", '"+trace.Floor+"', "+to_string(trace.MapMark)+", '"+trace.time+"'";
    if(DB.insertItem(table,value)==false){
        flag_insert=false;
    }else{
        value="TraceID";
        limits="PersonID="+to_string(trace.PersonID)+" AND PersonModule="+to_string(trace.PersonModule)+" AND DeviceID='"+trace.DeviceID+"' AND X="+to_string(trace.X)+" AND Y="+to_string(trace.Y)+" AND Floor='"+trace.Floor+"' AND MapMark="+to_string(trace.MapMark)+" AND Time='"+trace.time+"'";
        string_table ret=DB.selectItem(table,value,limits);
        TraceID=atoi(ret[0][0].c_str());
        if(DBUpdateDevice(trace.DeviceID,tableName,TraceID)!=DB_RET_OK){
            flag_insert=false;
        }
        if(DBUpdatePerson(trace.PersonID,tableName,TraceID)!=DB_RET_OK){
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
//添加多条轨迹信息
int DBTraceAPI::DBAddSomeTrace(vector<DBTrace> trace){
    DB.useDB(database);
    //查看所需存储的轨迹条数
    int row=trace.size();
    if(row==0){
        return DB_RET_NULL;
    }
    bool flag_add=true;
    DB.autoCommitOff();
    for(int i=0;i<row;i++){
        if(DBAddTrace(trace[i])!=DB_RET_OK){
            flag_add=false;
            break;
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
//搜索某一设备最近一条的轨迹信息
int DBTraceAPI::DBSearchDevice(string DeviceID,DBTrace&pTrace){
    DB.useDB(database);
    table="Device";
    value="TableName,TraceID";
    limits="DeviceID='"+DeviceID+"' AND TraceID IS NOT NULL";
    //搜索对应设备在设备表中记录的最近一条记录
    string_table ret=DB.selectItem(table,value,limits);
    if(ret.size()==0){
        return DB_RET_DEVICE_ERROR;
    }else if(ret.size()==1){
        //根据最近一条的轨迹信息来搜索轨迹具体信息
        table=ret[0][0];
        value="*";
        limits="TraceID="+ret[0][1];
        string_table temp=DB.selectItem(table,value,limits);
        if(temp.size()==0){
            return DB_RET_NULL;
        }
        pTrace.readTrace(temp);
    }
    return DB_RET_OK;
}
//搜索某几个设备最近一条的轨迹信息
int DBTraceAPI::DBSearchSomeDevice(vector<string> DeviceID,vector<DBTrace>&Trace){
    DB.useDB(database);
    for(unsigned int i=0;i<DeviceID.size();i++){
        DBTrace tempTrace;
        if(DBSearchDevice(DeviceID[i],tempTrace)==DB_RET_OK){
            Trace.push_back(tempTrace);
        }
    }
    if(Trace.size()==0){
        return DB_RET_NULL;
    }else{
        return DB_RET_OK;
    }
}
//搜索所有设备最近一条的轨迹信息
int DBTraceAPI::DBSearchAllDevice(vector<DBTrace>&Traces){
    DB.useDB(database);
    string_table tablename;
    //读取所有设备
    table="Device";
    value="TableName,TraceID";
    limits="TraceID IS NOT NULL";
    tablename=DB.selectItem(table,value,limits);
    int rows=tablename.size();
    if(rows==0){
        return DB_RET_DEVICE_ERROR;
    }
    for(unsigned int i=0;i<rows;i++){
        table=tablename[i][0];
        value="*";
        limits="TraceID="+tablename[i][1];
        string_table temp=DB.selectItem(table,value,limits);
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
//搜索某一人最近一条的轨迹信息
int DBTraceAPI::DBSearchPerson(int PersonID,DBTrace&pTrace){
    DB.useDB(database);
    table="Person";
    value="TableName,TraceID";
    limits="PersonID="+to_string(PersonID)+" AND TraceID IS NOT NULL";
    //搜索对应人员在人员表中记录的最近一条记录
    string_table ret=DB.selectItem(table,value,limits);
    if(ret.size()==0){
        return DB_RET_PERSON_ERROR;
    }else if(ret.size()==1){
        table=ret[0][0];
        value="*";
        limits="TraceID="+ret[0][1];
        string_table temp=DB.selectItem(table,value,limits);
        if(temp.size()==0){
            return DB_RET_NULL;
        }
        pTrace.readTrace(temp);
    }
    return DB_RET_OK;
}
//搜索某几个人员最近一条的轨迹信息
int DBTraceAPI::DBSearchSomePerson(vector<int> PersonID,vector<DBTrace>&Trace){
    DB.useDB(database);
    for(unsigned int i=0;i<PersonID.size();i++){
        DBTrace tempTrace;
        if(DBSearchPerson(PersonID[i],tempTrace)==DB_RET_OK){
            Trace.push_back(tempTrace);
        }
    }
    if(Trace.size()==0){
        return DB_RET_NULL;
    }else{
        return DB_RET_OK;
    }
}
//搜索所有人员最近一条的轨迹信息
int DBTraceAPI::DBSearchAllPerson (vector<DBTrace>&Traces){
    DB.useDB(database);
    string_table tablename;
    table="Person";
    value="TableName,TraceID";
    limits="TraceID IS NOT NULL";
    //获取所有人员最后一条轨迹的位置
    tablename=DB.selectItem(table,value,limits);
    int rows=tablename.size();
    if(rows==0){
        return DB_RET_PERSON_ERROR;
    }
    for(unsigned int i=0;i<rows;i++){
        table=tablename[i][0];
        value="*";
        limits="TraceID="+tablename[i][1];
        string_table temp=DB.selectItem(table,value,limits);
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
//搜索时间区间内的人员轨迹信息
int DBTraceAPI::DBSearchPersonTrace(int PersonID,ptime timeBegin,ptime timeEnd,vector<DBTrace>&Traces){
    DB.useDB(database);
    string tracetable1,tracetable2;
    table="Trace";
    value="TableName";
    string timeB=to_iso_extended_string(timeBegin);
    timeB=timeB.replace(timeB.find("T"),1," ");
    string timeE=to_iso_extended_string(timeEnd);
    timeE=timeE.replace(timeE.find("T"),1," ");
    limits="YearMonth>="+timeB.substr(0,4)+timeB.substr(5,2)+" AND YearMonth<="+timeE.substr(0,4)+timeE.substr(5,2);
    //检索在时间区间内的所有轨迹表
    string_table ret=DB.selectItem(table,value,limits);
    //轨迹表为0则返回没有数据，不为0则开始搜索
    int rows=ret.size();
    if(rows==0){
        return DB_RET_NULL;
    }
    string_table temp;
    if(rows==1){
        table=ret[0][0];
        value="*";
        limits="PersonID="+to_string(PersonID)+" AND Time>='"+timeB+"' AND Time<='"+timeE+"'";
        temp=DB.selectItem(table,value,limits);
        DBTrace trace;
        Traces=trace.readTraces(temp);
    }else if(rows>1){
        for(unsigned int i=0;i<rows;i++){
            table=ret[i][0];
            value="*";
            limits="PersonID="+to_string(PersonID)+" AND Time>='"+timeB+"' AND Time<='"+timeE+"'";
            temp=DB.selectItem(table,value,limits);
            DBTrace trace;
            vector<DBTrace> res;
            res=trace.readTraces(temp);
            Traces.insert(Traces.end(),res.begin(),res.end());
        }
    }
    if(Traces.size()==0){
        return DB_RET_NULL;
    }else{
        return DB_RET_OK;
    }
}
//搜索时间区间内的设备轨迹信息
int DBTraceAPI::DBSearchDeviceTrace(string DeviceID,ptime timeBegin,ptime timeEnd,vector<DBTrace>&Traces){
    DB.useDB(database);
    string tracetable1,tracetable2;
    table="Trace";
    value="TableName";
    string timeB=to_iso_extended_string(timeBegin);
    timeB=timeB.replace(timeB.find("T"),1," ");
    string timeE=to_iso_extended_string(timeEnd);
    timeE=timeE.replace(timeE.find("T"),1," ");
    limits="YearMonth>="+timeB.substr(0,4)+timeB.substr(5,2)+" AND YearMonth<="+timeE.substr(0,4)+timeE.substr(5,2);
    //检索在时间区间内的所有轨迹表
    string_table ret=DB.selectItem(table,value,limits);
    //轨迹表为0则返回没有数据，不为0则开始搜索
    int rows=ret.size();
    if(rows==0){
        return DB_RET_NULL;
    }
    string_table temp;
    if(rows==1){
        table=ret[0][0];
        value="*";
        limits="DeviceID='"+DeviceID+"' AND Time>='"+timeB+"' AND Time<='"+timeE+"'";
        temp=DB.selectItem(table,value,limits);
        DBTrace trace;
        Traces=trace.readTraces(temp);  
    }else{
        for(unsigned int i=0;i<rows;i++){
            table=ret[i][0];
            value="*";
            limits="DeviceID='"+DeviceID+"' AND Time>='"+timeB+"' AND Time<='"+timeE+"'";
            temp=DB.selectItem(table,value,limits);
            DBTrace trace; 
            vector<DBTrace> res;
            res=trace.readTraces(temp);
            Traces.insert(Traces.end(),res.begin(),res.end());
        }
    }
    if(Traces.size()==0){
        return DB_RET_NULL;
    }else{
        return DB_RET_OK;
    }
}
//搜索所有已存设备
int DBTraceAPI::DBSearchDeviceID(vector<string>&DeviceID){
    DB.useDB(database);
    table="Device";
    value="DeviceID";
    //搜索设备表，获取设备ID
    string_table ret=DB.selectItem(table,value);
    if(ret.size()==0){
        return DB_RET_NULL;
    }
    for(unsigned int i=0;i<ret.size();i++){
        DeviceID.push_back(ret[i][0]);
    }
    return DB_RET_OK;
}
//删除单条轨迹信息
int DBTraceAPI::DBDeleteTrace(DBTrace trace){
    DB.useDB(database);
    table="Trace";
    value="TableName";
    limits="YearMonth='"+trace.time.substr(0,4)+trace.time.substr(5,2)+"'";
    //搜索轨迹所在表格
    string_table ret=DB.selectItem(table,value,limits);
    if(ret.size()==0){
        return DB_RET_NULL;
    }
    table=ret[0][0];
    limits="TraceID="+to_string(trace.TraceID);
    //删除轨迹
    if(DB.deleteItem(table,limits)){
        return DB_RET_OK;
    }else{
        return DB_RET_FALL;
    }
}
//删除设备以及其对应关系
int DBTraceAPI::DBDeleteDevice(string DeviceID){
    DB.useDB(database);
    table="Device";
    limits="DeviceID='"+DeviceID+"'";
    DB.autoCommitOff();
    bool flag_delete=true;
    //删除在设备表中的信息
    if(DB.deleteItem(table,limits)==false){
        flag_delete=false;
    }
    table="Device_Person";
    //删除在设备人员关系表中的信息
    if(DB.deleteItem(table,limits)==false){
        flag_delete=false;
    }
    //若失败则部提交事件，事件回滚保持原有状态
    if(flag_delete==true){
        DB.commit();
        return DB_RET_OK;
    }else{
        DB.rollback();
        return DB_RET_FALL;
    }
}
//删除围栏信息
int DBTraceAPI::DBDeleteMap(int MapMark){
    DB.useDB(database);
    table="Map";
    limits="MapMark="+to_string(MapMark);
    if(DB.deleteItem(table,limits)){
        return DB_RET_OK;
    }else{
        return DB_RET_FALL;
    }
}
//更新轨迹信息
int DBTraceAPI::DBUpdateTrace(DBTrace traceOld,DBTrace traceNew){
    DB.useDB(database);
    table="Trace";
    value="TableName";
    limits="YearMonth="+traceOld.time.substr(0,4)+traceOld.time.substr(5,2);
    //搜索该条轨迹说在表格
    string_table ret=DB.selectItem(table,value,limits);
    if(ret.size()==0){
        return DB_RET_NULL;
    }
    table=ret[0][0];
    value="PersonID="+to_string(traceNew.PersonID)+", PersonModule="+to_string(traceNew.PersonModule)+", DeviceID=\""+traceNew.DeviceID+"\", X="+to_string(traceNew.X)+", Y="+to_string(traceNew.Y)+", Floor=\""+traceNew.Floor+"\", MapMark="+to_string(traceNew.MapMark)+", time=\""+traceNew.time+"\"";
    limits="TraceID="+to_string(traceOld.TraceID);
    if(DB.updateItem(table,value,limits)){
        return DB_RET_OK;
    }else{
        return DB_RET_FALL;
    }
}
//清除所有轨迹表
int DBTraceAPI::DBClearTable(){
    DB.useDB(database);
    table="Trace";
    value="distinct TableName";
    //获取所有轨迹表名
    string_table ret=DB.selectItem(table,value);
    if(ret.size()==0){
        return DB_RET_NULL;
    }
    //批量删除
    DB.autoCommitOff();
    bool flag_delete=true;
    for(unsigned int i=0;i<ret.size();i++){
        if(DB.deleteTB(ret[i][0])==false){
            flag_delete=false;
            break;
        }
    }
    if(DB.clearTB(table)==false){
        flag_delete=false;
    }
    if(flag_delete){
        DB.commit();
        return DB_RET_OK;
    }else{
        DB.rollback();
        return DB_RET_FALL;
    }
}
//具体围栏数据统计
int DBTraceAPI::DBMapCount(int PersonID,int MapMark,ptime timeBegin,ptime timeEnd,DBMapData&MapData){
    DB.useDB(database);
    vector<DBTrace> Traces;
    int flagOld=0;
    int flagNew=0;
    int res=DBSearchPersonTrace(PersonID,timeBegin,timeEnd,Traces);
    MapData.PersonID=PersonID;
    MapData.MapMark=MapMark;
    if(res==DB_RET_OK){
        for(unsigned int i=0;i<Traces.size();i++){
            if(Traces[i].MapMark==MapMark){
                flagNew=1;
            }else{
                flagNew=0;
            }
            if(flagNew==1 && flagOld==0){
                MapData.Enter++;
            }else if (flagNew==0 && flagOld==1)
            {
                ptime temp = (time_from_string(Traces[i].time)+MapData.StayTime);
                MapData.StayTime=temp-time_from_string(Traces[i-1].time);
                MapData.Out++;
            }else if (flagNew==1 && flagOld==1)
            {
                ptime temp = time_from_string(Traces[i].time)+MapData.StayTime;
                MapData.StayTime=temp-time_from_string(Traces[i-1].time);
            }
            flagOld=flagNew;
        }
    }else if (res==DB_RET_NULL){
        MapData.Enter=0;
        MapData.Out=0;
        MapData.StayTime=time_from_string("2020-02-01 00:00:00")-time_from_string("2020-02-01 00:00:00");
    }else{
        return DB_RET_FALL;
    }
    return DB_RET_OK;
}
//具体人员在围栏位置的统计
int DBTraceAPI::DBMapPersonCount(int PersonID, ptime timeBegin,ptime timeEnd,vector<DBMapData>&MapData){
    DB.useDB(database);
    vector<DBTrace> Traces;
    int res=DBSearchPersonTrace(PersonID,timeBegin,timeEnd,Traces);
    if(res==DB_RET_OK){
        table="MapMark";
        value="MapMark";
        string_table ret=DB.selectItem(table,value);
        for(int i=0;i<ret.size();i++){
            int flagOld=0;
            int flagNew=0;
            int MapMark=atoi(ret[i][0].c_str());
            DBMapData tempMapData(PersonID,MapMark);
            for(unsigned int i=0;i<Traces.size();i++){
                if(Traces[i].MapMark==MapMark){
                    flagNew=1;
                }else{
                    flagNew=0;
                }
                if(flagNew==1 && flagOld==0){
                    tempMapData.Enter++;
                }else if (flagNew==0 && flagOld==1)
                {
                    ptime temp = (time_from_string(Traces[i].time)+tempMapData.StayTime);
                    tempMapData.StayTime=temp-time_from_string(Traces[i-1].time);
                    tempMapData.Out++;
                }else if (flagNew==1 && flagOld==1)
                {
                    ptime temp = (time_from_string(Traces[i].time)+tempMapData.StayTime);
                    tempMapData.StayTime=temp-time_from_string(Traces[i-1].time);
                    tempMapData.Out++;
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
//具体围栏的统计
int DBTraceAPI::DBMapMarkCount(int MapMark,ptime timeBegin,ptime timeEnd,vector<DBMapData>&MapData){
    DB.useDB(database);
    table="Person";
    value="PersonID";
    string_table ret=DB.selectItem(table,value);
    if(ret.size()==0){
        return DB_RET_PERSON_ERROR;
    }
    DBMapData tempMapData;
    int resultcode[ret.size()];
    for(unsigned int i=0;i<ret.size();i++){
        resultcode[i]=DBMapCount(atoi(ret[i][0].c_str()),MapMark,timeBegin,timeEnd,tempMapData);
        MapData.push_back(tempMapData);
    }
    return DB_RET_OK;
}
//删除数据库
int DBTraceAPI::DBDeleteDB(){
    if(DB.deleteDB(database)){
        return DB_RET_OK;
    }else{
        return DB_RET_FALL;
    }
}