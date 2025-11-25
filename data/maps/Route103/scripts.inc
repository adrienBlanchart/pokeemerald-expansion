Route103_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route103_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, Route103_OnLoad
	.byte 0

Route103_OnTransition:
	call Common_EventScript_SetupRivalGfxId
	call ProfBirch_EventScript_UpdateLocation
	end

Route103_OnLoad:
	call_if_set FLAG_SYS_GAME_CLEAR, Route103_EventScript_OpenAlteringCave
	end

Route103_EventScript_OpenAlteringCave::
	setmetatile 45, 5, METATILE_General_CaveEntrance_Top, TRUE
	setmetatile 45, 6, METATILE_General_CaveEntrance_Bottom, FALSE
	return

Route103_EventScript_Rival::
	lockall
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, Route103_EventScript_RivalMay
	goto_if_eq VAR_RESULT, FEMALE, Route103_EventScript_RivalBrendan
	end

Route103_EventScript_RivalMay::
	bufferleadmonspeciesname STR_VAR_1
	msgbox Route103_Text_MayRoute103Pokemon, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ROUTE103_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	msgbox Route103_Text_MayRoute103Pokemon2, MSGBOX_DEFAULT
	closemessage
	playbgm MUS_ENCOUNTER_MAY, TRUE
	applymovement LOCALID_ROUTE103_RIVAL, Common_Movement_FacePlayer
	waitmovement 0
	applymovement LOCALID_ROUTE103_RIVAL, Common_Movement_Delay48
	waitmovement 0
	switch VAR_STARTER_MON
	case 0, Route103_EventScript_StartMayBattleTreecko
	case 1, Route103_EventScript_StartMayBattleTorchic
	case 2, Route103_EventScript_StartMayBattleMudkip
	end

Route103_EventScript_RivalBrendan::
	bufferleadmonspeciesname STR_VAR_1
	msgbox Route103_Text_BrendanRoute103Pokemon, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ROUTE103_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	msgbox Route103_Text_BrendanRoute103Pokemon2, MSGBOX_DEFAULT
	closemessage
	playbgm MUS_ENCOUNTER_BRENDAN, TRUE
	applymovement LOCALID_ROUTE103_RIVAL, Common_Movement_FacePlayer
	waitmovement 0
	applymovement LOCALID_ROUTE103_RIVAL, Common_Movement_Delay48
	waitmovement 0
	switch VAR_STARTER_MON
	case 0, Route103_EventScript_StartBrendanBattleTreecko
	case 1, Route103_EventScript_StartBrendanBattleTorchic
	case 2, Route103_EventScript_StartBrendanBattleMudkip
	end

Route103_EventScript_StartMayBattleTreecko::
	trainerbattle_no_intro TRAINER_MAY_ROUTE_103_TREECKO, Route103_Text_MayDefeated
	goto Route103_EventScript_RivalExit
	end

Route103_EventScript_StartMayBattleTorchic::
	trainerbattle_no_intro TRAINER_MAY_ROUTE_103_TORCHIC, Route103_Text_MayDefeated
	goto Route103_EventScript_RivalExit
	end

Route103_EventScript_StartMayBattleMudkip::
	trainerbattle_no_intro TRAINER_MAY_ROUTE_103_MUDKIP, Route103_Text_MayDefeated
	goto Route103_EventScript_RivalExit
	end

Route103_EventScript_StartBrendanBattleTreecko::
	trainerbattle_no_intro TRAINER_BRENDAN_ROUTE_103_TREECKO, Route103_Text_BrendanDefeated
	goto Route103_EventScript_RivalExit
	end

Route103_EventScript_StartBrendanBattleTorchic::
	trainerbattle_no_intro TRAINER_BRENDAN_ROUTE_103_TORCHIC, Route103_Text_BrendanDefeated
	goto Route103_EventScript_RivalExit
	end

Route103_EventScript_StartBrendanBattleMudkip::
	trainerbattle_no_intro TRAINER_BRENDAN_ROUTE_103_MUDKIP, Route103_Text_BrendanDefeated
	goto Route103_EventScript_RivalExit
	end

Route103_EventScript_RivalExit::
	closemessage
	switch VAR_FACING
	case DIR_SOUTH, Route103_EventScript_RivalExitFacingSouth
	case DIR_NORTH, Route103_EventScript_RivalExitFacingNorth
	case DIR_WEST, Route103_EventScript_RivalExitFacingEastOrWest
	case DIR_EAST, Route103_EventScript_RivalExitFacingEastOrWest
	end

Route103_EventScript_RivalExitFacingNorth::
	applymovement LOCALID_PLAYER, Route103_Movement_WatchRivalExitFacingNorth
	applymovement LOCALID_ROUTE103_RIVAL, Route103_Movement_RivalExitFacingNorth1
	waitmovement 0
	playse SE_LEDGE
	applymovement LOCALID_ROUTE103_RIVAL, Route103_Movement_RivalExitFacingNorth2
	waitmovement 0
	goto Route103_EventScript_RivalEnd
	end

Route103_EventScript_RivalExitFacingEastOrWest::
	applymovement LOCALID_PLAYER, Route103_Movement_WatchRivalExitFacingEastOrWest
	applymovement LOCALID_ROUTE103_RIVAL, Route103_Movement_RivalExit1
	waitmovement 0
	playse SE_LEDGE
	applymovement LOCALID_ROUTE103_RIVAL, Route103_Movement_RivalExit2
	waitmovement 0
	goto Route103_EventScript_RivalEnd
	end

Route103_EventScript_RivalExitFacingSouth::
	applymovement LOCALID_ROUTE103_RIVAL, Route103_Movement_RivalExit1
	waitmovement 0
	playse SE_LEDGE
	applymovement LOCALID_ROUTE103_RIVAL, Route103_Movement_RivalExit2
	waitmovement 0
	goto Route103_EventScript_RivalEnd
	end

Route103_EventScript_RivalEnd::
	removeobject LOCALID_ROUTE103_RIVAL
	setvar VAR_BIRCH_LAB_STATE, 4
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_RIVAL
	setflag FLAG_DEFEATED_RIVAL_ROUTE103
	setvar VAR_OLDALE_RIVAL_STATE, 1
	clearflag FLAG_HIDE_OLDALE_TOWN_RIVAL
	savebgm MUS_DUMMY
	fadedefaultbgm
	releaseall
	end

Route103_EventScript_FoundCriminal::
	lock
	applymovement LOCALID_PLAYER, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_PLAYER, Route103_Movement_HideInBush
	waitmovement 0

	msgbox Route103_Text_CriminalTxt1, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ROUTE103_CRIMINAL_SALAMENCE, Common_Movement_Angry
	waitmovement 0
	msgbox Route103_Text_CriminalTxt2, MSGBOX_DEFAULT
	closemessage
	checkplayergender
	call_if_eq VAR_RESULT, MALE, Route103_EventScript_RivalMay_TEXT_1
	call_if_eq VAR_RESULT, FEMALE, Route103_EventScript_RivalBrendan_TEXT_1
	closemessage
	applymovement LOCALID_ROUTE103_RIVAL_TREECKO, Movement_SmashRock
	waitmovement 0
	
	msgbox Route103_Text_CriminalTxt3, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ROUTE103_CRIMINAL_SALAMENCE, Common_Movement_Angry
	waitmovement 0
	applymovement LOCALID_ROUTE103_CRIMINAL, Common_Movement_Angry
	waitmovement 0
	msgbox Route103_Text_CriminalTxt4, MSGBOX_DEFAULT
	closemessage
	checkplayergender
	call_if_eq VAR_RESULT, MALE, Route103_EventScript_RivalMay_TEXT_2
	call_if_eq VAR_RESULT, FEMALE, Route103_EventScript_RivalBrendan_TEXT_2
	closemessage
	applymovement LOCALID_ROUTE103_RIVAL_TREECKO, Movement_SmashRock
	waitmovement 0
	
	msgbox Route103_Text_CriminalTxt5, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ROUTE103_CRIMINAL_SALAMENCE, Common_Movement_Angry
	waitmovement 0
	applymovement LOCALID_ROUTE103_CRIMINAL_SALAMENCE, Movement_CutTreeDown
	waitmovement 0
	removeobject LOCALID_ROUTE103_RIVAL_TREECKO
	checkplayergender
	call_if_eq VAR_RESULT, MALE, Route103_EventScript_RivalMay_TEXT_3
	call_if_eq VAR_RESULT, FEMALE, Route103_EventScript_RivalBrendan_TEXT_3
	closemessage
	removeobject LOCALID_ROUTE103_CRIMINAL_SALAMENCE
	applymovement LOCALID_ROUTE103_CRIMINAL, Route103_Movement_CriminalExitSouth
	waitmovement 0
	setvar VAR_CUSTOM_LITTLEROOT_PROGRESSION, 4
	setflag FLAG_CRIMINAL_DEFEATED_RIVAL_ROUTE103 
	release
	end

Route103_EventScript_RivalMay_TEXT_1::
	msgbox Route103_Text_MayRoute103_Text_1, MSGBOX_DEFAULT
	end
Route103_EventScript_RivalBrendan_TEXT_1::
	msgbox Route103_Text_BrendanRoute103_Text_1, MSGBOX_DEFAULT
	end

Route103_EventScript_RivalMay_TEXT_2::
	msgbox Route103_Text_MayRoute103_Text_2, MSGBOX_DEFAULT
	end
Route103_EventScript_RivalBrendan_TEXT_2::
	msgbox Route103_Text_BrendanRoute103_Text_2, MSGBOX_DEFAULT
	end

Route103_EventScript_RivalMay_TEXT_3::
	msgbox Route103_Text_MayRoute103_Text_3, MSGBOX_DEFAULT
	end
Route103_EventScript_RivalBrendan_TEXT_3::
	msgbox Route103_Text_BrendanRoute103_Text_3, MSGBOX_DEFAULT
	end


Route103_Movement_RivalExitFacingNorth1:
	walk_left
	walk_down
	step_end

Route103_Movement_CriminalExitSouth:
	walk_down
	jump_2_down
	delay_16
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	jump_2_down
	delay_16
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

Route103_Movement_RivalExitFacingNorth2:
	jump_2_down
	delay_16
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

Route103_Movement_WatchRivalExitFacingNorth:
	delay_16
	delay_4
	walk_in_place_faster_left
	delay_16
	walk_in_place_faster_down
	step_end

Route103_Movement_RivalExit1:
	walk_down
	step_end

Route103_Movement_RivalExit2:
	jump_2_down
	delay_16
	walk_down
	walk_down
	walk_down
	step_end

Route103_Movement_WatchRivalExitFacingEastOrWest:
	delay_16
	walk_in_place_faster_down
	step_end



Route103_Movement_HideInBush:
	lock
	walk_fast_up
	walk_fast_up
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	face_up
	release
	step_end


Route103_EventScript_Boy::
	msgbox Route103_Text_ShouldHaveBroughtPotion, MSGBOX_NPC
	end

Route103_EventScript_Man::
	msgbox Route103_Text_ShortcutToOldale, MSGBOX_NPC
	end

Route103_EventScript_RouteSign::
	msgbox Route103_Text_RouteSign, MSGBOX_SIGN
	end

Route103_EventScript_Daisy::
	trainerbattle_single TRAINER_DAISY, Route103_Text_DaisyIntro, Route103_Text_DaisyDefeated
	msgbox Route103_Text_DaisyPostBattle, MSGBOX_AUTOCLOSE
	end

Route103_EventScript_Amy::
	trainerbattle_double TRAINER_AMY_AND_LIV_1, Route103_Text_AmyIntro, Route103_Text_AmyDefeated, Route103_Text_AmyNotEnoughPokemon, Route102_EventScript_AmyRegisterMatchCallAfterBattle
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route102_EventScript_AmyRematch
	msgbox Route103_Text_AmyPostBattle, MSGBOX_AUTOCLOSE
	end

Route102_EventScript_AmyRegisterMatchCallAfterBattle::
	msgbox Route103_Text_AmyLivRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_AMY_AND_LIV_1
	release
	end

Route102_EventScript_AmyRematch::
	trainerbattle_rematch_double TRAINER_AMY_AND_LIV_1, Route103_Text_AmyRematchIntro, Route103_Text_AmyRematchDefeated, Route103_Text_AmyRematchNotEnoughPokemon
	msgbox Route103_Text_AmyRematchPostBattle, MSGBOX_AUTOCLOSE
	end

Route103_EventScript_Liv::
	trainerbattle_double TRAINER_AMY_AND_LIV_1, Route103_Text_LivIntro, Route103_Text_LivDefeated, Route103_Text_LivNotEnoughPokemon, Route102_EventScript_LivRegisterMatchCallAfterBattle
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route102_EventScript_LivRematch
	msgbox Route103_Text_LivPostBattle, MSGBOX_AUTOCLOSE
	end

Route102_EventScript_LivRegisterMatchCallAfterBattle::
	msgbox Route103_Text_AmyLivRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_AMY_AND_LIV_1
	release
	end

Route102_EventScript_LivRematch::
	trainerbattle_rematch_double TRAINER_AMY_AND_LIV_1, Route103_Text_LivRematchIntro, Route103_Text_LivRematchDefeated, Route103_Text_LivRematchNotEnoughPokemon
	msgbox Route103_Text_LivRematchPostBattle, MSGBOX_AUTOCLOSE
	end

Route103_EventScript_Andrew::
	trainerbattle_single TRAINER_ANDREW, Route103_Text_AndrewIntro, Route103_Text_AndrewDefeated
	msgbox Route103_Text_AndrewPostBattle, MSGBOX_AUTOCLOSE
	end

Route103_EventScript_Miguel::
	trainerbattle_single TRAINER_MIGUEL_1, Route103_Text_MiguelIntro, Route103_Text_MiguelDefeated, Route102_EventScript_MiguelRegisterMatchCallAfterBattle
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route103_EventScript_MiguelRematch
	msgbox Route103_Text_MiguelPostBattle, MSGBOX_DEFAULT
	release
	end

Route102_EventScript_MiguelRegisterMatchCallAfterBattle::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route103_Text_MiguelRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_MIGUEL_1
	release
	end

Route103_EventScript_MiguelRematch::
	trainerbattle_rematch TRAINER_MIGUEL_1, Route103_Text_MiguelRematchIntro, Route103_Text_MiguelRematchDefeated
	msgbox Route103_Text_MiguelRematchPostBattle, MSGBOX_AUTOCLOSE
	end

Route103_EventScript_Marcos::
	trainerbattle_single TRAINER_MARCOS, Route103_Text_MarcosIntro, Route103_Text_MarcosDefeated
	msgbox Route103_Text_MarcosPostBattle, MSGBOX_AUTOCLOSE
	end

Route103_EventScript_Rhett::
	trainerbattle_single TRAINER_RHETT, Route103_Text_RhettIntro, Route103_Text_RhettDefeated
	msgbox Route103_Text_RhettPostBattle, MSGBOX_AUTOCLOSE
	end

Route103_EventScript_Pete::
	trainerbattle_single TRAINER_PETE, Route103_Text_PeteIntro, Route103_Text_PeteDefeated
	msgbox Route103_Text_PetePostBattle, MSGBOX_AUTOCLOSE
	end

Route103_EventScript_Isabelle::
	trainerbattle_single TRAINER_ISABELLE, Route103_Text_IsabelleIntro, Route103_Text_IsabelleDefeated
	msgbox Route103_Text_IsabellePostBattle, MSGBOX_AUTOCLOSE
	end

Route103_Text_CriminalTxt1:
	.string "{PLAYER}{KUN}: Allez, attaque !$"

Route103_Text_CriminalTxt2:
	.string "{PLAYER}{KUN}: Obéis moi !$"

Route103_Text_CriminalTxt3:
	.string "{PLAYER}{KUN}: Allez, maintenant, déchiquettes-le !$"

Route103_Text_CriminalTxt4:
	.string "{PLAYER}{KUN}: Raaah !$"

Route103_Text_CriminalTxt5:
	.string "{PLAYER}{KUN}: Tu m'appartiens, tu dois m'obéir,"
	.string "utilises Draco griffe !$"

Route103_Text_MayRoute103_Text_1:
	.string "MAY: Arcko, utilise charge !$"
Route103_Text_BrendanRoute103_Text_1:
	.string "BRENDAN: Arcko, utilise charge !$"

Route103_Text_MayRoute103_Text_2:
	.string "MAY: Courage Arcko,\n"
	.string "Charge encore une fois !$"
Route103_Text_BrendanRoute103_Text_2:
	.string "BRENDAN: Courage Arcko,\n"
	.string "Charge encore une fois !$"

Route103_Text_MayRoute103_Text_3:
	.string "{PLAYER}{KUN}: Ahahah !\n"
	.string "Enfin !\n"
	.string "Quelle force !\n"
	.string "Avec un peu de dressage,"
	.string "plus rien ne pourra m'arrêter !\n"
	.string "MAY: Mais ...\n"
	.string "c'est impossible..."
	.string "je n'ai rien pu faire..."
	.string "tu as triché !\n"
	.string "{PLAYER}{KUN}: Dégage minus.\n"
	.string "Tu étais faible, j'ai gagné, c'est tout."
	.string "Je pars pour la League Pokémon,"
	.string "Tu ferais mieux de rendre ton pokémon\n"
	.string "et rentrer chez toi."
Route103_Text_BrendanRoute103_Text_3:
	.string "{PLAYER}{KUN}: Ahahah !\n"
	.string "Enfin !\n"
	.string "Quelle force !\n"
	.string "Avec un peu de dressage,"
	.string "plus rien ne pourra m'arrêter !\n"
	.string "BRENDAN: Mais ...\n"
	.string "c'est impossible..."
	.string "je n'ai rien pu faire..."
	.string "tu as triché !\n"
	.string "{PLAYER}{KUN}: Dégage minus.\n"
	.string "Tu étais faible, j'ai gagné, c'est tout."
	.string "Je pars pour la League Pokémon,"
	.string "Tu ferais mieux de rendre ton pokémon\n"
	.string "et rentrer chez toi."

Route103_Text_MayRoute103Pokemon:
	.string "MAY: C'est pas normal,\n"
	.string "ça devrait être interdit de commencer\n"
	.string "avec un pokémon si fort...\n"
	.string "...$"

Route103_Text_MayRoute103Pokemon2:
	.string "MAY: Mais...\n"
	.string "C'est un {STR_VAR_1} !!"
	.string "avec lui, la victoire est à moi !$"

Route103_Text_BrendanRoute103Pokemon:
	.string "BRENDAN: C'est pas normal,\n"
	.string "ça devrait être interdit de commencer\n"
	.string "avec un pokémon si fort...\n"
	.string "...$"

Route103_Text_BrendanRoute103Pokemon2:
	.string "BRENDAN: Mais...\n"
	.string "C'est un {STR_VAR_1} !!"
	.string "avec lui, la victoire est à moi !$"

Route103_Text_MayDefeated:
	.string "MAY: Mais c'est dingue !\n"
	.string "Même pas capable de capturer un pokémon ...$"


Route103_Text_BrendanLetsBattle:
	.string "Hey, it's {PLAYER}!\p"
	.string "…Oh, yeah, Dad gave you a POKéMON.\p"
	.string "Since we're here, how about a little\n"
	.string "battle?\p"
	.string "I'll teach you what being a TRAINER's\n"
	.string "about!$"

Route103_Text_BrendanDefeated:
	.string "BRENDAN: Mais c'est dingue !\n"
	.string "Même pas capable de capturer un pokémon ...$"

Route103_Text_ShouldHaveBroughtPotion:
    .string "Mes POKéMON sont épuisés…\n"
    .string "J'aurais dû prendre une POTION…$"


Route103_Text_ShortcutToOldale:
	.string "If you cross the sea from here,\n"
	.string "it'll be a shortcut to OLDALE TOWN.\p"
	.string "Fufufu, that's useful, isn't it?$"

Route103_Text_RouteSign:
	.string "ROUTE 103\n"
	.string "{DOWN_ARROW} OLDALE TOWN$"

