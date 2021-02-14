#include "autoclick.h"

int main()
{
    int countdown = 3;

    Display *display = XOpenDisplay(NULL);
    if (display == NULL)
    {
        printf("Error on start!");
        return -1;
    }

    do
    {
        printf("%i\n", countdown);
        sleep(1);
        countdown--;
    } while (countdown > 0);
    printf("Already!!!\n");

    do
    {
        click(display, Button1);
        usleep(10000);
    } while (True);

    XCloseDisplay(display);
    return 0;
}