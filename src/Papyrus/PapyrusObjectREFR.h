#pragma once

#pragma warning(disable : 4100)

namespace PapyrusObjectREFR
{
	using VM = RE::BSScript::IVirtualMachine;
	using StackID = RE::VMStackID;
	using Severity = RE::BSScript::ErrorLogger::Severity;

	auto FindClosestActorByLOS(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESObjectREFR* a_origin, float a_radius) -> RE::Actor*;
	auto FindClosestActorInFaction(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESObjectREFR* a_origin, RE::TESFaction* a_faction, float a_radius) -> RE::Actor*;
	auto FindClosestActorInFactionByLOS(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESObjectREFR* a_origin, RE::TESFaction* a_faction, float a_radius) -> RE::Actor*;
	auto FindNearbyActors(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESObjectREFR* a_origin, float a_radius) -> std::vector<RE::Actor*>;
	auto FindNearbyActorsInFaction(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESObjectREFR* a_origin, RE::TESFaction* a_faction, float a_radius) -> std::vector<RE::Actor*>;
	auto FindNearbyActorsInFactionByLOS(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESObjectREFR* a_origin, RE::TESFaction* a_faction, float a_radius) -> std::vector<RE::Actor*>;
	auto FindNearbyBooks(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESObjectREFR* a_origin, float a_radius) -> std::vector<RE::TESObjectREFR*>;
	auto FindNearbyCommandedActors(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESObjectREFR* a_origin, float a_radius) -> std::vector<RE::Actor*>;
	auto FindNearbyFollowers(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, float a_radius) -> std::vector<RE::Actor*>;
	auto FindNearbySummons(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESObjectREFR* a_origin, float a_radius) -> std::vector<RE::Actor*>;
	auto FindNearbyTeammates(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, float a_radius) -> std::vector<RE::Actor*>;
	auto GetPermanentActorValue(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESObjectREFR* a_ref, RE::BSFixedString a_actorValue) -> float;

	auto RegisterFuncs(VM* a_vm) -> bool;
}
