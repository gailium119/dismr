#pragma once
#include"havesxs.h"
HRESULT stage_package(SxSPackage package, std::wstring srcpath, std::wstring imgdir);
HRESULT stage_deployment(SxSAssembly assembly, std::wstring srcpath, std::wstring imgdir); 
HRESULT stage_assembly(SxSAssembly assembly, std::wstring srcpath, std::wstring imgdir);