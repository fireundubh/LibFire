#pragma once

#include "PapyrusFormList.h"

namespace PapyrusFormList
{
	auto SearchListForForms(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::BGSListForm* a_list, std::vector<RE::TESForm*> a_forms) -> std::vector<bool>
	{
		std::vector<bool> vec;

		if (!a_list) {
			a_vm->TraceStack("akHaystack cannot be None", a_stackID, Severity::kInfo);
			return vec;
		}

		if (a_list->forms.empty()) {
			a_vm->TraceStack("akHaystack cannot be empty", a_stackID, Severity::kInfo);
			return vec;
		}

		if (a_forms.empty()) {
			a_vm->TraceStack("argNeedles cannot be None", a_stackID, Severity::kInfo);
			return vec;
		}

		for (auto* form : a_forms) {
			vec.push_back(form != nullptr && a_list->HasForm(form));
		}

		return vec;
	}

	auto SearchListsForForm(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::BGSListForm* a_lists, RE::TESForm* a_form) -> std::vector<bool>
	{
		std::vector<bool> vec;

		if (a_form == nullptr) {
			a_vm->TraceStack("akNeedle cannot be None", a_stackID, Severity::kInfo);
			return vec;
		}

		if (a_lists == nullptr) {
			a_vm->TraceStack("akHaystack cannot be None", a_stackID, Severity::kInfo);
			return vec;
		}

		if (a_lists->forms.empty()) {
			a_vm->TraceStack("akHaystack cannot be empty", a_stackID, Severity::kInfo);
			return vec;
		}

		for (auto& column : a_lists->forms) {
			if (auto* row = column->As<RE::BGSListForm>(); row) {
				vec.push_back(!row->forms.empty() && row->HasForm(a_form));
			}
		}

		return vec;
	}

	auto RegisterFuncs(VM* a_vm) -> bool
	{
		if (!a_vm) {
			logger::info("PapyrusFormList - cannot get VMState"sv);
			return false;
		}

		a_vm->RegisterFunction("SearchListForForms"sv, PROJECT_NAME, SearchListForForms);
		a_vm->RegisterFunction("SearchListsForForm"sv, PROJECT_NAME, SearchListsForForm);

		return true;
	}
}