#include "main.h"

void switchToNintendo() {
    // TODO - Switch to Nintendo URLs
}

void switchToRetendo() {
    // TODO - Switch to Retendo URLs
}

int main(int argc, char *argv[]) {
    gfxInitDefault();
    consoleInit(GFX_TOP, NULL);

    printf("Welcome to Retendo Patcher for 3DS !");
    printf("Press A to use Nintendo Server.");
    printf("Press X to use Retendo Server.");

    while (aptMainLoop()) {
        hidScanInput();

        u32 kDown = hidKeysDown();

        if (kDown & KEY_A) {
            switchToNintendo();
        }else if (kDown & KEY_X) {
            switchToRetendo();
        } else if (kDown & KEY_START) {
            break;
        }

        gfxFlushBuffers();
        gfxSwapBuffers();
        gspWaitForVBlank();
    }

    gfxExit();
    return 0;
}