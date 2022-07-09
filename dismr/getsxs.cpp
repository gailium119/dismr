#include "getsxs.h"

std::vector<SxSPackage> get_packages_pending(std::wstring imgdir, int desiredstate)
{

		std::wstring sxspendingkeyname = SXS_HIVE_SOFT;
		sxspendingkeyname += L"\\Microsoft\\Windows\\CurrentVersion\\CBS\\PackagePending";
		auto keys = RegEnum(sxspendingkeyname);
		std::vector<SxSPackage> pkgs;
		SxSPackage pkg;
		for (int i = 0; i < keys.size(); i++) {
			DWORD currentstate;
			if (RegGetDWORD(sxspendingkeyname + L"\\" + keys[i], L"", &currentstate) == S_OK) {
				if (currentstate == desiredstate) {
					pkg.LoadFromFile(imgdir + L"\\Servicing\\Packages\\" + keys[i]+L".rum");
					pkg.Release();
					pkgs.push_back(pkg);
				}
			}
		}
		return pkgs;
}

std::vector<SxSDeployment> get_deployments_pending(std::wstring imgdir, int desiredstate)
{

	std::wstring sxspendingkeyname = SXS_HIVE_SOFT;
	sxspendingkeyname += L"\\Microsoft\\Windows\\CurrentVersion\\CBS\\DeploymentsPending";
	auto keys = RegEnum(sxspendingkeyname);
	std::vector<SxSDeployment> deps;
	SxSDeployment dep;
	for (int i = 0; i < keys.size(); i++) {
		DWORD currentstate;
		if (RegGetDWORD(sxspendingkeyname + L"\\" + keys[i], L"", &currentstate) == S_OK) {
			if (currentstate == desiredstate) {
				dep.LoadFromFile(imgdir + L"\\WinSxS\\Manifests\\" + keys[i] + L".manifest");
				dep.Release();
				deps.push_back(dep);
			}
		}
	}
	return deps;
}

std::vector<SxSAssembly> get_assemblies_pending(std::wstring imgdir, int desiredstate)
{

	std::wstring sxspendingkeyname = SXS_HIVE_SOFT;
	sxspendingkeyname += L"\\Microsoft\\Windows\\CurrentVersion\\CBS\\AssembliesPending";
	auto keys = RegEnum(sxspendingkeyname);
	std::vector<SxSAssembly> assemblies;
	SxSAssembly assembly;
	for (int i = 0; i < keys.size(); i++) {
		DWORD currentstate;
		if (RegGetDWORD(sxspendingkeyname + L"\\" + keys[i], L"", &currentstate) == S_OK) {
			if (currentstate == desiredstate) {
				assembly.LoadFromFile(imgdir + L"\\WinSxS\\Manifests\\" + keys[i] + L".manifest");
				assembly.Release();
				assemblies.push_back(assembly);
			}
		}
	}
	return assemblies;
}