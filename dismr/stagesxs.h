#pragma once
#include"havesxs.h"
HRESULT process_package(SxSPackage package, std::wstring srcpath, std::wstring imgdir,int operation, _In_opt_ bool bToInstall=false);
HRESULT process_deployment(SxSAssembly assembly, std::wstring srcpath, std::wstring imgdir, int operation,_In_opt_ bool bToInstall = false);
HRESULT process_assembly(SxSAssembly assembly, std::wstring srcpath, std::wstring imgdir, int operation, _In_opt_ bool bToInstall = false);
HRESULT InstallFile(std::wstring origpath, std::wstring newpath, std::wstring imgpath);
HRESULT InstallReg(SxSRegistry reg, std::wstring sxssoft, std::wstring sxssys, std::wstring sxsdef);
HRESULT install_assembly(SxSAssembly assembly, std::wstring imgdir);