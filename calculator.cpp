#include <iostream>
#include <string>
using namespace std;

struct calc {
    int no;
    string nama;
    string unit;
    float jumlahUnit;
    float CO2;
    float CH4;
    float N20;
    calc* next;
};

struct Emisi {
    string nama;
    string unit;
    float CO2;
    float CH4;
    float N20;  
};

void pushBack(calc*& head, int no, string nama, string unit, float faktorCO2, float faktorCH4, float faktorN20, float jumlahUnit) {
    calc* newNode = new calc;
    newNode->no = no;
    newNode->nama = nama;
    newNode->unit = unit;
    newNode->jumlahUnit = jumlahUnit;
    newNode->CO2 = faktorCO2 * jumlahUnit;         
    newNode->CH4 = faktorCH4 * jumlahUnit;
    newNode->N20 = faktorN20 * jumlahUnit;

    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
        return;
    }

    calc* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void deleteNode(calc*& head, int noD, int &id) {
    if (head->no == noD) {          
        calc* temp = head;
        head = head->next;
        delete temp;

        calc* curr = head;         
        while (curr != NULL) {
            curr->no--;     
            curr = curr->next;
        }
        id--;

        cout << "Node " << noD << " berhasil dihapus" << endl;
        return;
    }

    calc* curr = head;          
    while (curr->next != NULL && curr->next->no != noD) {
        curr = curr->next;
    }
       
    if (curr->next == NULL) {
        cout << "Node dengan nomor " << noD << " tidak ditemukan" << endl;    
        return;
    }
    
    if (curr->next != NULL) {         
        calc* temp = curr->next;
        curr->next = temp->next;
        delete temp;

        curr = curr->next;         
        while (curr != NULL) {
            curr->no--;
            curr = curr->next;
        }
        id--;

        cout << "Node " << noD << " berhasil dihapus" << endl;
    }
}

void printList(calc* head, bool &chk) {
    if (head == NULL) {        
        cout << "List kosong" << endl;
        chk = true;
        return;
    }

    calc* head2 = head;
    while (head2 != NULL) {
        cout << "No   : " << head2->no << endl;
        cout << "Nama : " << head2->nama << endl;
        cout << "Unit : " << head2->jumlahUnit << " " << head2->unit << endl;
        cout << "CO2  : " << head2->CO2 << " gram" << endl;
        cout << "CH4  : " << head2->CH4 << " gram" << endl;
        cout << "N2O  : " << head2->N20 << " gram" << endl;
        cout << "----------------------------------------------" << endl;

        head2 = head2->next;
    }
}

int main() {
    Emisi data[] = {
        {"Motor", "Km", 151, 0.0207, 0.0016},
        {"Mobil Bensin", "Km", 203, 0.0048, 0.0031},
        {"Mobil Diesel", "Km", 210, 0.0036, 0.0062},
        {"Mobil Hybrid", "Km", 93, 0.0008, 0.0003},
        {"Truk CNG/Diesel", "Km", 714, 0.2208, 0.0004},
        {"Bus CNG/Diesel", "Km", 714, 0.2208, 0.0004},
        {"AC rumah tangga (0.8 kW)", "Jam", 619, 0.0128, 0.0070},
        {"Kulkas (250 W)", "Jam", 194, 0.00399, 0.00219},
        {"Dispenser air panas (700 W)", "Jam", 542, 0.0112, 0.0061},
        {"Rice cooker (500 W)", "Jam", 387, 0.00797, 0.0044},
        {"Televisi LED (100 W)", "Jam", 77.4, 0.00159, 0.00088},
        {"Laptop (60 W)", "Jam", 46.5, 0.00096, 0.00053},
        {"Charger HP (10 W)", "Jam", 7.74, 0.00016, 0.00009}
    };

    calc* head = NULL;
    bool status = true;
    int select, id = 0;

    do {
        cout << "=======================================================================================" << endl;
        cout << "1. insert" << endl;
        cout << "2. delete" << endl;
        cout << "3. show data" << endl;
        cout << "4. sum" << endl;
        cout << "5. exit" << endl;
        cout << "=======================================================================================" << endl;            
        cout << "pilih : " ;
        cin >> select;

        switch (select) {
            case 1: {
                int no, c1pilih;
                string nama, unit;
                float faktorCO2, faktorCH4, faktorN20;
                float jumlahUnit;
                
                for(int i = 0; i < 13; i++){  
                    cout << i+1 << ". " << data[i].nama << endl;

                }
                cout << "99. custom" << endl;
                cout << "----------------------------------------" << endl;
                cout << "pilih : ";
                cin >> c1pilih;

                if(c1pilih == 99){
                    id++;
                    no = id;
                    cout << "Nama               : "; 
                    getline(cin >> ws, nama);
                    cout << "Unit (ex= km, jam) : "; 
                    cin >> unit;
                    cout << "Jumlah Unit        : "; 
                    cin >> jumlahUnit;
                    cout << "Faktor CO2 (gram)  : "; 
                    cin >> faktorCO2;
                    cout << "Faktor CH4 (gram)  : "; 
                    cin >> faktorCH4;
                    cout << "Faktor N2O (gram)  : "; 
                    cin >> faktorN20;

                    pushBack(head, no, nama, unit, faktorCO2, faktorCH4, faktorN20, jumlahUnit);
                }

                else if(c1pilih > 13 && c1pilih <= 99 || c1pilih == 0){
                    cout << "----------------------------------------" << endl;
                    cout << "pilihan tidak tersedia" << endl;
                }
                
                else{
                    id++;
                    no = id;
                    cout << "----------------------------------------" << endl;
                    cout << "unit : " << data[c1pilih-1].unit << endl;
                    cout << "Jumlah Unit   : "; 
                    cin >> jumlahUnit;
                    nama = data[c1pilih-1].nama;
                    unit = data[c1pilih-1].unit;
                    faktorCO2 = data[c1pilih-1].CO2;
                    faktorCH4 = data[c1pilih-1].CH4;
                    faktorN20 = data[c1pilih-1].N20;
                    pushBack(head, no, nama, unit, faktorCO2, faktorCH4, faktorN20, jumlahUnit);
                }
                
                break;
            }

            case 2: {
                int noD;
                bool chk = false;
                printList(head, chk);

                if (chk == true) {
                    break;
                }
                cout << "----------------------------------------" << endl;
                cout << "Masukkan no yang ingin dihapus : ";
                cin >> noD;
                deleteNode(head, noD, id);
                break;
            }

            case 3: {
                bool chk = false;
                printList(head, chk);
                break;
            }
            
            case 4: {
                bool chk = false;
                printList(head, chk);
                float totalCO2 = 0, totalCH4 = 0, totalN20 = 0;
                calc* temp = head;

                while (temp != NULL) {
                    
                    totalCO2 += temp->CO2;
                    totalCH4 += temp->CH4;
                    totalN20 += temp->N20;
                    temp = temp->next;
                }

                cout << "Total CO2 : " << totalCO2 << " gram" << endl;
                cout << "Total CH4 : " << totalCH4 << " gram" << endl;
                cout << "Total N2O : " << totalN20 << " gram" << endl;
                break;
            }

            case 5: {
                status = false;
                break;
            }

            default:
                cout << "Pilihan tidak valid!" << endl;
        }

    } while (status == true);

    return 0;
}
