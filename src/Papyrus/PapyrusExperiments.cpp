#pragma once

#include "PapyrusExperiments.h"

namespace PapyrusExperiments
{
	auto FindContainedFormsOfFormType(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESObjectREFR* a_container, std::uint32_t a_formType) -> std::vector<RE::TESForm*>
	{
		std::vector<RE::TESForm*> vec;

		if (!a_container) {
			a_vm->TraceStack("akContainer cannot be None", a_stackID, Severity::kInfo);
			return vec;
		}

		const auto inv = a_container->GetInventory();

		const auto formType = static_cast<RE::FormType>(a_formType);

		for (auto& [item, data] : inv) {
			auto& [count, entry] = data;
			if (item->Is(formType)) {
				vec.emplace_back(item);
			}
		}

		return vec;
	}

	auto SetContainedFormDisplayNames(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESObjectREFR* a_container, std::vector<RE::TESForm*> a_forms, std::vector<RE::BSFixedString> a_names, bool a_force) -> std::uint32_t
	{
		if (!a_container) {
			a_vm->TraceStack("akContainer cannot be None", a_stackID, Severity::kInfo);
			return 0;
		}

		if (a_forms.empty()) {
			a_vm->TraceStack("argForms cannot be empty", a_stackID, Severity::kInfo);
			return 0;
		}

		if (a_names.empty()) {
			a_vm->TraceStack("argNames cannot be empty", a_stackID, Severity::kInfo);
			return 0;
		}

		if (a_forms.size() != a_names.size()) {
			a_vm->TraceStack("argForms and argNames must be the same size", a_stackID, Severity::kInfo);
			return 0;
		}

		std::uint32_t result = 0;

		const auto inv = a_container->GetInventory();

		for (auto& [item, data] : inv) {
			auto& [count, entry] = data;

			if (auto it = std::find(a_forms.begin(), a_forms.end(), item); it != a_forms.end()) {
				auto idx = it - a_forms.begin();

				auto displayName = a_names[idx];

				if (displayName.empty() || displayName == item->GetName() || displayName == entry->GetDisplayName()) {
					continue;
				}

				std::string lognames = fmt::format("item name = {}, entry display name = {}, new display name = {}", item->GetName(), entry->GetDisplayName(), displayName);
				a_vm->TraceStack(lognames.c_str(), a_stackID, Severity::kInfo);

				if (!entry->extraLists) {
					entry->extraLists = new RE::BSSimpleList<RE::ExtraDataList*>;

					auto extraList = new RE::ExtraDataList();
					auto xTextData = new RE::ExtraTextDisplayData(displayName.c_str());
					extraList->Add(xTextData);

					entry->extraLists->push_front(extraList);
					result += 1;
				} else if (entry->extraLists) {
					for (auto& xList : *entry->extraLists) {
						if (xList) {
							auto xTextData = xList->GetByType<RE::ExtraTextDisplayData>();
							if (xTextData) {
								bool inUse = xTextData->displayNameText || xTextData->ownerQuest;
								if (inUse && a_force) {
									xTextData->displayNameText = nullptr;
									xTextData->ownerQuest = nullptr;
								}
								xTextData->SetName(displayName.c_str());
								result += 1;
							} else {
								xTextData = new RE::ExtraTextDisplayData(displayName.c_str());
								xList->Add(xTextData);
								result += 1;
							}
						}
					}
				}
			}
		}

		return result;
	}

	auto RegisterFuncs(VM* a_vm) -> bool
	{
		if (!a_vm) {
			logger::info("PapyrusExperiments - cannot get VMState");
			return false;
		}

		a_vm->RegisterFunction("FindContainedFormsOfFormType", PROJECT_NAME, FindContainedFormsOfFormType);
		a_vm->RegisterFunction("SetContainedFormDisplayNames", PROJECT_NAME, SetContainedFormDisplayNames);

		return true;
	}
}