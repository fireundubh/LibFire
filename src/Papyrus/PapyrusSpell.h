#pragma once

#pragma warning(disable : 4100)

namespace PapyrusSpell
{
	using VM = RE::BSScript::IVirtualMachine;
	using StackID = RE::VMStackID;
	using Severity = RE::BSScript::ErrorLogger::Severity;

	auto GetHighestMinSkillLevelForSpell(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::SpellItem* a_spell) -> std::uint32_t;

	auto RegisterFuncs(VM* a_vm) -> bool;
}
