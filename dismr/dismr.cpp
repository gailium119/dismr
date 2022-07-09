

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
	HRESULT hr= SxSRemovePendingPackages(SXS_HIVE_SOFT);

	auto deployments = get_deployments_pending(imgdir, SXS_STAGED);
	printf("34.9%%\n");
	for (int j = 0; j < deployments.size(); j++) {
		HRESULT hr = deployments[j].Verify(imgdir + L"\\WinSxS\\Manifests");
		if (hr == S_OK) {
			auto asses = deployments[j].GetDependencies();
			for (int i = 0; i < asses.size(); i++) {
				asses[i].Verify(srcdir);
				stage_assembly(asses[i], srcdir, imgdir);
				asses[i].Release();
			}
		}
	}
	hr = SxSRemovePendingDeployments(SXS_HIVE_SOFT);
	printf("69.0%%\n");
	auto assemblies = get_assemblies_pending(imgdir, SXS_STAGED);

	for (int j = 0; j < assemblies.size(); j++) {
		HRESULT hr = assemblies[j].Verify(imgdir + L"\\WinSxS\\Manifests");
		if (hr == S_OK) {
			auto files = assemblies[j].GetFiles();
			std::wstring filedir = srcdir +L"\\"+assemblies[j].genname();
			for (int i = 0; i < files.size(); i++) {
				std::wstring filepath = filedir +L"\\" +files[i].srcname;
				if (!PathFileExists(filepath.c_str())) {
					printf("Error:0x800f081f");
					return 0;
				}
			}
		}
	}
	return 0;
}
