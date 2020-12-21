#include <stdio.h>

enum DoWyborcow {WIADOMOSC_DO_WYBORCOW_X, WIADOMOSC_DO_WYBORCOW_Y, WIADOMOSC_DO_WYBORCOW_Z};

struct wiadomsc
{
    union Przekaz{
    char wiad1[1000];
    char wiad2[1000];
    char wiad3[1000];
}Wiadomosc;
    enum DoWyborcow Typ;
}WIADOMOSC_DO_WYBORCOW;


int main()
{

    return 0;
}
