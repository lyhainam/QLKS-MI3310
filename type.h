#include<time.h>

typedef struct khachhang
{
	char ht[30], ngaysinh[15], cmnd[13];
	int nuoc, giat;
	struct tm di;
} khachhang;

typedef struct phong
{
	char loai[10]; 
	int trangthai,sophong,sogiuong;
	float dongia;
	khachhang kh;
} phong;

typedef struct node
{
	phong data;
	node *next;
} node;

struct doanhthu
{
	float tphong, tgiat, tnuoc;
} dt;
