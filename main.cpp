#include <iostream>
#include <set>

using namespace std;

class Dynamic {
    string masname;
    int *pointer_to_mas;
    int mas_el_count;
public:
    Dynamic () {
        masname = "unnamed";
        mas_el_count = 0;
        pointer_to_mas = nullptr;
        cout << "Initialized dynamic array " << masname << " with " << mas_el_count << " elements: no parameters were given." << endl;
    }
    Dynamic (const Dynamic& other)
    {
        masname = other.masname + " copy";
        mas_el_count = other.mas_el_count;
        pointer_to_mas = new int[mas_el_count];
        for (int i = 0; i < mas_el_count; i++){
            pointer_to_mas[i] = other.pointer_to_mas[i];
        }
        cout << "Copied array \"" << other.masname << "\", new array name: \"" << masname << "\".\n";
    }
    Dynamic (const string& name, const int& numofelems) {
        masname = name;
        mas_el_count = numofelems;
        pointer_to_mas = new int[mas_el_count];
        cout << "Initialized dynamic array " << masname << " with " << mas_el_count << " elements: parameters masname(\"" << masname << "\") and numofelements(" << numofelems << ") were given." << endl;
    }
    ~Dynamic(){
        if(pointer_to_mas){
            delete [] pointer_to_mas;
            mas_el_count = 0;
            pointer_to_mas = nullptr;
            cout << "Destroyed dynamic array " << masname << "." << endl;
        }
        else{
            cout << "Destroyed empty unnamed dynamic array." << endl;
        }
    }

    Dynamic next() {
        Dynamic resultArr(*this);
        for(int i = 0; i < resultArr.size(); ++i){
            resultArr[i] += 1;
        }
        return resultArr;
    }

    int& size() {return mas_el_count;}
    string name(){
        return masname;
    }
    int* dbegin(){
        return pointer_to_mas;
    }

    int& operator[](int);
    Dynamic operator-(Dynamic& mas);
    Dynamic operator-(const int& num);
    friend Dynamic operator-(int& num, Dynamic& mas);
    Dynamic operator=(Dynamic mas);
    friend ostream& operator<<(ostream& os, const Dynamic& mas);
    friend istream& operator>>(istream& is, Dynamic& mas);
};

Dynamic Dynamic::operator-(Dynamic& right){
    int new_el_count = this->mas_el_count;
    set<int> setofr;
    for (int i = 0; i < right.mas_el_count; i++) {
        setofr.insert(right[i]);
    }
    for(int i = 0; i < this->mas_el_count; i++){
        if (setofr.find(this->pointer_to_mas[i]) != setofr.end()) {
            new_el_count--;
        }
    }
    Dynamic left(this->masname, new_el_count);
    int k = 0;
    for (int i = 0; i < this->mas_el_count; i++) {
        if (setofr.find(this->pointer_to_mas[i]) == setofr.end()) {
            left[k] = this->pointer_to_mas[i];
            k++;
        }
    }
    return left;
}

Dynamic Dynamic::operator-(const int &num) {
    int new_el_count = mas_el_count;
    for(int i = 0; i < mas_el_count; i++){
        if (pointer_to_mas[i] == num) {
            new_el_count--;
        }
    }
    Dynamic left(this->masname, new_el_count);
    int k = 0;
    for (int i = 0; i < this->mas_el_count; i++) {
        if (pointer_to_mas[i] != num) {
            left[k] = pointer_to_mas[i];
            k++;
        }
    }
    return left;
}

int& Dynamic::operator[](int index){
    if (index >=mas_el_count){
        cout << "Out of range in \"" << masname << "\". Returned " << masname << "[0]." << endl;
        return pointer_to_mas[0];
    }
    else {
        return pointer_to_mas[index];
    }
}

Dynamic Dynamic::operator=(Dynamic mas) {
    mas_el_count = mas.mas_el_count;
    pointer_to_mas = new int[mas_el_count];
    for(int i = 0; i < mas_el_count; i++){
        pointer_to_mas[i] = mas.pointer_to_mas[i];
    }
    cout << "\nAssigned array \"" << mas.masname << "\" to array \"" << masname << "\".\n";
    return *this;
}

ostream &operator<<(ostream &os, const Dynamic &mas) {
    os << "[";
    for (int i = 0; i < mas.mas_el_count - 1; ++i){
        os << mas.pointer_to_mas[i] << ", ";
    }
    os << mas.pointer_to_mas[mas.mas_el_count - 1] << "]";
    return os;
}

istream &operator>>(istream &is, Dynamic &mas) {
    for (int i = 0; i < mas.mas_el_count; ++i) is >> mas.pointer_to_mas[i];
    return is;
}

void F () {
    Dynamic A ("A", 10), B ("B", 5);
//введення елементів масивів А та В
    for(int i = 0; i < A.size(); i++) A[i] = i;
//    cout << "Input A:";
//    cin >> A;
    for(int i = 0; i < B.size(); i++) B[i] = 2 * i;
    cout << A << endl << B << endl;
    cout << "A.next().next()" << A.next().next() << endl;
    Dynamic C = A;
    Dynamic D ("D", 10);
    D = A - B; // замість ‘@’ підставте свою операцію над масивами
    //виведення масивів A, B, C, D
    cout << A << endl << B << endl << C << endl << D << endl;
}

int main() {
    F();

}
