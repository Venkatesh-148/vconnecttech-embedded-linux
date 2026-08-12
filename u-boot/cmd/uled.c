#include <common.h>
#include <command.h>
#include <asm/arch/imx-regs.h>
#include <asm/arch/iomux.h>
#include <asm/arch/clock.h>
#include <asm/io.h>
#include <asm/gpio.h>
#include <linux/delay.h>

/*
 * LED GPIO
 */
#define LED_D12		IMX_GPIO_NR(5, 1)
#define LED_D13		IMX_GPIO_NR(5, 2)

/*
 * LED states
 */
#define LED_ON		1
#define LED_OFF	0
#define LED_BLINK	2

#define MAX_ARGS	3


/*
 * LED parameters
 */
struct led_params {
	unsigned int led_no;
	unsigned int led_state;
};


/*
 * Check parameters
 */
static int check_params(int argc, char *const argv[],
			struct led_params *led_par)
{
	if (argc != MAX_ARGS) {
		printf("Usage: uled <1|2> <on|off|blink>\n");
		return false;
	}

	/*
	 * LED number
	 */
	if (strcmp(argv[1], "1") == 0) {
		led_par->led_no = 1;
	}
	else if (strcmp(argv[1], "2") == 0) {
		led_par->led_no = 2;
	}
	else {
		printf("Invalid LED number\n");
		return false;
	}

	/*
	 * LED state
	 */
	if (strcmp(argv[2], "on") == 0) {
		led_par->led_state = LED_ON;
	}
	else if (strcmp(argv[2], "off") == 0) {
		led_par->led_state = LED_OFF;
	}
	else if (strcmp(argv[2], "blink") == 0) {
		led_par->led_state = LED_BLINK;
	}
	else {
		printf("Invalid state\n");
		printf("Use: on / off / blink\n");
		return false;
	}

	return true;
}


/*
 * Get LED GPIO
 */
static int get_led_gpio(unsigned int led_no)
{
	if (led_no == 1)
		return LED_D12;

	if (led_no == 2)
		return LED_D13;

	return -1;
}


/*
 * Initialize LED
 */
static int init_led(unsigned int led_no)
{
	int gpio;
	int ret;

	gpio = get_led_gpio(led_no);

	if (gpio < 0)
		return -1;

	/*
	 * Request GPIO
	 */
	ret = gpio_request(gpio, "uled");

	if (ret) {
		/*
		 * GPIO may already be requested.
		 * Continue and try to configure it.
		 */
		printf("GPIO already requested\n");
	}

	/*
	 * Configure as output
	 */
	ret = gpio_direction_output(gpio, 0);

	if (ret) {
		printf("GPIO direction failed\n");
		return ret;
	}

	return 0;
}


/*
 * LED ON
 */
static void led_on(unsigned int led_no)
{
	int gpio;

	gpio = get_led_gpio(led_no);

	if (gpio < 0)
		return;

	gpio_set_value(gpio, 1);
}


/*
 * LED OFF
 */
static void led_off(unsigned int led_no)
{
	int gpio;

	gpio = get_led_gpio(led_no);

	if (gpio < 0)
		return;

	gpio_set_value(gpio, 0);
}


/*
 * LED BLINK
 */
static void led_blink(unsigned int led_no)
{
	while (1) {

		led_on(led_no);

		mdelay(200);

		led_off(led_no);

		mdelay(200);
	}
}


/*
 * U-Boot LED command
 */
static int do_user_led(cmd_tbl_t *cmdtp,
		       int flag,
		       int argc,
		       char *const argv[])
{
	struct led_params led_par;

	/*
	 * Check parameters
	 */
	if (!check_params(argc, argv, &led_par))
		return CMD_RET_USAGE;

	/*
	 * Initialize selected LED
	 */
	if (init_led(led_par.led_no))
		return CMD_RET_FAILURE;

	/*
	 * LED ON
	 */
	if (led_par.led_state == LED_ON) {

		led_on(led_par.led_no);

		printf("LED %d ON\n", led_par.led_no);
	}

	/*
	 * LED OFF
	 */
	else if (led_par.led_state == LED_OFF) {

		led_off(led_par.led_no);

		printf("LED %d OFF\n", led_par.led_no);
	}

	/*
	 * LED BLINK
	 */
	else if (led_par.led_state == LED_BLINK) {

		printf("LED %d BLINK\n", led_par.led_no);

		led_blink(led_par.led_no);
	}

	return CMD_RET_SUCCESS;
}


/*
 * U-Boot command
 */
U_BOOT_CMD(
	uled,
	3,
	0,
	do_user_led,
	"control VIYARA LED",
	"<1|2> <on|off|blink>\n"
	"    1 on      - D12 ON\n"
	"    1 off     - D12 OFF\n"
	"    1 blink   - D12 BLINK\n"
	"    2 on      - D13 ON\n"
	"    2 off     - D13 OFF\n"
	"    2 blink   - D13 BLINK"
);
