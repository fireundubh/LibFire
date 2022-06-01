#pragma once

#include "PapyrusFaction.h"

namespace PapyrusFaction
{
	auto GetFactionIgnoresMurder(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESFaction* a_faction) -> bool
	{
		if (!a_faction) {
			a_vm->TraceStack("akFaction cannot be None", a_stackID, Severity::kWarning);
			return false;
		}
		return a_faction->IgnoresMurder();
	}

	auto GetFactionIgnoresAssault(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESFaction* a_faction) -> bool
	{
		if (!a_faction) {
			a_vm->TraceStack("akFaction cannot be None", a_stackID, Severity::kWarning);
			return false;
		}
		return a_faction->IgnoresAssault();
	}

	auto GetFactionIgnoresTrespass(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESFaction* a_faction) -> bool
	{
		if (!a_faction) {
			a_vm->TraceStack("akFaction cannot be None", a_stackID, Severity::kWarning);
			return false;
		}
		return a_faction->IgnoresTrespass();
	}

	auto GetFactionIgnoresPickpocket(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESFaction* a_faction) -> bool
	{
		if (!a_faction) {
			a_vm->TraceStack("akFaction cannot be None", a_stackID, Severity::kWarning);
			return false;
		}
		return a_faction->IgnoresPickpocket();
	}

	auto GetFactionIgnoresStealing(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESFaction* a_faction) -> bool
	{
		if (!a_faction) {
			a_vm->TraceStack("akFaction cannot be None", a_stackID, Severity::kWarning);
			return false;
		}
		return a_faction->IgnoresStealing();
	}

	auto GetFactionIgnoresWerewolf(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESFaction* a_faction) -> bool
	{
		if (!a_faction) {
			a_vm->TraceStack("akFaction cannot be None", a_stackID, Severity::kWarning);
			return false;
		}
		return a_faction->IgnoresWerewolf();
	}

	auto GetFactionReportsCrimesAgainstMembers(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESFaction* a_faction) -> bool
	{
		if (!a_faction) {
			a_vm->TraceStack("akFaction cannot be None", a_stackID, Severity::kWarning);
			return false;
		}

		return a_faction->ReportsCrimesAgainstMembers();
	}

	auto GetFactionTracksCrime(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESFaction* a_faction) -> bool
	{
		if (!a_faction) {
			a_vm->TraceStack("akFaction cannot be None", a_stackID, Severity::kWarning);
			return false;
		}

		return a_faction->TracksCrimes();
	}

	auto GetFactionUsesCrimeGoldDefaults(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESFaction* a_faction) -> bool
	{
		if (!a_faction) {
			a_vm->TraceStack("akFaction cannot be None", a_stackID, Severity::kWarning);
			return false;
		}

		return a_faction->UsesCrimeGoldDefaults();
	}

	auto GetFactionCrimeValue(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESFaction* a_faction, std::int32_t a_member) -> float
	{
		if (!a_faction) {
			a_vm->TraceStack("akFaction cannot be None", a_stackID, Severity::kWarning);
			return -1.0f;
		}

		switch (a_member) {
			case 0x0:
				return a_faction->crimeData.crimevalues.arrest ? 1.0f : 0.0f;
			case 0x01:
				return a_faction->crimeData.crimevalues.attackOnSight ? 1.0f : 0.0f;
			case 0x02:
				return a_faction->crimeData.crimevalues.murderCrimeGold;
			case 0x04:
				return a_faction->crimeData.crimevalues.assaultCrimeGold;
			case 0x06:
				return a_faction->crimeData.crimevalues.trespassCrimeGold;
			case 0x08:
				return a_faction->crimeData.crimevalues.pickpocketCrimeGold;
			case 0x0C:
				return a_faction->crimeData.crimevalues.stealCrimeGoldMult;
			case 0x10:
				return a_faction->crimeData.crimevalues.escapeCrimeGold;
			case 0x12:
				return a_faction->crimeData.crimevalues.werewolfCrimeGold;
			default:
				break;
		}

		a_vm->TraceStack("aiMember is out of range", a_stackID, Severity::kWarning);
		return -1.0f;
	}

	auto SetAllies(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESFaction* a_faction, RE::BGSListForm* a_factions, const bool a_selfIsFriendToOther, const bool a_otherIsFriendToSelf) -> void
	{
		if (!a_faction) {
			a_vm->TraceStack("akFaction cannot be None", a_stackID, Severity::kWarning);
			return;
		}

		if (!a_factions) {
			a_vm->TraceStack("akFactions cannot be None", a_stackID, Severity::kWarning);
			return;
		}

		bool forceRefresh = false;

		for (auto& form : a_factions->forms) {
			if (form == nullptr) {
				continue;
			}

			if (auto* const otherFaction = form->As<RE::TESFaction>(); otherFaction) {
				a_faction->SetFactionFightReaction(otherFaction, a_selfIsFriendToOther ? RE::FIGHT_REACTION::kFriend : RE::FIGHT_REACTION::kAlly);
				otherFaction->SetFactionFightReaction(a_faction, a_otherIsFriendToSelf ? RE::FIGHT_REACTION::kFriend : RE::FIGHT_REACTION::kAlly);

				if (!forceRefresh) {
					forceRefresh = true;
				}
			}
		}

		if (forceRefresh) {
			if (auto* const processLists = RE::ProcessLists::GetSingleton(); processLists) {
				processLists->ClearCachedFactionFightReactions();
			}
		}
	}

	auto SetEnemies(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESFaction* a_faction, RE::BGSListForm* a_factions, const bool a_selfIsNeutralToOther, const bool a_otherIsNeutralToSelf) -> void
	{
		if (!a_faction) {
			a_vm->TraceStack("akFaction cannot be None", a_stackID, Severity::kWarning);
			return;
		}

		if (!a_factions) {
			a_vm->TraceStack("akFactions cannot be None", a_stackID, Severity::kWarning);
			return;
		}

		bool forceRefresh = false;

		for (auto& form : a_factions->forms) {
			if (form == nullptr) {
				continue;
			}

			if (auto* const otherFaction = form->As<RE::TESFaction>(); otherFaction) {
				a_faction->SetFactionFightReaction(otherFaction, a_selfIsNeutralToOther ? RE::FIGHT_REACTION::kNeutral : RE::FIGHT_REACTION::kEnemy);
				otherFaction->SetFactionFightReaction(a_faction, a_otherIsNeutralToSelf ? RE::FIGHT_REACTION::kNeutral : RE::FIGHT_REACTION::kEnemy);

				if (!forceRefresh) {
					forceRefresh = true;
				}
			}
		}

		if (forceRefresh) {
			if (auto* const processLists = RE::ProcessLists::GetSingleton(); processLists) {
				processLists->ClearCachedFactionFightReactions();
			}
		}
	}

	auto CopyFactionCrimeGold(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESFaction* a_faction, RE::TESFaction* a_otherFaction, const bool a_modify) -> void
	{
		if (!a_faction) {
			a_vm->TraceStack("akFaction cannot be None", a_stackID, Severity::kWarning);
			return;
		}

		if (!a_otherFaction) {
			a_vm->TraceStack("akOtherFaction cannot be None", a_stackID, Severity::kWarning);
			return;
		}

		if (a_modify) {
			a_otherFaction->ModCrimeGold(a_faction->GetCrimeGoldViolent(), true);
			a_otherFaction->ModCrimeGold(a_faction->GetCrimeGoldNonViolent(), false);
		} else {
			a_otherFaction->SetCrimeGoldViolent(a_faction->GetCrimeGoldViolent());
			a_otherFaction->SetCrimeGold(a_faction->GetCrimeGoldNonViolent());
		}

		if (auto* const processLists = RE::ProcessLists::GetSingleton(); processLists) {
			processLists->ClearCachedFactionFightReactions();
		}
	}

	auto ResetFactionCrimeGold(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESFaction* a_faction) -> void
	{
		if (!a_faction) {
			a_vm->TraceStack("akFaction cannot be None", a_stackID, Severity::kWarning);
			return;
		}

		a_faction->SetCrimeGoldViolent(0);
		a_faction->SetCrimeGold(0);

		if (auto* const processLists = RE::ProcessLists::GetSingleton(); processLists) {
			processLists->ClearCachedFactionFightReactions();
		}
	}

	auto ClearFactionReactionsCache(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*) -> bool
	{
		if (auto* const processLists = RE::ProcessLists::GetSingleton(); processLists) {
			processLists->ClearCachedFactionFightReactions();
			return true;
		}

		return false;
	}

	auto RegisterFuncs(VM* a_vm) -> bool
	{
		if (!a_vm) {
			logger::info("PapyrusFaction - cannot get VMState"sv);
			return false;
		}
		
		auto* plugin = SKSE::PluginDeclaration::GetSingleton();
		auto project_name = plugin->GetName();

		a_vm->RegisterFunction("GetFactionIgnoresMurder"sv, project_name, GetFactionIgnoresMurder);
		a_vm->RegisterFunction("GetFactionIgnoresAssault"sv, project_name, GetFactionIgnoresAssault);
		a_vm->RegisterFunction("GetFactionIgnoresTrespass"sv, project_name, GetFactionIgnoresTrespass);
		a_vm->RegisterFunction("GetFactionIgnoresPickpocket"sv, project_name, GetFactionIgnoresPickpocket);
		a_vm->RegisterFunction("GetFactionIgnoresStealing"sv, project_name, GetFactionIgnoresStealing);
		a_vm->RegisterFunction("GetFactionIgnoresWerewolf"sv, project_name, GetFactionIgnoresWerewolf);
		a_vm->RegisterFunction("GetFactionReportsCrimesAgainstMembers"sv, project_name, GetFactionReportsCrimesAgainstMembers);
		a_vm->RegisterFunction("GetFactionTracksCrime"sv, project_name, GetFactionTracksCrime);
		a_vm->RegisterFunction("GetFactionUsesCrimeGoldDefaults"sv, project_name, GetFactionUsesCrimeGoldDefaults);
		a_vm->RegisterFunction("GetFactionCrimeValue"sv, project_name, GetFactionCrimeValue);

		a_vm->RegisterFunction("SetAllies"sv, project_name, SetAllies);
		a_vm->RegisterFunction("SetEnemies"sv, project_name, SetEnemies);

		a_vm->RegisterFunction("CopyFactionCrimeGold"sv, project_name, CopyFactionCrimeGold);
		a_vm->RegisterFunction("ResetFactionCrimeGold"sv, project_name, ResetFactionCrimeGold);

		a_vm->RegisterFunction("ClearFactionReactionsCache"sv, project_name, ClearFactionReactionsCache);

		return true;
	}
}