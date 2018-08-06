#pragma once
#include <map>
class CViewTree;
struct PropertyGrid;
class CPropertiesWnd;
typedef void(*PROPERTY_CHG_FUNC)(CPropertiesWnd *propWnd, std::map<CString, PropertyGrid> &modProp, CString newValue);

struct PropertyGrid
{
	CString propertyValue;
	PROPERTY_CHG_FUNC callBack;   ///�ص�����
	BOOL isCombox;    ///�Ƿ�����������
	std::map<CString, CString> comboxValRel;    ///�������ֵӳ��
};

/*ȫ������*/
extern std::map<int, std::map<CString, PropertyGrid> > gProperties;

/*�˵���ʼ��*/
typedef void(__cdecl * INIT_FUNC)(CWnd *mainWnd, CViewTree *viewTree);
extern "C" __declspec(dllexport) void Initilize(CWnd *mainWnd, CViewTree *viewTree);
/*��ʼ��ģ������*/
typedef void(__cdecl * INIT_PROPERTY_FUNC)(std::map<int, std::map<CString, PropertyGrid> > &gProperty);
extern "C" __declspec(dllexport) void PropertyInitilize(std::map<int, std::map<CString, PropertyGrid> > &gProperty);



/*�����������ƶ���*/
const CString IP_ADDR = _TEXT("IP��ַ");
const CString IP_PORT = _TEXT("�˿ں�");
const CString TEST_NUMBER = _TEXT("���Ժ���");
const CString ACCT_ID = _TEXT("�˻�ID");
const CString USER_ID = _TEXT("�û�ID");
const CString USER_IMSI = _TEXT("�û�IMSI");
const CString USER_IMEI = _TEXT("�û�IMEI");
const CString USER_HOME_CODE = _TEXT("�û�������");
const CString USER_PROVIDER_CODE = _TEXT("������Ӫ��");
const CString CUST_ID = _TEXT("�ͻ�ID");
const CString DB_CONN_STRING = _TEXT("���ݿ����Ӵ�");
const CString HOST_USERNAME = _TEXT("�û���");
const CString HOST_USERPWD = _TEXT("����");


