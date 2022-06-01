#pragma once

#include "PapyrusSpell.h"

namespace PapyrusSpell
{
	auto GetHighestMinSkillLevelForSpell(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::SpellItem* a_spell) -> std::uint32_t
	{
		if (!a_spell) {
			a_vm->TraceStack("akSpell cannot be None", a_stackID, Severity::kInfo);
			return 0;
		}

		const auto effects = a_spell->effects;

		if (effects.empty()) {
			return 0;
		}

		auto level = 0;

		for (const auto effect : effects) {
			if (const auto baseEffect = effect->baseEffect; baseEffect) {
				const auto effectData = baseEffect->data;
				level = std::max(level, effectData.minimumSkill);
			}
		}

		return level;
	}

	auto RegisterFuncs(VM* a_vm) -> bool
	{
		if (!a_vm) {
			logger::info("PapyrusSpell - cannot get VMState"sv);
			return false;
		}
		
		auto* plugin = SKSE::PluginDeclaration::GetSingleton();
		auto project_name = plugin->GetName();

		a_vm->RegisterFunction("GetHighestMinSkillLevelForSpell"sv, project_name, GetHighestMinSkillLevelForSpell);

		return true;
	}
}