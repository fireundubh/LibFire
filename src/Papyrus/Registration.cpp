#include "Papyrus/Registration.h"

#include "Papyrus/PapyrusActor.h"
#include "Papyrus/PapyrusFaction.h"
#include "Papyrus/PapyrusExperiments.h"
#include "Papyrus/PapyrusFormList.h"
#include "Papyrus/PapyrusObjectREFR.h"
#include "Papyrus/PapyrusRace.h"
#include "Papyrus/PapyrusSpell.h"
#include "Papyrus/PapyrusString.h"
#include "Papyrus/PapyrusTime.h"


namespace Papyrus
{
	auto Register() -> void
	{
		const auto papyrus = SKSE::GetPapyrusInterface();

		papyrus->Register(PapyrusActor::RegisterFuncs);
		logger::info("Registered actor functions"sv);

		papyrus->Register(PapyrusFaction::RegisterFuncs);
		logger::info("Registered faction functions"sv);

		papyrus->Register(PapyrusFormList::RegisterFuncs);
		logger::info("Registered formlist functions"sv);

		papyrus->Register(PapyrusObjectREFR::RegisterFuncs);
		logger::info("Registered object reference functions"sv);

		papyrus->Register(PapyrusRace::RegisterFuncs);
		logger::info("Registered race functions"sv);

		papyrus->Register(PapyrusSpell::RegisterFuncs);
		logger::info("Registered spell functions"sv);

		papyrus->Register(PapyrusString::RegisterFuncs);
		logger::info("Registered string functions"sv);

		papyrus->Register(PapyrusTime::RegisterFuncs);
		logger::info("Registered time functions"sv);

		papyrus->Register(PapyrusExperiments::RegisterFuncs);
		logger::info("Registered experimental functions"sv);
	}
}