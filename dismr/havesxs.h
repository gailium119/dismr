#pragma once
#include<stdio.h>
#include<string>
#include <algorithm>
#include "md5.h"
#include"xmlproc_msxml.h"
#define SXS_HIVE_SOFT L"HKEY_LOCAL_MACHINE\\soft"
#define SXS_HIVE_SYS L"HKEY_LOCAL_MACHINE\\sys"
#define SXS_HIVE_DEF L"HKEY_LOCAL_MACHINE\\def"
#define SXS_HIVE_SOFT_SHORT L"soft"
#define SXS_HIVE_SYS_SHORT L"sys"
#define SXS_HIVE_DEF_SHORT L"def"
#define SXS_INSTALLED 0
#define SXS_STAGED 9
class SxSFile {
public:
	std::wstring name;
	std::wstring hash;
	std::wstring dest;
	std::wstring srcname;
};
class SxSVersion {
public:
	DWORD VersionMajor=0;
	DWORD VersionMinor=0;
	DWORD BuildNumber=0;
	DWORD UBR=0;
	SxSVersion(std::wstring verstring) {
		auto str = SysAllocString(verstring.c_str());
		wchar_t* dummyvalue;
		wchar_t* tmp = wcstok_s(str, L".",&dummyvalue);
		VersionMajor = wcstol(tmp, NULL, 10);
		tmp = wcstok_s(NULL, L".", &dummyvalue);
		VersionMinor = wcstol(tmp, NULL, 10);
		tmp = wcstok_s(NULL, L".", & dummyvalue);
		BuildNumber = wcstol(tmp, NULL, 10);
		tmp = wcstok_s(NULL, L"." ,& dummyvalue);
		UBR = wcstol(tmp, NULL, 10);
		SysFreeString(str);
	}
	bool operator <(SxSVersion newver) {
		if (this->VersionMajor > newver.VersionMajor) return false;
		if (this->VersionMinor > newver.VersionMinor) return false;
		if (this->BuildNumber > newver.BuildNumber) return false;
		if (this->UBR >= newver.UBR) return false;
		return true;
	}

	bool operator <=(SxSVersion newver) {
		if (this->VersionMajor > newver.VersionMajor) return false;
		if (this->VersionMinor > newver.VersionMinor) return false;
		if (this->BuildNumber > newver.BuildNumber) return false;
		if (this->UBR > newver.UBR) return false;
		return true;
	}
	bool operator >(SxSVersion newver) {
		return !(*this<=newver);
	}
	bool operator >=(SxSVersion newver) {
		return !(*this < newver);
	}
	bool operator ==(SxSVersion newver) {
		if (this->VersionMajor != newver.VersionMajor) return false;
		if (this->VersionMinor != newver.VersionMinor) return false;
		if (this->BuildNumber != newver.BuildNumber) return false;
		if (this->UBR != newver.UBR) return false;
		return true;
	}
};
class SxSRegistrySubKey {
public:
	std::wstring name;
	std::wstring valuetype;
	std::wstring value;
};
class SxSRegistry {
public:
	std::wstring keyname;
	std::vector<SxSRegistrySubKey> keys;
};
class SxSAssembly{
public:
	   std::wstring name=L"none";
       std::wstring culture=L"none";
       std::wstring type=L"none";
       std::wstring version = L"none";
       std::wstring publicKeyToken = L"none";
       std::wstring processorArchitecture = L"none";
       std::wstring versionScope = L"none";
	   bool winners=0;
	   std::wstring genname();
	   HRESULT LoadFromFile(std::wstring filename);
	   HRESULT Load2(std::wstring filename);
	   HRESULT Verify(std::wstring folder);
	   void Release();
	   std::vector<SxSFile> GetFiles();
	   std::vector<SxSRegistry> GetReg();
    protected:
		SxSXmlDoc sxsxmldoc;
		int status=0;
};
class SxSDeployment:public SxSAssembly {
public:
	std::vector<SxSAssembly> GetDependencies();
};
class SxSPackage {
public:
	std::wstring name = L"none";
	std::wstring lang = L"";
	std::wstring version = L"none";
	std::wstring publicKeyToken = L"none";
	std::wstring processorArchitecture = L"";
	std::wstring genname();
	HRESULT LoadFromFile(std::wstring filename);
	HRESULT Verify(std::wstring folder);
	void Release();
	std::vector<SxSDeployment> GetComponents();
	std::vector<SxSPackage> GetSubPackages();
protected:
	SxSXmlDoc sxsxmldoc;
	int status = 0;
};

std::wstring generate_pseudo_key(SxSAssembly assembly);
std::wstring generate_sxs_name(SxSAssembly assembly);