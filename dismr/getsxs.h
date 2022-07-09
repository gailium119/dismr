#pragma once
#include"stagesxs.h"
#include"sxsreg.h"
#include "sha256.h"
#include "base64.h"
std::vector<SxSPackage> get_packages_pending(std::wstring imgdir, int desiredstate);
std::vector<SxSDeployment> get_deployments_pending(std::wstring imgdir, int desiredstate);
std::vector<SxSAssembly> get_assemblies_pending(std::wstring imgdir, int desiredstate);
std::wstring SxSGetHashForFile(std::wstring filepath);