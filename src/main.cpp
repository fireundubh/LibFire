#include "Papyrus/Registration.h"

namespace
{
	void InitializeLog(const std::string_view a_project)
	{
#ifndef NDEBUG
		auto sink = std::make_shared<spdlog::sinks::msvc_sink_mt>();
#else
		auto path = logger::log_directory();
		if (!path) {
			util::report_and_fail("Failed to find standard logging directory"sv);
		}

		*path /= fmt::format("{}.log"sv, a_project);
		auto sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(path->string(), true);
#endif

#ifndef NDEBUG
		const auto level = spdlog::level::trace;
#else
		const auto level = spdlog::level::info;
#endif

		auto log = std::make_shared<spdlog::logger>("global log"s, std::move(sink));
		log->set_level(level);
		log->flush_on(level);

		spdlog::set_default_logger(std::move(log));
		spdlog::set_pattern("%g(%#): [%^%l%$] %v"s);
	}
}

SKSEPluginLoad(const SKSE::LoadInterface* a_skse)
{
	auto* plugin = SKSE::PluginDeclaration::GetSingleton();
	auto project_name = plugin->GetName();
	auto project_version = plugin->GetVersion();

	InitializeLog(project_name);

	logger::info("{} v{} is loading..."sv, project_name, project_version);

	Init(a_skse);

	Papyrus::Register();

	logger::info("{} has finished loading."sv, project_name);
	return true;
}
