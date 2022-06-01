#pragma once

#pragma warning(disable : 4100)

namespace PapyrusArray
{
	using VM = RE::BSScript::IVirtualMachine;
	using StackID = RE::VMStackID;
	using Severity = RE::BSScript::ErrorLogger::Severity;

	auto ArrayFindClosestActor(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, std::vector<RE::Actor*> a_actors, RE::TESObjectREFR* a_origin) -> std::int32_t;
	auto ArrayFindGlobalValue(VM* glob, StackID a_stackID, RE::StaticFunctionTag*, std::vector<RE::TESGlobal*> a_haystack, float a_needle) -> std::int32_t;

	auto RegisterFuncs(VM* a_vm) -> bool;
}
