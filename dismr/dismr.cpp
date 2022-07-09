

#include "stagesxs.h"
#include "regstub.h"
#include "sxsreg.h"
#include"getsxs.h"
int main()
{
	XmlInitialize();
	SxSPackage pkg;
	
	std::wstring srcpkg = L"C:\\Users\\Administrator\\Desktop\\ROS-Test-Package~31bf3856ad364e35~amd64~~10.0.22621.1.rum";
	std::wstring imgdir = L"E:\\ReactOS";
	pkg.LoadFromFile(srcpkg);
	auto cnt=srcpkg.find_last_of(L"\\");
	auto srcdir = srcpkg.substr(0, cnt);
	printf("9.1%%\n");
	stage_package(pkg, srcdir,imgdir);
	pkg.Release();
	printf("10.0%%\n");
	auto pkgs=get_packages_pending(imgdir, SXS_STAGED);
	printf("34.0%%\n");
	for (int j = 0; j < pkgs.size(); j++) {
		HRESULT hr=pkgs[j].Verify(imgdir + L"\\Servicing\\Packages");
		if(hr==S_OK){
		auto deps = pkgs[j].GetComponents();
		for (int i = 0; i < deps.size(); i++) {
			deps[i].Verify(srcdir);
			stage_deployment(deps[i], srcdir, imgdir);
			deps[i].Release();
			}
		}
	}
	return 0;
	auto deps=pkg.GetComponents();
	for (int i = 0; i < deps.size(); i++) {
		deps[i].Verify(srcdir);
		stage_deployment(deps[i], srcdir, imgdir);
		auto assemblies =deps[i].GetDependencies();
		for (int i = 0; i < assemblies.size(); i++) {
			stage_assembly(assemblies[i], srcdir, imgdir);
		}
	}
}
