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

{ String }

; Returns whether `asText` contains `asSubText` case-sensitively
Bool Function ContainsStr(String asText, String asSubText) Global Native

; Returns whether `asText` contains `asSubText` case-insensitively
Bool Function ContainsText(String asText, String asSubText) Global Native

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

{ Time }

; Returns hours passed since current day began
Float Function GetCurrentHourOfDay() Global Native
