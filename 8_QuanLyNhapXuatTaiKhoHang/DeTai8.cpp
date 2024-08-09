#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

struct NgayThangNam
{
	int ngay;
	int thang;
	int nam;
};

struct KhoHang
{
	string maKhoHang;
	string tenKhoHang;
	string diaDiem;
	float taiTrong;
	string loaiHangHoa;
	NgayThangNam ngayNhapHang;
	NgayThangNam ngayXuatHang;
	float taiTrongHangNhap;
};

struct Node
{
	KhoHang data;
	Node* next;
};

struct dsKhoHang
{
	Node* head;
	Node* tail;
};

void menu();
void menuNhap();
void menuLoaiXuLyNode();
void menuThem();
void menuXoa();
Node* taoNode(KhoHang khoHang);
NgayThangNam chuyenDoiNgay(const string& dateStr);
bool kiemTraNgay(NgayThangNam ngayNhap, NgayThangNam ngayXuat);
bool docTuFile(const string& fileName, dsKhoHang& ds, int& n);
void hienThi(dsKhoHang ds);
KhoHang taoKhoHang(int& soMaKho);
void nhapDuLieuTay(dsKhoHang& ds, int& n);
bool themDauDanhSach(dsKhoHang& ds, Node* p);
bool themOViTriBatKy(dsKhoHang& ds, Node* p, int k);
bool themOViTriCuoi(dsKhoHang& ds, Node* p);
bool xoaODauDanhSach(dsKhoHang& ds, Node* p);
bool xoaOViTriBatKy(dsKhoHang& ds, Node* p, int k);
bool xoaOViTriCuoi(dsKhoHang& ds, Node* p);
bool suaKhoHangTrongDanhSach(dsKhoHang& ds, Node* p, string maKho);
void sapXepTheoTaiTrong(dsKhoHang& ds);
KhoHang suaDuLieuKho(string maKho);
void themVanDamBao(Node* p, dsKhoHang& ds);
bool timNhapVao(dsKhoHang ds, int thang, int nam);
bool timKhoTrong(dsKhoHang ds);
bool timKhoHangTheoLoai(string loai, dsKhoHang ds);
double tinhTaiTrongTrungBinh(dsKhoHang ds, string diaDiem);
int demKhoHangBatDauBang(dsKhoHang ds, string prefix);
void sapXepTheoMa(dsKhoHang& ds);
void danhSachTaiTrongConLaiTrongKhoHang(dsKhoHang ds);
void hienThiTop5TaiTrongLonNhat(dsKhoHang ds);
void locTheoThoiGian(dsKhoHang ds, NgayThangNam batDau, NgayThangNam ketThuc);

int main()
{

	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	int chon = 0;
	dsKhoHang ds = { NULL, NULL };
	int n = 0;
	do
	{
		int chonCachNhap = 0;
		menu();
		cout << "Nhập lựa chọn của bạn: ";
		cin >> chon;
		cout << endl;
		switch (chon)
		{
		case 1:
		{
			do
			{
				menuNhap();
				/*cout << endl;*/
				cin >> chonCachNhap;
				switch (chonCachNhap)
				{
				case 0:
				{

				}
				break;
				case 1:
				{
					nhapDuLieuTay(ds, n);
					hienThi(ds);
				}
				break;
				case 2:
				{
					if (docTuFile("dulieu.txt", ds, n))
					{
						hienThi(ds);
					}

				}
				break;
				default:
					cout << "Lựa chọn của bạn không nằm trong yêu cầu của chúng tôi " << endl;
					break;
				}
			} while (chonCachNhap != 0);
		}
		break;
		case 0:
		{
			return 0;
		}
		break;

		case 2:
		{
			int cachChonXuLyNode = 0;
			do
			{
				menuLoaiXuLyNode();
				cout << "Mời bạn lựa chọn: ";
				cin >> cachChonXuLyNode;
				cout << endl;
				switch (cachChonXuLyNode)
				{
				case 1: // Thêm 
				{
					int chonThem = 0;
					do
					{
						menuThem();
						cin >> chonThem;
						cout << endl;
						switch (chonThem)
						{
						case 1: // Thêm đầu
						{
							n++;
							Node* p = taoNode(taoKhoHang(n));
							if (p == NULL)
								return 0;
							themDauDanhSach(ds, p);
							hienThi(ds);

						}
						break;

						case 2: // Thêm bất kỳ
						{
							n++;
							Node* p = taoNode(taoKhoHang(n));
							int k = 0;
							if (p == NULL)
								return 0;
							if (ds.head != NULL)
							{
								cout << "Nhập vị trí cần thêm: ";
								cin >> k;
							}
							themOViTriBatKy(ds, p, k);
							hienThi(ds);

						}
						break;

						case 3: // Thêm cuối
						{
							n++;
							Node* p = taoNode(taoKhoHang(n));
							if (p == NULL)
								return 0;
							themOViTriCuoi(ds, p);
							hienThi(ds);

						}
						break;

						case 0: // Thoát
						{

						}
						break;
						default:
							cout << "Lựa chọn của bạn không nằm trong yêu cầu của chúng tôi" << endl;
							break;
						}
					} while (chonThem != 0);
				}
				break;

				case 2: // Xóa
				{

					int chonXoa = 0;
					do
					{
						menuXoa();
						cin >> chonXoa;
						cout << endl;
						switch (chonXoa)
						{
						case 1: // Xóa đầu
						{
							Node* p = new Node;
							if (p == NULL)
								return 0;
							xoaODauDanhSach(ds, p);
							hienThi(ds);
						}
						break;
						case 2: // Xóa bất kỳ
						{
							Node* p = new Node;
							int k = 0;
							if (p == NULL)
								return 0;
							if (ds.head != NULL)
							{
								cout << endl << "Nhập vị trí cần xóa: ";
								cin >> k;
							}
							
							xoaOViTriBatKy(ds, p, k);
							hienThi(ds);
						}
						break;
						case 3: // Xóa cuối
						{
							Node* p = new Node;
							if (p == NULL)
								return 0;
							xoaOViTriCuoi(ds, p);
							hienThi(ds);
						}
						break;
						case 0: // Thoát
						{

						}
						break;
						default:
							cout << "Lựa chọn của bạn không nằm trong yêu cầu của chúng tôi" << endl;
							break;
						}
					} while (chonXoa != 0);
				}
				break;
				case 3: // Sửa
				{
					Node* p = new Node;
					string maKho = "";
					if (p == NULL)
						return 0;

					cin.ignore();
					cout << "Nhập mã kho cần sửa";
					getline(cin, maKho);
					suaKhoHangTrongDanhSach(ds, p, maKho);
					hienThi(ds);
				}
				break;

				case 0: // Thoát
				{

				}
				break;
				default:
					cout << "Lựa chọn của bạn không nằm trong yêu cầu của chúng tôi" << endl;
					break;
				}
			} while (cachChonXuLyNode != 0);
		}
		break;

		case 3: //  Sap xep danh sach theo tai trong
		{
			sapXepTheoTaiTrong(ds);
			hienThi(ds);
		}
		break;

		case 4:
		{
			n++;
			Node* p = taoNode(taoKhoHang(n));
			themVanDamBao(p, ds);
			hienThi(ds);
		}
		break;

		case 5:
		{
			int thang = 0, nam = 0;
			cout << endl << "Nhập tháng nhập hàng cần tìm: ";
			cin >> thang;
			cout << endl << "Nhập năm nhập hàng cần tìm: ";
			cin >> nam;
			cout << endl << "Danh sách kho hàng có tháng, năm nhập hàng như trên:" << endl;
			if (!timNhapVao(ds, thang, nam))
				cout << endl << "Không có kho có tháng, năm nhập hàng như trên" << endl;

		}
		break;

		case 6:
		{
			cout << endl << "Danh sách kho hàng trống" << endl;
			if (!timKhoTrong(ds))
				cout << "Không có kho hàng trống";
		}
		break;

		case 7:
		{
			string loai = "";
			cout << endl << "Nhập loại hàng trong kho cần tìm: ";
			cin.ignore();
			getline(cin, loai);
			cout << endl << "Danh sách kho hàng theo loại" << endl;
			if (!timKhoHangTheoLoai(loai, ds))
				cout << "Không có kho hàng nào có loại hàng trên";

		}
		break;

		case 8:
		{
			string diaDiem = "";
			cout << endl << "Nhập địa điểm: ";
			cin.ignore();
			getline(cin, diaDiem);
			if (tinhTaiTrongTrungBinh(ds, diaDiem))
				cout << endl << "Tải trọng trung bình là: " << tinhTaiTrongTrungBinh(ds, diaDiem) << endl << endl;
			else
				cout << "Không có kho hàng nào có địa điểm trên" << endl;
		}
		break;

		case 9:
		{
			string prefix = "KH";
			if (demKhoHangBatDauBang(ds, prefix))
				cout << "Số lượng kho có tên kho bắt đầu bằng <KH> là: " << demKhoHangBatDauBang(ds, prefix) << endl << endl;
			else
				cout << "Không có tên kho bắt đầu bằng KH" << endl;
		}
		break;
		case 10:
		{
			cout << endl << "Sắp xếp kho hàng theo mã kho hàng" << endl;
			sapXepTheoMa(ds);
			hienThi(ds);
		}
		break;
		case 11:
		{
			hienThiTop5TaiTrongLonNhat(ds);

		}
		break;

		case 12:
		{
			NgayThangNam batDau, ketThuc;
			cout << "Nhập ngày bắt đầu (ngày tháng năm): ";
			cin >> batDau.ngay >> batDau.thang >> batDau.nam;
			cout << "Nhập ngày kết thúc (ngày tháng năm): ";
			cin >> ketThuc.ngay >> ketThuc.thang >> ketThuc.nam;
			locTheoThoiGian(ds, batDau, ketThuc);
		}
		break;
		case 13:
		{
			 danhSachTaiTrongConLaiTrongKhoHang( ds);
		}
		break;
		default:

			cout << "Lựa chọn của bạn không nằm trong yêu cầu của chúng tôi" << endl;
			break;
		}
	} while (chon != 0);

	return 0;

}


void menu()
{
	cout << "\n========================================== MENU ==========================================" << endl;
	cout << "1. Tạo danh sách đơn chứa thông tin bằng hai cách: nhập từ bàn phím, nhập từ file .txt " << endl;
	cout << "2. Thêm/Xóa/Sửa tại ba vị trí đầu/cuối/bất kỳ trong danh sách" << endl;
	cout << "3. Sắp xếp danh sách theo tải trọng" << endl;
	cout << "4. Thêm một kho vào danh sách sao cho vẫn đảm bảo thứ tự vừa sắp xếp ở câu 3" << endl;
	cout << "5. Tìm danh sách các kho nào vừa nhập hàng vào tháng x năm y (ví dụ: tháng 10 năm 2021)" << endl;
	cout << "6. Tìm kho nào còn trống (tức tải trọng hàng nhập < tải trọng)" << endl;
	cout << "7. Tìm xem kho nào có thể chứa loại hàng hóa là: hàng đông lạnh" << endl;
	cout << "8. Tìm tải trọng trung bình của toàn bộ những kho hàng nào ở Đồng Nai" << endl;
	cout << "9. Có bao nhiêu kho hàng có tên bắt đầu bằng KH " << endl;
	cout << "10. Sắp xếp kho hàng theo mã kho hàng " << endl;
	cout << "11. Hiển thị top 5 kho hàng có tải trọng lớn nhất" << endl;
	cout << "12. Lọc danh sách kho hàng theo khoảng thời gian" << endl;
	cout << "13. Hiển thị tải trọng còn lại trong kho hàng " << endl;
	cout << "0. Thoát chương trinh" << endl;
}

void menuNhap()
{
	cout << "1.Nhập từ bàn phím" << endl;
	cout << "2. Nhập từ file " << endl;
	cout << "0. Thoát" << endl;
	cout << "Mời bạn chọn phương thức nhập: ";
}

void menuLoaiXuLyNode()
{
	cout << "1. Thêm" << endl;
	cout << "2. Xóa" << endl;
	cout << "3. Sửa" << endl;
	cout << "0. Thoát chương trình" << endl;
}

void menuThem()
{
	cout << "1. Thêm đầu" << endl;
	cout << "2. Thêm ở vị trí bất kỳ" << endl;
	cout << "3. Thêm cuối" << endl;
	cout << "0. Thoát chương trình" << endl;
	cout << "Mời bạn chọn phương thức nhập: ";
}

void menuXoa()
{
	cout << "1. Xóa đầu" << endl;
	cout << "2. Xóa ở vị trí bất kỳ" << endl;
	cout << "3. Xóa cuối" << endl;
	cout << "0. Thoát chương trình" << endl;
	cout << "Mời bạn chọn phương thức nhập: ";
}

Node* taoNode(KhoHang khoHang)
{
	Node* p = new Node;
	if (p == NULL)
	{
		cout << "Không thể cấp phát bộ nhớ" << endl;
		return NULL;
	}
	p->data = khoHang;
	p->next = NULL;
	return p;
}

NgayThangNam chuyenDoiNgay(const string& dateStr)
{
	NgayThangNam date;
	stringstream ss(dateStr);
	string token;
	getline(ss, token, '/');
	date.ngay = stoi(token);
	getline(ss, token, '/');
	date.thang = stoi(token);
	getline(ss, token);
	date.nam = stoi(token);
	return date;
}

bool kiemTraNgay(NgayThangNam ngayNhap, NgayThangNam ngayXuat)
{


	if (ngayNhap.nam > ngayXuat.nam)
	{
		return false;
	}
	if (ngayNhap.nam == ngayXuat.nam)
	{
		if (ngayNhap.thang > ngayXuat.thang)
		{
			return false;
		}
		if (ngayNhap.thang == ngayXuat.thang)
		{
			if (ngayNhap.ngay > ngayXuat.ngay)
				return false;
		}
	}
	return true;
}


KhoHang taoKhoHang(int& soMaKho)
{
	KhoHang khoHang;
	cout << endl;
	if (soMaKho >= 0 && soMaKho < 10)
	{
		string maKho = to_string(soMaKho);
		khoHang.maKhoHang = "KH00" + maKho;
		cout << "Mã kho hàng: " << khoHang.maKhoHang << endl;
	}
	else if (soMaKho >= 10 && soMaKho < 100)
	{
		string maKho = to_string(soMaKho);
		khoHang.maKhoHang = "KH0" + maKho;
		cout << "Mã kho hàng: " << khoHang.maKhoHang << endl;
	}
	else if (soMaKho >= 100 && soMaKho < 1000)
	{
		string maKho = to_string(soMaKho);
		khoHang.maKhoHang = "KH" + maKho;
		cout << "Mã kho hàng: " << khoHang.maKhoHang << endl;
	}

	cout << endl << "Nhập tên kho hàng: ";
	cin.ignore();
	getline(cin, khoHang.tenKhoHang);
	cout << endl;

	cout << endl << "Địa điểm kho hàng: ";
	getline(cin, khoHang.diaDiem);

	cout << endl << "Loại hàng hóa: ";
	getline(cin, khoHang.loaiHangHoa);

	cout << endl << "Nhập tải trọng kho hàng (tấn) : ";
	cin >> khoHang.taiTrong;

	while (khoHang.taiTrong < 0)
	{
		cout << endl << "Tải trọng không được bé hơn 0" << endl;
		cout << endl << "Nhập lại tải trọng kho hàng (tấn) : ";
		cin >> khoHang.taiTrong;
	}

	cout << endl << "Nhập ngày nhập hàng: ";
	cin >> khoHang.ngayNhapHang.ngay >> khoHang.ngayNhapHang.thang >> khoHang.ngayNhapHang.nam;

	cout << endl << "Nhập ngày xuất hàng: ";
	cin >> khoHang.ngayXuatHang.ngay >> khoHang.ngayXuatHang.thang >> khoHang.ngayXuatHang.nam;

	while (!kiemTraNgay(khoHang.ngayNhapHang, khoHang.ngayXuatHang))
	{
		cout << endl << "Ngày xuất phải lớn hơn hoặc bằng ngày nhập" << endl;
		cout << endl << "Mời bạn nhập lại ngày xuất hàng: ";
		cin >> khoHang.ngayXuatHang.ngay >> khoHang.ngayXuatHang.thang >> khoHang.ngayXuatHang.nam;
	}

	cout << endl << "Nhập tải trọng hàng nhập (tấn) : ";
	cin >> khoHang.taiTrongHangNhap;
	cout << endl;

	while ((khoHang.taiTrongHangNhap < 0) || (khoHang.taiTrongHangNhap > khoHang.taiTrong))
	{
		cout << endl << "Tải trọng hàng nhập bé hơn 0 hoặc tải trọng hàng nhập lớn hơn tải trọng" << endl;
		cout << endl << "Nhập tải trọng hàng nhập (tấn) : ";
		cin >> khoHang.taiTrongHangNhap;
		cout << endl;
	}

	return khoHang;
}

void nhapDuLieuTay(dsKhoHang& ds, int& n)
{
	int pre = n;
	int soMaKho = 1;
	int tongSoKho = 0;
	cout << "Nhập số lượng kho hàng: ";
	cin >> n;
	cout << endl;
	if (pre <= 0)
		soMaKho = 1;
	else
	{
		tongSoKho = pre + n;
		soMaKho = tongSoKho - n + 1;
	}

	for (int i = 0; i < n; i++)
	{
		KhoHang khoHang = taoKhoHang(soMaKho);
		Node* p = taoNode(khoHang);
		if (p == NULL)
		{
			cout << "Không đủ bộ nhớ để cấp phát" << endl;
			return;
		}
		if (ds.head == NULL)
		{
			ds.head = ds.tail = p;
		}
		else
		{
			ds.tail->next = p;
			ds.tail = p;
		}
		soMaKho++;
	}
	n = tongSoKho;
}

bool docTuFile(const string& fileName, dsKhoHang& ds, int& n)
{
	ifstream fData(fileName);
	if (!fData.is_open())
	{
		cout << "Lỗi đọc file" << endl;
		return false;
	}

	fData >> n;
	Node* q = new Node;
	if (q == NULL)
	{
		cout << "Bộ nhớ đầy" << endl;
		return false;
	}
	fData.ignore();

	for (int i = 0; i < n; ++i)
	{
		string line;
		if (!getline(fData, line))
			break;

		stringstream ss(line);
		KhoHang khoHang;
		string token;


		getline(ss, khoHang.maKhoHang, ';');
		getline(ss, khoHang.tenKhoHang, ';');
		getline(ss, khoHang.diaDiem, ';');

		getline(ss, token, ';');
		khoHang.taiTrong = stof(token);

		getline(ss, khoHang.loaiHangHoa, ';');

		getline(ss, token, ';');
		khoHang.ngayNhapHang = chuyenDoiNgay(token);

		getline(ss, token, ';');
		khoHang.ngayXuatHang = chuyenDoiNgay(token);

		getline(ss, token, ';');
		khoHang.taiTrongHangNhap = stof(token);

		if (ds.head != NULL)
		{
			if (ds.head->data.maKhoHang == khoHang.maKhoHang)
			{
				cout << endl << "File đã đọc rồi hoặc dữ liệu thay thế file đã được nhập" << endl << endl;
				return false;
				if (ds.head->data.tenKhoHang == khoHang.tenKhoHang)
				{
					cout << endl << "File đã đọc rồi hoặc dữ liệu thay thế file đã được nhập" << endl << endl;
					return false;
				}
			}
		}

		q = taoNode(khoHang);
		if (ds.head == NULL)
		{
			ds.head = ds.tail = q;
		}
		else
		{
			ds.tail->next = q;
			ds.tail = q;
		}
	}

	fData.close();
	return true;
}

// hiển thị
void hienThi(dsKhoHang ds)
{
	Node* p = ds.head;
	cout << endl << "Danh sách kho hàng " << endl << endl;
	while (p != NULL)
	{
		cout << "Mã kho hàng: " << p->data.maKhoHang << endl;
		cout << "Tên kho hàng: " << p->data.tenKhoHang << endl;
		cout << "Địa điểm: " << p->data.diaDiem << endl;
		cout << "Tải trọng (tấn) : " << p->data.taiTrong << endl;
		cout << "Loại hàng hóa: " << p->data.loaiHangHoa << endl;
		cout << "Ngày nhập hàng: " << p->data.ngayNhapHang.ngay << "/" << p->data.ngayNhapHang.thang << "/" << p->data.ngayNhapHang.nam << endl;
		cout << "Ngày xuất hàng: " << p->data.ngayXuatHang.ngay << "/" << p->data.ngayXuatHang.thang << "/" << p->data.ngayXuatHang.nam << endl;
		cout << "Tải trọng hàng nhập (tấn): " << p->data.taiTrongHangNhap << endl;
		cout << endl;
		p = p->next;
	}
}

// thêm đầu
bool themDauDanhSach(dsKhoHang& ds, Node* p)
{
	if (p == NULL)
	{
		cout << "Bộ nhớ đầy" << endl;
		return false;
	}

	if (ds.head == NULL)
	{
		ds.head = ds.tail = p;
		return true;
	}

	p->next = ds.head;
	ds.head = p;
	return true;
}

// thêm bất kỳ
bool themOViTriBatKy(dsKhoHang& ds, Node* p, int k)
{
	int i = 1;
	Node* q = ds.head;
	if (k == i)
	{
		themDauDanhSach(ds, p);
		return true;
	}

	while (q != NULL)
	{
		if (i == k - 1)
		{
			p->next = q->next;
			q->next = p;
			return true;
		}
		q = q->next;
		i++;
	}

	return false;
}

// thêm cuối
bool themOViTriCuoi(dsKhoHang& ds, Node* p)
{
	if (p == NULL)
		return false;
	ds.tail->next = p;
	p->next = NULL;
	ds.tail = p;
	return true;
}

// xóa đầu
bool xoaODauDanhSach(dsKhoHang& ds, Node* p)
{
	if (p == NULL)
		return false;
	p = ds.head;
	ds.head = ds.head->next;
	p->next = NULL;
	delete p;
	return true;
}

// xóa vị trí bất kỳ
bool xoaOViTriBatKy(dsKhoHang& ds, Node* p, int k)
{
	Node* q = ds.head;
	if (p == NULL)
		return false;
	int i = 1;
	while (q != NULL)
	{
		if (i == k - 1)
		{
			p = q->next;
			q->next = p->next;
			p->next = NULL;
			delete p;
			return true;
		}
		q = q->next;
	}
	return false;
}

// xóa cuối
bool xoaOViTriCuoi(dsKhoHang& ds, Node* p)
{
	if (p == NULL)
		return false;
	p = ds.head;
	Node* q = ds.tail;
	while (p != NULL)
	{
		if (p->next == ds.tail)
		{
			p->next = ds.tail->next;
			ds.tail = p;
			delete q;
			return true;
		}
		p = p->next;
	}
	return false;
}

// sửa
bool suaKhoHangTrongDanhSach(dsKhoHang& ds, Node* p, string maKho)
{


	p = ds.head;
	while (p != NULL)
	{
		if (p->data.maKhoHang == maKho)
		{
			p->data = suaDuLieuKho(p->data.maKhoHang);
			return true;
		}
		p = p->next;
	}
	return false;
}

KhoHang suaDuLieuKho(string maKho)
{
	KhoHang khoHang;
	khoHang.maKhoHang = maKho;
	cout << endl << "Nhập tên kho hàng: ";
	cin.ignore();
	getline(cin, khoHang.tenKhoHang);
	cout << endl;

	cout << endl << "Địa điểm kho hàng: ";
	getline(cin, khoHang.diaDiem);

	cout << endl << "Loại hàng hóa: ";
	getline(cin, khoHang.loaiHangHoa);

	cout << endl << "Nhập tải trọng kho hàng (tấn) : ";
	cin >> khoHang.taiTrong;

	while (khoHang.taiTrong < 0)
	{
		cout << endl << "Tải trọng không được bé hơn 0" << endl;
		cout << endl << "Nhập lại tải trọng kho hàng (tấn) : ";
		cin >> khoHang.taiTrong;
	}

	cout << endl << "Nhập ngày nhập hàng: ";
	cin >> khoHang.ngayNhapHang.ngay >> khoHang.ngayNhapHang.thang >> khoHang.ngayNhapHang.nam;

	cout << endl << "Nhập ngày xuất hàng: ";
	cin >> khoHang.ngayXuatHang.ngay >> khoHang.ngayXuatHang.thang >> khoHang.ngayXuatHang.nam;

	while (!kiemTraNgay(khoHang.ngayNhapHang, khoHang.ngayXuatHang))
	{
		cout << endl << "Ngày xuất phải lớn hơn hoặc bằng ngày nhập" << endl;
		cout << endl << "Mời bạn nhập lại ngày xuất hàng: ";
		cin >> khoHang.ngayXuatHang.ngay >> khoHang.ngayXuatHang.thang >> khoHang.ngayXuatHang.nam;
	}

	cout << endl << "Nhập tải trọng hàng nhập (tấn) : ";
	cin >> khoHang.taiTrongHangNhap;
	cout << endl;

	while ((khoHang.taiTrongHangNhap < 0) || (khoHang.taiTrongHangNhap > khoHang.taiTrong))
	{
		cout << endl << "Tải trọng hàng nhập bé hơn 0 hoặc tải trọng hàng nhập lớn hơn tải trọng" << endl;
		cout << endl << "Nhập tải trọng hàng nhập (tấn) : ";
		cin >> khoHang.taiTrongHangNhap;
		cout << endl;
	}

	return khoHang;
}

void sapXepTheoTaiTrong(dsKhoHang& ds)
{
	Node* p = ds.head; Node* q = new Node;
	if (p == NULL && q == NULL)
		return;

	while (p != NULL)
	{
		q = p->next;
		while (q != NULL) {
			if (p->data.taiTrong > q->data.taiTrong) {
				KhoHang temp = q->data;
				q->data = p->data;
				p->data = temp;
			}
			q = q->next;
		}
		p = p->next;
	}
}

// 5. Thêm 1 kho vào danh sách sao cho vẫn đảm bảo thứ tự
void themVanDamBao(Node* p, dsKhoHang& ds)
{

	if (!ds.head || ds.head->data.taiTrong >= p->data.taiTrong)
	{
		themDauDanhSach(ds, p);
		return;
	}
	Node* current = ds.head;
	while (current->next && current->next->data.taiTrong < p->data.taiTrong)
	{
		current = current->next;
	}
	p->next = current->next;
	current->next = p;
}

//6. Tìm danh sách các kho vừa nhập hàng vào tháng x năm y
bool timNhapVao(dsKhoHang ds, int thang, int nam)
{
	Node* current = ds.head;
	int count = 0;
	while (current)
	{
		if (current->data.ngayNhapHang.thang == thang && current->data.ngayNhapHang.nam == nam) {
			cout << "Mã kho hàng: " << current->data.maKhoHang << endl;
			cout << "Tên kho hàng: " << current->data.tenKhoHang << endl;
			cout << "Địa điểm: " << current->data.diaDiem << endl;
			cout << "Tải trọng (tấn) : " << current->data.taiTrong << endl;
			cout << "Loại hàng hóa: " << current->data.loaiHangHoa << endl;
			cout << "Ngày nhập hàng: " << current->data.ngayNhapHang.ngay << "/" << current->data.ngayNhapHang.thang << "/" << current->data.ngayNhapHang.nam << endl;
			cout << "Ngày xuất hàng: " << current->data.ngayXuatHang.ngay << "/" << current->data.ngayXuatHang.thang << "/" << current->data.ngayXuatHang.nam << endl;
			cout << "Tải trọng hàng nhập (tấn) : " << current->data.taiTrongHangNhap << endl;
			cout << endl;
			count++;
		}
		current = current->next;
	}
	if (count == 0)
		return false;
}

// 7. Tìm kho nào còn trống
bool timKhoTrong(dsKhoHang ds)
{
	Node* p = ds.head;
	int count = 0;
	while (p != nullptr)
	{
		if (p->data.taiTrongHangNhap < p->data.taiTrong)
		{
			cout << "Mã kho hàng: " << p->data.maKhoHang << endl;
			cout << "Tên kho hàng: " << p->data.tenKhoHang << endl;
			cout << "Địa điểm: " << p->data.diaDiem << endl;
			cout << "Tải trọng (tấn) : " << p->data.taiTrong << endl;
			cout << "Loại hàng hóa: " << p->data.loaiHangHoa << endl;
			cout << "Ngày nhập hàng: " << p->data.ngayNhapHang.ngay << "/" << p->data.ngayNhapHang.thang << "/" << p->data.ngayNhapHang.nam << endl;
			cout << "Ngày xuất hàng: " << p->data.ngayXuatHang.ngay << "/" << p->data.ngayXuatHang.thang << "/" << p->data.ngayXuatHang.nam << endl;
			cout << "Tải trọng hàng nhập (tấn) : " << p->data.taiTrongHangNhap << endl;
			cout << endl;
			count++;
		}
		p = p->next;
	}
	if (count == 0)
		return false;
}

bool timKhoHangTheoLoai(string loai, dsKhoHang ds)
{
	Node* temp = ds.head;
	int count = 0;
	while (temp != NULL && temp != ds.tail->next)
	{
		if (temp->data.loaiHangHoa == loai)
		{
			cout << "Mã kho: " << temp->data.maKhoHang << ", Tên kho: " << temp->data.tenKhoHang << endl;
			count++;
		}
		temp = temp->next;
	}
	if (count == 0)
		return false;
}

double tinhTaiTrongTrungBinh(dsKhoHang ds, string diaDiem)
{
	double tongTaiTrong = 0;
	int count = 0;
	Node* temp = ds.head;
	while (temp != nullptr && temp != ds.tail->next)
	{
		if (temp->data.diaDiem == diaDiem)
		{
			tongTaiTrong += temp->data.taiTrong;
			count++;
		}
		temp = temp->next;
	}
	return count > 0 ? tongTaiTrong / count : 0;
}

int demKhoHangBatDauBang(dsKhoHang ds, string prefix)
{
	int count = 0;
	Node* temp = ds.head;
	while (temp != nullptr && temp != ds.tail->next)
	{
		if (temp->data.tenKhoHang.substr(0, prefix.length()) == prefix)
		{
			count++;
		}
		temp = temp->next;
	}
	return count;
}

void sapXepTheoMa(dsKhoHang& ds)
{
	Node* p = ds.head, * q = new Node;
	if (p == NULL && q == NULL)
		return;

	while (p != NULL)
	{
		q = p->next;
		while (q != NULL) {
			string ma1 = p->data.maKhoHang.substr(2, 3);
			string ma2 = q->data.maKhoHang.substr(2, 3);
			if (ma1 > ma2) {
				KhoHang temp = q->data;
				q->data = p->data;
				p->data = temp;
			}
			q = q->next;
		}
		p = p->next;
	}
}

void danhSachTaiTrongConLaiTrongKhoHang(dsKhoHang ds)
{
	Node* p = ds.head;
	if (p == NULL)
	{
		cout << endl << "Bộ nhớ đầy";
		return;
	}
	cout << endl << "    <<<<Danh sách tải trọng còn lại của các kho>>>>       " << endl;
	while (p != NULL)
	{
		float taiTrongConLai = p->data.taiTrong - p->data.taiTrongHangNhap;
		cout << endl << "Mã kho hàng: " << p->data.maKhoHang;
		cout << endl << "Tên kho hàng: " << p->data.tenKhoHang << endl;

		if (taiTrongConLai > 0)
		{
			cout << "Tải trọng còn lại trong kho: " << taiTrongConLai << endl;
		}
		else
		{
			cout << "Tải trọng còn lại trong kho: đã đầy" << endl;
		}
		p = p->next;
	}
}

void hienThiTop5TaiTrongLonNhat(dsKhoHang ds)
{
	vector<KhoHang> danhSachKho;
	Node* p = ds.head;
	while (p != NULL) {
		danhSachKho.push_back(p->data);
		p = p->next;
	}

	sort(danhSachKho.begin(), danhSachKho.end(),
		[](const KhoHang& a, const KhoHang& b) { return a.taiTrong > b.taiTrong; });

	cout << "Top 5 kho hàng có tải trọng lớn nhất:" << endl;
	for (int i = 0; i < min(5, (int)danhSachKho.size()); i++) {
		cout << i + 1 << ". Mã kho: " << danhSachKho[i].maKhoHang
			<< ", Tải trọng: " << danhSachKho[i].taiTrong << " tấn" << endl;
	}
}

void locTheoThoiGian(dsKhoHang ds, NgayThangNam batDau, NgayThangNam ketThuc)
{
	Node* p = ds.head;
	while (p != NULL) {
		if (kiemTraNgay(batDau, p->data.ngayNhapHang) && kiemTraNgay(p->data.ngayNhapHang, ketThuc)) {
			
				cout << "Mã kho: " << p->data.maKhoHang << ", Ngày nhập: "
					<< p->data.ngayNhapHang.ngay << "/" << p->data.ngayNhapHang.thang << "/" << p->data.ngayNhapHang.nam << endl;
		}
		p = p->next;
	}
}
