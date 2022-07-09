#pragma once
#include"regstub.h"
HRESULT RegAddSZ(std::wstring keyName, std::wstring name, std::wstring value) {
	size_t keyfind = 1;
	HKEY basekey;
	keyfind = keyName.find(L"HKEY_LOCAL_MACHINE");
	if (keyfind == 0) {
		basekey = HKEY_LOCAL_MACHINE;
		//keyName = 0;
		keyName = keyName.substr(19);
	}
	else {
		keyfind = keyName.find(L"HKEY_CURRENT_USER");
		if (keyfind == 0) {
			basekey = HKEY_CURRENT_USER;
			//keyName = 0;
			keyName = keyName.substr(18);
		}
		else {
			keyfind = keyName.find(L"HKEY_CLASSES_ROOT");
			if (keyfind == 0) {
				basekey = HKEY_CLASSES_ROOT;
				//keyName = 0;
				keyName = keyName.substr(18);
			}
			else {
				return S_FALSE;
			}
		}
	}
	HKEY hRes = NULL;
	HRESULT hr = RegCreateKeyW(basekey, keyName.c_str(), &hRes);
	hr = RegSetValueExW(hRes, name.c_str(), 0, REG_SZ, (BYTE*)value.c_str(), value.length() * sizeof(wchar_t));
	RegCloseKey(hRes);
	return hr;
}

HRESULT RegAddMulti(std::wstring keyName, std::wstring name, std::wstring value) {
	size_t keyfind = 1;
	HKEY basekey;
	keyfind = keyName.find(L"HKEY_LOCAL_MACHINE");
	if (keyfind == 0) {
		basekey = HKEY_LOCAL_MACHINE;
		//keyName = 0;
		keyName = keyName.substr(19);
	}
	else {
		keyfind = keyName.find(L"HKEY_CURRENT_USER");
		if (keyfind == 0) {
			basekey = HKEY_CURRENT_USER;
			//keyName = 0;
			keyName = keyName.substr(18);
		}
		else {
			keyfind = keyName.find(L"HKEY_CLASSES_ROOT");
			if (keyfind == 0) {
				basekey = HKEY_CLASSES_ROOT;
				//keyName = 0;
				keyName = keyName.substr(18);
			}
			else {
				return S_FALSE;
			}
		}
	}
	HKEY hRes = NULL;
	HRESULT hr = RegCreateKeyW(basekey, keyName.c_str(), &hRes);
	hr = RegSetValueExW(hRes, name.c_str(), 0, REG_MULTI_SZ, (BYTE*)value.c_str(), value.length() * sizeof(wchar_t));
	RegCloseKey(hRes);
	return hr;
}
HRESULT RegAddDWORD(std::wstring keyName, std::wstring name, DWORD value) {
	size_t keyfind = 1;
	HKEY basekey;
	keyfind = keyName.find(L"HKEY_LOCAL_MACHINE");
	if (keyfind == 0) {
		basekey = HKEY_LOCAL_MACHINE;
		//keyName = 0;
		keyName = keyName.substr(19);
	}
	else {
		keyfind = keyName.find(L"HKEY_CURRENT_USER");
		if (keyfind == 0) {
			basekey = HKEY_CURRENT_USER;
			//keyName = 0;
			keyName = keyName.substr(18);
		}
		else {
			keyfind = keyName.find(L"HKEY_CLASSES_ROOT");
			if (keyfind == 0) {
				basekey = HKEY_CLASSES_ROOT;
				//keyName = 0;
				keyName = keyName.substr(18);
			}
			else {
				return S_FALSE;
			}
		}
	}
	HKEY hRes = NULL;
	HRESULT hr = RegCreateKeyW(basekey, keyName.c_str(), &hRes);
	hr = RegSetValueExW(hRes, name.c_str(), 0, REG_DWORD, (BYTE*)&value, sizeof(DWORD));
	RegCloseKey(hRes);
	return hr;
}

HRESULT RegGetDWORD(std::wstring keyName, std::wstring name, DWORD* outvalue) {
	size_t keyfind = 1;
	HKEY basekey;
	keyfind = keyName.find(L"HKEY_LOCAL_MACHINE");
	if (keyfind == 0) {
		basekey = HKEY_LOCAL_MACHINE;
		//keyName = 0;
		keyName = keyName.substr(19);
	}
	else {
		keyfind = keyName.find(L"HKEY_CURRENT_USER");
		if (keyfind == 0) {
			basekey = HKEY_CURRENT_USER;
			//keyName = 0;
			keyName = keyName.substr(18);
		}
		else {
			keyfind = keyName.find(L"HKEY_CLASSES_ROOT");
			if (keyfind == 0) {
				basekey = HKEY_CLASSES_ROOT;
				//keyName = 0;
				keyName = keyName.substr(18);
			}
			else {
				return S_FALSE;
			}
		}
	}
	HKEY hRes = NULL;
	DWORD MAX_SIZE = 260;
	HRESULT hr = RegCreateKeyW(basekey, keyName.c_str(), &hRes);
	hr = RegQueryValueExW(hRes, name.c_str(), 0, NULL, (BYTE*)outvalue, &MAX_SIZE);
	RegCloseKey(hRes);
	return hr;
}

HRESULT RegGetSZ(std::wstring keyName, std::wstring name, std::wstring* outvalue) {
	size_t keyfind = 1;
	HKEY basekey;
	keyfind = keyName.find(L"HKEY_LOCAL_MACHINE");
	if (keyfind == 0) {
		basekey = HKEY_LOCAL_MACHINE;
		//keyName = 0;
		keyName = keyName.substr(19);
	}
	else {
		keyfind = keyName.find(L"HKEY_CURRENT_USER");
		if (keyfind == 0) {
			basekey = HKEY_CURRENT_USER;
			//keyName = 0;
			keyName = keyName.substr(18);
		}
		else {
			keyfind = keyName.find(L"HKEY_CLASSES_ROOT");
			if (keyfind == 0) {
				basekey = HKEY_CLASSES_ROOT;
				//keyName = 0;
				keyName = keyName.substr(18);
			}
			else {
				return S_FALSE;
			}
		}
	}
	HKEY hRes = NULL;
	HRESULT hr = RegCreateKeyW(basekey, keyName.c_str(), &hRes);
	WCHAR data[260];
	DWORD MAX_SIZE = 260;
	hr = RegQueryValueExW(hRes, name.c_str(), 0, NULL, (BYTE*)data, &MAX_SIZE);
	*outvalue = data;
	RegCloseKey(hRes);
	return hr;
}

std::vector<std::wstring> RegEnum(std::wstring keyName)
{

	size_t keyfind = 1;
	HKEY basekey;
	keyfind = keyName.find(L"HKEY_LOCAL_MACHINE");
	if (keyfind == 0) {
		basekey = HKEY_LOCAL_MACHINE;
		//keyName = 0;
		keyName = keyName.substr(19);
	}
	else {
		keyfind = keyName.find(L"HKEY_CURRENT_USER");
		if (keyfind == 0) {
			basekey = HKEY_CURRENT_USER;
			//keyName = 0;
			keyName = keyName.substr(18);
		}
		else {
			keyfind = keyName.find(L"HKEY_CLASSES_ROOT");
			if (keyfind == 0) {
				basekey = HKEY_CLASSES_ROOT;
				//keyName = 0;
				keyName = keyName.substr(18);
			}
			else {
				return std::vector<std::wstring>();
			}
		}
	}
	HKEY hKey = NULL; //保存注册表的句柄 
	DWORD dwIndexs = 0; //需要返回子项的索引 
	WCHAR keyNames[MAX_PATH] = { 0 }; //保存子键的名称 
	DWORD charLength = 256;  //想要读取多少字节并返回实际读取到的字符长度
	WCHAR* subKey = L"SOFT\\Microsoft\\Windows\\CurrentVersion\\CBS\\PackagePending";
	std::vector<std::wstring> allregs;
	RegOpenKeyExW(basekey, keyName.c_str(), 0, KEY_READ, &hKey);
	while (RegEnumKeyExW(hKey, dwIndexs, keyNames, &charLength, NULL, NULL, NULL, NULL) == ERROR_SUCCESS)
	{
		++dwIndexs;
		charLength = 256;
		allregs.push_back(keyNames);
	}
	RegCloseKey(basekey);
	RegCloseKey(hKey);
	return allregs;
}

HRESULT RegDeleteSubKey(std::wstring keyName)
{
	size_t keyfind = 1;
	HKEY basekey;
	keyfind = keyName.find(L"HKEY_LOCAL_MACHINE");
	if (keyfind == 0) {
		basekey = HKEY_LOCAL_MACHINE;
		//keyName = 0;
		keyName = keyName.substr(19);
	}
	else {
		keyfind = keyName.find(L"HKEY_CURRENT_USER");
		if (keyfind == 0) {
			basekey = HKEY_CURRENT_USER;
			//keyName = 0;
			keyName = keyName.substr(18);
		}
		else {
			keyfind = keyName.find(L"HKEY_CLASSES_ROOT");
			if (keyfind == 0) {
				basekey = HKEY_CLASSES_ROOT;
				//keyName = 0;
				keyName = keyName.substr(18);
			}
			else {
				return S_FALSE;
			}
		}
	}
	return RegDeleteTreeW(basekey,keyName.c_str());
}
