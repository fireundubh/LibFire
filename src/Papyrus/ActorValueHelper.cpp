#pragma once

namespace ActorValueHelper
{
	auto StringToActorValue(const RE::BSFixedString& a_string) -> RE::ActorValue
	{
		std::string S(a_string);

		std::transform(S.begin(), S.end(), S.begin(),
					   [](unsigned char c) { return std::tolower(c); });

		if (S == "none")
			return RE::ActorValue::kNone;
		if (S == "aggression")
			return RE::ActorValue::kAggresion;
		if (S == "confidence")
			return RE::ActorValue::kConfidence;
		if (S == "energy")
			return RE::ActorValue::kEnergy;
		if (S == "morality")
			return RE::ActorValue::kMorality;
		if (S == "mood")
			return RE::ActorValue::kMood;
		if (S == "assistance")
			return RE::ActorValue::kAssistance;
		if (S == "onehanded")
			return RE::ActorValue::kOneHanded;
		if (S == "twohanded")
			return RE::ActorValue::kTwoHanded;
		if (S == "archery")
			return RE::ActorValue::kArchery;
		if (S == "block")
			return RE::ActorValue::kBlock;
		if (S == "smithing")
			return RE::ActorValue::kSmithing;
		if (S == "heavyarmor")
			return RE::ActorValue::kHeavyArmor;
		if (S == "lightarmor")
			return RE::ActorValue::kLightArmor;
		if (S == "pickpocket")
			return RE::ActorValue::kPickpocket;
		if (S == "lockpicking")
			return RE::ActorValue::kLockpicking;
		if (S == "sneak")
			return RE::ActorValue::kSneak;
		if (S == "alchemy")
			return RE::ActorValue::kAlchemy;
		if (S == "speech")
			return RE::ActorValue::kSpeech;
		if (S == "alteration")
			return RE::ActorValue::kAlteration;
		if (S == "conjuration")
			return RE::ActorValue::kConjuration;
		if (S == "destruction")
			return RE::ActorValue::kDestruction;
		if (S == "illusion")
			return RE::ActorValue::kIllusion;
		if (S == "restoration")
			return RE::ActorValue::kRestoration;
		if (S == "enchanting")
			return RE::ActorValue::kEnchanting;
		if (S == "health")
			return RE::ActorValue::kHealth;
		if (S == "magicka")
			return RE::ActorValue::kMagicka;
		if (S == "stamina")
			return RE::ActorValue::kStamina;
		if (S == "healrate")
			return RE::ActorValue::kHealRate;
		if (S == "magickarate")
			return RE::ActorValue::kMagickaRate;
		if (S == "staminarate")
			return RE::ActorValue::KStaminaRate;
		if (S == "speedmult")
			return RE::ActorValue::kSpeedMult;
		if (S == "inventoryweight")
			return RE::ActorValue::kInventoryWeight;
		if (S == "carryweight")
			return RE::ActorValue::kCarryWeight;
		if (S == "criticalchance")
			return RE::ActorValue::kCriticalChance;
		if (S == "meleedamage")
			return RE::ActorValue::kMeleeDamage;
		if (S == "unarmeddamage")
			return RE::ActorValue::kUnarmedDamage;
		if (S == "mass")
			return RE::ActorValue::kMass;
		if (S == "voicepoints")
			return RE::ActorValue::kVoicePoints;
		if (S == "voicerate")
			return RE::ActorValue::kVoiceRate;
		if (S == "damageresist")
			return RE::ActorValue::kDamageResist;
		if (S == "poisonresist")
			return RE::ActorValue::kPoisonResist;
		if (S == "resistfire")
			return RE::ActorValue::kResistFire;
		if (S == "resistshock")
			return RE::ActorValue::kResistShock;
		if (S == "resistfrost")
			return RE::ActorValue::kResistFrost;
		if (S == "resistmagic")
			return RE::ActorValue::kResistMagic;
		if (S == "resistdisease")
			return RE::ActorValue::kResistDisease;
		if (S == "perceptioncondition")
			return RE::ActorValue::kUnknown46;
		if (S == "endurancecondition")
			return RE::ActorValue::kUnknown47;
		if (S == "leftattackcondition")
			return RE::ActorValue::kUnknown48;
		if (S == "rightattackcondition")
			return RE::ActorValue::kUnknown49;
		if (S == "leftmobilitycondition")
			return RE::ActorValue::kUnknown50;
		if (S == "rightmobilitycondition")
			return RE::ActorValue::kUnknown51;
		if (S == "braincondition")
			return RE::ActorValue::kUnknown52;
		if (S == "paralysis")
			return RE::ActorValue::kParalysis;
		if (S == "invisibility")
			return RE::ActorValue::kInvisibility;
		if (S == "nighteye")
			return RE::ActorValue::kNightEye;
		if (S == "detectliferange")
			return RE::ActorValue::kDetectLifeRange;
		if (S == "waterbreathing")
			return RE::ActorValue::kWaterBreathing;
		if (S == "waterwalking")
			return RE::ActorValue::kWaterWalking;
		if (S == "unknown59")
			return RE::ActorValue::kUnknown59;
		if (S == "fame")
			return RE::ActorValue::kFame;
		if (S == "infamy")
			return RE::ActorValue::kInfamy;
		if (S == "jumpingbonus")
			return RE::ActorValue::kJumpingBonus;
		if (S == "wardpower")
			return RE::ActorValue::kWardPower;
		if (S == "rightitemcharge")
			return RE::ActorValue::kRightItemCharge;
		if (S == "armorperks")
			return RE::ActorValue::kArmorPerks;
		if (S == "shieldperks")
			return RE::ActorValue::kShieldPerks;
		if (S == "warddeflection")
			return RE::ActorValue::kWardDeflection;
		if (S == "variable01")
			return RE::ActorValue::kVariable01;
		if (S == "variable02")
			return RE::ActorValue::kVariable02;
		if (S == "variable03")
			return RE::ActorValue::kVariable03;
		if (S == "variable04")
			return RE::ActorValue::kVariable04;
		if (S == "variable05")
			return RE::ActorValue::kVariable05;
		if (S == "variable06")
			return RE::ActorValue::kVariable06;
		if (S == "variable07")
			return RE::ActorValue::kVariable07;
		if (S == "variable08")
			return RE::ActorValue::kVariable08;
		if (S == "variable09")
			return RE::ActorValue::kVariable09;
		if (S == "variable10")
			return RE::ActorValue::kVariable10;
		if (S == "bowspeedbonus")
			return RE::ActorValue::kBowSpeedBonus;
		if (S == "favoractive")
			return RE::ActorValue::kFavorActive;
		if (S == "favorsperday")
			return RE::ActorValue::kFavorsPerDay;
		if (S == "favorsperdaytimer")
			return RE::ActorValue::kFavorsPerDayTimer;
		if (S == "leftitemcharge")
			return RE::ActorValue::kLeftItemCharge;
		if (S == "absorbchance")
			return RE::ActorValue::kAbsorbChance;
		if (S == "blindness")
			return RE::ActorValue::kBlindness;
		if (S == "weaponspeedmult")
			return RE::ActorValue::kWeaponSpeedMult;
		if (S == "shoutrecoverymult")
			return RE::ActorValue::kShoutRecoveryMult;
		if (S == "bowstaggerbonus")
			return RE::ActorValue::kBowStaggerBonus;
		if (S == "telekinesis")
			return RE::ActorValue::kTelekinesis;
		if (S == "favorpointsbonus")
			return RE::ActorValue::kFavorPointsBonus;
		if (S == "lastbribedintimidated")
			return RE::ActorValue::kLastBribedIntimidated;
		if (S == "lastflattered")
			return RE::ActorValue::kLastFlattered;
		if (S == "movementnoisemult")
			return RE::ActorValue::kMovementNoiseMult;
		if (S == "bypassvendorstolencheck")
			return RE::ActorValue::kBypassVendorStolenCheck;
		if (S == "bypassvendorkeywordcheck")
			return RE::ActorValue::kBypassVendorKeywordCheck;
		if (S == "waitingforplayer")
			return RE::ActorValue::kWaitingForPlayer;
		if (S == "onehandedmodifier")
			return RE::ActorValue::kOneHandedModifier;
		if (S == "twohandedmodifier")
			return RE::ActorValue::kTwoHandedModifier;
		if (S == "marksmanmodifier")
			return RE::ActorValue::kMarksmanModifier;
		if (S == "blockmodifier")
			return RE::ActorValue::kBlockModifier;
		if (S == "smithingmodifier")
			return RE::ActorValue::kSmithingModifier;
		if (S == "heavyarmormodifier")
			return RE::ActorValue::kHeavyArmorModifier;
		if (S == "lightarmormodifier")
			return RE::ActorValue::kLightArmorModifier;
		if (S == "pickpocketmodifier")
			return RE::ActorValue::kPickpocketModifier;
		if (S == "lockpickingmodifier")
			return RE::ActorValue::kLockpickingModifier;
		if (S == "sneakingmodifier")
			return RE::ActorValue::kSneakingModifier;
		if (S == "alchemymodifier")
			return RE::ActorValue::kAlchemyModifier;
		if (S == "speechcraftmodifier")
			return RE::ActorValue::kSpeechcraftModifier;
		if (S == "alterationmodifier")
			return RE::ActorValue::kAlterationModifier;
		if (S == "conjurationmodifier")
			return RE::ActorValue::kConjurationModifier;
		if (S == "destructionmodifier")
			return RE::ActorValue::kDestructionModifier;
		if (S == "illusionmodifier")
			return RE::ActorValue::kIllusionModifier;
		if (S == "restorationmodifier")
			return RE::ActorValue::kRestorationModifier;
		if (S == "enchantingmodifier")
			return RE::ActorValue::kEnchantingModifier;
		if (S == "onehandedskilladvance")
			return RE::ActorValue::kOneHandedSkillAdvance;
		if (S == "twohandedskilladvance")
			return RE::ActorValue::kTwoHandedSkillAdvance;
		if (S == "marksmanskilladvance")
			return RE::ActorValue::kMarksmanSkillAdvance;
		if (S == "blockskilladvance")
			return RE::ActorValue::kBlockSkillAdvance;
		if (S == "smithingskilladvance")
			return RE::ActorValue::kSmithingSkillAdvance;
		if (S == "heavyarmorskilladvance")
			return RE::ActorValue::kHeavyArmorSkillAdvance;
		if (S == "lightarmorskilladvance")
			return RE::ActorValue::kLightArmorSkillAdvance;
		if (S == "pickpocketskilladvance")
			return RE::ActorValue::kPickpocketSkillAdvance;
		if (S == "lockpickingskilladvance")
			return RE::ActorValue::kLockpickingSkillAdvance;
		if (S == "sneakingskilladvance")
			return RE::ActorValue::kSneakingSkillAdvance;
		if (S == "alchemyskilladvance")
			return RE::ActorValue::kAlchemySkillAdvance;
		if (S == "speechcraftskilladvance")
			return RE::ActorValue::kSpeechcraftSkillAdvance;
		if (S == "alterationskilladvance")
			return RE::ActorValue::kAlterationSkillAdvance;
		if (S == "conjurationskilladvance")
			return RE::ActorValue::kConjurationSkillAdvance;
		if (S == "destructionskilladvance")
			return RE::ActorValue::kDestructionSkillAdvance;
		if (S == "illusionskilladvance")
			return RE::ActorValue::kIllusionSkillAdvance;
		if (S == "restorationskilladvance")
			return RE::ActorValue::kRestorationSkillAdvance;
		if (S == "enchantingskilladvance")
			return RE::ActorValue::kEnchantingSkillAdvance;
		if (S == "leftweaponspeedmultiply")
			return RE::ActorValue::kLeftWeaponSpeedMultiply;
		if (S == "dragonsouls")
			return RE::ActorValue::kDragonSouls;
		if (S == "combathealthregenmultiply")
			return RE::ActorValue::kCombatHealthRegenMultiply;
		if (S == "onehandedpowermodifier")
			return RE::ActorValue::kOneHandedPowerModifier;
		if (S == "twohandedpowermodifier")
			return RE::ActorValue::kTwoHandedPowerModifier;
		if (S == "marksmanpowermodifier")
			return RE::ActorValue::kMarksmanPowerModifier;
		if (S == "blockpowermodifier")
			return RE::ActorValue::kBlockPowerModifier;
		if (S == "smithingpowermodifier")
			return RE::ActorValue::kSmithingPowerModifier;
		if (S == "heavyarmorpowermodifier")
			return RE::ActorValue::kHeavyArmorPowerModifier;
		if (S == "lightarmorpowermodifier")
			return RE::ActorValue::kLightArmorPowerModifier;
		if (S == "pickpocketpowermodifier")
			return RE::ActorValue::kPickpocketPowerModifier;
		if (S == "lockpickingpowermodifier")
			return RE::ActorValue::kLockpickingPowerModifier;
		if (S == "sneakingpowermodifier")
			return RE::ActorValue::kSneakingPowerModifier;
		if (S == "alchemypowermodifier")
			return RE::ActorValue::kAlchemyPowerModifier;
		if (S == "speechcraftpowermodifier")
			return RE::ActorValue::kSpeechcraftPowerModifier;
		if (S == "alterationpowermodifier")
			return RE::ActorValue::kAlterationPowerModifier;
		if (S == "conjurationpowermodifier")
			return RE::ActorValue::kConjurationPowerModifier;
		if (S == "destructionpowermodifier")
			return RE::ActorValue::kDestructionPowerModifier;
		if (S == "illusionpowermodifier")
			return RE::ActorValue::kIllusionPowerModifier;
		if (S == "restorationpowermodifier")
			return RE::ActorValue::kRestorationPowerModifier;
		if (S == "enchantingpowermodifier")
			return RE::ActorValue::kEnchantingPowerModifier;
		if (S == "dragonrend")
			return RE::ActorValue::kDragonRend;
		if (S == "attackdamagemult")
			return RE::ActorValue::kAttackDamageMult;
		if (S == "healratemult")
			return RE::ActorValue::kHealRateMult;
		if (S == "magickaratemult")
			return RE::ActorValue::kMagickaRateMult;
		if (S == "staminaratemult")
			return RE::ActorValue::kStaminaRateMult;
		if (S == "werewolfperks")
			return RE::ActorValue::kWerewolfPerks;
		if (S == "vampireperks")
			return RE::ActorValue::kVampirePerks;
		if (S == "grabactoroffset")
			return RE::ActorValue::kGrabActorOffset;
		if (S == "grabbed")
			return RE::ActorValue::kGrabbed;
		if (S == "deprecated05")
			return RE::ActorValue::kUnknown162;
		if (S == "reflectdamage")
			return RE::ActorValue::kReflectDamage;

		return RE::ActorValue::kNone;
	}

	auto ActorValueToString(const RE::ActorValue a_actorValue) -> RE::BSFixedString
	{
		switch (a_actorValue) {
			case RE::ActorValue::kNone:
				return "None";
			case RE::ActorValue::kAggresion:
				return "Aggression";
			case RE::ActorValue::kConfidence:
				return "Confidence";
			case RE::ActorValue::kEnergy:
				return "Energy";
			case RE::ActorValue::kMorality:
				return "Morality";
			case RE::ActorValue::kMood:
				return "Mood";
			case RE::ActorValue::kAssistance:
				return "Assistance";
			case RE::ActorValue::kOneHanded:
				return "OneHanded";
			case RE::ActorValue::kTwoHanded:
				return "TwoHanded";
			case RE::ActorValue::kArchery:
				return "Archery";
			case RE::ActorValue::kBlock:
				return "Block";
			case RE::ActorValue::kSmithing:
				return "Smithing";
			case RE::ActorValue::kHeavyArmor:
				return "HeavyArmor";
			case RE::ActorValue::kLightArmor:
				return "LightArmor";
			case RE::ActorValue::kPickpocket:
				return "Pickpocket";
			case RE::ActorValue::kLockpicking:
				return "Lockpicking";
			case RE::ActorValue::kSneak:
				return "Sneak";
			case RE::ActorValue::kAlchemy:
				return "Alchemy";
			case RE::ActorValue::kSpeech:
				return "Speech";
			case RE::ActorValue::kAlteration:
				return "Alteration";
			case RE::ActorValue::kConjuration:
				return "Conjuration";
			case RE::ActorValue::kDestruction:
				return "Destruction";
			case RE::ActorValue::kIllusion:
				return "Illusion";
			case RE::ActorValue::kRestoration:
				return "Restoration";
			case RE::ActorValue::kEnchanting:
				return "Enchanting";
			case RE::ActorValue::kHealth:
				return "Health";
			case RE::ActorValue::kMagicka:
				return "Magicka";
			case RE::ActorValue::kStamina:
				return "Stamina";
			case RE::ActorValue::kHealRate:
				return "HealRate";
			case RE::ActorValue::kMagickaRate:
				return "MagickaRate";
			case RE::ActorValue::KStaminaRate:
				return "StaminaRate";
			case RE::ActorValue::kSpeedMult:
				return "SpeedMult";
			case RE::ActorValue::kInventoryWeight:
				return "InventoryWeight";
			case RE::ActorValue::kCarryWeight:
				return "CarryWeight";
			case RE::ActorValue::kCriticalChance:
				return "CriticalChance";
			case RE::ActorValue::kMeleeDamage:
				return "MeleeDamage";
			case RE::ActorValue::kUnarmedDamage:
				return "UnarmedDamage";
			case RE::ActorValue::kMass:
				return "Mass";
			case RE::ActorValue::kVoicePoints:
				return "VoicePoints";
			case RE::ActorValue::kVoiceRate:
				return "VoiceRate";
			case RE::ActorValue::kDamageResist:
				return "DamageResist";
			case RE::ActorValue::kPoisonResist:
				return "PoisonResist";
			case RE::ActorValue::kResistFire:
				return "ResistFire";
			case RE::ActorValue::kResistShock:
				return "ResistShock";
			case RE::ActorValue::kResistFrost:
				return "ResistFrost";
			case RE::ActorValue::kResistMagic:
				return "ResistMagic";
			case RE::ActorValue::kResistDisease:
				return "ResistDisease";
			case RE::ActorValue::kUnknown46:
				return "PerceptionCondition";
			case RE::ActorValue::kUnknown47:
				return "EnduranceCondition";
			case RE::ActorValue::kUnknown48:
				return "LeftAttackCondition";
			case RE::ActorValue::kUnknown49:
				return "RightAttackCondition";
			case RE::ActorValue::kUnknown50:
				return "LeftMobilityCondition";
			case RE::ActorValue::kUnknown51:
				return "RightMobilityCondition";
			case RE::ActorValue::kUnknown52:
				return "BrainCondition";
			case RE::ActorValue::kParalysis:
				return "Paralysis";
			case RE::ActorValue::kInvisibility:
				return "Invisibility";
			case RE::ActorValue::kNightEye:
				return "NightEye";
			case RE::ActorValue::kDetectLifeRange:
				return "DetectLifeRange";
			case RE::ActorValue::kWaterBreathing:
				return "WaterBreathing";
			case RE::ActorValue::kWaterWalking:
				return "WaterWalking";
			case RE::ActorValue::kUnknown59:
				return "Unknown59";
			case RE::ActorValue::kFame:
				return "Fame";
			case RE::ActorValue::kInfamy:
				return "Infamy";
			case RE::ActorValue::kJumpingBonus:
				return "JumpingBonus";
			case RE::ActorValue::kWardPower:
				return "WardPower";
			case RE::ActorValue::kRightItemCharge:
				return "RightItemCharge";
			case RE::ActorValue::kArmorPerks:
				return "ArmorPerks";
			case RE::ActorValue::kShieldPerks:
				return "ShieldPerks";
			case RE::ActorValue::kWardDeflection:
				return "WardDeflection";
			case RE::ActorValue::kVariable01:
				return "Variable01";
			case RE::ActorValue::kVariable02:
				return "Variable02";
			case RE::ActorValue::kVariable03:
				return "Variable03";
			case RE::ActorValue::kVariable04:
				return "Variable04";
			case RE::ActorValue::kVariable05:
				return "Variable05";
			case RE::ActorValue::kVariable06:
				return "Variable06";
			case RE::ActorValue::kVariable07:
				return "Variable07";
			case RE::ActorValue::kVariable08:
				return "Variable08";
			case RE::ActorValue::kVariable09:
				return "Variable09";
			case RE::ActorValue::kVariable10:
				return "Variable10";
			case RE::ActorValue::kBowSpeedBonus:
				return "BowSpeedBonus";
			case RE::ActorValue::kFavorActive:
				return "FavorActive";
			case RE::ActorValue::kFavorsPerDay:
				return "FavorsPerDay";
			case RE::ActorValue::kFavorsPerDayTimer:
				return "FavorsPerDayTimer";
			case RE::ActorValue::kLeftItemCharge:
				return "LeftItemCharge";
			case RE::ActorValue::kAbsorbChance:
				return "AbsorbChance";
			case RE::ActorValue::kBlindness:
				return "Blindness";
			case RE::ActorValue::kWeaponSpeedMult:
				return "WeaponSpeedMult";
			case RE::ActorValue::kShoutRecoveryMult:
				return "ShoutRecoveryMult";
			case RE::ActorValue::kBowStaggerBonus:
				return "BowStaggerBonus";
			case RE::ActorValue::kTelekinesis:
				return "Telekinesis";
			case RE::ActorValue::kFavorPointsBonus:
				return "FavorPointsBonus";
			case RE::ActorValue::kLastBribedIntimidated:
				return "LastBribedIntimidated";
			case RE::ActorValue::kLastFlattered:
				return "LastFlattered";
			case RE::ActorValue::kMovementNoiseMult:
				return "MovementNoiseMult";
			case RE::ActorValue::kBypassVendorStolenCheck:
				return "BypassVendorStolenCheck";
			case RE::ActorValue::kBypassVendorKeywordCheck:
				return "BypassVendorKeywordCheck";
			case RE::ActorValue::kWaitingForPlayer:
				return "WaitingForPlayer";
			case RE::ActorValue::kOneHandedModifier:
				return "OneHandedModifier";
			case RE::ActorValue::kTwoHandedModifier:
				return "TwoHandedModifier";
			case RE::ActorValue::kMarksmanModifier:
				return "MarksmanModifier";
			case RE::ActorValue::kBlockModifier:
				return "BlockModifier";
			case RE::ActorValue::kSmithingModifier:
				return "SmithingModifier";
			case RE::ActorValue::kHeavyArmorModifier:
				return "HeavyArmorModifier";
			case RE::ActorValue::kLightArmorModifier:
				return "LightArmorModifier";
			case RE::ActorValue::kPickpocketModifier:
				return "PickpocketModifier";
			case RE::ActorValue::kLockpickingModifier:
				return "LockpickingModifier";
			case RE::ActorValue::kSneakingModifier:
				return "SneakingModifier";
			case RE::ActorValue::kAlchemyModifier:
				return "AlchemyModifier";
			case RE::ActorValue::kSpeechcraftModifier:
				return "SpeechcraftModifier";
			case RE::ActorValue::kAlterationModifier:
				return "AlterationModifier";
			case RE::ActorValue::kConjurationModifier:
				return "ConjurationModifier";
			case RE::ActorValue::kDestructionModifier:
				return "DestructionModifier";
			case RE::ActorValue::kIllusionModifier:
				return "IllusionModifier";
			case RE::ActorValue::kRestorationModifier:
				return "RestorationModifier";
			case RE::ActorValue::kEnchantingModifier:
				return "EnchantingModifier";
			case RE::ActorValue::kOneHandedSkillAdvance:
				return "OneHandedSkillAdvance";
			case RE::ActorValue::kTwoHandedSkillAdvance:
				return "TwoHandedSkillAdvance";
			case RE::ActorValue::kMarksmanSkillAdvance:
				return "MarksmanSkillAdvance";
			case RE::ActorValue::kBlockSkillAdvance:
				return "BlockSkillAdvance";
			case RE::ActorValue::kSmithingSkillAdvance:
				return "SmithingSkillAdvance";
			case RE::ActorValue::kHeavyArmorSkillAdvance:
				return "HeavyArmorSkillAdvance";
			case RE::ActorValue::kLightArmorSkillAdvance:
				return "LightArmorSkillAdvance";
			case RE::ActorValue::kPickpocketSkillAdvance:
				return "PickpocketSkillAdvance";
			case RE::ActorValue::kLockpickingSkillAdvance:
				return "LockpickingSkillAdvance";
			case RE::ActorValue::kSneakingSkillAdvance:
				return "SneakingSkillAdvance";
			case RE::ActorValue::kAlchemySkillAdvance:
				return "AlchemySkillAdvance";
			case RE::ActorValue::kSpeechcraftSkillAdvance:
				return "SpeechcraftSkillAdvance";
			case RE::ActorValue::kAlterationSkillAdvance:
				return "AlterationSkillAdvance";
			case RE::ActorValue::kConjurationSkillAdvance:
				return "ConjurationSkillAdvance";
			case RE::ActorValue::kDestructionSkillAdvance:
				return "DestructionSkillAdvance";
			case RE::ActorValue::kIllusionSkillAdvance:
				return "IllusionSkillAdvance";
			case RE::ActorValue::kRestorationSkillAdvance:
				return "RestorationSkillAdvance";
			case RE::ActorValue::kEnchantingSkillAdvance:
				return "EnchantingSkillAdvance";
			case RE::ActorValue::kLeftWeaponSpeedMultiply:
				return "LeftWeaponSpeedMultiply";
			case RE::ActorValue::kDragonSouls:
				return "DragonSouls";
			case RE::ActorValue::kCombatHealthRegenMultiply:
				return "CombatHealthRegenMultiply";
			case RE::ActorValue::kOneHandedPowerModifier:
				return "OneHandedPowerModifier";
			case RE::ActorValue::kTwoHandedPowerModifier:
				return "TwoHandedPowerModifier";
			case RE::ActorValue::kMarksmanPowerModifier:
				return "MarksmanPowerModifier";
			case RE::ActorValue::kBlockPowerModifier:
				return "BlockPowerModifier";
			case RE::ActorValue::kSmithingPowerModifier:
				return "SmithingPowerModifier";
			case RE::ActorValue::kHeavyArmorPowerModifier:
				return "HeavyArmorPowerModifier";
			case RE::ActorValue::kLightArmorPowerModifier:
				return "LightArmorPowerModifier";
			case RE::ActorValue::kPickpocketPowerModifier:
				return "PickpocketPowerModifier";
			case RE::ActorValue::kLockpickingPowerModifier:
				return "LockpickingPowerModifier";
			case RE::ActorValue::kSneakingPowerModifier:
				return "SneakingPowerModifier";
			case RE::ActorValue::kAlchemyPowerModifier:
				return "AlchemyPowerModifier";
			case RE::ActorValue::kSpeechcraftPowerModifier:
				return "SpeechcraftPowerModifier";
			case RE::ActorValue::kAlterationPowerModifier:
				return "AlterationPowerModifier";
			case RE::ActorValue::kConjurationPowerModifier:
				return "ConjurationPowerModifier";
			case RE::ActorValue::kDestructionPowerModifier:
				return "DestructionPowerModifier";
			case RE::ActorValue::kIllusionPowerModifier:
				return "IllusionPowerModifier";
			case RE::ActorValue::kRestorationPowerModifier:
				return "RestorationPowerModifier";
			case RE::ActorValue::kEnchantingPowerModifier:
				return "EnchantingPowerModifier";
			case RE::ActorValue::kDragonRend:
				return "DragonRend";
			case RE::ActorValue::kAttackDamageMult:
				return "AttackDamageMult";
			case RE::ActorValue::kHealRateMult:
				return "HealRateMult";
			case RE::ActorValue::kMagickaRateMult:
				return "MagickaRateMult";
			case RE::ActorValue::kStaminaRateMult:
				return "StaminaRateMult";
			case RE::ActorValue::kWerewolfPerks:
				return "WerewolfPerks";
			case RE::ActorValue::kVampirePerks:
				return "VampirePerks";
			case RE::ActorValue::kGrabActorOffset:
				return "GrabActorOffset";
			case RE::ActorValue::kGrabbed:
				return "Grabbed";
			case RE::ActorValue::kUnknown162:
				return "DEPRECATED05";
			case RE::ActorValue::kReflectDamage:
				return "ReflectDamage";
			default:
				return "None";
		}
	}
}