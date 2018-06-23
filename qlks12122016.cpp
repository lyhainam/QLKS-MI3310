#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#include <stdlib.h>

FILE *f = fopen("khachsan.txt","r+");

typedef struct date{
	int d,m,y;
} date;

typedef struct khachhang
{
	char ht[30], ngaysinh[15], cmnd[13];
	date ngaydi, ngayve;
} khachhang;

typedef struct phong
{
	char loai[10]; //batdau[15];
	int trangthai,sophong,sogiuong;
	khachhang kh;
} phong;

typedef struct node
{
	phong data;
	node *next;
} node;



void graphic()
{
	int i, j;
	char x = 0xF0;
	for(j = 1; j <= 2; j++)
	{
		printf("\n            <|                 |");
	}
	printf("\n             |                @@@                |>>");
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


node* phanloaiphong(int i) //tao phong moi dua tren so i
{	
	node *x;
	x = (node *) malloc (sizeof(node)); 
	if ((i%10==0)||(i%10==9))
	strcpy(x->data.loai,"VIP");
	else strcpy(x->data.loai,"Thuong");
	if (i%10<5) x->data.sogiuong = 1;
	else x->data.sogiuong  = 2;	
//	x->data.sophong = (i/10 + 1)*100 + (i%10 + 1);
//	x->data.trangthai = 0;
	x->next = NULL;
	return x;
}


node* timcuoi(node *head) //tim node cuoi cung trong danh sach lien ket 
{
	node *p = head;	
	if (p==NULL) return NULL;
	while(p->next != NULL)
	{
		p = p->next;	
	}
	return p;
}


void addlast(node* &head, node *n) //them 1	 node vao cuoi danh sach
{
	node *p;
	if(head==NULL)
	{
		head = n;
	}
	else
	{
		p = timcuoi(head);
		p->next = n;
	}
}


void phanloailist(node* &head) //phan loai phong cho ca khach san 
{
	int i;
	node *p;
	for (i=0;i<90;i++)
	{
		p = phanloaiphong(i);
		fscanf(f,"%d-%d\n",&p->data.sophong,&p->data.trangthai);
		addlast(head,p);	
	//	fprintf(f,"%d-%d\n",p->data.sophong,p->data.trangthai);
	}
}

void thuetraphong(int i, int j)
{	
	int x,y;
	rewind(f);
	do{
		fscanf(f,"%d-%d\n",&x,&y);
	}while(x!=i);
//	printf("%d",x);
	fseek(f,-3,SEEK_CUR);
	fprintf(f,"%d\n",j);
}


node* duyet(node* head, int i) //tim phong theo so phong
{
	node* p = head;
	while (p!=NULL)
	{
		if (p->data.sophong == i)
		return p;
		p = p->next;		
	}
	return NULL;	
}


void tratruoc(node *p) 
{
	printf("\nSo tien tra truoc cua quy khach la: ");
	if (p->data.sogiuong==1)
	{
		if (strcmp(p->data.loai,"VIP")==0) printf("250k");
			else printf("150k");
	}
	else
	{
		if (strcmp(p->data.loai,"VIP")==0) printf("450k");
			else printf("300k");
	}
}


void thue(node* &head, int i) //thue phong theo so phong
{
	node *p;
	do{
		printf("\nChon phong so: ");
		scanf("%d",&i);
		p = duyet(head,i);
		if (p==NULL) printf("\nSo phong khong hop le, moi chon lai\n"); 
		else if (p->data.trangthai==1) printf("\nPhong da co nguoi thue, moi quy khach chon lai\n");
	} while ((p==NULL)||(p->data.trangthai==1));
	printf("\nMoi quy khach lam thu tuc nhan phong...\n");
	getch();
	system("cls");
	printf("\nNhap ho ten khach hang: "); fflush(stdin);	
	gets(p->data.kh.ht);
	printf("\nNhap So CMND: ");	fflush(stdin);
	gets(p->data.kh.cmnd);
	printf("\nNhap ngay sinh (VD:01/01/97): ");	fflush(stdin);	
	gets(p->data.kh.ngaysinh);
	do {
		printf("\nThoi gian thue bat dau tu ngay (dd/mm/yyyy): "); scanf("%d/%d/%d",&p->data.kh.ngaydi.d,&p->data.kh.ngaydi.m,&p->data.kh.ngaydi.y);
	} while ((p->data.kh.ngaydi.m<1||p->data.kh.ngaydi.m>12)&&(p->data.kh.ngaydi.d<1||p->data.kh.ngaydi.d>31));
	
	/*printf("\nNhap thoi gian (ngay): ");
	scanf("%d",&p->data.kh.thoigian);
	printf("\nBat dau tu ngay (VD:01/01/16): ");fflush(stdin);	
	gets(p->data.batdau);*/
	p->data.trangthai = 1;
	printf("\nKhach hang %s da dat phong %d thanh cong.\n",p->data.kh.ht,i);
	/*printf("\nSo tien dat coc cua qui khach la: ");	
	if (p->data.sogiuong==1){
		if (strcmp(p->data.loai,"VIP")==0) printf("250k");
		else printf("150k");
	}
	else 	if (strcmp(p->data.loai,"VIP")==0) printf("450k");
			else printf("300k");*/
	
	tratruoc(p);
	thuetraphong(i,1);
	
	getch();
}


void ptrong(node *head)
{
	node *p;
	p = head;
	int dem = 0, i = 0;
	while (p->next!=NULL) {
		if (p->data.trangthai==0)
		dem++;
		p = p->next;
	}
	printf("\n\t\t     PRICE LIST\n");
	printf("\n+------------------------------------------------+");
	printf("\n|%30s%18s|","VIP","Thuong");
	printf("\n|------------------------------------------------|");
	printf("\n|%15s%15s%18s|","1 giuong","500k","300k");
	printf("\n|------------------------------------------------|");
	printf("\n|%15s%15s%18s|","2 giuong","900k","550k");
	printf("\n+------------------------------------------------+\n");
 	p = head;
	if(dem != 0)
	{
		printf("\nDanh sach cac phong trong:\n\n");
		printf("\n%18s%31s\n","1 giuong","2 giuong");
		printf("----------------------------   ----------------------------");
		printf("\n%4s%30s%24s","VIP","Thuong","VIP");
		printf("\n-----    ------------------------------------------   -----\n");
		
		while (p!=NULL)
		{
			if (p->data.trangthai==0)
			printf("|%3d|",p->data.sophong);
			else printf("|   |");
			if ((i%10==0)||(i%10==8)||(i%10==4)) printf("   ");
			if (i%10==9) printf("\n\n");
			p = p -> next;
			i++;
		}
	}
	else printf("\nKhong con phong trong, mong quy khach thong cam!\n");
}


int thoigianthue(int yyyy, int mm, int dd)
{
	if (mm < 3)
	{
    	yyyy--;
		mm += 12;
	}
	return 365*yyyy + yyyy/4 - yyyy/100 + yyyy/400 + (153*mm-457)/5 + dd - 306;
}


void thanhtoan(node *p)
{
	int d1, d2, m1, m2, y1, y2, songay;
	do {
		printf("\n========================================\n");
		printf("\nBieu muc thanh toan khach hang\n");
		printf("\nNgay quy khach bat dau thue phong: %d/%d/%d",p->data.kh.ngaydi.d,p->data.kh.ngaydi.m,p->data.kh.ngaydi.y);
		do {
			printf("\nNgay quy khach tra phong: "); scanf("%d/%d/%d",&p->data.kh.ngayve.d,&p->data.kh.ngayve.m,&p->data.kh.ngayve.y);
		} while ((p->data.kh.ngayve.m<1||p->data.kh.ngayve.m>12)&&(p->data.kh.ngayve.d<1||p->data.kh.ngayve.d>31));
		songay = thoigianthue(p->data.kh.ngayve.y,p->data.kh.ngayve.m,p->data.kh.ngayve.d) - thoigianthue(p->data.kh.ngaydi.y,p->data.kh.ngaydi.m,p->data.kh.ngaydi.d);
		printf("\nThoi gian quy khach da thue phong la: %d ngay.\n",songay);
		getch();	
	} while (songay < 0);
	
	printf("\n========================================\n");
	if (songay == 0)
	{
		tratruoc(p);
		printf("\n\nSo tien quy khach can thanh toan them la: %d");
		getch();
	}
	else
	{
		printf("\nSo tien quy khach can thanh toan theo don gia la: ");
		if (p->data.sogiuong==1)
		{
			if (strcmp(p->data.loai,"VIP")==0) printf("%dk",songay*500);
				else printf("%dk",songay*300);
		}
		else
		{
			if (strcmp(p->data.loai,"VIP")==0) printf("%dk",songay*900);
				else printf("%dk",songay*550);
		}
		getch();
		//
		printf("\n\nSo tien quy khach da dat coc: ");	
		if (p->data.sogiuong==1)
		{
			if (strcmp(p->data.loai,"VIP")==0) printf("250k");
				else printf("150k");
		}
		else
		{
			if (strcmp(p->data.loai,"VIP")==0) printf("450k");
				else printf("300k");
		}
		printf("\n");
		getch();
		//
		printf("\n========================================\n");
		printf("\nQuy khach can thanh toan them: ");	
		if (p->data.sogiuong==1)
		{
			if (strcmp(p->data.loai,"VIP")==0) printf("%dk",songay*500-250);
				else printf("%dk",songay*300-150);
		}
		else
		{
			if (strcmp(p->data.loai,"VIP")==0) printf("%dk",songay*900-450);
				else printf("%dk",songay*550-300);
		}
		getch();
	}
	p->data.trangthai = 0;
	printf("\n\n========================================\n\n");
	printf("Cam on quy khach da lua chon dich vu cua khach san. Kinh chao tam biet quy khach!");
}


void tra(node *head, int i)
{
	node *p = head;
	printf("\nNhap phong tra: ");
	scanf("%d",&i);
	p = duyet(head,i);
	if(p==NULL)
	{
		printf("\nSo phong khong hop le!");
	}
	else if (p->data.trangthai == 0)
	{
		printf("\nPhong %d chua duoc dang ky thue",p->data.sophong);
	}
	else 
	{
		printf("\nMoi quy khach lam thu tuc thanh toan...\n");
		thanhtoan(p);
	}
		thuetraphong(i,0);
	getch();
}


void thongtin(node *head, int i)
{
	node *p = head;
	do {
		printf("\nChon phong quy khach can xem thong tin: ");
		scanf("%d",&i);
		p = duyet(head,i);
		if (p == NULL)
		{
			printf("\nSo phong khong hop le!\n");
			getch();
			system("cls");
		}
	} while (p == NULL);
	if(p->data.trangthai == 1)
	{
		printf("\nThong Tin Phong %d:\n",p->data.sophong);
		printf("\n%-20s%-20s%-20s%-20s","So phong","Loai phong","So giuong","Trang thai");
		printf("\n%-20d%-20s%-20d%-20s",p->data.sophong,p->data.loai,p->data.sogiuong,"Dang cho thue");
		printf("\n\nThong Tin Khach Hang:\n");
		printf("\n%-20s%-20s%-20s","Ho Va Ten","So CMND","Ngay Sinh"/*"Thoi Gian Thue"*/);
		printf("\n%-20s%-20s%-20s",p->data.kh.ht,p->data.kh.cmnd,p->data.kh.ngaysinh);
		getch();
	}
	else
	{
		printf("\nThong Tin Phong %d:\n",p->data.sophong);
		printf("\n%-20s%-20s%-20s%-20s","So phong","Loai phong","So giuong","Trang thai");
		printf("\n%-20d%-20s%-20d%-20s",p->data.sophong,p->data.loai,p->data.sogiuong,"Con trong");
		getch();
	} 
}



int main()
{
	int a,i;
	node *head = NULL;
//	FILE *f = fopen("khachsan.txt","r");
	phanloailist(head);
	do {
		system("cls");
		graphic();
		printf("\nCHAO MUNG QUY KHACH DEN VOI KHACH SAN. HAN HANH DUOC PHUC VU QUY KHACH.\n\n");
		printf("----------------------------------------------------------------------\n");
		printf("||1. Dat phong||");
		printf("||2. Xem thong tin phong||");
		printf("||3. Tra phong||");
		printf("||4. Thoat||\n");
		printf("----------------------------------------------------------------------\n");
		printf("\n");
		fflush(stdin);
		printf("Moi quy khach yeu cau: ");
		scanf("%d",&a);		
		switch(a)
		{
			case 1:
				ptrong(head);
				thue(head,i);
				break;
			case 2:
				system("cls");
				thongtin(head,i);
				break;
 			case 3:
				system("cls");
				tra(head,i);
			 	break;
			case 4:
				printf("\nKINH CHAO TAM BIET QUY KHACH.");
				break;
			default:
				printf("\nYeu cau khong hop le!");
				getch();
				break;	
		} 
	} while(a != 4);
	fclose(f);
	getch();
	return 0;	
}
