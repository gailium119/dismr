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
	HRESULT hr = RegCreateKeyW(basekey, keyName.c_str(), &hRes);
	hr = RegQueryValueExW(hRes, name.c_str(), 0, NULL, (BYTE*)outvalue, NULL);
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
	return hr;
}