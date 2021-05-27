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
		logger::info("Registered actor functions");

		papyrus->Register(PapyrusFaction::RegisterFuncs);
		logger::info("Registered faction functions");

		papyrus->Register(PapyrusFormList::RegisterFuncs);
		logger::info("Registered formlist functions");

		papyrus->Register(PapyrusObjectREFR::RegisterFuncs);
		logger::info("Registered object reference functions");

		papyrus->Register(PapyrusRace::RegisterFuncs);
		logger::info("Registered race functions");

		papyrus->Register(PapyrusSpell::RegisterFuncs);
		logger::info("Registered spell functions");

		papyrus->Register(PapyrusString::RegisterFuncs);
		logger::info("Registered string functions");

		papyrus->Register(PapyrusTime::RegisterFuncs);
		logger::info("Registered time functions");

		papyrus->Register(PapyrusExperiments::RegisterFuncs);
		logger::info("Registered experimental functions");
	}
}