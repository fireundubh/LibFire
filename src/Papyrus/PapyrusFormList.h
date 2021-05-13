#pragma once

#pragma warning(disable : 4100)

namespace PapyrusFormList
{
	using VM = RE::BSScript::IVirtualMachine;
	using StackID = RE::VMStackID;
	using Severity = RE::BSScript::ErrorLogger::Severity;

	auto SearchListForForms(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::BGSListForm* a_list, std::vector<RE::TESForm*> a_forms) -> std::vector<bool>;
	auto SearchListsForForm(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::BGSListForm* a_lists, RE::TESForm* a_form) -> std::vector<bool>;

	auto RegisterFuncs(VM* a_vm) -> bool;
}
