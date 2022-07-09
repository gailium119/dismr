#include"sxsreg.h"

HRESULT SxSAddRegPackage(SxSPackage package, std::wstring regpath, int operation) {
	SxSPackage packagefamily = package;
	packagefamily.version = L"";
	std::wstring basekey = regpath + L"\\Microsoft\\Windows\\CurrentVersion\\CBS\\Packages";
	basekey += L"\\";
	basekey += packagefamily.genname();
	std::wstring basekeypend = regpath + L"\\Microsoft\\Windows\\CurrentVersion\\CBS\\PackagePending";
	std::wstring origver;
	RegGetSZ(basekey, L"", &origver);
	if (origver.size() != 0) {
		SxSVersion over(origver);
		SxSVersion nver(package.version);
		if (over > nver) {
			printf("Skipping\n");
		}
		else if (over == nver) {
			return S_FALSE;
		}
		else {
			RegAddSZ(basekey, L"", package.version);
			RegAddDWORD(basekeypend + L"\\" + package.genname(), L"", operation);
		}

	}
	else {
		RegAddSZ(basekey, L"", package.version);
		RegAddDWORD(basekeypend+L"\\"+package.genname(), L"", operation);
	}
	RegAddDWORD(basekey, package.version, operation);
	return S_OK;
}
HRESULT SxSAddRegAssembly(SxSAssembly assembly, std::wstring regpath, int operation) {
	SxSAssembly assemblyfamily = assembly;
	assemblyfamily.winners = true;
	std::wstring basekey = regpath + L"\\Microsoft\\Windows\\CurrentVersion\\CBS\\Assemblies";
	basekey += L"\\";
	basekey += assemblyfamily.genname();
	std::wstring basekeypend = regpath + L"\\Microsoft\\Windows\\CurrentVersion\\CBS\\AssembliesPending";
	std::wstring origver;
	RegGetSZ(basekey, L"", &origver);
	if (origver.size() != 0) {
		SxSVersion over(origver);
		SxSVersion nver(assembly.version);
		if (over > nver) {
			printf("Skipping\n");
		}
		else if (over == nver) {
			return S_FALSE;
		}
		else {
			RegAddSZ(basekey, L"", assembly.version);
			RegAddDWORD(basekeypend + L"\\" + assembly.genname(), L"", operation);
		}
	}
	else {
		RegAddSZ(basekey, L"", assembly.version);
		RegAddDWORD(basekeypend + L"\\" + assembly.genname(), L"", operation);
	}
	RegAddDWORD(basekey, assembly.version, operation);
	return S_OK;
}

HRESULT SxSAddRegDeployment(SxSAssembly assembly, std::wstring regpath, int operation) {
	SxSAssembly assemblyfamily = assembly;
	assemblyfamily.winners = true;
	std::wstring basekey = regpath + L"\\Microsoft\\Windows\\CurrentVersion\\CBS\\Deployments";
	basekey += L"\\";
	basekey += assemblyfamily.genname();
	std::wstring basekeypend = regpath + L"\\Microsoft\\Windows\\CurrentVersion\\CBS\\DeploymentsPending";
	std::wstring origver;
	RegGetSZ(basekey, L"", &origver);
	if (origver.size() != 0) {
		SxSVersion over(origver);
		SxSVersion nver(assembly.version);
		if (over > nver) {
			printf("Skipping\n");
		}
		else if (over == nver) {
			return S_FALSE;
		}
		else {
			RegAddSZ(basekey, L"", assembly.version);
			RegAddDWORD(basekeypend + L"\\" + assembly.genname(), L"", operation);
		}
	}
	else {
		RegAddSZ(basekey, L"", assembly.version);
		RegAddDWORD(basekeypend + L"\\" + assembly.genname(), L"", operation);
	}
	RegAddDWORD(basekey, assembly.version, operation);
	return S_OK;
}
std::vector<SxSPackage> SxSGetRegPKGS(std::wstring regpath) {
	
}