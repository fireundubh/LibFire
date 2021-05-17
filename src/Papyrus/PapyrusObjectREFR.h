#pragma once

#pragma warning(disable : 4100)

namespace PapyrusObjectREFR
{
	using VM = RE::BSScript::IVirtualMachine;
	using StackID = RE::VMStackID;
	using Severity = RE::BSScript::ErrorLogger::Severity;

	auto FindNearbyActors(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESObjectREFR* a_origin, float a_radius) -> std::vector<RE::Actor*>;
	auto FindNearbyCommandedActors(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESObjectREFR* a_origin, float a_radius) -> std::vector<RE::Actor*>;
	auto FindNearbyFollowers(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, float a_radius) -> std::vector<RE::Actor*>;
	auto FindNearbySummons(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESObjectREFR* a_origin, float a_radius) -> std::vector<RE::Actor*>;
	auto FindNearbyTeammates(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, float a_radius) -> std::vector<RE::Actor*>;

	auto RegisterFuncs(VM* a_vm) -> bool;
}
