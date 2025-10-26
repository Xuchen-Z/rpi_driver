#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/leds.h>
#include <linux/delays.h>
#include <linux/error.h>

static struct led_classdev *act_led;

// predefined macro: __init, will be cleaned after first execution
static int __init led_init(void) {
    printk(KERN_INFO "ACT LED model init\n");
    
    act_led = led_classdev_find("ACT");
    if (!act_led) {
        printk(KERN_INFO "ACT LED not found\n");
        // return device not found error code
        return -ENODEV;
    }

    for (int i = 0; i < 5; i++) {
        // ON
        led_set_brightness(act_led, 255);
        msleep(500);
        // OFF
        led_set_brightness(act_led, 0);
        msleep(500);
    }

    return 0;
}

static void __exit led_exit(void) {
    printk(KERN_INFO "ACT LED model exit\n");
    if (act_led)
        led_set_brightness(act_led, 0);
}

module_init(led_init);
module_exit(led_exit);

MODULE_LICENSE("GPL");