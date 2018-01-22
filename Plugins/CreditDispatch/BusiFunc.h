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
	//��������,ͨ������http��Ϣ
	static void TriggerRemindByNet(ModuleContext *ctx, void *ptr);
	//��������,ͨ�������ſ��ļ�
	static void TriggerRemindByFile(ModuleContext *ctx, void *ptr);
private:
	BusiFunc();

};