#pragma once

#include "ActorValueHelper.h"

#include "PapyrusRace.h"

namespace PapyrusRace
{
	auto GetRaceSkillBonus(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESRace* a_race, RE::BSFixedString a_actorValue) -> std::int32_t
	{
		if (!a_race) {
			a_vm->TraceStack("akRace cannot be None", a_stackID, Severity::kInfo);
			return -1;
		}

		const auto actorValueId = RE::ActorValueList::GetSingleton()->LookupActorValueByName(a_actorValue);
		const auto actorValue = static_cast<RE::ActorValue>(actorValueId);

		for (const auto& [skill, bonus] : a_race->data.skillBoosts) {
			const auto skillValue = static_cast<RE::ActorValue>(skill.get());
			if (skillValue == actorValue) {
				return static_cast<std::int32_t>(bonus);
			}
		}

		return -1;
	}

	auto GetRaceSkills(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESRace* a_race) -> std::vector<RE::BSFixedString>
	{
		std::vector<RE::BSFixedString> vec;

		if (!a_race) {
			a_vm->TraceStack("akRace cannot be None", a_stackID, Severity::kInfo);
			return vec;
		}

		for (const auto& [skill, bonus] : a_race->data.skillBoosts) {
			const auto skillValue = static_cast<RE::ActorValue>(skill.get());
			const auto skillName = ActorValueHelper::ActorValueToString(skillValue);
			vec.push_back(skillName);
		}

		return vec;
	}

	auto GetRaceMaleHeight(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESRace* a_race) -> float
	{
		if (!a_race) {
			a_vm->TraceStack("akRace cannot be None", a_stackID, Severity::kInfo);
			return -1;
		}

		return a_race->data.height[RE::SEXES::kMale];
	}

	auto GetRaceFemaleHeight(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESRace* a_race) -> float
	{
		if (!a_race) {
			a_vm->TraceStack("akRace cannot be None", a_stackID, Severity::kInfo);
			return -1;
		}

		return a_race->data.height[RE::SEXES::kFemale];
	}

	auto GetRaceMaleWeight(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESRace* a_race) -> float
	{
		if (!a_race) {
			a_vm->TraceStack("akRace cannot be None", a_stackID, Severity::kInfo);
			return -1;
		}

		return a_race->data.weight[RE::SEXES::kMale];
	}

	auto GetRaceFemaleWeight(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESRace* a_race) -> float
	{
		if (!a_race) {
			a_vm->TraceStack("akRace cannot be None", a_stackID, Severity::kInfo);
			return -1;
		}

		return a_race->data.weight[RE::SEXES::kFemale];
	}

	auto GetRaceStartingHealth(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESRace* a_race) -> float
	{
		if (!a_race) {
			a_vm->TraceStack("akRace cannot be None", a_stackID, Severity::kInfo);
			return -1;
		}

		return a_race->data.startingHealth;
	}

	auto GetRaceStartingMagicka(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESRace* a_race) -> float
	{
		if (!a_race) {
			a_vm->TraceStack("akRace cannot be None", a_stackID, Severity::kInfo);
			return -1;
		}

		return a_race->data.startingMagicka;
	}

	auto GetRaceStartingStamina(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESRace* a_race) -> float
	{
		if (!a_race) {
			a_vm->TraceStack("akRace cannot be None", a_stackID, Severity::kInfo);
			return -1;
		}

		return a_race->data.startingStamina;
	}

	auto GetRaceCarryWeight(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESRace* a_race) -> float
	{
		if (!a_race) {
			a_vm->TraceStack("akRace cannot be None", a_stackID, Severity::kInfo);
			return -1;
		}

		return a_race->data.baseCarryWeight;
	}

	auto GetRaceMass(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESRace* a_race) -> float
	{
		if (!a_race) {
			a_vm->TraceStack("akRace cannot be None", a_stackID, Severity::kInfo);
			return -1;
		}

		return a_race->data.baseMass;
	}

	auto GetRaceHealthRegen(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESRace* a_race) -> float
	{
		if (!a_race) {
			a_vm->TraceStack("akRace cannot be None", a_stackID, Severity::kInfo);
			return -1;
		}

		return a_race->data.healthRegen;
	}

	auto GetRaceMagickaRegen(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESRace* a_race) -> float
	{
		if (!a_race) {
			a_vm->TraceStack("akRace cannot be None", a_stackID, Severity::kInfo);
			return -1;
		}

		return a_race->data.magickaRegen;
	}

	auto GetRaceStaminaRegen(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESRace* a_race) -> float
	{
		if (!a_race) {
			a_vm->TraceStack("akRace cannot be None", a_stackID, Severity::kInfo);
			return -1;
		}

		return a_race->data.staminaRegen;
	}

	auto GetRaceUnarmedDamage(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESRace* a_race) -> float
	{
		if (!a_race) {
			a_vm->TraceStack("akRace cannot be None", a_stackID, Severity::kInfo);
			return -1;
		}

		return a_race->data.unarmedDamage;
	}

	auto GetRaceUnarmedReach(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESRace* a_race) -> float
	{
		if (!a_race) {
			a_vm->TraceStack("akRace cannot be None", a_stackID, Severity::kInfo);
			return -1;
		}

		return a_race->data.unarmedReach;
	}

	auto RegisterFuncs(VM* a_vm) -> bool
	{
		if (!a_vm) {
			logger::info("PapyrusRace - cannot get VMState"sv);
			return false;
		}
		
		auto* plugin = SKSE::PluginDeclaration::GetSingleton();
		auto project_name = plugin->GetName();

		a_vm->RegisterFunction("GetRaceSkillBonus"sv, project_name, GetRaceSkillBonus);
		a_vm->RegisterFunction("GetRaceSkills"sv, project_name, GetRaceSkills);

		a_vm->RegisterFunction("GetRaceMaleHeight"sv, project_name, GetRaceMaleHeight);
		a_vm->RegisterFunction("GetRaceMaleWeight"sv, project_name, GetRaceMaleWeight);
		a_vm->RegisterFunction("GetRaceFemaleHeight"sv, project_name, GetRaceFemaleHeight);
		a_vm->RegisterFunction("GetRaceFemaleWeight"sv, project_name, GetRaceFemaleWeight);

		a_vm->RegisterFunction("GetRaceStartingHealth"sv, project_name, GetRaceStartingHealth);
		a_vm->RegisterFunction("GetRaceStartingMagicka"sv, project_name, GetRaceStartingMagicka);
		a_vm->RegisterFunction("GetRaceStartingStamina"sv, project_name, GetRaceStartingStamina);

		a_vm->RegisterFunction("GetRaceCarryWeight"sv, project_name, GetRaceCarryWeight);
		a_vm->RegisterFunction("GetRaceMass"sv, project_name, GetRaceMass);

		a_vm->RegisterFunction("GetRaceHealthRegen"sv, project_name, GetRaceHealthRegen);
		a_vm->RegisterFunction("GetRaceMagickaRegen"sv, project_name, GetRaceMagickaRegen);
		a_vm->RegisterFunction("GetRaceStaminaRegen"sv, project_name, GetRaceStaminaRegen);

		a_vm->RegisterFunction("GetRaceUnarmedDamage"sv, project_name, GetRaceUnarmedDamage);
		a_vm->RegisterFunction("GetRaceUnarmedReach"sv, project_name, GetRaceUnarmedReach);

		return true;
	}
}