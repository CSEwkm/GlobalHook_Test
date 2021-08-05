// GlobalHook_Test.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"

extern HMODULE g_hDllModule;
// 创建共享内存
#pragma data_seg("mydata")
    HHOOK g_hHook = NULL;
#pragma data_seg()
#pragma comment(linker, "/SECTION:mydata,RWS")//读、写、共享


// 钩子回调函数
LRESULT GetMsgProc(
	int code,
	WPARAM wParam,
	LPARAM lParam)
{
	printf("CallBack:GetMsgProc OK.\n");

	return ::CallNextHookEx(g_hHook, code, wParam, lParam);
}


// 设置全局钩子
BOOL SetGlobalHook()
{	
	//								消息钩子		回调函数	包含回调函数的DLL模块句柄	线程ID
	g_hHook = ::SetWindowsHookEx(WH_GETMESSAGE, (HOOKPROC)GetMsgProc, g_hDllModule, 0);
	if (NULL == g_hHook)
	{
		return FALSE;
	}
	return TRUE;
}


// 卸载钩子
BOOL UnsetGlobalHook()
{
	if (g_hHook)
	{
		::UnhookWindowsHookEx(g_hHook);
	}
	return TRUE;
}