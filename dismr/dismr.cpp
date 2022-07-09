

#include "stagesxs.h"
#include "regstub.h"
#include "sxsreg.h"
#include"getsxs.h"
#include "sxsinstall.h"
int main()
{
	XmlInitialize();
	do {


		std::wstring srcpkg = L"C:\\Users\\Administrator\\Desktop\\ROS-Test-Package~31bf3856ad364e35~amd64~~10.0.22621.1.rum";
		std::wstring imgdir = L"E:\\ReactOS";
		SxSInstallPackage(srcpkg, imgdir);

	} while (1);
	return 0;
}
