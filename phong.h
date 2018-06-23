#include<string.h>
#include"type.h"
#include<stdlib.h>
#include<stdio.h>
#include<conio.h>

FILE *f = fopen("khachsan.txt","r+");
FILE *g = fopen("khachhang.txt","r+");
FILE *r = fopen("doanhthu.txt","r+");

node* phanloaiphong (int i) // tao phong moi dua tren so i su dung cap phat dong
{	
	node *x;
	x = (node *) malloc (sizeof(node)); 
	if ((i%10 == 0) || (i%10 == 9))
	strcpy(x->data.loai, "VIP");
	else strcpy(x->data.loai, "Thuong");
	if (i%10 < 5) x->data.sogiuong = 1;
	else x->data.sogiuong = 2;
	// Bang gia dat phong
	if (x->data.sogiuong == 1)
	{
		if (strcmp(x->data.loai, "VIP") == 0) x->data.dongia = 500000;
			else x->data.dongia = 300000;
	}
	else
	{
		if (strcmp(x->data.loai, "VIP") == 0) x->data.dongia = 900000;
			else x->data.dongia = 550000;
	}

	x->data.kh.di.tm_sec = 0;
	x->data.kh.di.tm_hour = 0;
	x->data.kh.di.tm_min = 0;	
	x->next = NULL;
	return x;
}


node* timcuoi (node *head) // Tim node cuoi cung trong danh sach lien ket
{
	node *p = head;	
	if (p == NULL) return NULL;
	while (p->next != NULL)
	{
		p = p->next;	
	}
	return p;
}


void addlast (node* &head, node *n) // Them 1 node vao cuoi danh sach
{
	node *p;
	if (head == NULL)
	{
		head = n;
	}
	else
	{
		p = timcuoi (head);
		p->next = n;
	}
}


void phanloailist (node* &head) // Phan loai phong cho ca khach san 
{
	int i;
	node *p;
	for (i = 0; i < 90; i++)
	{
		p = phanloaiphong (i);
		fscanf(f, "%d-%d\n", &p->data.sophong, &p->data.trangthai);
		fscanf(g, "%d-", &p->data.sophong);
		fgets(p->data.kh.ht, 29, g);
		fseek(g, 2, SEEK_CUR);
		fgets(p->data.kh.ngaysinh, 14, g);
		fseek(g, 2, SEEK_CUR);
		fgets(p->data.kh.cmnd, 12, g);
		fseek(g, 2, SEEK_CUR);
		fscanf(g, "%d/%d/%d-%d\n", &p->data.kh.di.tm_mday, &p->data.kh.di.tm_mon, &p->data.kh.di.tm_year, &p->data.kh.giat);
		addlast (head,p);	
	}
}

// Doc tu file va ghi vao file trang thai cua phong
void thuetraphong (int i, int j)
{	
	int x;
	rewind(f);
	char s[5];
	do {
		fscanf(f, "%d-%[^\n]\n", &x, s);
	} while(x != i);
	fseek(f, -3, SEEK_CUR);
	fprintf(f, "%d\n", j);
}


// Doc tu file va ghi vao file cac du lieu dat va tra phong
void inthongtin (int i, char ht[30], char ngaysinh[15], char cmnd[13], int x1, int x2, int x3, int x4)
{
	char s[100];
	int x, y;
	rewind(g);
	do {
		fscanf(g,"%d-%[^\n]\n",&x,&s);
	} while(x != i);
	y = 6 + strlen(s);
	fseek(g,-y,SEEK_CUR);
	fprintf(g,"%3d-%-29s-%-14s-%-12s-%02d/%02d/%03d-%02d\n",i,ht,ngaysinh,cmnd,x1,x2,x3,x4);
}


node* duyet (node* head, int i) // Tim phong theo so phong
{
	node* p = head;
	while (p != NULL)
	{
		if (p->data.sophong == i)
		return p;
		p = p->next;		
	}
	return NULL;	
}


float tratruoc (node *p) // Cai dat so tien tra truoc cho tung loai phong
{
	if (p->data.sogiuong == 1)
	{
		if (strcmp(p->data.loai, "VIP") == 0) return 250000;
			else return 150000;
	}
	else
	{
		if (strcmp(p->data.loai, "VIP") == 0) return 450000;
			else return 300000;
	}
}


void docdoanhthu (int i) // Doc doanh thu theo thang tu file doanhthu.txt
{
	int x;
	rewind(r);
	fseek(r, 5, SEEK_CUR);
	do {
		fscanf(r, "%d-%f-%f-%f\n", &x, &dt.tphong, &dt.tgiat, &dt.tnuoc);
	} while(x != i);
}


void indoanhthu (int i,float x1, float x2, float x3)// In doanh thu theo thang vao file doanhthu.txt
{
	char s[100];
	int x, y;
	rewind(r);
	fseek(r, 5, SEEK_CUR);
	do {
		fscanf(r, "%d-%[^\n]\n", &x, &s);
	} while(x != i);
	y = 5 + strlen(s);
	fseek(r, -y, SEEK_CUR);
	fprintf(r, "%02d-%011.0f-%011.0f-%011.0f\n", i, x1, x2, x3);
}


void resetdoanhthu () // Reset doanh thu khi buoc sang nam moi
{
	time_t temp;
	struct tm *now;
	time(&temp);
	now = localtime(&temp);	
	int x;
	rewind(r);
	fscanf(r, "%d\n", &x);
	if ((now->tm_year + 1900 - x) == 1)
	{
		rewind(r);
		fprintf(r, "%d\n", now->tm_year + 1900);
		for (int i = 1; i <= 12; i++)
		indoanhthu (i, 0, 0, 0);
	}
}


// Muc so 5 tren giao dien chon
void baocao() // Ghi ra bao cao tong doanh thu chi tiet
{
	int i;
	float tong, dichvu;
	do {
		printf("\nChon thang (1 - 12): ");scanf("%d",&i);
		if ((i < 1)||(i > 12))
		printf("\nThang khong hop le!");
	} while ((i < 1)||(i > 12));
	docdoanhthu (i);
	tong = dt.tgiat + dt.tnuoc + dt.tphong;
	printf("\nDoanh thu thang %d: ",i);
	printf("\n------------------------------------");
	printf("\nDoanh thu tu cho thue phong: %.0f VND",dt.tphong);
	printf("\nDoanh thu tu dich vu: %.0f VND",dt.tgiat + dt.tnuoc);
	printf("\n------------------------------------");
	printf("\nTong doanh thu: %.0f VND",tong);
	getch();
}


// Muc so 1 tren giao dien chon
void datphong(node* &head, int i) // Thue phong theo so phong
{
	char s1[30], s2[15], s3[13];	
	int x1, x2, x3;
	time_t temp;
	time(&temp);
	node *p;
	p = duyet (head, i);
	if (p == NULL) printf("\nSo phong khong hop le!"); 
	else if (p->data.trangthai == 1) printf("\nPhong %d da co nguoi thue!",i);
	else{
	printf("\nMoi quy khach lam thu tuc nhan phong...\n");
	getch();
	system("cls");
	printf("\nNhap ho ten khach hang: "); fflush(stdin);
	gets(s1); strcpy(p->data.kh.ht, s1);
	printf("\nNhap So CMND: ");	fflush(stdin);
	gets(s3); strcpy(p->data.kh.cmnd, s3);
	printf("\nNhap ngay sinh: ");	fflush(stdin);	
	gets(s2); strcpy(p->data.kh.ngaysinh, s2);
	do {
		printf("\nThoi gian thue bat dau tu ngay (dd/mm/yyyy): "); scanf("%d/%d/%d", &x1, &x2, &x3);
		p->data.kh.di.tm_year = x3 - 1900;
		p->data.kh.di.tm_mon = x2 - 1;
		p->data.kh.di.tm_mday = x1;
		if(difftime(temp,mktime(&p->data.kh.di))>86400)
		printf("\nThoi gian thue khong hop le! Vui long nhap lai: ");
	} while (difftime(temp,mktime(&p->data.kh.di))>86400);
	p->data.trangthai = 1;
	printf("\nKhach hang %s da dat phong %d thanh cong.\n",p->data.kh.ht,i);
	inthongtin (i, s1, s2, s3, p->data.kh.di.tm_mday, p->data.kh.di.tm_mon, p->data.kh.di.tm_year, 0);
	tratruoc (p);
	thuetraphong (i, 1);
	}
}


void ptrong(node *head) // In ra danh sach phong trong theo so do
{
	node *p;
	p = head;
	int dem = 0, i = 0;
	int x;
	// Dem so phong trong
	while (p->next != NULL)
	{
		if (p->data.trangthai == 0)
		dem++;
		p = p->next;
	}
	// Hien thi bang gia dat phong
	printf("\n\t\t      PRICE LIST\n");
	printf("\n\t\t\t    Don vi tien te: VND");
	printf("\n+------------------------------------------------+");
	printf("\n|%30s%18s|","VIP","Thuong");
	printf("\n|------------------------------------------------|");
	printf("\n|%15s%15s%18s|","1 giuong","500000","300000");
	printf("\n|------------------------------------------------|");
	printf("\n|%15s%15s%18s|","2 giuong","900000","550000");
	printf("\n+------------------------------------------------+\n");
 	p = head;
	if(dem != 0)
	{
		printf("\nDanh sach cac phong trong:\n\n");
		printf("\n%18s%31s\n","1 giuong","2 giuong");
		printf("----------------------------   ----------------------------");
		printf("\n%4s%30s%24s","VIP","Thuong","VIP");
		printf("\n-----    ------------------------------------------   -----\n");
		
		while (p != NULL)
		{
			if (p->data.trangthai == 0)
			printf("|%3d|",p->data.sophong); 
			else printf("|   |");
			if ((i%10 == 0)||(i%10 == 8)||(i%10 == 4)) printf("   "); 
			if (i%10 == 9) printf("\n\n");
			p = p->next;
			i++;
		}
		printf("\nChon phong so: "); scanf("%d",&x);
		datphong(head,x);
	}
	else{ 
		printf("\nKhong con phong trong, mong quy khach thong cam!\n");
	}
}


// Muc so 2 tren giao dien chon
void thongtin(node *head) // Xem thong tin dua theo so phong
{
	int i;
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
	if(p->data.trangthai == 1) // Xem thong tin phong da dat
	{
		printf("\nThong Tin Phong %d:\n", p->data.sophong);
		printf("\n%-20s%-20s%-20s%-20s", "So phong", "Loai phong", "So giuong", "Trang thai");
		printf("\n%-20d%-20s%-20d%-20s", p->data.sophong, p->data.loai, p->data.sogiuong, "Dang cho thue");
		printf("\n\nThong Tin Khach Hang:\n");
		printf("\n%-29s%-12s%-14s", "Ho Va Ten", "So CMND", "Ngay Sinh");
		printf("\n%-29s%-12s%-14s", p->data.kh.ht, p->data.kh.cmnd, p->data.kh.ngaysinh);
		getch();
	}
	else // Xem thong tin phong trong
	{
		printf("\nThong Tin Phong %d:\n", p->data.sophong);
		printf("\n%-20s%-20s%-20s%-20s", "So phong", "Loai phong", "So giuong", "Trang thai");
		printf("\n%-20d%-20s%-20d%-20s", p->data.sophong, p->data.loai, p->data.sogiuong, "Con trong");
		getch();
	} 
}


// Muc so 3 tren giao dien chon
void giat(node *head)
{
	int n, i;
	node *p = head;
	printf("\nNhap so phong hien tai cua quy khach: ");
	scanf("%d",&i);
	p = duyet(head,i);
	if(p == NULL)
	{
		printf("\nSo phong khong hop le!");
		getch();
	}
	else if (p->data.trangthai == 0)
	{
		printf("\nPhong %d chua duoc dang ky thue",p->data.sophong);
		getch();
	}
	else
	{
		printf("\nSo luong quan ao can giat cua quy khach la (Don vi: bo): "); scanf("%d",&n);
		p->data.kh.giat += n;
		printf("\nYeu cau thanh cong!");
		getch();
		inthongtin(i, p->data.kh.ht, p->data.kh.ngaysinh, p->data.kh.cmnd, p->data.kh.di.tm_mday, p->data.kh.di.tm_mon, p->data.kh.di.tm_year, p->data.kh.giat);
	}
}


void thanhtoan(node *p)
{
	int songay, x1, x2, x3;
	float f1, f2, f3;
	struct tm temp;
	temp.tm_hour = 0;
	temp.tm_min = 0;
	temp.tm_sec = 0;
	float x = 10000;
	float tong;
	printf("\n------------------------------------\n");
	printf("\nBieu muc thanh toan khach hang\n");
	printf("\nNgay quy khach bat dau thue phong: %d/%d/%d",p->data.kh.di.tm_mday,p->data.kh.di.tm_mon + 1,p->data.kh.di.tm_year + 1900);
		do {
			printf("\nNgay quy khach tra phong (dd/mm/yyyy): "); scanf("%d/%d/%d",&x1,&x2,&x3);
		temp.tm_year = x3 - 1900;
		temp.tm_mon = x2 - 1;
		temp.tm_mday = x1;
		songay = difftime(mktime(&temp),mktime(&p->data.kh.di))/(86400);
		if (songay < 0)
		printf("\nNgay tra phong khong hop le! Vui long nhap lai: ");
	} while (songay < 0);
	printf("\n\nSo luong nuoc uong da dung (chai): "); scanf("%d",&p->data.kh.nuoc);
	printf("\n------------------------------------------------------------\n");
	printf("\nHoa don thanh toan cua quy khach:\n");
	printf("\n%30s%15s%15s%15s%15s\n", "Dich vu", "Don vi", "So luong", "Don gia", "Thanh tien");
	printf("\n%30s%15s%15d%15.0f%15.0f\n", "Thue phong", "Ngay", songay, p->data.dongia, songay*p->data.dongia);
	printf("\n%30s%15s%15d%15.0f%15.0f\n", "Giat do", "Bo", p->data.kh.giat, x, x*p->data.kh.giat);
	printf("\n%30s%15s%15d%15.0f%15.0f\n", "Nuoc uong", "Chai", p->data.kh.nuoc, x, x*p->data.kh.nuoc);
	tong = songay*p->data.dongia + x*p->data.kh.giat + x*p->data.kh.nuoc;
	printf("\n\n------------------------------------------------------------\n");
	printf("\n%15s%75.0f","Tong",tong);
	if(songay == 0)
	{
		printf("\nSo tien quy khach da tra truoc la %.0f VND",tratruoc(p));
		printf("\nSo tien quy khach can phai tra them la %.0f VND",tong);
		docdoanhthu(x2);
		f1 = dt.tphong + tratruoc(p);
		f2 = dt.tgiat + x*p->data.kh.giat;
		f3 = dt.tnuoc + x*p->data.kh.nuoc;
		indoanhthu(x2, f1, f2, f3);
	}
	else
	{
		printf("\nSo tien quy khach da tra truoc la %.0f VND",tratruoc(p));
		printf("\nSo tien quy khach can phai tra them la %.0f VND",tong - tratruoc(p));
		docdoanhthu(x2);
		f1 = dt.tphong + songay*p->data.dongia;
		f2 = dt.tgiat + x*p->data.kh.giat;
		f3 = dt.tnuoc + x*p->data.kh.nuoc;
		indoanhthu(x2, f1, f2, f3);
	}
	printf("\n\nCam on quy khach da lua chon dich vu cua khach san.\n\nKinh chao tam biet quy khach!");
}

// Muc so 4 tren giao dien chon
void tra(node* &head) // Tra phong va lam thu tuc thanh toan
{
	int i;
	node *p = head;
	char s1[30], s2[15], s3[13];
	printf("\nNhap phong tra: ");
	scanf("%d",&i);
	p = duyet(head,i);
	if(p == NULL)
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
		thuetraphong(i,0);
		strcpy(s1,"hoten");
		strcpy(s2,"0/0/0");
		strcpy(s3,"cmnd");
		p->data.trangthai = 0;
		inthongtin(i, s1, s2, s3, 0, 0, 0, 0);
	}
	getch();
}
