LittlerootTown_BrendansHouse_1F_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, LittlerootTown_BrendansHouse_1F_OnLoad
	map_script MAP_SCRIPT_ON_TRANSITION, LittlerootTown_BrendansHouse_1F_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, LittlerootTown_BrendansHouse_1F_OnFrame
	.byte 0

LittlerootTown_BrendansHouse_1F_OnLoad:
	call_if_lt VAR_LITTLEROOT_INTRO_STATE, 6, LittlerootTown_BrendansHouse_1F_EventScript_SetMovingBoxes
	call_if_set FLAG_RECEIVED_RUNNING_SHOES, LittlerootTown_BrendansHouse_1F_EventScript_CheckShowShoesManual
	end

LittlerootTown_BrendansHouse_1F_EventScript_SetMovingBoxes::
	setmetatile 5, 4, METATILE_BrendansMaysHouse_MovingBox_Open, TRUE
	setmetatile 5, 2, METATILE_BrendansMaysHouse_MovingBox_Closed, TRUE
	return

LittlerootTown_BrendansHouse_1F_EventScript_CheckShowShoesManual::
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, LittlerootTown_BrendansHouse_1F_EventScript_ShowRunningShoesManual
	return

LittlerootTown_BrendansHouse_1F_EventScript_ShowRunningShoesManual::
	setmetatile 3, 7, METATILE_BrendansMaysHouse_BookOnTable, TRUE
	return

LittlerootTown_BrendansHouse_1F_OnTransition:
	call_if_eq VAR_LITTLEROOT_INTRO_STATE, 3, LittlerootTown_BrendansHouse_1F_EventScript_MoveMomToDoor
	call_if_eq VAR_LITTLEROOT_INTRO_STATE, 5, LittlerootTown_BrendansHouse_1F_EventScript_MoveMomToStairs
	call_if_eq VAR_LITTLEROOT_INTRO_STATE, 6, LittlerootTown_BrendansHouse_1F_EventScript_MoveMomToTV
	end

LittlerootTown_BrendansHouse_1F_EventScript_MoveMomToStairs::
	setobjectxyperm LOCALID_PLAYERS_HOUSE_1F_MOM, 8, 4
	setobjectmovementtype LOCALID_PLAYERS_HOUSE_1F_MOM, MOVEMENT_TYPE_FACE_UP
	return

LittlerootTown_BrendansHouse_1F_EventScript_MoveMomToTV::
	setobjectxyperm LOCALID_PLAYERS_HOUSE_1F_MOM, 4, 5
	setobjectmovementtype LOCALID_PLAYERS_HOUSE_1F_MOM, MOVEMENT_TYPE_FACE_UP
	return

LittlerootTown_BrendansHouse_1F_EventScript_MoveMomToDoor::
	setobjectxyperm LOCALID_PLAYERS_HOUSE_1F_MOM, 9, 8
	setobjectmovementtype LOCALID_PLAYERS_HOUSE_1F_MOM, MOVEMENT_TYPE_FACE_UP
	return

@ Many of the below scripts have no gender check because they assume youre in the correct house
@ The below SS Ticket script uses Mays house state by accident(?), but theyre both set identically after the intro
LittlerootTown_BrendansHouse_1F_OnFrame:
	map_script_2 VAR_LITTLEROOT_INTRO_STATE, 3, LittlerootTown_BrendansHouse_1F_EventScript_EnterHouseMovingIn
	map_script_2 VAR_LITTLEROOT_INTRO_STATE, 5, LittlerootTown_BrendansHouse_1F_EventScript_GoUpstairsToSetClock
	map_script_2 VAR_LITTLEROOT_INTRO_STATE, 6, LittlerootTown_BrendansHouse_1F_EventScript_PetalburgGymReport
	map_script_2 VAR_LITTLEROOT_HOUSES_STATE_MAY, 1, LittlerootTown_BrendansHouse_1F_EventScript_YoureNewNeighbor
	map_script_2 VAR_LITTLEROOT_HOUSES_STATE_MAY, 3, PlayersHouse_1F_EventScript_GetSSTicketAndSeeLatiTV
	.2byte 0

LittlerootTown_BrendansHouse_1F_EventScript_GoUpstairsToSetClock::
	lockall
	msgbox PlayersHouse_1F_Text_GoSetTheClock, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, LittlerootTown_BrendansHouse_1F_Movement_PushTowardStairs
	applymovement LOCALID_PLAYERS_HOUSE_1F_MOM, LittlerootTown_BrendansHouse_1F_Movement_PushTowardStairs
	waitmovement 0
	warp MAP_LITTLEROOT_TOWN_BRENDANS_HOUSE_2F, 7, 1
	waitstate
	releaseall
	end

LittlerootTown_BrendansHouse_1F_Movement_PushTowardStairs:
	walk_up
	step_end

LittlerootTown_BrendansHouse_1F_EventScript_EnterHouseMovingIn::
	lockall
	setvar VAR_0x8004, LOCALID_PLAYERS_HOUSE_1F_MOM
	setvar VAR_0x8005, MALE
	goto PlayersHouse_1F_EventScript_EnterHouseMovingIn
	end

LittlerootTown_BrendansHouse_1F_EventScript_PetalburgGymReport::
	lockall
	setvar VAR_0x8004, MALE
	setvar VAR_0x8005, LOCALID_PLAYERS_HOUSE_1F_MOM
	goto PlayersHouse_1F_EventScript_PetalburgGymReportMale
	end

LittlerootTown_BrendansHouse_1F_EventScript_YoureNewNeighbor::
	lockall
	playse SE_PIN
	applymovement LOCALID_RIVALS_HOUSE_1F_MOM, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_RIVALS_HOUSE_1F_MOM, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	applymovement LOCALID_RIVALS_HOUSE_1F_MOM, LittlerootTown_BrendansHouse_1F_Movement_RivalMomApproach
	waitmovement 0
	special GetRivalSonDaughterString
	msgbox RivalsHouse_1F_Text_OhYoureTheNewNeighbor, MSGBOX_DEFAULT
	setflag FLAG_MET_RIVAL_MOM
	setvar VAR_LITTLEROOT_HOUSES_STATE_MAY, 2
	releaseall
	end

LittlerootTown_BrendansHouse_1F_Movement_RivalMomApproach:
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

LittlerootTown_BrendansHouse_1F_EventScript_GoSeeRoom::
	lockall
	setvar VAR_0x8004, LOCALID_PLAYERS_HOUSE_1F_MOM
	setvar VAR_0x8005, MALE
	applymovement VAR_0x8004, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	goto PlayersHouse_1F_EventScript_MomGoSeeRoom
	end

LittlerootTown_BrendansHouse_1F_EventScript_MeetRival0::
	lockall
	setvar VAR_0x8008, 0
	goto LittlerootTown_BrendansHouse_1F_EventScript_MeetRival
	end

LittlerootTown_BrendansHouse_1F_EventScript_MeetRival1::
	lockall
	setvar VAR_0x8008, 1
	goto LittlerootTown_BrendansHouse_1F_EventScript_MeetRival
	end

LittlerootTown_BrendansHouse_1F_EventScript_MeetRival2::
	lockall
	setvar VAR_0x8008, 2
	goto LittlerootTown_BrendansHouse_1F_EventScript_MeetRival
	end

LittlerootTown_BrendansHouse_1F_EventScript_MeetRival::
	playse SE_EXIT
	delay 10
	addobject LOCALID_RIVALS_HOUSE_1F_RIVAL
	delay 30
	playse SE_PIN
	applymovement LOCALID_RIVALS_HOUSE_1F_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_RIVALS_HOUSE_1F_RIVAL, Common_Movement_Delay48
	waitmovement 0
	call_if_ne VAR_0x8008, 1, LittlerootTown_BrendansHouse_1F_EventScript_PlayerFaceBrendan
	playbgm MUS_ENCOUNTER_BRENDAN, TRUE
	call_if_eq VAR_0x8008, 0, LittlerootTown_BrendansHouse_1F_EventScript_BrendanApproachPlayer0
	call_if_eq VAR_0x8008, 1, LittlerootTown_BrendansHouse_1F_EventScript_BrendanApproachPlayer1
	call_if_eq VAR_0x8008, 2, LittlerootTown_BrendansHouse_1F_EventScript_BrendanApproachPlayer2
	msgbox RivalsHouse_1F_Text_BrendanWhoAreYou, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_0x8008, 0, LittlerootTown_BrendansHouse_1F_EventScript_BrendanGoUpstairs0
	call_if_eq VAR_0x8008, 1, LittlerootTown_BrendansHouse_1F_EventScript_BrendanGoUpstairs1
	call_if_eq VAR_0x8008, 2, LittlerootTown_BrendansHouse_1F_EventScript_BrendanGoUpstairs2
	playse SE_EXIT
	removeobject LOCALID_RIVALS_HOUSE_1F_RIVAL
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_BRENDAN
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_2F_POKE_BALL
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_RIVAL_BEDROOM
	delay 30
	setvar VAR_LITTLEROOT_RIVAL_STATE, 3
	setvar VAR_LITTLEROOT_TOWN_STATE, 1
	savebgm MUS_DUMMY
	fadedefaultbgm
	releaseall
	end

LittlerootTown_BrendansHouse_1F_EventScript_PlayerFaceBrendan::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	return

LittlerootTown_BrendansHouse_1F_EventScript_BrendanApproachPlayer0::
	applymovement LOCALID_RIVALS_HOUSE_1F_RIVAL, LittlerootTown_BrendansHouse_1F_Movement_BrendanApproachPlayer0
	waitmovement 0
	return

LittlerootTown_BrendansHouse_1F_EventScript_BrendanApproachPlayer1::
	applymovement LOCALID_RIVALS_HOUSE_1F_RIVAL, LittlerootTown_BrendansHouse_1F_Movement_BrendanApproachPlayer1
	waitmovement 0
	return

LittlerootTown_BrendansHouse_1F_EventScript_BrendanApproachPlayer2::
	applymovement LOCALID_RIVALS_HOUSE_1F_RIVAL, LittlerootTown_BrendansHouse_1F_Movement_BrendanApproachPlayer2
	waitmovement 0
	return

LittlerootTown_BrendansHouse_1F_Movement_BrendanApproachPlayer0:
	walk_in_place_faster_left
	walk_left
	walk_in_place_faster_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

LittlerootTown_BrendansHouse_1F_Movement_BrendanApproachPlayer1:
	walk_up
	walk_up
	walk_up
	step_end

LittlerootTown_BrendansHouse_1F_Movement_BrendanApproachPlayer2:
	walk_in_place_faster_right
	walk_right
	walk_in_place_faster_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

LittlerootTown_BrendansHouse_1F_EventScript_BrendanGoUpstairs0::
	applymovement LOCALID_PLAYER, LittlerootTown_BrendansHouse_1F_Movement_PlayerWatchBrendanExit0
	applymovement LOCALID_RIVALS_HOUSE_1F_RIVAL, LittlerootTown_BrendansHouse_1F_Movement_BrendanGoUpstairs0
	waitmovement 0
	return

LittlerootTown_BrendansHouse_1F_EventScript_BrendanGoUpstairs1::
	applymovement LOCALID_PLAYER, LittlerootTown_BrendansHouse_1F_Movement_PlayerWatchBrendanExit1
	applymovement LOCALID_RIVALS_HOUSE_1F_RIVAL, LittlerootTown_BrendansHouse_1F_Movement_BrendanGoUpstairs1
	waitmovement 0
	return

LittlerootTown_BrendansHouse_1F_EventScript_BrendanGoUpstairs2::
	applymovement LOCALID_PLAYER, LittlerootTown_BrendansHouse_1F_Movement_PlayerWatchBrendanExit2
	applymovement LOCALID_RIVALS_HOUSE_1F_RIVAL, LittlerootTown_BrendansHouse_1F_Movement_BrendanGoUpstairs2
	waitmovement 0
	return

LittlerootTown_BrendansHouse_1F_Movement_PlayerWatchBrendanExit0:
	delay_16
	delay_8
	walk_in_place_faster_right
	step_end

LittlerootTown_BrendansHouse_1F_Movement_PlayerWatchBrendanExit1:
	delay_16
	delay_8
	walk_in_place_faster_right
	delay_16
	delay_16
	walk_in_place_faster_up
	step_end

LittlerootTown_BrendansHouse_1F_Movement_PlayerWatchBrendanExit2:
	delay_16
	delay_8
	walk_in_place_faster_left
	step_end

LittlerootTown_BrendansHouse_1F_Movement_BrendanGoUpstairs0:
	walk_in_place_faster_right
	walk_right
	walk_in_place_faster_up
	walk_up
	walk_up
	step_end

LittlerootTown_BrendansHouse_1F_Movement_BrendanGoUpstairs1:
	walk_in_place_faster_right
	walk_right
	walk_in_place_faster_up
	walk_up
	walk_up
	walk_in_place_faster_left
	walk_left
	walk_in_place_faster_up
	walk_up
	step_end

LittlerootTown_BrendansHouse_1F_Movement_BrendanGoUpstairs2:
	walk_in_place_faster_left
	walk_left
	walk_in_place_faster_up
	walk_up
	walk_up
	step_end
PlayersHouse_1F_Text_IsntItNiceInHere:
    .string "MAMAN : Tu vois, {PLAYER} ?\n"
    .string "C'est agréable ici aussi, non ?$"

PlayersHouse_1F_Text_MoversPokemonGoSetClock:
    .string "Les POKéMON des déménageurs font tout le travail\n"
    .string "pour nous installer et ranger après.\l"
    .string "C'est tellement pratique !\p"
    .string "{PLAYER}, ta chambre est à l'étage.\n"
    .string "Va voir, ma chérie !\p"
    .string "PAPA t'a acheté une nouvelle horloge pour\n"
    .string "marquer notre déménagement ici.\l"
    .string "N'oublie pas de la régler !$"

PlayersHouse_1F_Text_ArentYouInterestedInRoom:
    .string "MAMAN : Alors, {PLAYER} ?\p"
    .string "Tu n'as pas envie de voir ta\n"
    .string "propre chambre ?$"

PlayersHouse_1F_Text_GoSetTheClock:
    .string "MAMAN : {PLAYER}.\p"
    .string "Va régler l'horloge dans ta chambre, ma chérie.$"

PlayersHouse_1F_Text_OhComeQuickly:
    .string "MAMAN : Oh ! {PLAYER}, {PLAYER} !\n"
    .string "Vite ! Dépêche-toi !$"

PlayersHouse_1F_Text_MaybeDadWillBeOn:
    .string "MAMAN : Regarde ! C'est le DOJO DE PETALBURG !\n"
    .string "Peut-être que PAPA est là !$"

PlayersHouse_1F_Text_ItsOverWeMissedHim:
    .string "MAMAN : Oh… c'est fini.\p"
    .string "Je crois que PAPA était là, mais nous l'avons manqué.\n"
    .string "Quel dommage !$"

PlayersHouse_1F_Text_GoIntroduceYourselfNextDoor:
    .string "Ah oui.\n"
    .string "Un ami de PAPA habite en ville.\p"
    .string "Il s'appelle PROF. SEKO.\p"
    .string "Il habite juste à côté, tu devrais\n"
    .string "aller te présenter.$"

PlayersHouse_1F_Text_SeeYouHoney:
    .string "MAMAN : À bientôt, ma chérie !$"

PlayersHouse_1F_Text_DidYouMeetProfBirch:
    .string "MAMAN : Tu t'es présenté à\n"
    .string "PROF. SEKO ?$"

PlayersHouse_1F_Text_YouShouldRestABit:
    .string "MAMAN : Comment ça va, {PLAYER} ?\n"
    .string "Tu as l'air un peu fatigué.\p"
    .string "Je pense que tu devrais te reposer un peu.$"

PlayersHouse_1F_Text_TakeCareHoney:
    .string "MAMAN : Prends soin de toi, ma chérie !$"

PlayersHouse_1F_Text_GotDadsBadgeHeresSomethingFromMom:
    .string "MAMAN : Oh ? PAPA t'a donné ce BADGE ?\p"
    .string "Alors voici quelque chose de ta MAMAN !$"

PlayersHouse_1F_Text_DontPushYourselfTooHard:
    .string "Ne te fatigue pas trop, ma chérie.\n"
    .string "Tu peux toujours rentrer à la maison.\p"
    .string "Vas-y, ma chérie !$"

PlayersHouse_1F_Text_IsThatAPokenav:
    .string "MAMAN : Qu'est-ce que c'est, ma chérie ? Un POKéNAV ?\n"
    .string "Quelqu'un de DEVON te l'a donné ?\p"
    .string "Alors, ma chérie, que dirais-tu de\n"
    .string "m'enregistrer dans le PokéNav ?\p"
    .string "… … …$"

PlayersHouse_1F_Text_RegisteredMom:
    .string "MAMAN enregistrée\n"
    .string "dans le POKéNAV.$"

PlayersHouse_1F_Text_Vigoroth1:
    .string "Fugiiiiih !$"

PlayersHouse_1F_Text_Vigoroth2:
    .string "Huggoh, uggo uggo…$"

PlayersHouse_1F_Text_ReportFromPetalburgGym:
    .string "INTERVIEWER : …Nous vous apportons ce\n"
    .string "reportage depuis le DOJO DE PETALBURG.$"

PlayersHouse_1F_Text_TheresAMovieOnTV:
    .string "Il y a un film à la télévision.\p"
    .string "Deux hommes dansent sur un grand piano.\p"
    .string "Il vaut mieux y aller !$"

PlayersHouse_1F_Text_RunningShoesManual:
    .string "C'est le manuel des CHAUSSURES DE COURSE.\p"
    .string "« Appuie sur le bouton B pour courir\n"
    .string "en portant tes CHAUSSURES DE COURSE.\p"
    .string "« Lace tes CHAUSSURES DE COURSE et pars\n"
    .string "sur la route en courant ! »$"

PlayersHouse_1F_Text_TicketFromBrineyCameForYou:
    .string "PAPA : Hmm ?\p"
    .string "Tiens, c'est {PLAYER} !\p"
    .string "Ça fait un moment que je ne t'ai pas vu,\n"
    .string "mais tu as l'air… plus fort, d'une certaine façon.\p"
    .string "C'est l'impression que j'ai.\n"
    .string "Mais ton vieux n'a pas encore dit son dernier mot !\p"
    .string "Ah oui, j'ai quelque chose pour toi.\n"
    .string "Ceci t'a été envoyé par quelqu'un nommé\l"
    .string "MR. BRINEY.$"

PlayersHouse_1F_Text_PortsInSlateportLilycove:
    .string "PAPA : Hmm, un BILLET pour un ferry ?\p"
    .string "Si je me souviens bien, il y a des ports de ferry à\n"
    .string "PORT-SABLE et LILYCOVE.$"

PlayersHouse_1F_Text_BetterGetBackToGym:
    .string "Je ferais mieux de retourner au DOJO DE PETALBURG.\p"
    .string "MAMAN, merci d'avoir veillé sur la maison\n"
    .string "pendant mon absence.$"

PlayersHouse_1F_Text_DadShouldStayLonger:
    .string "MAMAN : Ton PAPA…\p"
    .string "Il rentre à la maison pour la première fois depuis un moment,\n"
    .string "et tout ce dont il parle, ce sont les POKéMON.\p"
    .string "Il devrait se détendre et rester un peu plus longtemps.$"

PlayersHouse_1F_Text_IsThatABreakingStory:
    .string "MAMAN : C'est un flash info ?$"

PlayersHouse_1F_Text_LatiEmergencyNewsFlash:
    .string "Nous vous apportons ce flash info d'urgence !\p"
    .string "Dans plusieurs lieux de HOENN, il y a eu\n"
    .string "des signalements d'un POKéMON de couleur BZZT…\l"
    .string "en plein vol.\p"
    .string "L'identité de ce POKéMON est\n"
    .string "actuellement inconnue.\p"
    .string "Nous revenons maintenant à la diffusion normale\n"
    .string "du film.$"

PlayersHouse_1F_Text_WhatColorDidTheySay:
    .string "MAMAN : {PLAYER}, as-tu entendu ?\p"
    .string "Quelle couleur a dit l'annonceur que ce POKéMON avait ?$"

PlayersHouse_1F_Text_StillUnknownPokemon:
    .string "MAMAN : Eh bien, c'est incroyable !\n"
    .string "Il existe encore des POKéMON inconnus.$"
