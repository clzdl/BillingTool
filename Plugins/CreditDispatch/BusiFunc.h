#pragma once
#include <map>

class ModuleContext;
class CBillingToolView;

class BusiFunc
{
public:
	//��������
	static void TriggerStartUp(ModuleContext *ctx,  void *ptr);
	//����ͣ��
	static void TriggerStop(ModuleContext *ctx, void *ptr);

private:
	BusiFunc();

};