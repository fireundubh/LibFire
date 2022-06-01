#pragma once

#include "PapyrusPlayerCharacter.h"

namespace PapyrusPlayerCharacter
{
	auto FindPlayerInfamousWithFactions(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*) -> std::vector<RE::TESFaction*>
	{
		std::vector<RE::TESFaction*> results;

		if (auto player = RE::PlayerCharacter::GetSingleton()) {
			for (const auto& [first, second] : player->GetCrimeValue().crimeGoldMap) {
				auto total = second.nonViolentInfamy + second.violentInfamy;
				if (total > 0.0f) {
					results.push_back(const_cast<RE::TESFaction*>(first));
				}
			}
		}

		return results;
	}

	auto FindPlayerWantedByFactions(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*) -> std::vector<RE::TESFaction*>
	{
		std::vector<RE::TESFaction*> results;

		if (auto player = RE::PlayerCharacter::GetSingleton()) {
			for (const auto& [first, second] : player->GetCrimeValue().crimeGoldMap) {
				auto total = second.nonViolentCur + second.violentCur;
				if (total > 0.0f) {
					results.push_back(const_cast<RE::TESFaction*>(first));
				}
			}
		}

		return results;
	}

	auto IsPlayerInfamous(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*) -> bool
	{
		auto total = 0.0f;

		if (auto player = RE::PlayerCharacter::GetSingleton()) {
			for (const auto& [first, second] : player->GetCrimeValue().crimeGoldMap) {
				total += (second.nonViolentInfamy + second.violentInfamy);
			}
		}

		return total > 0.0f;
	}

	auto IsPlayerWanted(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*) -> bool
	{
		auto total = 0.0f;

		if (auto player = RE::PlayerCharacter::GetSingleton()) {
			for (const auto& [first, second] : player->GetCrimeValue().crimeGoldMap) {
				total += (second.nonViolentCur + second.violentCur);
			}
		}

		return total > 0.0f;
	}

	auto RegisterFuncs(VM* a_vm) -> bool
	{
		if (!a_vm) {
			logger::info("PapyrusPlayerCharacter - cannot get VMState"sv);
			return false;
		}
		
		auto* plugin = SKSE::PluginDeclaration::GetSingleton();
		auto project_name = plugin->GetName();

		a_vm->RegisterFunction("FindPlayerInfamousWithFactions"sv, project_name, FindPlayerInfamousWithFactions);
		a_vm->RegisterFunction("FindPlayerWantedByFactions"sv, project_name, FindPlayerWantedByFactions);
		a_vm->RegisterFunction("IsPlayerInfamous"sv, project_name, IsPlayerInfamous);
		a_vm->RegisterFunction("IsPlayerWanted"sv, project_name, IsPlayerWanted);

		return true;
	}
}