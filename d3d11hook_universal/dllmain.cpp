#include "framework.h"

DWORD Thread(HMODULE hModule)
{
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	printf("D3D11 Hook Example\n");

	bool init_hook = false;
	do
	{
		if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
		{
			kiero::bind(8, (void**)&hooks::oPresent, hooks::hkPresent);
			kiero::bind(42, (void**)&hooks::oEndScene, hooks::hkEndScene);
			init_hook = true;
		}
	} while (!init_hook);

	FreeLibraryAndExitThread(hModule, 1);
	return TRUE;
}

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Thread, hModule, 0, NULL);

	return TRUE;
}