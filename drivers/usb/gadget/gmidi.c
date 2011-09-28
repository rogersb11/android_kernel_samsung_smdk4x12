/*
 * gmidi.c -- USB MIDI Gadget Driver
 *
 * Copyright (C) 2006 Thumtronics Pty Ltd.
 * Developed for Thumtronics by Grey Innovation
 * Ben Williamson <ben.williamson@greyinnovation.com>
 *
 * This software is distributed under the terms of the GNU General Public
 * License ("GPL") version 2, as published by the Free Software Foundation.
 *
 * This code is based in part on:
 *
 * Gadget Zero driver, Copyright (C) 2003-2004 David Brownell.
 * USB Audio driver, Copyright (C) 2002 by Takashi Iwai.
 * USB MIDI driver, Copyright (C) 2002-2005 Clemens Ladisch.
 *
 * Refer to the USB Device Class Definition for MIDI Devices:
 * http://www.usb.org/developers/devclass_docs/midi10.pdf
 */

/* #define VERBOSE_DEBUG */

#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/utsname.h>
#include <linux/device.h>

#include <sound/core.h>
#include <sound/initval.h>
#include <sound/rawmidi.h>

#include <linux/usb/ch9.h>
#include <linux/usb/gadget.h>
#include <linux/usb/audio.h>
#include <linux/usb/midi.h>

#include "gadget_chips.h"

#include "composite.c"
#include "usbstring.c"
#include "config.c"
#include "epautoconf.c"
#include "f_midi.c"

/*-------------------------------------------------------------------------*/

MODULE_AUTHOR("Ben Williamson");
MODULE_LICENSE("GPL v2");

static const char shortname[] = "g_midi";
static const char longname[] = "MIDI Gadget";

static int index = SNDRV_DEFAULT_IDX1;
module_param(index, int, S_IRUGO);
MODULE_PARM_DESC(index, "Index value for the USB MIDI Gadget adapter.");

static char *id = SNDRV_DEFAULT_STR1;
module_param(id, charp, S_IRUGO);
MODULE_PARM_DESC(id, "ID string for the USB MIDI Gadget adapter.");

static unsigned int buflen = 256;
module_param(buflen, uint, S_IRUGO);
MODULE_PARM_DESC(buflen, "MIDI buffer length");

static unsigned int qlen = 32;
module_param(qlen, uint, S_IRUGO);
MODULE_PARM_DESC(qlen, "USB read request queue length");

/* Thanks to Grey Innovation for donating this product ID.
 *
 * DO NOT REUSE THESE IDs with a protocol-incompatible driver!!  Ever!!
 * Instead:  allocate your own, using normal USB-IF procedures.
 */
#define DRIVER_VENDOR_NUM	0x17b3		/* Grey Innovation */
#define DRIVER_PRODUCT_NUM	0x0004		/* Linux-USB "MIDI Gadget" */

/* string IDs are assigned dynamically */

#define STRING_MANUFACTURER_IDX		0
#define STRING_PRODUCT_IDX		1
#define STRING_DESCRIPTION_IDX		2

static struct usb_device_descriptor device_desc = {
	.bLength =		USB_DT_DEVICE_SIZE,
	.bDescriptorType =	USB_DT_DEVICE,
	.bcdUSB =		__constant_cpu_to_le16(0x0200),
	.bDeviceClass =		USB_CLASS_PER_INTERFACE,
	.idVendor =		__constant_cpu_to_le16(DRIVER_VENDOR_NUM),
	.idProduct =		__constant_cpu_to_le16(DRIVER_PRODUCT_NUM),
	/* .iManufacturer =	DYNAMIC */
	/* .iProduct =		DYNAMIC */
	.bNumConfigurations =	1,
};

static struct usb_string strings_dev[] = {
	[STRING_MANUFACTURER_IDX].s	= "Grey Innovation",
	[STRING_PRODUCT_IDX].s		= "MIDI Gadget",
	[STRING_DESCRIPTION_IDX].s	= "MIDI",
	{  } /* end of list */
};

static struct usb_gadget_strings stringtab_dev = {
	.language	= 0x0409,	/* en-us */
	.strings	= strings_dev,
};

static struct usb_gadget_strings *dev_strings[] = {
	&stringtab_dev,
	NULL,
};

<<<<<<< HEAD
/*
 * Receives a chunk of MIDI data.
 */
static void gmidi_read_data(struct usb_ep *ep, int cable,
				   uint8_t *data, int length)
{
	struct gmidi_device *dev = ep->driver_data;
	/* cable is ignored, because for now we only have one. */

	if (!dev->out_substream) {
		/* Nobody is listening - throw it on the floor. */
		return;
	}
	if (!test_bit(dev->out_substream->number, &dev->out_triggered)) {
		return;
	}
	snd_rawmidi_receive(dev->out_substream, data, length);
}

static void gmidi_handle_out_data(struct usb_ep *ep, struct usb_request *req)
{
	unsigned i;
	u8 *buf = req->buf;

	for (i = 0; i + 3 < req->actual; i += 4) {
		if (buf[i] != 0) {
			int cable = buf[i] >> 4;
			int length = gmidi_cin_length[buf[i] & 0x0f];
			gmidi_read_data(ep, cable, &buf[i + 1], length);
		}
	}
}

static void gmidi_complete(struct usb_ep *ep, struct usb_request *req)
{
	struct gmidi_device *dev = ep->driver_data;
	int status = req->status;

	switch (status) {
	case 0:				/* normal completion */
		if (ep == dev->out_ep) {
			/* we received stuff.
			   req is queued again, below */
			gmidi_handle_out_data(ep, req);
		} else if (ep == dev->in_ep) {
			/* our transmit completed.
			   see if there's more to go.
			   gmidi_transmit eats req, don't queue it again. */
			gmidi_transmit(dev, req);
			return;
		}
		break;

	/* this endpoint is normally active while we're configured */
	case -ECONNABORTED:		/* hardware forced ep reset */
	case -ECONNRESET:		/* request dequeued */
	case -ESHUTDOWN:		/* disconnect from host */
		VDBG(dev, "%s gone (%d), %d/%d\n", ep->name, status,
				req->actual, req->length);
		if (ep == dev->out_ep) {
			gmidi_handle_out_data(ep, req);
		}
		free_ep_req(ep, req);
		return;

	case -EOVERFLOW:		/* buffer overrun on read means that
					 * we didn't provide a big enough
					 * buffer.
					 */
	default:
		DBG(dev, "%s complete --> %d, %d/%d\n", ep->name,
				status, req->actual, req->length);
		break;
	case -EREMOTEIO:		/* short read */
		break;
	}

	status = usb_ep_queue(ep, req, GFP_ATOMIC);
	if (status) {
		ERROR(dev, "kill %s:  resubmit %d bytes --> %d\n",
				ep->name, req->length, status);
		usb_ep_set_halt(ep);
		/* FIXME recover later ... somehow */
	}
}

static int set_gmidi_config(struct gmidi_device *dev, gfp_t gfp_flags)
{
	int err = 0;
	struct usb_request *req;
	struct usb_ep *ep;
	unsigned i;

	err = usb_ep_enable(dev->in_ep, &bulk_in_desc);
	if (err) {
		ERROR(dev, "can't start %s: %d\n", dev->in_ep->name, err);
		goto fail;
	}
	dev->in_ep->driver_data = dev;

	err = usb_ep_enable(dev->out_ep, &bulk_out_desc);
	if (err) {
		ERROR(dev, "can't start %s: %d\n", dev->out_ep->name, err);
		goto fail;
	}
	dev->out_ep->driver_data = dev;

	/* allocate a bunch of read buffers and queue them all at once. */
	ep = dev->out_ep;
	for (i = 0; i < qlen && err == 0; i++) {
		req = alloc_ep_req(ep, buflen);
		if (req) {
			req->complete = gmidi_complete;
			err = usb_ep_queue(ep, req, GFP_ATOMIC);
			if (err) {
				DBG(dev, "%s queue req: %d\n", ep->name, err);
			}
		} else {
			err = -ENOMEM;
		}
	}
fail:
	/* caller is responsible for cleanup on error */
	return err;
}


static void gmidi_reset_config(struct gmidi_device *dev)
{
	if (dev->config == 0) {
		return;
	}

	DBG(dev, "reset config\n");

	/* just disable endpoints, forcing completion of pending i/o.
	 * all our completion handlers free their requests in this case.
	 */
	usb_ep_disable(dev->in_ep);
	usb_ep_disable(dev->out_ep);
	dev->config = 0;
}

/* change our operational config.  this code must agree with the code
 * that returns config descriptors, and altsetting code.
 *
 * it's also responsible for power management interactions. some
 * configurations might not work with our current power sources.
 *
 * note that some device controller hardware will constrain what this
 * code can do, perhaps by disallowing more than one configuration or
 * by limiting configuration choices (like the pxa2xx).
 */
static int
gmidi_set_config(struct gmidi_device *dev, unsigned number, gfp_t gfp_flags)
{
	int result = 0;
	struct usb_gadget *gadget = dev->gadget;

#if 0
	/* FIXME */
	/* Hacking this bit out fixes a bug where on receipt of two
	   USB_REQ_SET_CONFIGURATION messages, we end up with no
	   buffered OUT requests waiting for data. This is clearly
	   hiding a bug elsewhere, because if the config didn't
	   change then we really shouldn't do anything. */
	/* Having said that, when we do "change" from config 1
	   to config 1, we at least gmidi_reset_config() which
	   clears out any requests on endpoints, so it's not like
	   we leak or anything. */
	if (number == dev->config) {
		return 0;
	}
#endif

	gmidi_reset_config(dev);

	switch (number) {
	case GMIDI_CONFIG:
		result = set_gmidi_config(dev, gfp_flags);
		break;
	default:
		result = -EINVAL;
		/* FALL THROUGH */
	case 0:
		return result;
	}

	if (!result && (!dev->in_ep || !dev->out_ep)) {
		result = -ENODEV;
	}
	if (result) {
		gmidi_reset_config(dev);
	} else {
		char *speed;

		switch (gadget->speed) {
		case USB_SPEED_LOW:	speed = "low"; break;
		case USB_SPEED_FULL:	speed = "full"; break;
		case USB_SPEED_HIGH:	speed = "high"; break;
		default:		speed = "?"; break;
		}

		dev->config = number;
		INFO(dev, "%s speed\n", speed);
	}
	return result;
}


static void gmidi_setup_complete(struct usb_ep *ep, struct usb_request *req)
{
	if (req->status || req->actual != req->length) {
		DBG((struct gmidi_device *) ep->driver_data,
				"setup complete --> %d, %d/%d\n",
				req->status, req->actual, req->length);
	}
}

/*
 * The setup() callback implements all the ep0 functionality that's
 * not handled lower down, in hardware or the hardware driver (like
 * device and endpoint feature flags, and their status).  It's all
 * housekeeping for the gadget function we're implementing.  Most of
 * the work is in config-specific setup.
 */
static int gmidi_setup(struct usb_gadget *gadget,
			const struct usb_ctrlrequest *ctrl)
{
	struct gmidi_device *dev = get_gadget_data(gadget);
	struct usb_request *req = dev->req;
	int value = -EOPNOTSUPP;
	u16 w_index = le16_to_cpu(ctrl->wIndex);
	u16 w_value = le16_to_cpu(ctrl->wValue);
	u16 w_length = le16_to_cpu(ctrl->wLength);

	/* usually this stores reply data in the pre-allocated ep0 buffer,
	 * but config change events will reconfigure hardware.
	 */
	req->zero = 0;
	switch (ctrl->bRequest) {

	case USB_REQ_GET_DESCRIPTOR:
		if (ctrl->bRequestType != USB_DIR_IN) {
			goto unknown;
		}
		switch (w_value >> 8) {

		case USB_DT_DEVICE:
			value = min(w_length, (u16) sizeof(device_desc));
			memcpy(req->buf, &device_desc, value);
			break;
		case USB_DT_CONFIG:
			value = config_buf(gadget, req->buf,
					w_value >> 8,
					w_value & 0xff);
			if (value >= 0) {
				value = min(w_length, (u16)value);
			}
			break;

		case USB_DT_STRING:
			/* wIndex == language code.
			 * this driver only handles one language, you can
			 * add string tables for other languages, using
			 * any UTF-8 characters
			 */
			value = usb_gadget_get_string(&stringtab,
					w_value & 0xff, req->buf);
			if (value >= 0) {
				value = min(w_length, (u16)value);
			}
			break;
		}
		break;

	/* currently two configs, two speeds */
	case USB_REQ_SET_CONFIGURATION:
		if (ctrl->bRequestType != 0) {
			goto unknown;
		}
		if (gadget->a_hnp_support) {
			DBG(dev, "HNP available\n");
		} else if (gadget->a_alt_hnp_support) {
			DBG(dev, "HNP needs a different root port\n");
		} else {
			VDBG(dev, "HNP inactive\n");
		}
		spin_lock(&dev->lock);
		value = gmidi_set_config(dev, w_value, GFP_ATOMIC);
		spin_unlock(&dev->lock);
		break;
	case USB_REQ_GET_CONFIGURATION:
		if (ctrl->bRequestType != USB_DIR_IN) {
			goto unknown;
		}
		*(u8 *)req->buf = dev->config;
		value = min(w_length, (u16)1);
		break;

	/* until we add altsetting support, or other interfaces,
	 * only 0/0 are possible.  pxa2xx only supports 0/0 (poorly)
	 * and already killed pending endpoint I/O.
	 */
	case USB_REQ_SET_INTERFACE:
		if (ctrl->bRequestType != USB_RECIP_INTERFACE) {
			goto unknown;
		}
		spin_lock(&dev->lock);
		if (dev->config && w_index < GMIDI_NUM_INTERFACES
			&& w_value == 0)
		{
			u8 config = dev->config;

			/* resets interface configuration, forgets about
			 * previous transaction state (queued bufs, etc)
			 * and re-inits endpoint state (toggle etc)
			 * no response queued, just zero status == success.
			 * if we had more than one interface we couldn't
			 * use this "reset the config" shortcut.
			 */
			gmidi_reset_config(dev);
			gmidi_set_config(dev, config, GFP_ATOMIC);
			value = 0;
		}
		spin_unlock(&dev->lock);
		break;
	case USB_REQ_GET_INTERFACE:
		if (ctrl->bRequestType != (USB_DIR_IN|USB_RECIP_INTERFACE)) {
			goto unknown;
		}
		if (!dev->config) {
			break;
		}
		if (w_index >= GMIDI_NUM_INTERFACES) {
			value = -EDOM;
			break;
		}
		*(u8 *)req->buf = 0;
		value = min(w_length, (u16)1);
		break;

	default:
unknown:
		VDBG(dev, "unknown control req%02x.%02x v%04x i%04x l%d\n",
			ctrl->bRequestType, ctrl->bRequest,
			w_value, w_index, w_length);
	}

	/* respond with data transfer before status phase? */
	if (value >= 0) {
		req->length = value;
		req->zero = value < w_length;
		value = usb_ep_queue(gadget->ep0, req, GFP_ATOMIC);
		if (value < 0) {
			DBG(dev, "ep_queue --> %d\n", value);
			req->status = 0;
			gmidi_setup_complete(gadget->ep0, req);
		}
	}

	/* device either stalls (value < 0) or reports success */
	return value;
}

static void gmidi_disconnect(struct usb_gadget *gadget)
{
	struct gmidi_device *dev = get_gadget_data(gadget);
	unsigned long flags;

	spin_lock_irqsave(&dev->lock, flags);
	gmidi_reset_config(dev);

	/* a more significant application might have some non-usb
	 * activities to quiesce here, saving resources like power
	 * or pushing the notification up a network stack.
	 */
	spin_unlock_irqrestore(&dev->lock, flags);

	/* next we may get setup() calls to enumerate new connections;
	 * or an unbind() during shutdown (including removing module).
	 */
}

static void /* __init_or_exit */ gmidi_unbind(struct usb_gadget *gadget)
{
	struct gmidi_device *dev = get_gadget_data(gadget);
	struct snd_card *card;

	DBG(dev, "unbind\n");

	card = dev->card;
	dev->card = NULL;
	if (card) {
		snd_card_free(card);
	}

	/* we've already been disconnected ... no i/o is active */
	if (dev->req) {
		dev->req->length = USB_BUFSIZ;
		free_ep_req(gadget->ep0, dev->req);
	}
	kfree(dev);
	set_gadget_data(gadget, NULL);
}

static int gmidi_snd_free(struct snd_device *device)
{
	return 0;
}

static void gmidi_transmit_packet(struct usb_request *req, uint8_t p0,
					uint8_t p1, uint8_t p2, uint8_t p3)
{
	unsigned length = req->length;
	u8 *buf = (u8 *)req->buf + length;

	buf[0] = p0;
	buf[1] = p1;
	buf[2] = p2;
	buf[3] = p3;
	req->length = length + 4;
}

/*
 * Converts MIDI commands to USB MIDI packets.
 */
static void gmidi_transmit_byte(struct usb_request *req,
				struct gmidi_in_port *port, uint8_t b)
{
	uint8_t p0 = port->cable;

	if (b >= 0xf8) {
		gmidi_transmit_packet(req, p0 | 0x0f, b, 0, 0);
	} else if (b >= 0xf0) {
		switch (b) {
		case 0xf0:
			port->data[0] = b;
			port->state = STATE_SYSEX_1;
			break;
		case 0xf1:
		case 0xf3:
			port->data[0] = b;
			port->state = STATE_1PARAM;
			break;
		case 0xf2:
			port->data[0] = b;
			port->state = STATE_2PARAM_1;
			break;
		case 0xf4:
		case 0xf5:
			port->state = STATE_UNKNOWN;
			break;
		case 0xf6:
			gmidi_transmit_packet(req, p0 | 0x05, 0xf6, 0, 0);
			port->state = STATE_UNKNOWN;
			break;
		case 0xf7:
			switch (port->state) {
			case STATE_SYSEX_0:
				gmidi_transmit_packet(req,
					p0 | 0x05, 0xf7, 0, 0);
				break;
			case STATE_SYSEX_1:
				gmidi_transmit_packet(req,
					p0 | 0x06, port->data[0], 0xf7, 0);
				break;
			case STATE_SYSEX_2:
				gmidi_transmit_packet(req,
					p0 | 0x07, port->data[0],
					port->data[1], 0xf7);
				break;
			}
			port->state = STATE_UNKNOWN;
			break;
		}
	} else if (b >= 0x80) {
		port->data[0] = b;
		if (b >= 0xc0 && b <= 0xdf)
			port->state = STATE_1PARAM;
		else
			port->state = STATE_2PARAM_1;
	} else { /* b < 0x80 */
		switch (port->state) {
		case STATE_1PARAM:
			if (port->data[0] < 0xf0) {
				p0 |= port->data[0] >> 4;
			} else {
				p0 |= 0x02;
				port->state = STATE_UNKNOWN;
			}
			gmidi_transmit_packet(req, p0, port->data[0], b, 0);
			break;
		case STATE_2PARAM_1:
			port->data[1] = b;
			port->state = STATE_2PARAM_2;
			break;
		case STATE_2PARAM_2:
			if (port->data[0] < 0xf0) {
				p0 |= port->data[0] >> 4;
				port->state = STATE_2PARAM_1;
			} else {
				p0 |= 0x03;
				port->state = STATE_UNKNOWN;
			}
			gmidi_transmit_packet(req,
				p0, port->data[0], port->data[1], b);
			break;
		case STATE_SYSEX_0:
			port->data[0] = b;
			port->state = STATE_SYSEX_1;
			break;
		case STATE_SYSEX_1:
			port->data[1] = b;
			port->state = STATE_SYSEX_2;
			break;
		case STATE_SYSEX_2:
			gmidi_transmit_packet(req,
				p0 | 0x04, port->data[0], port->data[1], b);
			port->state = STATE_SYSEX_0;
			break;
		}
	}
}

static void gmidi_transmit(struct gmidi_device *dev, struct usb_request *req)
{
	struct usb_ep *ep = dev->in_ep;
	struct gmidi_in_port *port = &dev->in_port;

	if (!ep) {
		return;
	}
	if (!req) {
		req = alloc_ep_req(ep, buflen);
	}
	if (!req) {
		ERROR(dev, "gmidi_transmit: alloc_ep_request failed\n");
		return;
	}
	req->length = 0;
	req->complete = gmidi_complete;

	if (port->active) {
		while (req->length + 3 < buflen) {
			uint8_t b;
			if (snd_rawmidi_transmit(dev->in_substream, &b, 1)
				!= 1)
			{
				port->active = 0;
				break;
			}
			gmidi_transmit_byte(req, port, b);
		}
	}
	if (req->length > 0) {
		usb_ep_queue(ep, req, GFP_ATOMIC);
	} else {
		free_ep_req(ep, req);
	}
}

static void gmidi_in_tasklet(unsigned long data)
{
	struct gmidi_device *dev = (struct gmidi_device *)data;

	gmidi_transmit(dev, NULL);
}

static int gmidi_in_open(struct snd_rawmidi_substream *substream)
{
	struct gmidi_device *dev = substream->rmidi->private_data;

	VDBG(dev, "gmidi_in_open\n");
	dev->in_substream = substream;
	dev->in_port.state = STATE_UNKNOWN;
	return 0;
}

static int gmidi_in_close(struct snd_rawmidi_substream *substream)
{
	struct gmidi_device *dev = substream->rmidi->private_data;

	VDBG(dev, "gmidi_in_close\n");
	return 0;
}

static void gmidi_in_trigger(struct snd_rawmidi_substream *substream, int up)
{
	struct gmidi_device *dev = substream->rmidi->private_data;

	VDBG(dev, "gmidi_in_trigger %d\n", up);
	dev->in_port.active = up;
	if (up) {
		tasklet_hi_schedule(&dev->tasklet);
	}
}

static int gmidi_out_open(struct snd_rawmidi_substream *substream)
{
	struct gmidi_device *dev = substream->rmidi->private_data;

	VDBG(dev, "gmidi_out_open\n");
	dev->out_substream = substream;
	return 0;
}

static struct usb_configuration midi_config = {
	.label		= "MIDI Gadget",
	.bConfigurationValue = 1,
	/* .iConfiguration = DYNAMIC */
	.bmAttributes	= USB_CONFIG_ATT_ONE,
	.bMaxPower	= CONFIG_USB_GADGET_VBUS_DRAW / 2,
};

static int __init midi_bind_config(struct usb_configuration *c)
{
	return f_midi_bind_config(c, index, id, buflen, qlen);
}

static int __init midi_bind(struct usb_composite_dev *cdev)
{
	struct usb_gadget *gadget = cdev->gadget;
	int gcnum, status;

	status = usb_string_id(cdev);
	if (status < 0)
		return status;
	strings_dev[STRING_MANUFACTURER_IDX].id = status;
	device_desc.iManufacturer = status;

	status = usb_string_id(cdev);
	if (status < 0)
		return status;
	strings_dev[STRING_PRODUCT_IDX].id = status;
	device_desc.iProduct = status;

	/* config description */
	status = usb_string_id(cdev);
	if (status < 0)
		return status;
	strings_dev[STRING_DESCRIPTION_IDX].id = status;

	midi_config.iConfiguration = status;

	gcnum = usb_gadget_controller_number(gadget);
	if (gcnum < 0) {
		/* gmidi is so simple (no altsettings) that
		 * it SHOULD NOT have problems with bulk-capable hardware.
		 * so warn about unrecognized controllers, don't panic.
		 */
		pr_warning("%s: controller '%s' not recognized\n",
			   __func__, gadget->name);
		device_desc.bcdDevice = cpu_to_le16(0x9999);
	} else {
		device_desc.bcdDevice = cpu_to_le16(0x0200 + gcnum);
	}

	status = usb_add_config(cdev, &midi_config, midi_bind_config);
	if (status < 0)
		return status;

	pr_info("%s\n", longname);
	return 0;
}

static struct usb_composite_driver midi_driver = {
	.name		= (char *) longname,
	.dev		= &device_desc,
	.strings	= dev_strings,
	.max_speed	= USB_SPEED_HIGH,
	.unbind		= __exit_p(midi_unbind),
};

static int __init midi_init(void)
{
	return usb_composite_probe(&midi_driver, midi_bind);
}
module_init(midi_init);

static void __exit midi_cleanup(void)
{
	usb_composite_unregister(&midi_driver);
}
module_exit(midi_cleanup);

