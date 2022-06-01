#pragma once

#include "PapyrusTime.h"

namespace PapyrusTime
{
	auto GetCurrentHourOfDay(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*) -> float
	{
		auto* const calendar = RE::Calendar::GetSingleton();

		if (calendar == nullptr) {
			a_vm->TraceStack("Cannot initialize calendar singleton", a_stackID, Severity::kWarning);
			return false;
		}

		auto currentGameTime = calendar->GetCurrentGameTime();
		currentGameTime -= floorf(currentGameTime);
		currentGameTime *= 24.f;

		return currentGameTime;
	}

	auto RegisterFuncs(VM* a_vm) -> bool
	{
		if (!a_vm) {
			logger::info("PapyrusTime - cannot get VMState"sv);
			return false;
		}
		
		auto* plugin = SKSE::PluginDeclaration::GetSingleton();
		auto project_name = plugin->GetName();

		a_vm->RegisterFunction("GetCurrentHourOfDay"sv, project_name, GetCurrentHourOfDay);

		return true;
	}
}