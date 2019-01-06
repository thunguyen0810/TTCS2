#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

# define	inp		"dulieu.txt"
# define	out1	"tam.txt"
# define	out2	"tam1.txt"

int n;

void TaoFile();
void Xuat(FILE *f, char	dd[]);
void Chia(FILE *f1, FILE *f2, FILE *f3, int p);
void Tron (FILE	*f1, FILE *f2, FILE *f3, int p);

int main()
{
	FILE *f1, *f2, *f3;
	
	TaoFile();
	
	printf("File chinh:");
	Xuat(f1, inp); 
	
	int p = 1;
	
	while(p < n)
	{
		Chia(f1, f2, f3, p);
		
		printf("\n File tam 1:"); 	
	
		Xuat(f2, out1);  
		printf("\n File tam 2:");
		
		Xuat(f3, out2);  
		
		Tron(f2, f3, f1, p);
		printf("\n File chinh sau khi duoc tron:");
		Xuat(f1, inp); 
		
		p = p * 2;		
	}
	printf("\n File cuoi cung:"); 
	Xuat(f1, inp); 
}

//Tao file f gom n phan tu
void TaoFile()
{
	int	x;
	FILE *f;
	
	f = fopen("dulieu.txt","wt"); 
	
	if(f == NULL)
		printf("\nKhong tao duoc file.");
		
	printf("Hay nhap so phan tu:"); 	
	scanf("%d", &n);
	
	for (int i = 0; i < n; i++)
	{
		x = rand() % 51; //Tra ve n so ngau nhien tu 0 toi 50
		fprintf(f, "%3d", x); //ghi day so x vao file f
	}
	fclose(f);	
}

//Xuat file f ra man hinh
void Xuat(FILE *f, char	dd[])
{
	int	x;
	f = fopen(dd,"rt"); 
	
	if(f == NULL)
		printf("\nKhong doc duoc file.");

	int i = 0;
	n = 0;
	while  (!feof(f)) 
	{
		fscanf(f, "%d", &x); //doc tu file f va luu vao bien x	 
		printf("%3d", x); //xuat bien x ra man hinh
		n++;
	}
	fclose(f);	
}

/*Chia file f1 lan luot tung phan tu cho file f2 va f3 cu moi lan la p 
phan tu cho den khi file f1 het phan tu*/
void Chia(FILE *f1, FILE *f2, FILE *f3, int p)
{
	int	dem, x;
	
	f1 = fopen("dulieu.txt","rt"); 	
	f2 = fopen("tam.txt","wt"); 	
	f3 = fopen("tam1.txt","wt"); 	
	
	while (!feof(f1))
	{
		//chia p phan tu tu file f1 cho file f2
		dem	= 0;
		while ( (dem < p) and (!feof(f1)) )
		{
			fscanf(f1, "%3d", &x);		
			fprintf(f2, "%3d", x);		
			dem++;	
		}
		//chia p phan tu tu file f1 cho file f3
		dem	= 0;
		while ( (dem < p) and (!feof(f1)) )
		{
			fscanf(f1, "%3d", &x);		
			fprintf(f3, "%3d", x);		
			dem++;			
		}
	}
	fclose(f1);	 
	fclose(f2);		
	fclose(f3);	
}

/*Tron p phan tu trong file f2 va p phan tu trong file f3 thanh 2p phan tu vao file f1 cho
den khi phan tu trong file f2 va f3 khong con*/
void Tron (FILE	*f1, FILE *f2, FILE *f3, int p)
{
	int	x, y, l, r;
	
	f1 = fopen("dulieu.txt","wt"); 	
	f2 = fopen("tam.txt","rt"); 	
	f3 = fopen("tam1.txt","rt"); 
	
	while ( (!feof(f2)) && (!feof(f3)) )
	{
		l = 0; //so phan tu cua file f2 da ghi tren file f1
		r = 0; //so phan tu cua file f3 da ghi tren file f1
		
		fscanf(f2, "%3d", &x);	
		fscanf(f3, "%3d", &y);
		
		int stop = 0;
		
		while ( (l != p) && (r != p) && (!stop) )
		{
			//ghi file f2 (da doc ra tu bien x) vao truoc
			if(x < y)					
			{
				fprintf(f1,"%3d", x);			
				l++;
				
				if( (l < p) && (!feof(f2)) ) //chua du p phan tu va file f2 van chua het			
					fscanf(f2, "%3d", &x);	
				//file f2 da het phan tu (thoa dieu kien), tiep theo ta ghi file f3 vao file f1
				else 						
				{
					fprintf(f1, "%3d", y);			
					r++;
					if (feof(f2)) //file f2 da het phan tu thi dung		
						stop =1;
				}
			}
			//ghi file f3 (da doc ra tu bien y) vao truoc
			else 		
			{
				fprintf(f1, "%3d", y);			
				r++;
				if ( (r < p) && (!feof(f3)) ) //chua du p phan tu va file f3 van chua het		
					fscanf(f3, "%3d", &y);
				//file f3 da het phan tu (thoa dieu kien), tiep theo ta ghi file f2 vao file f1	
				else 					
				{
					fprintf(f1,"%3d", x);		
					l++;
					if (feof(f3))	//file f2 da het phan tu thi dung			
						stop =1;
				}							
			}	
		}
		//ghi tiep p phan tu con sot lai tren file f2 vao file 1
		while ( (l < p) && (!feof(f2)) )	
		{
			fscanf(f2, "%3d", &x);
			fprintf(f1, "%3d", x);	
			l++;
		}
		//ghi tiep p phan tu con sot lai tren file f3 vao file 1
		while ( (r<p) && (!feof(f3)) ) 	
		{
			fscanf(f3, "%3d", &y);
			fprintf(f1,"%3d", y);	
			r++;
		}
	}
	if(!feof(f2))	//f2 con phan tu	
	{
		//chep cac phan tu con lai tren file f2 vao file f1
		while (!feof(f2))
		{	
			fscanf(f2, "%3d", &x);
			fprintf(f1, "%3d", x);	
		}
	}
	if(!feof(f3)) //f3 con phan tu
	{
		//chep cac phan tu con lai tren file f3 vao file f1
		while (!feof(f3))
		{	
			fscanf(f3, "%3d", &y);
			fprintf(f1, "%3d", y);	
		}
	}	
	fclose(f1);	 
	fclose(f2);		
	fclose(f3);	
}
