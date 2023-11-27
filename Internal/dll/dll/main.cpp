#include <Windows.h>
#include <cstdint>
#include <thread>
#include <iostream>
#include <cstdlib>
#include <ctime>

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

void InfHealth(const HMODULE instance) noexcept
{
	AllocConsole();
	FILE* pFile;
	freopen_s(&pFile, "CONOUT$", "w", stdout);

	int32_t gameVersion = *reinterpret_cast<int32_t*>(offsets::g_GameVersion);

	if (gameVersion != 1202)
	{
		MessageBoxA(nullptr, "UNSUPPORTED ASSAULT CUBE VERSION!", "ERROR", MB_OK);
		FreeLibraryAndExitThread(instance, 0);
	}


	int32_t oldRecoil = *reinterpret_cast<int32_t*>(offsets::m_MouseShotSensitivity);
	int32_t oldGameSpeed = *reinterpret_cast<int32_t*>(offsets::o_GameSpeed);
	int32_t localPlayer = *reinterpret_cast<int32_t*>(offsets::BaseAddress + offsets::OffsetLocalPlayer);
	int32_t oldHealth = *reinterpret_cast<int32_t*>(localPlayer + offsets::health);
	int32_t oldAmmo = *reinterpret_cast<int32_t*>(localPlayer + offsets::i_Ammo);
	int32_t oldSecAmmo = *reinterpret_cast<int32_t*>(localPlayer + offsets::m_SecAmmo);
	int32_t oldAmmoMags = *reinterpret_cast<int32_t*>(localPlayer + offsets::m_AmmoMags);
	int32_t oldVest = *reinterpret_cast<int32_t*>(localPlayer + offsets::m_Vest);
	int32_t oldFlashBangs = *reinterpret_cast<int32_t*>(localPlayer + offsets::m_Flashbangs);
	int32_t oldSpeed = *reinterpret_cast<int32_t*>(localPlayer + offsets::m_Speed);
	int32_t oldWeaponTimer = *reinterpret_cast<int32_t*>(localPlayer + offsets::m_WeaponTimer);

	int32_t Oldm_XPos = *reinterpret_cast<int32_t*>(localPlayer + offsets::m_XPos);
	int32_t Oldm_ZPos = *reinterpret_cast<int32_t*>(localPlayer + offsets::m_ZPos);
	int32_t Oldm_YPos = *reinterpret_cast<int32_t*>(localPlayer + offsets::m_YPos);

	std::cout << "[ * ] Saved X Cord: " << Oldm_XPos << '\n';
	std::cout << "[ * ] Saved Y Cord: " << Oldm_YPos << '\n';
	std::cout << "[ * ] Saved Z Cord: " << Oldm_ZPos << '\n';
	std::cout << "\n\n";

		std::cout << "[ + ] Successfully grabbed Health: " << oldHealth << "\n";
		std::cout << "[ + ] Successfully grabbed Primary Ammo: " << oldAmmo << "\n";
		std::cout << "[ + ] Successfully grabbed Secondary Ammo: " << oldSecAmmo << "\n";
		std::cout << "[ + ] Successfully grabbed Game Speed: " << oldGameSpeed << "\n";
		std::cout << "[ + ] Successfully grabbed Reserved Ammo: " << oldAmmoMags << "\n";
		std::cout << "[ + ] Successfully grabbed Vest Health: " << oldVest << "\n";
		std::cout << "[ + ] Successfully grabbed Flashbangs: " << oldFlashBangs << "\n";
		std::cout << "[ + ] Successfully grabbed Speed: " << oldSpeed << "\n";
		std::cout << "[ + ] Successfully grabbed Weapon Timer: " << oldWeaponTimer << "\n";
		std::cout << "[ + ] Successfully grabbed Recoil: " << oldRecoil << "\n";
		std::cout << "[ + ] Successfully grabbed Game Version: " << gameVersion << "\n";

		std::cout << "\n\n";

		std::cout << "[ :devhat: ] OFFSET OF HEALTH: 0x" << std::hex << offsets::health << std::dec << '\n';
		std::cout << "[ :devhat: ] OFFSET OF PRIMARY AMMO: 0x" << std::hex << offsets::i_Ammo << std::dec << '\n';
		std::cout << "[ :devhat: ] OFFSET OF SECONDARY AMMO: 0x" << std::hex << offsets::m_SecAmmo << std::dec << '\n';
		std::cout << "[ :devhat: ] OFFSET OF LOCALPLAYER: 0x" << std::hex << offsets::OffsetLocalPlayer << std::dec << '\n';
		std::cout << "[ :devhat: ] OFFSET OF GAMESPEED: 0x" << std::hex << offsets::o_GameSpeed << std::dec << '\n';
		std::cout << "[ :devhat: ] OFFSET OF AMMO MAGS: 0x" << std::hex << offsets::m_AmmoMags << std::dec << '\n';
		std::cout << "[ :devhat: ] OFFSET OF VEST: 0x" << std::hex << offsets::m_Vest << std::dec << '\n';
		std::cout << "[ :devhat: ] OFFSET OF FLASHBANGS: 0x" << std::hex << offsets::m_Flashbangs << std::dec << '\n';
		std::cout << "[ :devhat: ] OFFSET OF SPEED: 0x" << std::hex << offsets::m_Speed << std::dec << '\n';
		std::cout << "[ :devhat: ] OFFSET OF RECOIL: 0x" << std::hex << offsets::m_MouseShotSensitivity << std::dec << '\n';
		std::cout << "[ :devhat: ] OFFSET OF WEAPON TIMER: 0x" << std::hex << offsets::m_WeaponTimer << std::dec << '\n';
		std::cout << "[ :devhat: ] OFFSET OF VIEW X ANGLE: 0x" << std::hex << offsets::m_ViewAngleX << std::dec << '\n';
		std::cout << "[ :devhat: ] OFFSET OF VIEW Y ANGLE: 0x" << std::hex << offsets::m_ViewAngleY << std::dec << '\n';
		std::cout << "[ :devhat: ] OFFSET OF X CORD: 0x" << std::hex << offsets::m_XPos << std::dec << '\n';
		std::cout << "[ :devhat: ] OFFSET OF Y CORD: 0x" << std::hex << offsets::m_YPos << std::dec << '\n';
		std::cout << "[ :devhat: ] OFFSET OF Z CORD: 0x" << std::hex << offsets::m_ZPos << std::dec << '\n';
	

	//if (Oldm_XPos && Oldm_YPos && Oldm_ZPos)
	//{
	//	std::cout << "\n\n";
	//	*reinterpret_cast<int32_t*>(localPlayer + offsets::m_YPos) = 0;
	//	*reinterpret_cast<int32_t*>(localPlayer + offsets::m_XPos) = 0;
	//	*reinterpret_cast<int32_t*>(localPlayer + offsets::m_ZPos) = 0;
	//	std::cout << "Set X Cord to: " << *reinterpret_cast<int32_t*>(localPlayer + offsets::m_XPos) << "\n";
	//	std::cout << "Set Y Cord to: " << *reinterpret_cast<int32_t*>(localPlayer + offsets::m_YPos) << "\n";
	//	std::cout << "Set Z Cord to: " << *reinterpret_cast<int32_t*>(localPlayer + offsets::m_ZPos) << "\n";
	//}

	//if (*reinterpret_cast<int32_t*>(offsets::o_GameSpeed) = 500)
	//{
	//	std::cout << "[ + ] Game Speed Set to 500\n";
	//}

	std::cout << "[ + ] Cheat Loaded | End to unload!\n";
	while (!GetAsyncKeyState(VK_END))
	{
		std::srand(std::time(0));


		*reinterpret_cast<int32_t*>(localPlayer + offsets::health) = 500; //loop health
		*reinterpret_cast<int32_t*>(localPlayer + offsets::i_Ammo) = 10; // loop prim ammo
		*reinterpret_cast<int32_t*>(localPlayer + offsets::m_SecAmmo) = 10; // loop sec ammo
		*reinterpret_cast<int32_t*>(localPlayer + offsets::m_AmmoMags) = 10; // loop reserve ammo
		*reinterpret_cast<int32_t*>(localPlayer + offsets::m_Vest) = 100; // loop vest health;
		*reinterpret_cast<int32_t*>(localPlayer + offsets::m_Flashbangs) = 3; // loop grenades
		*reinterpret_cast<int32_t*>(localPlayer + offsets::m_WeaponTimer) = 2; // weapon timer??? dk what it does but sounds cool ig
		//if (GetAsyncKeyState('W') & 0x8000 || GetAsyncKeyState('A') & 0x8000 || GetAsyncKeyState('S') & 0x8000 || GetAsyncKeyState('D') & 0x8000)
		//{
		//	*reinterpret_cast<int32_t*>(localPlayer + offsets::m_Speed) = 3; // speed bost
		//}
	}
	int32_t newHealth = *reinterpret_cast<int32_t*>(localPlayer + offsets::health) = oldHealth;
	int32_t newAmmo = *reinterpret_cast<int32_t*>(localPlayer + offsets::i_Ammo) = oldAmmo;
	int32_t newSecAmmo = *reinterpret_cast<int32_t*>(localPlayer + offsets::m_SecAmmo) = oldSecAmmo;
	int32_t newAmmoMags = *reinterpret_cast<int32_t*>(localPlayer + offsets::m_AmmoMags) = oldAmmoMags;
	int32_t newVest = *reinterpret_cast<int32_t*>(localPlayer + offsets::m_Vest) = oldVest += 1; // if you set vest to 0 illegally it seems to crash :(
	int32_t newFlashbangs = *reinterpret_cast<int32_t*>(localPlayer + offsets::m_Flashbangs) = oldFlashBangs;
	int32_t newWeaponTimer = *reinterpret_cast<int32_t*>(localPlayer + offsets::m_WeaponTimer) = oldWeaponTimer;
	int32_t newSpeed = *reinterpret_cast<int32_t*>(localPlayer + offsets::m_Speed) = oldSpeed += 1;

	//int32_t newX = *reinterpret_cast<int32_t*>(localPlayer + offsets::m_XPos) = Oldm_XPos;
	//int32_t newY = *reinterpret_cast<int32_t*>(localPlayer + offsets::m_YPos) = Oldm_YPos;
	//int32_t newZ = *reinterpret_cast<int32_t*>(localPlayer + offsets::m_ZPos) = Oldm_ZPos;


	if (newHealth && newAmmo && newSecAmmo && newAmmoMags && newVest && newFlashbangs && newWeaponTimer && oldSpeed)
	{
		std::cout << "[ + ] Reset all modified values to old!\n";
	}


	std::cout << "[ * ] Unloaded Cheat Successfully!\n";
	FreeConsole();

	FreeLibraryAndExitThread(instance, 0);
}

int __stdcall DllMain(const HMODULE instance, const std::uintptr_t reason, const void* reserved)
{
	if (reason == 1)
	{
		DisableThreadLibraryCalls(instance);

		const auto health = CreateThread(
			nullptr,
			0,
			reinterpret_cast<LPTHREAD_START_ROUTINE>(InfHealth), instance, 0, nullptr);

		if (health)
			CloseHandle(health);

	}
	return 1;
}
