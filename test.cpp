#include"DataBase.h"
#include<vector>
using namespace std;

int main(int argc,char const *argv[]){
    DataBase DB;
    DB.connect("localhost","root","zenos");
    DB.createDB("mydb");
    DB.useDB("mydb");
    DB.createTB("tst", "id int default 0, password varchar(255) default \"000000\"");
	//string tst="tst";
	//int a=12345;
	//string b="hshsh";
	//string value=to_string(a)+", \""+b+"\"";
	//DB.insertItem(tst,value);
	/*DB.insertItem("tst", "12345, \"hshsh\"");
	DB.insertItem("tst", "\"hshsh\"", "password");
	DB.insertItem("tst", "12346", "id");
	DB.updateItem("tst", "password = 99999", "id = 12346");*/
	vector<vector<string>> ret = DB.selectItem("tst", "*");
	for (auto temp: ret) {
		for (auto &str: temp)
			cout << str << " ";
		cout << endl;
	}
	/*DB.deleteItem("tst", "id = 0");
	ret = DB.selectItem("tst", "*");
	for (auto temp: ret) {
		for (auto &str: temp)
			cout << str << " ";
		cout << endl;
	}*/
    DB.showTB();
	DB.deleteDB("mydb");
	DB.disconnect();
	return 0;
}