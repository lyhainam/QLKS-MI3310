#include "dohoa.h"
#include "phong.h"

void menu(){	
	char a;
	int i;
	node *head = NULL;
	resetdoanhthu();
	phanloailist(head);
	do {
		system("cls");
		graphic();
		printf("\nCHAO MUNG QUY KHACH DEN VOI KHACH SAN. HAN HANH DUOC PHUC VU QUY KHACH.\n\n");
		printf("----------------------------------------------------------------------------------------------------------------------\n");
		printf("|| 1. Dat phong |");
		printf("| 2. Xem thong tin phong |");
		printf("| 3. Yeu cau dich vu |");
		printf("| 4. Tra phong |");
		printf("| 5. Bao cao doanh thu |");
		printf("| 6. Thoat ||\n");
		printf("----------------------------------------------------------------------------------------------------------------------\n");
		fflush(stdin);
		printf("\nMoi quy khach yeu cau: ");
		a = getch();
		printf("%c",a);	
		switch(a)
		{
			case 49:
				ptrong(head);
				getch();
				break;
			case 50:
				system("cls");
				thongtin(head);
				break;
			case 51:
				system("cls");
				giat(head);
				break;
 			case 52:
				system("cls");
				tra(head);
			 	break;
			case 53:
				baocao();
				break;
			case 54:
				break;
			default:
				printf("\nYeu cau khong hop le!");
				getch();
				break;
		} 
	} while(a != 54);
	fclose(f);
	fclose(g);
	fclose(r);
	free(head);
}
