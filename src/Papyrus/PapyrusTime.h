#pragma once

#pragma warning(disable : 4100)

namespace PapyrusTime
{
	using VM = RE::BSScript::IVirtualMachine;
	using StackID = RE::VMStackID;
	using Severity = RE::BSScript::ErrorLogger::Severity;

	auto GetCurrentHourOfDay(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*) -> float;

	auto RegisterFuncs(VM* a_vm) -> bool;
}
