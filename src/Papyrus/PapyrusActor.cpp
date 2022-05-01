#pragma once

#include "PapyrusActor.h"

namespace PapyrusActor
{
	auto ActorFindAnyKeyword(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::Actor* a_actor, std::vector<RE::BGSKeyword*> a_keywords) -> std::int32_t
	{
		if (!a_actor) {
			a_vm->TraceStack("akActor cannot be None", a_stackID, Severity::kInfo);
			return -1;
		}

		if (a_keywords.empty()) {
			a_vm->TraceStack("argKeywords cannot be empty", a_stackID, Severity::kInfo);
			return -1;
		}

		for (auto& keyword : a_keywords) {
			if (keyword && a_actor->HasKeyword(keyword)) {
				if (auto it = std::find(a_keywords.begin(), a_keywords.end(), keyword); it != a_keywords.end()) {
					return static_cast<std::int32_t>(it - a_keywords.begin());
				}
			}
		}

		return -1;
	}

	auto ActorFindAnyPerk(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::Actor* a_actor, std::vector<RE::BGSPerk*> a_perks) -> std::int32_t
	{
		if (!a_actor) {
			a_vm->TraceStack("akActor cannot be None", a_stackID, Severity::kInfo);
			return -1;
		}

		if (a_perks.empty()) {
			a_vm->TraceStack("argPerks cannot be empty", a_stackID, Severity::kInfo);
			return -1;
		}

		if (auto player = RE::PlayerCharacter::GetSingleton(); player == a_actor) {
			if (const auto perkArray = player->addedPerks; !perkArray.empty()) {
				for (auto perkData : perkArray) {
					if (const auto perk = perkData->perk; perk) {
						if (auto it = std::find(a_perks.begin(), a_perks.end(), perk); it != a_perks.end()) {
							return static_cast<std::int32_t>(it - a_perks.begin());
						}
					}
				}
			}
		} else {
			if (const auto actorBase = a_actor->GetActorBase(); actorBase) {
				if (const auto perkArray = actorBase->As<RE::BGSPerkRankArray>(); perkArray) {
					for (std::uint32_t i = 0; i < perkArray->perkCount; ++i) {
						const auto perkData = perkArray->perks[i];

						if (const auto perk = perkData.perk; perk) {
							if (auto it = std::find(a_perks.begin(), a_perks.end(), perk); it != a_perks.end()) {
								return static_cast<std::int32_t>(it - a_perks.begin());
							}
						}
					}
				}
			}
		}

		return -1;
	}

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

	auto ActorHasPerkRank(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::Actor* a_actor, RE::BGSPerk* a_perk, std::int32_t a_rank) -> bool
	{
		if (!a_actor) {
			a_vm->TraceStack("akActor cannot be None", a_stackID, Severity::kInfo);
			return false;
		}

		if (!a_perk) {
			a_vm->TraceStack("akPerk cannot be None", a_stackID, Severity::kInfo);
			return false;
		}

		if (auto player = RE::PlayerCharacter::GetSingleton(); player == a_actor) {
			if (const auto perkArray = player->addedPerks; !perkArray.empty()) {
				for (auto perkData : perkArray) {
					if (const auto perk = perkData->perk; perk && a_perk == perk && a_rank == static_cast<std::int32_t>(perkData->currentRank)) {
						return true;
					}
				}
			}
		} else {
			if (const auto actorBase = a_actor->GetActorBase(); actorBase) {
				if (const auto perkArray = actorBase->As<RE::BGSPerkRankArray>(); perkArray) {
					for (std::uint32_t i = 0; i < perkArray->perkCount; ++i) {
						const auto perkData = perkArray->perks[i];

						if (const auto perk = perkData.perk; perk && a_perk == perk && a_rank == static_cast<std::int32_t>(perkData.currentRank)) {
							return true;
						}
					}
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

	auto GetActorPerkRank(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::Actor* a_actor, RE::BGSPerk* a_perk) -> std::int32_t
	{
		if (!a_actor) {
			a_vm->TraceStack("akActor cannot be None", a_stackID, Severity::kInfo);
			return -1;
		}

		if (!a_perk) {
			a_vm->TraceStack("akPerk cannot be None", a_stackID, Severity::kInfo);
			return -1;
		}

		if (auto player = RE::PlayerCharacter::GetSingleton(); player == a_actor) {
			if (const auto perkArray = player->addedPerks; !perkArray.empty()) {
				for (auto perkData : perkArray) {
					if (const auto perk = perkData->perk; perk && a_perk == perk) {
						return static_cast<std::int32_t>(perkData->currentRank);
					}
				}
			}
		} else {
			if (const auto actorBase = a_actor->GetActorBase(); actorBase) {
				if (const auto perkArray = actorBase->As<RE::BGSPerkRankArray>(); perkArray) {
					for (std::uint32_t i = 0; i < perkArray->perkCount; ++i) {
						const auto perkData = perkArray->perks[i];

						if (const auto perk = perkData.perk; perk && a_perk == perk) {
							return static_cast<std::int32_t>(perkData.currentRank);
						}
					}
				}
			}
		}

		return -1;
	}

	auto GetActorPerks(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::Actor* a_actor) -> std::vector<RE::BGSPerk*>
	{
		std::vector<RE::BGSPerk*> result;

		if (!a_actor) {
			a_vm->TraceStack("akActor cannot be None", a_stackID, Severity::kInfo);
			return result;
		}

		if (auto player = RE::PlayerCharacter::GetSingleton(); player == a_actor) {
			if (const auto perkArray = player->addedPerks; !perkArray.empty()) {
				for (auto perkData : perkArray) {
					if (const auto perk = perkData->perk; perk) {
						result.emplace_back(perk);
					}
				}
			}
		} else {
			if (const auto actorBase = a_actor->GetActorBase(); actorBase) {
				if (const auto perkArray = actorBase->As<RE::BGSPerkRankArray>(); perkArray) {
					for (std::uint32_t i = 0; i < perkArray->perkCount; ++i) {
						const auto perkData = perkArray->perks[i];

						if (const auto perk = perkData.perk; perk) {
							result.emplace_back(perk);
						}
					}
				}
			}
		}

		return result;
	}

	auto GetCommandedActors(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::Actor* a_actor) -> std::vector<RE::Actor*>
	{
		std::vector<RE::Actor*> result;

		if (!a_actor) {
			a_vm->TraceStack("akActor cannot be None", a_stackID, Severity::kInfo);
			return result;
		}

		if (const auto currentProcess = a_actor->currentProcess; currentProcess) {
			if (const auto middleProcess = currentProcess->middleHigh; middleProcess) {
				if (const auto commandedActors = middleProcess->commandedActors; !commandedActors.empty()) {
					for (const auto& commandedActorData : commandedActors) {
						if (const auto commandedActorHandle = commandedActorData.commandedActor; commandedActorHandle) {
							const auto commandedActorPtr = commandedActorHandle.get();
							const auto commandedActor = commandedActorPtr.get();

							result.push_back(commandedActor);
						}
					}
				}
			}
		}

		return result;
	}

	auto GetCommandingActor(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::Actor* a_actor) -> RE::Actor*
	{
		if (!a_actor) {
			a_vm->TraceStack("akActor cannot be None", a_stackID, Severity::kInfo);
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

	auto GetEquippedAmmo(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::Actor* a_actor) -> RE::TESAmmo*
	{
		if (!a_actor) {
			a_vm->TraceStack("akActor cannot be None", a_stackID, Severity::kInfo);
			return nullptr;
		}

		return a_actor->GetCurrentAmmo();
	}

	auto GetWornEquipmentInSlots(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::Actor* a_actor, std::vector<std::uint32_t> a_slots, bool a_leftWeapon, bool a_rightWeapon) -> std::vector<RE::TESForm*>
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
			for (const auto slot : a_slots) {
				auto* const armor = changes->GetArmorInSlot(slot);	// NOLINT(cppcoreguidelines-narrowing-conversions)
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
			logger::info("PapyrusActor - couldn't get VMState"sv);
			return false;
		}

		a_vm->RegisterFunction("ActorFindAnyKeyword"sv, PROJECT_NAME, ActorFindAnyKeyword);
		a_vm->RegisterFunction("ActorFindAnyPerk"sv, PROJECT_NAME, ActorFindAnyPerk);
		a_vm->RegisterFunction("ActorHasAnyKeyword"sv, PROJECT_NAME, ActorHasAnyKeyword);
		a_vm->RegisterFunction("ActorHasPerkRank"sv, PROJECT_NAME, ActorHasPerkRank);
		a_vm->RegisterFunction("ActorIsCommandedBy"sv, PROJECT_NAME, ActorIsCommandedBy);
		a_vm->RegisterFunction("ActorIsCommandedByPlayer"sv, PROJECT_NAME, ActorIsCommandedByPlayer);
		a_vm->RegisterFunction("ActorIsFollower"sv, PROJECT_NAME, ActorIsFollower);
		a_vm->RegisterFunction("ActorIsInAnyFaction"sv, PROJECT_NAME, ActorIsInAnyFaction);
		a_vm->RegisterFunction("ActorIsInFaction"sv, PROJECT_NAME, ActorIsInFaction);
		a_vm->RegisterFunction("ActorIsSummoned"sv, PROJECT_NAME, ActorIsSummoned);
		a_vm->RegisterFunction("GetActorPerkRank"sv, PROJECT_NAME, GetActorPerkRank);
		a_vm->RegisterFunction("GetActorPerks"sv, PROJECT_NAME, GetActorPerks);
		a_vm->RegisterFunction("GetCommandedActors"sv, PROJECT_NAME, GetCommandedActors);
		a_vm->RegisterFunction("GetCommandingActor"sv, PROJECT_NAME, GetCommandingActor);
		a_vm->RegisterFunction("GetEquippedAmmo"sv, PROJECT_NAME, GetEquippedAmmo);
		a_vm->RegisterFunction("GetWornEquipmentInSlots"sv, PROJECT_NAME, GetWornEquipmentInSlots);

		return true;
	}
}