#include <stdio.h>
#include <command.h>
static int do_hello(cmd_tbl_t *cmdtp, int flag, int argc, char *const argv[])
{
	printf("Hello - imx boot!\n");
	return 0;
}

//U_BOOT_CMD( hello, 1, 0, do_hello, "say hello to uboot");
U_BOOT_CMD(
    hello,          /* command name */
    1,              /* max arguments */
    0,              /* repeatable */
    do_hello,       /* command function */
    "say hello to uboot", /* short description */
    "              /* help */"
);
