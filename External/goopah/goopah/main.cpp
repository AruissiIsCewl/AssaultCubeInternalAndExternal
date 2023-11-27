#include <iostream>
#include <Windows.h>
#include <string>
#include <tchar.h>
#include <TlHelp32.h>
#include <thread>
#include <string>
#include <chrono>
#include <thread>


class Timer {
public:
	Timer() : start_time(std::chrono::high_resolution_clock::now()) {}

	void reset() {
		start_time = std::chrono::high_resolution_clock::now();
	}

	double elapsed() const {
		auto end_time = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
		return duration.count() * 1e-6; // convert microseconds to seconds
	}

private:
	std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
};



namespace offsets
{
		// needed for local player shit
		__int32 BaseAddress = 0x400000;
		__int32 OffsetLocalPlayer = 0x10F4F4;

		// cords shit
		const auto m_XPos = 0x38;
		const auto m_YPos = 0x3C;
		const auto m_ZPos = 0x40;

		// view angle offsets
		const auto m_ViewAngleX = 0x40;
		const auto m_ViewAngleY = 0x44;


		// local player shit
		const auto m_Speed = 0x0080;
		const auto health = 0x00F8;
		const auto i_Ammo = 0x0150;
		const auto m_SecAmmo = 0x013C;
		const auto m_AmmoMags = 0x0128;
		const auto m_Vest = 0x00FC;
		const auto m_Flashbangs = 0x0158;
		const auto m_WeaponTimer = 0x0178;

		//visual shit
		const auto sv_GetMode = 0x50F49C;
		const auto sv_ClientNumber = 0x510198;
		const auto sv_name = 0x51019C;
		const auto p_MaxRoll = 0x510144;
		const auto p_AutoReload = 0x5101D0;
		const auto o_Paused = 0x510CE0;
		const auto o_GameSpeed = 0x510CDC;
		const auto m_MouseShotSensitivity = 0x4EE444;
		const auto m_InvertMouse = 0x51016C;
		const auto h_ToggleConsole = 0x4FEC10;
		const auto h_ShowTarget = 0x50F284;
		const auto h_ShowSpeed = 0x50F288;
		const auto h_ShowScoreOnDeath = 0x50F514;
		const auto h_ShowRadarValues = 0x50F268;
		const auto h_ShowMap = 0x50F240;
		const auto h_Righthanded = 0x510A4C;
		const auto h_RadarHeight = 0x50F264;
		const auto h_RadarEntSize = 0x50F208;
		const auto h_OldAmmoHUD = 0x510A48;
		const auto h_HideRadar = 0x50F21C;
		const auto h_HideHudMessages = 0x50F230;
		const auto h_HideHudEquipment = 0x50F234;
		const auto h_HideDamageIndicator = 0x50F248;
		const auto h_HideCompass = 0x50F220;
		const auto h_DrawGun = 0x50F200;
		const auto h_DrawFPS = 0x50F210;
		const auto	h_DbgPos = 0x50F280;
		const auto h_DamageScreenFade = 0x50F278;
		const auto h_DamageScreenFactor = 0x50F270;
		const auto h_DamageScreenAlpha = 0x50F274;
		const auto h_DamageScreen = 0x50F26C;
		const auto h_CrosshairSize = 0x50F20C;
		const auto g_GameVersion = 0x510CF4;
		const auto dbg_FlySpeed = 0x510148;
		const auto EngineState_Test = 0x509BD8;
}

namespace variables
{
	int32_t localPlayer; // var to store localplayer
	DWORD plrSpeed;
	DWORD plrHealth;
	DWORD plrAmmo;
	DWORD plrGreandes;
	DWORD plrSecondaryAmmo;
	DWORD plrReserveAmmo;
	DWORD plrVestHealth;
	DWORD plrWeaponTimer;


	__int32 newHealth = 300;
	__int32 newAmmo = 10;
	__int32 newGrenades = 3;
	__int32 newSecAmmo = 10;
	__int32 newResAmmo = 10;
	__int32 newVestHealth = 100;
	__int32 newWeaponTimer = 1.5;


}

Timer timer1;

DWORD getprocess(const wchar_t* proc)
{
	Timer timer1;

    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (hSnap == INVALID_HANDLE_VALUE)
    {
        std::cout << "[ - ] Handle Failed to create";
        std::cin.get();
        return 0;
    }
    
	if (hSnap)
	{
		std::cout << "[ + ] Handle created successfully\n";
	}
    
    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);

    if (!Process32First(hSnap, &pe32))
    {
        CloseHandle(hSnap);
        std::cout << "[ - ] Failed to create entry";
        std::cin.get();
        return 0;
    }

    do
    {
        if (wcscmp(pe32.szExeFile, proc) == 0)
        {
            CloseHandle(hSnap);
            std::cout << "[ + ] Snapshot created and snatched PID @ " << pe32.th32ProcessID << " | " << pe32.th32ParentProcessID << "\n";
			HWND win = FindWindowA(NULL, "AssaultCube");
			SetWindowTextA(win, "this guy is using my wonderful hack!");
            return pe32.th32ProcessID;
        }
    } while (Process32Next(hSnap, &pe32));

    CloseHandle(hSnap);


    return 0;
}

double timerressult = timer1.elapsed();

int main()
{
	Timer timer2;
	SetConsoleTitle(L"hola bonjour nigga");
    DWORD process = getprocess(L"ac_client.exe"); // grabbing ac_client.exe;
	HANDLE hProc = OpenProcess(PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ, FALSE, process); // grant access to make sure we cant read and write shit
	int32_t gameVer;
	ReadProcessMemory(hProc, (LPVOID)offsets::g_GameVersion, &gameVer, 4, NULL);

	if (gameVer != 1202)
	{
		std::cout << "[ - ] Unsupported game version detected. Please use version 1202.\n";
		std::cin.get();
	}

	std::cout << "[ + ] Loading Hack...\n";



	using namespace variables;

	ReadProcessMemory(hProc, (LPVOID)(offsets::OffsetLocalPlayer + offsets::BaseAddress), &localPlayer, 4, NULL); // reading local player
	ReadProcessMemory(hProc, (LPVOID)(localPlayer + offsets::m_Speed), &plrSpeed, 4, NULL);
	ReadProcessMemory(hProc, (LPVOID)(localPlayer + offsets::health), &plrHealth, 4, NULL);
	ReadProcessMemory(hProc, (LPVOID)(localPlayer + offsets::i_Ammo), &plrAmmo, 4, NULL);
	ReadProcessMemory(hProc, (LPVOID)(localPlayer + offsets::m_Flashbangs), &plrGreandes, 4, NULL);
	ReadProcessMemory(hProc, (LPVOID)(localPlayer + offsets::m_SecAmmo), &plrSecondaryAmmo, 4, NULL);
	ReadProcessMemory(hProc, (LPVOID)(localPlayer + offsets::m_Vest), &plrVestHealth, 4, NULL);
	ReadProcessMemory(hProc, (LPVOID)(localPlayer + offsets::m_AmmoMags), &plrReserveAmmo, 4, NULL);
	ReadProcessMemory(hProc, (LPVOID)(localPlayer + offsets::m_WeaponTimer), &plrWeaponTimer, 4, NULL);

	//1122654640
	//1044381696
	//1114564809

	if (ReadProcessMemory(hProc, (LPVOID)(offsets::OffsetLocalPlayer + offsets::BaseAddress), &localPlayer, 4, NULL))
	{
		std::cout << "[ + ] Loaded 1 / 8 Offsets\n";

		if (ReadProcessMemory(hProc, (LPVOID)(localPlayer + offsets::m_Speed), &plrSpeed, 4, NULL))
		{
			std::cout << "[ + ] Loaded 2 / 8 Offsets\n";

			if (ReadProcessMemory(hProc, (LPVOID)(localPlayer + offsets::health), &plrHealth, 4, NULL))
			{
				std::cout << "[ + ] Loaded 3 / 8 Offsets\n";
				if (ReadProcessMemory(hProc, (LPVOID)(localPlayer + offsets::i_Ammo), &plrAmmo, 4, NULL))
				{
					std::cout << "[ + ] Loaded 4 / 8 Offsets\n";
						
					if (ReadProcessMemory(hProc, (LPVOID)(localPlayer + offsets::m_Flashbangs), &plrGreandes, 4, NULL))
					{
						std::cout << "[ + ] Loaded 4 / 8 Offsets\n";

						if (ReadProcessMemory(hProc, (LPVOID)(localPlayer + offsets::m_SecAmmo), &plrSecondaryAmmo, 4, NULL))
						{
							std::cout << "[ + ] Loaded 5 / 8 Offsets\n";

							if (ReadProcessMemory(hProc, (LPVOID)(localPlayer + offsets::m_Vest), &plrVestHealth, 4, NULL))
							{
								std::cout << "[ + ] Loaded 6 / 8 Offsets\n";

								if (ReadProcessMemory(hProc, (LPVOID)(localPlayer + offsets::m_AmmoMags), &plrReserveAmmo, 4, NULL))
								{
									std::cout << "[ + ] Loaded 7 / 8 Offsets\n";

									if (ReadProcessMemory(hProc, (LPVOID)(localPlayer + offsets::m_WeaponTimer), &plrWeaponTimer, 4, NULL))
									{
										std::cout << "[ + ] Loaded 8 / 8 Offsets\n";
									}
								}
							}
						}
					}
				}
			}
		}
	}
	else
	{
		std::cout << "[ - ] Failed to get localPlayer :(\n";
		std::cin.get();
	}


	std::cout << "\n\n[ + ] Hack Loaded" << "\n[ * ] Press END to unload\n";
	
	int32_t newX = 1122654640;
	int32_t newY = 1044381696;
	int32_t newZ = 1114564809;


	double injected = timer2.elapsed();

	while (!GetAsyncKeyState(VK_END))
	{

		WriteProcessMemory(hProc, (LPVOID)(localPlayer + offsets::health), &newHealth, 4, NULL);
		WriteProcessMemory(hProc, (LPVOID)(localPlayer + offsets::i_Ammo), &newAmmo, 4, NULL);
		WriteProcessMemory(hProc, (LPVOID)(localPlayer + offsets::m_Flashbangs), &newGrenades, 4, NULL);
		WriteProcessMemory(hProc, (LPVOID)(localPlayer + offsets::m_SecAmmo), &newSecAmmo, 4, NULL);
		WriteProcessMemory(hProc, (LPVOID)(localPlayer + offsets::m_Vest), &newVestHealth, 4, NULL);
		WriteProcessMemory(hProc, (LPVOID)(localPlayer + offsets::m_AmmoMags), &newResAmmo, 4, NULL);

		if (GetAsyncKeyState('F'))
		{
			WriteProcessMemory(hProc, (LPVOID)(localPlayer + offsets::m_XPos), &newX, 4, NULL);
			WriteProcessMemory(hProc, (LPVOID)(localPlayer + offsets::m_YPos), &newY, 4, NULL);
			WriteProcessMemory(hProc, (LPVOID)(localPlayer + offsets::m_ZPos), &newZ, 4, NULL);
		}
	}

	Timer timer3;

	WriteProcessMemory(hProc, (LPVOID)(localPlayer + offsets::m_Speed), &plrSpeed, 4, NULL);
	WriteProcessMemory(hProc, (LPVOID)(localPlayer + offsets::health), &plrHealth, 4, NULL);
	WriteProcessMemory(hProc, (LPVOID)(localPlayer + offsets::i_Ammo), &plrAmmo, 4, NULL);
	WriteProcessMemory(hProc, (LPVOID)(localPlayer + offsets::m_Flashbangs), &plrGreandes, 4, NULL);
	WriteProcessMemory(hProc, (LPVOID)(localPlayer + offsets::m_SecAmmo), &plrSecondaryAmmo, 4, NULL);
	WriteProcessMemory(hProc, (LPVOID)(localPlayer + offsets::m_Vest), &plrVestHealth, 4, NULL);
	WriteProcessMemory(hProc, (LPVOID)(localPlayer + offsets::m_AmmoMags), &plrReserveAmmo, 4, NULL);
	WriteProcessMemory(hProc, (LPVOID)(localPlayer + offsets::m_WeaponTimer), &plrWeaponTimer, 4, NULL);

	std::cout << "[ - ] Hack Unloaded\n";

	std::cout << "\n\n\n[ + ] Hook Time: " << timerressult << "\n";
	std::cout << "[ + ] Load Time: " << injected << "\n";
	double totaltimer = timer1.elapsed();
	std::cout << "[ + ] Total: " << totaltimer;
	CloseHandle(hProc);
	std::cin.get(); // pausing all execution
}