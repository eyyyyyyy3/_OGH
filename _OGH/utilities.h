#pragma once
#include <Windows.h>
#include <iostream>
#include <d3dx9.h>
#include "sdk.h"
#include "OFFSETS.h"
#include "NetVarManager.h"

struct Variables
{
	struct SafeData
	{

	}sd;

	WNDPROC oWndProc = NULL;
	LPD3DXFONT pFont = nullptr;
	bool p_open = true;
	bool Menu;
	bool men1 = false;
	bool men2 = true;
	bool ftmemoryreducer = true;
	int w, h;
	int CDELAY = 0;


}var;
class CRender
{
public:

	void DrawF(int X, int Y, ImVec4 Color, int Font, bool Center, char* _Input, ...)
	{
		/* set up buffer */
		char Buffer[1024] = { '\0' };

		/* set up varargs*/
		va_list Args;

		va_start(Args, _Input);
		vsprintf_s(Buffer, _Input, Args);
		va_end(Args);

		size_t Size = strlen(Buffer) + 1;

		/* set up widebuffer*/
		wchar_t* WideBuffer = new wchar_t[Size];

		/* char -> wchar */
		mbstowcs_s(0, WideBuffer, Size, Buffer, Size - 1);

		/* check center */
		int Width = 0, Height = 0;

		if (Center)
		{
			surf->GetTextSize(Font, WideBuffer, Width, Height);
		}

		/* call and draw*/
		surf->DrawSetTextColor((int)(Color.x * 255.0f), (int)(Color.y * 255.0f), (int)(Color.z * 255.0f), (int)(Color.w * 255.0f));
		surf->DrawSetTextFont(Font);
		surf->DrawSetTextPos(X - (Width * .5), Y);
		surf->DrawPrintText(WideBuffer, wcslen(WideBuffer));
	}

	void DrawRect(int X, int Y, int W, int H, ImVec4 color)
	{
		surf->DrawSetColor((int)(color.x * 255.0f), (int)(color.y * 255.0f), (int)(color.z * 255.0f), (int)(color.w * 255.0f));
		surf->DrawOutlinedRect(X, Y, X + W, Y + H);
	}

	void DrawFilledRect(int X, int Y, int W, int H, ImVec4 Color)
	{
		surf->DrawSetColor((int)(Color.x * 255.0f), (int)(Color.y * 255.0f), (int)(Color.z * 255.0f), (int)(Color.w * 255.0f));
		surf->DrawFilledRect(X, Y, X + W, Y + H);
	}

	void DrawInlineRect(int X, int Y, int W, int H, ImVec4 color)
	{
		DrawRect(X, Y, W, H, color);
		DrawRect(X + 1, Y + 1, W - 2, H - 2, ImVec4(0, 0, 0, 255));
		DrawRect(X - 1, Y - 1, W + 2, H + 2, ImVec4(0, 0, 0, 255));
	}

	void DrawShadowText(int X, int Y, ImVec4 color, int Font, bool Center, char* _Input, ...)
	{
		DrawF(X + 1, Y + 1, ImVec4(0, 0, 0, 150), Font, Center, _Input);
		DrawF(X, Y, color, Font, Center, _Input);
	}

};
CRender* g_pRender;


void GetNetVars()
{
	nvm	->Initialize();
	off.DT_BasePlayer.m_Local = nvm->GetOffset("DT_BasePlayer", "m_Local");
	off.DT_BasePlayer.m_aimPunchAngle = nvm->GetOffset("DT_BasePlayer", "m_aimPunchAngle");
	off.DT_BasePlayer.m_aimPunchAngleVel = nvm->GetOffset("DT_BasePlayer", "m_aimPunchAngleVel");
	off.DT_BasePlayer.m_viewPunchAngle = nvm->GetOffset("DT_BasePlayer", "m_viewPunchAngle");
	off.DT_BasePlayer.m_vecViewOffset = nvm->GetOffset("DT_BasePlayer", "m_vecViewOffset[0]");
	off.DT_BasePlayer.m_nTickBase = nvm->GetOffset("DT_BasePlayer", "m_nTickBase");
	off.DT_BasePlayer.m_vecVelocity = nvm->GetOffset("DT_BasePlayer", "m_vecVelocity[0]");
	off.DT_BasePlayer.m_iHealth = nvm->GetOffset("DT_BasePlayer", "m_iHealth");
	off.DT_BasePlayer.m_iMaxHealth = nvm->GetOffset("DT_BasePlayer", "m_iMaxHealth");
	off.DT_BasePlayer.m_lifeState = nvm->GetOffset("DT_BasePlayer", "m_lifeState");
	off.DT_BasePlayer.m_fFlags = nvm->GetOffset("DT_BasePlayer", "m_fFlags");
	off.DT_BasePlayer.m_iObserverMode = nvm->GetOffset("DT_BasePlayer", "m_iObserverMode");
	off.DT_BasePlayer.m_hObserverTarget = nvm->GetOffset("DT_BasePlayer", "m_hObserverTarget");
	off.DT_BasePlayer.m_hViewModel = nvm->GetOffset("DT_BasePlayer", "m_hViewModel[0]");
	off.DT_BasePlayer.m_szLastPlaceName = nvm->GetOffset("DT_BasePlayer", "m_szLastPlaceName");
	off.DT_BasePlayer.deadflag = nvm->GetOffset("DT_BasePlayer", "deadflag");

	off.DT_BaseEntity.m_flAnimTime = nvm->GetOffset("DT_BaseEntity", "m_flAnimTime");
	off.DT_BaseEntity.m_flSimulationTime = nvm->GetOffset("DT_BaseEntity", "m_flSimulationTime");
	off.DT_BaseEntity.m_vecOrigin = nvm->GetOffset("DT_BaseEntity", "m_vecOrigin");
	off.DT_BaseEntity.m_angRotation = nvm->GetOffset("DT_BaseEntity", "m_angRotation");
	off.DT_BaseEntity.m_nRenderMode = nvm->GetOffset("DT_BaseEntity", "m_nRenderMode");
	off.DT_BaseEntity.m_iTeamNum = nvm->GetOffset("DT_BaseEntity", "m_iTeamNum");
	off.DT_BaseEntity.m_MoveType = off.DT_BaseEntity.m_nRenderMode + 1;
	off.DT_BaseEntity.m_Collision = nvm->GetOffset("DT_BaseEntity", "m_Collision");
	off.DT_BaseEntity.m_hOwner = nvm->GetOffset("DT_BaseEntity", "m_hOwner");
	off.DT_BaseEntity.m_bSpotted = nvm->GetOffset("DT_BaseEntity", "m_bSpotted");
	off.DT_BaseEntity.m_bIsAutoaimTarget = nvm->GetOffset("DT_BaseEntity", "m_bIsAutoaimTarget");
	off.DT_BaseEntity.m_vecMins = nvm->GetOffset("DT_BaseEntity", "m_vecMins");
	off.DT_BaseEntity.m_vecMaxs = nvm->GetOffset("DT_BaseEntity", "m_vecMaxs");
	off.DT_BaseEntity.m_nSolidType = nvm->GetOffset("DT_BaseEntity", "m_nSolidType");
	off.DT_BaseEntity.m_usSolidFlags = nvm->GetOffset("DT_BaseEntity", "m_usSolidFlags");
	off.DT_BaseEntity.m_nSurroundType = nvm->GetOffset("DT_BaseEntity", "m_nSurroundType");


	off.DT_BaseCombatCharacter.m_hActiveWeapon = nvm->GetOffset("DT_BaseCombatCharacter", "m_hActiveWeapon");
	off.DT_BaseCombatCharacter.m_hMyWeapons = nvm->GetOffset("DT_BaseCombatCharacter", "m_hMyWeapons") / 2;
	off.DT_BaseCombatCharacter.m_hMyWearables = nvm->GetOffset("DT_BaseCombatCharacter", "m_hMyWearables");

	off.DT_PlayerResource.m_iPing = nvm->GetOffset("DT_PlayerResource", "m_iPing");
	off.DT_PlayerResource.m_iKills = nvm->GetOffset("DT_PlayerResource", "m_iKills");
	off.DT_PlayerResource.m_iAssists = nvm->GetOffset("DT_PlayerResource", "m_iAssists");
	off.DT_PlayerResource.m_iDeaths = nvm->GetOffset("DT_PlayerResource", "m_iDeaths");
	off.DT_PlayerResource.m_bConnected = nvm->GetOffset("DT_PlayerResource", "m_bConnected");
	off.DT_PlayerResource.m_iTeam = nvm->GetOffset("DT_PlayerResource", "m_iTeam");
	off.DT_PlayerResource.m_iPendingTeam = nvm->GetOffset("DT_PlayerResource", "m_iPendingTeam");
	off.DT_PlayerResource.m_bAlive = nvm->GetOffset("DT_PlayerResource", "m_bAlive");
	off.DT_PlayerResource.m_iHealth = nvm->GetOffset("DT_PlayerResource", "m_iHealth");

	off.DT_CSPlayerResource.m_iPlayerC4 = nvm->GetOffset("DT_CSPlayerResource", "m_iPlayerC4");
	off.DT_CSPlayerResource.m_iPlayerVIP = nvm->GetOffset("DT_CSPlayerResource", "m_iPlayerVIP");
	off.DT_CSPlayerResource.m_bHostageAlive = nvm->GetOffset("DT_CSPlayerResource", "m_bHostageAlive");
	off.DT_CSPlayerResource.m_isHostageFollowingSomeone = nvm->GetOffset("DT_CSPlayerResource", "m_isHostageFollowingSomeone");
	off.DT_CSPlayerResource.m_iHostageEntityIDs = nvm->GetOffset("DT_CSPlayerResource", "m_iHostageEntityIDs");
	off.DT_CSPlayerResource.m_bombsiteCenterB = nvm->GetOffset("DT_CSPlayerResource", "m_bombsiteCenterB");
	off.DT_CSPlayerResource.m_hostageRescueX = nvm->GetOffset("DT_CSPlayerResource", "m_hostageRescueX");
	off.DT_CSPlayerResource.m_hostageRescueY = nvm->GetOffset("DT_CSPlayerResource", "m_hostageRescueY");
	off.DT_CSPlayerResource.m_hostageRescueZ = nvm->GetOffset("DT_CSPlayerResource", "m_hostageRescueZ");
	off.DT_CSPlayerResource.m_iMVPs = nvm->GetOffset("DT_CSPlayerResource", "m_iMVPs");
	off.DT_CSPlayerResource.m_iArmor = nvm->GetOffset("DT_CSPlayerResource", "m_iArmor");
	off.DT_CSPlayerResource.m_bHasHelmet = nvm->GetOffset("DT_CSPlayerResource", "m_bHasHelmet");
	off.DT_CSPlayerResource.m_bHasDefuser = nvm->GetOffset("DT_CSPlayerResource", "m_bHasDefuser");
	off.DT_CSPlayerResource.m_iScore = nvm->GetOffset("DT_CSPlayerResource", "m_iScore");
	off.DT_CSPlayerResource.m_iCompetitiveRanking = nvm->GetOffset("DT_CSPlayerResource", "m_iCompetitiveRanking");
	off.DT_CSPlayerResource.m_iCompetitiveWins = nvm->GetOffset("DT_CSPlayerResource", "m_iCompetitiveWins");
	off.DT_CSPlayerResource.m_iCompTeammateColor = nvm->GetOffset("DT_CSPlayerResource", "m_iCompTeammateColor");
	off.DT_CSPlayerResource.m_bControllingBot = nvm->GetOffset("DT_CSPlayerResource", "m_bControllingBot");
	off.DT_CSPlayerResource.m_iControlledPlayer = nvm->GetOffset("DT_CSPlayerResource", "m_iControlledPlayer");
	off.DT_CSPlayerResource.m_iControlledByPlayer = nvm->GetOffset("DT_CSPlayerResource", "m_iControlledByPlayer");
	off.DT_CSPlayerResource.m_iBotDifficulty = nvm->GetOffset("DT_CSPlayerResource", "m_iBotDifficulty");
	off.DT_CSPlayerResource.m_szClan = nvm->GetOffset("DT_CSPlayerResource", "m_szClan");
	off.DT_CSPlayerResource.m_iTotalCashSpent = nvm->GetOffset("DT_CSPlayerResource", "m_iTotalCashSpent");
	off.DT_CSPlayerResource.m_iCashSpentThisRound = nvm->GetOffset("DT_CSPlayerResource", "m_iCashSpentThisRound");
	off.DT_CSPlayerResource.m_nEndMatchNextMapVotes = nvm->GetOffset("DT_CSPlayerResource", "m_nEndMatchNextMapVotes");
	off.DT_CSPlayerResource.m_bEndMatchNextMapAllVoted = nvm->GetOffset("DT_CSPlayerResource", "m_bEndMatchNextMapAllVoted");
	off.DT_CSPlayerResource.m_nActiveCoinRank = nvm->GetOffset("DT_CSPlayerResource", "m_nActiveCoinRank");
	off.DT_CSPlayerResource.m_nMusicID = nvm->GetOffset("DT_CSPlayerResource", "m_nMusicID");
	off.DT_CSPlayerResource.m_nPersonaDataPublicLevel = nvm->GetOffset("DT_CSPlayerResource", "m_nPersonaDataPublicLevel");
	off.DT_CSPlayerResource.m_nPersonaDataPublicCommendsLeader = nvm->GetOffset("DT_CSPlayerResource", "m_nPersonaDataPublicCommendsLeader");
	off.DT_CSPlayerResource.m_nPersonaDataPublicCommendsTeacher = nvm->GetOffset("DT_CSPlayerResource", "m_nPersonaDataPublicCommendsTeacher");
	off.DT_CSPlayerResource.m_nPersonaDataPublicCommendsFriendly = nvm->GetOffset("DT_CSPlayerResource", "m_nPersonaDataPublicCommendsFriendly");

	off.DT_PlantedC4.m_bBombTicking = nvm->GetOffset("DT_PlantedC4", "m_bBombTicking");
	off.DT_PlantedC4.m_flC4Blow = nvm->GetOffset("DT_PlantedC4", "m_flC4Blow");
	off.DT_PlantedC4.m_bBombDefused = nvm->GetOffset("DT_PlantedC4", "m_bBombDefused");
	off.DT_PlantedC4.m_hBombDefuser = nvm->GetOffset("DT_PlantedC4", "m_hBombDefuser");
	off.DT_PlantedC4.m_flDefuseCountDown = nvm->GetOffset("DT_PlantedC4", "m_flDefuseCountDown");

	off.DT_CSPlayer.m_iShotsFired = nvm->GetOffset("DT_CSPlayer", "m_iShotsFired");
	off.DT_CSPlayer.m_angEyeAngles[0] = nvm->GetOffset("DT_CSPlayer", "m_angEyeAngles[0]");
	off.DT_CSPlayer.m_angEyeAngles[1] = nvm->GetOffset("DT_CSPlayer", "m_angEyeAngles[1]");
	off.DT_CSPlayer.m_iAccount = nvm->GetOffset("DT_CSPlayer", "m_iAccount");
	off.DT_CSPlayer.m_totalHitsOnServer = nvm->GetOffset("DT_CSPlayer", "m_totalHitsOnServer");
	off.DT_CSPlayer.m_ArmorValue = nvm->GetOffset("DT_CSPlayer", "m_ArmorValue");
	off.DT_CSPlayer.m_bIsDefusing = nvm->GetOffset("DT_CSPlayer", "m_bIsDefusing");
	off.DT_CSPlayer.m_bIsGrabbingHostage = nvm->GetOffset("DT_CSPlayer", "m_bIsGrabbingHostage");
	off.DT_CSPlayer.m_bIsScoped = nvm->GetOffset("DT_CSPlayer", "m_bIsScoped");
	off.DT_CSPlayer.m_bGunGameImmunity = nvm->GetOffset("DT_CSPlayer", "m_bGunGameImmunity");
	off.DT_CSPlayer.m_bIsRescuing = nvm->GetOffset("DT_CSPlayer", "m_bIsRescuing");
	off.DT_CSPlayer.m_bHasHelmet = nvm->GetOffset("DT_CSPlayer", "m_bHasHelmet");
	off.DT_CSPlayer.m_bHasDefuser = nvm->GetOffset("DT_CSPlayer", "m_bHasDefuser");
	off.DT_CSPlayer.m_flFlashDuration = nvm->GetOffset("DT_CSPlayer", "m_flFlashDuration");
	off.DT_CSPlayer.m_flFlashMaxAlpha = nvm->GetOffset("DT_CSPlayer", "m_flFlashMaxAlpha");
	off.DT_CSPlayer.m_flLowerBodyYawTarget = nvm->GetOffset("DT_CSPlayer", "m_flLowerBodyYawTarget");
	off.DT_CSPlayer.m_bHasHeavyArmor = nvm->GetOffset("DT_CSPlayer", "m_bHasHeavyArmor");
	off.DT_CSPlayer.m_iGunGameProgressiveWeaponIndex = nvm->GetOffset("DT_CSPlayer", "m_iGunGameProgressiveWeaponIndex");

	off.DT_BaseAttributableItem.m_iItemDefinitionIndex = nvm->GetOffset("DT_BaseAttributableItem", "m_iItemDefinitionIndex");
	off.DT_BaseAttributableItem.m_iAccountID = nvm->GetOffset("DT_BaseAttributableItem", "m_iAccountID");
	off.DT_BaseAttributableItem.m_iEntityQuality = nvm->GetOffset("DT_BaseAttributableItem", "m_iEntityQuality");
	off.DT_BaseAttributableItem.m_szCustomName = nvm->GetOffset("DT_BaseAttributableItem", "m_szCustomName");
	off.DT_BaseAttributableItem.m_nFallbackPaintKit = nvm->GetOffset("DT_BaseAttributableItem", "m_nFallbackPaintKit");
	off.DT_BaseAttributableItem.m_nFallbackSeed = nvm->GetOffset("DT_BaseAttributableItem", "m_nFallbackSeed");
	off.DT_BaseAttributableItem.m_flFallbackWear = nvm->GetOffset("DT_BaseAttributableItem", "m_flFallbackWear");
	off.DT_BaseAttributableItem.m_nFallbackStatTrak = nvm->GetOffset("DT_BaseAttributableItem", "m_nFallbackStatTrak");
	off.DT_BaseAttributableItem.m_OriginalOwnerXuidLow = nvm->GetOffset("DT_BaseAttributableItem", "m_OriginalOwnerXuidLow");
	off.DT_BaseAttributableItem.m_OriginalOwnerXuidHigh = nvm->GetOffset("DT_BaseAttributableItem", "m_OriginalOwnerXuidHigh");
	off.DT_BaseAttributableItem.m_iItemIDLow = nvm->GetOffset("DT_BaseAttributableItem", "m_iItemIDLow");
	off.DT_BaseAttributableItem.m_iItemIDHigh = nvm->GetOffset("DT_BaseAttributableItem", "m_iItemIDHigh");


	off.DT_BaseViewModel.m_nModelIndex = nvm->GetOffset("DT_BaseViewModel", "m_nModelIndex");
	off.DT_BaseViewModel.m_hWeapon = nvm->GetOffset("DT_BaseViewModel", "m_hWeapon");
	off.DT_BaseViewModel.m_hOwner = nvm->GetOffset("DT_BaseViewModel", "m_hOwner");

	off.DT_WeaponCSBase.m_fAccuracyPenalty = nvm->GetOffset("DT_WeaponCSBase", "m_fAccuracyPenalty");
	off.DT_WeaponCSBase.m_flPostponeFireReadyTime = nvm->GetOffset("DT_WeaponCSBase", "m_flPostponeFireReadyTime");

	off.DT_WeaponC4.m_bStartedArming = nvm->GetOffset("DT_WeaponC4", "m_bStartedArming");

	off.DT_BaseCombatWeapon.m_flNextPrimaryAttack = nvm->GetOffset("DT_BaseCombatWeapon", "m_flNextPrimaryAttack");
	off.DT_BaseCombatWeapon.m_iViewModelIndex = nvm->GetOffset("DT_BaseCombatWeapon", "m_iViewModelIndex");
	off.DT_BaseCombatWeapon.m_iWorldModelIndex = nvm->GetOffset("DT_BaseCombatWeapon", "m_iWorldModelIndex");
	off.DT_BaseCombatWeapon.m_hOwner = nvm->GetOffset("DT_BaseCombatWeapon", "m_hOwner");
	off.DT_BaseCombatWeapon.m_iClip1 = nvm->GetOffset("DT_BaseCombatWeapon", "m_iClip1");
	off.DT_BaseCombatWeapon.m_iReserve = nvm->GetOffset("DT_BaseCombatWeapon", "m_iPrimaryReserveAmmoCount");
	off.DT_BaseCombatWeapon.m_bInReload = off.DT_BaseCombatWeapon.m_flNextPrimaryAttack + 113;
	off.DT_BaseCombatWeapon.m_hWeaponWorldModel = nvm->GetOffset("DT_BaseCombatWeapon", "m_hWeaponWorldModel");


	off.DT_BaseCSGrenade.m_bRedraw = nvm->GetOffset("DT_BaseCSGrenade", "m_bRedraw");
	off.DT_BaseCSGrenade.m_bIsHeldByPlayer = nvm->GetOffset("DT_BaseCSGrenade", "m_bIsHeldByPlayer");
	off.DT_BaseCSGrenade.m_bPinPulled = nvm->GetOffset("DT_BaseCSGrenade", "m_bPinPulled");
	off.DT_BaseCSGrenade.m_fThrowTime = nvm->GetOffset("DT_BaseCSGrenade", "m_fThrowTime");
	off.DT_BaseCSGrenade.m_bLoopingSoundPlaying = nvm->GetOffset("DT_BaseCSGrenade", "m_bLoopingSoundPlaying");
	off.DT_BaseCSGrenade.m_flThrowStrength = nvm->GetOffset("DT_BaseCSGrenade", "m_flThrowStrength");

	off.DT_DynamicProp.m_bShouldGlow = nvm->GetOffset("DT_DynamicProp", "m_bShouldGlow");

	off.DT_CSGameRulesProxy.m_bBombPlanted = nvm->GetOffset("DT_CSGameRulesProxy", "m_bBombPlanted");
	off.DT_CSGameRulesProxy.m_bIsValveDS = nvm->GetOffset("DT_CSGameRulesProxy", "m_bIsValveDS");

	off.DT_CSGameRulesProxy.m_bFreezePeriod = nvm->GetOffset("DT_CSGameRulesProxy", "m_bFreezePeriod");
	off.DT_CSGameRulesProxy.m_bMatchWaitingForResume = nvm->GetOffset("DT_CSGameRulesProxy", "m_bMatchWaitingForResume");
	off.DT_CSGameRulesProxy.m_bWarmupPeriod = nvm->GetOffset("DT_CSGameRulesProxy", "m_bWarmupPeriod");
	off.DT_CSGameRulesProxy.m_fWarmupPeriodEnd = nvm->GetOffset("DT_CSGameRulesProxy", "m_fWarmupPeriodEnd");
	off.DT_CSGameRulesProxy.m_fWarmupPeriodStart = nvm->GetOffset("DT_CSGameRulesProxy", "m_fWarmupPeriodStart");
	off.DT_CSGameRulesProxy.m_bTerroristTimeOutActive = nvm->GetOffset("DT_CSGameRulesProxy", "m_bTerroristTimeOutActive");
	off.DT_CSGameRulesProxy.m_bCTTimeOutActive = nvm->GetOffset("DT_CSGameRulesProxy", "m_bCTTimeOutActive");
	off.DT_CSGameRulesProxy.m_flTerroristTimeOutRemaining = nvm->GetOffset("DT_CSGameRulesProxy", "m_flTerroristTimeOutRemaining");
	off.DT_CSGameRulesProxy.m_flCTTimeOutRemaining = nvm->GetOffset("DT_CSGameRulesProxy", "m_flCTTimeOutRemaining");
	off.DT_CSGameRulesProxy.m_nTerroristTimeOuts = nvm->GetOffset("DT_CSGameRulesProxy", "m_nTerroristTimeOuts");
	off.DT_CSGameRulesProxy.m_nCTTimeOuts = nvm->GetOffset("DT_CSGameRulesProxy", "m_nCTTimeOuts");
	off.DT_CSGameRulesProxy.m_iRoundTime = nvm->GetOffset("DT_CSGameRulesProxy", "m_iRoundTime");
	off.DT_CSGameRulesProxy.m_gamePhase = nvm->GetOffset("DT_CSGameRulesProxy", "m_gamePhase");
	off.DT_CSGameRulesProxy.m_totalRoundsPlayed = nvm->GetOffset("DT_CSGameRulesProxy", "m_totalRoundsPlayed");
	off.DT_CSGameRulesProxy.m_nOvertimePlaying = nvm->GetOffset("DT_CSGameRulesProxy", "m_nOvertimePlaying");
	off.DT_CSGameRulesProxy.m_timeUntilNextPhaseStarts = nvm->GetOffset("DT_CSGameRulesProxy", "m_timeUntilNextPhaseStarts");
	off.DT_CSGameRulesProxy.m_flCMMItemDropRevealStartTime = nvm->GetOffset("DT_CSGameRulesProxy", "m_flCMMItemDropRevealStartTime");
	off.DT_CSGameRulesProxy.m_flCMMItemDropRevealEndTime = nvm->GetOffset("DT_CSGameRulesProxy", "m_flCMMItemDropRevealEndTime");
	off.DT_CSGameRulesProxy.m_fRoundStartTime = nvm->GetOffset("DT_CSGameRulesProxy", "m_fRoundStartTime");
	off.DT_CSGameRulesProxy.m_bGameRestart = nvm->GetOffset("DT_CSGameRulesProxy", "m_bGameRestart");
	off.DT_CSGameRulesProxy.m_flRestartRoundTime = nvm->GetOffset("DT_CSGameRulesProxy", "m_flRestartRoundTime");
	off.DT_CSGameRulesProxy.m_flGameStartTime = nvm->GetOffset("DT_CSGameRulesProxy", "m_flGameStartTime");
	off.DT_CSGameRulesProxy.m_iHostagesRemaining = nvm->GetOffset("DT_CSGameRulesProxy", "m_iHostagesRemaining");
	off.DT_CSGameRulesProxy.m_bAnyHostageReached = nvm->GetOffset("DT_CSGameRulesProxy", "m_bAnyHostageReached");
	off.DT_CSGameRulesProxy.m_bMapHasBombTarget = nvm->GetOffset("DT_CSGameRulesProxy", "m_bMapHasBombTarget");
	off.DT_CSGameRulesProxy.m_bMapHasRescueZone = nvm->GetOffset("DT_CSGameRulesProxy", "m_bMapHasRescueZone");
	off.DT_CSGameRulesProxy.m_bMapHasBuyZone = nvm->GetOffset("DT_CSGameRulesProxy", "m_bMapHasBuyZone");
	off.DT_CSGameRulesProxy.m_bIsQueuedMatchmaking = nvm->GetOffset("DT_CSGameRulesProxy", "m_bIsQueuedMatchmaking");
	off.DT_CSGameRulesProxy.m_bIsValveDS = nvm->GetOffset("DT_CSGameRulesProxy", "m_bIsValveDS");
	off.DT_CSGameRulesProxy.m_bIsQuestEligible = nvm->GetOffset("DT_CSGameRulesProxy", "m_bIsQuestEligible");
	off.DT_CSGameRulesProxy.m_bLogoMap = nvm->GetOffset("DT_CSGameRulesProxy", "m_bLogoMap");
	off.DT_CSGameRulesProxy.m_iNumGunGameProgressiveWeaponsCT = nvm->GetOffset("DT_CSGameRulesProxy", "m_iNumGunGameProgressiveWeaponsCT");
	off.DT_CSGameRulesProxy.m_iNumGunGameProgressiveWeaponsT = nvm->GetOffset("DT_CSGameRulesProxy", "m_iNumGunGameProgressiveWeaponsT");
	off.DT_CSGameRulesProxy.m_iSpectatorSlotCount = nvm->GetOffset("DT_CSGameRulesProxy", "m_iSpectatorSlotCount");
	off.DT_CSGameRulesProxy.m_bBombDropped = nvm->GetOffset("DT_CSGameRulesProxy", "m_bBombDropped");
	off.DT_CSGameRulesProxy.m_bBombPlanted = nvm->GetOffset("DT_CSGameRulesProxy", "m_bBombPlanted");
	off.DT_CSGameRulesProxy.m_iRoundWinStatus = nvm->GetOffset("DT_CSGameRulesProxy", "m_iRoundWinStatus");
	off.DT_CSGameRulesProxy.m_eRoundWinReason = nvm->GetOffset("DT_CSGameRulesProxy", "m_eRoundWinReason");
	off.DT_CSGameRulesProxy.m_flDMBonusStartTime = nvm->GetOffset("DT_CSGameRulesProxy", "m_flDMBonusStartTime");
	off.DT_CSGameRulesProxy.m_flDMBonusTimeLength = nvm->GetOffset("DT_CSGameRulesProxy", "m_flDMBonusTimeLength");
	off.DT_CSGameRulesProxy.m_unDMBonusWeaponLoadoutSlot = nvm->GetOffset("DT_CSGameRulesProxy", "m_unDMBonusWeaponLoadoutSlot");
	off.DT_CSGameRulesProxy.m_bDMBonusActive = nvm->GetOffset("DT_CSGameRulesProxy", "m_bDMBonusActive");
	off.DT_CSGameRulesProxy.m_bTCantBuy = nvm->GetOffset("DT_CSGameRulesProxy", "m_bTCantBuy");
	off.DT_CSGameRulesProxy.m_bCTCantBuy = nvm->GetOffset("DT_CSGameRulesProxy", "m_bCTCantBuy");
	off.DT_CSGameRulesProxy.m_flGuardianBuyUntilTime = nvm->GetOffset("DT_CSGameRulesProxy", "m_flGuardianBuyUntilTime");
	off.DT_CSGameRulesProxy.m_iMatchStats_RoundResults = nvm->GetOffset("DT_CSGameRulesProxy", "m_iMatchStats_RoundResults");
	off.DT_CSGameRulesProxy.m_iMatchStats_PlayersAlive_T = nvm->GetOffset("DT_CSGameRulesProxy", "m_iMatchStats_PlayersAlive_T");
	off.DT_CSGameRulesProxy.m_iMatchStats_PlayersAlive_CT = nvm->GetOffset("DT_CSGameRulesProxy", "m_iMatchStats_PlayersAlive_CT");
	off.DT_CSGameRulesProxy.m_GGProgressiveWeaponOrderC = nvm->GetOffset("DT_CSGameRulesProxy", "m_GGProgressiveWeaponOrderC");
	off.DT_CSGameRulesProxy.m_GGProgressiveWeaponOrderT = nvm->GetOffset("DT_CSGameRulesProxy", "m_GGProgressiveWeaponOrderT");
	off.DT_CSGameRulesProxy.m_GGProgressiveWeaponKillUpgradeOrderCT = nvm->GetOffset("DT_CSGameRulesProxy", "m_GGProgressiveWeaponKillUpgradeOrderCT");
	off.DT_CSGameRulesProxy.m_GGProgressiveWeaponKillUpgradeOrderT = nvm->GetOffset("DT_CSGameRulesProxy", "m_GGProgressiveWeaponKillUpgradeOrderT");
	off.DT_CSGameRulesProxy.m_MatchDevice = nvm->GetOffset("DT_CSGameRulesProxy", "m_MatchDevice");
	off.DT_CSGameRulesProxy.m_bHasMatchStarted = nvm->GetOffset("DT_CSGameRulesProxy", "m_bHasMatchStarted");
	off.DT_CSGameRulesProxy.m_TeamRespawnWaveTimes = nvm->GetOffset("DT_CSGameRulesProxy", "m_TeamRespawnWaveTimes");
	off.DT_CSGameRulesProxy.m_flNextRespawnWave = nvm->GetOffset("DT_CSGameRulesProxy", "m_flNextRespawnWave");
	off.DT_CSGameRulesProxy.m_nNextMapInMapgroup = nvm->GetOffset("DT_CSGameRulesProxy", "m_nNextMapInMapgroup");
	off.DT_CSGameRulesProxy.m_nEndMatchMapGroupVoteOptions = nvm->GetOffset("DT_CSGameRulesProxy", "m_nEndMatchMapGroupVoteOptions");
	off.DT_CSGameRulesProxy.m_bIsDroppingItems = nvm->GetOffset("DT_CSGameRulesProxy", "m_bIsDroppingItems");
	off.DT_CSGameRulesProxy.m_iActiveAssassinationTargetMissionID = nvm->GetOffset("DT_CSGameRulesProxy", "m_iActiveAssassinationTargetMissionID");
	off.DT_CSGameRulesProxy.m_fMatchStartTime = nvm->GetOffset("DT_CSGameRulesProxy", "m_fMatchStartTime");
	off.DT_CSGameRulesProxy.m_szTournamentEventName = nvm->GetOffset("DT_CSGameRulesProxy", "m_szTournamentEventName");
	off.DT_CSGameRulesProxy.m_szTournamentEventStage = nvm->GetOffset("DT_CSGameRulesProxy", "m_szTournamentEventStage");
	off.DT_CSGameRulesProxy.m_szTournamentPredictionsTxt = nvm->GetOffset("DT_CSGameRulesProxy", "m_szTournamentPredictionsTxt");
	off.DT_CSGameRulesProxy.m_nTournamentPredictionsPct = nvm->GetOffset("DT_CSGameRulesProxy", "m_nTournamentPredictionsPct");
	off.DT_CSGameRulesProxy.m_szMatchStatTxt = nvm->GetOffset("DT_CSGameRulesProxy", "m_szMatchStatTxt");
	off.DT_CSGameRulesProxy.m_nGuardianModeWaveNumber = nvm->GetOffset("DT_CSGameRulesProxy", "m_nGuardianModeWaveNumber");
	off.DT_CSGameRulesProxy.m_nGuardianModeSpecialKillsRemaining = nvm->GetOffset("DT_CSGameRulesProxy", "m_nGuardianModeSpecialKillsRemaining");
	off.DT_CSGameRulesProxy.m_nGuardianModeSpecialWeaponNeeded = nvm->GetOffset("DT_CSGameRulesProxy", "m_nGuardianModeSpecialWeaponNeeded");
	off.DT_CSGameRulesProxy.m_nHalloweenMaskListSeed = nvm->GetOffset("DT_CSGameRulesProxy", "m_nHalloweenMaskListSeed");
	off.DT_CSGameRulesProxy.m_numGlobalGiftsGiven = nvm->GetOffset("DT_CSGameRulesProxy", "m_numGlobalGiftsGiven");
	off.DT_CSGameRulesProxy.m_numGlobalGifters = nvm->GetOffset("DT_CSGameRulesProxy", "m_numGlobalGifters");
	off.DT_CSGameRulesProxy.m_numGlobalGiftsPeriodSeconds = nvm->GetOffset("DT_CSGameRulesProxy", "m_numGlobalGiftsPeriodSeconds");
	off.DT_CSGameRulesProxy.m_arrFeaturedGiftersAccounts = nvm->GetOffset("DT_CSGameRulesProxy", "m_arrFeaturedGiftersAccounts");
	off.DT_CSGameRulesProxy.m_arrFeaturedGiftersGifts = nvm->GetOffset("DT_CSGameRulesProxy", "m_arrFeaturedGiftersGifts");
	off.DT_CSGameRulesProxy.m_arrTournamentActiveCasterAccounts = nvm->GetOffset("DT_CSGameRulesProxy", "m_arrTournamentActiveCasterAccounts");
	off.DT_BaseAnimating.m_nHitboxSet = nvm->GetOffset("DT_BaseAnimating", "m_nHitboxSet");

}

void Updater()
{
	if (eng->IsConnected() && eng->IsInGame() && var.ftmemoryreducer == true)
	{
		me = (BaseEntity*)entlist->GetClientEntity(eng->GetLocalPlayer());
		std:: cout << std::hex << me << std::endl;
		eng->GetScreenSize(var.w, var.h);
		var.ftmemoryreducer = false;
	}

	if (!eng->IsInGame() && var.ftmemoryreducer == false)
	{
		var.ftmemoryreducer = true;
	}

}

static bool ScreenTransform(const Vector& in, Vector& out)
{
	static auto& w2sMatrix = eng->WorldToScreenMatrix();

	out.x = w2sMatrix.m[0][0] * in.x + w2sMatrix.m[0][1] * in.y + w2sMatrix.m[0][2] * in.z + w2sMatrix.m[0][3];
	out.y = w2sMatrix.m[1][0] * in.x + w2sMatrix.m[1][1] * in.y + w2sMatrix.m[1][2] * in.z + w2sMatrix.m[1][3];
	out.z = 0.0f;

	float w = w2sMatrix.m[3][0] * in.x + w2sMatrix.m[3][1] * in.y + w2sMatrix.m[3][2] * in.z + w2sMatrix.m[3][3];

	if (w < 0.001f) {
		out.x *= 100000;
		out.y *= 100000;
		return false;
	}

	out.x /= w;
	out.y /= w;

	return true;
}

bool WorldToScreen(const Vector& origin, Vector& screen)
{
	if (ScreenTransform(origin, screen)) {
		int w, h;
		eng->GetScreenSize(w, h);

		screen.x = (w / 2.0f) + (screen.x * w) / 2.0f;
		screen.y = (h / 2.0f) - (screen.y * h) / 2.0f;

		return true;
	}
	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
