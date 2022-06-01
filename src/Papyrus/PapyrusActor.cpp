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

	auto ActorFindCrimeFactions(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::Actor* a_actor) -> std::vector<RE::TESFaction*>
	{
		std::vector<RE::TESFaction*> results;

		if (!a_actor) {
			a_vm->TraceStack("akActor cannot be None", a_stackID, Severity::kInfo);
			return results;
		}

		a_actor->VisitFactions([&](RE::TESFaction* faction, int8_t rank) -> bool {
			if (rank > -1 && faction->TracksCrimes()) {
				results.emplace_back(faction);
			}
			return true;
		});

		return results;
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

		if (const auto commandingActorPtr = a_actor->GetCommandingActor(); commandingActorPtr) {
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
			if (const auto commandingActorPtr = a_actor->GetCommandingActor(); commandingActorPtr) {
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
				if (const auto commandingActorPtr = a_actor->GetCommandingActor(); commandingActorPtr) {
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

		if (const auto commandingActorPtr = a_actor->GetCommandingActor(); commandingActorPtr) {
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

	auto RegisterFuncs(VM* a_vm) -> bool
	{
		if (!a_vm) {
			logger::info("PapyrusActor - couldn't get VMState"sv);
			return false;
		}
		
		auto* plugin = SKSE::PluginDeclaration::GetSingleton();
		auto project_name = plugin->GetName();

		a_vm->RegisterFunction("ActorFindAnyKeyword"sv, project_name, ActorFindAnyKeyword);
		a_vm->RegisterFunction("ActorFindAnyPerk"sv, project_name, ActorFindAnyPerk);
		a_vm->RegisterFunction("ActorFindCrimeFactions"sv, project_name, ActorFindCrimeFactions);
		a_vm->RegisterFunction("ActorHasAnyKeyword"sv, project_name, ActorHasAnyKeyword);
		a_vm->RegisterFunction("ActorHasPerkRank"sv, project_name, ActorHasPerkRank);
		a_vm->RegisterFunction("ActorIsCommandedBy"sv, project_name, ActorIsCommandedBy);
		a_vm->RegisterFunction("ActorIsCommandedByPlayer"sv, project_name, ActorIsCommandedByPlayer);
		a_vm->RegisterFunction("ActorIsFollower"sv, project_name, ActorIsFollower);
		a_vm->RegisterFunction("ActorIsInAnyFaction"sv, project_name, ActorIsInAnyFaction);
		a_vm->RegisterFunction("ActorIsInFaction"sv, project_name, ActorIsInFaction);
		a_vm->RegisterFunction("ActorIsSummoned"sv, project_name, ActorIsSummoned);
		a_vm->RegisterFunction("GetActorPerkRank"sv, project_name, GetActorPerkRank);
		a_vm->RegisterFunction("GetActorPerks"sv, project_name, GetActorPerks);
		a_vm->RegisterFunction("GetCommandedActors"sv, project_name, GetCommandedActors);
		a_vm->RegisterFunction("GetCommandingActor"sv, project_name, GetCommandingActor);
		a_vm->RegisterFunction("GetEquippedAmmo"sv, project_name, GetEquippedAmmo);

		return true;
	}
}