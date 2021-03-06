/*
                     R E A L M S    O F    D E S P A I R  !
   ___________________________________________________________________________
  //            /                                                            \\
 [|_____________\   ********   *        *   ********   *        *   *******   |]
 [|   \\._.//   /  **********  **      **  **********  **      **  *********  |]
 [|   (0...0)   \  **********  ***    ***  **********  ***    ***  *********  |]
 [|    ).:.(    /  ***         ****  ****  ***    ***  ***    ***  ***        |]
 [|    {o o}    \  *********   **********  **********  ***    ***  *** ****   |]
 [|   / ' ' \   /   *********  *** ** ***  **********  ***    ***  ***  ****  |]
 [|-'- /   \ -`-\         ***  ***    ***  ***    ***  ***    ***  ***   ***  |]
 [|   .VxvxV.   /   *********  ***    ***  ***    ***  **********  *********  |]
 [|_____________\  **********  **      **  **      **  **********  *********  |]
 [|             /  *********   *        *  *        *   ********    *******   |]
  \\____________\____________________________________________________________//
     |                                                                     |
     |    --{ [S]imulated [M]edieval [A]dventure Multi[U]ser [G]ame }--    |
     |_____________________________________________________________________|
     |                                                                     |
     |       -*- Commands for personal player settings/statictics -*-      |
     |_____________________________________________________________________|
    //                                                                     \\
   [|  SMAUG 2.0 © 2014-2015 Antonio Cao (@burzumishi)                      |]
   [|                                                                       |]
   [|  AFKMud Copyright 1997-2007 by Roger Libiez (Samson),                 |]
   [|  Levi Beckerson (Whir), Michael Ward (Tarl), Erik Wolfe (Dwip),       |]
   [|  Cameron Carroll (Cam), Cyberfox, Karangi, Rathian, Raine,            |]
   [|  Xorith, and Adjani.                                                  |]
   [|  All Rights Reserved. External contributions from Remcon, Quixadhal,  |]
   [|  Zarius and many others.                                              |]
   [|                                                                       |]
   [|  SMAUG 1.4 © 1994-1998 Thoric/Altrag/Blodkai/Narn/Haus/Scryn/Rennard  |]
   [|  Swordbearer/Gorog/Grishnakh/Nivek/Tricops/Fireblade/Edmond/Conran    |]
   [|                                                                       |]
   [|  Merc 2.1 Diku Mud improvments © 1992-1993 Michael Chastain, Michael  |]
   [|  Quan, and Mitchell Tse. Original Diku Mud © 1990-1991 by Sebastian   |]
   [|  Hammer, Michael Seifert, Hans Henrik St{rfeldt, Tom Madsen, Katja    |]
   [|  Nyboe. Win32 port Nick Gammon.                                       |]
    \\_____________________________________________________________________//
*/

#include <sys/types.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "mud.h"

/*
 *  Locals
 */
char *tiny_affect_loc_name (int location);

void
do_gold (CHAR_DATA * ch, char *argument)
{
  set_char_color (AT_GOLD, ch);
#ifdef ENABLE_GOLD_SILVER_COPPER
	ch_printf (ch, _("You have %s gold, "), num_punct(ch->gold));
	ch_printf (ch, _("%s silver"), num_punct(ch->silver));
	ch_printf (ch, _(", and %s copper coins.\n"), num_punct(ch->copper));
#else
  ch_printf (ch, _("You have %s gold pieces.\n"), num_punct (ch->gold));
#endif
  return;
}

    /*
     * Returns a string from the honour_rank matrix for display purpose
     * -- Raltaris
     */
char *
get_honour (CHAR_DATA * ch)
{
  int honour = ch->pcdata->honour;
  int class = ch->class > 11 ? 3 : ch->class;

  if (honour > 99)
    return honour_rank[class][6];
  else if (honour > 64)
    return honour_rank[class][5];
  else if (honour > 39)
    return honour_rank[class][4];
  else if (honour > 19)
    return honour_rank[class][3];
  else if (honour > 9)
    return honour_rank[class][2];
  else if (honour > 4)
    return honour_rank[class][1];

  return honour_rank[class][0];
}

void
do_worth (CHAR_DATA * ch, char *argument)
{
  char buf[MAX_STRING_LENGTH];
  char buf2[MAX_STRING_LENGTH];

  if (IS_NPC (ch))
    return;

  set_pager_color (AT_GREEN, ch);
  pager_printf_color (ch, "\n\r&GWorth for &w%s&G%s.\n\r", ch->name,
		      ch->pcdata->title);
  send_to_pager_color
    (" &g----------------------------------------------------------------------------\n\r",
     ch);
  if (!ch->pcdata->deity)
    sprintf (buf, "N/A");
  else if (ch->pcdata->favor > 2250)
    sprintf (buf, "loved");
  else if (ch->pcdata->favor > 2000)
    sprintf (buf, "cherished");
  else if (ch->pcdata->favor > 1750)
    sprintf (buf, "honored");
  else if (ch->pcdata->favor > 1500)
    sprintf (buf, "praised");
  else if (ch->pcdata->favor > 1250)
    sprintf (buf, "favored");
  else if (ch->pcdata->favor > 1000)
    sprintf (buf, "respected");
  else if (ch->pcdata->favor > 750)
    sprintf (buf, "liked");
  else if (ch->pcdata->favor > 250)
    sprintf (buf, "tolerated");
  else if (ch->pcdata->favor > -250)
    sprintf (buf, "ignored");
  else if (ch->pcdata->favor > -750)
    sprintf (buf, "shunned");
  else if (ch->pcdata->favor > -1000)
    sprintf (buf, "disliked");
  else if (ch->pcdata->favor > -1250)
    sprintf (buf, "dishonored");
  else if (ch->pcdata->favor > -1500)
    sprintf (buf, "disowned");
  else if (ch->pcdata->favor > -1750)
    sprintf (buf, "abandoned");
  else if (ch->pcdata->favor > -2000)
    sprintf (buf, "despised");
  else if (ch->pcdata->favor > -2250)
    sprintf (buf, "hated");
  else
    sprintf (buf, "damned");

  if (ch->level < 10)
    {
      if (ch->alignment > 900)
	sprintf (buf2, "devout");
      else if (ch->alignment > 700)
	sprintf (buf2, "noble");
      else if (ch->alignment > 350)
	sprintf (buf2, "honorable");
      else if (ch->alignment > 100)
	sprintf (buf2, "worthy");
      else if (ch->alignment > -100)
	sprintf (buf2, "neutral");
      else if (ch->alignment > -350)
	sprintf (buf2, "base");
      else if (ch->alignment > -700)
	sprintf (buf2, "evil");
      else if (ch->alignment > -900)
	sprintf (buf2, "ignoble");
      else
	sprintf (buf2, "fiendish");
    }
  else
    sprintf (buf2, "%d", ch->alignment);
  pager_printf_color (ch,
		      "&g|&GLevel: &w%-4d &g|&GFavor: &w%-10s &g|&GAlignment: &w%-9s &g|&GExperience: &w%-9d&g|\n\r",
		      ch->level, buf, buf2, ch->exp);
  send_to_pager_color
    ("&g ----------------------------------------------------------------------------\n\r",
     ch);
  switch (ch->style)
    {
    case STYLE_EVASIVE:
      sprintf (buf, "evasive");
      break;
    case STYLE_DEFENSIVE:
      sprintf (buf, "defensive");
      break;
    case STYLE_AGGRESSIVE:
      sprintf (buf, "aggressive");
      break;
    case STYLE_BERSERK:
      sprintf (buf, "berserk");
      break;
    default:
      sprintf (buf, "standard");
      break;
    }
  pager_printf_color (ch,
     "&g|&GGlory: &w%-4d &g|&GWeight: &w%-9d &g|&GStyle: &w%-13s &g|&GGold: &w%-14s &g|\n\r",
     ch->pcdata->quest_curr, ch->carry_weight, buf, num_punct (ch->gold));
#ifdef ENABLE_GOLD_SILVER_COPPER
	pager_printf_color (ch, "|            |Silver: %-9s",
		num_punct (ch->silver));
	pager_printf_color (ch, " |Copper: %-13s|                     |\n\r",
		num_punct (ch->copper));
#endif
  send_to_pager_color
    ("&g ----------------------------------------------------------------------------\n\r",
     ch);
  if (ch->level < 15 && !IS_PKILL (ch))
    pager_printf_color (ch,
			"&g|            |&GHitroll: &g-------- |&GDamroll: &g----------- |                     |\n\r");
  else if (ch->level >= 50)
    pager_printf_color (ch,
			"&g|&GHonour: &w%-3d &g|&GRank: &w%-11s &g|&GHitroll: &w%-11d &g|&GDamroll: &w%-11d &g|\n\r",
			ch->pcdata->honour, get_honour (ch), GET_HITROLL (ch),
			GET_DAMROLL (ch));
  else
    pager_printf_color (ch,
			"&g|            |&GHitroll: &w%-8d &g|&GDamroll: &w%-11d &g|                     |\n\r",
			GET_HITROLL (ch), GET_DAMROLL (ch));
  send_to_pager_color
    ("&g ----------------------------------------------------------------------------\n\r",
     ch);
  return;
}


#ifndef NEWSCORE
/*
 * New score command by Haus
 * This version is left for the people who have lost sight of reality so badly as to
 * become violently problematic over the colors added to do_score
 */
void
do_score (CHAR_DATA * ch, char *argument)
{
  char buf[MAX_STRING_LENGTH];
  AFFECT_DATA *paf;
//    int iLang;

  if (IS_NPC (ch))
    {
      do_oldscore (ch, argument);
      return;
    }
  set_pager_color (AT_SCORE, ch);

  pager_printf (ch, _("\nScore for %s%s.\n"), ch->name, ch->pcdata->title);

  if (get_trust (ch) != ch->level)
    pager_printf (ch, _("You are trusted at level %d.\n"), get_trust (ch));

  send_to_pager
    ("----------------------------------------------------------------------------\n\r",
     ch);

  pager_printf (ch,
		_("LEVEL: %-3d         Race : %-10.10s        Played: %d hours\n"),
		ch->level, capitalize (get_race (ch)),
		(get_age (ch) - 17) * 2);

  pager_printf (ch, _("YEARS: %-6d      Class: %-11.11s       Log In: %s"),
		get_age (ch), capitalize (get_class (ch)),
		ctime (&(ch->logon)));

  if (ch->level >= 15 || IS_PKILL (ch))
    {
      pager_printf (ch,
		    _("STR  : %2.2d(%2.2d)      HitRoll: %-4d            Saved:  %s"),
		    get_curr_str (ch), ch->perm_str, GET_HITROLL (ch),
		    ch->save_time ? ctime (&(ch->save_time)) :
		    _("no save this session\n"));

      pager_printf (ch,
		    _("INT  : %2.2d(%2.2d)      DamRoll: %-4d            Time:   %s"),
		    get_curr_int (ch), ch->perm_int, GET_DAMROLL (ch),
		    ctime (&current_time));
    }
  else
    {
      pager_printf (ch,
		    _("STR  : %2.2d(%2.2d)                               Saved:  %s"),
		    get_curr_str (ch), ch->perm_str,
		    ch->save_time ? ctime (&(ch->save_time)) :
		    _("no save this session\n"));

      pager_printf (ch,
		    _("INT  : %2.2d(%2.2d)                               Time:   %s"),
		    get_curr_int (ch), ch->perm_int, ctime (&current_time));
    }

  if (GET_AC (ch) >= 101)
    sprintf (buf, _("the rags of a beggar"));
  else if (GET_AC (ch) >= 80)
    sprintf (buf, _("improper for adventure"));
  else if (GET_AC (ch) >= 55)
    sprintf (buf, _("shabby and threadbare"));
  else if (GET_AC (ch) >= 40)
    sprintf (buf, _("of poor quality"));
  else if (GET_AC (ch) >= 20)
    sprintf (buf, _("scant protection"));
  else if (GET_AC (ch) >= 10)
    sprintf (buf, _("that of a knave"));
  else if (GET_AC (ch) >= 0)
    sprintf (buf, _("moderately crafted"));
  else if (GET_AC (ch) >= -10)
    sprintf (buf, _("well crafted"));
  else if (GET_AC (ch) >= -20)
    sprintf (buf, _("the envy of squires"));
  else if (GET_AC (ch) >= -40)
    sprintf (buf, _("excellently crafted"));
  else if (GET_AC (ch) >= -60)
    sprintf (buf, _("the envy of knights"));
  else if (GET_AC (ch) >= -80)
    sprintf (buf, _("the envy of barons"));
  else if (GET_AC (ch) >= -100)
    sprintf (buf, _("the envy of dukes"));
  else if (GET_AC (ch) >= -200)
    sprintf (buf, _("the envy of emperors"));
  else
    sprintf (buf, _("that of an avatar"));
  if (ch->level > 24)
    pager_printf (ch, _("WIS  : %2.2d(%2.2d)      Armor: %4.4d, %s\n"),
		  get_curr_wis (ch), ch->perm_wis, GET_AC (ch), buf);
  else
    pager_printf (ch, _("WIS  : %2.2d(%2.2d)      Armor: %s \n"),
		  get_curr_wis (ch), ch->perm_wis, buf);

  if (ch->alignment > 900)
    sprintf (buf, "devout");
  else if (ch->alignment > 700)
    sprintf (buf, "noble");
  else if (ch->alignment > 350)
    sprintf (buf, "honorable");
  else if (ch->alignment > 100)
    sprintf (buf, "worthy");
  else if (ch->alignment > -100)
    sprintf (buf, "neutral");
  else if (ch->alignment > -350)
    sprintf (buf, "base");
  else if (ch->alignment > -700)
    sprintf (buf, "evil");
  else if (ch->alignment > -900)
    sprintf (buf, "ignoble");
  else
    sprintf (buf, "fiendish");
  if (ch->level < 10)
    pager_printf (ch,
		  _("DEX  : %2.2d(%2.2d)      Align: %-20.20s    Items: %5.5d   (max %5.5d)\n"),
		  get_curr_dex (ch), ch->perm_dex, buf, ch->carry_number,
		  can_carry_n (ch));
  else
    pager_printf (ch,
		  _("DEX  : %2.2d(%2.2d)      Align: %+4.4d, %-14.14s   Items: %5.5d   (max %5.5d)\n"),
		  get_curr_dex (ch), ch->perm_dex, ch->alignment, buf,
		  ch->carry_number, can_carry_n (ch));

  switch (ch->position)
    {
    case POS_DEAD:
      sprintf (buf, _("slowly decomposing"));
      break;
    case POS_MORTAL:
      sprintf (buf, _("mortally wounded"));
      break;
    case POS_INCAP:
      sprintf (buf, _("incapacitated"));
      break;
    case POS_STUNNED:
      sprintf (buf, _("stunned"));
      break;
    case POS_SLEEPING:
      sprintf (buf, _("sleeping"));
      break;
    case POS_RESTING:
      sprintf (buf, _("resting"));
      break;
    case POS_STANDING:
      sprintf (buf, _("standing"));
      break;
    case POS_FIGHTING:
      sprintf (buf, _("fighting"));
      break;
    case POS_EVASIVE:
      sprintf (buf, _("fighting (evasive)"));	/* Fighting style support -haus */
      break;
    case POS_DEFENSIVE:
      sprintf (buf, _("fighting (defensive)"));
      break;
    case POS_AGGRESSIVE:
      sprintf (buf, _("fighting (aggressive)"));
      break;
    case POS_BERSERK:
      sprintf (buf, _("fighting (berserk)"));
      break;
    case POS_MOUNTED:
      sprintf (buf, _("mounted"));
      break;
    case POS_SITTING:
      sprintf (buf, _("sitting"));
      break;
    }
  pager_printf (ch,
		_("CON  : %2.2d(%2.2d)      Pos'n: %-21.21s  Weight: %5.5d (max %7.7d)\n"),
		get_curr_con (ch), ch->perm_con, buf, ch->carry_weight,
		can_carry_w (ch));


  /*
   * Fighting style support -haus
   */
  pager_printf (ch, _("CHA  : %2.2d(%2.2d)      Wimpy: %-5d     \n"),
		get_curr_cha (ch), ch->perm_cha, ch->wimpy);

  pager_printf (ch, _("LCK  : %2.2d(%2.2d)      "),
		get_curr_lck (ch), ch->perm_lck);

  switch (ch->style)
    {
    case STYLE_EVASIVE:
      sprintf (buf, _("evasive"));
      break;
    case STYLE_DEFENSIVE:
      sprintf (buf, _("defensive"));
      break;
    case STYLE_AGGRESSIVE:
      sprintf (buf, _("aggressive"));
      break;
    case STYLE_BERSERK:
      sprintf (buf, _("berserk"));
      break;
    default:
      sprintf (buf, _("standard"));
      break;
    }
  pager_printf (ch, _("Style: %-10.10s\n"), buf);
  if (ch->level >= 50)
    pager_printf (ch, _("Honour: %3.3d        Rank: %s\n"), ch->pcdata->honour,
		  get_honour (ch));

#ifdef PLRSHOWSTANCE
  pager_printf (ch, _("Glory: %4.4d(%4.4d)  Stance: %s\n"),
		ch->pcdata->quest_curr, ch->pcdata->quest_accum,
		get_stance_name (ch->stance));
#else
  pager_printf (ch, _("Glory: %4.4d(%4.4d)\n"),
		ch->pcdata->quest_curr, ch->pcdata->quest_accum);
#endif

  pager_printf (ch,
		_("PRACT: %3.3d         Hitpoints: %-5d of %5d   Pager: (%c) %3d    AutoExit(%c)\n"),
		ch->practice, ch->hit, ch->max_hit, IS_SET (ch->pcdata->flags,
							    PCFLAG_PAGERON) ?
		'X' : ' ', ch->pcdata->pagerlen, xIS_SET (ch->act,
							  PLR_AUTOEXIT) ? 'X'
		: ' ');

  if (IS_VAMPIRE(ch) || IS_DEMON(ch))
    pager_printf (ch,
		  _("XP   : %-9d       Blood: %-5d of %5d   MKills:  %-5.5d    AutoLoot(%c)\n"),
		  ch->exp, ch->pcdata->condition[COND_BLOODTHIRST],
		  10 + ch->level, ch->pcdata->mkills, xIS_SET (ch->act,
							       PLR_AUTOLOOT) ?
		  'X' : ' ');
  else if (ch->class == CLASS_WARRIOR)
    pager_printf (ch,
		  _("XP   : %-9d                               MKills:  %-5.5d    AutoLoot(%c)\n"),
		  ch->exp, ch->pcdata->mkills, xIS_SET (ch->act,
							PLR_AUTOLOOT) ? 'X' :
		  ' ');
  else
    pager_printf (ch,
		  _("XP   : %-9d        Mana: %-5d of %5d   MKills:  %-5.5d    AutoLoot(%c)\n"),
		  ch->exp, ch->mana, ch->max_mana, ch->pcdata->mkills,
		  xIS_SET (ch->act, PLR_AUTOLOOT) ? 'X' : ' ');

#ifdef ENABLE_GOLD_SILVER_COPPER
	pager_printf (ch, _("Move: %-5d of %5d   Mdeaths: %-5.5d    AutoSac (%c)\n"),
		ch->move, ch->max_move, ch->pcdata->mdeaths, xIS_SET(ch->act, PLR_AUTOSAC) ? 'X' : ' ');
	pager_printf (ch, _("Gold: %s  "), num_punct(ch->gold));
	pager_printf (ch, _("Silver: %s	"), num_punct(ch->silver));
	pager_printf (ch, _("Copper: %s\n"), num_punct(ch->copper));
#else
  pager_printf (ch,
		_("GOLD : %-13s    Move: %-5d of %5d   Mdeaths: %-5.5d    AutoSac (%c)\n"),
		num_punct (ch->gold), ch->move, ch->max_move,
		ch->pcdata->mdeaths, xIS_SET (ch->act,
					      PLR_AUTOSAC) ? 'X' : ' ');
#endif
  if (!IS_NPC (ch) && ch->pcdata->condition[COND_DRUNK] > 10)
    send_to_pager ("You are drunk.\n\r", ch);
  if (!IS_NPC (ch) && ch->pcdata->condition[COND_THIRST] == 0)
    send_to_pager ("You are in danger of dehydrating.\n\r", ch);
  if (!IS_NPC (ch) && ch->pcdata->condition[COND_FULL] == 0)
    send_to_pager ("You are starving to death.\n\r", ch);
  if (ch->position != POS_SLEEPING)
    switch (ch->mental_state / 10)
      {
      default:
	send_to_pager ("You're completely messed up!\n\r", ch);
	break;
      case -10:
	send_to_pager ("You're barely conscious.\n\r", ch);
	break;
      case -9:
	send_to_pager ("You can barely keep your eyes open.\n\r", ch);
	break;
      case -8:
	send_to_pager ("You're extremely drowsy.\n\r", ch);
	break;
      case -7:
	send_to_pager ("You feel very unmotivated.\n\r", ch);
	break;
      case -6:
	send_to_pager ("You feel sedated.\n\r", ch);
	break;
      case -5:
	send_to_pager ("You feel sleepy.\n\r", ch);
	break;
      case -4:
	send_to_pager ("You feel tired.\n\r", ch);
	break;
      case -3:
	send_to_pager ("You could use a rest.\n\r", ch);
	break;
      case -2:
	send_to_pager ("You feel a little under the weather.\n\r", ch);
	break;
      case -1:
	send_to_pager ("You feel fine.\n\r", ch);
	break;
      case 0:
	send_to_pager ("You feel great.\n\r", ch);
	break;
      case 1:
	send_to_pager ("You feel energetic.\n\r", ch);
	break;
      case 2:
	send_to_pager ("Your mind is racing.\n\r", ch);
	break;
      case 3:
	send_to_pager ("You can't think straight.\n\r", ch);
	break;
      case 4:
	send_to_pager ("Your mind is going 100 miles an hour.\n\r", ch);
	break;
      case 5:
	send_to_pager ("You're high as a kite.\n\r", ch);
	break;
      case 6:
	send_to_pager ("Your mind and body are slipping apart.\n\r", ch);
	break;
      case 7:
	send_to_pager ("Reality is slipping away.\n\r", ch);
	break;
      case 8:
	send_to_pager ("You have no idea what is real, and what is not.\n\r",
		       ch);
	break;
      case 9:
	send_to_pager ("You feel immortal.\n\r", ch);
	break;
      case 10:
	send_to_pager ("You are a Supreme Entity.\n\r", ch);
	break;
      }
  else if (ch->mental_state > 45)
    send_to_pager ("Your sleep is filled with strange and vivid dreams.\n\r",
		   ch);
  else if (ch->mental_state > 25)
    send_to_pager ("Your sleep is uneasy.\n\r", ch);
  else if (ch->mental_state < -35)
    send_to_pager ("You are deep in a much needed sleep.\n\r", ch);
  else if (ch->mental_state < -25)
    send_to_pager ("You are in deep slumber.\n\r", ch);
/*
    send_to_pager("Languages: ", ch );
    for ( iLang = 0; lang_array[iLang] != LANG_UNKNOWN; iLang++ )
	if ( knows_language( ch, lang_array[iLang], ch )
	||  (IS_NPC(ch) && ch->speaks == 0) )
	{
	    if ( lang_array[iLang] & ch->speaking
	    ||  (IS_NPC(ch) && !ch->speaking) )
		set_pager_color( AT_RED, ch );
	    send_to_pager( lang_names[iLang], ch );
	    send_to_pager( " ", ch );
	    set_pager_color( AT_SCORE, ch );
	}
    send_to_pager( "\n\r", ch );
*/
  if (ch->pcdata->bestowments && ch->pcdata->bestowments[0] != '\0')
    pager_printf (ch, "You are bestowed with the command(s): %s.\n\r",
		  ch->pcdata->bestowments);

  if (ch->morph && ch->morph->morph)
    {
      send_to_pager
	("----------------------------------------------------------------------------\n\r",
	 ch);
      if (IS_IMMORTAL (ch))
	pager_printf (ch, "Morphed as (%d) %s with a timer of %d.\n\r",
		      ch->morph->morph->vnum, ch->morph->morph->short_desc,
		      ch->morph->timer);
      else
	pager_printf (ch, "You are morphed into a %s.\n\r",
		      ch->morph->morph->short_desc);
      send_to_pager
	("----------------------------------------------------------------------------\n\r",
	 ch);
    }
  if (CAN_PKILL (ch))
    {
      send_to_pager
	("----------------------------------------------------------------------------\n\r",
	 ch);
      pager_printf (ch,
		    "PKILL DATA:  Pkills (%3.3d)     Illegal Pkills (%3.3d)     Pdeaths (%3.3d)\n\r",
		    ch->pcdata->pkills, ch->pcdata->illegal_pk,
		    ch->pcdata->pdeaths);
    }
  if (ch->pcdata->clan && ch->pcdata->clan->clan_type != CLAN_ORDER
      && ch->pcdata->clan->clan_type != CLAN_GUILD)
    {
      send_to_pager
	("----------------------------------------------------------------------------\n\r",
	 ch);
      pager_printf (ch,
		    "CLAN STATS:  %-14.14s  Clan AvPkills : %-5d  Clan NonAvpkills : %-5d\n\r",
		    ch->pcdata->clan->name, ch->pcdata->clan->pkills[6],
		    (ch->pcdata->clan->pkills[1] +
		     ch->pcdata->clan->pkills[2] +
		     ch->pcdata->clan->pkills[3] +
		     ch->pcdata->clan->pkills[4] +
		     ch->pcdata->clan->pkills[5]));
      pager_printf (ch,
		    "                             Clan AvPdeaths: %-5d  Clan NonAvpdeaths: %-5d\n\r",
		    ch->pcdata->clan->pdeaths[6],
		    (ch->pcdata->clan->pdeaths[1] +
		     ch->pcdata->clan->pdeaths[2] +
		     ch->pcdata->clan->pdeaths[3] +
		     ch->pcdata->clan->pdeaths[4] +
		     ch->pcdata->clan->pdeaths[5]));
    }
  if (ch->pcdata->deity)
    {
      send_to_pager
	("----------------------------------------------------------------------------\n\r",
	 ch);
      if (ch->pcdata->favor > 2250)
	sprintf (buf, "loved");
      else if (ch->pcdata->favor > 2000)
	sprintf (buf, "cherished");
      else if (ch->pcdata->favor > 1750)
	sprintf (buf, "honored");
      else if (ch->pcdata->favor > 1500)
	sprintf (buf, "praised");
      else if (ch->pcdata->favor > 1250)
	sprintf (buf, "favored");
      else if (ch->pcdata->favor > 1000)
	sprintf (buf, "respected");
      else if (ch->pcdata->favor > 750)
	sprintf (buf, "liked");
      else if (ch->pcdata->favor > 250)
	sprintf (buf, "tolerated");
      else if (ch->pcdata->favor > -250)
	sprintf (buf, "ignored");
      else if (ch->pcdata->favor > -750)
	sprintf (buf, "shunned");
      else if (ch->pcdata->favor > -1000)
	sprintf (buf, "disliked");
      else if (ch->pcdata->favor > -1250)
	sprintf (buf, "dishonored");
      else if (ch->pcdata->favor > -1500)
	sprintf (buf, "disowned");
      else if (ch->pcdata->favor > -1750)
	sprintf (buf, "abandoned");
      else if (ch->pcdata->favor > -2000)
	sprintf (buf, "despised");
      else if (ch->pcdata->favor > -2250)
	sprintf (buf, "hated");
      else
	sprintf (buf, "damned");
      pager_printf (ch, "Deity:  %-20s  Favor: %s\n\r",
		    ch->pcdata->deity->name, buf);
    }
  if (ch->pcdata->clan && ch->pcdata->clan->clan_type == CLAN_ORDER)
    {
      send_to_pager
	("----------------------------------------------------------------------------\n\r",
	 ch);
      pager_printf (ch,
		    "Order:  %-20s  Order Mkills:  %-6d   Order MDeaths:  %-6d\n\r",
		    ch->pcdata->clan->name, ch->pcdata->clan->mkills,
		    ch->pcdata->clan->mdeaths);
    }
  if (ch->pcdata->clan && ch->pcdata->clan->clan_type == CLAN_GUILD)
    {
      send_to_pager
	("----------------------------------------------------------------------------\n\r",
	 ch);
      pager_printf (ch,
		    "Guild:  %-20s  Guild Mkills:  %-6d   Guild MDeaths:  %-6d\n\r",
		    ch->pcdata->clan->name, ch->pcdata->clan->mkills,
		    ch->pcdata->clan->mdeaths);
    }
  if (IS_IMMORTAL (ch))
    {
      send_to_pager
	("----------------------------------------------------------------------------\n\r",
	 ch);

      pager_printf (ch, "IMMORTAL DATA:  Wizinvis [%s]  Wizlevel (%d)\n\r",
		    xIS_SET (ch->act, PLR_WIZINVIS) ? "X" : " ",
		    ch->pcdata->wizinvis);

      pager_printf (ch, "Bamfin:  %s %s\n\r", ch->name,
		    (ch->pcdata->bamfin[0] !=
		     '\0') ? ch->
		    pcdata->bamfin : "appears in a swirling mist.");
      pager_printf (ch, "Bamfout: %s %s\n\r", ch->name,
		    (ch->pcdata->bamfout[0] !=
		     '\0') ? ch->
		    pcdata->bamfout : "leaves in a swirling mist.");


      /* Area Loaded info - Scryn 8/11 */
      if (ch->pcdata->area)
	{
	  pager_printf (ch,
			"Vnums:   Room (%-5.5d - %-5.5d)   Object (%-5.5d - %-5.5d)   Mob (%-5.5d - %-5.5d)\n\r",
			ch->pcdata->area->low_r_vnum,
			ch->pcdata->area->hi_r_vnum,
			ch->pcdata->area->low_o_vnum,
			ch->pcdata->area->hi_o_vnum,
			ch->pcdata->area->low_m_vnum,
			ch->pcdata->area->hi_m_vnum);
	  pager_printf (ch, _("Area Loaded [%s]\n"),
			(IS_SET (ch->pcdata->area->status, AREA_LOADED)) ?
			_("yes") : _("no"));
	}
    }
  if (ch->first_affect)
    {
      int i;
      SKILLTYPE *sktmp;

      i = 0;
      send_to_pager
	("----------------------------------------------------------------------------\n\r",
	 ch);
      send_to_pager ("AFFECT DATA:                            ", ch);
      for (paf = ch->first_affect; paf; paf = paf->next)
	{
	  if ((sktmp = get_skilltype (paf->type)) == NULL)
	    continue;
	  if (ch->level < 20)
	    {
	      pager_printf (ch, "[%-34.34s]    ", sktmp->name);
	      if (i == 0)
		i = 2;
	      if ((++i % 3) == 0)
		send_to_pager ("\n\r", ch);
	    }
	  if (ch->level >= 20)
	    {
	      if (paf->modifier == 0)
		pager_printf (ch, "[%-24.24s;%5d rds]    ",
			      sktmp->name, paf->duration);
	      else if (paf->modifier > 999)
		pager_printf (ch, "[%-15.15s; %7.7s;%5d rds]    ",
			      sktmp->name,
			      tiny_affect_loc_name (paf->location),
			      paf->duration);
	      else
		pager_printf (ch, "[%-11.11s;%+-3.3d %7.7s;%5d rds]    ",
			      sktmp->name,
			      paf->modifier,
			      tiny_affect_loc_name (paf->location),
			      paf->duration);
	      if (i == 0)
		i = 1;
	      if ((++i % 2) == 0)
		send_to_pager ("\n\r", ch);
	    }
	}
    }
  send_to_pager ("\n\r", ch);
  return;
}

/* Alternative scoretable */
void do_altscore( CHAR_DATA *ch, char *argument )
{

  char buf[MAX_STRING_LENGTH];
  AFFECT_DATA *paf;
  int i;

  if (IS_NPC (ch))
    {
      do_oldscore (ch, argument);
      return;
    }

  set_pager_color (AT_SCORE, ch);

  pager_printf ( ch,
	"                                          ________________\n\r");

  pager_printf ( ch,
	" ________________________________________/%s\n\r",
  ch->name);

  pager_printf ( ch, _("| You are%s\n"),
	IS_NPC(ch) ? _(", the mobile.") : ch->pcdata->title);

  pager_printf ( ch,
	_("| You are level %d, and are %d years old.\n"),
  ch->level, get_age(ch) );

  if ( get_trust( ch ) != ch->level )
    {
			pager_printf ( ch, _("You are trusted at level %d.\n"),
	    get_trust( ch ) );
    }

  pager_printf ( ch, _("| You are a %s %s %s\n"),
	ch->sex == 0 ? _("Sexless") : ch->sex == 1 ? _("Male" : "Female"),
	capitalize (get_race (ch)),
	IS_NPC(ch) ? _("mobile") : capitalize (get_class (ch)));

  pager_printf ( ch,
	_("| You have %d practices.\n"),
	ch->practice);

  pager_printf ( ch,
	_("| Carrying %d/%d items at %d/10 pounds.\n"),
	ch->carry_number, can_carry_n(ch),
	can_carry_w(ch));


  pager_printf ( ch,
	_("| %d/%dHPs, %d/%dMana, %d/%dMoves.\n"),
	ch->hit,  ch->max_hit,
	ch->mana, ch->max_mana,
	ch->move, ch->max_move);

  if ( ch->level >= 15 )
    {
    pager_printf ( ch, _("| Hitroll: %d   Damroll: %d   Saved:  %d\n"),
		GET_HITROLL(ch),
		GET_DAMROLL(ch),
		ch->save_time ? ctime (&(ch->save_time)) : _("no save this session\n");
    }
    pager_printf ( ch, " ----------------------------------------------------------\n\r");
    pager_printf ( ch, _("|    Str: %d(%d)    |         {D-=ARMOR={D-\n"));

			if (GET_AC (ch) >= 101)
				sprintf (buf, "the rags of a beggar");
			else if (GET_AC (ch) >= 80)
				sprintf (buf, "improper for adventure");
			else if (GET_AC (ch) >= 55)
				sprintf (buf, "shabby and threadbare");
			else if (GET_AC (ch) >= 40)
				sprintf (buf, "of poor quality");
			else if (GET_AC (ch) >= 20)
				sprintf (buf, "scant protection");
			else if (GET_AC (ch) >= 10)
				sprintf (buf, "that of a knave");
			else if (GET_AC (ch) >= 0)
				sprintf (buf, "moderately crafted");
			else if (GET_AC (ch) >= -10)
				sprintf (buf, "well crafted");
			else if (GET_AC (ch) >= -20)
				sprintf (buf, "the envy of squires");
			else if (GET_AC (ch) >= -40)
				sprintf (buf, "excellently crafted");
			else if (GET_AC (ch) >= -60)
				sprintf (buf, "the envy of knights");
			else if (GET_AC (ch) >= -80)
				sprintf (buf, "the envy of barons");
			else if (GET_AC (ch) >= -100)
				sprintf (buf, "the envy of dukes");
			else if (GET_AC (ch) >= -200)
				sprintf (buf, "the envy of emperors");
			else
				sprintf (buf, "that of an avatar");

    pager_printf ( ch, _("|    Int: %d(%d)\n"),ch->perm_int);
    pager_printf ( ch, _("|    Wis: %d(%d)\n"),ch->perm_wis);
    pager_printf ( ch, _("|    Dex: %d(%d)\n"),ch->perm_dex);
    pager_printf ( ch, _("|    Con: %d(%d)\n"),ch->perm_con);

    pager_printf ( ch, " ----------------------------------------------------------\n");

#ifdef ENABLE_GOLD_SILVER_COPPER
    pager_printf ( ch, _("| You have %ld gold, %ld silver and %ld copper coins.\n"), ch->gold, ch->silver, ch->copper);
#ifdef BANK_INSTALLED
    pager_printf ( ch, _("| You have %ld gold and your bank balance is %ld gold, %ld silver, %ld copper coins.\n"),
		ch->gold, ch->pcdata->gbalance, ch->pcdata->sbalance, ch->pcdata->cbalance);
#endif
#else
    pager_printf ( ch, _("| You have %ld gold coins.\n"), ch->gold);
#ifdef BANK_INSTALLED
    pager_printf ( ch, _("| You have %ld gold and your bank balance is %ld gold coins.\n"),
		ch->gold, ch->pcdata->balance);
#endif
#endif
    
		if (!IS_NPC(ch)) {
			pager_printf ( ch, _("| You have scored %ld exp.\n"),
	    ch->exp);
    }

    if (ch->wimpy)
    {
			pager_printf ( ch, _("| Wimpy set to %d hit points.\n"), ch->wimpy );
    }
 
    pager_printf ( ch, _("| You are "));
         if ( ch->alignment >  900 ) sprintf ( buf, "angelic.");
    else if ( ch->alignment >  700 ) sprintf ( buf, "saintly.");
    else if ( ch->alignment >  350 ) sprintf ( buf, "good.");
    else if ( ch->alignment >  100 ) sprintf ( buf, "kind.");
    else if ( ch->alignment > -100 ) sprintf ( buf, "neutral.");
    else if ( ch->alignment > -350 ) sprintf ( buf, "mean.");
    else if ( ch->alignment > -700 ) sprintf ( buf, "evil.");
    else if ( ch->alignment > -900 ) sprintf ( buf, "demonic.");
    else                             sprintf ( buf, "satanic.");

    if ( ch->level >= 10 )
    {
			pager_printf ( ch, _("   Alignment: %d\n"), ch->alignment );
    }

    if (ch->pcdata->quest_curr)
    {
		if (ch->pcdata->quest_curr == 1)
	    pager_printf ( ch, _("| You have %d quest point.\n"), ch->pcdata->quest_curr );
		else
	    pager_printf ( ch, _("| You have %d quest points.\n"), ch->pcdata->quest_curr );
    }
    if (ch->pcdata->quest_accum)
    {	
		if (ch->pcdata->quest_accum == 1)
	    pager_printf ( ch, _("| You have accumulated %d quest point.\n"), ch->pcdata->quest_accum);
		else
	    pager_printf ( ch, _("| You have accumulated %d quest points.\n"), ch->pcdata->quest_accum);
    }

    /* RT wizinvis and holy light */
    if ( IS_IMMORTAL(ch))
    {
      pager_printf ( ch, _("| Holy Light: "));
      if (xIS_SET(ch->act,PLR_HOLYLIGHT))
        pager_printf ( ch, _("On"));
      else
        pager_printf ( ch, _("Off"));

      if (ch->pcdata->wizinvis)
      {
        pager_printf ( ch, _("  Wizi %d"), ch->pcdata->wizinvis);
      }
      pager_printf ( ch,"\n\r");
    }

	 if (ch->first_affect)
   {
      int i;
      SKILLTYPE *sktmp;

	    i = 0;
	    send_to_pager (" ----------------------------------------------------------\n\r", ch);

    send_to_pager (_("Affect Data:                            "), ch);
    for (paf = ch->first_affect; paf; paf = paf->next)
			{
		  if ((sktmp = get_skilltype (paf->type)) == NULL)
		    continue;
			  if (ch->level < 20)
			    {
			      pager_printf (ch, "[%-34.34s]    ", sktmp->name);
			      if (i == 0)
							i = 2;
					      if ((++i % 3) == 0)
									send_to_pager ("\n\r", ch);
						    }
							  if (ch->level >= 20)
						    {
						      if (paf->modifier == 0)
										pager_printf (ch, "[%-24.24s;%5d rds]    ",
							      sktmp->name, paf->duration);
						      else if (paf->modifier > 999)
										pager_printf (ch, "[%-15.15s; %7.7s;%5d rds]    ",
							      sktmp->name,
			  				    tiny_affect_loc_name (paf->location),
			  				    paf->duration);
						      else
										pager_printf (ch, "[%-11.11s;%+-3.3d %7.7s;%5d rds]    ",
							      sktmp->name,
							      paf->modifier,
							      tiny_affect_loc_name (paf->location),
							      paf->duration);
				    if (i == 0)
						i = 1;
	      			if ((++i % 2) == 0)
								send_to_pager ("\n\r", ch);
					    }
			}
	}   

  send_to_pager ("\n\r", ch);
  return;
}
#endif

void
do_colorscheme (CHAR_DATA * ch, char *argument)
{
  char arg[MAX_INPUT_LENGTH];

  argument = one_argument (argument, arg);

  if (IS_NPC (ch))
    return;

  if (!strcmp (arg, "1"))
    {
      ch->pcdata->colorize[24] = 2;
      ch->pcdata->colorize[25] = 3;
      ch->pcdata->colorize[38] = 7;
      send_to_char_color ("&GColor scheme set.\n\r", ch);
    }
  else if (!strcmp (arg, "2"))
    {
      ch->pcdata->colorize[24] = 2;
      ch->pcdata->colorize[25] = 15;
      ch->pcdata->colorize[38] = 7;
      send_to_char_color ("&GColor scheme set.\n\r", ch);
    }
  else if (!strcmp (arg, "3"))
    {
      ch->pcdata->colorize[24] = 2;
      ch->pcdata->colorize[25] = 7;
      ch->pcdata->colorize[38] = 15;
      send_to_char_color ("&GColor scheme set.\n\r", ch);
    }
  else if (!strcmp (arg, "4"))
    {
      ch->pcdata->colorize[24] = 3;
      ch->pcdata->colorize[25] = 2;
      ch->pcdata->colorize[38] = 15;
      send_to_char_color ("&GColor scheme set.\n\r", ch);
    }
  else if (!strcmp (arg, "5"))
    {
      ch->pcdata->colorize[24] = 3;
      ch->pcdata->colorize[25] = 15;
      ch->pcdata->colorize[38] = 7;
      send_to_char_color ("&GColor scheme set.\n\r", ch);
    }
  else if (!strcmp (arg, "6"))
    {
      ch->pcdata->colorize[24] = 3;
      ch->pcdata->colorize[25] = 7;
      ch->pcdata->colorize[38] = 15;
      send_to_char_color ("&GColor scheme set.\n\r", ch);
    }
  else if (!strcmp (arg, "7"))
    {
      ch->pcdata->colorize[24] = 15;
      ch->pcdata->colorize[25] = 2;
      ch->pcdata->colorize[38] = 7;
      send_to_char_color ("&GColor scheme set.\n\r", ch);
    }
  else if (!strcmp (arg, "8"))
    {
      ch->pcdata->colorize[24] = 15;
      ch->pcdata->colorize[25] = 10;
      ch->pcdata->colorize[38] = 7;
      send_to_char_color ("&GColor scheme set.\n\r", ch);
    }
  else if (!strcmp (arg, "9"))
    {
      ch->pcdata->colorize[24] = 15;
      ch->pcdata->colorize[25] = 3;
      ch->pcdata->colorize[38] = 7;
      send_to_char_color ("&GColor scheme set.\n\r", ch);
    }
  else if (!strcmp (arg, "default"))
    {
      ch->pcdata->colorize[25] = -1;
      ch->pcdata->colorize[24] = -1;
      ch->pcdata->colorize[38] = -1;
      send_to_char_color ("&GColor scheme set to MUD default.\n\r", ch);
    }
  else
    do_help (ch, "colorscheme");
  return;
}

void
do_compass (CHAR_DATA * ch, char *argument)
{
  char arg[MAX_INPUT_LENGTH];

  one_argument (argument, arg);

  if (arg[0] == '\0')
    {
      if (xIS_SET (ch->act, PLR_COMPASS))
	{
	  xREMOVE_BIT (ch->act, PLR_COMPASS);
	  send_to_char (_("Compass is now off.\n"), ch);
	  return;
	}
      else
	{
	  xSET_BIT (ch->act, PLR_COMPASS);
	  do_look (ch, "auto");
	  return;
	}
    }
  if ((strcmp (arg, "on") == 0) || (strcmp (arg, "ON") == 0))
    {
      xSET_BIT (ch->act, PLR_COMPASS);
      do_look (ch, "auto");
      return;
    }
  if ((strcmp (arg, "off") == 0) || (strcmp (arg, "OFF") == 0))
    {
      xREMOVE_BIT (ch->act, PLR_COMPASS);
      send_to_char (_("Compass is now off.\n"), ch);
      return;
    }
}


#ifdef NEWSCORE
/*
 * New score command by Haus
 * Colorized in 2001
 */
void
do_score (CHAR_DATA * ch, char *argument)
{
  char buf[MAX_STRING_LENGTH];
  AFFECT_DATA *paf;
//    int iLang;

  if (IS_NPC (ch))
    {
      do_oldscore (ch, argument);
      return;
    }
  set_pager_color (AT_GREEN, ch);

  pager_printf_color (ch, _("\n&GScore for %s%s.\n"), ch->name, ch->pcdata->title);

  if (get_trust (ch) != ch->level)
    pager_printf_color (ch, _("&GYou are trusted at level &Y%d.\n"), get_trust (ch));

  send_to_pager_color
    ("&g----------------------------------------------------------------------------\n\r", ch);

  pager_printf_color (ch,
		      _("&GLEVEL: &w%-3d         &GRace : &w%-10.10s        &gPlayed: &w%d hours\n"),
		      ch->level, capitalize (get_race (ch)),
		      (get_age (ch) - 17) * 2);

  pager_printf_color (ch,
		      _("&GYEARS: &w%-6d      &GClass: &w%-11.11s       &gLog In: &w%s"),
		      get_age (ch), capitalize (get_class (ch)),
		      ctime (&(ch->logon)));

  if (ch->level >= 15 || IS_PKILL (ch))
    {
      pager_printf_color (ch,
			  _("&GSTR  : &w%2.2d&g(&W%2.2d&g)      &GHitRoll: &R%-4d            &gSaved:  &w%s"),
			  get_curr_str (ch), ch->perm_str, GET_HITROLL (ch),
			  ch->save_time ? ctime (&(ch->save_time)) :
			  _("no save this session\n"));

      pager_printf_color (ch,
			  _("&GINT  : &w%2.2d&g(&W%2.2d&g)      &GDamRoll: &R%-4d            &gTime:   &w%s"),
			  get_curr_int (ch), ch->perm_int, GET_DAMROLL (ch),
			  ctime (&current_time));
    }
  else
    {
      pager_printf_color (ch,
			  _("&GSTR  : &w%2.2d&g(&W%2.2d&g)                               &gSaved:  &w%s"),
			  get_curr_str (ch), ch->perm_str,
			  ch->save_time ? ctime (&(ch->save_time)) :
			  _("no save this session\n"));

      pager_printf_color (ch,
			  _("&GINT  : &w%2.2d&g(&W%2.2d&g)                               &gTime:   &w%s"),
			  get_curr_int (ch), ch->perm_int,
			  ctime (&current_time));
    }

  if (GET_AC (ch) >= 101)
    sprintf (buf, "the rags of a beggar");
  else if (GET_AC (ch) >= 80)
    sprintf (buf, "improper for adventure");
  else if (GET_AC (ch) >= 55)
    sprintf (buf, "shabby and threadbare");
  else if (GET_AC (ch) >= 40)
    sprintf (buf, "of poor quality");
  else if (GET_AC (ch) >= 20)
    sprintf (buf, "scant protection");
  else if (GET_AC (ch) >= 10)
    sprintf (buf, "that of a knave");
  else if (GET_AC (ch) >= 0)
    sprintf (buf, "moderately crafted");
  else if (GET_AC (ch) >= -10)
    sprintf (buf, "well crafted");
  else if (GET_AC (ch) >= -20)
    sprintf (buf, "the envy of squires");
  else if (GET_AC (ch) >= -40)
    sprintf (buf, "excellently crafted");
  else if (GET_AC (ch) >= -60)
    sprintf (buf, "the envy of knights");
  else if (GET_AC (ch) >= -80)
    sprintf (buf, "the envy of barons");
  else if (GET_AC (ch) >= -100)
    sprintf (buf, "the envy of dukes");
  else if (GET_AC (ch) >= -200)
    sprintf (buf, "the envy of emperors");
  else
    sprintf (buf, "that of an avatar");
  if (ch->level > 24)
    pager_printf_color (ch,
			_("&GWIS  : &w%2.2d&g(&W%2.2d&g)      &GArmor: &w%4.4d, %s\n"),
			get_curr_wis (ch), ch->perm_wis, GET_AC (ch), buf);
  else
    pager_printf_color (ch,
			_("&GWIS  : &w%2.2d&g(&W%2.2d&g)      &WArmor: &w%s \n"),
			get_curr_wis (ch), ch->perm_wis, buf);

  if (ch->alignment > 900)
    sprintf (buf, "devout");
  else if (ch->alignment > 700)
    sprintf (buf, "noble");
  else if (ch->alignment > 350)
    sprintf (buf, "honorable");
  else if (ch->alignment > 100)
    sprintf (buf, "worthy");
  else if (ch->alignment > -100)
    sprintf (buf, "neutral");
  else if (ch->alignment > -350)
    sprintf (buf, "base");
  else if (ch->alignment > -700)
    sprintf (buf, "evil");
  else if (ch->alignment > -900)
    sprintf (buf, "ignoble");
  else
    sprintf (buf, "fiendish");
  if (ch->level < 10)
    pager_printf_color (ch,
			_("&GDEX  : &w%2.2d&g(&W%2.2d&g)      &GAlign: &w%-20.20s    &GItems: &W%5.5d   &g(&wmax %5.5d&g)\n"),
			get_curr_dex (ch), ch->perm_dex, buf,
			ch->carry_number, can_carry_n (ch));
  else
    pager_printf_color (ch,
			_("&GDEX  : &w%2.2d&g(&W%2.2d&g)      &GAlign: &w%+4.4d, %-14.14s   &GItems: &W%5.5d   &g(&wmax %5.5d&g)\n"),
			get_curr_dex (ch), ch->perm_dex, ch->alignment, buf,
			ch->carry_number, can_carry_n (ch));

  switch (ch->position)
    {
    case POS_DEAD:
      sprintf (buf, _("slowly decomposing"));
      break;
    case POS_MORTAL:
      sprintf (buf, _("mortally wounded"));
      break;
    case POS_INCAP:
      sprintf (buf, _("incapacitated"));
      break;
    case POS_STUNNED:
      sprintf (buf, _("stunned"));
      break;
    case POS_SLEEPING:
      sprintf (buf, _("sleeping"));
      break;
    case POS_RESTING:
      sprintf (buf, _("resting"));
      break;
    case POS_STANDING:
      sprintf (buf, _("standing"));
      break;
    case POS_FIGHTING:
      sprintf (buf, _("fighting"));
      break;
    case POS_EVASIVE:
      sprintf (buf, _("fighting (evasive)"));	/* Fighting style support -haus */
      break;
    case POS_DEFENSIVE:
      sprintf (buf, _("fighting (defensive)"));
      break;
    case POS_AGGRESSIVE:
      sprintf (buf, _("fighting (aggressive)"));
      break;
    case POS_BERSERK:
      sprintf (buf, _("fighting (berserk)"));
      break;
    case POS_MOUNTED:
      sprintf (buf, _("mounted"));
      break;
    case POS_SITTING:
      sprintf (buf, _("sitting"));
      break;
    }
  pager_printf_color (ch,
		      _("&GCON  : &w%2.2d&g(&W%2.2d&g)      &GPos'n: &w%-21.21s  &GWeight: &W%5.5d &g(&wmax %7.7d&g)\n"),
		      get_curr_con (ch), ch->perm_con, buf, ch->carry_weight,
		      can_carry_w (ch));


  /*
   * Fighting style support -haus
   */
  pager_printf_color (ch,
		      _("&GCHA  : &w%2.2d&g(&W%2.2d&g)      &GWimpy: &Y%-5d     \n"),
		      get_curr_cha (ch), ch->perm_cha, ch->wimpy);

  pager_printf_color (ch, _("&GLCK  : &w%2.2d&g(&W%2.2d&g)      "),
		      get_curr_lck (ch), ch->perm_lck);

  switch (ch->style)
    {
    case STYLE_EVASIVE:
      sprintf (buf, _("evasive"));
      break;
    case STYLE_DEFENSIVE:
      sprintf (buf, _("defensive"));
      break;
    case STYLE_AGGRESSIVE:
      sprintf (buf, _("aggressive"));
      break;
    case STYLE_BERSERK:
      sprintf (buf, _("berserk"));
      break;
    default:
      sprintf (buf, _("standard"));
      break;
    }
  pager_printf_color (ch, _("&GStyle: &W%-10.10s\n"), buf);
  if (ch->level >= 50)
    pager_printf_color (ch, _("&GHonour: &w%3.3d        &GRank: &w%s\n"),
			ch->pcdata->honour, get_honour (ch));

#ifdef PLRSHOWSTANCE
  pager_printf_color (ch, _("&GGlory: &w%4.4d&g(&W%4.4d&g)  &GStance: &W%s\n"),
		      ch->pcdata->quest_curr, ch->pcdata->quest_accum,
		      get_stance_name (ch->stance));
#else
  pager_printf_color (ch, _("&GGlory: &w%4.4d&g(&W%4.4d&g)\n"),
		      ch->pcdata->quest_curr, ch->pcdata->quest_accum);
#endif

  pager_printf_color (ch,
		      _("&GPRACT: &w%3.3d         &GHitpoints: &W%-5d &gof &W%5d   &GPager: &g(&w%c&g) &w%3d    &GAutoExit&g(&w%c&g)\n"),
		      ch->practice, ch->hit, ch->max_hit,
		      IS_SET (ch->pcdata->flags, PCFLAG_PAGERON) ? 'X' : ' ',
		      ch->pcdata->pagerlen, xIS_SET (ch->act,
						     PLR_AUTOEXIT) ? 'X' :
		      ' ');

  if (IS_VAMPIRE(ch) || IS_DEMON(ch))
    pager_printf_color (ch,
			_("&GXP   : &w%-9d       &GBlood: &R%-5d &Gof &R%5d   &GMKills:  &w%-5.5d    &GAutoLoot&g(&w%c&g)\n"),
			ch->exp, ch->pcdata->condition[COND_BLOODTHIRST],
			10 + ch->level, ch->pcdata->mkills, xIS_SET (ch->act,
								     PLR_AUTOLOOT)
			? 'X' : ' ');
  else if (ch->class == CLASS_WARRIOR)
    pager_printf_color (ch,
			_("&GXP   : &w%-9d                               &GMKills:  &w%-5.5d    &GAutoLoot&g(&w%c&g)\n"),
			ch->exp, ch->pcdata->mkills, xIS_SET (ch->act,
							      PLR_AUTOLOOT) ?
			'X' : ' ');
  else
    pager_printf_color (ch,
			_("&GXP   : &w%-9d        &GMana: &C%-5d &Gof &C%5d   &GMKills:  &w%-5.5d    &GAutoLoot&g(&w%c&g)\n"),
			ch->exp, ch->mana, ch->max_mana, ch->pcdata->mkills,
			xIS_SET (ch->act, PLR_AUTOLOOT) ? 'X' : ' ');

#ifdef ENABLE_GOLD_SILVER_COPPER
	pager_printf_color (ch, _("&CMove: &W%-5d &Cof &w%5d   &CMdeaths: &W%5d    &CAutoSac (&W%c&C)\n"),
		ch->move, ch->max_move, ch->pcdata->mdeaths, xIS_SET(ch->act, PLR_AUTOSAC) ? 'X' : ' ');
	pager_printf_color (ch, _("&CGold: &Y%s "), num_punct(ch->gold));
	pager_printf_color (ch, _("&CSilver: &Y%s	"), num_punct(ch->silver));
	pager_printf_color (ch, _("&CCopper: &Y%s\n"), num_punct(ch->copper));
#else
  pager_printf_color (ch,
		      _("&GGOLD : &Y%-13s    &GMove: &w%-5d &Gof &w%5d   &GMdeaths: &w%-5.5d    &GAutoSac &g(&w%c&g)\n"),
		      num_punct (ch->gold), ch->move, ch->max_move,
		      ch->pcdata->mdeaths, xIS_SET (ch->act,
						    PLR_AUTOSAC) ? 'X' : ' ');
#endif

  set_char_color (AT_GREEN, ch);
  if (!IS_NPC (ch) && ch->pcdata->condition[COND_DRUNK] > 10)
    send_to_pager (_("You are drunk.\n"), ch);
  if (!IS_NPC (ch) && ch->pcdata->condition[COND_THIRST] == 0)
    send_to_pager (_("You are in danger of dehydrating.\n"), ch);
  if (!IS_NPC (ch) && ch->pcdata->condition[COND_FULL] == 0)
    send_to_pager (_("You are starving to death.\n"), ch);
  if (ch->position != POS_SLEEPING)
    switch (ch->mental_state / 10)
      {
      default:
	send_to_pager (_("You're completely messed up!\n"), ch);
	break;
      case -10:
	send_to_pager (_("You're barely conscious.\n"), ch);
	break;
      case -9:
	send_to_pager (_("You can barely keep your eyes open.\n"), ch);
	break;
      case -8:
	send_to_pager (_("You're extremely drowsy.\n"), ch);
	break;
      case -7:
	send_to_pager (_("You feel very unmotivated.\n"), ch);
	break;
      case -6:
	send_to_pager (_("You feel sedated.\n"), ch);
	break;
      case -5:
	send_to_pager (_("You feel sleepy.\n"), ch);
	break;
      case -4:
	send_to_pager (_("You feel tired.\n"), ch);
	break;
      case -3:
	send_to_pager (_("You could use a rest.\n"), ch);
	break;
      case -2:
	send_to_pager (_("You feel a little under the weather.\n"), ch);
	break;
      case -1:
	send_to_pager (_("You feel fine.\n"), ch);
	break;
      case 0:
	send_to_pager (_("You feel great.\n"), ch);
	break;
      case 1:
	send_to_pager (_("You feel energetic.\n"), ch);
	break;
      case 2:
	send_to_pager (_("Your mind is racing.\n"), ch);
	break;
      case 3:
	send_to_pager (_("You can't think straight.\n"), ch);
	break;
      case 4:
	send_to_pager (_("Your mind is going 100 miles an hour.\n"), ch);
	break;
      case 5:
	send_to_pager (_("You're high as a kite.\n"), ch);
	break;
      case 6:
	send_to_pager (_("Your mind and body are slipping apart.\n"), ch);
	break;
      case 7:
	send_to_pager (_("Reality is slipping away.\n"), ch);
	break;
      case 8:
	send_to_pager (_("You have no idea what is real, and what is not.\n"),
		       ch);
	break;
      case 9:
	send_to_pager (_("You feel immortal.\n"), ch);
	break;
      case 10:
	send_to_pager (_("You are a Supreme Entity.\n"), ch);
	break;
      }
  else if (ch->mental_state > 45)
    send_to_pager (_("Your sleep is filled with strange and vivid dreams.\n"),
		   ch);
  else if (ch->mental_state > 25)
    send_to_pager (_("Your sleep is uneasy.\n"), ch);
  else if (ch->mental_state < -35)
    send_to_pager (_("You are deep in a much needed sleep.\n"), ch);
  else if (ch->mental_state < -25)
    send_to_pager (_("You are in deep slumber.\n"), ch);
/*
    send_to_pager("Languages: ", ch );
    for ( iLang = 0; lang_array[iLang] != LANG_UNKNOWN; iLang++ )
	if ( knows_language( ch, lang_array[iLang], ch )
	||  (IS_NPC(ch) && ch->speaks == 0) )
	{
	    if ( lang_array[iLang] & ch->speaking
	    ||  (IS_NPC(ch) && !ch->speaking) )
		set_pager_color( AT_RED, ch );
	    send_to_pager( lang_names[iLang], ch );
	    send_to_pager( " ", ch );
	    set_pager_color( AT_SCORE, ch );
	}
    send_to_pager( "\n\r", ch );
*/
  if (ch->pcdata->bestowments && ch->pcdata->bestowments[0] != '\0')
    pager_printf (ch, _("You are bestowed with the command(s): %s.\n"),
		  ch->pcdata->bestowments);

  if (ch->morph && ch->morph->morph)
    {
      send_to_pager_color
	("&g----------------------------------------------------------------------------\n\r",
	 ch);
      if (IS_IMMORTAL (ch))
	pager_printf (ch, _("Morphed as (%d) %s with a timer of %d.\n"),
		      ch->morph->morph->vnum, ch->morph->morph->short_desc,
		      ch->morph->timer);
      else
	pager_printf (ch, _("You are morphed into a %s.\n"),
		      ch->morph->morph->short_desc);
      send_to_pager_color
	("&g----------------------------------------------------------------------------\n\r",
	 ch);
    }
  if (CAN_PKILL (ch))
    {
      send_to_pager_color
	("&g----------------------------------------------------------------------------\n\r",
	 ch);
      pager_printf_color (ch,
			  _("&GPKILL DATA:  Pkills &g(&w%3.3d&g)     &GIllegal Pkills &g(&w%3.3d&g)     &GPdeaths &g(&w%3.3d&g)\n"),
			  ch->pcdata->pkills, ch->pcdata->illegal_pk,
			  ch->pcdata->pdeaths);
    }
  if (ch->pcdata->clan && ch->pcdata->clan->clan_type != CLAN_ORDER
      && ch->pcdata->clan->clan_type != CLAN_GUILD)
    {
      send_to_pager_color
	("&g----------------------------------------------------------------------------\n\r",
	 ch);
      pager_printf_color (ch,
			  _("&GCLAN STATS:  &w%-14.14s  &GClan AvPkills : &w%-5d  &GClan NonAvpkills : &w%-5d\n"),
			  ch->pcdata->clan->name, ch->pcdata->clan->pkills[6],
			  (ch->pcdata->clan->pkills[1] +
			   ch->pcdata->clan->pkills[2] +
			   ch->pcdata->clan->pkills[3] +
			   ch->pcdata->clan->pkills[4] +
			   ch->pcdata->clan->pkills[5]));
      pager_printf_color (ch,
			  _("                             &GClan AvPdeaths: &w%-5d  &GClan NonAvpdeaths: &w%-5d\n"),
			  ch->pcdata->clan->pdeaths[6],
			  (ch->pcdata->clan->pdeaths[1] +
			   ch->pcdata->clan->pdeaths[2] +
			   ch->pcdata->clan->pdeaths[3] +
			   ch->pcdata->clan->pdeaths[4] +
			   ch->pcdata->clan->pdeaths[5]));
    }
  if (ch->pcdata->deity)
    {
      send_to_pager_color
	("&g----------------------------------------------------------------------------\n\r",
	 ch);
      if (ch->pcdata->favor > 2250)
	sprintf (buf, "loved");
      else if (ch->pcdata->favor > 2000)
	sprintf (buf, "cherished");
      else if (ch->pcdata->favor > 1750)
	sprintf (buf, "honored");
      else if (ch->pcdata->favor > 1500)
	sprintf (buf, "praised");
      else if (ch->pcdata->favor > 1250)
	sprintf (buf, "favored");
      else if (ch->pcdata->favor > 1000)
	sprintf (buf, "respected");
      else if (ch->pcdata->favor > 750)
	sprintf (buf, "liked");
      else if (ch->pcdata->favor > 250)
	sprintf (buf, "tolerated");
      else if (ch->pcdata->favor > -250)
	sprintf (buf, "ignored");
      else if (ch->pcdata->favor > -750)
	sprintf (buf, "shunned");
      else if (ch->pcdata->favor > -1000)
	sprintf (buf, "disliked");
      else if (ch->pcdata->favor > -1250)
	sprintf (buf, "dishonored");
      else if (ch->pcdata->favor > -1500)
	sprintf (buf, "disowned");
      else if (ch->pcdata->favor > -1750)
	sprintf (buf, "abandoned");
      else if (ch->pcdata->favor > -2000)
	sprintf (buf, "despised");
      else if (ch->pcdata->favor > -2250)
	sprintf (buf, "hated");
      else
	sprintf (buf, "damned");
      pager_printf_color (ch, _("&GDeity:  &w%-20s  &GFavor: &w%s\n"),
			  ch->pcdata->deity->name, buf);
    }
  if (ch->pcdata->clan && ch->pcdata->clan->clan_type == CLAN_ORDER)
    {
      send_to_pager_color
	("&g----------------------------------------------------------------------------\n\r",
	 ch);
      pager_printf_color (ch,
			  _("&GOrder:  &w%-20s  &GOrder Mkills:  &w%-6d   &GOrder MDeaths:  &w%-6d\n"),
			  ch->pcdata->clan->name, ch->pcdata->clan->mkills,
			  ch->pcdata->clan->mdeaths);
    }
  if (ch->pcdata->clan && ch->pcdata->clan->clan_type == CLAN_GUILD)
    {
      send_to_pager_color
	("&g----------------------------------------------------------------------------\n\r",
	 ch);
      pager_printf_color (ch,
			  _("&GGuild:  &w%-20s  &GGuild Mkills:  &w%-6d   &GGuild MDeaths:  &w%-6d\n"),
			  ch->pcdata->clan->name, ch->pcdata->clan->mkills,
			  ch->pcdata->clan->mdeaths);
    }
  if (IS_IMMORTAL (ch))
    {
      send_to_pager_color
	("&g----------------------------------------------------------------------------\n\r",
	 ch);

      pager_printf_color (ch,
			  _("&GIMMORTAL DATA:  Wizinvis &g[&w%s&g]  &GWizlevel &g(&w%d&g)\n"),
			  xIS_SET (ch->act, PLR_WIZINVIS) ? "X" : " ",
			  ch->pcdata->wizinvis);

      pager_printf_color (ch, _("&GBamfin:  &W%s %s\n"), ch->name,
			  (ch->pcdata->bamfin[0] !=
			   '\0') ? ch->
			  pcdata->bamfin : _("appears in a swirling mist."));
      pager_printf_color (ch, _("&GBamfout: &W%s %s\n"), ch->name,
			  (ch->pcdata->bamfout[0] !=
			   '\0') ? ch->
			  pcdata->bamfout : _("leaves in a swirling mist."));


      /* Area Loaded info - Scryn 8/11 */
      if (ch->pcdata->area)
	{
	  pager_printf_color (ch,
			      _("&GVnums:   Room &g(&w%-5.5d - %-5.5d&g)   &GObject &g(&w%-5.5d - %-5.5d&g)   &GMob &g(&w%-5.5d - %-5.5d&g)\n"),
			      ch->pcdata->area->low_r_vnum,
			      ch->pcdata->area->hi_r_vnum,
			      ch->pcdata->area->low_o_vnum,
			      ch->pcdata->area->hi_o_vnum,
			      ch->pcdata->area->low_m_vnum,
			      ch->pcdata->area->hi_m_vnum);
	  pager_printf_color (ch, _("&GArea Loaded &g[&w%s&g]\n"),
			      (IS_SET (ch->pcdata->area->status, AREA_LOADED))
			      ? _("yes") : _("no"));
	}
    }
  if (ch->first_affect)
    {
      int i;
      SKILLTYPE *sktmp;

      i = 0;
      send_to_pager_color
	("&g----------------------------------------------------------------------------\n\r",
	 ch);
      send_to_pager_color (_("&GAFFECT DATA:                            "), ch);
      set_char_color (AT_WHITE, ch);
      for (paf = ch->first_affect; paf; paf = paf->next)
	{
	  if ((sktmp = get_skilltype (paf->type)) == NULL)
	    continue;
	  if (ch->level < 20)
	    {
	      pager_printf (ch, "[%-34.34s]    ", sktmp->name);
	      if (i == 0)
		i = 2;
	      if ((++i % 3) == 0)
		send_to_pager ("\n\r", ch);
	    }
	  if (ch->level >= 20)
	    {
	      if (paf->modifier == 0)
		pager_printf (ch, "[%-24.24s;%5d rds]    ",
			      sktmp->name, paf->duration);
	      else if (paf->modifier > 999)
		pager_printf (ch, "[%-15.15s; %7.7s;%5d rds]    ",
			      sktmp->name,
			      tiny_affect_loc_name (paf->location),
			      paf->duration);
	      else
		pager_printf (ch, "[%-11.11s;%+-3.3d %7.7s;%5d rds]    ",
			      sktmp->name,
			      paf->modifier,
			      tiny_affect_loc_name (paf->location),
			      paf->duration);
	      if (i == 0)
		i = 1;
	      if ((++i % 2) == 0)
		send_to_pager ("\n\r", ch);
	    }
	}
    }
  send_to_pager ("\n\r", ch);
  return;
}

void
do_altscore (CHAR_DATA * ch, char *argument)
{
  char buf[MAX_STRING_LENGTH];
  char arg[MAX_INPUT_LENGTH];
  AFFECT_DATA *paf;

  if (IS_NPC (ch))
    {
      do_oldscore (ch, argument);
      return;
    }
  set_pager_color (AT_GREEN, ch);

  pager_printf_color (ch, "\n\r&G%s%s.\n\r", ch->name, ch->pcdata->title);
  if (get_trust (ch) != ch->level)
    pager_printf (ch, _("You are trusted at level %d.\n"), get_trust (ch));

  send_to_pager_color
    ("&g----------------------------------------------------------------------------\n\r",
     ch);

  pager_printf_color (ch,
		      _("&gLevel: &W%-3d         &gRace : &W%-10.10s        &gPlayed: &W%d &ghours\n"),
		      ch->level, capitalize (get_race (ch)),
		      (get_age (ch) - 17) * 2);
  pager_printf_color (ch,
		      _("&gYears: &W%-6d      &gClass: &W%-11.11s       &gLog In: %s"),
		      get_age (ch), capitalize (get_class (ch)),
		      ctime (&(ch->logon)));

  if (ch->level >= 15 || IS_PKILL (ch))
    {
      pager_printf_color (ch,
			  _("&GSTR  : &W%2.2d&g(&w%2.2d&g)&G    HitRoll: &R%-4d               &gSaved: %s"),
			  get_curr_str (ch), ch->perm_str, GET_HITROLL (ch),
			  ch->save_time ? ctime (&(ch->save_time)) :
			  _("no save this session\n"));

      pager_printf_color (ch,
			  _("&GINT  : &W%2.2d&g(&w%2.2d&g)&G    DamRoll: &R%-4d                &gTime: %s"),
			  get_curr_int (ch), ch->perm_int, GET_DAMROLL (ch),
			  ctime (&current_time));
    }
  else
    {
      pager_printf_color (ch,
			  _("&GSTR  : &W%2.2d&g(&w%2.2d&g)&G                               Saved:  %s"),
			  get_curr_str (ch), ch->perm_str,
			  ch->save_time ? ctime (&(ch->save_time)) :
			  _("no save this session\n"));

      pager_printf_color (ch,
			  _("&GINT  : &W%2.2d&g(&w%2.2d&g)&G                               Time:   %s"),
			  get_curr_int (ch), ch->perm_int,
			  ctime (&current_time));
    }

  if (GET_AC (ch) >= 101)
    sprintf (buf, "the rags of a beggar");
  else if (GET_AC (ch) >= 80)
    sprintf (buf, "improper for adventure");
  else if (GET_AC (ch) >= 55)
    sprintf (buf, "shabby and threadbare");
  else if (GET_AC (ch) >= 40)
    sprintf (buf, "of poor quality");
  else if (GET_AC (ch) >= 20)
    sprintf (buf, "scant protection");
  else if (GET_AC (ch) >= 10)
    sprintf (buf, "that of a knave");
  else if (GET_AC (ch) >= 0)
    sprintf (buf, "moderately crafted");
  else if (GET_AC (ch) >= -10)
    sprintf (buf, "well crafted");
  else if (GET_AC (ch) >= -20)
    sprintf (buf, "the envy of squires");
  else if (GET_AC (ch) >= -40)
    sprintf (buf, "excellently crafted");
  else if (GET_AC (ch) >= -60)
    sprintf (buf, "the envy of knights");
  else if (GET_AC (ch) >= -80)
    sprintf (buf, "the envy of barons");
  else if (GET_AC (ch) >= -100)
    sprintf (buf, "the envy of dukes");
  else if (GET_AC (ch) >= -200)
    sprintf (buf, "the envy of emperors");
  else
    sprintf (buf, "that of an avatar");
  if (ch->level > 24)
    pager_printf_color (ch,
			_("&GWIS  : &W%2.2d&g(&w%2.2d&g)&G      Armor: &O%-d; %s\n"),
			get_curr_wis (ch), ch->perm_wis, GET_AC (ch), buf);
  else
    pager_printf_color (ch,
			_("&GWIS  : &W%2.2d&g(&w%2.2d&g)&G      Armor: &O%s \n"),
			get_curr_wis (ch), ch->perm_wis, buf);

  if (ch->alignment > 900)
    sprintf (buf, "devout");
  else if (ch->alignment > 700)
    sprintf (buf, "noble");
  else if (ch->alignment > 350)
    sprintf (buf, "honorable");
  else if (ch->alignment > 100)
    sprintf (buf, "worthy");
  else if (ch->alignment > -100)
    sprintf (buf, "neutral");
  else if (ch->alignment > -350)
    sprintf (buf, "base");
  else if (ch->alignment > -700)
    sprintf (buf, "evil");
  else if (ch->alignment > -900)
    sprintf (buf, "ignoble");
  else
    sprintf (buf, "fiendish");
  if (ch->level < 10)
    pager_printf_color (ch,
			_("&GDEX  : &W%2.2d&g(&w%2.2d&g)&G      Align: &W%-20.20s    &GItems:  &W%d (max %d)\n"),
			get_curr_dex (ch), ch->perm_dex, buf,
			ch->carry_number, can_carry_n (ch));
  else
    pager_printf_color (ch,
			_("&GDEX  : &W%2.2d&g(&w%2.2d&g)&G      Align: &W%4d; %-14.14s   &GItems:  &W%d &g(&wmax %d&g)\n"),
			get_curr_dex (ch), ch->perm_dex, ch->alignment, buf,
			ch->carry_number, can_carry_n (ch));

  switch (ch->position)
    {
    case POS_DEAD:
      sprintf (buf, "slowly decomposing");
      break;
    case POS_MORTAL:
      sprintf (buf, "mortally wounded");
      break;
    case POS_INCAP:
      sprintf (buf, "incapacitated");
      break;
    case POS_STUNNED:
      sprintf (buf, "stunned");
      break;
    case POS_SLEEPING:
      sprintf (buf, "sleeping");
      break;
    case POS_RESTING:
      sprintf (buf, "resting");
      break;
    case POS_STANDING:
      sprintf (buf, "standing");
      break;
    case POS_FIGHTING:
      sprintf (buf, "fighting");
      break;
    case POS_EVASIVE:
      sprintf (buf, "fighting (evasive)");	/* Fighting style support -haus */
      break;
    case POS_DEFENSIVE:
      sprintf (buf, "fighting (defensive)");
      break;
    case POS_AGGRESSIVE:
      sprintf (buf, "fighting (aggressive)");
      break;
    case POS_BERSERK:
      sprintf (buf, "fighting (berserk)");
      break;
    case POS_MOUNTED:
      sprintf (buf, "mounted");
      break;
    case POS_SITTING:
      sprintf (buf, "sitting");
      break;
    }
  pager_printf_color (ch,
		      _("&GCON  : &W%2.2d&g(&w%2.2d&g)&G      Pos'n: &W%-21.21s  &GWeight: &W%d &g(&wmax %d&g)\n"),
		      get_curr_con (ch), ch->perm_con, buf, ch->carry_weight,
		      can_carry_w (ch));


  /*
   * Fighting style support -haus
   */
  pager_printf_color (ch,
		      _("&GCHA  : &W%2.2d&g(&w%2.2d&g)&G      Wimpy: &Y%-5d      "),
		      get_curr_cha (ch), ch->perm_cha, ch->wimpy);

  switch (ch->style)
    {
    case STYLE_EVASIVE:
      sprintf (buf, "evasive");
      break;
    case STYLE_DEFENSIVE:
      sprintf (buf, "defensive");
      break;
    case STYLE_AGGRESSIVE:
      sprintf (buf, "aggressive");
      break;
    case STYLE_BERSERK:
      sprintf (buf, "berserk");
      break;
    default:
      sprintf (buf, "standard");
      break;
    }
  pager_printf_color (ch,
		      _("\n&GLCK  : &W%2.2d&g(&w%2.2d&g)&G      Style: &W%-10.10s\n"),
		      get_curr_lck (ch), ch->perm_lck, buf);

  pager_printf_color (ch, _("&GGlory: &W%d&g/&w%d\n"),
		      ch->pcdata->quest_curr, ch->pcdata->quest_accum);

  pager_printf_color (ch,
		      _("&GPRACT: &W%3d         &GHitpoints: &Y%-5d &Gof &Y%5d   &GPager: &G(&W%c&g) &W%3d    &GAutoExit&g(&W%c&g)\n"),
		      ch->practice, ch->hit, ch->max_hit,
		      IS_SET (ch->pcdata->flags, PCFLAG_PAGERON) ? 'X' : ' ',
		      ch->pcdata->pagerlen, xIS_SET (ch->act,
						     PLR_AUTOEXIT) ? 'X' :
		      ' ');

  if (IS_VAMPIRE(ch) || IS_DEMON(ch))
    pager_printf_color (ch,
			_("&GEXP  : &P%-9d       &GBlood: &R%-5d &Gof &R%5d   &GMKills:  &W%5d    &GAutoLoot&g(&W%c&g)\n"),
			ch->exp, ch->pcdata->condition[COND_BLOODTHIRST],
			10 + ch->level, ch->pcdata->mkills, xIS_SET (ch->act,
								     PLR_AUTOLOOT)
			? 'X' : ' ');
  else if (ch->class == CLASS_WARRIOR)
    pager_printf_color (ch,
			_("&GEXP  : &P%-9d                               &GMKills:  &W%5d    &GAutoLoot&g(&W%c&g)\n"),
			ch->exp, ch->pcdata->mkills, xIS_SET (ch->act,
							      PLR_AUTOLOOT) ?
			'X' : ' ');
  else
    pager_printf_color (ch,
			_("&GEXP  : &P%-9d        &GMana: &B%-5d &Gof &B%5d   &GMKills:  &W%5d    &GAutoLoot&g(&W%c&g)\n"),
			ch->exp, ch->mana, ch->max_mana, ch->pcdata->mkills,
			xIS_SET (ch->act, PLR_AUTOLOOT) ? 'X' : ' ');

#ifdef ENABLE_GOLD_SILVER_COPPER
	pager_printf_color(ch, "&GMove: &O%-5d &Gof &O%5d   &GMdeaths: &W%5d    &GAutoSac (&W%c&g)\n\r",
	ch->move, ch->max_move, ch->pcdata->mdeaths, xIS_SET(ch->act, PLR_AUTOSAC) ? 'X' : ' ');
	pager_printf_color(ch,"&GGold: &Y%s ",num_punct(ch->gold));
	pager_printf_color(ch,"&GSilver: &Y%s	",num_punct(ch->silver));
	pager_printf_color(ch,"&GCopper: &Y%s\n\r",num_punct(ch->copper));
#else
  pager_printf_color (ch,
		      _("&GGOLD : &Y%-13s    &GMove: &O%-5d &Gof &O%5d   &GMdeaths: &W%5d    &GAutoSac &g(&W%c&g)\n"),
		      num_punct (ch->gold), ch->move, ch->max_move,
		      ch->pcdata->mdeaths, xIS_SET (ch->act,
						    PLR_AUTOSAC) ? 'X' : ' ');
#endif

  if (!IS_NPC (ch) && ch->pcdata->condition[COND_DRUNK] > 10)
    send_to_pager (_("You are drunk.\n"), ch);
  if (!IS_NPC (ch) && ch->pcdata->condition[COND_THIRST] == 0)
    send_to_pager (_("You are in danger of dehydrating.\n"), ch);
  if (!IS_NPC (ch) && ch->pcdata->condition[COND_FULL] == 0)
    send_to_pager (_("You are starving to death.\n"), ch);
  if (ch->position != POS_SLEEPING)
    switch (ch->mental_state / 10)
      {
      default:
	send_to_pager ("You're completely messed up!\n\r", ch);
	break;
      case -10:
	send_to_pager ("You're barely conscious.\n\r", ch);
	break;
      case -9:
	send_to_pager ("You can barely keep your eyes open.\n\r", ch);
	break;
      case -8:
	send_to_pager ("You're extremely drowsy.\n\r", ch);
	break;
      case -7:
	send_to_pager ("You feel very unmotivated.\n\r", ch);
	break;
      case -6:
	send_to_pager ("You feel sedated.\n\r", ch);
	break;
      case -5:
	send_to_pager ("You feel sleepy.\n\r", ch);
	break;
      case -4:
	send_to_pager ("You feel tired.\n\r", ch);
	break;
      case -3:
	send_to_pager ("You could use a rest.\n\r", ch);
	break;
      case -2:
	send_to_pager ("You feel a little under the weather.\n\r", ch);
	break;
      case -1:
	send_to_pager ("You feel fine.\n\r", ch);
	break;
      case 0:
	send_to_pager ("You feel great.\n\r", ch);
	break;
      case 1:
	send_to_pager ("You feel energetic.\n\r", ch);
	break;
      case 2:
	send_to_pager ("Your mind is racing.\n\r", ch);
	break;
      case 3:
	send_to_pager ("You can't think straight.\n\r", ch);
	break;
      case 4:
	send_to_pager ("Your mind is going 100 miles an hour.\n\r", ch);
	break;
      case 5:
	send_to_pager ("You're high as a kite.\n\r", ch);
	break;
      case 6:
	send_to_pager ("Your mind and body are slipping apart.\n\r", ch);
	break;
      case 7:
	send_to_pager ("Reality is slipping away.\n\r", ch);
	break;
      case 8:
	send_to_pager ("You have no idea what is real, and what is not.\n\r",
		       ch);
	break;
      case 9:
	send_to_pager ("You feel immortal.\n\r", ch);
	break;
      case 10:
	send_to_pager ("You are a Supreme Entity.\n\r", ch);
	break;
      }
  else if (ch->mental_state > 45)
    send_to_pager ("Your sleep is filled with strange and vivid dreams.\n\r",
		   ch);
  else if (ch->mental_state > 25)
    send_to_pager ("Your sleep is uneasy.\n\r", ch);
  else if (ch->mental_state < -35)
    send_to_pager ("You are deep in a much needed sleep.\n\r", ch);
  else if (ch->mental_state < -25)
    send_to_pager ("You are in deep slumber.\n\r", ch);
/*  send_to_pager("Languages: ", ch );
    for ( iLang = 0; lang_array[iLang] != LANG_UNKNOWN; iLang++ )
	if ( knows_language( ch, lang_array[iLang], ch )
	||  (IS_NPC(ch) && ch->speaks == 0) )
	{
	    if ( lang_array[iLang] & ch->speaking
	    ||  (IS_NPC(ch) && !ch->speaking) )
		set_pager_color( AT_RED, ch );
	    send_to_pager( lang_names[iLang], ch );
	    send_to_pager( " ", ch );
	    set_pager_color( AT_SCORE, ch );
	}
    send_to_pager( "\n\r", ch );
*/
  if (ch->pcdata->bestowments && ch->pcdata->bestowments[0] != '\0')
    pager_printf_color (ch,
			_("&GYou are bestowed with the command(s): &Y%s\n"),
			ch->pcdata->bestowments);

  if (ch->morph && ch->morph->morph)
    {
      send_to_pager_color
	("&g----------------------------------------------------------------------------&G\n\r",
	 ch);
      if (IS_IMMORTAL (ch))
	pager_printf (ch, _("Morphed as (%d) %s with a timer of %d.\n"),
		      ch->morph->morph->vnum, ch->morph->morph->short_desc,
		      ch->morph->timer);
      else
	pager_printf (ch, _("You are morphed into a %s.\n"),
		      ch->morph->morph->short_desc);
      send_to_pager_color
	("&g----------------------------------------------------------------------------&G\n\r",
	 ch);
    }
  if (CAN_PKILL (ch))
    {
      send_to_pager_color
	("&g----------------------------------------------------------------------------&G\n\r",
	 ch);
      pager_printf_color (ch,
			  _("&GPKILL DATA:  Pkills (&W%d&G)     Illegal Pkills (&W%d&G)     Pdeaths (&W%d&G)\n"),
			  ch->pcdata->pkills, ch->pcdata->illegal_pk,
			  ch->pcdata->pdeaths);
    }
  if (ch->pcdata->clan && ch->pcdata->clan->clan_type != CLAN_ORDER
      && ch->pcdata->clan->clan_type != CLAN_GUILD)
    {
/*
	send_to_pager_color( "&W----------------------------------------------------------------------------&G\n\r", ch);
*/
      pager_printf_color (ch,
			  _("&GCLAN STATS:  &W%-14.14s  &GClan AvPkills : &W%-5d  &GClan NonAvpkills : &W%-5d\n"),
			  ch->pcdata->clan->name, ch->pcdata->clan->pkills[5],
			  (ch->pcdata->clan->pkills[0] +
			   ch->pcdata->clan->pkills[1] +
			   ch->pcdata->clan->pkills[2] +
			   ch->pcdata->clan->pkills[3] +
			   ch->pcdata->clan->pkills[4]));
      pager_printf_color (ch,
			  _("&G                             Clan AvPdeaths: &W%-5d  &GClan NonAvpdeaths: &W%-5d\n"),
			  ch->pcdata->clan->pdeaths[5],
			  (ch->pcdata->clan->pdeaths[0] +
			   ch->pcdata->clan->pdeaths[1] +
			   ch->pcdata->clan->pdeaths[2] +
			   ch->pcdata->clan->pdeaths[3] +
			   ch->pcdata->clan->pdeaths[4]));
    }
  if (ch->pcdata->deity)
    {
      send_to_pager_color
	("&g----------------------------------------------------------------------------&G\n\r",
	 ch);
      if (ch->pcdata->favor > 2250)
	sprintf (buf, "loved");
      else if (ch->pcdata->favor > 2000)
	sprintf (buf, "cherished");
      else if (ch->pcdata->favor > 1750)
	sprintf (buf, "honored");
      else if (ch->pcdata->favor > 1500)
	sprintf (buf, "praised");
      else if (ch->pcdata->favor > 1250)
	sprintf (buf, "favored");
      else if (ch->pcdata->favor > 1000)
	sprintf (buf, "respected");
      else if (ch->pcdata->favor > 750)
	sprintf (buf, "liked");
      else if (ch->pcdata->favor > 250)
	sprintf (buf, "tolerated");
      else if (ch->pcdata->favor > -250)
	sprintf (buf, "ignored");
      else if (ch->pcdata->favor > -750)
	sprintf (buf, "shunned");
      else if (ch->pcdata->favor > -1000)
	sprintf (buf, "disliked");
      else if (ch->pcdata->favor > -1250)
	sprintf (buf, "dishonored");
      else if (ch->pcdata->favor > -1500)
	sprintf (buf, "disowned");
      else if (ch->pcdata->favor > -1750)
	sprintf (buf, "abandoned");
      else if (ch->pcdata->favor > -2000)
	sprintf (buf, "despised");
      else if (ch->pcdata->favor > -2250)
	sprintf (buf, "hated");
      else
	sprintf (buf, "damned");
      pager_printf_color (ch, _("&GDeity:  &W%-20s &GFavor:  &W%s&G\n"),
			  ch->pcdata->deity->name, buf);
    }
  if (ch->pcdata->clan && ch->pcdata->clan->clan_type == CLAN_ORDER)
    {
      send_to_pager_color
	("&g----------------------------------------------------------------------------&G\n\r",
	 ch);
      pager_printf_color (ch,
			  _("&GOrder:  &W%-20s  &GOrder Mkills:  &W%-6d   &GOrder MDeaths:  &W%-6d\n"),
			  ch->pcdata->clan->name, ch->pcdata->clan->mkills,
			  ch->pcdata->clan->mdeaths);
    }
  if (ch->pcdata->clan && ch->pcdata->clan->clan_type == CLAN_GUILD)
    {
      send_to_pager_color
	("&g----------------------------------------------------------------------------&G\n\r",
	 ch);
      pager_printf_color (ch,
			  _("&GGuild:  &W%-20s  &GGuild Mkills:  &W%-6d   &GGuild MDeaths:  &W%-6d\n"),
			  ch->pcdata->clan->name, ch->pcdata->clan->mkills,
			  ch->pcdata->clan->mdeaths);
    }
  argument = one_argument (argument, arg);
  if (ch->first_affect && !str_cmp (arg, "affects"))
    {
      int i;
      SKILLTYPE *sktmp;

      i = 0;
      send_to_pager_color
	("&g----------------------------------------------------------------------------&G\n\r",
	 ch);
      send_to_pager_color ("AFFECT DATA:                            ", ch);
      for (paf = ch->first_affect; paf; paf = paf->next)
	{
	  if ((sktmp = get_skilltype (paf->type)) == NULL)
	    continue;
	  if (ch->level < 20)
	    {
	      pager_printf_color (ch, "&G[&W%-34.34s&G]    ", sktmp->name);
	      if (i == 0)
		i = 2;
	      if ((++i % 3) == 0)
		send_to_pager ("\n\r", ch);
	    }
	  if (ch->level >= 20)
	    {
	      if (paf->modifier == 0)
		pager_printf_color (ch, "&G[&W%-24.24s;%5d &Grds]    ",
				    sktmp->name, paf->duration);
	      else if (paf->modifier > 999)
		pager_printf_color (ch, "&G[&W%-15.15s; %7.7s;%5d &Grds]    ",
				    sktmp->name,
				    tiny_affect_loc_name (paf->location),
				    paf->duration);
	      else
		pager_printf_color (ch,
				    "&G[&W%-11.11s;%+-3.3d %7.7s;%5d &Grds]    ",
				    sktmp->name, paf->modifier,
				    tiny_affect_loc_name (paf->location),
				    paf->duration);
	      if (i == 0)
		i = 1;
	      if ((++i % 2) == 0)
		send_to_pager ("\n\r", ch);
	    }
	}
    }
  send_to_pager ("\n\r", ch);
  return;
}
#endif

/*
 * Return ascii name of an affect location.
 */
char *
tiny_affect_loc_name (int location)
{
  switch (location)
    {
    case APPLY_NONE:
      return "NIL";
    case APPLY_STR:
      return " STR  ";
    case APPLY_DEX:
      return " DEX  ";
    case APPLY_INT:
      return " INT  ";
    case APPLY_WIS:
      return " WIS  ";
    case APPLY_CON:
      return " CON  ";
    case APPLY_CHA:
      return " CHA  ";
    case APPLY_LCK:
      return " LCK  ";
    case APPLY_SEX:
      return " SEX  ";
    case APPLY_CLASS:
      return " CLASS";
    case APPLY_LEVEL:
      return " LVL  ";
    case APPLY_AGE:
      return " AGE  ";
    case APPLY_MANA:
      return " MANA ";
    case APPLY_HIT:
      return " HV   ";
    case APPLY_MOVE:
      return " MOVE ";
    case APPLY_GOLD:
      return " GOLD ";
    case APPLY_EXP:
      return " EXP  ";
    case APPLY_AC:
      return " AC   ";
    case APPLY_HITROLL:
      return " HITRL";
    case APPLY_DAMROLL:
      return " DAMRL";
    case APPLY_SAVING_POISON:
      return "SV POI";
    case APPLY_SAVING_ROD:
      return "SV ROD";
    case APPLY_SAVING_PARA:
      return "SV PARA";
    case APPLY_SAVING_BREATH:
      return "SV BRTH";
    case APPLY_SAVING_SPELL:
      return "SV SPLL";
    case APPLY_HEIGHT:
      return "HEIGHT";
    case APPLY_WEIGHT:
      return "WEIGHT";
    case APPLY_AFFECT:
      return "AFF BY";
    case APPLY_RESISTANT:
      return "RESIST";
    case APPLY_IMMUNE:
      return "IMMUNE";
    case APPLY_SUSCEPTIBLE:
      return "SUSCEPT";
    case APPLY_WEAPONSPELL:
      return " WEAPON";
    case APPLY_BACKSTAB:
      return "BACKSTB";
    case APPLY_PICK:
      return " PICK  ";
    case APPLY_TRACK:
      return " TRACK ";
    case APPLY_STEAL:
      return " STEAL ";
    case APPLY_SNEAK:
      return " SNEAK ";
    case APPLY_HIDE:
      return " HIDE  ";
    case APPLY_PALM:
      return " PALM  ";
    case APPLY_DETRAP:
      return " DETRAP";
    case APPLY_DODGE:
      return " DODGE ";
    case APPLY_PEEK:
      return " PEEK  ";
    case APPLY_SCAN:
      return " SCAN  ";
    case APPLY_GOUGE:
      return " GOUGE ";
    case APPLY_SEARCH:
      return " SEARCH";
    case APPLY_MOUNT:
      return " MOUNT ";
    case APPLY_DISARM:
      return " DISARM";
    case APPLY_KICK:
      return " KICK  ";
    case APPLY_PARRY:
      return " PARRY ";
    case APPLY_BASH:
      return " BASH  ";
    case APPLY_STUN:
      return " STUN  ";
    case APPLY_PUNCH:
      return " PUNCH ";
    case APPLY_CLIMB:
      return " CLIMB ";
    case APPLY_GRIP:
      return " GRIP  ";
    case APPLY_SCRIBE:
      return " SCRIBE";
    case APPLY_BREW:
      return " BREW  ";
    case APPLY_WEARSPELL:
      return " WEAR  ";
    case APPLY_REMOVESPELL:
      return " REMOVE";
    case APPLY_EMOTION:
      return "EMOTION";
    case APPLY_MENTALSTATE:
      return " MENTAL";
    case APPLY_STRIPSN:
      return " DISPEL";
    case APPLY_REMOVE:
      return " REMOVE";
    case APPLY_DIG:
      return " DIG   ";
    case APPLY_FULL:
      return " HUNGER";
    case APPLY_THIRST:
      return " THIRST";
    case APPLY_DRUNK:
      return " DRUNK ";
    case APPLY_BLOOD:
      return " BLOOD ";
    case APPLY_COOK:
      return " COOK  ";
    case APPLY_RECURRINGSPELL:
      return " RECURR";
    case APPLY_CONTAGIOUS:
      return "CONTGUS";
    case APPLY_ODOR:
      return " ODOR  ";
    case APPLY_ROOMFLAG:
      return " RMFLG ";
    case APPLY_SECTORTYPE:
      return " SECTOR";
    case APPLY_ROOMLIGHT:
      return " LIGHT ";
    case APPLY_TELEVNUM:
      return " TELEVN";
    case APPLY_TELEDELAY:
      return " TELEDY";
#ifdef ENABLE_GOLD_SILVER_COPPER
		case APPLY_SILVER:
      return " SILVER";
		case APPLY_COPPER:
      return " COPPER";
#endif
    };

  bug (_("Affect_location_name: unknown location %d."), location);
  return "Unknown";
}

char *
get_class (CHAR_DATA * ch)
{
  if (IS_NPC (ch) && ch->class < MAX_NPC_CLASS && ch->class >= 0)
    return (npc_class[ch->class]);
  else if (!IS_NPC (ch) && ch->class < MAX_PC_CLASS && ch->class >= 0)
    return class_table[ch->class]->who_name;
  return (_("Unknown"));
}


char *
get_race (CHAR_DATA * ch)
{
  if (ch->race < MAX_PC_RACE && ch->race >= 0)
    return (race_table[ch->race]->race_name);
  if (ch->race < MAX_NPC_RACE && ch->race >= 0)
    return (npc_race[ch->race]);
  return (_("Unknown"));
}

void
do_oldscore (CHAR_DATA * ch, char *argument)
{
  AFFECT_DATA *paf;
  SKILLTYPE *skill;

  set_pager_color (AT_SCORE, ch);
  pager_printf (ch,
		_("You are %s%s.\nLevel %d, %d years old (%d hours).\n"),
		ch->name,
		IS_NPC (ch) ? "" : ch->pcdata->title,
		ch->level, get_age (ch), (get_age (ch) - 17) * 2);

  if (get_trust (ch) != ch->level)
    pager_printf (ch, _("You are trusted at level %d.\n"), get_trust (ch));

  if (IS_NPC (ch) && xIS_SET (ch->act, ACT_MOBINVIS))
    pager_printf (ch, _("You are mobinvis at level %d.\n"), ch->mobinvis);

  if (!IS_NPC (ch) && IS_VAMPIRE (ch))
  if (!IS_NPC (ch) && IS_DEMON (ch))
    pager_printf (ch,
		  _("You have %d/%d hit, %d/%d blood level, %d/%d moves, %d practices.\n"),
		  ch->hit, ch->max_hit,
		  ch->pcdata->condition[COND_BLOODTHIRST], 10 + ch->level,
		  ch->move, ch->max_move, ch->practice);
  else
    pager_printf (ch,
		  _("You have %d/%d hit, %d/%d mana, %d/%d moves, %d practices.\n"),
		  ch->hit, ch->max_hit,
		  ch->mana, ch->max_mana,
		  ch->move, ch->max_move, ch->practice);

  pager_printf (ch,
		_("You are carrying %d/%d items with weight %d/%d kg.\n"),
		ch->carry_number, can_carry_n (ch),
		ch->carry_weight, can_carry_w (ch));

  pager_printf (ch,
		_("Str: %d  Int: %d  Wis: %d  Dex: %d  Con: %d  Cha: %d  Lck: %d.\n"),
		get_curr_str (ch),
		get_curr_int (ch),
		get_curr_wis (ch),
		get_curr_dex (ch),
		get_curr_con (ch), get_curr_cha (ch), get_curr_lck (ch));

  /* Can no longer have 2 occurences of num_punct on the same line -Shaddai */
  pager_printf (ch, _("You have scored %s exp, and have "), num_punct (ch->exp));
#ifdef ENABLE_GOLD_SILVER_COPPER
	pager_printf (ch, _("%s gold, "), num_punct(ch->gold) );
	pager_printf (ch, _("%s silver, and "), num_punct(ch->silver));
	pager_printf (ch, _("%s copper coins.\n"), num_punct(ch->copper));
#else
  pager_printf (ch, _("%s gold coins.\n"), num_punct (ch->gold));
#endif

  if (!IS_NPC (ch))
    pager_printf (ch,
		  _("You have achieved %d glory during your life, and currently have %d.\n"),
		  ch->pcdata->quest_accum, ch->pcdata->quest_curr);

  pager_printf (ch,
		_("Autoexit: %s   Autoloot: %s   Autosac: %s   Autogold: %s\n"),
		(!IS_NPC (ch)
		 && xIS_SET (ch->act, PLR_AUTOEXIT)) ? _("yes") : _("no"),
		(!IS_NPC (ch)
		 && xIS_SET (ch->act, PLR_AUTOLOOT)) ? _("yes") : _("no"),
		(!IS_NPC (ch)
		 && xIS_SET (ch->act, PLR_AUTOSAC)) ? _("yes") : _("no"),
		(!IS_NPC (ch)
		 && xIS_SET (ch->act, PLR_AUTOGOLD)) ? _("yes") : _("no"));

  pager_printf (ch, _("Wimpy set to %d hit points.\n"), ch->wimpy);

  if (!IS_NPC (ch))
    {
      if (ch->pcdata->condition[COND_DRUNK] > 10)
	send_to_pager ("You are drunk.\n\r", ch);
      if (ch->pcdata->condition[COND_THIRST] == 0)
	send_to_pager ("You are thirsty.\n\r", ch);
      if (ch->pcdata->condition[COND_FULL] == 0)
	send_to_pager ("You are hungry.\n\r", ch);
    }

  switch (ch->mental_state / 10)
    {
    default:
      send_to_pager ("You're completely messed up!\n\r", ch);
      break;
    case -10:
      send_to_pager ("You're barely conscious.\n\r", ch);
      break;
    case -9:
      send_to_pager ("You can barely keep your eyes open.\n\r", ch);
      break;
    case -8:
      send_to_pager ("You're extremely drowsy.\n\r", ch);
      break;
    case -7:
      send_to_pager ("You feel very unmotivated.\n\r", ch);
      break;
    case -6:
      send_to_pager ("You feel sedated.\n\r", ch);
      break;
    case -5:
      send_to_pager ("You feel sleepy.\n\r", ch);
      break;
    case -4:
      send_to_pager ("You feel tired.\n\r", ch);
      break;
    case -3:
      send_to_pager ("You could use a rest.\n\r", ch);
      break;
    case -2:
      send_to_pager ("You feel a little under the weather.\n\r", ch);
      break;
    case -1:
      send_to_pager ("You feel fine.\n\r", ch);
      break;
    case 0:
      send_to_pager ("You feel great.\n\r", ch);
      break;
    case 1:
      send_to_pager ("You feel energetic.\n\r", ch);
      break;
    case 2:
      send_to_pager ("Your mind is racing.\n\r", ch);
      break;
    case 3:
      send_to_pager ("You can't think straight.\n\r", ch);
      break;
    case 4:
      send_to_pager ("Your mind is going 100 miles an hour.\n\r", ch);
      break;
    case 5:
      send_to_pager ("You're high as a kite.\n\r", ch);
      break;
    case 6:
      send_to_pager ("Your mind and body are slipping appart.\n\r", ch);
      break;
    case 7:
      send_to_pager ("Reality is slipping away.\n\r", ch);
      break;
    case 8:
      send_to_pager ("You have no idea what is real, and what is not.\n\r",
		     ch);
      break;
    case 9:
      send_to_pager ("You feel immortal.\n\r", ch);
      break;
    case 10:
      send_to_pager ("You are a Supreme Entity.\n\r", ch);
      break;
    }

  switch (ch->position)
    {
    case POS_DEAD:
      send_to_pager (_("You are DEAD!!\n"), ch);
      break;
    case POS_MORTAL:
      send_to_pager (_("You are mortally wounded.\n"), ch);
      break;
    case POS_INCAP:
      send_to_pager (_("You are incapacitated.\n"), ch);
      break;
    case POS_STUNNED:
      send_to_pager (_("You are stunned.\n"), ch);
      break;
    case POS_SLEEPING:
      send_to_pager (_("You are sleeping.\n"), ch);
      break;
    case POS_RESTING:
      send_to_pager (_("You are resting.\n"), ch);
      break;
    case POS_STANDING:
      send_to_pager (_("You are standing.\n"), ch);
      break;
    case POS_FIGHTING:
      send_to_pager (_("You are fighting.\n"), ch);
      break;
    case POS_MOUNTED:
      send_to_pager (_("Mounted.\n"), ch);
      break;
    case POS_SHOVE:
      send_to_pager (_("Being shoved.\n"), ch);
      break;
    case POS_DRAG:
      send_to_pager (_("Being dragged.\n"), ch);
      break;
    }

  if (ch->level >= 25)
    pager_printf (ch, "AC: %d.  ", GET_AC (ch));

  send_to_pager (_("You are "), ch);
  if (GET_AC (ch) >= 101)
    send_to_pager ("WORSE than naked!\n\r", ch);
  else if (GET_AC (ch) >= 80)
    send_to_pager ("naked.\n\r", ch);
  else if (GET_AC (ch) >= 60)
    send_to_pager ("wearing clothes.\n\r", ch);
  else if (GET_AC (ch) >= 40)
    send_to_pager ("slightly armored.\n\r", ch);
  else if (GET_AC (ch) >= 20)
    send_to_pager ("somewhat armored.\n\r", ch);
  else if (GET_AC (ch) >= 0)
    send_to_pager ("armored.\n\r", ch);
  else if (GET_AC (ch) >= -20)
    send_to_pager ("well armored.\n\r", ch);
  else if (GET_AC (ch) >= -40)
    send_to_pager ("strongly armored.\n\r", ch);
  else if (GET_AC (ch) >= -60)
    send_to_pager ("heavily armored.\n\r", ch);
  else if (GET_AC (ch) >= -80)
    send_to_pager ("superbly armored.\n\r", ch);
  else if (GET_AC (ch) >= -100)
    send_to_pager ("divinely armored.\n\r", ch);
  else
    send_to_pager ("invincible!\n\r", ch);

  if (ch->level >= 15 || IS_PKILL (ch))
    pager_printf (ch, "Hitroll: %d  Damroll: %d.\n\r",
		  GET_HITROLL (ch), GET_DAMROLL (ch));

  if (ch->level >= 10)
    pager_printf (ch, "Alignment: %d.  ", ch->alignment);

  send_to_pager (_("You are "), ch);
  if (ch->alignment > 900)
    send_to_pager ("angelic.\n\r", ch);
  else if (ch->alignment > 700)
    send_to_pager ("saintly.\n\r", ch);
  else if (ch->alignment > 350)
    send_to_pager ("good.\n\r", ch);
  else if (ch->alignment > 100)
    send_to_pager ("kind.\n\r", ch);
  else if (ch->alignment > -100)
    send_to_pager ("neutral.\n\r", ch);
  else if (ch->alignment > -350)
    send_to_pager ("mean.\n\r", ch);
  else if (ch->alignment > -700)
    send_to_pager ("evil.\n\r", ch);
  else if (ch->alignment > -900)
    send_to_pager ("demonic.\n\r", ch);
  else
    send_to_pager ("satanic.\n\r", ch);
#ifdef PLRSHOWSTANCE
  pager_printf (ch, _("Stance:    %s \n"), get_stance_name (ch->stance));
#endif

  if (ch->first_affect)
    {
      send_to_pager (_("You are affected by:\n"), ch);
      for (paf = ch->first_affect; paf; paf = paf->next)
	if ((skill = get_skilltype (paf->type)) != NULL)
	  {
	    pager_printf (ch, _("Spell: '%s'"), skill->name);

	    if (ch->level >= 20)
	      pager_printf (ch,
			    _(" modifies %s by %d for %d rounds"),
			    affect_loc_name (paf->location),
			    paf->modifier, paf->duration);

	    send_to_pager (".\n\r", ch);
	  }
    }

  if (!IS_NPC (ch) && IS_IMMORTAL (ch))
    {
      pager_printf (ch, _("\nWizInvis level: %d   WizInvis is %s\n"),
		    ch->pcdata->wizinvis,
		    xIS_SET (ch->act, PLR_WIZINVIS) ? "ON" : "OFF");
      if (ch->pcdata->r_range_lo && ch->pcdata->r_range_hi)
	pager_printf (ch, "Room Range: %d - %d\n\r", ch->pcdata->r_range_lo,
		      ch->pcdata->r_range_hi);
      if (ch->pcdata->o_range_lo && ch->pcdata->o_range_hi)
	pager_printf (ch, "Obj Range : %d - %d\n\r", ch->pcdata->o_range_lo,
		      ch->pcdata->o_range_hi);
      if (ch->pcdata->m_range_lo && ch->pcdata->m_range_hi)
	pager_printf (ch, "Mob Range : %d - %d\n\r", ch->pcdata->m_range_lo,
		      ch->pcdata->m_range_hi);
    }

  return;
}

/*								-Thoric
 * Display your current exp, level, and surrounding level exp requirements
 */
void
do_level (CHAR_DATA * ch, char *argument)
{
  char buf[MAX_STRING_LENGTH];
  char buf2[MAX_STRING_LENGTH];
  int x, lowlvl, hilvl;

  if (ch->level == 1)
    lowlvl = 1;
  else
    lowlvl = UMAX (2, ch->level - 5);
  hilvl = URANGE (ch->level, ch->level + 5, MAX_LEVEL);
  set_char_color (AT_GREEN, ch);
  ch_printf_color (ch,
		   _("\n&GExperience required, levels &W%d &Gto &W%d&G:\n&g______________________________________________\n\n"),
		   lowlvl, hilvl);
  sprintf (buf, _("&W exp  (Current: %12s)"), num_punct (ch->exp));
  sprintf (buf2, _("&W exp  (Needed:  &G%12s&W)"),
	   num_punct (exp_level (ch, ch->level + 1) - ch->exp));
  for (x = lowlvl; x <= hilvl; x++)
    ch_printf_color (ch, "&G (&W%2d&G) &W%12s%s\n\r", x,
		     num_punct (exp_level (ch, x)),
		     (x == ch->level) ? buf : (x ==
					       ch->level +
					       1) ? buf2 : " exp");
  send_to_char_color ("&g______________________________________________\n\r",
		      ch);
}

/* 1997, Blodkai */
void
do_remains (CHAR_DATA * ch, char *argument)
{
  char buf[MAX_STRING_LENGTH];
  OBJ_DATA *obj;
  bool found = FALSE;

  if (IS_NPC (ch))
    return;
  set_char_color (AT_MAGIC, ch);
  if (!ch->pcdata->deity)
    {
      send_to_pager
	(_("You have no deity from which to seek such assistance...\n"), ch);
      return;
    }
  if (ch->pcdata->favor < ch->level * 2)
    {
      send_to_pager ("Your favor is insufficient for such assistance...\n\r",
		     ch);
      return;
    }
  pager_printf (ch, "%s appears in a vision, revealing that your remains... ",
		ch->pcdata->deity->name);
  sprintf (buf, _("the corpse of %s"), ch->name);
  for (obj = first_object; obj; obj = obj->next)
    {
      if (obj->in_room && !str_cmp (buf, obj->short_descr)
	  && (obj->pIndexData->vnum == 11))
	{
	  found = TRUE;
	  pager_printf (ch, "\n\r  - at %s will endure for %d ticks",
			obj->in_room->name, obj->timer);
	}
    }
  if (!found)
    send_to_pager (" no longer exist.\n\r", ch);
  else
    {
      send_to_pager ("\n\r", ch);
      ch->pcdata->favor -= ch->level * 2;
    }
  return;
}

/* Affects-at-a-glance, Blodkai */
void
do_affected (CHAR_DATA * ch, char *argument)
{
  char arg[MAX_INPUT_LENGTH];
  AFFECT_DATA *paf;
  SKILLTYPE *skill;

  if (IS_NPC (ch))
    return;

  set_char_color (AT_GREEN, ch);

  argument = one_argument (argument, arg);
  if (!str_cmp (arg, _("by")))
    {
      send_to_char_color ("\n\r&BImbued with:\n\r", ch);
      ch_printf_color (ch, "&C%s\n\r",
		       !xIS_EMPTY (ch->
				   affected_by) ?
		       affect_bit_name (&ch->affected_by) : "nothing");
      if (ch->level >= 20)
	{

	  send_to_char ("\n\r", ch);
	  if (ch->resistant > 0 || ch->stance_resistant > 0)
	    {
	      send_to_char_color ("&BResistances:  ", ch);
#ifdef PLRSHOWSTANCE
	      ch_printf_color (ch, "&C%s\n\r",
			       flag_string (ch->resistant
					    || ch->stance_resistant,
					    ris_flags));
#endif
	      ch_printf_color (ch, "&C%s\n\r",
			       flag_string (ch->resistant, ris_flags));
	    }
	  if (ch->immune > 0 || ch->stance_immune > 0)
	    {
	      send_to_char_color ("&BImmunities:   ", ch);
#ifdef PLRSHOWSTANCE
	      ch_printf_color (ch, "&C%s\n\r",
			       flag_string (ch->immune
					    || ch->stance_immune, ris_flags));
#endif
	      ch_printf_color (ch, "&C%s\n\r",
			       flag_string (ch->immune, ris_flags));
	    }
	  if (ch->susceptible > 0 || ch->stance_susceptible > 0)
	    {
	      send_to_char_color ("&BSuscepts:     ", ch);
#ifdef PLRSHOWSTANCE
	      ch_printf_color (ch, "&C%s\n\r",
			       flag_string (ch->susceptible
					    || ch->stance_susceptible,
					    ris_flags));
#endif
	      ch_printf_color (ch, "&C%s\n\r",
			       flag_string (ch->susceptible, ris_flags));
	    }
	}
      return;
    }

  if (!ch->first_affect)
    {
      send_to_char_color ("\n\r&CNo cantrip or skill affects you.\n\r", ch);
    }
  else
    {
      send_to_char ("\n\r", ch);
      for (paf = ch->first_affect; paf; paf = paf->next)
	if ((skill = get_skilltype (paf->type)) != NULL)
	  {
	    set_char_color (AT_BLUE, ch);
	    send_to_char ("Affected:  ", ch);
	    set_char_color (AT_SCORE, ch);
	    if (ch->level >= 20 || IS_PKILL (ch))
	      {
		if (paf->duration < 25)
		  set_char_color (AT_WHITE, ch);
		ch_printf (ch, "(%5d)   ", paf->duration);
	      }
	    ch_printf (ch, "%-18s\n\r", skill->name);
	  }
    }
  return;
}

/*
 * Support for GOD+ to view inventory of others	-Thoric
 */
void
do_inventory (CHAR_DATA * ch, char *argument)
{
  CHAR_DATA *victim = ch;
  bool invtarget = FALSE;

  if (get_trust (ch) >= LEVEL_GOD && argument[0] != '\0')
    {
      if ((victim = get_char_world (ch, argument)) == NULL)
	{
	  send_to_char (_("They're not here.\n"), ch);
	  return;
	}
      invtarget = TRUE;
    }

  ch_printf_color (ch, _("&R%s %s carrying:\n"),
		   invtarget ? capitalize (victim->name) : _("You"),
		   invtarget ? _("is") : _("are"));
  show_list_to_char (victim->first_carrying, ch, TRUE, TRUE);

}

void
do_condition (CHAR_DATA * ch, char *argument)
{
  CHAR_DATA *victim = ch;
  OBJ_DATA *obj;
  int iWear;
  bool found;
  int cond;

  if (get_trust (ch) > LEVEL_GOD && argument[0] != '\0')
    {
      if ((victim = get_char_world (ch, argument)) == NULL)
	{
	  send_to_char (_("They're not here.\n"), ch);
	  return;
	}
      act (AT_RED, _("$n is using:"), victim, NULL, ch, TO_VICT);
    }
  else
    {
      set_char_color (AT_RED, ch);
      send_to_char (_("You are using:\n"), ch);
    }
  found = FALSE;
  set_char_color (AT_OBJECT, ch);
  for (iWear = 0; iWear < MAX_WEAR; iWear++)
    {
      for (obj = victim->first_carrying; obj; obj = obj->next_content)
	if (obj->wear_loc == iWear)
	  {
	    if ((!IS_NPC (ch)) && (ch->race > 0) && (ch->race < MAX_PC_RACE))
	      send_to_char (race_table[ch->race]->where_name[iWear], ch);
	    else
	      send_to_char (where_name[iWear], ch);



	    if (can_see_obj (ch, obj))
	      {
		switch (obj->item_type)
		  {
		  case ITEM_ARMOR:
		    cond = (int) ((10 * obj->value[0] / obj->value[1]));
		    break;
		  case ITEM_WEAPON:
		    cond = (int) ((10 * obj->value[0] / 12));
		    break;
		  default:
		    cond = -1;
		    break;
		  }
/*
                    send_to_char_color("&g<&Y",ch);
*/
		if (cond >= 0)
		  {
		    if (cond > 8)
		      ch_printf_color (ch, "&w[&G+&w]&G ");
		    else if (cond > 5)
		      ch_printf_color (ch, "&w[&Y-&w]&G ");
		    else
		      ch_printf_color (ch, "&w[&R!&w]&G ");
		  }
		else
		  send_to_char ("    ", ch);
/*
                    send_to_char_color("&g>&G  ",ch);
*/
		send_to_char (format_obj_to_char (obj, ch, TRUE), ch);
		send_to_char ("\n\r", ch);
	      }
	    else
	      send_to_char (_("something.\n"), ch);
	    found = TRUE;
	  }
    }

  if (!found)
    send_to_char (_("Nothing.\n"), ch);

  return;
}


void
do_equipment (CHAR_DATA * ch, char *argument)
{
  CHAR_DATA *victim = ch;
  OBJ_DATA *obj;
  int iWear;
  bool found;

  if (get_trust (ch) > LEVEL_GOD && argument[0] != '\0')
    {
      if ((victim = get_char_world (ch, argument)) == NULL)
	{
	  send_to_char (_("They're not here.\n"), ch);
	  return;
	}
      act (AT_RED, _("$n is using:"), victim, NULL, ch, TO_VICT);
    }
  else
    {
      set_char_color (AT_RED, ch);
      send_to_char (_("You are using:\n"), ch);
    }
  found = FALSE;
  set_char_color (AT_OBJECT, ch);
  for (iWear = 0; iWear < MAX_WEAR; iWear++)
    {
      for (obj = victim->first_carrying; obj; obj = obj->next_content)
	if (obj->wear_loc == iWear)
	  {
	    if ((!IS_NPC (ch)) && (ch->race > 0) && (ch->race < MAX_PC_RACE))
	      send_to_char (race_table[ch->race]->where_name[iWear], ch);
	    else
	      send_to_char (where_name[iWear], ch);

	    if (can_see_obj (ch, obj))
	      {
		send_to_char (format_obj_to_char (obj, ch, TRUE), ch);
		send_to_char ("\n\r", ch);
	      }
	    else
	      send_to_char (_("something.\n"), ch);
	    found = TRUE;
	  }
    }

  if (!found)
    send_to_char (_("Nothing.\n"), ch);

  send_to_char_color (_("&g(type 'garb' for a list of all wear locations)\n"),
		      ch);
  return;
}


void
do_equipment_full (CHAR_DATA * ch, char *argument)
{
  OBJ_DATA *obj;
  int iWear;
  bool ankler = FALSE, anklel = FALSE;
  bool candual, hasloc;
  candual = FALSE;
  set_char_color (AT_RED, ch);
  send_to_char (_("You are using:\n"), ch);

  set_char_color (AT_OBJECT, ch);
  if (LEARNED (ch, gsn_dual_wield))
    {
      candual = TRUE;
    }
  if (get_eq_char (ch, WEAR_HOLD))
    candual = FALSE;
  if (get_eq_char (ch, WEAR_MISSILE_WIELD))
    candual = FALSE;
  for (iWear = 0; iWear < MAX_WEAR; iWear++)
    {
      hasloc = FALSE;
      for (obj = ch->first_carrying; obj; obj = obj->next_content)
	{
	  if (obj->wear_loc == iWear)
	    {
	      if ((!IS_NPC (ch)) && (ch->race > 0)
		  && (ch->race < MAX_PC_RACE))
		send_to_char (race_table[ch->race]->where_name[iWear], ch);
	      else
		send_to_char (where_name[iWear], ch);
	      if (iWear == WEAR_SHIELD)
		candual = FALSE;
	      if (iWear == WEAR_ANKLE_L)
		anklel = TRUE;
	      if (iWear == WEAR_ANKLE_R)
		ankler = TRUE;
	      if (can_see_obj (ch, obj))
		{
		  send_to_char (format_obj_to_char (obj, ch, TRUE), ch);
		  send_to_char ("\n\r", ch);
		}
	      else
		send_to_char (_("something.\n"), ch);
	      hasloc = TRUE;
	    }
	}
      if (!hasloc)
	{
	  if (iWear <= WEAR_EYES)
	    {
	      if ((candual) && (iWear == WEAR_SHIELD))
		continue;
	      if ((candual) && (iWear == WEAR_HOLD))
		continue;
	      if ((!candual) && (iWear == WEAR_DUAL_WIELD))
		continue;
	      send_to_char (where_name[iWear], ch);
	      send_to_char (_("[nothing] \n"), ch);
	    }
	}
    }
  if (!anklel)
    {
      send_to_char (where_name[WEAR_ANKLE_L], ch);
      send_to_char (_("[nothing] \n"), ch);
    }
  if (!ankler)
    {
      send_to_char (where_name[WEAR_ANKLE_R], ch);
      send_to_char (_("[nothing] \n"), ch);
    }
  return;
}


void
set_title (CHAR_DATA * ch, char *title)
{
  char buf[MAX_STRING_LENGTH];

  if (IS_NPC (ch))
    {
      bug (_("Set_title: NPC."), 0);
      return;
    }

  if (isalpha (title[0]) || isdigit (title[0]))
    {
      buf[0] = ' ';
      strcpy (buf + 1, title);
    }
  else
    strcpy (buf, title);

  STRFREE (ch->pcdata->title);
  ch->pcdata->title = STRALLOC (buf);
  return;
}



void
do_title (CHAR_DATA * ch, char *argument)
{
  if (IS_NPC (ch))
    return;

  set_char_color (AT_SCORE, ch);

  if (IS_SET (ch->pcdata->flags, PCFLAG_NOTITLE))
    {
      set_char_color (AT_IMMORT, ch);
      send_to_char (_("The Gods prohibit you from changing your title.\n"),
		    ch);
      return;
    }

  if (argument[0] == '\0')
    {
      send_to_char (_("Change your title to what?\n"), ch);
      return;
    }

  if (strlen (argument) > 50)
    argument[50] = '\0';

  smash_tilde (argument);
  smash_color_token (argument);
  set_title (ch, argument);
  send_to_char (_("Your new title has been set.\n"), ch);
}

void
do_email (CHAR_DATA * ch, char *argument)
{
  char arg[MAX_STRING_LENGTH];

  if (IS_NPC (ch))
    return;

  if (ch->level < 5)
    {
      send_to_char (_("Sorry... you must be at least level 5 to do that.\n"),
		    ch);
      return;
    }

  one_argument (argument, arg);
  smash_tilde (arg);
  if (arg[0] == '\0')
    {
      if (!ch->pcdata->email)
	ch->pcdata->email = str_dup ("");
      ch_printf (ch, _("Your email is: %s\n"), show_tilde (ch->pcdata->email));
      return;
    }

  if (!str_cmp (arg, "clear"))
    {
      if (ch->pcdata->email)
	DISPOSE (ch->pcdata->email);
      ch->pcdata->email = str_dup ("");
      send_to_char (_("Email cleared.\n"), ch);
      return;
    }

  if (ch->pcdata->email)
    DISPOSE (ch->pcdata->email);
  ch->pcdata->email = str_dup (arg);
  send_to_char (_("Email set.\n"), ch);
}

void
do_icq (CHAR_DATA * ch, char *argument)
{
  char arg[MAX_STRING_LENGTH];

  if (IS_NPC (ch))
    return;

  if (ch->level < 5)
    {
      send_to_char (_("Sorry... you must be at least level 5 to do that.\n"),
		    ch);
      return;
    }

  one_argument (argument, arg);
  smash_tilde (arg);
  if (arg[0] == '\0')
    {
      if (!ch->pcdata->icq)
	ch->pcdata->icq = str_dup ("");
      ch_printf (ch, _("Your icq is: %s\n"), show_tilde (ch->pcdata->icq));
      return;
    }

  if (!str_cmp (arg, "clear"))
    {
      if (ch->pcdata->icq)
	DISPOSE (ch->pcdata->icq);
      ch->pcdata->icq = str_dup ("");
      send_to_char (_("ICQ cleared.\n"), ch);
      return;
    }

  hide_tilde (arg);
  if (ch->pcdata->icq)
    DISPOSE (ch->pcdata->icq);
  ch->pcdata->icq = str_dup (arg);
  send_to_char (_("ICQ set.\n"), ch);
}

void
do_homepage (CHAR_DATA * ch, char *argument)
{
  char buf[MAX_STRING_LENGTH];

  if (IS_NPC (ch))
    return;

  if (ch->level < 5)
    {
      send_to_char ("Sorry... you must be at least level 5 to do that.\n\r",
		    ch);
      return;
    }

  if (xIS_SET (ch->act, PLR_NOHOMEPAGE))
    {
      send_to_char ("The Gods prohibit you from changing your homepage.\n\r",
		    ch);
      return;
    }

  if (argument[0] == '\0')
    {
      if (!ch->pcdata->homepage)
	ch->pcdata->homepage = str_dup ("");
      ch_printf (ch, "Your homepage is: %s\n\r",
		 show_tilde (ch->pcdata->homepage));
      return;
    }

  if (!str_cmp (argument, "clear"))
    {
      if (ch->pcdata->homepage)
	DISPOSE (ch->pcdata->homepage);
      ch->pcdata->homepage = str_dup ("");
      send_to_char ("Homepage cleared.\n\r", ch);
      return;
    }

  if (strstr (argument, "://"))
    strcpy (buf, argument);
  else
    sprintf (buf, "http://%s", argument);
  if (strlen (buf) > 70)
    buf[70] = '\0';

  hide_tilde (buf);
  if (ch->pcdata->homepage)
    DISPOSE (ch->pcdata->homepage);
  ch->pcdata->homepage = str_dup (buf);
  send_to_char ("Homepage set.\n\r", ch);
}


void
do_delete_char (CHAR_DATA * ch, char *argument)
{
  char arg[MAX_INPUT_LENGTH];
  char arg1[MAX_INPUT_LENGTH];
  char buf[MAX_INPUT_LENGTH];

  argument = case_argument (argument, arg);
  argument = one_argument (argument, arg1);

  if (IS_NPC (ch))
    return;

  if (get_trust (ch) > 5)
    {
      send_to_char
	("A character must be between levels 2 and 5, and 18 years of age, to delete itself.\n\r",
	 ch);
      return;
    }

  if (get_age (ch) < 18)
    {
      send_to_char
	("A character must be between levels 2 and 5, and 18 years of age, to delete itself.\n\r",
	 ch);
      return;
    }

  if (arg[0] == '\0')
    {
      send_to_char ("Syntax:  chardelete <password> yes\n\r", ch);
      return;
    }

  if (strcmp (sha256_crypt (arg, ch->pcdata->pwd), ch->pcdata->pwd))
    {
      send_to_char ("Incorrect password.\n\r", ch);
      return;
    }

  if (arg1[0] == '\0' || (str_cmp (arg1, "yes")))
    {
      send_to_char ("Syntax:  chardelete <password> yes\n\r", ch);
      return;
    }
  else
    {
      sprintf (buf, "%s deleted pfile from site %s", ch->name,
	       ch->desc->host);
      send_to_char_color ("&RYour character has been deleted.\n\r", ch);
      do_destroy (ch, ch->name);
      log_string_plus (log_buf, LOG_NORMAL, 65);
    }
  return;
}


/*
 * Set your personal description				-Thoric
 */
void
do_description (CHAR_DATA * ch, char *argument)
{
  if (IS_NPC (ch))
    {
      send_to_char ("Monsters are too dumb to do that!\n\r", ch);
      return;
    }

  if (IS_SET (ch->pcdata->flags, PCFLAG_NODESC))
    {
      send_to_char ("You cannot set your description.\n\r", ch);
      return;
    }

  if (!ch->desc)
    {
      bug ("do_description: no descriptor", 0);
      return;
    }

  switch (ch->substate)
    {
    default:
      bug ("do_description: illegal substate", 0);
      return;

    case SUB_RESTRICTED:
      send_to_char
	("You cannot use this command from within another command.\n\r", ch);
      return;

    case SUB_NONE:
      ch->substate = SUB_PERSONAL_DESC;
      ch->dest_buf = ch;
      start_editing (ch, ch->description);
      return;

    case SUB_PERSONAL_DESC:
      STRFREE (ch->description);
      ch->description = copy_buffer (ch);
      stop_editing (ch);
      return;
    }
}

/* Ripped off do_description for whois bio's -- Scryn*/
void
do_bio (CHAR_DATA * ch, char *argument)
{
  if (IS_NPC (ch))
    {
      send_to_char ("Mobs cannot set a bio.\n\r", ch);
      return;
    }
  if (ch->level < 5)
    {
      set_char_color (AT_SCORE, ch);
      send_to_char
	("You must be at least level five to write your bio...\n\r", ch);
      return;
    }

  if (IS_SET (ch->pcdata->flags, PCFLAG_NOBIO))
    {
      set_char_color (AT_RED, ch);
      send_to_char ("The gods won't allow you to do that!\n\r", ch);
      return;
    }

  if (!ch->desc)
    {
      bug ("do_bio: no descriptor", 0);
      return;
    }

  switch (ch->substate)
    {
    default:
      bug ("do_bio: illegal substate", 0);
      return;

    case SUB_RESTRICTED:
      send_to_char
	("You cannot use this command from within another command.\n\r", ch);
      return;

    case SUB_NONE:
      ch->substate = SUB_PERSONAL_BIO;
      ch->dest_buf = ch;
      start_editing (ch, ch->pcdata->bio);
      return;

    case SUB_PERSONAL_BIO:
      STRFREE (ch->pcdata->bio);
      ch->pcdata->bio = copy_buffer (ch);
      stop_editing (ch);
      return;
    }
}



/*
 * New stat and statreport command coded by Morphina
 * Bug fixes by Shaddai
 */

void
do_statreport (CHAR_DATA * ch, char *argument)
{
  char buf[MAX_INPUT_LENGTH];

  if (IS_NPC (ch))
    {
      send_to_char (_("Huh?\n"), ch);
      return;
    }

  if (IS_VAMPIRE(ch) || IS_DEMON(ch))
    {
      ch_printf (ch, "You report: %d/%d hp %d/%d blood %d/%d mv %d xp.\n\r",
		 ch->hit, ch->max_hit,
		 ch->pcdata->condition[COND_BLOODTHIRST], 10 + ch->level,
		 ch->move, ch->max_move, ch->exp);
      sprintf (buf, "$n reports: %d/%d hp %d/%d blood %d/%d mv %d xp.",
	       ch->hit, ch->max_hit, ch->pcdata->condition[COND_BLOODTHIRST],
	       10 + ch->level, ch->move, ch->max_move, ch->exp);
      act (AT_REPORT, buf, ch, NULL, NULL, TO_ROOM);
    }
  else
    {
      ch_printf (ch, "You report: %d/%d hp %d/%d mana %d/%d mv %d xp.\n\r",
		 ch->hit, ch->max_hit, ch->mana, ch->max_mana,
		 ch->move, ch->max_move, ch->exp);
      sprintf (buf, "$n reports: %d/%d hp %d/%d mana %d/%d mv %d xp.",
	       ch->hit, ch->max_hit, ch->mana, ch->max_mana,
	       ch->move, ch->max_move, ch->exp);
      act (AT_REPORT, buf, ch, NULL, NULL, TO_ROOM);
    }

  ch_printf (ch,
	     "Your base stats:    %-2d str %-2d wis %-2d int %-2d dex %-2d con %-2d cha %-2d lck.\n\r",
	     ch->perm_str, ch->perm_wis, ch->perm_int, ch->perm_dex,
	     ch->perm_con, ch->perm_cha, ch->perm_lck);
  sprintf (buf,
	   "$n's base stats:    %-2d str %-2d wis %-2d int %-2d dex %-2d con %-2d cha %-2d lck.",
	   ch->perm_str, ch->perm_wis, ch->perm_int, ch->perm_dex,
	   ch->perm_con, ch->perm_cha, ch->perm_lck);
  act (AT_REPORT, buf, ch, NULL, NULL, TO_ROOM);

  ch_printf (ch,
	     "Your current stats: %-2d str %-2d wis %-2d int %-2d dex %-2d con %-2d cha %-2d lck.\n\r",
	     get_curr_str (ch), get_curr_wis (ch), get_curr_int (ch),
	     get_curr_dex (ch), get_curr_con (ch), get_curr_cha (ch),
	     get_curr_lck (ch));
  sprintf (buf,
	   "$n's current stats: %-2d str %-2d wis %-2d int %-2d dex %-2d con %-2d cha %-2d lck.",
	   get_curr_str (ch), get_curr_wis (ch), get_curr_int (ch),
	   get_curr_dex (ch), get_curr_con (ch), get_curr_cha (ch),
	   get_curr_lck (ch));
  act (AT_REPORT, buf, ch, NULL, NULL, TO_ROOM);
  return;
}

void
do_stat (CHAR_DATA * ch, char *argument)
{
  if (IS_NPC (ch))
    {
      send_to_char (_("Huh?\n"), ch);
      return;
    }

  if (IS_VAMPIRE(ch) || IS_DEMON(ch))
    ch_printf (ch, "You report: %d/%d hp %d/%d blood %d/%d mv %d xp.\n\r",
	       ch->hit, ch->max_hit, ch->pcdata->condition[COND_BLOODTHIRST],
	       10 + ch->level, ch->move, ch->max_move, ch->exp);
  else
    ch_printf (ch, "You report: %d/%d hp %d/%d mana %d/%d mv %d xp.\n\r",
	       ch->hit, ch->max_hit, ch->mana, ch->max_mana,
	       ch->move, ch->max_move, ch->exp);

  ch_printf (ch,
	     "Your base stats:    %-2d str %-2d wis %-2d int %-2d dex %-2d con %-2d cha %-2d lck.\n\r",
	     ch->perm_str, ch->perm_wis, ch->perm_int, ch->perm_dex,
	     ch->perm_con, ch->perm_cha, ch->perm_lck);

  ch_printf (ch,
	     "Your current stats: %-2d str %-2d wis %-2d int %-2d dex %-2d con %-2d cha %-2d lck.\n\r",
	     get_curr_str (ch), get_curr_wis (ch), get_curr_int (ch),
	     get_curr_dex (ch), get_curr_con (ch), get_curr_cha (ch),
	     get_curr_lck (ch));
  return;
}


void
do_report (CHAR_DATA * ch, char *argument)
{
  char buf[MAX_INPUT_LENGTH];

  if (IS_NPC (ch) && ch->fighting)
    return;

  if (IS_AFFECTED (ch, AFF_POSSESS))
    {
      send_to_char ("You can't do that in your current state of mind!\n\r",
		    ch);
      return;
    }


  if (IS_VAMPIRE(ch) || IS_DEMON(ch))
    ch_printf (ch,
	       "You report: %d/%d hp %d/%d blood %d/%d mv %d xp.\n\r",
	       ch->hit, ch->max_hit,
	       ch->pcdata->condition[COND_BLOODTHIRST], 10 + ch->level,
	       ch->move, ch->max_move, ch->exp);
  else
    ch_printf (ch,
	       "You report: %d/%d hp %d/%d mana %d/%d mv %d xp.\n\r",
	       ch->hit, ch->max_hit,
	       ch->mana, ch->max_mana, ch->move, ch->max_move, ch->exp);

  if (IS_VAMPIRE(ch) || IS_DEMON(ch))
    sprintf (buf, "$n reports: %d/%d hp %d/%d blood %d/%d mv %d xp.\n\r",
	     ch->hit, ch->max_hit,
	     ch->pcdata->condition[COND_BLOODTHIRST], 10 + ch->level,
	     ch->move, ch->max_move, ch->exp);
  else
    sprintf (buf, "$n reports: %d/%d hp %d/%d mana %d/%d mv %d xp.",
	     ch->hit, ch->max_hit,
	     ch->mana, ch->max_mana, ch->move, ch->max_move, ch->exp);

  act (AT_REPORT, buf, ch, NULL, NULL, TO_ROOM);

  return;
}

void
do_fprompt (CHAR_DATA * ch, char *argument)
{
  char arg[MAX_INPUT_LENGTH];

  set_char_color (AT_GREY, ch);

  if (IS_NPC (ch))
    {
      send_to_char ("NPC's can't change their prompt..\n\r", ch);
      return;
    }
  smash_tilde (argument);
  one_argument (argument, arg);
  if (!*arg || !str_cmp (arg, "display"))
    {
      send_to_char ("Your current fighting prompt string:\n\r", ch);
      set_char_color (AT_WHITE, ch);
      ch_printf (ch, "%s\n\r",
		 !str_cmp (ch->pcdata->fprompt,
			   "") ? "(default prompt)" : ch->pcdata->fprompt);
      set_char_color (AT_GREY, ch);
      send_to_char
	("Type 'help prompt' for information on changing your prompt.\n\r",
	 ch);
      return;
    }
  send_to_char ("Replacing old prompt of:\n\r", ch);
  set_char_color (AT_WHITE, ch);
  ch_printf (ch, "%s\n\r",
	     !str_cmp (ch->pcdata->fprompt,
		       "") ? "(default prompt)" : ch->pcdata->fprompt);
  if (ch->pcdata->fprompt)
    STRFREE (ch->pcdata->fprompt);
  if (strlen (argument) > 128)
    argument[128] = '\0';

  /* Can add a list of pre-set prompts here if wanted.. perhaps
     'prompt 1' brings up a different, pre-set prompt */
  if (!str_cmp (arg, "default"))
    ch->pcdata->fprompt = STRALLOC ("");
  else if (!str_cmp (arg, "none"))
    ch->pcdata->fprompt = STRALLOC (ch->pcdata->prompt);
  else
    ch->pcdata->fprompt = STRALLOC (argument);
  return;
}

void
do_prompt (CHAR_DATA * ch, char *argument)
{
  char arg[MAX_INPUT_LENGTH];

  set_char_color (AT_GREY, ch);

  if (IS_NPC (ch))
    {
      send_to_char ("NPC's can't change their prompt..\n\r", ch);
      return;
    }
  smash_tilde (argument);
  one_argument (argument, arg);
  if (!*arg || !str_cmp (arg, "display"))
    {
      send_to_char ("Your current prompt string:\n\r", ch);
      set_char_color (AT_WHITE, ch);
      ch_printf (ch, "%s\n\r",
		 !str_cmp (ch->pcdata->prompt,
			   "") ? "(default prompt)" : ch->pcdata->prompt);
      set_char_color (AT_GREY, ch);
      send_to_char
	("Type 'help prompt' for information on changing your prompt.\n\r",
	 ch);
      return;
    }
  send_to_char ("Replacing old prompt of:\n\r", ch);
  set_char_color (AT_WHITE, ch);
  ch_printf (ch, "%s\n\r",
	     !str_cmp (ch->pcdata->prompt,
		       "") ? "(default prompt)" : ch->pcdata->prompt);
  if (ch->pcdata->prompt)
    STRFREE (ch->pcdata->prompt);
  if (strlen (argument) > 128)
    argument[128] = '\0';

  /* Can add a list of pre-set prompts here if wanted.. perhaps
     'prompt 1' brings up a different, pre-set prompt */
  if (!str_cmp (arg, "default"))
    ch->pcdata->prompt = STRALLOC ("");
  else if (!str_cmp (arg, "fprompt"))
    ch->pcdata->prompt = STRALLOC (ch->pcdata->fprompt);
  else
    ch->pcdata->prompt = STRALLOC (argument);
  return;
}

/*
 * Figured this belonged here seeing it involves players... 
 * really simple little function to tax players with a large
 * amount of gold to help reduce the overall gold pool...
 *  --TRI
 */
void
tax_player (CHAR_DATA * ch)
{
/*
  int gold = ch->gold;
  int mgold = (ch->level * 2000000);
  int tax = (ch->gold * .05);

  if ( gold > mgold )
  {
    set_char_color( AT_WHITE, ch );
    ch_printf( ch, "You are level %d and carry more than %d coins.\n\r",
	ch->level, mgold );
    ch_printf( ch, "You are being taxed \%5 percent (%d coins) of your %d coins,\n\r",
	tax, ch->gold );
    ch_printf( ch, "and that leaves you with %d coins.\n\r",
	(ch->gold - tax));
    ch->gold -= tax;

  }
  return;
*/
}

void
do_die (CHAR_DATA * ch, char *argument)
{
  if (ch->position > POS_STUNNED)
    {
      send_to_char
	(_("You don't feel like throwing your life away just yet....\n"), ch);
      return;
    }
  ch->hit = -11;
  update_pos (ch);
  act (AT_DEAD, _("$n is DEAD!!"), ch, 0, 0, TO_ROOM);
  act (AT_DEAD, _("You have been KILLED!!\n"), ch, 0, 0, TO_CHAR);
  raw_kill (ch, ch);
  return;
}

/*
 *  Command to show current favor by Edmond
 */
void
do_favor (CHAR_DATA * ch, char *argument)
{
  char buf[MAX_STRING_LENGTH];

  if (IS_NPC (ch))
    {
      send_to_char (_("Huh?\n"), ch);
      return;
    }
  set_char_color (AT_GREEN, ch);
  if (!ch->pcdata->deity)
    sprintf (buf, "N/A");
  else if (ch->pcdata->favor > 2250)
    sprintf (buf, "loved");
  else if (ch->pcdata->favor > 2000)
    sprintf (buf, "cherished");
  else if (ch->pcdata->favor > 1750)
    sprintf (buf, "honored");
  else if (ch->pcdata->favor > 1500)
    sprintf (buf, "praised");
  else if (ch->pcdata->favor > 1250)
    sprintf (buf, "favored");
  else if (ch->pcdata->favor > 1000)
    sprintf (buf, "respected");
  else if (ch->pcdata->favor > 750)
    sprintf (buf, "liked");
  else if (ch->pcdata->favor > 250)
    sprintf (buf, "tolerated");
  else if (ch->pcdata->favor > -250)
    sprintf (buf, "ignored");
  else if (ch->pcdata->favor > -750)
    sprintf (buf, "shunned");
  else if (ch->pcdata->favor > -1000)
    sprintf (buf, "disliked");
  else if (ch->pcdata->favor > -1250)
    sprintf (buf, "dishonored");
  else if (ch->pcdata->favor > -1500)
    sprintf (buf, "disowned");
  else if (ch->pcdata->favor > -1750)
    sprintf (buf, "abandoned");
  else if (ch->pcdata->favor > -2000)
    sprintf (buf, "despised");
  else if (ch->pcdata->favor > -2250)
    sprintf (buf, "hated");
  else
    sprintf (buf, "damned");

  ch_printf (ch, _("%s considers you to be %s.\n"), ch->pcdata->deity->name,
	     buf);
  return;
}
