#include<iostream>
#include<math.h>
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
		cout << goc -> info << " " ;
		DuyetLNR(goc -> phai);
	}
}

void DuyetRLN(Node *goc)
{
	if(goc != NULL)
	{
		DuyetRLN(goc -> phai);
		DuyetRLN(goc -> trai);
		cout << goc -> info << " ";
	}
}

void DuyetNRL(Node *goc)
{
	if(goc != NULL)
	{
		cout << goc -> info << " ";
		DuyetNRL(goc -> phai);
		DuyetNRL(goc -> trai);
	}
}

void InMuci(Node *goc, int i, int muc = 1)
{
	if(goc != NULL)
		if(muc == i)
			cout << goc -> info << "\t";
		else
		{
			InMuci(goc -> trai, i , muc + 1);
			InMuci(goc -> phai, i , muc + 1);
		}
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

//Cay nhi can bang la chieu cao cay con trai va phai chenh lech khong qua 1
void TimMax(Node *&c, int &max)
{
	if(c == NULL)
		return ;
	if(c -> trai != NULL)
		max = (max > c -> trai -> info) ? max : c -> trai -> info;
	if(c -> phai != NULL)
		max = (max > c -> phai -> info) ? max : c -> phai -> info;
	max = (max > c -> info) ? max : c -> info;
	TimMax(c -> trai, max);
	TimMax(c -> phai, max);
}

int ChieuCaoAVL(Node *&c)
{
	if(c == NULL)
		return 0;
	int ChieuCaoAVLPhai = ChieuCaoAVL(c -> phai);
	int ChieuCaoAVLTrai = ChieuCaoAVL(c -> trai);
	int max = (ChieuCaoAVLPhai > ChieuCaoAVLTrai) ? ChieuCaoAVLPhai : ChieuCaoAVLTrai;
	return max + 1;
}

//Tra ve 1 thi khong can bang, nguoc lai tra ve 0 thi khong can bang
int KiemTra(Node *&c)
{
	if(c == NULL)
	//Kiem tra dieu kien cua cay nhi phan tim kiem
	if((c -> trai != NULL) && (c -> phai != NULL))
	{
		int maxtrai, maxphai;
		TimMax(c -> trai, maxtrai);
		TimMax(c -> phai, maxphai);
		if(!((maxtrai < c -> info) && (c -> info < maxphai)))
			return 1;
	}
	else
		if((c -> trai == NULL) && (c -> phai != NULL))
		{
			int maxtrai, maxphai;
			TimMax(c -> phai, maxphai);
			if(!(c -> info < maxphai))
				return 1;
		}
		else
			if((c -> trai != NULL) && (c -> phai == NULL))
			{
				int maxtrai, maxphai;
				TimMax(c -> trai, maxtrai);
				if(!(maxphai < c -> info))
					return 1;
			}
	//Kiem tra dieu kien cua cay nhi phan tim kiem can bang
	int ChieuCaoAVLPhai = ChieuCaoAVL(c -> phai);
	int ChieuCaoAVLTrai = ChieuCaoAVL(c -> trai);
	cout << "Nut " << c -> info << " lech phai " << ChieuCaoAVLPhai << " trai " << ChieuCaoAVLTrai << endl;
	if(abs(ChieuCaoAVLPhai - ChieuCaoAVLTrai) > 1) //Chenh lech lon hon 1
		return 1;
	int Phai = KiemTra(c -> phai);
	int Trai = KiemTra(c -> trai);
	return (Trai + Phai);
}

void XuatKiemTra(Node *&c)
{
	int kt = KiemTra(c);
	if(kt == 0)
		cout << "La cay nhi phan tim kiem can bang " << endl;
	else
		cout << "Khong phai la cay nhi phan tim kiem can bang " << endl;
}

void SaoChep(Node *goc, Node *&goc1)
{
	if(goc == NULL)
		goc1 = NULL;
	else
	{
		goc1 = new Node;
		goc1 -> info = goc -> info;
		SaoChep(goc -> trai, goc1 -> trai);
		SaoChep(goc -> phai, goc1 -> phai);
	}
}

int XoaNut(Node *&goc, int x)
{
    if (goc == NULL) 
		return 0;
    else 
		if (goc -> info > x) 
			return XoaNut(goc -> trai, x);
    	else 
			if (goc -> info < x) 
				return XoaNut(goc -> phai, x);
    		else // T -> info == x
    		{
        		Node *p = goc;
        		if (goc -> trai == NULL) 
					goc = goc -> phai;    // Node chi co cay con phai
        		else 
					if (goc -> phai == NULL) 
						goc = goc -> trai;   // Node chi co cay con trai
       				else // Node co ca 2 con
        			{
            			Node *s = goc, *q = s -> trai;
            			// s la cha cua q, q la Node phai nhat cua cay con trai cua P
            			while (q -> phai != NULL)
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

int main()
{
	int x, i;
	KhoiTao(goc);
	TaoCay(goc);
	
	cout << "-------------------------------------------" << endl;
	
	cout << "Duyet cay theo thu tu giua (LNR) " << endl;
	DuyetLNR(goc);
	
	cout << endl;
	cout << "------------------------------------------" << endl;
	
	cout << "Nhap muc muon in ra man hinh : ";
	cin >> i;
	InMuci(goc, i, 1);
	
	cout << endl;
	cout << "------------------------------------------" << endl;
	
	cout << "Chieu cao cua cay : " << ChieuCaoAVL(goc) << endl;

	cout << "---------------------------------------------" << endl;
	cout << endl;
	
	XuatKiemTra(goc);
	
	cout << endl;
	cout << "--------------------------------------------" << endl;
	
		if(KiemTraCayAVL(goc) == 1)
		cout << "La cay AVL" << endl;
	else
		cout << "Khong phai cay AVL" << endl;
		
	cout << endl;
	cout << "------------------------------------------" << endl;
		
	KhoiTao(goc1);
	SaoChep(goc, goc1);
	
	cout << "Cay sau khi sao chep " << endl;
	DuyetLNR(goc1);
		
	cout << endl;
	cout << "------------------------------------------" << endl;
	
	cout << "Nhap nut can xoa : ";
	cin >> x;
	
	if(XoaNut(goc, x))
		cout << "Xoa thanh cong ! " << endl;
	else
		cout << "Khong tim thay nut can xoa !" << endl;
		
	cout << "------------------------------------------" << endl;
	
	cout << "Cay sau khi xoa " << endl;
	DuyetLNR(goc);
	
	cout << endl;
	cout << "-------------------------------------------" << endl;
}
