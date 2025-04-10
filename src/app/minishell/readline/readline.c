#include "minilib.h"
#include "readline.h"
#include "platform.h"

#define MAX_HISTORY 100
#define MAX_LINE_LEN 256

static char history[MAX_HISTORY][MAX_LINE_LEN];
static int history_count = 0;
static int history_pos = 0;

void add_history(const char *line) {
  if (history_count < MAX_HISTORY) {
    strcpy(history[history_count], line);
    history_count++;
  } else {
    // If history is full, remove the oldest record
    for (int i = 0; i < MAX_HISTORY - 1; i++) {
      strcpy(history[i], history[i + 1]);
    }
    strcpy(history[MAX_HISTORY - 1], line);
  }
  history_pos = history_count;
}

char *readline(const char *prompt) {
  static char line[MAX_LINE_LEN];
  int pos = 0;
  char c;

  printf("%s", prompt);
  
  while (1) {
    // Wait for any character
    while (!stdio_has_char()) {
      // Do nothing, just wait
    }
    
    c = stdio_popc();
    
    // Handle enter key
    if (c == '\n' || c == '\r') {
      printf("\n");
      line[pos] = '\0';
      if (pos > 0) {
        add_history(line);
      }
      return pos > 0 ? line : NULL;
    }
    
    // Handle backspace
    if (c == '\b' || c == 127) {
      if (pos > 0) {
        pos--;
        printf("\b \b");
      }
      continue;
    }
    
    // Handle up arrow (history)
    if (c == 27) {  // ESC
      if (stdio_has_char()) {
        c = stdio_popc();
        if (c == '[') {
          if (stdio_has_char()) {
            c = stdio_popc();
            if (c == 'A') {  // Up arrow
              if (history_pos > 0) {
                history_pos--;
                // Clear current line
                for (int i = 0; i < pos; i++) {
                  printf("\b \b");
                }
                strcpy(line, history[history_pos]);
                pos = strlen(line);
                printf("%s", line);
              }
              continue;
            }
            if (c == 'B') {  // Down arrow
              if (history_pos < history_count) {
                history_pos++;
                // Clear current line
                for (int i = 0; i < pos; i++) {
                  printf("\b \b");
                }
                if (history_pos < history_count) {
                  strcpy(line, history[history_pos]);
                  pos = strlen(line);
                  printf("%s", line);
                } else {
                  pos = 0;
                  line[0] = '\0';
                }
              }
              continue;
            }
          }
        }
      }
    }
    
    // Handle normal characters
    if (pos < MAX_LINE_LEN - 1 && c >= 32 && c <= 126) {
      line[pos++] = c;
      printf("%c", c);
    }
  }
}

