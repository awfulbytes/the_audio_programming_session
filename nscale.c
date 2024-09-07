#include <stdio.h>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("usage: nscale notes_number midinote\n");
        return 1;
    }

    int notes, midinote;

    notes = atoi(argv[1]);

    if (notes < 1) {
        printf("Error: Notes number must be positive and bigger than 0\n");
        return 1;
    }

    if (notes > 24) {
        printf("Error: Notes number must be at max = 24\n");
        return 1;
    }

    midinote = atoi(argv[2]);

    if (midinote < 0) {
        printf("Error: Cannot have negative Midi Notes!\n");
        return 1;
    }

    if (midinote > 127) {
        printf("Error: Maximum Midi Note is 127\n");
        return 1;
    }
    return 0;
}
