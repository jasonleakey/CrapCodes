/*
 *  CPP_practice - TODO
 *  
 *  Feb 7, 2010
 *  Copyleft(R) by jasonleakey
 *  <jasonleakey@gmail.com>
 *  <QQ:174481438>
 *  --------------------------------------------------------------------
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *  MA 02110-1301, USA.
 *  --------------------------------------------------------------------
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <canberra.h>
#include <knotify.h>
#include <errno.h>

void callback(ca_context* c, uint32_t id, int error_code, void* userdata)
{
	fprintf(stderr, "error occurs!\n");
	exit(-1);
}

int main(int argc, char **argv)
{
//	ca_context* cont = NULL;
//	ca_proplist* pro = NULL;
//	int ret = 0;
//
//	if (CA_SUCCESS != (ret =  ca_proplist_create(&pro)))
//	{
//		fprintf(stderr, "error, ca_proplist_create: %s", ca_strerror(ret));
//		return -1;
//	}
//
////	if (CA_SUCCESS != ca_context_change_props_full(cont, pro))
////	{
////		fprintf(stderr, "error, ca_context_change_props_full");
////		return -1;
////  }
//	if (CA_SUCCESS != ca_proplist_sets(pro, CA_PROP_EVENT_MOUSE_BUTTON, "1"))
//	{
//		fprintf(stderr, "error, ca_proplist_sets: %s", strerror(errno));
//		return -1;
//	}
//	if (CA_SUCCESS != (ret = ca_proplist_sets(pro, CA_PROP_MEDIA_FILENAME,
//			"/home/jasonleakey/software-source/win98_sound/ding.wav")))
//	{
//		fprintf(stderr, "error, ca_proplist_sets_2: %s", ca_strerror(ret));
//		return -1;
//	}
//
//	if (CA_SUCCESS != (ret = ca_context_create(&cont)))
//	{
//		fprintf(stderr, "error, ca_context_create: %s", ca_strerror(ret));
//		return -1;
//	}
//	if (CA_SUCCESS != (ret = ca_context_open(cont)))
//	{
//		fprintf(stderr, "error, ca_context_open: %s", ca_strerror(ret));
//		return -1;
//	}
//	if (CA_SUCCESS == ca_context_play_full(cont, 0, pro, callback, NULL))
//	{
//		sleep(5);
//		fprintf(stderr, "timeout!\n");
//		return -1;
//	}
//
//	ca_proplist_destroy(pro);

	{
		ca_context *c = NULL;

		/* Create a context for the event sounds for your application */
		ca_context_create(&c);

		/* Set a few application-global properties */
		ca_context_change_props(c,
                    CA_PROP_APPLICATION_NAME, "An example",
					CA_PROP_APPLICATION_ID, "org.freedesktop.libcanberra.Test",
					CA_PROP_APPLICATION_ICON_NAME, "libcanberra-test",
				        NULL);

		/* ... */

		/* Trigger an event sound */
		ca_context_play(c, 0,
				CA_PROP_EVENT_ID, "window-close", /* The XDG sound name */
				CA_PROP_MEDIA_FILENAME,
				"/home/jasonleakey/software-source/win98_sound/ding.wav",
				CA_PROP_CANBERRA_CACHE_CONTROL, "permanent",
//				CA_PROP_MEDIA_NAME, "The user pressed the button foobar",
//				CA_PROP_EVENT_MOUSE_X, "555",
//				CA_PROP_EVENT_MOUSE_Y, "666",
//				CA_PROP_WINDOW_NAME, "Foobar Dialog",
//				CA_PROP_WINDOW_ICON_NAME, "libcanberra-test-foobar-dialog",
//				CA_PROP_WINDOW_X11_DISPLAY, ":0",
//				CA_PROP_WINDOW_X11_XID, "4711",
				NULL);

		/* ... */

		ca_context_destroy(c);
	}

	return 0;
}

/*
 Copyright (C) 2006-2008 Nokia Corporation. All rights reserved.

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.

 This program is distributed in the hope that it will be useful, but
 WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 02110-1301 USA
 */

//#include <canberra.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <unistd.h>
//
//#define ALARM_GCONF_PATH "/apps/osso/sound/system_alert_volume"
//
//static void callback(ca_context *c, uint32_t id, int error, void *userdata)
//{
//	fprintf(stderr, "callback called, error '%s'\n", ca_strerror(error));
//	exit(0);
//}
//
//static int play_sound(char *filename)
//{
//	int ret, pan;
//	ca_context *ca_con = NULL;
//	ca_proplist *pl = NULL;
//	float volume;
//
//
//
//	/* FIXME: This might need adjusting...
//	 *
//	 * The volume is from -0dB to -6dB,
//	 The full volume is marked as 2 in gconf */
//
//
////	if ((ret = ca_context_set_driver(ca_con, "alsa")) != CA_SUCCESS)
////	{
////		fprintf(stderr, "ca_context_set_driver: %s\n", ca_strerror(ret));
////		return 1;
////	}
//
//	ca_proplist_create(&pl);
//	if (CA_SUCCESS != (ret = ca_proplist_sets(pl, CA_PROP_MEDIA_FILENAME, filename)))
//	{
//		fprintf(stderr, "error, ca_proplist_sets: %s", ca_strerror(ret));
//		return -1;
//	}
//	if (CA_SUCCESS != (ret = ca_proplist_sets(pl, CA_PROP_EVENT_MOUSE_BUTTON, "2")))
//	{
//		fprintf(stderr, "error, ca_proplist_sets_2: %s", ca_strerror(ret));
//		return -1;
//	}
//
//	if ((ret = ca_context_create(&ca_con)) != CA_SUCCESS)
//	{
//		fprintf(stderr, "ca_context_create: %s\n", ca_strerror(ret));
//		return 1;
//	}
//	if ((ret = ca_context_open(ca_con)) != CA_SUCCESS)
//	{
//		fprintf(stderr, "ca_context_open: %s\n", ca_strerror(ret));
//		return 1;
//	}
//	ret = ca_context_play_full(ca_con, 0, pl, callback, NULL);
//	fprintf(stderr, "ca_context_play_full (vol %f): %s\n", volume, ca_strerror(
//			ret));
//	if (ret == CA_SUCCESS)
//	{
//		/* wait for the callback */
//		sleep(100);
//		fprintf(stderr, "timeout\n");
//	}
//
//	return 0;
//}
//
//int main(int argc, char *argv[])
//{
//	if (argc < 2)
//	{
//		fprintf(stderr, "usage: %s <sound file>\n", argv[0]);
//		return 1;
//	}
//	return play_sound(argv[1]);
//}
