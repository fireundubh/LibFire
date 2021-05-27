#pragma once

#pragma warning(disable : 4100)

namespace PapyrusExperiments
{
	using VM = RE::BSScript::IVirtualMachine;
	using StackID = RE::VMStackID;
	using Severity = RE::BSScript::ErrorLogger::Severity;

	auto FindContainedFormsOfFormType(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESObjectREFR* a_container, std::uint32_t a_formType) -> std::vector<RE::TESForm*>;
	auto SetContainedFormDisplayNames(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESObjectREFR* a_container, std::vector<RE::TESForm*> a_forms, std::vector<RE::BSFixedString> a_names, bool a_force) -> std::uint32_t;

	auto RegisterFuncs(VM* a_vm) -> bool;
}
