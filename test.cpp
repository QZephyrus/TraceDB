//#include"DBTraceAPI.h"
//#include<vector>
#include<iostream>
#include<string>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#define BOOST_DATE_TIME_SOURCE
using namespace boost::posix_time;
using namespace boost::gregorian;
using namespace std;
using namespace boost;

int main(int argc,char const *argv[]){
    //ptime p(date(2020,02,20),hours(14));
	//cout<<p<<endl;
	//string s=to_simple_string(p);
	//cout<<s<<endl;

	enum color_set1 {RED, BLUE, WHITE, BLACK} color1;
	//string test=enum.GetName(typeof(color1),Colors.RED));

	ptime time1 = time_from_string("1981-08-20 08:05:00");
	ptime time2 = time_from_string("1981-08-21 08:05:45");
	ptime time3 = time_from_string("1981-08-22 08:05:00");
	time_duration time = time2-time1;
	time1=time1+time;
	//time=time+time3-time2;
	cout<<time.total_seconds()<<endl;
	cout<<time1<<endl;
	//cout <<time.date().month()<<endl;
  	// ptime to string.
	//string str_time = to_iso_extended_string(time);
	//str_time=str_time.replace(str_time.find("T"),1," ");
	//string time1="1998-01-28";
	//string t=time1.substr(0,4)+time1.substr(5,2);
  	//cout << str_time << endl;
	//out << t << endl;
	return 0;
}