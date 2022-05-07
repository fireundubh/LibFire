#pragma once

#pragma warning(disable : 4244)

namespace ActorValueHelper
{
	auto GetActorValueIdFromName(const char* a_name) -> std::int32_t;
	auto ActorValueToString(RE::ActorValue a_actorValue) -> RE::BSFixedString;
}
