/*
    ettercap -- curses GUI

    Copyright (C) ALoR & NaGA

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

    $Id: ec_curses_view.c,v 1.3 2003/12/14 12:21:52 alor Exp $
*/

#include <ec.h>
#include <wdg.h>
#include <ec_curses.h>

/* proto */

static void toggle_resolve(void);
static void curses_show_stats(void);
static void curses_stop_stats(void);
static void refresh_stats(void);

/* globals */

static char tag_resolve[] = " ";
static wdg_t *wdg_stats;

struct wdg_menu menu_view[] = { {"View",                "V", NULL},
                                {"Profiles",             "", NULL},
                                {"Connections",          "", NULL},
                                {"-",                    "", NULL},
                                {"Resolve IP addresses", tag_resolve, toggle_resolve},
                                {"-",                    "", NULL},
                                {"Statistics",           "", curses_show_stats},
                                {NULL, NULL, NULL},
                              };


/*******************************************/


static void toggle_resolve(void)
{
   if (GBL_OPTIONS->resolve) {
      tag_resolve[0] = ' ';
      GBL_OPTIONS->resolve = 0;
   } else {
      tag_resolve[0] = '*';
      GBL_OPTIONS->resolve = 1;
   }
}

/*
 * display the statistics windows
 */
static void curses_show_stats(void)
{
   DEBUG_MSG("curses_show_stats");

   wdg_create_object(&wdg_stats, WDG_WINDOW, WDG_OBJ_WANT_FOCUS);
   
   wdg_set_title(wdg_stats, "Statistics:", WDG_ALIGN_LEFT);
   wdg_set_size(wdg_stats, 2, 2, 70, 22);
   wdg_set_color(wdg_stats, WDG_COLOR_SCREEN, EC_COLOR);
   wdg_set_color(wdg_stats, WDG_COLOR_WINDOW, EC_COLOR);
   wdg_set_color(wdg_stats, WDG_COLOR_BORDER, EC_COLOR_BORDER);
   wdg_set_color(wdg_stats, WDG_COLOR_FOCUS, EC_COLOR_FOCUS);
   wdg_set_color(wdg_stats, WDG_COLOR_TITLE, EC_COLOR_TITLE);
   wdg_draw_object(wdg_stats);
 
   wdg_set_focus(wdg_stats);
  
   /* display the stats */
   refresh_stats(); 

   /* add the callback on idle to refresh the stats */
   wdg_add_idle_callback(refresh_stats);

   /* add the destroy callback */
   wdg_add_destroy_key(wdg_stats, CTRL('Q'), curses_stop_stats);
}

static void curses_stop_stats(void)
{
   DEBUG_MSG("curses_stop_stats");
   wdg_del_idle_callback(refresh_stats);
}

static void refresh_stats(void)
{
   /* if not focused don't refresh it */
   if (!(wdg_stats->flags & WDG_OBJ_FOCUSED))
      return;
   
   wdg_window_print(wdg_stats, 1, 1, "Received packets    : %lld", GBL_STATS->ps_recv);
   wdg_window_print(wdg_stats, 1, 2, "Dropped packets     : %lld", GBL_STATS->ps_drop);
   wdg_window_print(wdg_stats, 1, 3, "Lost percentage     : %.2f %%",
          (GBL_STATS->ps_recv) ? (float)GBL_STATS->ps_drop * 100 / GBL_STATS->ps_recv : 0 );
  
   wdg_window_print(wdg_stats, 1, 5, "Current queue len   : %d", GBL_STATS->queue_curr);
   wdg_window_print(wdg_stats, 1, 6, "Max queue len       : %d", GBL_STATS->queue_max);
   
   wdg_window_print(wdg_stats, 1, 7, "Sampling rate       : %d", GBL_CONF->sampling_rate);
   
   wdg_window_print(wdg_stats, 1, 9, "Bottom Half received packet : pck: %8lld  byte: %8lld", 
         GBL_STATS->bh.pck_recv, GBL_STATS->bh.pck_size);
   wdg_window_print(wdg_stats, 1, 10, "Top Half received packet    : pck: %8lld  byte: %8lld", 
         GBL_STATS->th.pck_recv, GBL_STATS->th.pck_size);
   wdg_window_print(wdg_stats, 1, 11, "Interesting packets         : %.2f %%",
         (GBL_STATS->bh.pck_recv) ? (float)GBL_STATS->th.pck_recv * 100 / GBL_STATS->bh.pck_recv : 0 );

   wdg_window_print(wdg_stats, 1, 13, "Bottom Half packet rate : worst: %8d  adv: %8d p/s", 
         GBL_STATS->bh.rate_worst, GBL_STATS->bh.rate_adv);
   wdg_window_print(wdg_stats, 1, 14, "Top Half packet rate    : worst: %8d  adv: %8d p/s", 
         GBL_STATS->th.rate_worst, GBL_STATS->th.rate_adv);
   
   wdg_window_print(wdg_stats, 1, 15, "Bottom Half thruoutput  : worst: %8d  adv: %8d b/s", 
         GBL_STATS->bh.thru_worst, GBL_STATS->bh.thru_adv);
   wdg_window_print(wdg_stats, 1, 16, "Top Half thruoutput     : worst: %8d  adv: %8d b/s", 
         GBL_STATS->th.thru_worst, GBL_STATS->th.thru_adv);
}


/* EOF */

// vim:ts=3:expandtab
