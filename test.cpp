#include<iostream>
#include<string>
#include"db/DataBase.h"
#include"db/DBStruct.h"
#include"db/DBTraceAPI.h"
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
	ptime tick,now;
	time_duration diff;
	tick=microsec_clock::local_time();  
	info=DBAPI.DBConnect();
	now=microsec_clock::local_time();
	diff=now-tick;	
	cout<<"use "<<diff.total_milliseconds()<<" ms"<<endl;
	return info;
}
//创建数据库测试方法
int creatDBtest(DBTraceAPI&DBAPI){ 
	int info;
	ptime tick,now;
	time_duration diff;
	tick=microsec_clock::local_time(); 
	info=DBAPI.DBCreateDB();
	now=microsec_clock::local_time();
	diff=now-tick;	
	cout<<"use "<<diff.total_milliseconds()<<" ms"<<endl;
	return info;
}
//单条设备输入验证
int addDeviceDBtest(DBTraceAPI&DBAPI){ 
	int info;
	DBDeviceData temp;
	temp.DeviceID="D101";
	temp.PersonID=101;
	temp.PersonModule=1;
	ptime tick,now;
	time_duration diff;
	tick=microsec_clock::local_time(); 
	info=DBAPI.DBAddDevice(temp);
	now=microsec_clock::local_time();
	diff=now-tick;	
	cout<<"use "<<diff.total_milliseconds()<<" ms"<<endl;
	return info;
}
//多条设备输入验证
int addSomeDeviceDBtest(DBTraceAPI&DBAPI){
	int info;
	vector<DBDeviceData> deviceData;	
	for(int i=2;i<=5;i++){
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
	ptime tick,now;
	time_duration diff;
	tick=microsec_clock::local_time();
	info=DBAPI.DBAddDevice(deviceData);
	now=microsec_clock::local_time();
	diff=now-tick;	
	cout<<"use "<<diff.total_milliseconds()<<" ms"<<endl;
	return info;
}
//单条设备人员关系表更新测试
int updateRelatedtest(DBTraceAPI&DBAPI){
	int info;
	DBDeviceData temp1;
	temp1.DeviceID="D101";
	ptime tick,now;
	time_duration diff;
	tick=microsec_clock::local_time();  
	info=DBAPI.DBUpdateDeviceRelat(temp1);
	now=microsec_clock::local_time();
	diff=now-tick;	
	cout<<"use "<<diff.total_milliseconds()<<" ms"<<endl;
	cout<<info<<endl;
	DBDeviceData temp2;
	temp2.DeviceID="D106";
	temp2.PersonID=106;
	temp2.PersonModule=1;
	tick=microsec_clock::local_time();  
	info=DBAPI.DBUpdateDeviceRelat(temp2);
	now=microsec_clock::local_time();
	diff=now-tick;	
	cout<<"use "<<diff.total_milliseconds()<<" ms"<<endl;
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
	ptime tick,now;
	time_duration diff;
	tick=microsec_clock::local_time();  
	info=DBAPI.DBUpdateDeviceRelat(deviceData);
	now=microsec_clock::local_time();
	diff=now-tick;	
	cout<<"use "<<diff.total_milliseconds()<<" ms"<<endl;
	return info;
}
//单条增加人员测试方法
int addPersontest(DBTraceAPI&DBAPI){
	int info;
	DBDeviceData temp;
	temp.PersonID=101;
	temp.PersonModule=1;
	ptime tick,now;
	time_duration diff;
	tick=microsec_clock::local_time();  
	info=DBAPI.DBAddPerson(temp);
	now=microsec_clock::local_time();
	diff=now-tick;	
	cout<<"use "<<diff.total_milliseconds()<<" ms"<<endl;
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
	ptime tick,now;
	time_duration diff;
	tick=microsec_clock::local_time();  
	info=DBAPI.DBAddPerson(deviceData);
	now=microsec_clock::local_time();
	diff=now-tick;	
	cout<<"use "<<diff.total_milliseconds()<<" ms"<<endl;
	return info;
}
//单条添加围栏信息测试方法
int addMapMarktest(DBTraceAPI&DBAPI){
	int info;
	int tempMapMark=1;
	ptime tick,now;
	time_duration diff;
	tick=microsec_clock::local_time();  
	info=DBAPI.DBAddMapMark(tempMapMark);
	now=microsec_clock::local_time();
	diff=now-tick;	
	cout<<"use "<<diff.total_milliseconds()<<" ms"<<endl;
	return info;
}
//多条添加围栏信息测试方法
int addSomeMapMarktest(DBTraceAPI&DBAPI){
	int info;
	vector<int> mapmark;
	mapmark.push_back(2);
	mapmark.push_back(3);
	ptime tick,now;
	time_duration diff;
	tick=microsec_clock::local_time();  
	info=DBAPI.DBAddMapMark(mapmark);
	now=microsec_clock::local_time();
	diff=now-tick;	
	cout<<"use "<<diff.total_milliseconds()<<" ms"<<endl;
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
	ptime tick,now;
	time_duration diff;
	tick=microsec_clock::local_time();  
	info=DBAPI.DBAddBCON(bcon);
	now=microsec_clock::local_time();
	diff=now-tick;	
	cout<<"use "<<diff.total_milliseconds()<<" ms"<<endl;
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
	ptime tick,now;
	time_duration diff;
	tick=microsec_clock::local_time();  
	info=DBAPI.DBAddBCON(bcon);
	now=microsec_clock::local_time();
	diff=now-tick;	
	cout<<"use "<<diff.total_milliseconds()<<" ms"<<endl;
	return info;
}
//单条添加BCON和MapMark关系表测试方法
int addMaptest(DBTraceAPI&DBAPI){
	int info;
	Map map;
	map.MapMark=1;
	map.BCONID=1;
	ptime tick,now;
	time_duration diff;
	tick=microsec_clock::local_time();  
	info=DBAPI.DBAddMap(map);
	now=microsec_clock::local_time();
	diff=now-tick;	
	cout<<"use "<<diff.total_milliseconds()<<" ms"<<endl;
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
	ptime tick,now;
	time_duration diff;
	tick=microsec_clock::local_time();  
	info=DBAPI.DBAddMap(map);
	now=microsec_clock::local_time();
	diff=now-tick;	
	cout<<"use "<<diff.total_milliseconds()<<" ms"<<endl;
	return info;
}
//单条添加轨迹测试方法
int addTracetest(DBTraceAPI&DBAPI){
	DBTrace trace;
	int info;
	trace.getvalue(101,1,"D101",1,1,"1F",1,"2020-02-26 09:53:26");
	ptime tick,now;
	time_duration diff;
	tick=microsec_clock::local_time();  
	info=DBAPI.DBAddTrace(trace);
	now=microsec_clock::local_time();
	diff=now-tick;	
	cout<<"use "<<diff.total_milliseconds()<<" ms"<<endl;
	return info;
}
//多条添加轨迹测试方法
int addSomeTracetest(DBTraceAPI&DBAPI){
	vector<DBTrace> trace;
	DBTrace temp;
	int info;
	ptime time;
	string ti;
	time_duration onesecond=time_from_string("2020-05-26 10:54:01")-time_from_string("2020-05-26 10:54:00");
	time=second_clock::local_time();
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",2,2,"1F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",3,3,"2F",2,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(102,1,"D102",4,4,"2F",2,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(102,1,"D102",4,4,"2F",2,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	ptime tick,now;
	time_duration diff;
	tick=microsec_clock::local_time();  
	info=DBAPI.DBAddTrace(trace);
	now=microsec_clock::local_time();
	diff=now-tick;	
	cout<<"use "<<diff.total_milliseconds()<<" ms"<<endl;
	return info;
}
//删除数据库测试方法
int deleteDBtest(DBTraceAPI&DBAPI){
	int info;
	ptime tick,now;
	time_duration diff;
	tick=microsec_clock::local_time();  
	info=DBAPI.DBDeleteDB();
	now=microsec_clock::local_time();
	diff=now-tick;	
	cout<<"use "<<diff.total_milliseconds()<<" ms"<<endl;
	return info;
}
//单条查询最近轨迹（按设备ID）
int selectDevicetest(DBTraceAPI&DBAPI){
	int info;
	DBTrace rec;
	string DeviceID="D101";
	ptime tick,now;
	time_duration diff;
	tick=microsec_clock::local_time();  
	info=DBAPI.DBSearchDevice(DeviceID,rec);
	now=microsec_clock::local_time();
	diff=now-tick;	
	cout<<"use "<<diff.total_milliseconds()<<" ms"<<endl;
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
	ptime tick,now;
	time_duration diff;
	tick=microsec_clock::local_time();  
	info=DBAPI.DBSearchDevice(DeviceID,rec);
	now=microsec_clock::local_time();
	diff=now-tick;	
	cout<<"use "<<diff.total_milliseconds()<<" ms"<<endl;
	for(auto &v:rec){
		cout<<"TraceID="<<v.TraceID<<",PersonID="<<v.PersonID<<",PersonModule="<<v.PersonModule<<",DeviceID="<<v.DeviceID<<",X="<<v.X<<",Y="<<v.Y<<",Floor="<<v.Floor<<",MapMark="<<v.MapMark<<",Time="<<v.time<<endl;
	}
	return info;
}
//查询所有最近轨迹（按设备ID）
int selectAllDevicetest(DBTraceAPI&DBAPI){
	int info;
	vector<DBTrace> rec;
	ptime tick,now;
	time_duration diff;
	tick=microsec_clock::local_time();  
	info=DBAPI.DBSearchDevice(rec);
	now=microsec_clock::local_time();
	diff=now-tick;	
	cout<<"use "<<diff.total_milliseconds()<<" ms"<<endl;
	for(auto &v:rec){
		cout<<"TraceID="<<v.TraceID<<",PersonID="<<v.PersonID<<",PersonModule="<<v.PersonModule<<",DeviceID="<<v.DeviceID<<",X="<<v.X<<",Y="<<v.Y<<",Floor="<<v.Floor<<",MapMark="<<v.MapMark<<",Time="<<v.time<<endl;
	}
	return info;
}
//单条查询最近轨迹（按人员ID）
int selectPersontest(DBTraceAPI&DBAPI){
	int info;
	DBTrace rec;
	int PersonID=101;
	int PersonModule=1;
	ptime tick,now;
	time_duration diff;
	tick=microsec_clock::local_time();  
	info=DBAPI.DBSearchPerson(PersonID,PersonModule,rec);
	now=microsec_clock::local_time();
	diff=now-tick;	
	cout<<"use "<<diff.total_milliseconds()<<" ms"<<endl;
	cout<<"TraceID="<<rec.TraceID<<",PersonID="<<rec.PersonID<<",PersonModule="<<rec.PersonModule<<",DeviceID="<<rec.DeviceID<<",X="<<rec.X<<",Y="<<rec.Y<<",Floor="<<rec.Floor<<",MapMark="<<rec.MapMark<<",Time="<<rec.time<<endl;
	return info;
}
//多条查询最近轨迹（按人员ID）
int selectSomePersontest(DBTraceAPI&DBAPI){
	int info;
	vector<DBTrace> rec;
	vector<vector<int>> Person;
	for(int i=1;i<=3;i++){
		vector<int> temp;
		int PersonID=100+i;
		int PersonModule=1;
		temp.push_back(PersonID);
		temp.push_back(PersonModule);
		Person.push_back(temp);
	}
	ptime tick,now;
	time_duration diff;
	tick=microsec_clock::local_time();  
	info=DBAPI.DBSearchPerson(Person,rec);
	now=microsec_clock::local_time();
	diff=now-tick;	
	cout<<"use "<<diff.total_milliseconds()<<" ms"<<endl;
	for(auto &v:rec){
		cout<<"TraceID="<<v.TraceID<<",PersonID="<<v.PersonID<<",PersonModule="<<v.PersonModule<<",DeviceID="<<v.DeviceID<<",X="<<v.X<<",Y="<<v.Y<<",Floor="<<v.Floor<<",MapMark="<<v.MapMark<<",Time="<<v.time<<endl;
	}
	return info;
}
//查询所有最近轨迹（按人员ID）
int selectAllPersontest(DBTraceAPI&DBAPI){
	int info;
	vector<DBTrace> rec;
	ptime tick,now;
	time_duration diff;
	tick=microsec_clock::local_time();  
	info=DBAPI.DBSearchPerson(rec);
	now=microsec_clock::local_time();
	diff=now-tick;	
	cout<<"use "<<diff.total_milliseconds()<<" ms"<<endl;
	for(auto &v:rec){
		cout<<"TraceID="<<v.TraceID<<",PersonID="<<v.PersonID<<",PersonModule="<<v.PersonModule<<",DeviceID="<<v.DeviceID<<",X="<<v.X<<",Y="<<v.Y<<",Floor="<<v.Floor<<",MapMark="<<v.MapMark<<",Time="<<v.time<<endl;
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
	int PersonModule=1;
	ptime tick,now;
	time_duration diff;
	tick=microsec_clock::local_time();  
	info=DBAPI.DBSearchPersonTrace(PersonID,PersonModule=1,begin,end,rec);
	now=microsec_clock::local_time();
	diff=now-tick;	
	cout<<"use "<<diff.total_milliseconds()<<" ms"<<endl;
	for(auto &v:rec){
		cout<<"TraceID="<<v.TraceID<<",PersonID="<<v.PersonID<<",PersonModule="<<v.PersonModule<<",DeviceID="<<v.DeviceID<<",X="<<v.X<<",Y="<<v.Y<<",Floor="<<v.Floor<<",MapMark="<<v.MapMark<<",Time="<<v.time<<endl;
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
	ptime tick,now;
	time_duration diff;
	tick=microsec_clock::local_time();  
	info=DBAPI.DBSearchDeviceTrace(DeviceID,begin,end,rec);
	now=microsec_clock::local_time();
	diff=now-tick;	
	cout<<"use "<<diff.total_milliseconds()<<" ms"<<endl;
	for(auto &v:rec){
		cout<<"TraceID="<<v.TraceID<<",PersonID="<<v.PersonID<<",PersonModule="<<v.PersonModule<<",DeviceID="<<v.DeviceID<<",X="<<v.X<<",Y="<<v.Y<<",Floor="<<v.Floor<<",MapMark="<<v.MapMark<<",Time="<<v.time<<endl;
	}
	return info;
}
//查询所有已有的设备ID
int selectDevices(DBTraceAPI&DBAPI){
	int info;
	vector<string> rec;
	ptime tick,now;
	time_duration diff;
	tick=microsec_clock::local_time();  
	info=DBAPI.DBSearchDeviceID(rec);
	now=microsec_clock::local_time();
	diff=now-tick;	
	cout<<"use "<<diff.total_milliseconds()<<" ms"<<endl;
	for(auto &v:rec){
		cout<<"DeviceID="<<v<<endl;
	}
	return info;
}
//统计标识（PersonID+Time+MapMark）
int mapCount(DBTraceAPI&DBAPI){
	int info;
	int PersonID=102;
	int PersonModule=1;
	int MapMark=2;
	ptime timeBegin=time_from_string("2020-04-26 09:53:00");
	ptime timeEnd=time_from_string("2020-05-26 10:53:00");
	DBMapData MapData;
	ptime tick,now;
	time_duration diff;
	tick=microsec_clock::local_time();  
	info=DBAPI.DBMapCount(PersonID,PersonModule,MapMark,timeBegin,timeEnd,MapData);
	now=microsec_clock::local_time();
	diff=now-tick;	
	cout<<"use "<<diff.total_milliseconds()<<" ms"<<endl;
	cout<<"PersinID="<<MapData.PersonID<<",PersonModule="<<MapData.PersonModule<<",MapMark="<<MapData.MapMark<<",EnterTimes="<<MapData.Enter<<",OutTimes="<<MapData.Out<<",StayTime="<<MapData.StayTime<<endl;
	return info;
}
//统计标识（PersonID+Time）
int mapPersonCount(DBTraceAPI&DBAPI){
	int info;
	int PersonID=101;
	int PersonModule=1;
	ptime timeBegin=time_from_string("2020-04-26 09:53:00");
	ptime timeEnd=time_from_string("2020-05-26 10:54:00");
	vector<DBMapData> MapData;
	ptime tick,now;
	time_duration diff;
	tick=microsec_clock::local_time();  
	info=DBAPI.DBMapPersonCount(PersonID,PersonModule,timeBegin,timeEnd,MapData);
	now=microsec_clock::local_time();
	diff=now-tick;	
	cout<<"use "<<diff.total_milliseconds()<<" ms"<<endl;
	for(auto &v:MapData){
		cout<<"PersinID="<<v.PersonID<<",PersonModule="<<v.PersonModule<<",MapMark="<<v.MapMark<<",EnterTimes="<<v.Enter<<",OutTimes="<<v.Out<<",StayTime="<<v.StayTime<<endl;
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
	ptime tick,now;
	time_duration diff;
	tick=microsec_clock::local_time();  
	info=DBAPI.DBMapMarkCount(MapMark,timeBegin,timeEnd,MapData);
	now=microsec_clock::local_time();
	diff=now-tick;	
	cout<<"use "<<diff.total_milliseconds()<<" ms"<<endl;
	for(auto &v:MapData){
		cout<<"PersinID="<<v.PersonID<<",PersonModule="<<v.PersonModule<<",MapMark="<<v.MapMark<<",EnterTimes="<<v.Enter<<",OutTimes="<<v.Out<<",StayTime="<<v.StayTime<<endl;
	}
	return info;
}
//删除单条轨迹
int deleteTrace(DBTraceAPI&DBAPI){
	int info;
	DBTrace trace;
	trace.TraceID=5;
	trace.time="2020-03-26 10:53:26";
	ptime tick,now;
	time_duration diff;
	tick=microsec_clock::local_time();  
	info=DBAPI.DBDeleteTrace(trace);
	now=microsec_clock::local_time();
	diff=now-tick;	
	cout<<"use "<<diff.total_milliseconds()<<" ms"<<endl;
	return info;
}
//删除单个设备
int deleteDevice(DBTraceAPI&DBAPI){
	int info;
	string DeviceID="D110";
	ptime tick,now;
	time_duration diff;
	tick=microsec_clock::local_time();  
	info=DBAPI.DBDeleteDevice(DeviceID);
	now=microsec_clock::local_time();
	diff=now-tick;	
	cout<<"use "<<diff.total_milliseconds()<<" ms"<<endl;
	return info;
}
//删除单个围栏
int deleteMap(DBTraceAPI&DBAPI){
	int info;
	int MapMark=3;
	ptime tick,now;
	time_duration diff;
	tick=microsec_clock::local_time();  
	info=DBAPI.DBDeleteMap(MapMark);
	now=microsec_clock::local_time();
	diff=now-tick;	
	cout<<"use "<<diff.total_milliseconds()<<" ms"<<endl;
	return info;
}
//更新轨迹
int updateTrace(DBTraceAPI&DBAPI){
	int info;
	DBTrace traceOld;
	DBTrace traceNew;
	traceOld.getvalue(4,102,1,"D102",4,4,"2F",2,"2020-02-26 10:53:26");
	traceNew.getvalue(4,101,1,"D101",4,4,"2F",2,"2020-02-26 10:53:26");
	ptime tick,now;
	time_duration diff;
	tick=microsec_clock::local_time();  
	info=DBAPI.DBUpdateTrace(traceOld,traceNew);
	now=microsec_clock::local_time();
	diff=now-tick;	
	cout<<"use "<<diff.total_milliseconds()<<" ms"<<endl;
	return info;
}
int clearTable(DBTraceAPI&DBAPI){
	int info;
	ptime tick,now;
	time_duration diff;
	tick=microsec_clock::local_time();  
	info=DBAPI.DBClearTable();
	now=microsec_clock::local_time();
	diff=now-tick;	
	cout<<"use "<<diff.total_milliseconds()<<" ms"<<endl;
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
	ptime tick,now;
	time_duration diff;
	tick=microsec_clock::local_time();  
	info=DBAPI.DBAddTrace(trace);
	now=microsec_clock::local_time();
	diff=now-tick;	
	cout<<"use "<<diff.total_milliseconds()<<" ms"<<endl;
	return info;
}
int addcrossSomeTracetest2(DBTraceAPI&DBAPI){
	int info;
	vector<DBTrace> trace;
	DBTrace temp;
	temp.getvalue(102,1,"D102",2,2,"2F",2,"2020-02-29 10:20:00");
	trace.push_back(temp);
	temp.getvalue(102,1,"D102",2,2,"2F",2,"2020-04-30 10:20:00");
	trace.push_back(temp);
	temp.getvalue(102,1,"D102",2,2,"2F",2,"2020-04-30 10:25:00");
	trace.push_back(temp);
	temp.getvalue(102,1,"D102",1,1,"1F",1,"2020-04-30 10:30:00");
	trace.push_back(temp);
	temp.getvalue(102,1,"D102",1,1,"1F",1,"2020-04-30 10:33:00");
	trace.push_back(temp);
	temp.getvalue(102,1,"D102",2,2,"2F",2,"2020-04-30 10:45:00");
	trace.push_back(temp);
	temp.getvalue(102,1,"D102",2,2,"2F",2,"2020-04-30 11:00:00");
	trace.push_back(temp);
	temp.getvalue(102,1,"D102",2,2,"2F",2,"2020-04-30 23:50:00");
	trace.push_back(temp);
	temp.getvalue(102,1,"D102",1,1,"1F",1,"2020-04-30 23:55:00");
	trace.push_back(temp);
	temp.getvalue(102,1,"D102",1,1,"1F",1,"2020-05-01 00:05:00");
	trace.push_back(temp);
	temp.getvalue(102,1,"D102",2,2,"2F",2,"2020-05-01 00:10:00");
	trace.push_back(temp);
	ptime tick,now;
	time_duration diff;
	tick=microsec_clock::local_time();  
	info=DBAPI.DBAddTrace(trace);
	now=microsec_clock::local_time();
	diff=now-tick;	
	cout<<"use "<<diff.total_milliseconds()<<" ms"<<endl;
	return info;
}
//查询地图频次
int countMapMark(DBTraceAPI&DBAPI){
	int info;
	int MapMark=2;
	ptime timeBegin=time_from_string("2020-04-26 09:53:00");
	ptime timeEnd=time_from_string("2020-05-26 10:54:00");
	DBMapData MapData;
	ptime tick,now;
	time_duration diff;
	tick=microsec_clock::local_time();  
	info=DBAPI.MapMarkCount(MapMark,timeBegin,timeEnd,MapData);
	now=microsec_clock::local_time();
	diff=now-tick;	
	cout<<"use "<<diff.total_milliseconds()<<" ms"<<endl;
	cout<<"MapMark="<<MapData.MapMark<<",Frequency="<<MapData.rate<<",StayTime="<<MapData.StayTime<<endl;
	return info;
}

int addTracestest(DBTraceAPI&DBAPI){
	int info;
	vector<DBTrace> trace;
	DBTrace temp;
	ptime time;
	string ti;
	time_duration onesecond=time_from_string("2020-05-26 10:54:01")-time_from_string("2020-05-26 10:54:00");
	time=second_clock::local_time();
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(102,1,"D102",-415,-766,"3F",2,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(102,1,"D102",-415,-780,"3F",2,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(102,1,"D102",-415,-800,"3F",2,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(102,1,"D102",-415,-830,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(102,1,"D102",-415,-870,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(102,1,"D102",-415,-920,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(102,1,"D102",-415,-970,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(102,1,"D102",-415,-1020,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(102,1,"D102",-515,-1020,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(102,1,"D102",-615,-1020,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(102,1,"D102",-715,-1020,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(102,1,"D102",-815,-1020,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(102,1,"D102",-915,-1020,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(102,1,"D102",-930,-1020,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(102,1,"D102",-945,-1020,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(102,1,"D102",-960,-1020,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(102,1,"D102",-975,-1020,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(102,1,"D102",-990,-1020,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(102,1,"D102",-1005,-1020,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(102,1,"D102",-1020,-1020,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(102,1,"D102",-1035,-1020,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(102,1,"D102",-1050,-1020,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(102,1,"D102",-1065,-1020,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(102,1,"D102",-1080,-1020,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(102,1,"D102",-1095,-1020,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(102,1,"D102",-1095,-970,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(102,1,"D102",-1095,-920,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(102,1,"D102",-1095,-870,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(102,1,"D102",-1095,-825,"3F",3,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(102,1,"D102",-1095,-770,"3F",3,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(102,1,"D102",-1095,-720,"3F",3,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(102,1,"D102",-1095,-670,"3F",3,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(102,1,"D102",-1125,-670,"3F",3,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(102,1,"D102",-1155,-670,"3F",3,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(102,1,"D102",-1185,-670,"3F",3,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(102,1,"D102",-1215,-670,"3F",3,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(102,1,"D102",-1245,-670,"3F",3,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(102,1,"D102",-1275,-670,"3F",3,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(102,1,"D102",-1305,-670,"3F",3,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(102,1,"D102",-1335,-670,"3F",3,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(102,1,"D102",-1365,-670,"3F",3,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(102,1,"D102",-1395,-670,"3F",3,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(102,1,"D102",-1425,-670,"3F",3,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(102,1,"D102",-1425,-620,"3F",3,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(102,1,"D102",-1425,-570,"3F",3,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(102,1,"D102",-1425,-520,"3F",3,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(102,1,"D102",-1425,-470,"3F",3,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(102,1,"D102",-1425,-420,"3F",3,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(102,1,"D102",-1425,-370,"3F",3,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(102,1,"D102",-1400,-370,"3F",3,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(102,1,"D102",-1375,-370,"3F",3,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(102,1,"D102",-1350,-370,"3F",3,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(102,1,"D102",-1300,-370,"3F",3,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(102,1,"D102",-1250,-370,"3F",3,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(102,1,"D102",-1200,-370,"3F",3,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(102,1,"D102",-1150,-370,"3F",3,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(102,1,"D102",-1100,-370,"3F",3,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(102,1,"D102",-1050,-370,"3F",3,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(102,1,"D102",-1000,-370,"3F",3,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(102,1,"D102",-950,-370,"3F",3,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(102,1,"D102",-900,-370,"3F",2,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(102,1,"D102",-850,-370,"3F",2,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(102,1,"D102",-800,-370,"3F",2,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(102,1,"D102",-750,-370,"3F",2,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(102,1,"D102",-750,-420,"3F",2,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(102,1,"D102",-750,-470,"3F",2,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(102,1,"D102",-750,-520,"3F",2,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(102,1,"D102",-750,-570,"3F",2,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(102,1,"D102",-750,-620,"3F",2,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(102,1,"D102",-750,-670,"3F",2,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(102,1,"D102",-750,-720,"3F",2,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(102,1,"D102",-700,-720,"3F",2,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(102,1,"D102",-650,-720,"3F",2,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(102,1,"D102",-600,-720,"3F",2,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(102,1,"D102",-550,-720,"3F",2,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(102,1,"D102",-500,-720,"3F",2,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(102,1,"D102",-450,-720,"3F",2,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(102,1,"D102",-400,-720,"3F",2,ti);
	trace.push_back(temp);
	ptime tick,now;
	time_duration diff;
	tick=microsec_clock::local_time();  
	info=DBAPI.DBAddTrace(trace);
	now=microsec_clock::local_time();
	diff=now-tick;	
	cout<<"use "<<diff.total_milliseconds()<<" ms"<<endl;
	return info;
}
int addTracestest2(DBTraceAPI&DBAPI){
	int info;
	vector<DBTrace> trace;
	DBTrace temp;
	ptime time;
	string ti;
	time_duration onesecond=time_from_string("2020-05-26 10:54:01")-time_from_string("2020-05-26 10:54:00");
	time=second_clock::local_time();
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-420,-750,"3F",2,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-420,-800,"3F",2,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-420,-850,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-420,-900,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-420,-950,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-420,-1000,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-420,-1050,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-420,-1100,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-470,-1100,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-520,-1100,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-570,-1100,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-620,-1100,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-670,-1100,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-720,-1100,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-770,-1100,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-820,-1100,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-870,-1100,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-920,-1100,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-970,-1100,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-1020,-1100,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-1070,-1100,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-1120,-1100,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-1170,-1100,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-1220,-1100,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-1270,-1100,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-1320,-1100,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-1370,-1100,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-1420,-1100,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-1470,-1100,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-1520,-1100,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-1570,-1100,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-1620,-1100,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-1620,-1150,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-1620,-1200,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-1620,-1250,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-1620,-1300,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-1620,-1350,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-1620,-1400,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-1620,-1450,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-1620,-1500,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-1620,-1550,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-1620,-1600,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-1620,-1650,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-1620,-1700,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-1620,-1750,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-1620,-1800,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-1620,-1850,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-1520,-1850,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-1420,-1850,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-1320,-1850,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-1220,-1850,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-1120,-1850,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-1020,-1850,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-920,-1850,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-820,-1850,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-720,-1850,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-620,-1850,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-520,-1850,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-420,-1850,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-320,-1850,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-220,-1850,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-120,-1850,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-20,-1850,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",80,-1850,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",80,-1800,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",80,-1750,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",80,-1700,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",80,-1650,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",80,-1600,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",80,-1550,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",80,-1500,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",80,-1450,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",80,-1400,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",80,-1350,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",80,-1300,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",80,-1250,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",80,-1200,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",80,-1150,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-20,-1150,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-120,-1150,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-220,-1150,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-320,-1150,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-420,-1150,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-420,-1200,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-420,-1250,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-420,-1300,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-420,-1350,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-420,-1400,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-420,-1450,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-420,-1500,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-420,-1550,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-420,-1600,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-420,-1650,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-420,-1700,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-420,-1750,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-420,-1800,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-420,-1850,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-520,-1850,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-620,-1850,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-720,-1850,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-820,-1850,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-820,-1800,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-820,-1750,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-820,-1700,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-820,-1650,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-820,-1600,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-820,-1550,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-820,-1500,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-820,-1450,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-820,-1400,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-820,-1350,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-820,-1300,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-820,-1250,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-820,-1200,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-820,-1150,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-920,-1150,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-1020,-1150,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-1120,-1150,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-1220,-1150,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-1220,-1200,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-1220,-1250,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-1220,-1300,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-1220,-1350,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-1220,-1400,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-1220,-1450,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-1220,-1500,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-1220,-1550,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-1220,-1600,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-1220,-1650,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-1220,-1700,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-1220,-1750,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-1220,-1800,"3F",1,ti);
	trace.push_back(temp);
	time=time+onesecond;
	ti=ptime_to_string(time);
	temp.getvalue(101,1,"D101",-1220,-1850,"3F",1,ti);
	trace.push_back(temp);

	ptime tick,now;
	time_duration diff;
	tick=microsec_clock::local_time();  
	info=DBAPI.DBAddTrace(trace);
	now=microsec_clock::local_time();
	diff=now-tick;	
	cout<<"use "<<diff.total_milliseconds()<<" ms"<<endl;
	return info;
}
//查询时间区间内的轨迹（人员ID+时间区间）
int selectPersonTracetest2(DBTraceAPI&DBAPI){
	int info;
	vector<DBTrace> rec;
	ptime timeBegin=time_from_string("2020-03-09 9:00:00");
	ptime timeEnd=time_from_string("2020-03-09 24:00:00");
	int PersonID=101;
	int PersonModule=1;
	ptime tick,now;
	time_duration diff;
	tick=microsec_clock::local_time();  
	info=DBAPI.DBSearchPersonTrace(PersonID,PersonModule=1,timeBegin,timeEnd,rec);
	now=microsec_clock::local_time();
	diff=now-tick;	
	cout<<"use "<<diff.total_milliseconds()<<" ms"<<endl;
	for(auto &v:rec){
		cout<<"TraceID="<<v.TraceID<<",PersonID="<<v.PersonID<<",PersonModule="<<v.PersonModule<<",DeviceID="<<v.DeviceID<<",X="<<v.X<<",Y="<<v.Y<<",Floor="<<v.Floor<<",MapMark="<<v.MapMark<<",Time="<<v.time<<endl;
	}
	return info;
}
//查询时间区间内的轨迹（设备ID+时间区间）
int selectDeviceTracetest2(DBTraceAPI&DBAPI){
	int info;
	vector<DBTrace> rec;
	ptime timeBegin=time_from_string("2020-03-09 9:00:00");
	ptime timeEnd=time_from_string("2020-03-09 24:00:00");
	string DeviceID="D102";
	ptime tick,now;
	time_duration diff;
	tick=microsec_clock::local_time();  
	info=DBAPI.DBSearchDeviceTrace(DeviceID,timeBegin,timeEnd,rec);
	now=microsec_clock::local_time();
	diff=now-tick;	
	cout<<"use "<<diff.total_milliseconds()<<" ms"<<endl;
	for(auto &v:rec){
		cout<<"TraceID="<<v.TraceID<<",PersonID="<<v.PersonID<<",PersonModule="<<v.PersonModule<<",DeviceID="<<v.DeviceID<<",X="<<v.X<<",Y="<<v.Y<<",Floor="<<v.Floor<<",MapMark="<<v.MapMark<<",Time="<<v.time<<endl;
	}
	return info;
}
int countMap2(DBTraceAPI&DBAPI){
	int info;
	ptime timeBegin=time_from_string("2020-03-09 9:00:00");
	ptime timeEnd=time_from_string("2020-03-09 24:00:00");
	vector<DBMapData> MapData;
	ptime tick,now;
	time_duration diff;
	tick=microsec_clock::local_time();  
	info=DBAPI.MapCount(timeBegin,timeEnd,MapData);
	now=microsec_clock::local_time();
	diff=now-tick;	
	cout<<"use "<<diff.total_milliseconds()<<" ms"<<endl;
	for(auto &v:MapData){
		cout<<"MapMark="<<v.MapMark<<",Frequency="<<v.rate<<",StayTime="<<v.StayTime<<endl;
	}
	return info;
}


int countMap(DBTraceAPI&DBAPI){
	int info;
	ptime timeBegin=time_from_string("2020-04-26 09:53:00");
	ptime timeEnd=time_from_string("2020-05-26 10:54:00");
	vector<DBMapData> MapData;
	ptime tick,now;
	time_duration diff;
	tick=microsec_clock::local_time();  
	info=DBAPI.MapCount(timeBegin,timeEnd,MapData);
	now=microsec_clock::local_time();
	diff=now-tick;	
	cout<<"use "<<diff.total_milliseconds()<<" ms"<<endl;
	for(auto &v:MapData){
		cout<<"MapMark="<<v.MapMark<<",Frequency="<<v.rate<<",StayTime="<<v.StayTime<<endl;
	}
	return info;
}


int main(int argc,char const *argv[]){
    //接口类的调用
	DBTraceAPI DBAPI;

	//判断数据库服务状态
	assert(DB_RET_OK==DBAPI.DBInitialize());

	//数据库建立连接
	assert(DB_RET_OK==connectDBtest(DBAPI));
	
	//数据库创建
	//assert(DB_RET_OK==creatDBtest(DBAPI));

	//单条添加设备
	//assert(DB_RET_OK==addDeviceDBtest(DBAPI));

	//多条添加设备
	//assert(DB_RET_OK==addSomeDeviceDBtest(DBAPI));

	//单条更新设备人员关系
	//assert(DB_RET_OK==updateRelatedtest(DBAPI));

	//多条更新设备人员关系
	//assert(DB_RET_OK==updateSomeRelatedtest(DBAPI));

	//单条添加人员
	//assert(DB_RET_OK==addPersontest(DBAPI));

	//多条添加人员
	//assert(DB_RET_OK==addSomePersontest(DBAPI));

	//单条添加围栏
	//assert(DB_RET_OK==addMapMarktest(DBAPI));

	//多条添加围栏
	//assert(DB_RET_OK==addSomeMapMarktest(DBAPI));

	//单条添加BCON
	//assert(DB_RET_OK==addBCONtest(DBAPI));

	//多条添加BCON
	//assert(DB_RET_OK==addSomeBCONtest(DBAPI));

	//单条添加围栏和BCON对应关系
	//assert(DB_RET_OK==addMaptest(DBAPI));

	//多条添加围栏和BCON对应关系
	//assert(DB_RET_OK==addSomeMaptest(DBAPI));

	//单条添加轨迹信息
	//assert(DB_RET_OK==addTracetest(DBAPI));

	//多条添加轨迹信息
	//assert(DB_RET_OK==addSomeTracetest(DBAPI));

	//单条查询最近轨迹（按设备ID）
	//assert(DB_RET_OK==selectDevicetest(DBAPI));

	//多条查询最近轨迹（按设备ID）
	//assert(DB_RET_OK==selectSomeDevicetest(DBAPI));

	//单条查询最近轨迹（按人员ID）
	//assert(DB_RET_OK==selectPersontest(DBAPI));

	//多条查询最近轨迹（按人员ID）
	//assert(DB_RET_OK==selectSomePersontest(DBAPI));

	//查询所有最近轨迹（按设备ID）
	//assert(DB_RET_OK==selectAllDevicetest(DBAPI));

	//查询所有最近轨迹（按人员ID）
	//assert(DB_RET_OK==selectAllPersontest(DBAPI));

	//查询时间区间内的轨迹（人员ID+时间）
	//assert(DB_RET_OK==selectPersonTracetest(DBAPI));

	//查询时间区间内的轨迹（设备ID+时间）
	//assert(DB_RET_OK==selectDeviceTracetest(DBAPI));

	//查询所有已有设备ID
	//assert(DB_RET_OK==selectDevices(DBAPI));

	//统计标识（PersonID+Time+MapMark）
	//assert(DB_RET_OK==mapCount(DBAPI));

	//统计标识（PersonID+Time）
	//assert(DB_RET_OK==mapPersonCount(DBAPI));

	//统计标识（Time+MapMark）
	//assert(DB_RET_OK==mapMarkCount(DBAPI));

	//删除单条轨迹
	//assert(DB_RET_OK==deleteTrace(DBAPI));

	//删除单个设备
	//assert(DB_RET_OK==deleteDevice(DBAPI));

	//删除单个围栏
	//assert(DB_RET_OK==deleteMap(DBAPI));

	//更新单条轨迹
	//assert(DB_RET_OK==updateTrace(DBAPI));

	//清除所有轨迹数据
	//assert(DB_RET_OK==clearTable(DBAPI));

	//添加轨迹数据（跨表添加)
	//assert(DB_RET_OK==addcrossSomeTracetest2(DBAPI));

	//验证跨表查询
	//assert(DB_RET_OK==selectPersonTracetest(DBAPI));
	//assert(DB_RET_OK==selectDeviceTracetest(DBAPI));
	
	//跨表统计（有具体Person、MapMark和时间）
	//assert(DB_RET_OK==mapCount(DBAPI));
	//跨表统计（有具体MapMark和时间）统计分人返回
	//assert(DB_RET_OK==mapMarkCount(DBAPI));
	//跨表统计（有具体Person和时间）
	//assert(DB_RET_OK==mapPersonCount(DBAPI));
	//跨表统计（有具体MapMark和时间），统计不在分人返回只看区域
	//assert(DB_RET_OK==countMapMark(DBAPI));
	//跨表统计，返回所有区域的统计数据
	//assert(DB_RET_OK==countMap(DBAPI));
	//assert(DB_RET_OK==addTracestest(DBAPI));
	//assert(DB_RET_OK==addTracestest2(DBAPI));
	//for(int i=0;i<500;i++){
		assert(DB_RET_OK==addTracestest(DBAPI));
		assert(DB_RET_OK==addTracestest2(DBAPI));
	//}

	//assert(DB_RET_OK==selectPersonTracetest2(DBAPI));
	//assert(DB_RET_OK==selectDeviceTracetest2(DBAPI));
	//assert(DB_RET_OK==countMap2(DBAPI));
	//assert(DB_RET_OK==deleteDBtest(DBAPI));
	
	return 0;
}


