#include<iostream>
#include<conio.h>

using namespace std;

int thutu = 2;
const int n = 5;
int a[n][n] = {	0, 1, 0, 1, 0,
				0, 0, 1, 1, 1,
			    0, 0, 0, 0, 1,
				0, 0, 0, 0, 0,
				0, 0, 0, 0, 0};
int tt[n];
void GhiNhan(int j);
//------------------------------------------------------------------------------------------
//ham tra ve dinh khong co cung den, -1 khong co dinh
int Dinhkd(int a[n][n], int n)
{
	int j = 0, i;
	int kt = 0;
	while(j < n)
	{
		for(i = 0; i < n; i++)
			if(a[i][j] != 0)
				kt = 3;
			if((kt == 0) && (tt[j] == 0))
			{
				GhiNhan(j);	
				thutu + 1;
				return j;
			}
			else 
			{
				kt = 0;
				j = j + 1;
			}
	}
	if(j > n)
	return -1;
}
//---------------------------------------------------------------------
//xoa cung den tu dinh j
void XoaCung(int j)
{
	int k;
	for(k = 0; k < n; k++)
		a[j][k] = 0;		
}
//----------------------------------------------------------------------
void GhiNhan(int j)
{
	tt[j] = thutu;
}
//------------------------------------------------------------------------
void Ktra(int tt[n],int n)
{
	int k, dem = 0;
	int i;
	for (k = 0;k <= n; k++)
		if(tt[k] != 0)
			dem += 1;
	if(dem != n)
		cout << "Khong sap xep Topo \n";
	else
	{
		for(k = 2; k <= n + 2; k++)
			{
				for(i = 0; i < n; i++)
					if(tt[i] == k)
						cout << i <<"\t";
			}
	}
}
//------------------------------------------------------------------------
int main()
{
	int dinh;
	int sddc=0;
	do
		{
			dinh = Dinhkd(a,n);
			if((dinh!=-1) && (sddc<n))
			{
				if(tt[dinh] != 0)
				{
					GhiNhan(dinh);
					thutu + 1;
					XoaCung(dinh);
					sddc += 1;
				}
			}
		}
	while((dinh != -1) && (sddc < n));
	Ktra(tt, n);
	return 0;
	getch();
}
