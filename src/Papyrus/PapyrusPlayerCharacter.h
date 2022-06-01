#pragma once

#pragma warning(disable : 4100)

namespace PapyrusPlayerCharacter
{
	using VM = RE::BSScript::IVirtualMachine;
	using StackID = RE::VMStackID;
	using Severity = RE::BSScript::ErrorLogger::Severity;

	auto FindPlayerInfamousWithFactions(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*) -> std::vector<RE::TESFaction*>;
	auto FindPlayerWantedByFactions(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*) -> std::vector<RE::TESFaction*>;
	auto IsPlayerInfamous(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*) -> bool;
	auto IsPlayerWanted(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*) -> bool;

	auto RegisterFuncs(VM* a_vm) -> bool;
}
