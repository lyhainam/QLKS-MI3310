#include <stdio.h>
#include <conio.h>
#include <ctime>

void graphic () //Hinh toa nha o giao dien dau tien.
{
	int i, j;
	char x = 0xF0;
	// Ham tính thoi gian thuc (Real-time function)
	time_t hientai = time(0);
	// Chuyen doi thoi gian thuc ve dang chuoi
	char* dt = ctime(&hientai);
	printf("\n     Local time (UTC + 7) at Hanoi: %s",dt);
	for(j = 1; j <= 2; j++)
	{
		printf("\n            <|                 |");
	}
	printf("\n             |                 @                 |>>");
	printf("\n             @                @@@                |");
	printf("\n            @@@              @@@@@               |");
	printf("\n          @@@@@@@            @@@@@               |");
	printf("\n         @@@@@@@@@          @@@@@@@              |");
	printf("\n           @@@@@            @@@@@@@              @");
	printf("\n          @@@@@@@            %c%c%c%c%c              @@@",x,x,x,x,x);
	printf("\n          %c%c%c%c%c%c%c            %c%c%c%c%c             @@@@@",x,x,x,x,x,x,x,x,x,x,x,x);
	printf("\n          %c%c%c%c%c%c%c            %c%c%c%c%c            @@@@@@@",x,x,x,x,x,x,x,x,x,x,x,x);
	printf("\n");
	for(j = 1; j <= 7; j++)
	{	
		printf("          %c%c%c%c%c%c%c------------%c%c%c%c%c------------%c%c%c%c%c%c%c      ",x,x,x,x,x,x,x,x,x,x,x,x,x,x,x,x,x,x,x);
		printf("\n");
	}
	printf("                _______________________________");
	printf("\n");
	printf("            _______________________________________");
	printf("\n");
	printf("        _______________________________________________");
	printf("\n\n\n");
	printf("\t\tNhan phim bat ky de tiep tuc...\n\n");
	getch();
}
