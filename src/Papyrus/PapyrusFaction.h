#pragma once

#pragma warning(disable : 4100)

namespace PapyrusFaction
{
	using VM = RE::BSScript::IVirtualMachine;
	using StackID = RE::VMStackID;
	using Severity = RE::BSScript::ErrorLogger::Severity;

	auto SetAllies(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESFaction* a_faction, RE::BGSListForm* a_factions, bool a_selfIsFriendToOther, bool a_otherIsFriendToSelf) -> void;
	auto SetEnemies(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESFaction* a_faction, RE::BGSListForm* a_factions, bool a_selfIsNeutralToOther, bool a_otherIsNeutralToSelf) -> void;

	auto RegisterFuncs(VM* a_vm) -> bool;
}