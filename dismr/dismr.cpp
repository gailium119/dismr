

#include "stagesxs.h"
#include "regstub.h"
#include "sxsreg.h"

int main()
{
	XmlInitialize();
	SxSPackage pkg;
	pkg.LoadFromFile(L"C:\\Users\\Administrator\\Desktop\\ROS-Test-Package~31bf3856ad364e35~amd64~~10.0.22621.1.rum");
	stage_package(pkg, L"C:\\Users\\Administrator\\Desktop", L"E:\\ReactOS");
	auto deps=pkg.GetComponents();
	for (int i = 0; i < deps.size(); i++) {
		deps[i].Verify(L"C:\\Users\\Administrator\\Desktop");
		stage_deployment(deps[i], L"C:\\Users\\Administrator\\Desktop", L"E:\\ReactOS");
		auto assemblies =deps[i].GetDependencies();
		for (int i = 0; i < assemblies.size(); i++) {
			stage_assembly(assemblies[i], L"C:\\Users\\Administrator\\Desktop", L"E:\\ReactOS");
		}
	}
}
