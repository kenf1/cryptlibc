#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "../src/cryptlibc.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  InitWindow(400, 200, "Cryptlibc GUI");
  SetTargetFPS(60);

  char inputText[256] = {0};     // input buffer for text box
  char encryptedText[256] = {0}; // buffer store encrypted result

  bool showMessageBox = false;

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

    GuiLabel((Rectangle){24, 4, 350, 20},
             "Enter text and press Enter to encrypt:");

    bool textBoxFocused = GuiTextBox((Rectangle){24, 24, 350, 30}, inputText,
                                     sizeof(inputText), true);

    if (textBoxFocused && IsKeyPressed(KEY_ENTER)) {
      CryptConfig cfg = {
          .version = "encrypt",
          .inputstr = inputText,
          .refstr =
              "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890",
          .offset = 1};

      char *encrypted = cryptlogic(&cfg);
      if (encrypted) {
        strncpy(encryptedText, encrypted, sizeof(encryptedText) - 1);
        encryptedText[sizeof(encryptedText) - 1] = '\0';

        free(encrypted);
        showMessageBox = true;
      } else {
        strncpy(encryptedText, "Encryption failed", sizeof(encryptedText) - 1);
        showMessageBox = true;
      }
    }

    // todo: option show directly
    // encrypted string in message box
    if (showMessageBox) {
      int result = GuiMessageBox((Rectangle){50, 70, 300, 120},
                                 "#191#Encrypted Text", encryptedText, "Close");
      if (result >= 0)
        showMessageBox = false;
    }

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
