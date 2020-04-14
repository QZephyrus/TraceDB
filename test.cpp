#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/random.hpp>
#include <iostream>
#include <string>
#include "db/DBStruct.h"
#include "db/DBTraceAPI.h"
#include "db/DataBase.h"
#define BOOST_DATE_TIME_SOURCE
using namespace boost::posix_time;
using namespace boost::gregorian;
using namespace std;
using namespace boost;
using namespace boost::random;

void creatTrace(double &X, double &Y, double XStep, double YStep, int num, vector<DBTrace> &trace, int PersonID,
                int PersonModule, string DeviceID, string floor, int MapMark) {
    mt19937 gen;
    uniform_int<> dist(-5, 5);
    // uniform_real_distribution<double> dist(-5.0, 5.0);
    variate_generator<mt19937 &, uniform_int<>> die(gen, dist);
    DBTrace tempTrace;
    ptime time = second_clock::local_time();
    time_duration twosecond = seconds(2);
    for (int i = 0; i < num; i++) {
        X = X + XStep + die();
        Y = Y + YStep + die();
        // X=X+XStep;
        // Y=Y+YStep;
        time = time + twosecond;
        tempTrace.setValue(PersonID, PersonModule, DeviceID, X, Y, floor, MapMark, ptime_to_string(time));
        trace.push_back(tempTrace);
    }
}

//连接数据库测试方法
int connectDBtest(DBTraceAPI &DBAPI) {
    int info;
    ptime tick, now;
    time_duration diff;
    tick = microsec_clock::local_time();
    info = DBAPI.DBConnect();
    now = microsec_clock::local_time();
    diff = now - tick;
    cout << "database connect use " << diff.total_milliseconds() << " ms" << endl;
    return info;
}
//创建数据库测试方法
int creatDBtest(DBTraceAPI &DBAPI) {
    int info;
    ptime tick, now;
    time_duration diff;
    tick = microsec_clock::local_time();
    info = DBAPI.DBCreateDB();
    now = microsec_clock::local_time();
    diff = now - tick;
    cout << "Create Database use " << diff.total_milliseconds() << " ms" << endl;
    return info;
}
//预构建轨迹表（1年）
int creatTraceTable(DBTraceAPI &DBAPI) {
    int year = 2020;
    int month = 3;
    //构建2020年轨迹表，每3个月存一张表
    int info = DBAPI.DBCreatYearTraceTable(year, month);
    return info;
}
//单条设备输入验证
int addDeviceDBtest(DBTraceAPI &DBAPI) {
    int info;
    DBDeviceData temp;
    temp.setValue(101, 1, "D101");
    // temp.DeviceID="D101";
    // temp.PersonID=101;
    // temp.PersonModule=1;
    ptime tick, now;
    time_duration diff;
    tick = microsec_clock::local_time();
    info = DBAPI.DBAddDevice(temp);
    now = microsec_clock::local_time();
    diff = now - tick;
    cout << "insert one device use " << diff.total_milliseconds() << " ms" << endl;
    return info;
}
//多条设备输入验证
int addSomeDeviceDBtest(DBTraceAPI &DBAPI) {
    int info;
    vector<DBDeviceData> deviceData;
    for (int i = 2; i <= 5; i++) {
        DBDeviceData temp1;
        temp1.setValue(100 + i, 1, "D" + to_string(100 + i));
        // temp1.PersonID=100+i;
        // temp1.DeviceID="D"+to_string(100+i);
        // temp1.PersonModule=1;
        deviceData.push_back(temp1);
    }
    for (int i = 1; i <= 5; i++) {
        DBDeviceData temp2;
        temp2.setValue(0, 0, "D" + to_string(105 + i));
        // temp2.DeviceID="D"+to_string(105+i);
        // temp2.PersonID=0;
        // temp2.PersonModule=0;
        deviceData.push_back(temp2);
    }
    ptime tick, now;
    time_duration diff;
    tick = microsec_clock::local_time();
    info = DBAPI.DBAddDevice(deviceData);
    now = microsec_clock::local_time();
    diff = now - tick;
    cout << "insert 9 devices use " << diff.total_milliseconds() << " ms" << endl;
    return info;
}
//单条设备人员关系表更新测试
int updateRelatedtest(DBTraceAPI &DBAPI) {
    int info;
    DBDeviceData temp1;
    temp1.setValue(0, 0, "D120");

    ptime tick, now;
    time_duration diff;
    tick = microsec_clock::local_time();
    info = DBAPI.DBUpdateDeviceRelat(temp1);
    now = microsec_clock::local_time();
    diff = now - tick;
    cout << "update one Device use " << diff.total_milliseconds() << " ms" << endl;
    cout << info << endl;
    DBDeviceData temp2;
    temp2.setValue(121, 1, "D121");
    // temp2.DeviceID="D106";
    // temp2.PersonID=106;
    // temp2.PersonModule=1;
    tick = microsec_clock::local_time();
    info = DBAPI.DBUpdateDeviceRelat(temp2);
    now = microsec_clock::local_time();
    diff = now - tick;
    cout << "update one Device use " << diff.total_milliseconds() << " ms" << endl;
    return info;
}
//多条设备人员关系表更新测试
int updateSomeRelatedtest(DBTraceAPI &DBAPI) {
    int info;
    vector<DBDeviceData> deviceData;
    DBDeviceData temp(101, 1, "D101");
    // temp.DeviceID="D101";
    // temp.PersonID=101;
    // temp.PersonModule=1;
    deviceData.push_back(temp);
    for (int i = 2; i <= 6; i++) {
        DBDeviceData temp(0, 0, "D" + to_string(100 + i));
        // temp.DeviceID="D"+to_string(100+i);
        // temp.PersonID=0;
        // temp.PersonModule=0;
        deviceData.push_back(temp);
    }
    for (int i = 2; i <= 5; i++) {
        DBDeviceData temp(105 + i, 1, "D" + to_string(105 + i));
        // temp.DeviceID="D"+to_string(105+i);
        // temp.PersonID=105+i;
        // temp.PersonModule=1;
        deviceData.push_back(temp);
    }
    for (int i = 2; i <= 5; i++) {
        DBDeviceData temp(120 + i, 1, "D" + to_string(120 + i));
        deviceData.push_back(temp);
    }

    ptime tick, now;
    time_duration diff;
    tick = microsec_clock::local_time();
    info = DBAPI.DBUpdateDeviceRelat(deviceData);
    now = microsec_clock::local_time();
    diff = now - tick;
    cout << "update some Device use " << diff.total_milliseconds() << " ms" << endl;
    return info;
}
//单条增加人员测试方法
int addPersontest(DBTraceAPI &DBAPI) {
    int info;
    DBDeviceData temp(101, 1);
    // temp.PersonID=101;
    // temp.PersonModule=1;
    ptime tick, now;
    time_duration diff;
    tick = microsec_clock::local_time();
    info = DBAPI.DBAddPerson(temp);
    now = microsec_clock::local_time();
    diff = now - tick;
    cout << "add one Person use " << diff.total_milliseconds() << " ms" << endl;
    return info;
}
//多条增加人员测试方法
int addSomePersontest(DBTraceAPI &DBAPI) {
    int info;
    vector<DBDeviceData> deviceData;
    for (int i = 2; i <= 10; i++) {
        DBDeviceData temp1(100 + i, 1);
        // temp1.PersonID=100+i;
        // temp1.PersonModule=1;
        deviceData.push_back(temp1);
    }
    ptime tick, now;
    time_duration diff;
    tick = microsec_clock::local_time();
    info = DBAPI.DBAddPerson(deviceData);
    now = microsec_clock::local_time();
    diff = now - tick;
    cout << "add some Person use " << diff.total_milliseconds() << " ms" << endl;
    return info;
}
//单条添加围栏信息测试方法
int addMapMarktest(DBTraceAPI &DBAPI) {
    int info;
    int tempMapMark = 1;
    ptime tick, now;
    time_duration diff;
    tick = microsec_clock::local_time();
    info = DBAPI.DBAddMapMark(tempMapMark);
    now = microsec_clock::local_time();
    diff = now - tick;
    cout << "add one MapMark use " << diff.total_milliseconds() << " ms" << endl;
    return info;
}
//多条添加围栏信息测试方法
int addSomeMapMarktest(DBTraceAPI &DBAPI) {
    int info;
    vector<int> mapmark;
    mapmark.push_back(2);
    mapmark.push_back(3);
    ptime tick, now;
    time_duration diff;
    tick = microsec_clock::local_time();
    info = DBAPI.DBAddMapMark(mapmark);
    now = microsec_clock::local_time();
    diff = now - tick;
    cout << "add some MapMark use " << diff.total_milliseconds() << " ms" << endl;
    return info;
}
//单条BCON信息测试方法
int addBCONtest(DBTraceAPI &DBAPI) {
    int info;
    BCON bcon("1", 1, 1, "1F");
    // bcon.BCONID=1;
    // bcon.BCONX=1;
    // bcon.BCONY=1;
    // bcon.Floor="1F";
    ptime tick, now;
    time_duration diff;
    tick = microsec_clock::local_time();
    info = DBAPI.DBAddBCON(bcon);
    now = microsec_clock::local_time();
    diff = now - tick;
    cout << "add one bcon use " << diff.total_milliseconds() << " ms" << endl;
    return info;
}
//多条添加BCON信息测试方法
int addSomeBCONtest(DBTraceAPI &DBAPI) {
    int info;
    vector<BCON> bcon;

    for (int i = 2; i <= 3; i++) {
        BCON tempbcon(to_string(i), 1, i, "1F");
        // tempbcon.BCONID=i;
        // tempbcon.BCONX=1;
        // tempbcon.BCONY=i;
        // tempbcon.Floor="1F";
        bcon.push_back(tempbcon);
    }
    for (int i = 4; i <= 7; i++) {
        BCON tempbcon(to_string(i), 2, i - 3, "2F");
        // tempbcon.BCONID=i;
        // tempbcon.BCONX=2;
        // tempbcon.BCONY=i-3;
        // tempbcon.Floor="2F";
        bcon.push_back(tempbcon);
    }
    for (int i = 8; i <= 10; i++) {
        BCON tempbcon(to_string(i), 3, i - 7, "3F");
        // tempbcon.BCONID=i;
        // tempbcon.BCONX=3;
        // tempbcon.BCONY=i-7;
        // tempbcon.Floor="3F";
        bcon.push_back(tempbcon);
    }
    ptime tick, now;
    time_duration diff;
    tick = microsec_clock::local_time();
    info = DBAPI.DBAddBCON(bcon);
    now = microsec_clock::local_time();
    diff = now - tick;
    cout << "add some bcon use " << diff.total_milliseconds() << " ms" << endl;
    return info;
}
//单条添加BCON和MapMark关系表测试方法
int addMaptest(DBTraceAPI &DBAPI) {
    int info;
    Map map(1, "1");
    // map.MapMark=1;
    // map.BCONID=1;
    ptime tick, now;
    time_duration diff;
    tick = microsec_clock::local_time();
    info = DBAPI.DBAddMap(map);
    now = microsec_clock::local_time();
    diff = now - tick;
    cout << "add one Map use " << diff.total_milliseconds() << " ms" << endl;
    return info;
}
//多条添加BCON和MapMark关系表测试方法
int addSomeMaptest(DBTraceAPI &DBAPI) {
    int info;
    vector<Map> map;
    for (int i = 2; i <= 3; i++) {
        Map tempmap(1, to_string(i));
        // tempmap.MapMark=1;
        // tempmap.BCONID=i;
        map.push_back(tempmap);
    }
    for (int i = 4; i <= 7; i++) {
        Map tempmap(2, to_string(i));
        // tempmap.MapMark=2;
        // tempmap.BCONID=i;
        map.push_back(tempmap);
    }
    for (int i = 8; i <= 10; i++) {
        Map tempmap(3, to_string(i));
        // tempmap.MapMark=3;
        // tempmap.BCONID=i;
        map.push_back(tempmap);
    }
    ptime tick, now;
    time_duration diff;
    tick = microsec_clock::local_time();
    info = DBAPI.DBAddMap(map);
    now = microsec_clock::local_time();
    diff = now - tick;
    cout << "add some Map use " << diff.total_milliseconds() << " ms" << endl;
    return info;
}
//批量BCON和围栏信息
int addMap_BCON(DBTraceAPI &DBAPI) {
    vector<BCON> bcon;
    vector<Map> map;
    Map temp;
    temp.setValue(10, "10");
    map.push_back(temp);
    temp.setValue(10, "20");
    map.push_back(temp);
    temp.setValue(10, "30");
    map.push_back(temp);
    temp.setValue(20, "40");
    map.push_back(temp);
    temp.setValue(20, "50");
    map.push_back(temp);
    temp.setValue(30, "60");
    map.push_back(temp);
    BCON temp_bcon;
    temp_bcon.setValue("10", 10, 10, "1F");
    bcon.push_back(temp_bcon);
    temp_bcon.setValue("20", 20, 20, "1F");
    bcon.push_back(temp_bcon);
    temp_bcon.setValue("30", 30, 30, "1F");
    bcon.push_back(temp_bcon);
    temp_bcon.setValue("40", 40, 40, "2F");
    bcon.push_back(temp_bcon);
    temp_bcon.setValue("50", 50, 50, "2F");
    bcon.push_back(temp_bcon);
    temp_bcon.setValue("60", 60, 60, "3F");
    bcon.push_back(temp_bcon);
    int info = DBAPI.DBAddAllMap(map, bcon);
    return info;
}
//单条添加轨迹测试方法
int addTracetest(DBTraceAPI &DBAPI) {
    DBTrace trace;
    int info;
    trace.setValue(103, 1, "D101", 1, 1.2F, "1F", 1, "2020-02-28 09:53:26");
    ptime tick, now;
    time_duration diff;
    tick = microsec_clock::local_time();
    info = DBAPI.DBAddTrace(trace);
    now = microsec_clock::local_time();
    diff = now - tick;
    cout << "add one trace use " << diff.total_milliseconds() << " ms" << endl;
    return info;
}
//多条添加轨迹测试方法
int addSomeTracetest(DBTraceAPI &DBAPI) {
    vector<DBTrace> trace;
    DBTrace temp;
    int info;
    ptime time;
    string ti;
    time_duration onesecond = seconds(1);
    time = second_clock::local_time();
    ti = ptime_to_string(time);
    temp.setValue(101, 1, "D101", 2, 2, "1F", 1, ti);
    trace.push_back(temp);
    time = time + onesecond;
    ti = ptime_to_string(time);
    temp.setValue(101, 1, "D101", 3, 3, "2F", 2, ti);
    trace.push_back(temp);
    time = time + onesecond;
    ti = ptime_to_string(time);
    temp.setValue(102, 1, "D102", 4, 4, "2F", 2, ti);
    trace.push_back(temp);
    time = time + onesecond;
    ti = ptime_to_string(time);
    temp.setValue(102, 1, "D102", 4, 4, "2F", 2, ti);
    trace.push_back(temp);
    time = time + onesecond;
    ti = ptime_to_string(time);
    ptime tick, now;
    time_duration diff;
    tick = microsec_clock::local_time();
    info = DBAPI.DBAddTrace(trace);
    now = microsec_clock::local_time();
    diff = now - tick;
    cout << "add some trace use " << diff.total_milliseconds() << " ms" << endl;
    return info;
}
//通过设备ID联系轨迹的Person数据并保存轨迹
int addTraceDevice(DBTraceAPI &DBAPI) {
    DBTrace trace;
    trace.setValue("D121", 1, 1.2, "1F", 1, "2020-04-28 09:53:26");
    ptime tick, now;
    time_duration diff;
    tick = microsec_clock::local_time();
    int info = DBAPI.DBAddTraceD(trace);
    now = microsec_clock::local_time();
    diff = now - tick;
    cout << "add one trace use " << diff.total_milliseconds() << " ms" << endl;
    cout << info << endl;
    trace.setValue("D120", 1, 1.2, "1F", 1, "2020-04-28 09:53:26");
    info = DBAPI.DBAddTraceD(trace);
    cout << info << endl;
    return info;
}
int addSomeTraceDevice(DBTraceAPI &DBAPI) {
    vector<DBTrace> trace;
    DBTrace temp;
    int info;
    ptime time;
    string ti;
    time_duration onesecond = seconds(1);
    time = second_clock::local_time();
    ti = ptime_to_string(time);
    temp.setValue("D121", 2, 2, "1F", 1, ti);
    trace.push_back(temp);
    time = time + onesecond;
    ti = ptime_to_string(time);
    temp.setValue("D121", 3, 3, "2F", 2, ti);
    trace.push_back(temp);
    time = time + onesecond;
    ti = ptime_to_string(time);
    temp.setValue("D120", 4, 4, "2F", 2, ti);
    trace.push_back(temp);
    time = time + onesecond;
    ti = ptime_to_string(time);
    temp.setValue("D120", 4, 4, "2F", 2, ti);
    trace.push_back(temp);
    time = time + onesecond;
    ti = ptime_to_string(time);
    ptime tick, now;
    time_duration diff;
    tick = microsec_clock::local_time();
    info = DBAPI.DBAddTraceD(trace);
    now = microsec_clock::local_time();
    diff = now - tick;
    cout << "add some trace use " << diff.total_milliseconds() << " ms" << endl;
    return info;
}

//删除数据库测试方法
int deleteDBtest(DBTraceAPI &DBAPI) {
    int info;
    ptime tick, now;
    time_duration diff;
    tick = microsec_clock::local_time();
    info = DBAPI.DBDeleteDB();
    now = microsec_clock::local_time();
    diff = now - tick;
    cout << "delete database use " << diff.total_milliseconds() << " ms" << endl;
    return info;
}
//单条查询最近轨迹（按设备ID）
int selectDevicetest(DBTraceAPI &DBAPI) {
    int info;
    DBTrace rec;
    string DeviceID = "D101";
    ptime tick, now;
    time_duration diff;
    tick = microsec_clock::local_time();
    info = DBAPI.DBSearchDevice(DeviceID, rec);
    now = microsec_clock::local_time();
    diff = now - tick;
    cout << "select recent trace by deviceID use " << diff.total_milliseconds() << " ms" << endl;
    cout << "TraceID=" << rec.TraceID << ",PersonID=" << rec.PersonID << ",PersonModule=" << rec.PersonModule
         << ",DeviceID=" << rec.DeviceID << ",X=" << rec.X << ",Y=" << rec.Y << ",Floor=" << rec.Floor
         << ",MapMark=" << rec.MapMark << ",Time=" << rec.time << endl;
    return info;
}
//多条查询最近轨迹（按设备ID）
int selectSomeDevicetest(DBTraceAPI &DBAPI) {
    int info;
    vector<DBTrace> rec;
    vector<string> DeviceID;
    string DeviceIDtemp = "D101";
    DeviceID.push_back(DeviceIDtemp);
    DeviceIDtemp = "D110";
    DeviceID.push_back(DeviceIDtemp);

    DeviceIDtemp = "D111";
    DeviceID.push_back(DeviceIDtemp);
    ptime tick, now;
    time_duration diff;
    tick = microsec_clock::local_time();
    info = DBAPI.DBSearchDevice(DeviceID, rec);
    now = microsec_clock::local_time();
    diff = now - tick;
    cout << "select recent trace by deviceID use " << diff.total_milliseconds() << " ms" << endl;
    for (auto &v : rec) {
        if (v.found == true) {
            cout << "TraceID=" << v.TraceID << ",PersonID=" << v.PersonID << ",PersonModule=" << v.PersonModule
                 << ",DeviceID=" << v.DeviceID << ",X=" << v.X << ",Y=" << v.Y << ",Floor=" << v.Floor
                 << ",MapMark=" << v.MapMark << ",Time=" << v.time << endl;
        } else {
            if (v.inTable == true) {
                cout << "DeviceID=" << v.DeviceID << " have no trace" << endl;
            } else {
                cout << "DeviceID=" << v.DeviceID << " is no exist" << endl;
            }
        }
    }
    return info;
}
//查询所有最近轨迹（按设备ID）
int selectAllDevicetest(DBTraceAPI &DBAPI) {
    int info;
    vector<DBTrace> rec;
    ptime tick, now;
    time_duration diff;
    tick = microsec_clock::local_time();
    info = DBAPI.DBSearchDevice(rec);
    now = microsec_clock::local_time();
    diff = now - tick;
    cout << "select all recent traces by deviceID use " << diff.total_milliseconds() << " ms" << endl;
    for (auto &v : rec) {
        if (v.found == true) {
            cout << "TraceID=" << v.TraceID << ",PersonID=" << v.PersonID << ",PersonModule=" << v.PersonModule
                 << ",DeviceID=" << v.DeviceID << ",X=" << v.X << ",Y=" << v.Y << ",Floor=" << v.Floor
                 << ",MapMark=" << v.MapMark << ",Time=" << v.time << endl;
        } else {
            cout << "DeviceID=" << v.DeviceID << " have no trace" << endl;
        }
    }

    return info;
}
//单条查询最近轨迹（按人员ID）
int selectPersontest(DBTraceAPI &DBAPI) {
    int info;
    DBTrace rec;
    int PersonID = 101;
    int PersonModule = 1;
    ptime tick, now;
    time_duration diff;
    tick = microsec_clock::local_time();
    info = DBAPI.DBSearchPerson(PersonID, PersonModule, rec);
    now = microsec_clock::local_time();
    diff = now - tick;
    cout << "select recent trace by personID and module use " << diff.total_milliseconds() << " ms" << endl;
    cout << "TraceID=" << rec.TraceID << ",PersonID=" << rec.PersonID << ",PersonModule=" << rec.PersonModule
         << ",DeviceID=" << rec.DeviceID << ",X=" << rec.X << ",Y=" << rec.Y << ",Floor=" << rec.Floor
         << ",MapMark=" << rec.MapMark << ",Time=" << rec.time << endl;
    return info;
}
//多条查询最近轨迹（按人员ID）
int selectSomePersontest(DBTraceAPI &DBAPI) {
    int info;
    vector<DBTrace> rec;
    vector<vector<int>> Person;
    vector<int> temp;
    temp.push_back(101);
    temp.push_back(1);
    Person.push_back(temp);
    temp.clear();
    temp.push_back(110);
    temp.push_back(1);
    Person.push_back(temp);
    temp.clear();
    temp.push_back(111);
    temp.push_back(1);
    Person.push_back(temp);
    temp.clear();
    /*
    for (int i = 1; i <= 3; i++) {
        vector<int> temp;
        int PersonID = 100 + i;
        int PersonModule = 1;
        temp.push_back(PersonID);
        temp.push_back(PersonModule);
        Person.push_back(temp);
    }
    */
    ptime tick, now;
    time_duration diff;
    tick = microsec_clock::local_time();
    info = DBAPI.DBSearchPerson(Person, rec);
    now = microsec_clock::local_time();
    diff = now - tick;
    cout << "select recent trace by personID and module use " << diff.total_milliseconds() << " ms" << endl;
    for (auto &v : rec) {
        if (v.found == true) {
            cout << "TraceID=" << v.TraceID << ",PersonID=" << v.PersonID << ",PersonModule=" << v.PersonModule
                 << ",DeviceID=" << v.DeviceID << ",X=" << v.X << ",Y=" << v.Y << ",Floor=" << v.Floor
                 << ",MapMark=" << v.MapMark << ",Time=" << v.time << endl;
        } else {
            if (v.inTable == true) {
                cout << "PersonID=" << v.PersonID << ",PersonModule=" << v.PersonModule << " have no trace" << endl;
            } else {
                cout << "PersonID=" << v.PersonID << ",PersonModule=" << v.PersonModule << " is no exist" << endl;
            }
        }
    }
    return info;
}
//查询所有最近轨迹（按人员ID）
int selectAllPersontest(DBTraceAPI &DBAPI) {
    int info;
    vector<DBTrace> rec;
    ptime tick, now;
    time_duration diff;
    tick = microsec_clock::local_time();
    info = DBAPI.DBSearchPerson(rec);
    now = microsec_clock::local_time();
    diff = now - tick;
    cout << "select all recent trace by personID and Module use " << diff.total_milliseconds() << " ms" << endl;
    for (auto &v : rec) {
        if (v.found == true) {
            cout << "TraceID=" << v.TraceID << ",PersonID=" << v.PersonID << ",PersonModule=" << v.PersonModule
                 << ",DeviceID=" << v.DeviceID << ",X=" << v.X << ",Y=" << v.Y << ",Floor=" << v.Floor
                 << ",MapMark=" << v.MapMark << ",Time=" << v.time << endl;
        } else {
            cout << "PersonID=" << v.PersonID << ",PersonModule=" << v.PersonModule << " have no trace" << endl;
        }
    }
    return info;
}
//查询时间区间内的轨迹（人员ID+时间区间）
int selectPersonTracetest(DBTraceAPI &DBAPI) {
    int info;
    vector<DBTrace> rec;
    ptime begin = time_from_string("2020-04-26 09:53:00");
    ptime end = time_from_string("2020-06-26 09:57:00");
    int PersonID = 101;
    int PersonModule = 1;
    ptime tick, now;
    time_duration diff;
    tick = microsec_clock::local_time();
    info = DBAPI.DBSearchPersonTrace(PersonID, PersonModule, begin, end, rec);
    now = microsec_clock::local_time();
    diff = now - tick;
    cout << "select traces by personID and Module and time use " << diff.total_milliseconds() << " ms" << endl;
    for (auto &v : rec) {
        cout << "TraceID=" << v.TraceID << ",PersonID=" << v.PersonID << ",PersonModule=" << v.PersonModule
             << ",DeviceID=" << v.DeviceID << ",X=" << v.X << ",Y=" << v.Y << ",Floor=" << v.Floor
             << ",MapMark=" << v.MapMark << ",Time=" << v.time << endl;
    }
    return info;
}
int selectPersonModule(DBTraceAPI &DBAPI) {
    int info;
    vector<DBTrace> rec;
    int module = 1;
    ptime tick, now;
    time_duration diff;
    tick = microsec_clock::local_time();
    info = DBAPI.DBSearchPersonM(module, rec);
    now = microsec_clock::local_time();
    diff = now - tick;
    cout << "select recent traces by Module use " << diff.total_milliseconds() << " ms" << endl;
    for (auto &v : rec) {
        cout << "TraceID=" << v.TraceID << ",PersonID=" << v.PersonID << ",PersonModule=" << v.PersonModule
             << ",DeviceID=" << v.DeviceID << ",X=" << v.X << ",Y=" << v.Y << ",Floor=" << v.Floor
             << ",MapMark=" << v.MapMark << ",Time=" << v.time << endl;
    }
    return info;
}
int selectPersonID(DBTraceAPI &DBAPI) {
    int info;
    vector<DBTrace> rec;
    vector<int> PersonID;
    int ID = 101;
    PersonID.push_back(ID);
    ID = 102;
    PersonID.push_back(ID);
    ptime tick, now;
    time_duration diff;
    tick = microsec_clock::local_time();
    info = DBAPI.DBSearchPersonP(PersonID, rec);
    now = microsec_clock::local_time();
    diff = now - tick;
    cout << "select recent traces by PersonID use " << diff.total_milliseconds() << " ms" << endl;
    for (auto &v : rec) {
        cout << "TraceID=" << v.TraceID << ",PersonID=" << v.PersonID << ",PersonModule=" << v.PersonModule
             << ",DeviceID=" << v.DeviceID << ",X=" << v.X << ",Y=" << v.Y << ",Floor=" << v.Floor
             << ",MapMark=" << v.MapMark << ",Time=" << v.time << endl;
    }
    return info;
}
//查询时间区间内的轨迹（设备ID+时间区间）
int selectDeviceTracetest(DBTraceAPI &DBAPI) {
    int info;
    vector<DBTrace> rec;
    ptime begin = time_from_string("2020-04-26 09:53:00");
    ptime end = time_from_string("2020-06-26 09:57:00");
    string DeviceID = "D101";
    ptime tick, now;
    time_duration diff;
    tick = microsec_clock::local_time();
    info = DBAPI.DBSearchDeviceTrace(DeviceID, begin, end, rec);
    now = microsec_clock::local_time();
    diff = now - tick;
    cout << "select traces by deviceID and time use " << diff.total_milliseconds() << " ms" << endl;
    for (auto &v : rec) {
        cout << "TraceID=" << v.TraceID << ",PersonID=" << v.PersonID << ",PersonModule=" << v.PersonModule
             << ",DeviceID=" << v.DeviceID << ",X=" << v.X << ",Y=" << v.Y << ",Floor=" << v.Floor
             << ",MapMark=" << v.MapMark << ",Time=" << v.time << endl;
    }
    return info;
}
//查询所有已有的设备ID
int selectDevices(DBTraceAPI &DBAPI) {
    int info;
    vector<string> rec;
    ptime tick, now;
    time_duration diff;
    tick = microsec_clock::local_time();
    info = DBAPI.DBSearchDeviceID(rec);
    now = microsec_clock::local_time();
    diff = now - tick;
    cout << "select all DeviceID use " << diff.total_milliseconds() << " ms" << endl;
    for (auto &v : rec) {
        cout << "DeviceID=" << v << endl;
    }
    return info;
}
//统计标识（PersonID+Time+MapMark）
int mapCount(DBTraceAPI &DBAPI) {
    int info;
    int PersonID = 102;
    int PersonModule = 1;
    int MapMark = 2;
    ptime timeBegin = time_from_string("2020-04-26 09:53:00");
    ptime timeEnd = time_from_string("2020-05-26 10:53:00");
    DBMapData MapData;
    ptime tick, now;
    time_duration diff;
    tick = microsec_clock::local_time();
    info = DBAPI.DBMapCount(PersonID, PersonModule, MapMark, timeBegin, timeEnd, MapData);
    now = microsec_clock::local_time();
    diff = now - tick;
    cout << "mapcount by personID and time and MapMark use " << diff.total_milliseconds() << " ms" << endl;
    cout << "PersinID=" << MapData.PersonID << ",PersonModule=" << MapData.PersonModule
         << ",MapMark=" << MapData.MapMark << ",EnterTimes=" << MapData.Enter << ",OutTimes=" << MapData.Out
         << ",StayTime=" << MapData.StayTime << endl;
    return info;
}
//统计标识（PersonID+Time）
int mapPersonCount(DBTraceAPI &DBAPI) {
    int info;
    int PersonID = 101;
    int PersonModule = 1;
    ptime timeBegin = time_from_string("2020-04-26 09:53:00");
    ptime timeEnd = time_from_string("2020-06-26 10:54:00");
    vector<DBMapData> MapData;
    ptime tick, now;
    time_duration diff;
    tick = microsec_clock::local_time();
    info = DBAPI.DBMapPersonCount(PersonID, PersonModule, timeBegin, timeEnd, MapData);
    now = microsec_clock::local_time();
    diff = now - tick;
    cout << "mapcount by personID and time use " << diff.total_milliseconds() << " ms" << endl;
    for (auto &v : MapData) {
        cout << "PersinID=" << v.PersonID << ",PersonModule=" << v.PersonModule << ",MapMark=" << v.MapMark
             << ",EnterTimes=" << v.Enter << ",OutTimes=" << v.Out << ",StayTime=" << v.StayTime << endl;
    }
    return info;
}
//统计标识（Time+MapMark）
int mapMarkCount(DBTraceAPI &DBAPI) {
    int info;
    int MapMark = 2;
    ptime timeBegin = time_from_string("2020-04-26 09:53:00");
    ptime timeEnd = time_from_string("2020-06-26 10:54:00");
    vector<DBMapData> MapData;
    ptime tick, now;
    time_duration diff;
    tick = microsec_clock::local_time();
    info = DBAPI.DBMapMarkCount(MapMark, timeBegin, timeEnd, MapData);
    now = microsec_clock::local_time();
    diff = now - tick;
    cout << "mapcount by time and MapMark use " << diff.total_milliseconds() << " ms" << endl;
    for (auto &v : MapData) {
        cout << "PersinID=" << v.PersonID << ",PersonModule=" << v.PersonModule << ",MapMark=" << v.MapMark
             << ",EnterTimes=" << v.Enter << ",OutTimes=" << v.Out << ",StayTime=" << v.StayTime << endl;
    }
    return info;
}
//删除单条轨迹
int deleteTrace(DBTraceAPI &DBAPI) {
    int info;
    DBTrace trace;
    trace.TraceID = 5;
    trace.time = "2020-05-31 10:25:00";
    ptime tick, now;
    time_duration diff;
    tick = microsec_clock::local_time();
    info = DBAPI.DBDeleteTrace(trace);
    now = microsec_clock::local_time();
    diff = now - tick;
    cout << "delete one trace use " << diff.total_milliseconds() << " ms" << endl;
    return info;
}
//删除单个设备
int deleteDevice(DBTraceAPI &DBAPI) {
    int info;
    string DeviceID = "D110";
    ptime tick, now;
    time_duration diff;
    tick = microsec_clock::local_time();
    info = DBAPI.DBDeleteDevice(DeviceID);
    now = microsec_clock::local_time();
    diff = now - tick;
    cout << "delete one device use " << diff.total_milliseconds() << " ms" << endl;
    return info;
}
//删除单个围栏
int deleteMap(DBTraceAPI &DBAPI) {
    int info;
    int MapMark = 3;
    ptime tick, now;
    time_duration diff;
    tick = microsec_clock::local_time();
    info = DBAPI.DBDeleteMap(MapMark);
    now = microsec_clock::local_time();
    diff = now - tick;
    cout << "delete one map use " << diff.total_milliseconds() << " ms" << endl;
    return info;
}
//更新轨迹
int updateTrace(DBTraceAPI &DBAPI) {
    int info;
    DBTrace traceOld;
    DBTrace traceNew;
    traceOld.setValue(4, 101, 1, "D101", 2, 2, "2F", 2, "2020-05-31 10:23:00");
    traceNew.setValue(4, 101, 1, "D101", 4, 4, "2F", 2, "2020-05-31 10:23:00");
    ptime tick, now;
    time_duration diff;
    tick = microsec_clock::local_time();
    info = DBAPI.DBUpdateTrace(traceOld, traceNew);
    now = microsec_clock::local_time();
    diff = now - tick;
    cout << "update one trace use " << diff.total_milliseconds() << " ms" << endl;
    return info;
}
int clearTable(DBTraceAPI &DBAPI) {
    int info;
    ptime tick, now;
    time_duration diff;
    tick = microsec_clock::local_time();
    info = DBAPI.DBClearTable();
    now = microsec_clock::local_time();
    diff = now - tick;
    cout << "delete all trace table use " << diff.total_milliseconds() << " ms" << endl;
    return info;
}
//多条跨表查询数据添加轨迹测试方法
int addcrossSomeTracetest(DBTraceAPI &DBAPI) {
    int info;
    vector<DBTrace> trace;
    DBTrace temp;
    temp.setValue(101, 1, "D101", 2, 2, "2F", 2, "2020-05-31 10:20:00");
    trace.push_back(temp);
    temp.setValue(101, 1, "D101", 2, 2, "2F", 2, "2020-05-31 10:23:00");
    trace.push_back(temp);
    temp.setValue(101, 1, "D101", 2, 2, "2F", 2, "2020-05-31 10:25:00");
    trace.push_back(temp);
    temp.setValue(101, 1, "D101", 1, 1, "1F", 1, "2020-05-31 10:30:00");
    trace.push_back(temp);
    temp.setValue(101, 1, "D101", 1, 1, "1F", 1, "2020-05-31 10:33:00");
    trace.push_back(temp);
    temp.setValue(101, 1, "D101", 2, 2, "2F", 2, "2020-05-31 10:45:00");
    trace.push_back(temp);
    temp.setValue(101, 1, "D101", 2, 2, "2F", 2, "2020-05-31 11:00:00");
    trace.push_back(temp);
    temp.setValue(101, 1, "D101", 2, 2, "2F", 2, "2020-05-31 23:50:00");
    trace.push_back(temp);
    temp.setValue(101, 1, "D101", 1, 1, "1F", 1, "2020-05-31 23:55:00");
    trace.push_back(temp);
    temp.setValue(101, 1, "D101", 1, 1, "1F", 1, "2020-06-01 00:05:00");
    trace.push_back(temp);
    temp.setValue(101, 1, "D101", 2, 2, "2F", 2, "2020-06-01 00:10:00");
    trace.push_back(temp);
    ptime tick, now;
    time_duration diff;
    tick = microsec_clock::local_time();
    info = DBAPI.DBAddTrace(trace);
    now = microsec_clock::local_time();
    diff = now - tick;
    cout << "add some traces use " << diff.total_milliseconds() << " ms" << endl;
    return info;
}
int addcrossSomeTracetest2(DBTraceAPI &DBAPI) {
    int info;
    vector<DBTrace> trace;
    DBTrace temp;
    temp.setValue(102, 1, "D102", 2, 2, "2F", 2, "2020-02-29 10:20:00");
    trace.push_back(temp);
    temp.setValue(102, 1, "D102", 2, 2, "2F", 2, "2020-04-30 10:20:00");
    trace.push_back(temp);
    temp.setValue(102, 1, "D102", 2, 2, "2F", 2, "2020-04-30 10:25:00");
    trace.push_back(temp);
    temp.setValue(102, 1, "D102", 1, 1, "1F", 1, "2020-04-30 10:30:00");
    trace.push_back(temp);
    temp.setValue(102, 1, "D102", 1, 1, "1F", 1, "2020-04-30 10:33:00");
    trace.push_back(temp);
    temp.setValue(102, 1, "D102", 2, 2, "2F", 2, "2020-04-30 10:45:00");
    trace.push_back(temp);
    temp.setValue(102, 1, "D102", 2, 2, "2F", 2, "2020-04-30 11:00:00");
    trace.push_back(temp);
    temp.setValue(102, 1, "D102", 2, 2, "2F", 2, "2020-04-30 23:50:00");
    trace.push_back(temp);
    temp.setValue(102, 1, "D102", 1, 1, "1F", 1, "2020-04-30 23:55:00");
    trace.push_back(temp);
    temp.setValue(102, 1, "D102", 1, 1, "1F", 1, "2020-05-01 00:05:00");
    trace.push_back(temp);
    temp.setValue(102, 1, "D102", 2, 2, "2F", 2, "2020-05-01 00:10:00");
    trace.push_back(temp);
    ptime tick, now;
    time_duration diff;
    tick = microsec_clock::local_time();
    info = DBAPI.DBAddTrace(trace);
    now = microsec_clock::local_time();
    diff = now - tick;
    cout << "add some traces use " << diff.total_milliseconds() << " ms" << endl;
    return info;
}
//查询地图频次
int countMapMark(DBTraceAPI &DBAPI) {
    int info;
    int MapMark = 2;
    ptime timeBegin = time_from_string("2020-04-26 09:53:00");
    ptime timeEnd = time_from_string("2020-05-26 10:54:00");
    DBMapData MapData;
    ptime tick, now;
    time_duration diff;
    tick = microsec_clock::local_time();
    info = DBAPI.MapMarkCount(MapMark, timeBegin, timeEnd, MapData);
    now = microsec_clock::local_time();
    diff = now - tick;
    cout << "map count by MapMark and time use " << diff.total_milliseconds() << " ms" << endl;
    cout << "MapMark=" << MapData.MapMark << ",Frequency=" << MapData.rate << ",StayTime=" << MapData.StayTime << endl;
    return info;
}

int addTracestest(DBTraceAPI &DBAPI) {
    int info;
    vector<DBTrace> trace;
    double X = -420;
    double Y = -700;
    creatTrace(X, Y, 0, -50, 2, trace, 101, 1, "D101", "3F", 2);
    creatTrace(X, Y, 0, -50, 6, trace, 101, 1, "D101", "3F", 1);
    creatTrace(X, Y, -50, 0, 24, trace, 101, 1, "D101", "3F", 1);
    creatTrace(X, Y, 0, -50, 15, trace, 101, 1, "D101", "3F", 1);
    creatTrace(X, Y, 100, 0, 17, trace, 101, 1, "D101", "3F", 1);
    creatTrace(X, Y, 0, 50, 14, trace, 101, 1, "D101", "3F", 1);
    creatTrace(X, Y, -100, 0, 5, trace, 101, 1, "D101", "3F", 1);
    creatTrace(X, Y, 0, -50, 14, trace, 101, 1, "D101", "3F", 1);
    creatTrace(X, Y, -100, 0, 4, trace, 101, 1, "D101", "3F", 1);
    creatTrace(X, Y, 0, 50, 14, trace, 101, 1, "D101", "3F", 1);
    creatTrace(X, Y, -100, 0, 4, trace, 101, 1, "D101", "3F", 1);
    creatTrace(X, Y, 0, -50, 14, trace, 101, 1, "D101", "3F", 1);
    ptime tick, now;
    time_duration diff;
    tick = microsec_clock::local_time();
    info = DBAPI.DBAddTrace(trace);
    now = microsec_clock::local_time();
    diff = now - tick;
    cout << "add some traces use " << diff.total_milliseconds() << " ms" << endl;
    return info;
}
int addTracestest2(DBTraceAPI &DBAPI) {
    int info;
    vector<DBTrace> trace;
    double X = -415;
    double Y = -740;
    creatTrace(X, Y, 0, -20, 3, trace, 101, 1, "D101", "3F", 2);
    creatTrace(X, Y, 0, -20, 5, trace, 101, 1, "D101", "3F", 1);
    creatTrace(X, Y, -100, 0, 17, trace, 101, 1, "D101", "3F", 1);
    creatTrace(X, Y, 0, 50, 3, trace, 101, 1, "D101", "3F", 1);
    creatTrace(X, Y, 0, 50, 4, trace, 101, 1, "D101", "3F", 3);
    creatTrace(X, Y, -30, 0, 11, trace, 101, 1, "D101", "3F", 3);
    creatTrace(X, Y, 0, -50, 6, trace, 101, 1, "D101", "3F", 3);
    creatTrace(X, Y, 20, 0, 11, trace, 101, 1, "D101", "3F", 3);
    creatTrace(X, Y, 20, 0, 4, trace, 101, 1, "D101", "3F", 2);
    creatTrace(X, Y, 0, -50, 7, trace, 101, 1, "D101", "3F", 2);
    creatTrace(X, Y, 50, 0, 7, trace, 101, 1, "D101", "3F", 2);

    ptime tick, now;
    time_duration diff;
    tick = microsec_clock::local_time();
    info = DBAPI.DBAddTrace(trace);
    now = microsec_clock::local_time();
    diff = now - tick;
    cout << "add some traces use " << diff.total_milliseconds() << " ms" << endl;
    return info;
}
//查询时间区间内的轨迹（人员ID+时间区间）
int selectPersonTracetest2(DBTraceAPI &DBAPI) {
    int info;
    vector<DBTrace> rec;
    ptime timeBegin = time_from_string("2020-03-04 9:00:00");
    ptime timeEnd = time_from_string("2020-04-30 24:00:00");
    int PersonID = 101;
    int PersonModule = 1;
    ptime tick, now;
    time_duration diff;
    tick = microsec_clock::local_time();
    info = DBAPI.DBSearchPersonTrace(PersonID, PersonModule, timeBegin, timeEnd, rec);
    now = microsec_clock::local_time();
    diff = now - tick;
    cout << "select traces by PersonID and Module and time use " << diff.total_milliseconds() << " ms" << endl;
    for (auto &v : rec) {
        cout << "TraceID=" << v.TraceID << ",PersonID=" << v.PersonID << ",PersonModule=" << v.PersonModule
             << ",DeviceID=" << v.DeviceID << ",X=" << v.X << ",Y=" << v.Y << ",Floor=" << v.Floor
             << ",MapMark=" << v.MapMark << ",Time=" << v.time << endl;
    }
    return info;
}
//查询时间区间内的轨迹（设备ID+时间区间）
int selectDeviceTracetest2(DBTraceAPI &DBAPI) {
    int info;
    vector<DBTrace> rec;
    ptime timeBegin = time_from_string("2020-03-04 9:00:00");
    ptime timeEnd = time_from_string("2020-04-30 24:00:00");
    string DeviceID = "D102";
    ptime tick, now;
    time_duration diff;
    tick = microsec_clock::local_time();
    info = DBAPI.DBSearchDeviceTrace(DeviceID, timeBegin, timeEnd, rec);
    now = microsec_clock::local_time();
    diff = now - tick;
    cout << "select traces by deviceID and time use " << diff.total_milliseconds() << " ms" << endl;
    for (auto &v : rec) {
        cout << "TraceID=" << v.TraceID << ",PersonID=" << v.PersonID << ",PersonModule=" << v.PersonModule
             << ",DeviceID=" << v.DeviceID << ",X=" << v.X << ",Y=" << v.Y << ",Floor=" << v.Floor
             << ",MapMark=" << v.MapMark << ",Time=" << v.time << endl;
    }
    return info;
}
int countMap2(DBTraceAPI &DBAPI) {
    int info;
    ptime timeBegin = time_from_string("2020-05-31 9:00:00");
    ptime timeEnd = time_from_string("2020-06-04 24:00:00");
    vector<DBMapData> MapData;
    ptime tick, now;
    time_duration diff;
    tick = microsec_clock::local_time();
    info = DBAPI.MapCount(timeBegin, timeEnd, MapData);
    now = microsec_clock::local_time();
    diff = now - tick;
    cout << "map count by time use " << diff.total_milliseconds() << " ms" << endl;
    for (auto &v : MapData) {
        cout << "MapMark=" << v.MapMark << ",Frequency=" << v.rate << ",StayTime=" << v.StayTime << endl;
    }
    return info;
}

int countMap(DBTraceAPI &DBAPI) {
    int info;
    ptime timeBegin = time_from_string("2020-03-04 09:53:00");
    ptime timeEnd = time_from_string("2020-05-26 10:54:00");
    vector<DBMapData> MapData;
    ptime tick, now;
    time_duration diff;
    tick = microsec_clock::local_time();
    info = DBAPI.MapCount(timeBegin, timeEnd, MapData);
    now = microsec_clock::local_time();
    diff = now - tick;
    cout << "map count by time use " << diff.total_milliseconds() << " ms" << endl;
    for (auto &v : MapData) {
        cout << "MapMark=" << v.MapMark << ",Frequency=" << v.rate << ",StayTime=" << v.StayTime << endl;
    }
    return info;
}

int main(int argc, char const *argv[]) {
    //接口类的调用
    DBTraceAPI DBAPI;

    //判断数据库服务状态
    assert(DB_RET_OK == DBAPI.DBInitialize());

    //数据库建立连接
    assert(DB_RET_OK == connectDBtest(DBAPI));

    //数据库创建
    assert(DB_RET_OK == creatDBtest(DBAPI));

    assert(DB_RET_OK == creatTraceTable(DBAPI));

    assert(DB_RET_OK == addMap_BCON(DBAPI));

    //单条添加设备
    assert(DB_RET_OK == addDeviceDBtest(DBAPI));

    //多条添加设备
    assert(DB_RET_OK == addSomeDeviceDBtest(DBAPI));

    //单条更新设备人员关系
    assert(DB_RET_OK == updateRelatedtest(DBAPI));

    //多条更新设备人员关系
    assert(DB_RET_OK == updateSomeRelatedtest(DBAPI));

    //单条添加人员
    assert(DB_RET_OK == addPersontest(DBAPI));

    //多条添加人员
    assert(DB_RET_OK == addSomePersontest(DBAPI));

    //单条添加围栏
    assert(DB_RET_OK == addMapMarktest(DBAPI));

    //多条添加围栏
    assert(DB_RET_OK == addSomeMapMarktest(DBAPI));

    //单条添加BCON
    assert(DB_RET_OK == addBCONtest(DBAPI));

    //多条添加BCON
    assert(DB_RET_OK == addSomeBCONtest(DBAPI));

    //单条添加围栏和BCON对应关系
    assert(DB_RET_OK == addMaptest(DBAPI));

    //多条添加围栏和BCON对应关系
    assert(DB_RET_OK == addSomeMaptest(DBAPI));

    //单条添加轨迹信息
    assert(DB_RET_OK == addTracetest(DBAPI));

    //多条添加轨迹信息
    assert(DB_RET_OK == addSomeTracetest(DBAPI));

    //添加轨迹数据（跨表添加)
    assert(DB_RET_OK == addcrossSomeTracetest2(DBAPI));

    assert(DB_RET_OK == addTracestest(DBAPI));
    assert(DB_RET_OK == addTracestest2(DBAPI));
    assert(DB_RET_OK == addcrossSomeTracetest(DBAPI));

    //查询所有已有设备ID
    assert(DB_RET_OK == selectDevices(DBAPI));

    //单条查询最近轨迹（按设备ID）
    // assert(DB_RET_OK == selectDevicetest(DBAPI));
    //多条查询最近轨迹（按设备ID）
    assert(DB_RET_OK == selectSomeDevicetest(DBAPI));

    //单条查询最近轨迹（按人员ID）
    // assert(DB_RET_OK == selectPersontest(DBAPI));

    //多条查询最近轨迹（按人员ID）
    assert(DB_RET_OK == selectSomePersontest(DBAPI));

    //查询所有最近轨迹（按设备ID）
    assert(DB_RET_OK == selectAllDevicetest(DBAPI));

    //查询所有最近轨迹（按人员ID）
    assert(DB_RET_OK == selectAllPersontest(DBAPI));

    //查询时间区间内的轨迹（人员ID+时间）
    assert(DB_RET_OK == selectPersonTracetest(DBAPI));

    //查询时间区间内的轨迹（设备ID+时间）
    assert(DB_RET_OK == selectDeviceTracetest(DBAPI));

    //更新单条轨迹
    assert(DB_RET_OK == updateTrace(DBAPI));

    //验证跨表查询
    assert(DB_RET_OK == selectPersonTracetest(DBAPI));
    assert(DB_RET_OK == selectDeviceTracetest(DBAPI));

    //跨表统计（有具体Person、MapMark和时间）
    assert(DB_RET_OK == mapCount(DBAPI));
    //跨表统计（有具体MapMark和时间）统计分人返回
    assert(DB_RET_OK == mapMarkCount(DBAPI));
    //跨表统计（有具体Person和时间）
    assert(DB_RET_OK == mapPersonCount(DBAPI));
    //跨表统计（有具体MapMark和时间），统计不在分人返回只看区域
    assert(DB_RET_OK == countMapMark(DBAPI));
    //跨表统计，返回所有区域的统计数据
    assert(DB_RET_OK == countMap(DBAPI));
    //按module返回最近轨迹
    assert(DB_RET_OK == selectPersonModule(DBAPI));
    //按ID返回最近轨迹
    assert(DB_RET_OK == selectPersonID(DBAPI));

    assert(DB_RET_OK == selectPersonTracetest2(DBAPI));
    assert(DB_RET_OK == selectDeviceTracetest2(DBAPI));

    //统计标识（PersonID+Time+MapMark）
    assert(DB_RET_OK == mapCount(DBAPI));

    //统计标识（PersonID+Time）
    assert(DB_RET_OK == mapPersonCount(DBAPI));

    //统计标识（Time+MapMark）
    assert(DB_RET_OK == mapMarkCount(DBAPI));

    //删除单条轨迹
    // assert(DB_RET_OK == deleteTrace(DBAPI));

    //删除单个设备
    // assert(DB_RET_OK == deleteDevice(DBAPI));

    //删除单个围栏
    // assert(DB_RET_OK == deleteMap(DBAPI));

    // assert(DB_RET_OK == countMap(DBAPI));

    //清除所有轨迹数据
    // assert(DB_RET_OK == clearTable(DBAPI));

    // assert(DB_RET_OK == deleteDBtest(DBAPI));

    return 0;
}
