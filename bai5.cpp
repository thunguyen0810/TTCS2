#include<iostream>
#include<fstream>
using namespace std;

//Khai cao cau truc cua phan so 
struct PhanSo
{
	int tu;
	int mau;
};

//Doc du lieu tu file FRACTIONS_INP.txt
void DocFile(int &n, int &t, int &m)
{
	fstream f;
	f.open("FRACTIONS_INP.txt", ios::in);
	f >> n;
	f >> t; 
	f >> m;
	f.close();
}

//Ham luu ket qua va sap xep ket qua theo thu tu tang dan
void LuuKQ(PhanSo ps[], int n)
{
	//Sap xep ket qua theo thu tu tang dan
	for(int i = 0; i < n - 1; i++)
		for(int j = 0; j < n; j++)
			if((ps[i].tu / ps[i].mau) > (ps[j].tu / ps[j].mau))
				swap(ps[i], ps[j]);
	
	//Luu ket qua vao file FRACTIONS_OUT.txt
	fstream f;
	f.open("FRACTIONS_OUT.txt", ios::out);
	for(int i = 0; i < n; i++)
		f << ps[i].tu << "/" << ps[i].mau << endl;
	f.close();
}

//Ham kiem tra theo dieu kien cua de bai
void KiemTra(int n, int t, int m)
{
	PhanSo ps[(n / 2) - 1];
	int tam = 0;
	for(float i = n / 2; i < n; i++)
		for(float j = 1; j < n / 2; j++)
			if((j / i) > ((float)1 / t) && (j / i) < ((float)1 / m))
			{
				ps[tam].tu = j;
				ps[tam].mau = i;
				tam++;
			}
	LuuKQ(ps, (n / 2) - 1);
	cout << "Hay mo file FRACTIONS_OUT.txt de xem va kiem tra ket qua !";
}

int main()
{
	int n, t, m;
	
	DocFile(n, t, m);
	
	KiemTra(n, t, m);
}

