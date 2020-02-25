
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

int main(int argc,char const *argv[]){
    //接口类的调用
	DBTraceAPI DBAPI;
	int info;
	//建立数据库连接测试
	info=DBAPI.DBConnect();
	cout<<info<<endl;
	//创建数据库测试
	//info=DBAPI.DBCreateDB();
	//cout<<info<<endl;
	
	//单条设备输入验证
	/*
	DBDeviceData temp1;
	temp.DeviceID="D101";
	temp.PersonID=101;
	temp.PersonModule=1;
	info=DBAPI.DBAddDevice(temp);
	cout<<info<<endl;
	DBDeviceData temp2;
	temp.DeviceID="D102";
	info=DBAPI.DBAddDevice(temp);
	cout<<info<<endl;
	*/
	//多条模拟设备数据
	
	//在单个输入时若Person和PersonModule为空可以直接不用填写系统默认为0，当多条输入这两个值为空时则需要手动赋值为0
	/*
	vector<DBDeviceData> deviceData;	
	for(int i=1;i<=5;i++){
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
	cout<<info<<endl;
	*/

	//设备人员关系表更新测试（人员与设备绑定关系改变）
	//单条改变
	/*
	DBDeviceData temp1;
	temp1.DeviceID="D101";
	info=DBAPI.DBUpdateDeviceRelat(temp1);
	cout<<info<<endl;
	DBDeviceData temp2;
	temp2.DeviceID="D106";
	temp2.PersonID=106;
	temp2.PersonModule=1;
	info=DBAPI.DBUpdateDeviceRelat(temp2);
	cout<<info<<endl;
	*/
	//多条测试
	/*
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
	cout<<info<<endl;
	*/

	//测试增加人员
	//单条增加
	/*
	DBDeviceData temp;
	temp.PersonID=101;
	temp.PersonModule=1;
	info=DBAPI.DBAddPerson(temp);
	cout<<info<<endl;
	*/
	//批量增加
	/*
	vector<DBDeviceData> deviceData;	
	for(int i=2;i<=10;i++){
		DBDeviceData temp1;
		temp1.PersonID=100+i;
		temp1.PersonModule=1;
		deviceData.push_back(temp1);
	}
	info=DBAPI.DBAddSomePerson(deviceData);
	cout<<info<<endl;
	*/

	//添加围栏信息
	//添加单条围栏信息
	/*
	int tempMapMark=1;
	info=DBAPI.DBAddMapMark(tempMapMark);
	cout<<info<<endl;
	*/
	//添加多条围栏信息
	/*
	vector<int> mapmark;
	mapmark.push_back(2);
	mapmark.push_back(3);
	info=DBAPI.DBAddSomeMapMark(mapmark);
	cout<<info<<endl;
	*/

	//添加BCON信息测试
	//单条添加
	/*
	BCON bcon;
	bcon.BCONID=1;
	bcon.BCONX=1;
	bcon.BCONY=1;
	bcon.Floor="1F";
	info=DBAPI.DBAddBCON(bcon);
	cout<<info<<endl;
	*/
	//多条添加
	/*
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
	cout<<info<<endl;
	*/

	//添加BCON和MapMark关系表
	//单条添加
	/*
	Map map;
	map.MapMark=1;
	map.BCONID=1;
	info=DBAPI.DBAddMap(map);
	cout<<info<<endl;
	*/
	//多条添加
	///*
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
	cout<<info<<endl;
	//*/

	//删除数据库测试
	//info=DBAPI.DBDeleteDB();
	//cout<<info<<endl;

	

	return 0;
}