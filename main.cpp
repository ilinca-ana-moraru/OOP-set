/*
implementare în C++ folosind clase

constructori de inițializare 

constructor de copiere 

operator de atribuire

operator == și operator != (unde are sens)

destructori

supraîncărcarea operatorilor << și >> pentru ieșiri și intrări de obiecte

get / set pentru toate datele membru

alocare dinamică

să se poată realiza citirea și afișarea a n obiecte

programul să aibă un meniu interactiv

folosiți const peste tot unde puteți

nu folosiți std::string, std::vector, std::queue, std::stack, etc.

CERINTE PARTICULARE:

Membrii privați pentru vectorul propriu zis și numărul de elemente

Se vor filtra valorile astfel încât să nu existe elemente duplicate

reuniune a două mulțimi, implementată prin supraîncărcarea operatorului +

intersecție a două mulțimi, implementată prin supraîncărcarea operatorului *

diferența a două mulțimi, implementată prin supraîncărcarea operatorului -

metodă publică len pentru a obține numărul de elemente prezente în mulțime
*/

#include <iostream>
#include <cstdarg>
using namespace std;

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}


class set{
    private:

        int* arr;
        int n;

    public:

        // constructor de initializare, initializeaza cu multimea vida
        set(){
            n = 0;
            arr = NULL;
        }

       // constructor de initializare
        set (int N, ...){

            n = N;
            va_list args;
            va_start(args,N);
            arr = new int[N ];
            for(int i = 0; i < N; i++){
                arr[i] = va_arg(args,int);
            }
            va_end(args);

            dublicates_remover();

        }


        //setter de lungime
        void lenght_setter(int new_lenght){

            n = new_lenght;
            delete [] arr;
            arr = new int[n * sizeof(int)];

        }
        
        void dublicates_remover(){

            qsort(arr, n, sizeof(int), cmpfunc);
       
            int next = 1;
            int i = 0;
            while (next < n)
                {
                    if(arr[i] == arr[next])
                        next++;
                    else {
                        i++;
                        arr[i] = arr[next];
                        next++;
                
                    }
                }
                n = i+1; 
        } 
        
        //setter de un singur element, reperat prin indice
        void element_setter(int poz, int value){
            if(poz < n){
                arr[poz] = value;
                dublicates_remover();
            }
        }

        //setter de elemente ale multimii
        void set_setter (int N, ...){

            delete [] arr;
            va_list args;
            va_start(args, N);
            delete [] arr;
            arr = new int[N];
            for(int i = 0; i < N; i++){
                arr[i] = va_arg(args,int);
            }
            va_end(args);
            dublicates_remover();

        }

        // returneaza numarul de elemente
        int get_lenght() const{

            return n;

        }

        // returneaza adresa vectorului
        int* get_set() const{
            
            return arr;

        }


        friend istream& operator>>(istream &is, set &s) {

        is >> s.n;
        s.lenght_setter(s.n);
        
        for(int i = 0; i < s.n; i++){
            is >> s.arr[i];
        }

        return is;
    }
    
        friend ostream& operator<<(ostream &os, set &s) {
          for(int i = 0; i < s.n; i++)
            os << s.arr[i] << " ";
          os << endl;

        return os;
    }


        // constructor de copiere
        set(const set &rhs) {
            
            //cout<<"tocmai ai apelat constructorul de copiere"<<endl;
            n = rhs.n;
            arr = new int[n ];

            for(int i = 0; i < n; i++){
                arr[i] = rhs.arr[i];    
            }
        }

        //operator de atribuire
        set& operator=(const set &rhs){

            //cout<<"tocmai ai apelat operatorul de atribuire"<<endl;
            if(this != &rhs){

                n = rhs.n;
                delete [] arr;
                arr = new int[n ];

                for(int i = 0; i < n; i++){
                    arr[i] = rhs.arr[i];    
                }
            }
            return *this;
        }



        void add(int N, ...){
            int *aux = new int[n+N];
            for(int i = 0; i<n; i++){
                aux[i] = arr[i];
            }
            
            va_list args;
            va_start(args, N);

            for(int i = n; i < n+N; i++){
                aux[i] = va_arg(args,int);
            }
            va_end(args);
            
            n = n + N;

            delete [] arr;
            arr = new int[n];
            for(int i = 0; i < n; i++)
                arr[i] = aux[i];

            dublicates_remover();
            
            delete [] aux;
        }


        bool operator==(const set &rhs) const{
            if (n != rhs.n) return false;
            
            for(int i = 0; i < n; i++)
                if(arr[i] != rhs.arr[i])
                return false;
            
            return true;
        }

        bool operator!=(const set &rhs) const{
            if (n != rhs.n) return true;

            for(int i = 0; i < n; i++)
                if(arr[i] != rhs.arr[i])
                return true;
            
            return false;
        }

        set operator+(const set&rhs) const{
            
            set aux;
           
            aux.arr = new int[n + rhs.n ];
            for(int i = 0; i<n; i++){
                aux.arr[i] = arr[i];
            }
            
            for(int i = n; i < n+rhs.n; i++){
                aux.arr[i] = rhs.arr[i-n];
            }
            
            aux.n = n + rhs.n;
            aux.dublicates_remover();

            return aux;
                
        }

        set operator*(const set&rhs) const{
            
            set aux;
           
            aux.arr = new int[n + rhs.n ];
          
            int i = 0, j = 0, k = 0;
            while(i < n && j < rhs.n){
                if(arr[i] == rhs.arr[j]){
                    aux.arr[k] = arr[i];
                    i ++;
                    j ++;
                    k ++;
                }

                else if(arr[i] < rhs.arr[j])
                    i++;
                
                else if(arr[i] > rhs.arr[j])
                    j++;
            }
            
            aux.n = k;
            
            return aux;       
        }

        set operator-(const set&rhs) const{
            
            set aux;
           
            aux.arr = new int[n + rhs.n];
          
            int i = 0, j = 0, k = 0;
            while(i < n && j < rhs.n){
                if(arr[i] == rhs.arr[j]){
                    i ++;
                    j ++;
                }

                else if(arr[i] > rhs.arr[j]){
                    j++;
                    
                }
                
                else if(arr[i] < rhs.arr[j]){
                    aux.arr[k] = arr[i];
                    i++;
                    k++;
                }
            }

            while(i < n){
                aux.arr[k] = arr[i];
                i++;
                k++;
            }
            
            aux.n = k;
            return aux;
        }

        //destructor
        ~set(){

            delete[] arr;

        }

};



int main(){
    int parameter;
    set * SET;
    int nr_of_sets = 0;
    int a = 1;
    
    while(a){
        cout <<" -------------------------------------------------";
        if(nr_of_sets)
            cout<<endl<<"in acest moment lucram cu multimile:"<<endl<<endl;
            
        for(int i = 0; i < nr_of_sets; i++){
            cout<<"multimea "<<i+1<<":";
            cout << SET[i];
        }
         cout <<endl;
        cout<<"tasteaza: "<<" | -1 -> incheierea jocului "<<"| 1 -> adaugare de multime "<<
        "| 2 -> eliminare de multime "<<"| 3 -> copiere de multime intr o noua multime "
        <<"| 4 -> adaugare de elemente multimii "<<"| 5 -> eliminare de elemente ale unei multimi "
        <<"| 6 -> reuniune a două mulțimi intr-o noua multime "
        <<"| 7 -> intersecție a două mulțimi intr-o noua multime"
        <<"| 8 -> diferenta a două mulțimi intr-o noua multime "
        <<"| 9 -> sunt doua multimi egale? "
        <<"| 10 -> sunt doua multimi inegale? |"<<endl;
        
        cin>>parameter;
        cout<<endl;
        switch (parameter)
        {
        case 1: //initializare multime
            {
            set* aux = new set[nr_of_sets+1];
            for(int i = 0; i < nr_of_sets; i++)
                aux[i] = SET[i];

            cout<<"tasteaza nr de elemente pe care vrei sa le adaugi, apoi elementele"<<endl;
            set new_set;
            cin>> new_set;
     
            
            new_set.dublicates_remover();
            aux[nr_of_sets] = new_set;
            nr_of_sets++;
            SET = new set[nr_of_sets];
            
            for(int i = 0; i < nr_of_sets; i++){
                SET[i] = aux[i];   
            }
            delete [] aux; 
            break;
            }
            
        case 2: //stergere multime
            {
            cout<<"alege numarul multimii pe care vrei sa o stergi"<<endl;  
            int poz_sterg;
            cin>>poz_sterg;
            poz_sterg --;
            set* aux = new set[nr_of_sets-1];
            
            for(int i = 0; i < poz_sterg; i++)
                aux[i] = SET[i];
            
            for(int i = poz_sterg; i < nr_of_sets-1; i++)
                aux[i] = SET[i+1];

            nr_of_sets--;
            SET = new set[nr_of_sets];
            
            for(int i = 0; i < nr_of_sets; i++){
                SET[i] = aux[i];
            }
            delete [] aux;
            break;
            }
        
        case 3:{// copiere de multime intr o noua multime
            set* aux = new set[nr_of_sets+1];
            
            for(int i = 0; i < nr_of_sets; i++)
                aux[i] = SET[i];
                
            cout<<"tasteaza nr multimii pe care vrei sa o copiezi"<<endl;
            int to_copy;
            cin>>to_copy;
            cout<<endl;
            set new_set = SET[to_copy-1];
            aux[nr_of_sets] = new_set;
            nr_of_sets++;
            SET = new set[nr_of_sets];
            
            for(int i = 0; i < nr_of_sets; i++){
                SET[i] = aux[i];
            }
            delete [] aux;
            break;
        }
        
        case 4:{ // adaugare de elemente intr o multime

            cout<<"tasteaza multimea careia doresti sa ii adaugi elemente"<<endl;
            int set_to_add;
            cin>>set_to_add;
            cout<<"tasteaza cate elemente iti doresti sa adaugi, apoi elementele"<<endl;
            set new_set;
            cin >> new_set;
            
            new_set.dublicates_remover();
            SET[set_to_add-1] = SET[set_to_add-1] + new_set;
            SET[set_to_add].dublicates_remover();
            break;
        }
    
        case 5:{ // eliminarea de elemente intr o multime
        
            cout<<"tasteaza multimea careia doresti sa ii elimini elemente"<<endl;
            int set_to_modify;
            cin>>set_to_modify;
            cout<<"tasteaza cate elemente iti doresti sa elimini, apoi elementele"<<endl;
            set new_set;
            cin >> new_set;
            new_set.dublicates_remover();
            SET[set_to_modify-1] = SET[set_to_modify-1] - new_set;
            break;
        }
        
        case 6:{ //reuniune a două mulțimi intr-o noua multime
            cout<<"tasteaza multimile pe care doresti sa le reunesti"<<endl;
            int m1, m2;
            cin>>m1>>m2;
            set* aux = new set[nr_of_sets+1];
            
            for(int i = 0; i < nr_of_sets; i++)
                aux[i] = SET[i];
                
            set new_set = SET[m1-1] + SET[m2-1];
            new_set.dublicates_remover();
            aux[nr_of_sets] = new_set;
            nr_of_sets++;
            SET = new set[nr_of_sets];
            for(int i = 0; i < nr_of_sets; i++){
                SET[i] = aux[i];
                
            }
            delete [] aux;
            break;
            
        }
        
        case 7:{ //intersecție a două mulțimi intr-o noua multime
            cout<<"tasteaza multimile pe care doresti sa le intersectezi"<<endl;
            int m1, m2;
            cin>>m1>>m2;
            set* aux = new set[nr_of_sets+1];
            
            for(int i = 0; i < nr_of_sets; i++)
                aux[i] = SET[i];

            set new_set = SET[m1-1] * SET[m2-1];
            new_set.dublicates_remover();
            aux[nr_of_sets] = new_set;
            nr_of_sets++;
            SET = new set[nr_of_sets];
            
            for(int i = 0; i < nr_of_sets; i++){
                SET[i] = aux[i];
                
            }
            delete [] aux;
            break;
    
        }
        
        case 8:{ //diferența a două mulțimi intr-o noua multime
            cout<<"tasteaza multimile pe care doresti sa le scazi"<<endl;
            int m1, m2;
            cin>>m1>>m2;
            set* aux = new set[nr_of_sets+1];
            
            for(int i = 0; i < nr_of_sets; i++)
                aux[i] = SET[i];

            set new_set = SET[m1-1] - SET[m2-1];
            new_set.dublicates_remover();
            aux[nr_of_sets] = new_set;
            nr_of_sets++;
            SET = new set[nr_of_sets];
            
            for(int i = 0; i < nr_of_sets; i++){
                SET[i] = aux[i];
                
            }
            delete [] aux;
            break;
    
        }
        
        
        case 9:{ //sunt doua multimi egale?
            cout<<"tasteaza multimile despre care doresti sa stii daca sunt egale"<<endl;
            int s1, s2;
            cin>>s1>>s2;
            
            if(SET[s1-1] == SET[s2-1])
                cout<<"cele doua multimi sunt egale!"<<endl;
                
            else cout <<"cele doua multimi nu sunt egale!"<<endl;
            break;
        }

        
        case 10:{ //sunt doua multimi inegale?
            cout<<"tasteaza multimile despre care doresti sa stii daca sunt inegale"<<endl;
            int s1, s2;
            cin>>s1>>s2;
            
            if(SET[s1-1] != SET[s2-1])
                cout<<"cele doua multimi sunt inegale!"<<endl;
                
            else cout <<"cele doua multimi nu sunt inegale!"<<endl;
            break;
            
        }

        case -1:
            {cout<<"jocul s-a incheiat"<<endl;
            a = 0;
            break;
                
            }
            
        }

        }
    
    return 0;
}