#pragma once

#pragma warning(disable : 4244)

namespace ActorValueHelper
{
	auto StringToActorValue(const RE::BSFixedString& a_string) -> RE::ActorValue;
	auto ActorValueToString(RE::ActorValue a_actorValue) -> RE::BSFixedString;
}
