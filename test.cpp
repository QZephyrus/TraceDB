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

	ptime time = time_from_string("1981-08-20 08:05:00");
	ptime now=second_clock::local_time();
	
	cout <<time.date().month()<<endl;
  	// ptime to string.
	string str_time = to_iso_extended_string(time);
	str_time=str_time.replace(str_time.find("T"),1," ");
  	cout << str_time << endl;
	return 0;
}