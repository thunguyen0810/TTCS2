#include<iostream>
#include<string.h>
using namespace std;

struct nut
{
	char nd[80];
	nut *sau, *truoc;	
};

nut *dau;
nut *dau1;

//Khoi tao van ban
void KhoiTao(nut *&dau)
{
	dau = NULL;
}

//Nhap van ban
void NhapVB(nut *&dau)
{
	char tam[80];
	nut *q, *p;
	do
	{
		cout << "Nhap vao dong van ban, Enter khi dung " << endl;
		fflush(stdin);
		gets(tam);
		if(strcmp(tam, "\0") != 0)
		{
			//tao nut moi
			p = new nut;
			strcpy(p -> nd, tam);
			p -> sau = NULL;
			p -> truoc = NULL;
			//Moc vao van ban
			if(dau == NULL)
				dau = p;
			else
			{
				q -> sau = p;
				p -> truoc = q;
			}
			q = p;
		}
	}
	while(strcmp(tam, "\0") != 0);
}

//Duyet van ban
void DuyetVB(nut *&dau)
{
	if(dau != NULL)
	{
		cout << dau -> nd << endl;
		DuyetVB(dau -> sau);
	}
}

void InDongij(nut *dau, int i, int j)
{
	int dem;
	nut *p, *q;
	if(j >= i)
	{
		//tim i
		dem = 1;
		p = dau;
		while(p != NULL && dem != i)
		{
			p = p -> sau;
			dem = dem + 1;
		}
		if(p != NULL)
		{
			//tim j
			q = p;
			while(q != NULL && dem != j)
			{
				q = q -> sau;
				dem = dem + 1;
			}
			// in ra dong i den dong j
			if(q != NULL)
			while(p != q -> sau)
			{
				cout << p -> nd << endl;
				p = p -> sau;
			}
		}
	}
}

void ChenDong(nut *&dau)
{
	nut *p, *q;
	char tam[80];
	p = new nut;
	cout << "Nhap dong muon chen : ";
	cin.getline(tam, 80);
	strcpy(p -> nd, tam);
	p -> sau = NULL;
	p -> truoc = NULL;
	q = dau;
	while(q -> sau != NULL)
	{
		q = q -> sau;
	}
	q -> sau = p;
	p -> truoc = q;
}

void XoaDong(nut *&dau, int i)
{
	nut *p, *t, *s;
	int k = 1;
	p = dau;
	while((p != NULL) && (k != i))
	{
		p = p -> sau;
		k = k + 1;
	}
	if(p != NULL)
	{
		//truong hop p == dau
		if(p == dau)
		{
			dau = dau -> sau;
			dau -> truoc = NULL;
		}
		else
			//truong hop p nut cuoi
			if(p -> sau == NULL)
			{
				t = p -> truoc;
				t -> sau = NULL;
			}
			else
				if((p != dau) && (p -> sau != NULL))
				{
					t = p -> truoc;
					s = p -> sau;
					t -> sau = s;
					s -> truoc = t;
				}
		delete p;
	}
}

void XoaDongij(nut *&dau, int i, int j)
{
	int k;
	for(k = i; k <= j; k++)
		XoaDong(dau, i);
}

void ChepDongij(nut *dau, int i, int j, nut *&dau1)
{
	int dem;
	nut *p, *q, *t, *n;
	if(j >= i)
	{
		// tim i
		dem = 1;
		p = dau;
		while(p != NULL && dem!=i)
		{
			p = p-> sau;
			dem = dem + 1;
		}
		if(p != NULL)
		{
			// tim j
			q = p;
			while(q != NULL && dem != j)
			{
				q = q -> sau;
				dem = dem + 1;
			}
			// in ra dong i den dong j.
			if(q != NULL)
			while(p != q -> sau)
			{

				t = new nut;
				strcpy(t -> nd, p -> nd);
				t -> sau = NULL;
				t -> truoc = NULL;
				if(dau1 == NULL)
					dau1 = t;
				else
				{
					n -> sau = t;
					t -> truoc = n;
				}
				n = t;
				p = p -> sau;
			}
		}
	}
}

void ChenDongij(nut *&dau, int i, int j, int k)
{
	int m;
	nut *v, *u, *w;
	v = dau;
	m = 1;
	ChepDongij(dau, i, j, dau1);
	while(v != NULL && m != k)
	{
		v = v -> sau;
		m = m + 1;
	}
	if(v != NULL)
	{ 
		// v tro den dong k
		u = dau1;
		while(u -> sau != NULL)
		u = u -> sau;
		// u la dong cuoi cua ds dau1
		w = v -> sau; // dong sau dong k
		v -> sau = dau1;
		dau1 -> truoc = v;
		u -> sau = w;
		w -> truoc = u;
	}
}
int main()
{
	KhoiTao(dau);
	NhapVB(dau);
	DuyetVB(dau);
	cout << "------------------------------------" << endl;
	cout << "Van ban tu dong 1 den dong 2 : " << endl;
	InDongij(dau, 1, 2);
	cout << "-------------------------------------" << endl;
	ChenDong(dau);
	DuyetVB(dau);
	cout << "---------------------------------------" << endl;
	cout << "Van ban sau khi xoa tu dong 1 den dong 3: " << endl;
	XoaDongij(dau, 1, 3);
	DuyetVB(dau);
	cout << "-----------------------------------------" << endl;
	cout << "Van ban sau khi chen dong 1 va dong 2 vao sau dong 3 : " << endl;
	ChenDongij(dau, 1, 2, 3);
	DuyetVB(dau);
}
