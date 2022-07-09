#include "sxsinstall.h"
HRESULT SxSStagePackage(std::wstring srcpkg, std::wstring imgdir,_Outptr_opt_ SxSPackage* ppkg,_In_opt_ bool bToInstall) {
	SxSPackage pkg;
	HRESULT hr;
	pkg.LoadFromFile(srcpkg);
	auto cnt = srcpkg.find_last_of(L"\\");
	auto srcdir = srcpkg.substr(0, cnt);
	printf("9.1%%\n");
	hr=process_package(pkg, srcdir, imgdir, SXS_STAGED,bToInstall);
	pkg.Release();
	printf("10.0%%\n");
	auto pkgs = get_packages_pending(imgdir, SXS_STAGED);
	printf("34.0%%\n");
	for (int j = 0; j < pkgs.size(); j++) {
		hr = pkgs[j].Verify(imgdir + L"\\Servicing\\Packages");
		if (hr == S_OK) {
			auto deps = pkgs[j].GetComponents();
			for (int i = 0; i < deps.size(); i++) {
				deps[i].Verify(srcdir);
				hr = process_deployment(deps[i], srcdir, imgdir, SXS_STAGED, bToInstall);
				deps[i].Release();
			}
		}
	}
	SxSRemovePendingPackages(SXS_HIVE_SOFT);

	auto deployments = get_deployments_pending(imgdir, SXS_STAGED);
	printf("34.9%%\n");
	for (int j = 0; j < deployments.size(); j++) {
		hr = deployments[j].Verify(imgdir + L"\\WinSxS\\Manifests");
		if (hr == S_OK) {
			auto asses = deployments[j].GetDependencies();
			for (int i = 0; i < asses.size(); i++) {
				asses[i].Verify(srcdir);
				hr = process_assembly(asses[i], srcdir, imgdir, SXS_STAGED, bToInstall);
				asses[i].Release();
			}
		}
	}
	SxSRemovePendingDeployments(SXS_HIVE_SOFT);
	printf("69.0%%\n");
	auto assemblies = get_assemblies_pending(imgdir, SXS_STAGED);

	for (int j = 0; j < assemblies.size(); j++) {
		hr = assemblies[j].Verify(imgdir + L"\\WinSxS\\Manifests");
		if (hr == S_OK) {
			auto files = assemblies[j].GetFiles();
			std::wstring filedir = srcdir + L"\\" + assemblies[j].genname();
			for (int i = 0; i < files.size(); i++) {
				std::wstring filepath = filedir + L"\\" + files[i].srcname;
				if (!PathFileExists(filepath.c_str())) {
					printf("Error:0x800f081f");
					return 0;
				}
				else {
					if (files[i].hash.compare(SxSGetHashForFile(filepath)) != 0) {
						printf("Hash error verify");
						return 0;
					}
				}
			}
		}
		assemblies[j].Release();
	}
	printf("69.7%%\n");

	for (int j = 0; j < assemblies.size(); j++) {
		hr = assemblies[j].Verify(imgdir + L"\\WinSxS\\Manifests");
		if (hr == S_OK) {
			auto files = assemblies[j].GetFiles();
			std::wstring filedir = srcdir + L"\\" + assemblies[j].genname();
			std::wstring filenewdir = imgdir + L"\\WinSxS\\" + assemblies[j].genname();

			if (_wmkdir(filenewdir.c_str()));
			for (int i = 0; i < files.size(); i++) {
				std::wstring filepath = filedir + L"\\" + files[i].srcname;
				std::wstring filenewpath = filenewdir + L"\\" + files[i].srcname;
				if (!PathFileExists(filenewpath.c_str())) {
					CopyFileW(filepath.c_str(), filenewpath.c_str(), 0);
				}
			}
		}
		assemblies[j].Release();
	}
	SxSRemovePendingAssemblies(SXS_HIVE_SOFT);
	printf("70.0%%\n");
	if (ppkg == NULL) {
		printf("100.0%%\n");
		return 0;
	}
	else {
		*ppkg = pkg;
	}
	return hr;
}
HRESULT SxSInstallPackage(std::wstring srcpkg, std::wstring imgdir) {
	SxSPackage pkg;
	HRESULT hr=SxSStagePackage(srcpkg, imgdir,&pkg,true);
	pkg.Verify(imgdir + L"\\Servicing\\Packages");
	printf("70.1%%\n");
	hr = process_package(pkg, imgdir + L"\\Servicing\\Packages", imgdir, SXS_INSTALLED);
	pkg.Release();
	printf("70.3%%\n");
	auto pkgs = get_packages_pending(imgdir, SXS_INSTALLED);
	printf("70.6%%\n");
	for (int j = 0; j < pkgs.size(); j++) {
		hr = pkgs[j].Verify(imgdir + L"\\Servicing\\Packages");
		if (hr == S_OK) {
			auto deps = pkgs[j].GetComponents();
			for (int i = 0; i < deps.size(); i++) {
				deps[i].Verify(imgdir + L"\\WinSxS\\Manifests");
				hr = process_deployment(deps[i], imgdir + L"\\WinSxS\\Manifests", imgdir, SXS_INSTALLED);
				deps[i].Release();
			}
		}
	}
	SxSRemovePendingPackages(SXS_HIVE_SOFT);

	auto deployments = get_deployments_pending(imgdir, SXS_INSTALLED);
	printf("71.0%%\n");
	for (int j = 0; j < deployments.size(); j++) {
		hr = deployments[j].Verify(imgdir + L"\\WinSxS\\Manifests");
		if (hr == S_OK) {
			auto asses = deployments[j].GetDependencies();
			for (int i = 0; i < asses.size(); i++) {
				asses[i].Verify(imgdir + L"\\WinSxS\\Manifests");
				hr = process_assembly(asses[i], imgdir + L"\\WinSxS\\Manifests", imgdir, SXS_INSTALLED);
				asses[i].Release();
			}
		}
	}
	printf("80.0%%\n");
	SxSRemovePendingDeployments(SXS_HIVE_SOFT);
	auto assemblies= get_assemblies_pending(imgdir, SXS_INSTALLED);
	for (int j = 0; j < assemblies.size(); j++) {
		install_assembly(assemblies[j], imgdir);
	}
	printf("100.0%%\n");

	SxSRemovePendingAssemblies(SXS_HIVE_SOFT);
	return hr;
}