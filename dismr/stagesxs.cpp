#include"stagesxs.h"
#include "sxsreg.h"

HRESULT process_package(SxSPackage package, std::wstring srcpath, std::wstring imgdir,int operation, _In_opt_ bool bToInstall)
{
	std::wstring package_name = package.genname();
	std::wstring pkg_path = srcpath + L"\\" + package_name + L".rum";
	std::wstring pkg_new_path = imgdir + L"\\Servicing\\Packages\\" + package_name + L".rum";
	HRESULT hr = SxSAddRegPackage(package, SXS_HIVE_SOFT, operation, bToInstall);
	if (hr != S_OK) {
		return hr;
	}
	if (pkg_path.compare(pkg_new_path) != 0) {
		if (!PathFileExists(pkg_path.c_str())) {
			//wprintf(L"Not found:%ls\n", manifest_path.c_str());
			return 0x80070002;
		}
		if (!CopyFileW(pkg_path.c_str(), pkg_new_path.c_str(), 0)) {
			return GetLastError();
		}
	}
	auto subpackages = package.GetSubPackages();
	package.Release();
	for(int i=0;i<subpackages.size();i++){
		subpackages[i].Verify(srcpath);
		hr = process_package(subpackages[i],srcpath,imgdir, operation);
		if (FAILED(hr)) return hr;
	}
	return S_OK;
}

HRESULT process_deployment(SxSAssembly assembly, std::wstring srcpath, std::wstring imgdir,int operation, _In_opt_ bool bToInstall) {
	std::wstring assembly_name = assembly.genname();
	std::wstring manifest_path = srcpath + L"\\" + assembly_name + L".manifest";
	std::wstring manifest_new_path = imgdir + L"\\WinSxS\\Manifests\\" + assembly_name + L".manifest";
	HRESULT hr = SxSAddRegDeployment(assembly, SXS_HIVE_SOFT, operation, bToInstall);
	if (hr!= S_OK) {
		return hr;
	}

	if (manifest_path.compare(manifest_new_path) != 0) {
		if (!PathFileExists(manifest_path.c_str())) {
			//wprintf(L"Not found:%ls\n", manifest_path.c_str());
			return 0x80070002;
		}
		if (!CopyFileW(manifest_path.c_str(), manifest_new_path.c_str(), 0)) {
			return GetLastError();
		}
	}
	//wprintf(L"%ls\n", assembly.genname().c_str());
	return S_OK;//parse_assembly(manifest_path, destdir);
}

HRESULT process_assembly(SxSAssembly assembly, std::wstring srcpath, std::wstring imgdir,int operation, _In_opt_ bool bToInstall) {
	std::wstring assembly_name = assembly.genname();
	std::wstring manifest_path = srcpath + L"\\" + assembly_name + L".manifest";
	std::wstring manifest_new_path = imgdir + L"\\WinSxS\\Manifests\\" + assembly_name + L".manifest";
	HRESULT hr = SxSAddRegAssembly(assembly, SXS_HIVE_SOFT, operation, bToInstall);
	if (hr != S_OK) {
		return hr;
	}
	if (manifest_path.compare(manifest_new_path) != 0) {
		if (!PathFileExists(manifest_path.c_str())) {
			//wprintf(L"Not found:%ls\n", manifest_path.c_str());
			return 0x80070002;
		}
		if (!CopyFileW(manifest_path.c_str(), manifest_new_path.c_str(), 0)) {
			return GetLastError();
		}
	}
	//wprintf(L"%ls\n", assembly.genname().c_str());
	return S_OK;//parse_assembly(manifest_path, destdir);
}
void StringReplace(std::wstring *str,std::wstring old_value,std::wstring new_value) {

	for (std::wstring::size_type pos(0); pos != std::wstring::npos; pos += new_value.length()) {
		if ((pos = str->find(old_value, pos)) != std::wstring::npos)
			str->replace(pos, old_value.length(), new_value);
		else break;
	}
	return;
}
HRESULT InstallFile(std::wstring origpath, std::wstring newpath, std::wstring imgpath)
{

	StringReplace(&newpath,L"$(runtime.system32)",imgpath+L"\\System32");
	StringReplace(&newpath, L"$(runtime.windows)", imgpath);
	StringReplace(&newpath, L"$(runtime.reactos)", imgpath);
	StringReplace(&newpath, L"$(runtime.wbem)", imgpath + L"\\System32\\wbem");
	StringReplace(&newpath, L"$(runtime.drivers)", imgpath + L"\\System32\\drivers");
	auto cnt = newpath.find_last_of(L"\\");
	auto newdir = newpath.substr(0, cnt);
	_wmkdir(newdir.c_str());
	return CopyFileW(origpath.c_str(), newpath.c_str(),0);
}
HRESULT InstallReg(SxSRegistry reg, std::wstring sxssoft, std::wstring sxssys, std::wstring sxsdef)
{
	StringReplace(&reg.keyname, L"HKEY_LOCAL_MACHINE\\SOFTWARE", sxssoft);
	StringReplace(&reg.keyname, L"HKEY_LOCAL_MACHINE\\SYSTEM", sxssys);
	StringReplace(&reg.keyname, L"HKEY_CURRENT_USER", sxsdef);
	HRESULT hr;
	for (int i = 0; i < reg.keys.size(); i++) {
		if (reg.keys[i].valuetype.compare(L"REG_SZ") == 0) {
			hr=RegAddSZ(reg.keyname, reg.keys[i].name, reg.keys[i].value);
		}
		else if (reg.keys[i].valuetype.compare(L"REG_DWORD") == 0){
			wchar_t* end;
			DWORD dw = wcstol(reg.keys[i].value.c_str(),&end,16);
			hr=RegAddDWORD(reg.keyname, reg.keys[i].name, dw);
		}
		else if (reg.keys[i].valuetype.compare(L"REG_MULTI_SZ") == 0) {
			wchar_t* f = ::SysAllocString(reg.keys[i].value.c_str());
			std::replace(f, f + sizeof(wchar_t) * reg.keys[i].value.length(), L'\"', L'\0');
			std::wstring s(f, reg.keys[i].value.length());
			hr=RegAddMulti(reg.keyname, reg.keys[i].name, s);
		}
	}
	return S_OK;
}
HRESULT install_assembly(SxSAssembly assembly, std::wstring imgdir) {
	std::wstring assembly_name = assembly.genname();
	std::wstring manifest_path = imgdir + L"\\WinSxS\\Manifests\\" + assembly_name + L".manifest";

	HRESULT hr = assembly.Verify(imgdir + L"\\WinSxS\\Manifests");
	if (hr == S_OK) {
		auto files = assembly.GetFiles();
		std::wstring filedir = imgdir + L"\\WinSxS\\" + assembly.genname();

		if (_wmkdir(filedir.c_str()));
		for (int i = 0; i < files.size(); i++) {
			std::wstring filepath = filedir + L"\\" + files[i].srcname;
			std::wstring filenewpath = files[i].dest+files[i].name;
			InstallFile(filepath, filenewpath, imgdir);
		}

		auto regs = assembly.GetReg();

		for (int i = 0; i < regs.size(); i++) {
			InstallReg(regs[i], SXS_HIVE_SOFT,SXS_HIVE_SYS, SXS_HIVE_DEF);
		}
	}
	assembly.Release();
	if (hr != S_OK) {
		return hr;
	}
	//wprintf(L"%ls\n", assembly.genname().c_str());
	return S_OK;//parse_assembly(manifest_path, destdir);
}