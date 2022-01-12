#ifndef INCLUDE_json_process_H
#define INCLUDE_json_process_H


#include "json/json.h"
#include "json/reader.h"
#include "json/writer.h"
#include "json/value.h"
#include "server_property.h"//���Լ�����������

//#pragma comment(lib,"lib_json_d.lib")//������Ҫ�Ŀ��ļ�

/*===========================test================================
�ɽ����´������main�����в���

	//��json��ʽ�ַ������봴����json�ṹ��
	Json::Value json_struct;//�㴴��һ��json����
	Json::FastWriter writer;//�㽨һ��jsonд��string�Ľӿ�
	json_struct["test1"]="sss";//�㸳��json��������ֵ
	string kk=writer.write(json_struct);//�㽫json����ת��Ϊstring�ַ���
	char StrBuf[1000]={0};
	strcpy(StrBuf,kk.c_str());//stringת��Ϊchar
	
	
	JSON_package json_msg(StrBuf);//����json�ṹ�壬�������Ǹ�char��Ϊ��ʼ�������봫��
	json_msg.add_item("blood","10");//����
	json_msg.add_item("������",8);
	json_msg.add_item("������",17);//���蹥�������ԣ�ֵΪ17������������Ǹ�8
	cout<<"Ϊһ��json�ṹ����������������ݣ���ԭ������test1\n"<<json_msg.to_StrBuf()<<endl;//��json�ṹ�����Ϊ�ַ�������������ʾ


	//��������json�ṹ�壬������һ��������һ��
	JSON_package json_msg1;//����json�ṹ�壬��������������
	cout<<"������json�ṹ������:"<<json_msg1.to_StrBuf()<<endl;//���û��������������뽫�ýṹ��ת��Ϊstring���ʱ����ʾû����
	json_msg1.add_item("name","������");
	json_msg1.add_item("blood","102.23456");//ֻ�ܴ���int���ͣ�float��double����string����
	json_msg1.add_item("attack",228);

	JSON_package effect_all;//����json�ṹ�壬�������Ч����ϸ����
	JSON_package effect;//����Ч��
	effect.add_item("effect","2002");
	effect.add_item("effect_p1","1");
	effect.add_item("effect_p2","2");
	effect.add_item("effect_p3","5");
	effect_all.add_struct_array(effect.get_json());
	effect.add_item("effect","2052");
	effect.add_item("effect_p1","3");
	effect.add_item("effect_p2","1");
	effect.add_item("effect_p3","6");
	effect_all.add_struct_array(effect.get_json());
	effect.add_item("effect","2231");
	effect.add_item("effect_p1","23");
	effect.add_item("effect_p2","31");
	effect.add_item("effect_p3","622");
	effect.add_item("effect_p4","6");//֮ǰ��������û�д����������鷽ʽ�鿴����֮ǰ����Ϊnull
	effect_all.add_struct_array(effect.get_json());

	cout<<"������ȡֵ��\n";
	for(int i=0;i<3;i++)//��ʾ������������Ϊeffect��ֵ
		cout<<effect_all.get_json()[i]["effect"];//�����Ǹ�i���ܸ���ֵ��ֻ�ܸ�ֵ����

	
	json_msg1.add_struct("Ч������",effect_all.get_json());//����Ч�����ṹ����ӵ���������������ݽṹ��
	cout<<"������ݵ�����Ч��:\n"<<json_msg1.to_StrBuf()<<endl;
	

	cout<<"��ȡattack�������ַ�����"<<json_msg1.get_value("attack")<<endl;

	JSON_package json_msg2(json_msg1.get_json("Ч������"));//��ȡ�ṹ���нṹ�岢�����´����Ľṹ����
	cout<<"��ȡ�ṹ���еĽṹ��:\n"<<json_msg2.to_StrBuf()<<endl;
	cout<<"����ȡ�Ľṹ������ȡֵ��\n";
	for(int i=0;i<3;i++)//��ʾ������������Ϊeffect��ֵ
		cout<<json_msg2.get_json()[i]["effect_p4"];//�����Ǹ�i���ܸ���ֵ��ֻ�ܸ�ֵ����


===========================test================================*/


class JSON_package
{
	private:
		string json_string;//����json���ݽṹ��ת��Ϊ�ַ����������
		char* json_value;//�洢����ȡ�ı������ַ���
		Json::Value json_struct;//��������json���ݽṹ��


		bool whether_process;//�Ƿ��json�ṹ�崦���,��ʼ��Ŀ�꽨��ʱΪfalse������������ݲ������Ϊtrue

	public:

		void ini();//��ʼ���������

		JSON_package();//����һ��������JSON_package����
		JSON_package(char* StrBuf);//����һ��JSON_package�ṹ�壬������Ϣ�ַ������ݲ�����
		JSON_package(Json::Value other_json_struct);//����һ����ȡ����json�ṹ�崴��json�ṹ��

		void add_item(string name,string value);//���������ֵ���ṹ����
		void add_item(string name,int value);//���������ֵ���ṹ����
		void add_struct(string name,Json::Value other_struct);//��ӱ�Ľṹ�壬�ṹ������Ϊname

		//add_item����ͬһ��{ }������"����"="ֵ"��������ö��Ÿ���
		//��append���ں����Ӹ�{}�����Խ�ǰ������{ }��Ϊͬһ�������ڵ�������ͬ��Ա

		void add_item_array(string name,string value);//��ĳһ��ֵ���������ݷ�ʽ����array_name������
		void add_item_array(string array_name,string name,string value);//��ĳһ��ֵ���������ݷ�ʽ����array_name������
		void add_struct_array(Json::Value other_struct);
		void add_struct_array(string array_name,Json::Value other_struct);//��ĳһ�ṹ�����������ݷ�ʽ����array_name������

		Json::Value get_json();//��ȡ����json�ṹ��
		Json::Value get_json(string name);//��ȡ�ýṹ���е�����Ϊname�Ľṹ�壬��ȡ��ṹ�壨�����ҵ�name�Ľṹ��������JSON_package(Json::Value other_json_struct)���캯�����������ýṹ�壩

		const char* to_StrBuf();//��json_string������ת��Ϊchar*�ַ����󴫳�
		char* get_value(string name);//��ȡ��������Ϊname��ֵ

};

void JSON_package::add_struct_array(Json::Value other_struct)
{
	json_struct.append(other_struct);
	whether_process=true;
}

void JSON_package::add_struct_array(string array_name,Json::Value other_struct)
{
	json_struct[array_name].append(other_struct);
	whether_process=true;
}

void JSON_package::add_item_array(string name,string value)
{
	Json::Value item;
	item[name]=value;
	json_struct.append(item);
	whether_process=true;
}

void JSON_package::add_item_array(string array_name,string name,string value)
{
	Json::Value item;
	item[name]=value;
	json_struct[array_name].append(item);
	whether_process=true;
}




void JSON_package::add_struct(string name,Json::Value other_struct)//��ӱ�Ľṹ�壬�ṹ������Ϊname
{
	json_struct[name]=other_struct;
	whether_process=true;
}


Json::Value JSON_package::get_json(string name)
{
	if(!whether_process)cout<<"û�����!\n";
	return json_struct[name];
}


Json::Value JSON_package::get_json()
{
	if(!whether_process)cout<<"û�����!\n";
	return json_struct;
}
void JSON_package::ini()
{
	json_value= new char[20];
	json_string="";//�ַ��������ÿ�
}

JSON_package::JSON_package(Json::Value other_json_struct)
{
	ini();
	json_struct=other_json_struct;
	whether_process=true;
}

JSON_package::JSON_package()
{
	ini();
	whether_process=false;
}

JSON_package::JSON_package(char* StrBuf)
{
	ini();
	json_string=StrBuf;
	Json::Reader reader;
	Json::FastWriter writer;
	if(!reader.parse(json_string, json_struct))//���ַ�������ת��Ϊ�ṹ��
		cout<<"reader parse error[json��������!]:"<<strerror(errno)<<endl;
	whether_process=true;
}

const char* JSON_package::to_StrBuf()
{
	if(!whether_process)cout<<"û�����!\n";
	Json::FastWriter writer;
	//Json::Reader reader;
	json_string=writer.write(json_struct);//���ṹ������ת��Ϊ�ַ�����ʽ
	const char* StrBuf=json_string.c_str();
	return StrBuf;
}
 char* JSON_package::get_value(string name)
{
	if(!whether_process)cout<<"û�����!\n";
	Json::FastWriter writer;
	
	//ϸ�ڣ��������ֱ�ӣ�const char* StrBuf=json_struct[name].toStyledString().c_str();
	//�������ӡ��������ʾ�����������ص����Ϊ����
	//ԭ��Ϊconst charָ��һ����ʱ������ַ������ڱ���������ʱ�������ַ������ݣ����·��ص�StrBufָ����Ч����
	
	strcpy(json_value,json_struct[name].toStyledString().c_str());
	return json_value;
}



void JSON_package::add_item(string name,string value)//����Ϊ���������,���֮ǰ�й���name�ˣ���valueֱ�Ӹ���
{
	json_struct[name]=value;//�Խṹ��������ֵ
	whether_process=true;

}
void JSON_package::add_item(string name,int value)//����Ϊ���������,���֮ǰ�й���name�ˣ���valueֱ�Ӹ���
{
	json_struct[name]=value;//�Խṹ��������ֵ
	whether_process=true;
}
















#endif