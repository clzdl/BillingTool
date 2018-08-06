#pragma once
#include <map>

class ModuleContext;
class CBillingToolView;

class BusiFunc
{
public:
	//��������
	static void TriggerStartUp(ModuleContext *ctx,  void *ptr);
	//����ͣ��,ͨ������http��Ϣ
	static void TriggerStopByNet(ModuleContext *ctx, void *ptr);
	//����ͣ��,ͨ�������ſ��ļ�
	static void TriggerStopByFile(ModuleContext *ctx, void *ptr);
	//��������,ͨ�������ſ��ļ�
	static void TriggerRemindByFile(ModuleContext *ctx, void *ptr);
private:
	BusiFunc();

};


const CString CREDIT_SERVICE = _TEXT("����ͣ�������ַ");
const CString BILL_FEE = _TEXT("��������");
const CString BILL_VOLUME = _TEXT("����ʹ����");
const CString CUR_TOTAL_USED_VOLUME = _TEXT("��ֹ��������ǰ����������");
const CString BASE_VOLUME = _TEXT("�û��ܵĻ�����");
const CString FILE_IN = _TEXT("�ſطַ��ļ����");