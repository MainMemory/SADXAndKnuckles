// SADXAndKnuckles.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "SADXModLoader.h"

static void PlaySegaSonicTeamVoice()
{
	if (SegaLogo_Frames == 1 && SoundManager_ptr == nullptr)
	{
		SoundManager_Load(LoadObject((LoadObj)0, 1, SoundManager_Load));
	}

	if (SegaLogo_Frames != 30)
	{
		return;
	}

	if (SoundManager_ptr != nullptr)
	{
		switch (SegaLogo_Mode)
		{
		case 1:
			VoiceLanguage = 1;
			PlayVoice(166);
			SoundManager_ptr->MainSub(SoundManager_ptr);
			break;

		case 16:
			PlayVoice(164);
			SoundManager_ptr->MainSub(SoundManager_ptr);
			VoiceLanguage = 1;
			break;

		default:
			break;
		}
	}
	else
	{
		PrintDebug("Error initializing Sound Manager.\n");
	}
}


void __declspec(naked) PlaySegaSonicTeamVoice_asm()
{
	__asm
	{
		call DisplayLogoScreen
		add esp, 4
		call PlaySegaSonicTeamVoice
		xor eax, eax
		retn
	}
}

bool __cdecl CheckTailsAI_r()
{
	if (CurrentCharacter == Characters_Tails)
		switch (CurrentLevel)
		{
		case LevelIDs_WindyValley:
		case LevelIDs_Casinopolis:
		case LevelIDs_IceCap:
		case LevelIDs_SkyDeck:
			return false;
		}
	switch (CurrentLevel)
	{
	case LevelIDs_SkyChase1:
	case LevelIDs_SkyChase2:
	case LevelIDs_TwinkleCircuit:
		return false;
	}
	return true;
}

int MenuMusicList[] = {
	MusicIDs_KnucklesTutorial, // title screen
	MusicIDs_KnucklesAppearance, // main menu
	MusicIDs_KnucklesAppearance, // options
	MusicIDs_KnucklesTutorial, // character select
	MusicIDs_KnucklesTutorial, // trial
};

static float xpos = 239.36f;
static float xpos2 = 359.04f;
static float ypos = 123.0f;

void Draw19(int texnum, float x, float y, float z, float scaleX, float scaleY)
{
	x = -110.0f * HorizontalStretch + HorizontalStretch * 359.04f;
	DrawBG(texnum, x, y, z, scaleX, scaleY);
}

void Draw19_2(int texnum, float x, float y, float z, float scaleX, float scaleY)
{
	x = x + HorizontalStretch * 359.04f;
	y = 0.0f * VerticalStretch + VerticalStretch * 123.0;
	DrawBG(texnum, x, y, z, scaleX, scaleY);
}

extern "C"
{
	__declspec(dllexport) void OnFrame()
	{
		MenuVoice = 3;
	}

	__declspec(dllexport) void Init(const char *path, const HelperFunctions &helperFunctions)
	{
		WriteJump((void*)0x42CCC7, PlaySegaSonicTeamVoice_asm);
		WriteJump((void*)0x42CD2F, PlaySegaSonicTeamVoice_asm);
		WriteData<2>((void*)0x41592D, 0x90u);
		WriteData<2>((void*)0x41593C, 0x90u);
		WriteData<2>((void*)0x415945, 0x90u);
		WriteJump((void*)0x47E7C0, CheckTailsAI_r);
		WriteData((char*)0x47EDBC, (char)Characters_Knuckles);
		WriteData((ObjectFuncPtr*)0x47EDC1, Knuckles_Main);
		WriteData((char*)0x47EDE6, (char)Characters_Knuckles);
		WriteData((ObjectFuncPtr*)0x47DA1C, Knuckles_Main);
		WriteData((int**)0x505997, MenuMusicList);
		WriteCall((void*)0x0050F8DE, Draw19_2);
		WriteCall((void*)0x0050EE31, Draw19);
		WriteData((float**)0x0050ECCC, &xpos2);
		WriteData((float**)0x0050EC62, &xpos);
		WriteData((float**)0x0050F717, &xpos);
		WriteData((float**)0x0050F77F, &xpos2);
		WriteData((float**)0x0050EE16, &ypos);
	}

	__declspec(dllexport) ModInfo SADXModInfo = { ModLoaderVer };
}