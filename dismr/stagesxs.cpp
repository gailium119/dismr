#include"stagesxs.h"
#include "sxsreg.h"

HRESULT stage_package(SxSPackage package, std::wstring srcpath, std::wstring imgdir)
{
	std::wstring package_name = package.genname();
	std::wstring manifest_path = srcpath + L"\\" + package_name + L".rum";
	std::wstring manifest_new_path = imgdir + L"\\Servicing\\Packages\\" + package_name + L".rum";
	HRESULT hr = SxSAddRegPackage(package, SXS_HIVE_SOFT, SXS_STAGED);
	if (hr != S_OK) {
		return hr;
	}
	if (!PathFileExists(manifest_path.c_str())) {
		//wprintf(L"Not found:%ls\n", manifest_path.c_str());
		return 0x80070002;
	}
	if (!CopyFileW(manifest_path.c_str(), manifest_new_path.c_str(), 0)) {
		return GetLastError();
	}
	//wprintf(L"%ls\n", package.genname().c_str());
	return S_OK;//parse_package(manifest_path, destdir);
}

HRESULT stage_deployment(SxSAssembly assembly, std::wstring srcpath, std::wstring imgdir) {
	std::wstring assembly_name = assembly.genname();
	std::wstring manifest_path = srcpath + L"\\" + assembly_name + L".manifest";
	std::wstring manifest_new_path = imgdir + L"\\WinSxS\\Manifests\\" + assembly_name + L".manifest";
	HRESULT hr = SxSAddRegDeployment(assembly, SXS_HIVE_SOFT, SXS_STAGED);
	if (hr!= S_OK) {
		return hr;
	}
	if (!PathFileExists(manifest_path.c_str())) {
		//wprintf(L"Not found:%ls\n", manifest_path.c_str());
		return 0x80070002;
	}
	if (!CopyFileW(manifest_path.c_str(), manifest_new_path.c_str(), 0)) {
		return GetLastError();
	}
	//wprintf(L"%ls\n", assembly.genname().c_str());
	return S_OK;//parse_assembly(manifest_path, destdir);
}

HRESULT stage_assembly(SxSAssembly assembly, std::wstring srcpath, std::wstring imgdir) {
	std::wstring assembly_name = assembly.genname();
	std::wstring manifest_path = srcpath + L"\\" + assembly_name + L".manifest";
	std::wstring manifest_new_path = imgdir + L"\\WinSxS\\Manifests\\" + assembly_name + L".manifest";
	HRESULT hr = SxSAddRegAssembly(assembly, SXS_HIVE_SOFT, SXS_STAGED);
	if (hr != S_OK) {
		return hr;
	}
	if (!PathFileExists(manifest_path.c_str())) {
		//wprintf(L"Not found:%ls\n", manifest_path.c_str());
		return 0x80070002;
	}
	if (!CopyFileW(manifest_path.c_str(), manifest_new_path.c_str(), 0)) {
		return GetLastError();
	}
	//wprintf(L"%ls\n", assembly.genname().c_str());
	return S_OK;//parse_assembly(manifest_path, destdir);
}