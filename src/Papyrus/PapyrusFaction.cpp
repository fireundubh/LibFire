#pragma once

#include "PapyrusFaction.h"

namespace PapyrusFaction
{
	auto SetAllies(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESFaction* a_faction, RE::BGSListForm* a_factions, const bool a_selfIsFriendToOther, const bool a_otherIsFriendToSelf) -> void
	{
		if (!a_faction) {
			a_vm->TraceStack("akFaction cannot be None", a_stackID, Severity::kWarning);
			return;
		}

		if (!a_factions) {
			a_vm->TraceStack("akFactions cannot be None", a_stackID, Severity::kWarning);
			return;
		}

		bool forceRefresh = false;

		for (auto& form : a_factions->forms) {
			if (form == nullptr) {
				continue;
			}

			if (auto* const otherFaction = form->As<RE::TESFaction>(); otherFaction) {
				a_faction->SetFactionFightReaction(otherFaction, a_selfIsFriendToOther ? RE::FIGHT_REACTION::kFriend : RE::FIGHT_REACTION::kAlly);
				otherFaction->SetFactionFightReaction(a_faction, a_otherIsFriendToSelf ? RE::FIGHT_REACTION::kFriend : RE::FIGHT_REACTION::kAlly);

				if (!forceRefresh) {
					forceRefresh = true;
				}
			}
		}

		if (forceRefresh) {
			if (auto* const processLists = RE::ProcessLists::GetSingleton(); processLists) {
				processLists->ClearCachedFactionFightReactions();
			}
		}
	}

	auto SetEnemies(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESFaction* a_faction, RE::BGSListForm* a_factions, const bool a_selfIsNeutralToOther, const bool a_otherIsNeutralToSelf) -> void
	{
		if (!a_faction) {
			a_vm->TraceStack("akFaction cannot be None", a_stackID, Severity::kWarning);
			return;
		}

		if (!a_factions) {
			a_vm->TraceStack("akFactions cannot be None", a_stackID, Severity::kWarning);
			return;
		}

		bool forceRefresh = false;

		for (auto& form : a_factions->forms) {
			if (form == nullptr) {
				continue;
			}

			if (auto* const otherFaction = form->As<RE::TESFaction>(); otherFaction) {
				a_faction->SetFactionFightReaction(otherFaction, a_selfIsNeutralToOther ? RE::FIGHT_REACTION::kNeutral : RE::FIGHT_REACTION::kEnemy);
				otherFaction->SetFactionFightReaction(a_faction, a_otherIsNeutralToSelf ? RE::FIGHT_REACTION::kNeutral : RE::FIGHT_REACTION::kEnemy);

				if (!forceRefresh) {
					forceRefresh = true;
				}
			}
		}

		if (forceRefresh) {
			if (auto* const processLists = RE::ProcessLists::GetSingleton(); processLists) {
				processLists->ClearCachedFactionFightReactions();
			}
		}
	}

	auto RegisterFuncs(VM* a_vm) -> bool
	{
		if (!a_vm) {
			logger::info("PapyrusFaction - cannot get VMState");
			return false;
		}

		a_vm->RegisterFunction("SetAllies", PROJECT_NAME, SetAllies);
		a_vm->RegisterFunction("SetEnemies", PROJECT_NAME, SetEnemies);

		return true;
	}
}