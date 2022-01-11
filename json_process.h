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

	Json::Value json_struct;//�㴴��һ��json����
	Json::FastWriter writer;//�㽨һ��jsonд��string�Ľӿ�
	//json_struct["shit"]="sss";//�㸳��json��������ֵ
	string kk=writer.write(json_struct);//�㽫json����ת��Ϊstring�ַ���
	char StrBuf[1000]={0};
	strcpy(StrBuf,kk.c_str());//stringת��Ϊchar
	
	JSON_package json_msg(StrBuf);//����json�ṹ�壬�������Ǹ�char��Ϊ��ʼ�������봫��
	json_msg.add_item("blood","10");//����
	json_msg.add_item("������",8);
	json_msg.add_item("������",17);//���蹥�������ԣ�ֵΪ17������������Ǹ�8
	cout<<"pp"<<json_msg.to_StrBuf()<<endl;//��json�ṹ�����Ϊ�ַ�������������ʾ

	JSON_package json_msg1;//����json�ṹ�壬��������������
	cout<<"������json�ṹ������:"<<json_msg1.to_StrBuf()<<endl;//���û��������������뽫�ýṹ��ת��Ϊstring���ʱ����ʾû����
	json_msg1.add_item("[1]name","������");
	json_msg1.add_item("[2]blood",10);
	json_msg1.add_item("[3]attack","8");
	
	JSON_package json_character_effect;//����json�ṹ�壬�������Ч����ϸ����
	json_character_effect.add_item("effect1-1",2022);//Ч��1��1������
	json_character_effect.add_item("effect1-2",2052);//Ч��1��2������
	json_character_effect.add_item("effect1-3",4022);//Ч��1��3������
	json_character_effect.add_item("effect1-4",5022);//Ч��1��4������
	json_character_effect.add_item("effect2-1",5052);//Ч��1��1������
	json_character_effect.add_item("effect2-2",4);//Ч��1��2������
	json_character_effect.add_item("effect2-3",255);//Ч��1��3������
	json_character_effect.add_item("effect2-4",122);//Ч��1��4������
	
	json_msg1.add_struct("Ч������",json_character_effect.to_json());//��Ч���ṹ����ӵ�����������ݽṹ��
	cout<<"����Ч��:\n"<<json_msg1.to_StrBuf()<<endl;

===========================test================================*/


class JSON_package
{
	private:
		string json_string;//����json���ݽṹ��ת��Ϊ�ַ����������
		Json::Value json_struct;//��������json���ݽṹ��


		bool whether_process;//�Ƿ��json�ṹ�崦���,��ʼ��Ŀ�꽨��ʱΪfalse������������ݲ������Ϊtrue

	public:
		JSON_package();//����һ��������JSON_package����
		JSON_package(char* StrBuf);//����һ��JSON_package�ṹ�壬������Ϣ�ַ������ݲ�����
		void add_item(string name,string value);//���������ֵ���ṹ����
		void add_item(string name,int value);//���������ֵ���ṹ����
		const char* to_StrBuf();//��json_string������ת��Ϊchar*�ַ����󴫳�

		void add_struct(string name,Json::Value other_struct);//��ӱ�Ľṹ�壬�ṹ������Ϊname

		Json::Value to_json();//��ȡjson�ṹ��
};

void JSON_package::add_struct(string name,Json::Value other_struct)//��ӱ�Ľṹ�壬�ṹ������Ϊname
{
	json_struct[name]=other_struct;
}

Json::Value JSON_package::to_json()
{
	if(!whether_process)cout<<"û�����!\n";
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