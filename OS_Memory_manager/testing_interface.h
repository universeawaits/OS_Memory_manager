#include <Windows.h>

#define __CLEAR_CONSOLE_CONTENT system("cls")
#define __PRINT_UNCORRECT_CHOOSE_WARN printf("   Choose a right variant. ")
#define __SLEEP_SHORT printf("Waiting..."); Sleep(1000);
#define __SLEEP_LONG printf("Waiting..."); Sleep(5000);
#define __PRINT_CHOOSE_PROMPT printf(">  Your choose: ")

int choose;

void print_init_test_menu ();
void print_main_menu ();
void print_malloc_test_menu ();
void print_write_test_menu ();
void print_read_test_menu ();