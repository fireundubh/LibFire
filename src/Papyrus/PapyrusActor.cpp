#pragma once

#include "PapyrusActor.h"

namespace PapyrusActor
{
	auto ActorHasAnyKeyword(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::Actor* a_actor, RE::BGSListForm* a_keywords) -> bool
	{
		if (!a_actor) {
			a_vm->TraceStack("akActor cannot be None", a_stackID, Severity::kInfo);
			return false;
		}

		if (!a_keywords) {
			a_vm->TraceStack("akKeywords cannot be None", a_stackID, Severity::kInfo);
			return false;
		}

		for (auto& form : a_keywords->forms) {
			if (form == nullptr)
				continue;

			if (auto* const keyword = form->As<RE::BGSKeyword>(); keyword) {
				if (a_actor->HasKeyword(keyword)) {
					return true;
				}
			}
		}

		return false;
	}

	auto ActorIsCommandedBy(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::Actor* a_actor, RE::Actor* a_otherActor) -> bool
	{
		if (!a_actor) {
			a_vm->TraceStack("akCommandedActor cannot be None", a_stackID, Severity::kInfo);
			return false;
		}

		if (!a_otherActor) {
			a_vm->TraceStack("akCommandingActor cannot be None", a_stackID, Severity::kInfo);
			return false;
		}

		if (!a_actor->IsCommandedActor()) {
			return false;
		}

		if (const auto commandingActorHandle = a_actor->GetCommandingActor(); commandingActorHandle) {
			const auto commandingActorPtr = commandingActorHandle.get();
			const auto commandingActor = commandingActorPtr.get();

			return commandingActor != nullptr && commandingActor == a_otherActor;
		}

		return false;
	}

	auto ActorIsCommandedByPlayer(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::Actor* a_actor) -> bool
	{
		if (!a_actor) {
			a_vm->TraceStack("akCommandedActor cannot be None", a_stackID, Severity::kInfo);
			return false;
		}

		if (!a_actor->IsCommandedActor()) {
			return false;
		}

		if (auto player = RE::PlayerCharacter::GetSingleton(); player) {
			if (const auto commandingActorHandle = a_actor->GetCommandingActor(); commandingActorHandle) {
				const auto commandingActorPtr = commandingActorHandle.get();
				const auto commandingActor = commandingActorPtr.get();

				return commandingActor != nullptr && commandingActor == player;
			}
		}

		return false;
	}

	auto ActorIsFollower(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::Actor* a_actor) -> bool
	{
		if (!a_actor) {
			a_vm->TraceStack("akActor cannot be None", a_stackID, Severity::kInfo);
			return false;
		}

		if (a_actor->IsPlayerTeammate()) {
			return true;
		}

		if (a_actor->IsCommandedActor() || a_actor->IsSummoned()) {
			if (auto player = RE::PlayerCharacter::GetSingleton(); player) {
				if (const auto commandingActorHandle = a_actor->GetCommandingActor(); commandingActorHandle) {
					const auto commandingActorPtr = commandingActorHandle.get();
					const auto commandingActor = commandingActorPtr.get();

					return commandingActor != nullptr && commandingActor == player;
				}
			}
		}

		return false;
	}

	auto ActorIsInAnyFaction(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::Actor* a_actor, RE::BGSListForm* a_factions) -> bool
	{
		if (!a_actor) {
			a_vm->TraceStack("akActor cannot be None", a_stackID, Severity::kInfo);
			return false;
		}

		if (!a_factions) {
			a_vm->TraceStack("akFactions cannot be None", a_stackID, Severity::kInfo);
			return false;
		}

		if (auto* actorBase = a_actor->GetActorBase(); actorBase) {
			if (auto* factionChanges = a_actor->extraList.GetByType<RE::ExtraFactionChanges>(); factionChanges) {
				for (auto& change : factionChanges->factionChanges) {
					if (a_factions->HasForm(change.faction) && change.rank > -1) {
						return true;
					}
				}
			}

			for (auto& factionInfo : actorBase->factions) {
				if (a_factions->HasForm(factionInfo.faction) && factionInfo.rank > -1) {
					return true;
				}
			}
		}

		return false;
	}

	auto ActorIsInFaction(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::Actor* a_actor, RE::TESFaction* a_faction) -> bool
	{
		if (!a_actor) {
			a_vm->TraceStack("akActor cannot be None", a_stackID, Severity::kInfo);
			return false;
		}

		if (!a_faction) {
			a_vm->TraceStack("akFaction cannot be None", a_stackID, Severity::kInfo);
			return false;
		}

		if (auto* actorBase = a_actor->GetActorBase(); actorBase) {
			if (auto* factionChanges = a_actor->extraList.GetByType<RE::ExtraFactionChanges>(); factionChanges) {
				for (auto& change : factionChanges->factionChanges) {
					if (change.faction == a_faction && change.rank > -1) {
						return true;
					}
				}
			}

			for (auto& factionInfo : actorBase->factions) {
				if (factionInfo.faction == a_faction && factionInfo.rank > -1) {
					return true;
				}
			}
		}

		return false;
	}

	auto ActorIsSummoned(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::Actor* a_actor) -> bool
	{
		if (!a_actor) {
			a_vm->TraceStack("akActor cannot be None", a_stackID, Severity::kInfo);
			return false;
		}

		return a_actor->IsSummoned();
	}

	auto GetCommandingActor(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::Actor* a_actor) -> RE::Actor*
	{
		if (!a_actor) {
			a_vm->TraceStack("akCommandedActor cannot be None", a_stackID, Severity::kInfo);
			return nullptr;
		}

		if (!a_actor->IsCommandedActor()) {
			return nullptr;
		}

		if (const auto commandingActorHandle = a_actor->GetCommandingActor(); commandingActorHandle) {
			const auto commandingActorPtr = commandingActorHandle.get();
			const auto commandingActor = commandingActorPtr.get();

			return commandingActor;
		}

		return nullptr;
	}

	auto GetWornEquipmentInSlots(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::Actor* a_actor, const std::vector<int32_t> a_slots, bool a_leftWeapon, bool a_rightWeapon) -> std::vector<RE::TESForm*>
	{
		std::vector<RE::TESForm*> vec;

		if (!a_actor) {
			a_vm->TraceStack("akActor cannot be None", a_stackID, Severity::kInfo);
			return vec;
		}

		auto* changes = a_actor->GetInventoryChanges();

		if (!changes) {
			a_vm->TraceStack("akActor does not have inventory", a_stackID, Severity::kInfo);
			return vec;
		}

		if (!a_slots.empty()) {
			for (auto slot : a_slots) {
				auto* const armor = changes->GetArmorInSlot(slot);
				vec.push_back(armor);
			}
		}

		if (a_leftWeapon) {
			auto* lweapon = a_actor->GetEquippedObject(true);
			vec.push_back(lweapon);
		}

		if (a_rightWeapon) {
			auto* rweapon = a_actor->GetEquippedObject(false);
			vec.push_back(rweapon);
		}

		return vec;
	}

	auto RegisterFuncs(VM* a_vm) -> bool
	{
		if (!a_vm) {
			logger::info("PapyrusActor - couldn't get VMState");
			return false;
		}

		a_vm->RegisterFunction("ActorHasAnyKeyword", PROJECT_NAME, ActorHasAnyKeyword);
		a_vm->RegisterFunction("ActorIsCommandedBy", PROJECT_NAME, ActorIsCommandedBy);
		a_vm->RegisterFunction("ActorIsCommandedByPlayer", PROJECT_NAME, ActorIsCommandedByPlayer);
		a_vm->RegisterFunction("ActorIsFollower", PROJECT_NAME, ActorIsFollower);
		a_vm->RegisterFunction("ActorIsInAnyFaction", PROJECT_NAME, ActorIsInAnyFaction);
		a_vm->RegisterFunction("ActorIsInFaction", PROJECT_NAME, ActorIsInFaction);
		a_vm->RegisterFunction("ActorIsSummoned", PROJECT_NAME, ActorIsSummoned);
		a_vm->RegisterFunction("GetCommandingActor", PROJECT_NAME, GetCommandingActor);
		a_vm->RegisterFunction("GetWornEquipmentInSlots", PROJECT_NAME, GetWornEquipmentInSlots);

		return true;
	}
}