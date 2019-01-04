#include<iostream>
using namespace std;

struct nut
{
	int info;
	int cb;
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

void XoayTrai(Node *&p)
{
	Node *q;
	q = p -> phai;
	p -> phai = q -> trai;
	q -> trai = p;
	p = q;
}

void XoayPhai(Node *&p)
{
	Node *q;
	q = p -> trai;
	p -> trai = q -> phai;
	q -> phai = p;
	p = q;
}

void CanBangTrai(Node *&p)
{
	switch(p -> trai -> cb)
	{
		case 1: //Mat can bang trai
			XoayPhai(goc);
			p -> cb = 0;
			p -> phai -> cb = 0;
			break;
		case 2: //Cho biet truong hop mat can bang nao
			XoayTrai(p -> trai);
			XoayPhai(goc);
			switch(p -> cb)
			{
				case 0: 
					p -> trai -> cb = 0;
					p -> phai -> cb = 0;
					break;
				case 1:
					p -> trai -> cb = 0;
					p -> phai -> cb = 2;
					break;
				case 2:	
					p -> trai -> cb = 1;
					p -> phai -> cb = 2;
					break;
			}
			p -> cb = 0;
			break;
	}
}

void CanBangPhai(Node *&p)
{
	switch(p -> phai -> cb)
	{
		case 1: //Cho biet la truong hop mat can bang nao
			XoayPhai(p -> phai);
			XoayTrai(goc);
			switch(p -> cb)
			{
				case 0: 
					p -> trai -> cb = 0;
					p -> phai -> cb = 0;
					break;
				case 1:
					p -> trai -> cb = 1;
					p -> phai -> cb = 0;
					break;
				case 2:
					p -> trai -> cb = 0;
					p -> phai -> cb = 2;
					break;
			}
			p -> cb = 0;
			break;
		case 2: // Cho biet day la truong hop mat can bang nao
			XoayTrai(goc);
			p -> cb = 0;
			p -> trai -> cb = 0;
			break;
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

int KiemTraCayAVL(Node *goc)
{
	if(goc == NULL)
		return 1;
	if((goc -> trai == NULL) && (goc -> phai == NULL))
		return 1;
	else
		if(goc -> trai == NULL)
			KiemTraCayAVL(goc -> phai);
		else
			if(goc -> phai == NULL)
				KiemTraCayAVL(goc -> trai);
			else
				if((goc -> trai -> info > goc -> info) || (goc -> phai -> info < goc -> info))
					return 0;
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
		cout << "Xoa thanh cong ! " << endl;
	else
		cout << "Khong tim thay nut can xoa !" << endl;
	cout << "-------------------------------------------" << endl;
	if(KiemTraCayAVL(goc) == 1)
		cout << "La cay AVL" << endl;
	else
		cout << "Khong phai cay AVL" << endl;
}
