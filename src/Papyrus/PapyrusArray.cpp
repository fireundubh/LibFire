#pragma once

#include "PapyrusArray.h"

static volatile float FloatMinNormal = 1.175494E-38f;
static volatile float FloatMinDenormal = 1.401298E-45f;
static bool IsFlushToZeroEnabled = static_cast<double>(FloatMinDenormal) == 0.0;

static float Epsilon = IsFlushToZeroEnabled ? FloatMinNormal : FloatMinDenormal;

static auto approximately(const float a, const float b) -> bool
{
	return fabs(b - a) < std::max(0.000001f * std::max(fabs(a), fabs(b)), Epsilon * 8);
}

namespace PapyrusArray
{
	auto ArrayFindClosestActor(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, std::vector<RE::Actor*> a_actors, RE::TESObjectREFR* a_origin) -> std::int32_t
	{
		if (a_actors.empty()) {
			a_vm->TraceStack("argHaystack cannot be empty", a_stackID, Severity::kInfo);
			return -1;
		}

		std::multimap<float, RE::Actor*> results;

		for (auto* actor : a_actors) {
			auto distance = a_origin->As<RE::NiPoint3>()->GetSquaredDistance(actor->GetPosition());
			results.insert(std::pair<float, RE::Actor*>(distance, actor));
		}

		auto needle = results.cbegin()->second;
		auto it = std::find(a_actors.cbegin(), a_actors.cend(), needle);

		return it != a_actors.cend() ? (std::int32_t)(it - a_actors.cbegin()) : -1;
	}

	auto ArrayFindGlobalValue(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, std::vector<RE::TESGlobal*> a_haystack, float a_needle) -> std::int32_t
	{
		if (a_haystack.empty()) {
			a_vm->TraceStack("argHaystack cannot be empty", a_stackID, Severity::kInfo);
			return -1;
		}

		for (std::int32_t i = 0; i < a_haystack.size(); ++i) {
			const auto* glob = a_haystack[i];
			if (glob->value == a_needle || approximately(glob->value, a_needle)) {
				return i;
			}
		}

		return -1;
	}

	auto RegisterFuncs(VM* a_vm) -> bool
	{
		if (!a_vm) {
			logger::info("PapyrusArray - cannot get VMState"sv);
			return false;
		}
		
		auto* plugin = SKSE::PluginDeclaration::GetSingleton();
		auto project_name = plugin->GetName();

		a_vm->RegisterFunction("ArrayFindClosestActor"sv, project_name, ArrayFindClosestActor);
		a_vm->RegisterFunction("ArrayFindGlobalValue"sv, project_name, ArrayFindGlobalValue);

		return true;
	}
}