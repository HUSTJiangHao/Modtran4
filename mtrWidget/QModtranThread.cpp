
#include "QModtranThread.h"
#include <windows.h>
#include <ShellAPI.h>

#include<QDir>
#include<Qdebug>



QModtranThread::QModtranThread()
{

}



void QModtranThread::run()
{

	QString curPath = QDir::currentPath();
	qDebug() << curPath;




	SHELLEXECUTEINFO ShExecInfo = { 0 };
	ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	ShExecInfo.hwnd = NULL;
	ShExecInfo.lpVerb = NULL;
	ShExecInfo.lpFile = (LPCWSTR)L"Mod4.exe";
	ShExecInfo.lpParameters = (LPCWSTR)L"";
	ShExecInfo.lpDirectory = (LPCWSTR)L"./Modtran4";
	ShExecInfo.nShow = SW_SHOWMINIMIZED;
	ShExecInfo.hInstApp = NULL;

	ShellExecuteEx(&ShExecInfo);

	WaitForSingleObject(ShExecInfo.hProcess, INFINITE);  // 等待进程结束


	quit();
}
