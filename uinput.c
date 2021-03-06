/*
 *    This file is part of wdaemon.
 *
 *    wdaemon is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    wdaemon is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with wdaemon; if not, write to the Free Software
 *    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */
#if HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <linux/input.h>
#include <linux/uinput.h>
#include "log.h"
#include "uinput.h"

#ifndef UINPUT_DEVICE
//#error Please define UINPUT_DEVICE in Makefile
#define UINPUT_DEVICE "/dev/uinput"
#endif

#define USB_VENDOR_ID_WACOM 0x056a
#ifndef BUS_VIRTUAL
#define BUS_VIRTUAL 6
#endif

#define set_event(x, y, z) do { if (ioctl((x)->fd, (y), (z)) == -1) { \
	LOG("Error enabling %s (%s)\n", \
#z, strerror(errno)); \
	return 1; \
} \
} while(0)

int adonit_set_events(struct uinput_info *info) {
	/* common */
	set_event(info, UI_SET_EVBIT, EV_KEY);
	set_event(info, UI_SET_EVBIT, EV_ABS);

	/*
	   set_event(info, UI_SET_KEYBIT, BTN_0);
	   set_event(info, UI_SET_KEYBIT, BTN_1);
	   set_event(info, UI_SET_KEYBIT, BTN_TOUCH);
	   */

	set_event(info, UI_SET_KEYBIT, BTN_TOOL_PEN);
	set_event(info, UI_SET_ABSBIT, ABS_X);
	set_event(info, UI_SET_ABSBIT, ABS_Y);
	set_event(info, UI_SET_ABSBIT, ABS_PRESSURE);

	/*
	   set_event(info, UI_SET_ABSBIT, ABS_MT_POSITION_X);
	   set_event(info, UI_SET_ABSBIT, ABS_MT_POSITION_Y);
	   set_event(info, UI_SET_ABSBIT, ABS_MT_SLOT);
	   set_event(info, UI_SET_ABSBIT, ABS_MT_TOUCH_MAJOR);
	   set_event(info, UI_SET_ABSBIT, ABS_MT_TOUCH_MINOR);
	   set_event(info, UI_SET_ABSBIT, ABS_MT_ORIENTATION);
	   set_event(info, UI_SET_ABSBIT, ABS_MT_TRACKING_ID);
	   set_event(info, UI_SET_ABSBIT, ABS_MT_TOOL_X);
	   set_event(info, UI_SET_ABSBIT, ABS_MT_TOOL_Y);
	   */
	return 0;
}

int adonit_set_initial_values(struct uinput_info *info,
		struct uinput_user_dev *dev)
{
	strcpy(dev->name, "Adonit Jot Touch");
	dev->id.bustype = BUS_VIRTUAL;
	dev->id.vendor = USB_VENDOR_ID_WACOM;
	dev->id.product = 0;
	dev->id.version = 9999;	/* XXX */

	/* common */
	dev->absmin[ABS_X] = 0;
	dev->absmax[ABS_X] = 2832;
	//dev->absres[ABS_X] = 10;

	dev->absmin[ABS_Y] = 0;
	dev->absmax[ABS_Y] = 1584;
	//dev->absres[ABS_Y] = 10;

	dev->absmin[ABS_PRESSURE] = 0;
	dev->absmax[ABS_PRESSURE] = 2047;

	/*
	   dev->absmin[ABS_MT_TOUCH_MAJOR] = 0;
	   dev->absmax[ABS_MT_TOOL_X] = 2832;

	   dev->absmin[ABS_MT_TOUCH_MINOR] = 0;
	   dev->absmax[ABS_MT_TOUCH_MINOR] = 255;

	   dev->absmin[ABS_MT_TOUCH_MAJOR] = 0;
	   dev->absmax[ABS_MT_TOUCH_MAJOR] = 255;

	   dev->absmin[ABS_MT_SLOT] = 0;
	   dev->absmax[ABS_MT_SLOT] = 9;

	   dev->absmin[ABS_MT_ORIENTATION] = 0;
	   dev->absmax[ABS_MT_ORIENTATION] = 1;

	   dev->absmin[ABS_MT_POSITION_X] = 0;
	   dev->absmax[ABS_MT_POSITION_X] = 2832;

	   dev->absmin[ABS_MT_POSITION_Y] = 0;
	   dev->absmax[ABS_MT_POSITION_Y] = 1584;

	   dev->absmin[ABS_MT_TOOL_X] = 0;
	   dev->absmax[ABS_MT_TOOL_X] = 2832;

	   dev->absmin[ABS_MT_TOOL_Y] = 0;
	   dev->absmax[ABS_MT_TOOL_Y] = 1584;
	//dev->absres[ABS_MT_TOOL_Y] = 10;

	dev->absmin[ABS_MT_TRACKING_ID] = 0;
	dev->absmax[ABS_MT_TRACKING_ID] = 65535;


	dev->absmin[ABS_MT_TOOL_X] = 0;
	dev->absmax[ABS_MT_TOOL_X] = 2832;
	//dev->absres[ABS_MT_TOOL_X] = 10;
	*/
	return uinput_write_dev(info, dev);
}

int uinput_write_dev(struct uinput_info *info,
		struct uinput_user_dev *dev)
{
	int retval;
	retval = write(info->fd, dev, sizeof(*dev));
	if (retval < 0) {
		perror("Unable to create input device");
		return 1;
	}
	if (retval != sizeof(*dev)) {
		fprintf(stderr, "Short write while creating input device. "
				"Different versions?\n");
		return 1;
	}
	return 0;
}

int uinput_create(struct uinput_info *info)
{
	struct uinput_user_dev dev;
	char file[50], *tmp;
	int retval = -1;
	int need_init = 0;

	tmp = getenv("UINPUT_DEVICE");
	if (!tmp)
		tmp = UINPUT_DEVICE;
	snprintf(file, sizeof(file), "%s", tmp);

	info->fd = open(file, O_RDWR);
	if (info->fd < 0) {
		printf("Unable to open uinput file %s: %s\n", file,
				strerror(errno));
		return -1;
	}

	memset(&dev, 0, sizeof(dev));

	if (adonit_set_initial_values(info, &dev))
		goto err;

	switch(info->create_mode) {
		case SELF_CREATE:
			break;
		case WDAEMON_CREATE:
			need_init = 1;
			break;
		default:
			fprintf(stderr, "Invalid create mode for device.\n");
			return -1;
	}

	if (adonit_set_events(info))
		goto err;

	if (need_init) {
		retval = ioctl(info->fd, UI_DEV_CREATE);
		if (retval == -1) {
			perror("Unable to create uinput device: ");
			goto err;
		}
	}

	retval = 0;
out:
	return retval;
err:
	close(info->fd);
	goto out;
}

int uinput_write_event(struct uinput_info *info, struct input_event *ev)
{
	VLOG("[\e[33m%05ld.%06ld\e[0m] [%s] 0x%04x\t%d\n", ev->time.tv_sec, ev->time.tv_usec,
			(ev->type == EV_SYN ? "EV_SYN" :
			 ev->type == EV_KEY ? "EV_KEY" :
			 ev->type == EV_ABS ? "EV_ABS" : "UNKNOWN"),
			ev->code,
			ev->value);

	if (write(info->fd, ev, sizeof(struct input_event)) !=
			sizeof(struct input_event)) {
		perror("Error writing uinput event: ");
		return 1;
	}
	return 0;
}

/* vim: set noexpandtab tabstop=8 shiftwidth=8: */
