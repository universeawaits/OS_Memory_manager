#include "testing_interface.h"
#include "unit_test.h"

#include <stdio.h>
#include <stdlib.h>

void print_init_test_menu()
{
	__CLEAR_CONSOLE_CONTENT;
	printf(" -------------------------------\n");
	printf("|  INITIALIGING\t\t\t|\n");
	printf(" -------------------------------\n");
	printf("|  1. Init with correct params\t|\n|  2. Init with wrong params\t|\n|  3. Init with unknown error\t|\n");
	printf(" -------------------------------\n");
	__PRINT_CHOOSE_PROMPT;

	scanf_s("%d", &choose);
	fflush(stdin);

	switch (choose)
	{
	case 1:
	{
		test_init__success();
		printf("   Number of pages where %d, page size where %d. ", n, szPage);
		__SLEEP_LONG;
		print_main_menu ();
		break;
	}
	case 2:
	{
		test_init__wrong_params();
		printf("   Number of pages where %d, page size where %d. ", n, szPage);
		__SLEEP_LONG;
		print_init_test_menu();
		break;
	}
	case 3:
	{
		test_init__unknown_err();
		printf("   Number of pages where %d, page size where %d. ", n, szPage);
		__SLEEP_LONG;
		print_init_test_menu();
		break;
	}
	default:
	{
		__PRINT_UNCORRECT_CHOOSE_WARN;
		__SLEEP_SHORT;
		print_init_test_menu();
		break; // а что если его убрать?
	}
	}
}

void print_main_menu()
{
	__CLEAR_CONSOLE_CONTENT;
	printf(" -------------------------------\n");
	printf("|  TESTING MENU\t\t\t|\n");
	printf(" -------------------------------\n");
	printf("|  1. _malloc()\ttests\t\t|\n|  2. _read()\ttests\t\t|\n|  3. _write()\ttests\t\t|\n");
	printf(" -------------------------------\n");
	printf("|  0. Exit\t\t\t|\n");
	printf(" -------------------------------\n");
	__PRINT_CHOOSE_PROMPT;

	scanf_s("%d", &choose);
	fflush(stdin);

	switch (choose)
	{
	case 1:
	{
		print_malloc_test_menu ();
		break;
	}
	case 2:
	{
		print_write_test_menu ();
		break;
	}
	case 3:
	{
		print_read_test_menu();
		break;
	}
	case 0:
	{
		exit(0);
	}
	default:
	{
		__PRINT_UNCORRECT_CHOOSE_WARN;
		__SLEEP_SHORT;
		print_main_menu();
		break; //  а что если его убрать?
	}
	}
}

void print_malloc_test_menu ()
{
	__CLEAR_CONSOLE_CONTENT;
	printf(" -------------------------------\n");
	printf("|  MALLOC TESTING\t\t|\n");
	printf(" -------------------------------\n");
	printf("|  1. With success\t\t|\n|  2. With wrong params\t\t|\n");
	printf("|  3. With memory lack\t\t|\n|  4. With unknown error\t|\n");
	printf(" -------------------------------\n");
	printf("|  0. Exit\t\t\t|\n| -1. Back\t\t\t|\n");
	printf(" -------------------------------\n");
	__PRINT_CHOOSE_PROMPT;

	scanf_s("%d", &choose);
	fflush(stdin);

	switch (choose)
	{
	case 1:
	{
		test_malloc__success ();
		printf("   Size of new segment is %d, segment starting adress is %p. ", size, *out_ptr);
		__SLEEP_LONG;
		print_malloc_test_menu ();
		break;
	}
	case 2:
	{
		test_malloc__wrong_params ();
		printf("   Size of new segment may be %d, but it's greater than VAS size. ", size);
		__SLEEP_LONG;
		print_malloc_test_menu ();
		break;
	}
	case 3:
	{
		test_malloc__memory_lack();
		printf("   Size of new segment may be %d, but it's greater than VAS free place size. ", size);
		__SLEEP_LONG;
		print_malloc_test_menu();
		break;
	}
	case 4:
	{
		test_malloc__unknown_err();
		__SLEEP_LONG;
		print_malloc_test_menu();
		break;
	}
	case 0:
	{
		exit(0);
	}
	case -1:
	{
		print_main_menu();
		break;
	}
	default:
	{
		__PRINT_UNCORRECT_CHOOSE_WARN;
		__SLEEP_SHORT;
		print_malloc_test_menu();
		break; // а что если его убрать?
	}
	}
}

void print_write_test_menu()
{

}

void print_read_test_menu()
{

}
