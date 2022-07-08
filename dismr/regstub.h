#pragma once
#include"havesxs.h"
HRESULT RegAddSZ(std::wstring keyName, std::wstring name, std::wstring value);

HRESULT RegAddDWORD(std::wstring keyName, std::wstring name, DWORD value);

HRESULT RegGetDWORD(std::wstring keyName, std::wstring name, DWORD* outvalue);

HRESULT RegGetSZ(std::wstring keyName, std::wstring name, std::wstring* outvalue);