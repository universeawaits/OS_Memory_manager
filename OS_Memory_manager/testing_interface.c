#include "testing_interface.h"
#include "unit_test.h"
#include "adress_spaces.h"

#include <stdio.h>
#include <stdlib.h>

//void print_init_test_menu ()
//{
//	__CLEAR_CONSOLE_CONTENT;
//	printf(" -------------------------------\n");
//	printf("|  INITIALIGING\t\t\t|\n");
//	printf(" -------------------------------\n");
//	printf("|  1. Init with correct params\t|\n|  2. Init with wrong params\t|\n|  3. Init with unknown error\t|\n");
//	printf(" -------------------------------\n");
//	__PRINT_CHOOSE_PROMPT;
//
//	scanf_s("%d", &choose);
//	fflush(stdin);
//
//	switch (choose)
//	{
//	case 1:
//	{
//		test_init__success();
//		printf("   Number of pages where %d, page size where %d. ", n, szPage);
//		__SLEEP_LONG;
//		print_main_menu ();
//		break;
//	}
//	case 2:
//	{
//		test_init__wrong_params();
//		printf("   Number of pages where %d, page size where %d. ", n, szPage);
//		__SLEEP_LONG;
//		print_init_test_menu();
//		break;
//	}
//	case 3:
//	{
//		test_init__unknown_err();
//		printf("   Number of pages where %d, page size where %d. ", n, szPage);
//		__SLEEP_LONG;
//		print_init_test_menu();
//		break;
//	}
//	default:
//	{
//		__PRINT_UNCORRECT_CHOOSE_WARN;
//		__SLEEP_SHORT;
//		print_init_test_menu();
//		break; // а что если его убрать?
//	}
//	}
//}
//
//void print_main_menu ()
//{
//	__CLEAR_CONSOLE_CONTENT;
//	printf(" -------------------------------\n");
//	printf("|  TESTING MENU\t\t\t|\n");
//	printf(" -------------------------------\n");
//	printf("|  1. _malloc()\ttests\t\t|\n|  2. _free()\ttests\t\t|\n");
//	printf("|  3. _read()\ttests\t\t|\n|  4. _write()\ttests\t\t|\n");
//	printf(" -------------------------------\n");
//	printf("|  0. Exit\t\t\t|\n");
//	printf("| -2. Print VAS\t\t\t|\n| -3. Print PAS\t\t\t|\n");
//	printf(" -------------------------------\n");
//	__PRINT_CHOOSE_PROMPT;
//
//	scanf_s("%d", &choose);
//	fflush(stdin);
//
//	switch (choose)
//	{
//	case -3:
//	{
//		_print_space(_pas, _pas_size, _PAS_NAME);
//		__WAIT_FOR_CONTINUE;
//		print_main_menu();
//		break;
//	}
//	case -2:
//	{
//		_print_space(_vas, _vas_size, _VAS_NAME);
//		__WAIT_FOR_CONTINUE;
//		print_main_menu();
//		break;
//	}
//	case 1:
//	{
//		print_malloc_test_menu ();
//		break;
//	}
//	case 2:
//	{
//		print_free_test_menu ();
//		break;
//	}
//	case 3:
//	{
//		print_read_test_menu();
//		break;
//	}
//	case 4:
//	{
//		print_write_test_menu();
//		break;
//	}
//	case 0:
//	{
//		exit(0);
//	}
//	default:
//	{
//		__PRINT_UNCORRECT_CHOOSE_WARN;
//		__SLEEP_SHORT;
//		print_main_menu();
//		break; //  а что если его убрать?
//	}
//	}
//}
//
//void print_malloc_test_menu ()
//{
//	__CLEAR_CONSOLE_CONTENT;
//	printf(" -------------------------------\n");
//	printf("|  MALLOC TESTING\t\t|\n");
//	printf(" -------------------------------\n");
//	printf("|  1. With success\t\t|\n|  2. With wrong params\t\t|\n");
//	printf("|  3. With memory lack\t\t|\n|  4. With unknown error\t|\n");
//	printf(" -------------------------------\n");
//	printf("|  0. Exit\t\t\t|\n| -1. Back\t\t\t|\n");
//	printf("| -2. Print VAS\t\t\t|\n| -3. Print PAS\t\t\t|\n");
//	printf(" -------------------------------\n");
//	__PRINT_CHOOSE_PROMPT;
//
//	scanf_s("%d", &choose);
//
//	switch (choose)
//	{
//	case -3:
//	{
//		_print_space(_pas, _pas_size, _PAS_NAME);
//		__WAIT_FOR_CONTINUE;
//		print_malloc_test_menu();
//		break;
//	}
//	case -2:
//	{
//		_print_space(_vas, _vas_size, _VAS_NAME);
//		__WAIT_FOR_CONTINUE;
//		print_malloc_test_menu();
//		break;
//	}
//	case 1:
//	{
//		test_malloc__success ();
//		printf("   Size of new segment is %d, segment starting adress is %p. ", size, *out_ptr);
//		__SLEEP_LONG;
//		print_malloc_test_menu ();
//		break;
//	}
//	case 2:
//	{
//		test_malloc__wrong_params ();
//		printf("   Size of new segment may be %d, but it's greater than VAS size. ", size);
//		__SLEEP_LONG;
//		print_malloc_test_menu ();
//		break;
//	}
//	case 3:
//	{
//		test_malloc__memory_lack();
//		printf("   Size of new segment may be %d, but it's greater than VAS free place size. ", size);
//		__SLEEP_LONG;
//		print_malloc_test_menu();
//		break;
//	}
//	case 4:
//	{
//		test_malloc__unknown_err();
//		__SLEEP_LONG;
//		print_malloc_test_menu();
//		break;
//	}
//	case 0:
//	{
//		exit(0);
//	}
//	case -1:
//	{
//		print_main_menu();
//		break;
//	}
//	default:
//	{
//		__PRINT_UNCORRECT_CHOOSE_WARN;
//		__SLEEP_SHORT;
//		print_malloc_test_menu();
//		break; // а что если его убрать?
//	}
//	}
//}
//
//void print_free_test_menu () {
//	__CLEAR_CONSOLE_CONTENT;
//	printf(" -------------------------------\n");
//	printf("|  FREE TESTING\t\t\t|\n");
//	printf(" -------------------------------\n");
//	printf("|  1. With success\t\t|\n|  2. With wrong params\t\t|\n");
//	printf("|  3. With unknown error\t|\n");
//	printf(" -------------------------------\n");
//	printf("|  0. Exit\t\t\t|\n| -1. Back\t\t\t|\n");
//	printf("| -2. Print VAS\t\t\t|\n| -3. Print PAS\t\t\t|\n");
//	printf(" -------------------------------\n");
//	__PRINT_CHOOSE_PROMPT;
//
//	scanf_s("%d", &choose);
//
//	switch (choose)
//	{
//	case -3:
//	{
//		_print_space(_pas, _pas_size, _PAS_NAME);
//		__WAIT_FOR_CONTINUE;
//		print_free_test_menu();
//		break;
//	}
//	case -2:
//	{
//		_print_space(_vas, _vas_size, _VAS_NAME);
//		__WAIT_FOR_CONTINUE;
//		print_free_test_menu();
//		break;
//	}
//	case 1:
//	{
//		test_free__success();
//		if (*freed_seg_starting_adress != NULL)
//		{
//			printf("   Freed segment adress (&VA) is %p, size was %d. ",
//				*freed_seg_starting_adress,
//				size);
//		}
//		else
//		{
//			printf("   There's no any segment in memory. ");
//		}
//		__SLEEP_LONG;
//		print_free_test_menu();
//		break;
//	}
//	case 2:
//	{
//		test_free__wrong_params();
//		printf	("   Segment starting adress (&VA) expected to be is %p, but there's no such segment. ",
//				*freed_seg_starting_adress);
//		__SLEEP_LONG;
//		print_free_test_menu();
//		break;
//	}
//	case 3:
//	{
//		test_free__unknown_err();
//		__SLEEP_LONG;
//		print_free_test_menu();
//		break;
//	}
//	case 0:
//	{
//		exit(0);
//	}
//	case -1:
//	{
//		print_main_menu();
//		break;
//	}
//	default:
//	{
//		__PRINT_UNCORRECT_CHOOSE_WARN;
//		__SLEEP_SHORT;
//		print_free_test_menu();
//		break; // а что если его убрать? // ничего
//	}
//	}
//}
//
//void print_write_test_menu ()
//{
//	__CLEAR_CONSOLE_CONTENT;
//	printf(" -------------------------------\n");
//	printf("|  WRITE TESTING\t\t|\n");
//	printf(" -------------------------------\n");
//	printf("|  1. With success\t\t|\n|  2. With wrong params\t\t|\n");
//	printf("|  3. With unknown error\t\n|  4. With segment violation\t|\n");
//	printf(" -------------------------------\n");
//	printf("|  0. Exit\t\t\t|\n| -1. Back\t\t\t|\n");
//	printf("| -2. Print VAS\t\t\t|\n| -3. Print PAS\t\t\t|\n");
//	printf(" -------------------------------\n");
//	__PRINT_CHOOSE_PROMPT;
//
//	scanf_s("%d", &choose);
//
//	switch (choose)
//	{
//	case -3:
//	{
//		_print_space(_pas, _pas_size, _PAS_NAME);
//		__WAIT_FOR_CONTINUE;
//		print_write_test_menu();
//		break;
//	}
//	case -2:
//	{
//		_print_space(_vas, _vas_size, _VAS_NAME);
//		__WAIT_FOR_CONTINUE;
//		print_write_test_menu();
//		break;
//	}
//	case 1:
//	{
//		test_write__success();
//		if (pBuffer != NULL)
//		{
//			printf("   Filled adress (&VA) is %p, size was %d, buffer was %c%c. ",
//				written, size, *pBuffer, *(pBuffer + 1));
//		}
//		else
//		{
//			printf("   There's no any segment in memory. ");
//		}
//		__SLEEP_LONG;
//		print_write_test_menu();
//		break;
//	}
//	case 2:
//	{
//		test_write__wrong_params();
//		if (pBuffer != NULL)
//		{
//			printf("   Filled adress (&VA) may be %p, but the size of buffer was 0. ", written);
//		}
//		else
//		{
//			printf("   There's no any segment in memory. ");
//		}
//		__SLEEP_LONG;
//		print_write_test_menu();
//		break;
//	}
//	case 3:
//	{
//		test_write__unknown_error();
//		__SLEEP_LONG;
//		print_write_test_menu();
//		break;
//	}
//	case 0:
//	{
//		exit(0);
//	}
//	case -1:
//	{
//		print_main_menu();
//		break;
//	}
//	default:
//	{
//		__PRINT_UNCORRECT_CHOOSE_WARN;
//		__SLEEP_SHORT;
//		print_write_test_menu();
//		break; // а что если его убрать? // ничего
//	}
//	}
//}
//
//void print_read_test_menu ()
//{
//
//}
