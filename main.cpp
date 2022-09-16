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
            cout << "Destroyed array " << masname << "." << endl;
        }
        else{
            cout << "Nothing to delete." << endl;
        }
    }

    int& size(){
        return mas_el_count;
    }

    string name(){
        return masname;
    }

    int* dbegin(){
        return pointer_to_mas;
    }

    int& operator[](int);

    Dynamic operator-(Dynamic& mas);

//    Dynamic (const Dynamic& other)
//    {
//        Dynamic tmp;
//        tmp.masname = other.masname;
//        tmp.mas_el_count = other.mas_el_count;
//        tmp.pointer_to_mas = new int[tmp.mas_el_count];
//        for (int i = 0; i < tmp.mas_el_count; i++){
//            tmp.pointer_to_mas[i] = other.pointer_to_mas[i];
//        }
//        return *this;
//    }
};

Dynamic Dynamic::operator-(Dynamic& right){
    int new_el_count = this->mas_el_count;
    set<int> setofr;
    for (int i = 0; i < right.mas_el_count; i++) setofr.insert(right[i]);
    for(int i = 0; i < this->mas_el_count; i++){
        if (setofr.find(this->pointer_to_mas[i]) == setofr.end()) {
            new_el_count--;
        }
    }
    Dynamic left(this->masname, new_el_count);
    int k = 0;
    for (int i = 0; i < this->mas_el_count; i++) {
        if (setofr.find(this->pointer_to_mas[i]) != setofr.end()) {
            left[k] = this->pointer_to_mas[i];
            k++;
        }
    }
    return left;
}


int& Dynamic::operator[](int index){
    if (index >=mas_el_count){
        this->~Dynamic();
        throw out_of_range("Index out of range in array \"" + this->masname + '"');
    }
    return pointer_to_mas[index];
}

void outdmas(Dynamic& dmas){
    cout << "[";
    for (int i = 0; i < dmas.size(); i++){
        cout << dmas[i] << ", ";
    }
    cout << "]" << endl;
}

void F () {
    Dynamic A ("A", 10), B ("B", 5);
//введення елементів масивів А та В
    outdmas(A);
    outdmas(B);
    Dynamic C = A;
    Dynamic D ("D", 10);
    D = A - B; // замість ‘@’ підставте свою операцію над масивами
//виведення масивів A, B, C, D
    outdmas(A);
    outdmas(B);
    outdmas(C);
    outdmas(D);
}

int main() {
    F();

}
