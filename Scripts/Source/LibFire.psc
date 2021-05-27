ScriptName LibFire Hidden

{ Actor }

; Returns whether `akActor` has any keyword in `akKeywords`
Bool Function ActorHasAnyKeyword(Actor akActor, FormList akKeywords) Global Native

; Returns whether `akActor` is commanded by `akOtherActor`
Bool Function ActorIsCommandedBy(Actor akActor, Actor akOtherActor) Global Native

; Returns whether `akActor` is commanded by the player
Bool Function ActorIsCommandedByPlayer(Actor akActor) Global Native

; Returns whether `akActor` is a teammate or player-controlled commanded/summoned actor
Bool Function ActorIsFollower(Actor akActor) Global Native

; Returns whether `akActor` is a member of any faction in `akFactions` with a rank greater than -1
Bool Function ActorIsInAnyFaction(Actor akActor, FormList akFactions) Global Native

; Returns whether `akActor` is a member of `akFaction` with a rank greater than -1
Bool Function ActorIsInFaction(Actor akActor, Faction akFaction) Global Native

; Returns whether `akActor` is a summoned actor
Bool Function ActorIsSummoned(Actor akActor) Global Native

; Returns an array of commanded actors for `akActor` or `None`
Actor[] Function GetCommandedActors(Actor akActor) Global Native

; Returns the commanding actor for `akActor` when actor is commanded
Actor Function GetCommandingActor(Actor akActor) Global Native

; Returns the ammo currently used by `akActor`
Ammo Function GetEquippedAmmo(Actor akActor) Global Native

; Returns armor items equipped in each slot in `argArmorSlots` (can be empty), and each weapon equipped in either hand
; when `abLeftWeapon` or `abRightWeapon` are True (Note: Return values are in array order and can be None)
Form[] Function GetWornEquipmentInSlots(Actor akActor, Int[] argArmorSlots, Bool abWeaponL, Bool abWeaponR) Global Native

{ Faction }

; Sets `akFaction` as ally or friend to each faction in `akFactions`
Function SetAllies(Faction akFaction, FormList akFactions, Bool abSelfIsFriendToOther = False, Bool abOtherIsFriendToSelf = False) Global Native

; Sets `akFaction` as enemy or neutral to each faction in `akFactions`
Function SetEnemies(Faction akFaction, FormList akFactions, Bool abSelfIsNeutralToOther = False, Bool abOtherIsNeutralToSelf = False) Global Native

{ FormList }

; Returns whether `akHaystack` contains each form in `argNeedles`
Bool[] Function SearchListForForms(FormList akHaystack, Form[] argNeedles) Global Native

; Returns whether each formlist in `akHaystack` contains `akNeedle`
Bool[] Function SearchListsForForm(FormList akHaystack, Form akNeedle) Global Native

{ ObjectReference }

; Returns actors in loaded cells within `afRadius` of `akOrigin`
Actor[] Function FindNearbyActors(ObjectReference akOrigin, Float afRadius) Global Native

; Returns books in loaded cells within `afRadius` of `akOrigin`
ObjectReference[] Function FindNearbyBooks(ObjectReference akOrigin, Float afRadius) Global Native

; Returns commanded actors in loaded cells within `afRadius` of `akOrigin` who are controlled by `akOrigin`
Actor[] Function FindNearbyCommandedActors(ObjectReference akOrigin, Float afRadius) Global Native

; Returns teammates and player-controlled commanded/summoned actors in loaded cells within `afRadius` of player
Actor[] Function FindNearbyFollowers(Float afRadius) Global Native

; Returns summoned actors in loaded cells within `afRadius` of `akOrigin`
Actor[] Function FindNearbySummons(ObjectReference akOrigin, Float afRadius) Global Native

; Returns teammates in loaded cells within `afRadius` of player
Actor[] Function FindNearbyTeammates(Float afRadius) Global Native

; Returns the permanent value of `asActorValue` for `akActor`
Float Function GetPermanentActorValue(ObjectReference akActor, String asActorValue) Global Native

{ Race }

; Returns the skill boost value of `asActorValue` for `akRace`
Int Function GetRaceSkillBonus(Race akRace, String asActorValue) Global Native

; Returns names of boosted actor values for `akRace`
String[] Function GetRaceSkills(Race akRace) Global Native

; Returns the base male height for `akRace`
Float Function GetRaceMaleHeight(Race akRace) Global Native

; Returns the base female height for `akRace`
Float Function GetRaceFemaleHeight(Race akRace) Global Native

; Returns the base male weight for `akRace`
Float Function GetRaceMaleWeight(Race akRace) Global Native

; Returns the base female weight for `akRace`
Float Function GetRaceFemaleWeight(Race akRace) Global Native

; Returns the starting health for `akRace`
Float Function GetRaceStartingHealth(Race akRace) Global Native

; Returns the starting magicka for `akRace`
Float Function GetRaceStartingMagicka(Race akRace) Global Native

; Returns the starting stamina for `akRace`
Float Function GetRaceStartingStamina(Race akRace) Global Native

; Returns the base carry weight for `akRace`
Float Function GetRaceCarryWeight(Race akRace) Global Native

; Returns the base mass for `akRace`
Float Function GetRaceMass(Race akRace) Global Native

; Returns the base health regen for `akRace`
Float Function GetRaceHealthRegen(Race akRace) Global Native

; Returns the base magicka regen for `akRace`
Float Function GetRaceMagickaRegen(Race akRace) Global Native

; Returns the base stamina regen for `akRace`
Float Function GetRaceStaminaRegen(Race akRace) Global Native

; Returns the base unarmed damage for `akRace`
Float Function GetRaceUnarmedDamage(Race akRace) Global Native

; Returns the base unarmed reach for `akRace`
Float Function GetRaceUnarmedReach(Race akRace) Global Native

{ String }

; Returns whether `asText` contains `asSubText` case-sensitively
Bool Function ContainsStr(String asText, String asSubText) Global Native

; Returns whether `asText` contains `asSubText` case-insensitively
Bool Function ContainsText(String asText, String asSubText) Global Native

; Replaces `{}` tokens in `asFormat` with `argValues` (supports up to 9 values)
;   Note: Arrays exceeding the maximum number of values will be truncated.
;   Syntax: https://fmt.dev/latest/syntax.html
String Function FormatFloat(String asFormat, Float[] argValues) Global Native

; Replaces `{}` tokens in `asFormat` with `argValues` (supports up to 9 values)
;   Note: Arrays exceeding the maximum number of values will be truncated.
;   Syntax: https://fmt.dev/latest/syntax.html
String Function FormatInt(String asFormat, Int[] argValues) Global Native

; Replaces `{}` tokens in `asFormat` with `argValues` (supports up to 9 values)
;   Note: Arrays exceeding the maximum number of values will be truncated.
;   Syntax: https://fmt.dev/latest/syntax.html
String Function FormatString(String asFormat, String[] argValues) Global Native

; Returns the hexadecimal string representation of `aiSource`
String Function IntToHex(Int aiSource) Global Native

; Returns `asSource` as array of String split by `asDelimiter`
String[] Function SplitString(String asSource, String asDelimiter) Global Native

; Returns `asSource` as array of Float split by `asDelimiter`
Float[] Function StrToFloatArray(String asSource, String asDelimiter) Global Native

; Returns `asSource` as array of Int split by `asDelimiter`
Int[] Function StrToIntArray(String asSource, String asDelimiter) Global Native

; Returns `asSource` wrapped to column `aiMaxLength` with lines delimited by newline character
String Function WrapString(String asSource, Int aiMaxLength) Global Native

{ Spell }

; Returns highest minimum skill level for `akSpell` (does not account for conditions)
Int Function GetHighestMinSkillLevelForSpell(Spell akSpell) Global Native

{ Time }

; Returns hours passed since current day began
Float Function GetCurrentHourOfDay() Global Native
