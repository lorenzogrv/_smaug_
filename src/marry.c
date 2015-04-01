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
     |                    -*- Player Marriage Module -*-                   |
     |_____________________________________________________________________|
     |                                                                     |
     |                          Marriage Code v1.3                         |
     |                                By Cid                               |
     |                         eos.execnet.com:1234                        |
     |_____________________________________________________________________|
     |                                                                     |
     | Unlike my other codes this one does require the addition of another |
     | pcdata field. Like spouse. If you add it spouse is a string not an  |
     | integer. So thats how it works. Plus you'll have to modify db.c     |
     | save.c to load up the spouse string so this will work. This snippet | 
     | also includes a rings command. It'll create the rings for the       |
     | married couple.  Which you'll have to define in mud.h               |
     | OBJ_VNUM_DIAMOND_RING and OBJ_VNUM_WEDDING_BAND to vnums that you   |
     | might have (ofcourse I created 2 rings for this then added in the   |
     | marriage code).  The rings command would be the easiest to add in   |
     | cause of just putting in 2 lines in mud.h...even though its a lot   |
     | easier then the marriage, and divorce code...but it needs the spouse|
     | field(checks to see if they are married).   Well enjoy...btw dont   |
     | forget to put somewhere in your code to give me credits or if you   |
     | just pop in this file... Keep the this header intact.               |
     |                                                                     |
     | Add do_divorce and do_marry to mud.h and tables.c                   |
     |  - Ntanel StormBlade                                                |
     |_____________________________________________________________________|
    //                                                                     \\
   [|  SMAUG 1.4 © 1994-1998 Thoric/Altrag/Blodkai/Narn/Haus/Scryn/Rennard  |]
   [|  Swordbearer/Gorog/Grishnakh/Nivek/Tricops/Fireblade/Edmond/Conran    |]
   [|                                                                       |]
   [|  Merc 2.1 Diku Mud improvments © 1992-1993 Michael Chastain, Michael  |]
   [|  Quan, and Mitchell Tse. Original Diku Mud © 1990-1991 by Sebastian   |]
   [|  Hammer, Michael Seifert, Hans Henrik St{rfeldt, Tom Madsen, Katja    |]
   [|  Nyboe. Win32 port Nick Gammon.                                       |]
   [|                                                                       |]
   [|  SMAUG 2.0 © 2014-2015 Antonio Cao (@burzumishi)                      |]
    \\_____________________________________________________________________//
*/  
  
#include <sys/types.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
  
#include "mud.h"
  
do_marry (CHAR_DATA * ch, char *argument) 
{
  
  
  
  
  
  
  
    
    {
      
      
    
  
	 ((victim2 = get_char_world (ch, arg2)) == NULL))
    
    {
      
      
    
  
    
    {
      
      
    
  
	   && victim2->pcdata->spouse[0] == '\0')
    
    {
      
      
      
      
	      NULL, victim2, TO_ROOM);
      
      
      
    
  
  else
    
    {
      
      
    
  
    
    {
      
      
    
  



do_divorce (CHAR_DATA * ch, char *argument) 
{
  
  
  
  
  
  
  
    
    {
      
      
    
  
       ((victim2 = get_char_world (ch, arg2)) == NULL))
    
    {
      
      
    
  
    
    {
      
      
    
  
	 && !str_cmp (victim2->pcdata->spouse, victim->name))
    
/*       if (victim->pcdata->spouse != victim2->name || victim2->pcdata->spouse != victim->name)
          {
          send_to_char("They aren't even married!!\n\r",ch);
          return;
          } */ 
    {
      
      
      
      
	      "$n and $N swap divorce papers, they are no-longer married.",
	      victim, NULL, victim2, TO_NOTVICT);
      
      
      
      
      
    
  
  else
    
    {
      
      
    



do_rings (CHAR_DATA * ch, char *argument) 
{
  
  
  
  
  
  
  
  
  
  
	   ((victim2 = get_char_world (ch, arg2)) == NULL))
    
    {
      
      
    
  
/*       if ((victim->pcdata->spouse != victim2->name) || (victim2->pcdata->spouse != victim->name))
       {
          send_to_char("They arent even married!!\n\r", ch);
          return;
       } */ 
    
    
    {
    
      
      {
	
	
	  
	  {
	  
	    
	    {
	      
			"This is the beautiful diamond ring given to you by your lovely\n\rwife %s at your wedding. It signifies your eternal love for eachother.\n\r",
			victim->name);
	      
	      
	    
	  
	    
	    {
	      
			"This is the beautiful diamond ring given to you by your handsome\n\rhusband %s at your wedding. It signifies your eternal love for eachother.\n\r",
			victim->name);
	      
	      
	    
	  
	  
	    
	    {
	      
			"This is the beautiful diamond ring given to you by your\n\rspouse %s at your wedding. It signifies your eternal love for eachother.\n\r",
			victim->name);
	      
	      
	    
	  
	
	  
	  {
	    
	  
	
	else
	  
	  {
	    
	    
	  
	
	
		  "The inscription reads:\n\rTo my lovely wife, yours forever, %s\n\r",
		  victim->name);
	
	
	
	
	
      
    
    
    
      
      {
	
	
	  
	  {
	  
	    
	    {
	      
			"This is the ring given to you by your beautifull wife %s\n\rat your wedding. It signifies your eternal love for eachother.\n\r",
			victim->name);
	      
	      
	    
	  
	    
	    {
	      
			"This is the ring given to you by your handsome husband %s\n\rat your wedding. It signifies your eternal love for eachother.\n\r",
			victim->name);
	      
	      
	    
	  
	  
	    
	    {
	      
			"This is the ring given to you by your spouse %s at\n\ryour wedding. It signifies your eternal love for eachother.\n\r",
			victim->name);
	      
	      
	    
	  
	
	  
	  {
	    
	  
	
	else
	  
	  {
	    
	    
	  
	
	
	
	
	
	  
	  {
	  
	  
	    
	    {
	      
			"The inscription reads:\n\rTo my handsome husband... Forever yours, %s\n\r",
			victim->name);
	      
	      
	    
	  
	    
	    {
	      
			victim->name);
	      
	      
	    
	  
      
    
  
  


