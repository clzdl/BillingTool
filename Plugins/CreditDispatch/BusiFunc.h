#pragma once
#include <map>

class ModuleContext;
class CBillingToolView;

class BusiFunc
{
public:
	//触发开机
	static void TriggerStartUp(ModuleContext *ctx,  void *ptr);
	//触发停机,通过发送http消息
	static void TriggerStopByNet(ModuleContext *ctx, void *ptr);
	//触发停机,通过生成信控文件
	static void TriggerStopByFile(ModuleContext *ctx, void *ptr);
	//触发提醒,通过发送http消息
	static void TriggerRemindByNet(ModuleContext *ctx, void *ptr);
	//触发提醒,通过生成信控文件
	static void TriggerRemindByFile(ModuleContext *ctx, void *ptr);
private:
	BusiFunc();

};