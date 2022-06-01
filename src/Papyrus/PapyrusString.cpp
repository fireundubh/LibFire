#pragma once

#include "PapyrusString.h"

template <typename T>
static auto intToHex(T i) -> std::string
{
	std::stringstream stream;
	stream << std::setfill('0') << std::setw(sizeof(T) * 2)
		   << std::hex << i;
	return stream.str();
}

static auto ltrim(std::string& s) -> void
{
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](const int ch) {
		return !std::isspace(ch);
	}));
}

static auto rtrim(std::string& s) -> void
{
	s.erase(std::find_if(s.rbegin(), s.rend(), [](const int ch) {
		return !std::isspace(ch);
	}).base(),
		s.end());
}

static auto split(const RE::BSFixedString& src, const char delimiter) -> std::vector<RE::BSFixedString>
{
	std::vector<RE::BSFixedString> vec;

	const auto* cstr = src.c_str();

	std::stringstream ss(cstr);

	while (ss.good()) {
		std::string substr;

		std::getline(ss, substr, delimiter);

		ltrim(substr);
		rtrim(substr);

		vec.emplace_back(substr.c_str());
	}

	return vec;
}

static auto splitAsFloat(const RE::BSFixedString& src, const char delimiter) -> std::vector<float>
{
	std::vector<float> vec;

	const auto* cstr = src.c_str();

	std::stringstream ss(cstr);

	while (ss.good()) {
		std::string substr;

		std::getline(ss, substr, delimiter);

		try {
			auto n = std::stof(substr);
			vec.push_back(n);
		} catch (std::invalid_argument& e) {
			logger::critical(e.what());
			vec.push_back(-1.f);
		} catch (std::out_of_range& e) {
			logger::critical(e.what());
			vec.push_back(-1.f);
		}
	}

	return vec;
}

static auto splitAsInt(const RE::BSFixedString& src, const char delimiter) -> std::vector<std::int32_t>
{
	std::vector<std::int32_t> vec;

	const auto* cstr = src.c_str();

	std::stringstream ss(cstr);

	while (ss.good()) {
		std::string substr;

		std::getline(ss, substr, delimiter);

		try {
			const auto n = std::stol(substr);
			vec.push_back(n);
		} catch (std::invalid_argument& e) {
			logger::critical(e.what());
			vec.push_back(-1);
		} catch (std::out_of_range& e) {
			logger::critical(e.what());
			vec.push_back(-1);
		}
	}

	return vec;
}

namespace PapyrusString
{
	auto ContainsText(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::BSFixedString a_text, RE::BSFixedString a_subtext) -> bool
	{
		auto text = std::string(a_text);
		auto subtext = std::string(a_subtext);

		std::transform(text.begin(), text.end(), text.begin(),
			[](unsigned char c) { return std::tolower(c); });

		std::transform(subtext.begin(), subtext.end(), subtext.begin(),
			[](unsigned char c) { return std::tolower(c); });

		auto it = std::search(text.begin(), text.end(), std::boyer_moore_searcher(subtext.begin(), subtext.end()));
		return it != text.end();
	}

	auto FormatFloat(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::BSFixedString a_format, std::vector<float> a_argv) -> RE::BSFixedString
	{
		if (a_format.empty()) {
			a_vm->TraceStack("asFormat cannot be empty", a_stackID, Severity::kInfo);
			return "";
		}

		if (a_argv.empty()) {
			a_vm->TraceStack("argValues cannot be empty", a_stackID, Severity::kInfo);
			return "";
		}

		auto format = std::string(a_format);
		auto argv = std::vector<float>(a_argv);

		if (argv.size() != 9) {
			while (argv.size() > 9) {
				argv.pop_back();
			}

			while (argv.size() < 9) {
				argv.emplace_back(0.0);
			}
		}

		return fmt::format(format, argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8]);
	}

	auto FormatInt(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::BSFixedString a_format, std::vector<std::int32_t> a_argv) -> RE::BSFixedString
	{
		if (a_format.empty()) {
			a_vm->TraceStack("asFormat cannot be empty", a_stackID, Severity::kInfo);
			return "";
		}

		if (a_argv.empty()) {
			a_vm->TraceStack("argValues cannot be empty", a_stackID, Severity::kInfo);
			return "";
		}

		auto format = std::string(a_format);
		auto argv = std::vector<std::int32_t>(a_argv);

		if (argv.size() != 9) {
			while (argv.size() > 9) {
				argv.pop_back();
			}

			while (argv.size() < 9) {
				argv.emplace_back(0);
			}
		}

		return fmt::format(format, argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8]);
	}

	auto FormatString(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::BSFixedString a_format, std::vector<RE::BSFixedString> a_argv) -> RE::BSFixedString
	{
		if (a_format.empty()) {
			a_vm->TraceStack("asFormat cannot be empty", a_stackID, Severity::kInfo);
			return "";
		}

		if (a_argv.empty()) {
			a_vm->TraceStack("argValues cannot be empty", a_stackID, Severity::kInfo);
			return "";
		}

		auto format = std::string(a_format);
		auto argv = std::vector<RE::BSFixedString>(a_argv);

		if (argv.size() != 9) {
			while (argv.size() > 9) {
				argv.pop_back();
			}

			while (argv.size() < 9) {
				argv.emplace_back("");
			}
		}

		return fmt::format(format, argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8]);
	}

	auto IntToHex(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, std::int32_t a_source) -> RE::BSFixedString
	{
		return intToHex(a_source);
	}

	auto StrToFloatArray(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::BSFixedString a_string, RE::BSFixedString a_delimiter) -> std::vector<float>
	{
		std::vector<float> vec;

		if (a_string.empty()) {
			a_vm->TraceStack("asString cannot be empty", a_stackID, Severity::kInfo);
			return vec;
		}

		if (a_delimiter.empty()) {
			a_vm->TraceStack("asDelimiter cannot be empty", a_stackID, Severity::kInfo);
			return vec;
		}

		const auto delimiter = a_delimiter[0];
		vec = splitAsFloat(a_string, delimiter);

		return vec;
	}

	auto StrToIntArray(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::BSFixedString a_string, RE::BSFixedString a_delimiter) -> std::vector<std::int32_t>
	{
		std::vector<std::int32_t> vec;

		if (a_string.empty()) {
			a_vm->TraceStack("asString cannot be empty", a_stackID, Severity::kInfo);
			return vec;
		}

		if (a_delimiter.empty()) {
			a_vm->TraceStack("asDelimiter cannot be empty", a_stackID, Severity::kInfo);
			return vec;
		}

		const auto delimiter = a_delimiter[0];
		vec = splitAsInt(a_string, delimiter);

		return vec;
	}

	auto SplitString(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::BSFixedString a_string, RE::BSFixedString a_delimiter) -> std::vector<RE::BSFixedString>
	{
		std::vector<RE::BSFixedString> vec;

		if (a_string.empty()) {
			a_vm->TraceStack("asString cannot be empty", a_stackID, Severity::kInfo);
			return vec;
		}

		if (a_delimiter.empty()) {
			a_vm->TraceStack("asDelimiter cannot be empty", a_stackID, Severity::kInfo);
			return vec;
		}

		const auto delimiter = a_delimiter[0];
		vec = split(a_string, delimiter);

		return vec;
	}

	auto WrapString(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::BSFixedString a_string, std::int32_t a_max_length) -> RE::BSFixedString
	{
		auto S = std::string(a_string);

		const auto lineWrap = std::regex{ "(.{1," + std::to_string(a_max_length) + "})(?: +|$)" };

		S = std::regex_replace(S, lineWrap, "$1\n");
		S.resize(S.size() - 1);

		return S;
	}

	auto RegisterFuncs(VM* a_vm) -> bool
	{
		if (!a_vm) {
			logger::info("PapyrusString - cannot get VMState"sv);
			return false;
		}
		
		auto* plugin = SKSE::PluginDeclaration::GetSingleton();
		auto project_name = plugin->GetName();

		a_vm->RegisterFunction("ContainsText"sv, project_name, ContainsText);
		a_vm->RegisterFunction("FormatFloat"sv, project_name, FormatFloat);
		a_vm->RegisterFunction("FormatInt"sv, project_name, FormatInt);
		a_vm->RegisterFunction("FormatString"sv, project_name, FormatString);
		a_vm->RegisterFunction("IntToHex"sv, project_name, IntToHex);
		a_vm->RegisterFunction("SplitString"sv, project_name, SplitString);
		a_vm->RegisterFunction("StrToFloatArray"sv, project_name, StrToFloatArray);
		a_vm->RegisterFunction("StrToIntArray"sv, project_name, StrToIntArray);
		a_vm->RegisterFunction("WrapString"sv, project_name, WrapString);

		return true;
	}
}