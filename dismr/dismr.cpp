

#include "stagesxs.h"
#include "regstub.h"
#include "sxsreg.h"
#include"getsxs.h"
#include "sxsinstall.h"
int wmain(int argc,wchar_t ** argv)
{
	XmlInitialize();
	std::wstring imgdir=L"", pkgdir=L"";
	for (int i = 1; i < argc; i++) {
		std::wstring tmpstr = argv[i];
		transform(tmpstr.begin(), tmpstr.end(), tmpstr.begin(), ::tolower);
		int find = tmpstr.find(L"/add-package");
		if (find == 0) {
			tmpstr = argv[i];
			//tmpstr.erase(std::remove(tmpstr.begin(), tmpstr.end(), '\"'), tmpstr.end());
			pkgdir = tmpstr.substr(13);
		}
		else {
			find = tmpstr.find(L"/image:");
			if (find == 0) {
				tmpstr = argv[i];
				//tmpstr.erase(std::remove(tmpstr.begin(), tmpstr.end(), '\"'), tmpstr.end());
				imgdir = tmpstr.substr(7);
			}
		}
	}
	if (imgdir.length() == 0 || pkgdir.length() == 0) {
		wprintf(L"Usage:dismr /image:[Your ReactOS folder] /Add-Package:[Your pkg path]\n");
		return 0;
	}
	HRESULT hr=RegLoadKeyW(HKEY_LOCAL_MACHINE, SXS_HIVE_DEF_SHORT, L"E:\\ReactOS\\System32\\config\\DEFAULT");
	if (hr!=S_OK) {
		wprintf(L"dismr require TrustedInstaller privilege on Windows host.\n");
		return 0;
	}
	hr = RegLoadKeyW(HKEY_LOCAL_MACHINE, SXS_HIVE_SOFT_SHORT, L"E:\\ReactOS\\System32\\config\\SOFTWARE");
	hr = RegLoadKeyW(HKEY_LOCAL_MACHINE, SXS_HIVE_SYS_SHORT, L"E:\\ReactOS\\System32\\config\\SYSTEM");
	/*
	std::wstring srcpkg = L"C:\\Users\\Administrator\\Desktop\\ROS-Test-Package~31bf3856ad364e35~amd64~~10.0.22621.1.rum";
	std::wstring imgdir = L"E:\\ReactOS";*/
	SxSInstallPackage(pkgdir, imgdir);
	XmlUnInitialize();
	RegUnLoadKeyW(HKEY_LOCAL_MACHINE, SXS_HIVE_DEF_SHORT);

	hr=RegUnLoadKeyW(HKEY_LOCAL_MACHINE, SXS_HIVE_SOFT_SHORT);
	//wprintf(L"Unload result-SOFT:%x", hr);
	hr=RegUnLoadKeyW(HKEY_LOCAL_MACHINE, SXS_HIVE_SYS_SHORT);
	//wprintf(L"Unload result-SYS:%x", hr);
	return 0;
}
