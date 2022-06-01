#pragma once

#pragma warning(disable : 4100)

namespace PapyrusFaction
{
	using VM = RE::BSScript::IVirtualMachine;
	using StackID = RE::VMStackID;
	using Severity = RE::BSScript::ErrorLogger::Severity;

	auto GetFactionIgnoresMurder(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESFaction* a_faction) -> bool;
	auto GetFactionIgnoresAssault(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESFaction* a_faction) -> bool;
	auto GetFactionIgnoresTrespass(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESFaction* a_faction) -> bool;
	auto GetFactionIgnoresPickpocket(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESFaction* a_faction) -> bool;
	auto GetFactionIgnoresStealing(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESFaction* a_faction) -> bool;
	auto GetFactionIgnoresWerewolf(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESFaction* a_faction) -> bool;
	auto GetFactionReportsCrimesAgainstMembers(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESFaction* a_faction) -> bool;
	auto GetFactionTracksCrime(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESFaction* a_faction) -> bool;
	auto GetFactionUsesCrimeGoldDefaults(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESFaction* a_faction) -> bool;
	auto GetFactionCrimeValue(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESFaction* a_faction, std::int32_t a_member) -> float;

	auto SetAllies(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESFaction* a_faction, RE::BGSListForm* a_factions, bool a_selfIsFriendToOther, bool a_otherIsFriendToSelf) -> void;
	auto SetEnemies(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESFaction* a_faction, RE::BGSListForm* a_factions, bool a_selfIsNeutralToOther, bool a_otherIsNeutralToSelf) -> void;

	auto CopyFactionCrimeGold(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESFaction* a_faction, RE::TESFaction* a_otherFaction, bool a_modify) -> void;
	auto ResetFactionCrimeGold(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESFaction* a_faction) -> void;

	auto ClearFactionReactionsCache(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*) -> bool;

	auto RegisterFuncs(VM* a_vm) -> bool;
}