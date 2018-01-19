#pragma once
#include <map>

class ModuleContext;
class CBillingToolView;

class BusiFunc
{
public:
	//触发开机
	static void TriggerStartUp(ModuleContext *ctx,  void *ptr);
	//触发停机
	static void TriggerStop(ModuleContext *ctx, void *ptr);

private:
	BusiFunc();

};