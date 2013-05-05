/* include/linux/touch_wake.h */

#ifndef _LINUX_TOUCH_WAKE_H
#define _LINUX_TOUCH_WAKE_H

#include <linux/input.h>

struct touchwake_implementation
{
    void (* enable)(void);
    void (* disable)(void);
};

void register_touchwake_implementation(struct touchwake_implementation * imp);

void powerkey_pressed(void);
void powerkey_released(void);
void proximity_detected(void);
void proximity_off(void);
void touch_press(void);
int get_touchoff_delay(void);
bool device_is_suspended(void);
void set_powerkeydev(struct input_dev * input_device);
void set_touch_wake_enabled(bool touchwake_enabled);
void set_s2w_enabled(bool s2w_enabled);
void set_touchoff_delay (int delay);

#endif
