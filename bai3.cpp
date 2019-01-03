#include<iostream>
using namespace std;

struct nut
{
	int info;
	nut *trai, *phai;
};

typedef nut Node;
Node *goc, *goc1;

void KhoiTao(Node *&goc)
{
	goc = NULL;
}

void MocNut(Node *&goc, int x)
{
	if(goc == NULL)
	{
		goc = new Node;
		goc -> info = x;
		goc -> trai = NULL;
		goc -> phai = NULL;
	}
	else
	{
		if(goc -> info >= x)
			MocNut(goc -> trai, x);
		else
			MocNut(goc -> phai, x);
	}
}

void TaoCay(Node *&goc)
{
	int tmp;
	do
	{
		cout << "Nhap so nguyen, nhap 0 de dung : ";
		cin >> tmp;
		cout << endl;
		if(tmp != 0)
			MocNut(goc, tmp);
	}
	while(tmp != 0);
}

void DuyetLNR(Node *goc)
{
	if(goc != NULL)
	{
		DuyetLNR(goc -> trai);
		cout << goc -> info << " " << endl;
		DuyetLNR(goc -> phai);
	}
}

void DuyetRLN(Node *goc)
{
	if(goc != NULL)
	{
		DuyetRLN(goc -> phai);
		DuyetRLN(goc -> trai);
		cout << goc -> info << " " << endl;
	}
}

void DuyetNRL(Node *goc)
{
	if(goc != NULL)
	{
		cout << goc -> info << " " << endl;
		DuyetNRL(goc -> phai);
		DuyetNRL(goc -> trai);
	}
}

int XoaNut(Node *goc, int x)
{
	if(goc == NULL)
		return 0;
	else
		if(goc -> info > x)
			return XoaNut(goc -> trai, x);
		else
			if(goc -> info < x)
				return XoaNut(goc -> phai, x);
			else
			{
				Node *p = goc;
				if(goc -> trai == NULL)
					goc = goc -> phai;
				else
					if(goc -> phai == NULL)
						goc = goc -> trai;
					else
					{
						Node *s = goc;
						Node *q = s -> trai;
						while(q -> phai != NULL)
						{
							s = q;
							q = q -> phai;
						}
						p -> info = q -> info;
						s -> phai = q -> trai;
						delete q;
					}
			}
	return 1;
}

void TimMax(Node c, int &max)
{
	if(c == NULL)
		return 0;
	if(c -> trai != NULL)
	
}

int main()
{
	KhoiTao(goc);
	TaoCay(goc);
	cout << "-------------------------------------------" << endl;
	cout << "Duyet cay theo thu tu giua (LNR) " << endl;
	DuyetLNR(goc);
	cout << "------------------------------------------" << endl;
	cout << "Duyet cay theo thu tu sau (RLN) " << endl;
	DuyetRLN(goc);
	cout << "------------------------------------------" << endl;
	cout << "Duyet cay theo thu tu truoc (NRL) " << endl;
	DuyetNRL(goc);
	cout << "------------------------------------------" << endl;
	if(XoaNut(goc, 2))
		cout << "Xoa thanh cong ! ";
	else
		cout << "Khong tim thay nut can xoa !";
}
