
#include<iostream>
#include<string>
#include"DataBase.h"
#include"DBStruct.h"
#include"DBTraceAPI.h"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#define BOOST_DATE_TIME_SOURCE
using namespace boost::posix_time;
using namespace boost::gregorian;
using namespace std;
using namespace boost;


//连接数据库测试方法
int connectDBtest(DBTraceAPI&DBAPI){
	int info;
	info=DBAPI.DBConnect();
	return info;
}
//创建数据库测试方法
int creatDBtest(DBTraceAPI&DBAPI){
	int info;
	info=DBAPI.DBCreateDB();
	return info;
}
//单条设备输入验证
int addDeviceDBtest(DBTraceAPI&DBAPI){
	int info;
	DBDeviceData temp;
	temp.DeviceID="D101";
	temp.PersonID=101;
	temp.PersonModule=1;
	info=DBAPI.DBAddDevice(temp);
	cout<<info<<endl;

	temp.DeviceID="D102";
	info=DBAPI.DBAddDevice(temp);
	return info;
}
//多条设备输入验证
int addSomeDeviceDBtest(DBTraceAPI&DBAPI){
	int info;
	vector<DBDeviceData> deviceData;	
	for(int i=3;i<=5;i++){
		DBDeviceData temp1;
		temp1.PersonID=100+i;
		temp1.DeviceID="D"+to_string(100+i);
		temp1.PersonModule=1;
		deviceData.push_back(temp1);
	}
	for(int i=1;i<=5;i++){
		DBDeviceData temp2;
		temp2.DeviceID="D"+to_string(105+i);
		temp2.PersonID=0;
		temp2.PersonModule=0;
		deviceData.push_back(temp2);
	}
	info=DBAPI.DBAddSomeDevice(deviceData);
	return info;
}
//单条设备人员关系表更新测试
int updateRelatedtest(DBTraceAPI&DBAPI){
	int info;
	DBDeviceData temp1;
	temp1.DeviceID="D101";
	info=DBAPI.DBUpdateDeviceRelat(temp1);
	cout<<info<<endl;
	DBDeviceData temp2;
	temp2.DeviceID="D106";
	temp2.PersonID=106;
	temp2.PersonModule=1;
	info=DBAPI.DBUpdateDeviceRelat(temp2);
	return info;
}
//多条设备人员关系表更新测试
int updateSomeRelatedtest(DBTraceAPI&DBAPI){
	int info;
	vector<DBDeviceData> deviceData;
	DBDeviceData temp;
	temp.DeviceID="D101";
	temp.PersonID=101;
	temp.PersonModule=1;
	deviceData.push_back(temp);
	for(int i=2;i<=6;i++){
		DBDeviceData temp;
		temp.DeviceID="D"+to_string(100+i);
		temp.PersonID=0;
		temp.PersonModule=0;
		deviceData.push_back(temp);
	}
	for(int i=2;i<=5;i++){
		DBDeviceData temp;
		temp.DeviceID="D"+to_string(105+i);
		temp.PersonID=105+i;
		temp.PersonModule=1;
		deviceData.push_back(temp);
	}
	info=DBAPI.DBUpdateSomeDeviceRelat(deviceData);
	return info;
}
//单条增加人员测试方法
int addPersontest(DBTraceAPI&DBAPI){
	int info;
	DBDeviceData temp;
	temp.PersonID=101;
	temp.PersonModule=1;
	info=DBAPI.DBAddPerson(temp);
	return info;
}
//多条增加人员测试方法
int addSomePersontest(DBTraceAPI&DBAPI){
	int info;
	vector<DBDeviceData> deviceData;	
	for(int i=2;i<=10;i++){
		DBDeviceData temp1;
		temp1.PersonID=100+i;
		temp1.PersonModule=1;
		deviceData.push_back(temp1);
	}
	info=DBAPI.DBAddSomePerson(deviceData);
	return info;
}
//单条添加围栏信息测试方法
int addMapMarktest(DBTraceAPI&DBAPI){
	int info;
	int tempMapMark=1;
	info=DBAPI.DBAddMapMark(tempMapMark);
	return info;
}
//多条添加围栏信息测试方法
int addSomeMapMarktest(DBTraceAPI&DBAPI){
	int info;
	vector<int> mapmark;
	mapmark.push_back(2);
	mapmark.push_back(3);
	info=DBAPI.DBAddSomeMapMark(mapmark);
	return info;
}
//单条BCON信息测试方法
int addBCONtest(DBTraceAPI&DBAPI){
	int info;
	BCON bcon;
	bcon.BCONID=1;
	bcon.BCONX=1;
	bcon.BCONY=1;
	bcon.Floor="1F";
	info=DBAPI.DBAddBCON(bcon);
	return info;
}
//多条添加BCON信息测试方法
int addSomeBCONtest(DBTraceAPI&DBAPI){
	int info;
	vector<BCON> bcon;
	
	for(int i=2;i<=3;i++){
		BCON tempbcon;
		tempbcon.BCONID=i;
		tempbcon.BCONX=1;
		tempbcon.BCONY=i;
		tempbcon.Floor="1F";
		bcon.push_back(tempbcon);
	}
	for(int i=4;i<=7;i++){
		BCON tempbcon;
		tempbcon.BCONID=i;
		tempbcon.BCONX=2;
		tempbcon.BCONY=i-3;
		tempbcon.Floor="2F";
		bcon.push_back(tempbcon);
	}
	for(int i=8;i<=10;i++){
		BCON tempbcon;
		tempbcon.BCONID=i;
		tempbcon.BCONX=3;
		tempbcon.BCONY=i-7;
		tempbcon.Floor="3F";
		bcon.push_back(tempbcon);
	}	
	info=DBAPI.DBAddSomeBCON(bcon);
	return info;
}
//单条添加BCON和MapMark关系表测试方法
int addMaptest(DBTraceAPI&DBAPI){
	int info;
	Map map;
	map.MapMark=1;
	map.BCONID=1;
	info=DBAPI.DBAddMap(map);
	return info;
}
//多条添加BCON和MapMark关系表测试方法
int addSomeMaptest(DBTraceAPI&DBAPI){
	int info;
	vector<Map> map;
	for(int i=2;i<=3;i++){
		Map tempmap;
		tempmap.MapMark=1;
		tempmap.BCONID=i;
		map.push_back(tempmap);
	}
	for(int i=4;i<=7;i++){
		Map tempmap;
		tempmap.MapMark=2;
		tempmap.BCONID=i;
		map.push_back(tempmap);
	}
	for(int i=8;i<=10;i++){
		Map tempmap;
		tempmap.MapMark=3;
		tempmap.BCONID=i;
		map.push_back(tempmap);
	}
	info=DBAPI.DBAddSomeMap(map);
	return info;
}
//单条添加轨迹测试方法
int addTracetest(DBTraceAPI&DBAPI){
	DBTrace trace;
	int info;
	trace.PersonID=101;
	trace.PersonModule=1;
	trace.DeviceID="D101";
	trace.X=1;
	trace.Y=1;
	trace.Floor="1F";
	trace.time="2020-02-26 09:53:26";
	trace.MapMark=1;
	info=DBAPI.DBAddTrace(trace);
	return info;
}
//多条添加轨迹测试方法
int addSomeTracetest(DBTraceAPI&DBAPI){
	vector<DBTrace> trace;
	DBTrace temp;
	int info;
	temp.PersonID=101;
	temp.PersonModule=1;
	temp.DeviceID="D101";	
	temp.X=2;
	temp.Y=2;
	temp.Floor="1F";
	temp.time="2020-02-26 09:55:26";
	temp.MapMark=1;
	trace.push_back(temp);
	temp.X=3;
	temp.Y=3;
	temp.Floor="2F";
	temp.time="2020-02-26 09:57:26";
	temp.MapMark=2;
	trace.push_back(temp);
	temp.PersonID=102;
	temp.PersonModule=1;
	temp.DeviceID="D102";	
	temp.X=4;
	temp.Y=4;
	temp.Floor="2F";
	temp.time="2020-02-26 10:53:26";
	temp.MapMark=2;
	trace.push_back(temp);
	temp.PersonID=102;
	temp.PersonModule=1;
	temp.DeviceID="D102";	
	temp.X=4;
	temp.Y=4;
	temp.Floor="2F";
	temp.time="2020-03-26 10:53:26";
	temp.MapMark=2;
	trace.push_back(temp);
	info=DBAPI.DBAddSomeTrace(trace);
	return info;
}
//删除数据库测试方法
int deleteDBtest(DBTraceAPI&DBAPI){
	int info;
	info=DBAPI.DBDeleteDB();
	return info;
}
//单条查询最近轨迹（按设备ID）
int selectDevicetest(DBTraceAPI&DBAPI){
	int info;
	DBTrace rec;
	string DeviceID="D101";
	info=DBAPI.DBSearchDevice(DeviceID,rec);
	cout<<"TraceID="<<rec.TraceID<<",PersonID="<<rec.PersonID<<",PersonModule="<<rec.PersonModule<<",DeviceID="<<rec.DeviceID<<",X="<<rec.X<<",Y="<<rec.Y<<",Floor="<<rec.Floor<<",MapMark="<<rec.MapMark<<",Time="<<rec.time<<endl;
	return info;
}
//多条查询最近轨迹（按设备ID）
int selectSomeDevicetest(DBTraceAPI&DBAPI){
	int info;
	vector<DBTrace> rec;
	vector<string> DeviceID;
	string DeviceIDtemp="D101";
	DeviceID.push_back(DeviceIDtemp);
	DeviceIDtemp="D102";
	DeviceID.push_back(DeviceIDtemp);

	DeviceIDtemp="D103";
	DeviceID.push_back(DeviceIDtemp);
	info=DBAPI.DBSearchSomeDevice(DeviceID,rec);
	for(int i=0;i<rec.size();i++){
		cout<<"TraceID="<<rec[i].TraceID<<",PersonID="<<rec[i].PersonID<<",PersonModule="<<rec[i].PersonModule<<",DeviceID="<<rec[i].DeviceID<<",X="<<rec[i].X<<",Y="<<rec[i].Y<<",Floor="<<rec[i].Floor<<",MapMark="<<rec[i].MapMark<<",Time="<<rec[i].time<<endl;
	}
	return info;
}
//查询所有最近轨迹（按设备ID）
int selectAllDevicetest(DBTraceAPI&DBAPI){
	int info;
	vector<DBTrace> rec;
	info=DBAPI.DBSearchAllDevice(rec);
	for(int i=0;i<rec.size();i++){
		cout<<"TraceID="<<rec[i].TraceID<<",PersonID="<<rec[i].PersonID<<",PersonModule="<<rec[i].PersonModule<<",DeviceID="<<rec[i].DeviceID<<",X="<<rec[i].X<<",Y="<<rec[i].Y<<",Floor="<<rec[i].Floor<<",MapMark="<<rec[i].MapMark<<",Time="<<rec[i].time<<endl;
	}
	return info;
}
//单条查询最近轨迹（按人员ID）
int selectPersontest(DBTraceAPI&DBAPI){
	int info;
	DBTrace rec;
	int PersonID=101;
	info=DBAPI.DBSearchPerson(PersonID,rec);
	cout<<"TraceID="<<rec.TraceID<<",PersonID="<<rec.PersonID<<",PersonModule="<<rec.PersonModule<<",DeviceID="<<rec.DeviceID<<",X="<<rec.X<<",Y="<<rec.Y<<",Floor="<<rec.Floor<<",MapMark="<<rec.MapMark<<",Time="<<rec.time<<endl;
	return info;
}
//多条查询最近轨迹（按人员ID）
int selectSomePersontest(DBTraceAPI&DBAPI){
	int info;
	vector<DBTrace> rec;
	vector<int>PersonID;
	int PersonIDtemp=101;
	PersonID.push_back(PersonIDtemp);
	PersonIDtemp=102;
	PersonID.push_back(PersonIDtemp);
	PersonIDtemp=103;
	PersonID.push_back(PersonIDtemp);
	info=DBAPI.DBSearchSomePerson(PersonID,rec);
	for(int i=0;i<rec.size();i++){
		cout<<"TraceID="<<rec[i].TraceID<<",PersonID="<<rec[i].PersonID<<",PersonModule="<<rec[i].PersonModule<<",DeviceID="<<rec[i].DeviceID<<",X="<<rec[i].X<<",Y="<<rec[i].Y<<",Floor="<<rec[i].Floor<<",MapMark="<<rec[i].MapMark<<",Time="<<rec[i].time<<endl;
	}
	return info;
}
//查询所有最近轨迹（按人员ID）
int selectAllPersontest(DBTraceAPI&DBAPI){
	int info;
	vector<DBTrace> rec;
	info=DBAPI.DBSearchAllPerson(rec);
	for(int i=0;i<rec.size();i++){
		cout<<"TraceID="<<rec[i].TraceID<<",PersonID="<<rec[i].PersonID<<",PersonModule="<<rec[i].PersonModule<<",DeviceID="<<rec[i].DeviceID<<",X="<<rec[i].X<<",Y="<<rec[i].Y<<",Floor="<<rec[i].Floor<<",MapMark="<<rec[i].MapMark<<",Time="<<rec[i].time<<endl;
	}
	return info;
}
//查询时间区间内的轨迹（人员ID+时间区间）
int selectPersonTracetest(DBTraceAPI&DBAPI){
	int info;
	vector<DBTrace> rec;
	ptime begin=time_from_string("2020-04-26 09:53:00");
	ptime end=time_from_string("2020-05-26 09:57:00");
	int PersonID=101;
	info=DBAPI.DBSearchPersonTrace(PersonID,begin,end,rec);
	for(int i=0;i<rec.size();i++){
		cout<<"TraceID="<<rec[i].TraceID<<",PersonID="<<rec[i].PersonID<<",PersonModule="<<rec[i].PersonModule<<",DeviceID="<<rec[i].DeviceID<<",X="<<rec[i].X<<",Y="<<rec[i].Y<<",Floor="<<rec[i].Floor<<",MapMark="<<rec[i].MapMark<<",Time="<<rec[i].time<<endl;
	}
	return info;
}
//查询时间区间内的轨迹（设备ID+时间区间）
int selectDeviceTracetest(DBTraceAPI&DBAPI){
	int info;
	vector<DBTrace> rec;
	ptime begin=time_from_string("2020-04-26 09:53:00");
	ptime end=time_from_string("2020-05-26 09:57:00");
	string DeviceID="D101";
	info=DBAPI.DBSearchDeviceTrace(DeviceID,begin,end,rec);
	for(int i=0;i<rec.size();i++){
		cout<<"TraceID="<<rec[i].TraceID<<",PersonID="<<rec[i].PersonID<<",PersonModule="<<rec[i].PersonModule<<",DeviceID="<<rec[i].DeviceID<<",X="<<rec[i].X<<",Y="<<rec[i].Y<<",Floor="<<rec[i].Floor<<",MapMark="<<rec[i].MapMark<<",Time="<<rec[i].time<<endl;
	}
	return info;
}
//查询所有已有的设备ID
int selectDevices(DBTraceAPI&DBAPI){
	int info;
	vector<string> rec;
	info=DBAPI.DBSearchDeviceID(rec);
	for(int i=0;i<rec.size();i++){
		cout<<"DeviceID="<<rec[i]<<endl;
	}
	return info;
}
//统计标识（PersonID+Time+MapMark）
int mapCount(DBTraceAPI&DBAPI){
	int info;
	int PersonID=101;
	int MapMark=1;
	ptime timeBegin=time_from_string("2020-04-26 09:53:00");
	ptime timeEnd=time_from_string("2020-05-26 10:53:00");
	DBMapData MapData;
	info=DBAPI.DBMapCount(PersonID,MapMark,timeBegin,timeEnd,MapData);
	cout<<"PersinID="<<MapData.PersonID<<",MapMark="<<MapData.MapMark<<",EnterTimes="<<MapData.Enter<<",OutTimes="<<MapData.Out<<",StayTime="<<MapData.StayTime<<endl;
	return info;
}
//统计标识（PersonID+Time）
int mapPersonCount(DBTraceAPI&DBAPI){
	int info;
	int PersonID=101;
	ptime timeBegin=time_from_string("2020-04-26 09:53:00");
	ptime timeEnd=time_from_string("2020-05-26 10:54:00");
	vector<DBMapData> MapData;
	info=DBAPI.DBMapPersonCount(PersonID,timeBegin,timeEnd,MapData);
	for(int i=0;i<MapData.size();i++){
		cout<<"PersinID="<<MapData[i].PersonID<<",MapMark="<<MapData[i].MapMark<<",EnterTimes="<<MapData[i].Enter<<",OutTimes="<<MapData[i].Out<<",StayTime="<<MapData[i].StayTime<<endl;
	}
	return info;
}
//统计标识（Time+MapMark）
int mapMarkCount(DBTraceAPI&DBAPI){
	int info;
	int MapMark=2;
	ptime timeBegin=time_from_string("2020-04-26 09:53:00");
	ptime timeEnd=time_from_string("2020-05-26 10:54:00");
	vector<DBMapData> MapData;
	info=DBAPI.DBMapMarkCount(MapMark,timeBegin,timeEnd,MapData);
	for(int i=0;i<MapData.size();i++){
		cout<<"PersinID="<<MapData[i].PersonID<<",MapMark="<<MapData[i].MapMark<<",EnterTimes="<<MapData[i].Enter<<",OutTimes="<<MapData[i].Out<<",StayTime="<<MapData[i].StayTime<<endl;
	}
	return info;
	return info;
}
//删除单条轨迹
int deleteTrace(DBTraceAPI&DBAPI){
	int info;
	DBTrace trace;
	trace.TraceID=5;
	trace.time="2020-03-26 10:53:26";
	info=DBAPI.DBDeleteTrace(trace);
	return info;
}
//删除单个设备
int deleteDevice(DBTraceAPI&DBAPI){
	int info;
	string DeviceID="D110";
	info=DBAPI.DBDeleteDevice(DeviceID);
	return info;
}
//删除单个围栏
int deleteMap(DBTraceAPI&DBAPI){
	int info;
	int MapMark=3;
	info=DBAPI.DBDeleteMap(MapMark);
	return info;
}
//更新轨迹
int updateTrace(DBTraceAPI&DBAPI){
	int info;
	DBTrace traceOld;
	DBTrace traceNew;
	traceOld.TraceID=4;
	traceOld.PersonID=102;
	traceOld.PersonModule=1;
	traceOld.DeviceID="D102";
	traceOld.X=4;
	traceOld.Y=4;
	traceOld.Floor="2F";
	traceOld.MapMark=2;
	traceOld.time="2020-02-26 10:53:26";

	traceNew.TraceID=4;
	traceNew.PersonID=101;
	traceNew.PersonModule=1;
	traceNew.DeviceID="D101";
	traceNew.X=4;
	traceNew.Y=4;
	traceNew.Floor="2F";
	traceNew.MapMark=2;
	traceNew.time="2020-02-26 10:53:26";

	info=DBAPI.DBUpdateTrace(traceOld,traceNew);
	return info;
}
int clearTable(DBTraceAPI&DBAPI){
	int info;
	info=DBAPI.DBClearTable();
	return info;
}
//多条跨表查询数据添加轨迹测试方法
int addcrossSomeTracetest(DBTraceAPI&DBAPI){
	int info;
	vector<DBTrace> trace;
	DBTrace temp;
	temp.getvalue(101,1,"D101",2,2,"2F",2,"2020-02-29 10:20:00");
	trace.push_back(temp);
	temp.getvalue(101,1,"D101",2,2,"2F",2,"2020-04-30 10:20:00");
	trace.push_back(temp);
	temp.getvalue(101,1,"D101",2,2,"2F",2,"2020-04-30 10:25:00");
	trace.push_back(temp);
	temp.getvalue(101,1,"D101",1,1,"1F",1,"2020-04-30 10:30:00");
	trace.push_back(temp);
	temp.getvalue(101,1,"D101",1,1,"1F",1,"2020-04-30 10:33:00");
	trace.push_back(temp);
	temp.getvalue(101,1,"D101",2,2,"2F",2,"2020-04-30 10:45:00");
	trace.push_back(temp);
	temp.getvalue(101,1,"D101",2,2,"2F",2,"2020-04-30 11:00:00");
	trace.push_back(temp);
	temp.getvalue(101,1,"D101",2,2,"2F",2,"2020-04-30 23:50:00");
	trace.push_back(temp);
	temp.getvalue(101,1,"D101",1,1,"1F",1,"2020-04-30 23:55:00");
	trace.push_back(temp);
	temp.getvalue(101,1,"D101",1,1,"1F",1,"2020-05-01 00:05:00");
	trace.push_back(temp);
	temp.getvalue(101,1,"D101",2,2,"2F",2,"2020-05-01 00:10:00");
	trace.push_back(temp);
	info=DBAPI.DBAddSomeTrace(trace);
	return info;
}


int main(int argc,char const *argv[]){
    //接口类的调用
	DBTraceAPI DBAPI;
	int info;
	//数据库建立连接
	info=connectDBtest(DBAPI);
	cout<<info<<endl;
/*
	//数据库创建
	info=creatDBtest(DBAPI);
	cout<<info<<endl;
	//单条添加设备
	info=addDeviceDBtest(DBAPI);
	cout<<info<<endl;
	//多条添加设备
	info=addSomeDeviceDBtest(DBAPI);
	cout<<info<<endl;
	//单条更新设备人员关系
	info=updateRelatedtest(DBAPI);
	cout<<info<<endl;
	//多条更新设备人员关系
	info=updateSomeRelatedtest(DBAPI);
	cout<<info<<endl;
	//单条添加人员
	info=addPersontest(DBAPI);
	cout<<info<<endl;
	//多条添加人员
	info=addSomePersontest(DBAPI);
	cout<<info<<endl;
	//单条添加围栏
	info=addMapMarktest(DBAPI);
	cout<<info<<endl;
	//多条添加围栏
	info=addSomeMapMarktest(DBAPI);
	cout<<info<<endl;
	//单条添加BCON
	info=addBCONtest(DBAPI);
	cout<<info<<endl;
	//多条添加BCON
	info=addSomeBCONtest(DBAPI);
	cout<<info<<endl;
	//单条添加围栏和BCON对应关系
	info=addMaptest(DBAPI);
	cout<<info<<endl;
	//多条添加围栏和BCON对应关系
	info=addSomeMaptest(DBAPI);
	cout<<info<<endl;
*/
/*	
	//单条添加轨迹信息
	info=addTracetest(DBAPI);
	cout<<info<<endl;
	//多条添加轨迹信息
	info=addSomeTracetest(DBAPI);
	cout<<info<<endl;
	//单条查询最近轨迹（按设备ID）
	info=selectDevicetest(DBAPI);
	cout<<info<<endl;
	//多条查询最近轨迹（按设备ID）
	info=selectSomeDevicetest(DBAPI);
	cout<<info<<endl;
	//单条查询最近轨迹（按人员ID）
	info=selectPersontest(DBAPI);
	cout<<info<<endl;
	//多条查询最近轨迹（按人员ID）
	info=selectSomePersontest(DBAPI);
	cout<<info<<endl;
	//查询所有最近轨迹（按设备ID）
	info=selectAllDevicetest(DBAPI);
	cout<<info<<endl;
	//查询所有最近轨迹（按人员ID）
	info=selectAllPersontest(DBAPI);
	cout<<info<<endl;	
	//查询时间区间内的轨迹（人员ID+时间）
	info=selectPersonTracetest(DBAPI);
	cout<<info<<endl;
	//查询时间区间内的轨迹（设备ID+时间）
	info=selectDeviceTracetest(DBAPI);
	cout<<info<<endl;
	//查询所有已有设备ID
	info=selectDevices(DBAPI);
	cout<<info<<endl;	
	//统计标识（PersonID+Time+MapMark）
	info=mapCount(DBAPI);
	cout<<info<<endl;
	//统计标识（PersonID+Time）
	info=mapPersonCount(DBAPI);
	cout<<info<<endl;
	//统计标识（Time+MapMark）
	info=mapMarkCount(DBAPI);
	cout<<info<<endl;
	//删除单条轨迹
	info=deleteTrace(DBAPI);
	cout<<info<<endl;
	//删除单个设备
	info=deleteDevice(DBAPI);
	cout<<info<<endl;
	//删除单个围栏
	info=deleteMap(DBAPI);
	cout<<info<<endl;
	//更新单条轨迹
	info=updateTrace(DBAPI);
	cout<<info<<endl;

	//清除所有轨迹数据
	info=clearTable(DBAPI);
	cout<<info<<endl;
*/
	//info=addcrossSomeTracetest(DBAPI);
	//cout<<info<<endl;

	info=selectPersonTracetest(DBAPI);
	cout<<info<<endl;
	info=selectDeviceTracetest(DBAPI);
	cout<<info<<endl;
	info=mapCount(DBAPI);
	cout<<info<<endl;
	info=mapMarkCount(DBAPI);
	cout<<info<<endl;
	info=mapPersonCount(DBAPI);
	cout<<info<<endl;



	//删除数据库
	//info=deleteDBtest(DBAPI);
	//cout<<info<<endl;

	
	
	return 0;
}