#pragma once

#pragma warning(disable : 4100)

namespace PapyrusRace
{
	using VM = RE::BSScript::IVirtualMachine;
	using StackID = RE::VMStackID;
	using Severity = RE::BSScript::ErrorLogger::Severity;

	auto GetRaceSkillBonus(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESRace* a_race, RE::BSFixedString a_actorValue) -> std::int32_t;
	auto GetRaceSkills(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESRace* a_race) -> std::vector<RE::BSFixedString>;

	auto GetRaceMaleHeight(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESRace* a_race) -> float;
	auto GetRaceFemaleHeight(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESRace* a_race) -> float;

	auto GetRaceMaleWeight(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESRace* a_race) -> float;
	auto GetRaceFemaleWeight(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESRace* a_race) -> float;

	auto GetRaceStartingHealth(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESRace* a_race) -> float;
	auto GetRaceStartingMagicka(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESRace* a_race) -> float;
	auto GetRaceStartingStamina(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESRace* a_race) -> float;

	auto GetRaceCarryWeight(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESRace* a_race) -> float;
	auto GetRaceMass(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESRace* a_race) -> float;

	auto GetRaceHealthRegen(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESRace* a_race) -> float;
	auto GetRaceMagickaRegen(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESRace* a_race) -> float;
	auto GetRaceStaminaRegen(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESRace* a_race) -> float;

	auto GetRaceUnarmedDamage(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESRace* a_race) -> float;
	auto GetRaceUnarmedReach(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESRace* a_race) -> float;

	auto RegisterFuncs(VM* a_vm) -> bool;
}
