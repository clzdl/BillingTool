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
	//触发提醒,通过生成信控文件
	static void TriggerRemindByFile(ModuleContext *ctx, void *ptr);
private:
	BusiFunc();

};


const CString CREDIT_SERVICE = _TEXT("触发停机服务地址");
const CString BILL_FEE = _TEXT("话单费用");
const CString BILL_VOLUME = _TEXT("话单使用量");
const CString CUR_TOTAL_USED_VOLUME = _TEXT("截止本条话单前的总是用量");
const CString BASE_VOLUME = _TEXT("用户总的基础量");
const CString FILE_IN = _TEXT("信控分发文件入口");