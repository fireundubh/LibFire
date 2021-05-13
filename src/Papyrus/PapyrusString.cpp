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
	auto ContainsStr(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const RE::BSFixedString a_text, const RE::BSFixedString a_subtext) -> bool
	{
		std::string in = a_text.c_str();
		std::string needle = a_subtext.c_str();

		auto it = std::search(in.begin(), in.end(), std::boyer_moore_searcher(needle.begin(), needle.end()));
		return it != in.end();
	}

	auto ContainsText(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const RE::BSFixedString a_text, const RE::BSFixedString a_subtext) -> bool
	{
		std::string in = a_text.c_str();
		std::string needle = a_subtext.c_str();

		std::transform(in.begin(), in.end(), in.begin(),
			[](unsigned char c) { return std::tolower(c); });

		std::transform(needle.begin(), needle.end(), needle.begin(),
			[](unsigned char c) { return std::tolower(c); });

		auto it = std::search(in.begin(), in.end(), std::boyer_moore_searcher(needle.begin(), needle.end()));
		return it != in.end();
	}

	auto IntToHex(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const int32_t a_source) -> RE::BSFixedString
	{
		return intToHex(a_source).c_str();
	}

	auto StrToFloatArray(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const RE::BSFixedString a_source, const RE::BSFixedString a_delimiter) -> std::vector<float>
	{
		return splitAsFloat(a_source, a_delimiter[0]);
	}

	auto StrToIntArray(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const RE::BSFixedString a_source, const RE::BSFixedString a_delimiter) -> std::vector<std::int32_t>
	{
		return splitAsInt(a_source, a_delimiter[0]);
	}

	auto SplitString(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const RE::BSFixedString a_source, const RE::BSFixedString a_delimiter) -> std::vector<RE::BSFixedString>
	{
		return split(a_source, a_delimiter[0]);
	}

	auto WrapString(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const RE::BSFixedString a_source, const std::int32_t a_max_length) -> RE::BSFixedString
	{
		std::string s = a_source.c_str();

		const auto lineWrap = std::regex{ "(.{1," + std::to_string(a_max_length) + "})(?: +|$)" };

		s = std::regex_replace(s, lineWrap, "$1\n");
		s.resize(s.size() - 1);

		return s.c_str();
	}

	auto RegisterFuncs(VM* a_vm) -> bool
	{
		if (!a_vm) {
			logger::info("PapyrusString - cannot get VMState");
			return false;
		}

		a_vm->RegisterFunction("ContainsStr", PROJECT_NAME, ContainsStr);
		a_vm->RegisterFunction("ContainsText", PROJECT_NAME, ContainsText);
		a_vm->RegisterFunction("IntToHex", PROJECT_NAME, IntToHex);
		a_vm->RegisterFunction("SplitString", PROJECT_NAME, SplitString);
		a_vm->RegisterFunction("StrToFloatArray", PROJECT_NAME, StrToFloatArray);
		a_vm->RegisterFunction("StrToIntArray", PROJECT_NAME, StrToIntArray);
		a_vm->RegisterFunction("WrapString", PROJECT_NAME, WrapString);

		return true;
	}
}