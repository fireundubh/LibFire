#pragma once

#include "PapyrusObjectREFR.h"

namespace PapyrusObjectREFR
{
	auto FindClosestActorByLOS(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESObjectREFR* a_origin, float a_radius) -> RE::Actor*
	{
		if (!a_origin) {
			a_vm->TraceStack("akOrigin cannot be None", a_stackID, Severity::kInfo);
			return nullptr;
		}

		std::vector<RE::Actor*> vec;

		if (const auto TES = RE::TES::GetSingleton(); TES) {
			const auto formType = RE::FormType::NPC;

			if (auto player = RE::PlayerCharacter::GetSingleton(); player == a_origin) {
				bool codePath = false;

				TES->ForEachReferenceInRange(a_origin, a_radius, [&](RE::TESObjectREFR& a_ref) {
					auto base = a_ref.GetBaseObject();
					if (a_ref.As<RE::TESObjectREFR>() != a_origin && (a_ref.Is(formType) || base && base->Is(formType))) {
						if (auto actor = a_ref.As<RE::Actor>(); actor && actor->HasLineOfSight(a_origin, codePath)) {
							vec.push_back(actor);
						}
					}
					return true;
				});
			}
			else {
				bool codePath = true;

				TES->ForEachReferenceInRange(a_origin, a_radius, [&](RE::TESObjectREFR& a_ref) {
					auto base = a_ref.GetBaseObject();
					if (a_ref.As<RE::TESObjectREFR>() != a_origin && (a_ref.Is(formType) || base && base->Is(formType))) {
						if (auto actor = a_ref.As<RE::Actor>(); actor && actor->HasLineOfSight(a_origin, codePath)) {
							vec.push_back(actor);
						}
					}
					return true;
				});
			}
		}

		if (vec.empty())
			return nullptr;

		if (vec.size() == 1)
			return vec.front();

		std::multimap<float, RE::Actor*> results;

		for (auto* actor : vec) {
			auto distance = a_origin->As<RE::NiPoint3>()->GetSquaredDistance(actor->GetPosition());
			results.insert(std::pair<float, RE::Actor*>(distance, actor));
		}

		return results.cbegin()->second;
	}

	auto FindClosestActorInFaction(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESObjectREFR* a_origin, RE::TESFaction* a_faction, float a_radius) -> RE::Actor*
	{
		if (!a_origin) {
			a_vm->TraceStack("akOrigin cannot be None", a_stackID, Severity::kInfo);
			return nullptr;
		}

		if (!a_faction) {
			a_vm->TraceStack("akFaction cannot be None", a_stackID, Severity::kInfo);
			return nullptr;
		}

		std::vector<RE::Actor*> vec;

		if (const auto TES = RE::TES::GetSingleton(); TES) {
			const auto formType = RE::FormType::NPC;

			TES->ForEachReferenceInRange(a_origin, a_radius, [&](RE::TESObjectREFR& a_ref) {
				auto base = a_ref.GetBaseObject();
				if (a_ref.As<RE::TESObjectREFR>() != a_origin && (a_ref.Is(formType) || base && base->Is(formType))) {
					if (auto actor = a_ref.As<RE::Actor>(); actor && actor->IsInFaction(a_faction)) {
						vec.push_back(actor);
					}
				}
				return true;
			});
		}

		if (vec.empty())
			return nullptr;

		if (vec.size() == 1)
			return vec.front();

		std::multimap<float, RE::Actor*> results;

		for (auto* actor : vec) {
			auto distance = a_origin->As<RE::NiPoint3>()->GetSquaredDistance(actor->GetPosition());
			results.insert(std::pair<float, RE::Actor*>(distance, actor));
		}

		return results.cbegin()->second;
	}

	auto FindClosestActorInFactionByLOS(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESObjectREFR* a_origin, RE::TESFaction* a_faction, float a_radius) -> RE::Actor*
	{
		if (!a_origin) {
			a_vm->TraceStack("akOrigin cannot be None", a_stackID, Severity::kInfo);
			return nullptr;
		}

		std::vector<RE::Actor*> vec;

		if (const auto TES = RE::TES::GetSingleton(); TES) {
			const auto formType = RE::FormType::NPC;

			if (auto player = RE::PlayerCharacter::GetSingleton(); player == a_origin) {
				bool codePath = false;

				TES->ForEachReferenceInRange(a_origin, a_radius, [&](RE::TESObjectREFR& a_ref) {
					auto base = a_ref.GetBaseObject();
					if (a_ref.As<RE::TESObjectREFR>() != a_origin && (a_ref.Is(formType) || base && base->Is(formType))) {
						if (auto actor = a_ref.As<RE::Actor>(); actor && actor->IsInFaction(a_faction) && actor->HasLineOfSight(a_origin, codePath)) {
							vec.push_back(actor);
						}
					}
					return true;
				});
			} else {
				bool codePath = true;

				TES->ForEachReferenceInRange(a_origin, a_radius, [&](RE::TESObjectREFR& a_ref) {
					auto base = a_ref.GetBaseObject();
					if (a_ref.As<RE::TESObjectREFR>() != a_origin && (a_ref.Is(formType) || base && base->Is(formType))) {
						if (auto actor = a_ref.As<RE::Actor>(); actor && actor->IsInFaction(a_faction) && actor->HasLineOfSight(a_origin, codePath)) {
							vec.push_back(actor);
						}
					}
					return true;
				});
			}
		}

		if (vec.empty())
			return nullptr;

		if (vec.size() == 1)
			return vec.front();

		std::multimap<float, RE::Actor*> results;

		for (auto* actor : vec) {
			auto distance = a_origin->As<RE::NiPoint3>()->GetSquaredDistance(actor->GetPosition());
			results.insert(std::pair<float, RE::Actor*>(distance, actor));
		}

		return results.cbegin()->second;
	}

	auto FindNearbyActors(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESObjectREFR* a_origin, float a_radius) -> std::vector<RE::Actor*>
	{
		std::vector<RE::Actor*> vec;

		if (!a_origin) {
			a_vm->TraceStack("akOrigin cannot be None", a_stackID, Severity::kInfo);
			return vec;
		}

		if (const auto TES = RE::TES::GetSingleton(); TES) {
			const auto formType = RE::FormType::NPC;

			TES->ForEachReferenceInRange(a_origin, a_radius, [&](RE::TESObjectREFR& a_ref) {
				auto base = a_ref.GetBaseObject();
				if (a_ref.As<RE::TESObjectREFR>() != a_origin && (a_ref.Is(formType) || base && base->Is(formType))) {
					if (auto actor = a_ref.As<RE::Actor>(); actor) {
						vec.push_back(actor);
					}
				}
				return true;
			});
		}

		return vec;
	}

	auto FindNearbyActorsInFaction(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESObjectREFR* a_origin, RE::TESFaction* a_faction, float a_radius) -> std::vector<RE::Actor*>
	{
		std::vector<RE::Actor*> vec;

		if (!a_origin) {
			a_vm->TraceStack("akOrigin cannot be None", a_stackID, Severity::kInfo);
			return vec;
		}

		if (const auto TES = RE::TES::GetSingleton(); TES) {
			const auto formType = RE::FormType::NPC;

			TES->ForEachReferenceInRange(a_origin, a_radius, [&](RE::TESObjectREFR& a_ref) {
				auto base = a_ref.GetBaseObject();
				if (a_ref.As<RE::TESObjectREFR>() != a_origin && (a_ref.Is(formType) || base && base->Is(formType))) {
					if (auto actor = a_ref.As<RE::Actor>(); actor && actor->IsInFaction(a_faction)) {
						vec.push_back(actor);
					}
				}
				return true;
			});
		}

		return vec;
	}

	auto FindNearbyActorsInFactionByLOS(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESObjectREFR* a_origin, RE::TESFaction* a_faction, float a_radius) -> std::vector<RE::Actor*>
	{
		std::vector<RE::Actor*> vec;

		if (!a_origin) {
			a_vm->TraceStack("akOrigin cannot be None", a_stackID, Severity::kInfo);
			return vec;
		}

		if (const auto TES = RE::TES::GetSingleton(); TES) {
			const auto formType = RE::FormType::NPC;

			if (auto player = RE::PlayerCharacter::GetSingleton(); player == a_origin) {
				bool codePath = false;

				TES->ForEachReferenceInRange(a_origin, a_radius, [&](RE::TESObjectREFR& a_ref) {
					auto base = a_ref.GetBaseObject();
					if (a_ref.As<RE::TESObjectREFR>() != a_origin && (a_ref.Is(formType) || base && base->Is(formType))) {
						if (auto actor = a_ref.As<RE::Actor>(); actor && actor->IsInFaction(a_faction) && actor->HasLineOfSight(a_origin, codePath)) {
							vec.push_back(actor);
						}
					}
					return true;
				});
			} else {
				bool codePath = true;

				TES->ForEachReferenceInRange(a_origin, a_radius, [&](RE::TESObjectREFR& a_ref) {
					auto base = a_ref.GetBaseObject();
					if (a_ref.As<RE::TESObjectREFR>() != a_origin && (a_ref.Is(formType) || base && base->Is(formType))) {
						if (auto actor = a_ref.As<RE::Actor>(); actor && actor->IsInFaction(a_faction) && actor->HasLineOfSight(a_origin, codePath)) {
							vec.push_back(actor);
						}
					}
					return true;
				});
			}
		}

		return vec;
	}

	auto FindNearbyBooks(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESObjectREFR* a_origin, float a_radius) -> std::vector<RE::TESObjectREFR*>
	{
		std::vector<RE::TESObjectREFR*> vec;

		if (!a_origin) {
			a_vm->TraceStack("akOrigin cannot be None", a_stackID, Severity::kInfo);
			return vec;
		}

		if (const auto TES = RE::TES::GetSingleton(); TES) {
			const auto formType = RE::FormType::Book;

			TES->ForEachReferenceInRange(a_origin, a_radius, [&](RE::TESObjectREFR& a_ref) {
				auto base = a_ref.GetBaseObject();
				if (a_ref.As<RE::TESObjectREFR>() != a_origin && (a_ref.Is(formType) || base && base->Is(formType))) {
					vec.push_back(&a_ref);
				}
				return true;
			});
		}

		return vec;
	}

	auto FindNearbyCommandedActors(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESObjectREFR* a_origin, float a_radius) -> std::vector<RE::Actor*>
	{
		std::vector<RE::Actor*> vec;

		if (!a_origin) {
			a_vm->TraceStack("akOrigin cannot be None", a_stackID, Severity::kInfo);
			return vec;
		}

		if (const auto TES = RE::TES::GetSingleton(); TES) {
			const auto formType = RE::FormType::NPC;

			TES->ForEachReferenceInRange(a_origin, a_radius, [&](RE::TESObjectREFR& a_ref) {
				auto base = a_ref.GetBaseObject();
				if (a_ref.As<RE::TESObjectREFR>() != a_origin && (a_ref.Is(formType) || base && base->Is(formType))) {
					if (auto actor = a_ref.As<RE::Actor>(); actor) {
						if (actor->IsCommandedActor()) {
							if (const auto commandingActorPtr = actor->GetCommandingActor(); commandingActorPtr) {
								const auto commandingActor = commandingActorPtr.get();

								if (commandingActor != nullptr && commandingActor == a_origin) {
									vec.push_back(actor);
								}
							}
						}
					}
				}
				return true;
			});
		}

		return vec;
	}

	auto FindNearbyFollowers(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, float a_radius) -> std::vector<RE::Actor*>
	{
		std::vector<RE::Actor*> vec;

		if (const auto TES = RE::TES::GetSingleton(); TES) {
			if (const auto player = RE::PlayerCharacter::GetSingleton(); player) {
				const auto formType = RE::FormType::NPC;

				TES->ForEachReferenceInRange(player, a_radius, [&](RE::TESObjectREFR& a_ref) {
					auto base = a_ref.GetBaseObject();
					if (a_ref.As<RE::TESObjectREFR>() != player && (a_ref.Is(formType) || base && base->Is(formType))) {
						if (auto actor = a_ref.As<RE::Actor>(); actor) {
							if (actor->IsPlayerTeammate()) {
								vec.push_back(actor);
							} else if (actor->IsCommandedActor() || actor->IsSummoned()) {
								if (const auto commandingActorPtr = actor->GetCommandingActor(); commandingActorPtr) {
									const auto commandingActor = commandingActorPtr.get();

									if (commandingActor != nullptr && commandingActor == player) {
										vec.push_back(actor);
									}
								}
							}
						}
					}
					return true;
				});
			}
		}

		return vec;
	}

	auto FindNearbySummons(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESObjectREFR* a_origin, float a_radius) -> std::vector<RE::Actor*>
	{
		std::vector<RE::Actor*> vec;

		if (!a_origin) {
			a_vm->TraceStack("akOrigin cannot be None", a_stackID, Severity::kInfo);
			return vec;
		}

		if (const auto TES = RE::TES::GetSingleton(); TES) {
			const auto formType = RE::FormType::NPC;

			TES->ForEachReferenceInRange(a_origin, a_radius, [&](RE::TESObjectREFR& a_ref) {
				auto base = a_ref.GetBaseObject();
				if (a_ref.As<RE::TESObjectREFR>() != a_origin && (a_ref.Is(formType) || base && base->Is(formType))) {
					if (auto actor = a_ref.As<RE::Actor>(); actor) {
						if (actor->IsSummoned()) {
							vec.push_back(actor);
						}
					}
				}
				return true;
			});
		}

		return vec;
	}

	auto FindNearbyTeammates(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, float a_radius) -> std::vector<RE::Actor*>
	{
		std::vector<RE::Actor*> vec;

		if (const auto TES = RE::TES::GetSingleton(); TES) {
			if (const auto player = RE::PlayerCharacter::GetSingleton(); player) {
				if (player->teammateCount > 0) {
					const auto formType = RE::FormType::NPC;

					TES->ForEachReferenceInRange(player, a_radius, [&](RE::TESObjectREFR& a_ref) {
						auto base = a_ref.GetBaseObject();
						if (a_ref.As<RE::TESObjectREFR>() != player && (a_ref.Is(formType) || base && base->Is(formType))) {
							if (auto actor = a_ref.As<RE::Actor>(); actor) {
								if (actor->IsPlayerTeammate()) {
									vec.push_back(actor);
								}
							}
						}
						return true;
					});
				}
			}
		}

		return vec;
	}

	auto GetPermanentActorValue(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESObjectREFR* a_ref, RE::BSFixedString a_actorValue) -> float
	{
		if (!a_ref) {
			a_vm->TraceStack("akActor cannot be None", a_stackID, Severity::kInfo);
			return -1.0;
		}

		if (const auto actor = a_ref->As<RE::Actor>(); actor) {
			const auto actorValueId = RE::ActorValueList::GetSingleton()->LookupActorValueByName(a_actorValue);
			const auto actorValue = static_cast<RE::ActorValue>(actorValueId);
			return actor->GetPermanentActorValue(actorValue);
		}

		return -1.0;
	}

	auto RegisterFuncs(VM* a_vm) -> bool
	{
		if (!a_vm) {
			logger::info("PapyrusObjectREFR - couldn't get VMState"sv);
			return false;
		}
		
		auto* plugin = SKSE::PluginDeclaration::GetSingleton();
		auto project_name = plugin->GetName();

		a_vm->RegisterFunction("FindClosestActorByLOS"sv, project_name, FindClosestActorByLOS);
		a_vm->RegisterFunction("FindClosestActorInFaction"sv, project_name, FindClosestActorInFaction);
		a_vm->RegisterFunction("FindClosestActorInFactionByLOS"sv, project_name, FindClosestActorInFactionByLOS);
		a_vm->RegisterFunction("FindNearbyActors"sv, project_name, FindNearbyActors);
		a_vm->RegisterFunction("FindNearbyActorsInFaction"sv, project_name, FindNearbyActorsInFaction);
		a_vm->RegisterFunction("FindNearbyActorsInFactionByLOS"sv, project_name, FindNearbyActorsInFactionByLOS);
		a_vm->RegisterFunction("FindNearbyBooks"sv, project_name, FindNearbyBooks);
		a_vm->RegisterFunction("FindNearbyCommandedActors"sv, project_name, FindNearbyCommandedActors);
		a_vm->RegisterFunction("FindNearbyFollowers"sv, project_name, FindNearbyFollowers);
		a_vm->RegisterFunction("FindNearbySummons"sv, project_name, FindNearbySummons);
		a_vm->RegisterFunction("FindNearbyTeammates"sv, project_name, FindNearbyTeammates);
		a_vm->RegisterFunction("GetPermanentActorValue"sv, project_name, GetPermanentActorValue);

		return true;
	}
}