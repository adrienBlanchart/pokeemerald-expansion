Clearing_Pkmn_Nest_MapScripts::
	.byte 0

Clearing_Pkmn_Nest_SignParentWasHere::
	msgbox Clearing_Pkmn_Nest_Text_SignParentWasHere, MSGBOX_DEFAULT
	closemessage
	end

	
Clearing_Pkmn_Nest_EventScript_Shuckle_Approch::
	lock
	applymovement LOCALID_CARATROC_CLEARING_1, Clearing_Pkmn_Nest_Movement_Shuckle_Approch
	waitmovement 0
	msgbox Clearing_Pkmn_Nest_Text_Caratroc, MSGBOX_DEFAULT
	
	applymovement LOCALID_CARATROC_CLEARING_1, Clearing_Pkmn_Nest_Movement_Shuckle_backward
	waitmovement 0
	setflag FLAG_HIDE_CLEARING_NEST_SHUCKLE_1
	setvar VAR_CUSTOM_LITTLEROOT_PROGRESSION, 3
	release
	end

Clearing_Pkmn_Nest_Movement_Shuckle_Approch:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_left
	walk_down
	walk_left
	walk_left
	walk_up
	walk_left
	step_end

Clearing_Pkmn_Nest_Movement_Shuckle_backward:
	walk_right
	walk_down
	walk_right
	walk_right
	walk_up
	walk_right
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end


Clearing_Pkmn_Nest_Text_SignParentWasHere:
    .string "“Une odeur familière… Maman était ici.”'$"

Clearing_Pkmn_Nest_Text_Caratroc:
    .string "J'avais bien vu quelque chose filer dans cette clairière…$\n"
    .string "C'était ta mère, n'est-ce pas ?$\n"
    .string "Ils l'ont prise. Je reconnais cette odeur…$\n"
    .string "Un humain, sûr de lui et froid, qui prend ce qu'il veut.$\n"
    .string "Les humains ne s'arrêtent jamais. Ils capturent, utilisent… puis jettent.$\n"
    .string "Tu veux la retrouver ? Tu n'es qu'un enfant.$\n"
    .string "Et ils possèdent une arme pour nous enchaîner… la Poké Ball.$\n"
    .string "Suis la piste si tu veux$\n"
    .string "Mais tu ne seras plus jamais le même.$\n"
    .string "Un conseil,$\n"
    .string "Évite les humains autant que possible.$\n"
    .string "Ils sont tous pareils… avides de pouvoir et de renommée.$\n"
    .string "Adieu, et bonne chance.$"
