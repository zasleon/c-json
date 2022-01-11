#ifndef INCLUDE_json_process_H
#define INCLUDE_json_process_H


#include "json/json.h"
#include "json/reader.h"
#include "json/writer.h"
#include "json/value.h"
#include "server_property.h"//我自己的其他函数

//#pragma comment(lib,"lib_json_d.lib")//链接需要的库文件

/*===========================test================================
可将以下代码放入main函数中测试

	Json::Value json_struct;//裸创建一个json对象
	Json::FastWriter writer;//裸建一个json写入string的接口
	//json_struct["shit"]="sss";//裸赋予json对象属性值
	string kk=writer.write(json_struct);//裸将json对象转化为string字符串
	char StrBuf[1000]={0};
	strcpy(StrBuf,kk.c_str());//string转化为char
	
	JSON_package json_msg(StrBuf);//创建json结构体，将上面那个char作为初始创建参入传入
	json_msg.add_item("blood","10");//赋予
	json_msg.add_item("攻击力",8);
	json_msg.add_item("攻击力",17);//赋予攻击力属性，值为17，会替代上面那个8
	cout<<"pp"<<json_msg.to_StrBuf()<<endl;//将json结构体具象化为字符串传出，并显示

	JSON_package json_msg1;//创建json结构体，存放人物基本数据
	cout<<"空数据json结构体内容:"<<json_msg1.to_StrBuf()<<endl;//如果没处理过其内容且想将该结构体转化为string输出时会提示没处理
	json_msg1.add_item("[1]name","虹马玉");
	json_msg1.add_item("[2]blood",10);
	json_msg1.add_item("[3]attack","8");
	
	JSON_package json_character_effect;//创建json结构体，存放人物效果详细参数
	json_character_effect.add_item("effect1-1",2022);//效果1第1个参数
	json_character_effect.add_item("effect1-2",2052);//效果1第2个参数
	json_character_effect.add_item("effect1-3",4022);//效果1第3个参数
	json_character_effect.add_item("effect1-4",5022);//效果1第4个参数
	json_character_effect.add_item("effect2-1",5052);//效果1第1个参数
	json_character_effect.add_item("effect2-2",4);//效果1第2个参数
	json_character_effect.add_item("effect2-3",255);//效果1第3个参数
	json_character_effect.add_item("effect2-4",122);//效果1第4个参数
	
	json_msg1.add_struct("效果总览",json_character_effect.to_json());//将效果结构体添加到人物基本数据结构体
	cout<<"最终效果:\n"<<json_msg1.to_StrBuf()<<endl;

===========================test================================*/


class JSON_package
{
	private:
		string json_string;//保存json数据结构体转变为字符串后的内容
		Json::Value json_struct;//保存抽象的json数据结构体


		bool whether_process;//是否对json结构体处理过,初始无目标建立时为false，经过添加数据操作后变为true

	public:
		JSON_package();//创建一个无内容JSON_package对象
		JSON_package(char* StrBuf);//创建一个JSON_package结构体，接受消息字符串内容并解析
		void add_item(string name,string value);//添加属性与值到结构体中
		void add_item(string name,int value);//添加属性与值到结构体中
		const char* to_StrBuf();//将json_string中内容转化为char*字符串后传出

		void add_struct(string name,Json::Value other_struct);//添加别的结构体，结构体名字为name

		Json::Value to_json();//获取json结构体
};

void JSON_package::add_struct(string name,Json::Value other_struct)//添加别的结构体，结构体名字为name
{
	json_struct[name]=other_struct;
}

Json::Value JSON_package::to_json()
{
	if(!whether_process)cout<<"没处理过!\n";
	return json_struct;
}

JSON_package::JSON_package()
{
	json_string="";
	whether_process=false;
}

JSON_package::JSON_package(char* StrBuf)
{
	json_string=StrBuf;
	
	Json::Reader reader;
	Json::FastWriter writer;
	if(!reader.parse(json_string, json_struct))//将字符串内容转化为结构体
		cout<<"reader parse error[json解析出错!]:"<<strerror(errno)<<endl;
	whether_process=true;
}

const char* JSON_package::to_StrBuf()
{
	if(!whether_process)cout<<"没处理过!\n";
	Json::FastWriter writer;
	//Json::Reader reader;
	json_string=writer.write(json_struct);//将结构体内容转变为字符串形式
	const char* StrBuf=json_string.c_str();
	return StrBuf;
}




void JSON_package::add_item(string name,string value)//单纯为其添加属性,如果之前有过该name了，则value直接覆盖
{
	json_struct[name]=value;//对结构体新增赋值
	whether_process=true;

}
void JSON_package::add_item(string name,int value)//单纯为其添加属性,如果之前有过该name了，则value直接覆盖
{
	json_struct[name]=value;//对结构体新增赋值
	whether_process=true;
}
















#endif