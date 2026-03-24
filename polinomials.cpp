#include <iostream>
#include <complex>
#include <vector>
#include <stdint.h>
#include <iomanip>
using namespace std;

class Polynomial{
protected:
    std::vector<double> mCoeffs;
    uint32_t mDegree;
public:
    Polynomial(std::vector<double> cof){
        mCoeffs = cof;
        mDegree = cof.size() - 1;
    }

    Polynomial(uint32_t deg){
        for(int i = 0 ; i <= deg ; i++){
            mCoeffs[i] = 0;
        }
        mDegree = deg;
    }

    Polynomial derivate() const {

        vector<double> coefic;

        if(mCoeffs.size() == 1){
            coefic.push_back(0);
            Polynomial rez(coefic);
            return rez;
        }

        for(int k = 0 ; k <= mDegree; k++){
            coefic.push_back( mCoeffs[k] * (mDegree - k));
        }
        coefic.erase(coefic.begin()+coefic.size()-1);
        Polynomial rez(coefic);
        return rez;
    }

    double calculate(double value) const{
        double suma = 0;
        for(int k = 0 ; k <= mDegree ; k++){
            suma+= mCoeffs[k] * (pow(value , mDegree-k));
        }
        return suma;
    }

    std::complex<double> calculate(const std::complex<double>& value) const{
        std::complex<double> suma(0,0);
        for(int k = 0 ; k <= mDegree ; k++){
            suma+= mCoeffs[k] * (pow(value , mDegree-k));
        }
        return suma;
    }

    uint32_t getDegree() const{
        return mDegree;
    }

    double& operator[](uint32_t index){
        return mCoeffs[index];
    }

    double operator[](uint32_t index) const{
        return mCoeffs[index];
    }

    Polynomial operator+(const Polynomial& rhs) const{
        std::vector<double> coefic;
        int32_t dif = mDegree - rhs.mDegree;
        if(dif ==0){
            for(int k = 0 ; k <= mDegree ; k++){
                coefic.push_back(mCoeffs[k]+rhs.mCoeffs[k]);
            }
        }
        if(dif>0){
            for(int k = 0 ; k <= mDegree; k++){
                coefic.push_back(mCoeffs[k]);
            }
            for(int k = 0 ; k <=rhs.mDegree ; k++){
                coefic[k+dif]+=rhs.mCoeffs[k];
            }
        }
        if(dif < 0){
            for(int k = 0 ; k <= rhs.mDegree ; k++){
                coefic.push_back(rhs.mCoeffs[k]);
            }
            for(int k = 0 ; k <=mDegree ; k++){
                coefic[k-dif]+=mCoeffs[k];
            }
        }
        Polynomial rez(coefic);
        return rez;
    }

    Polynomial operator*(const Polynomial& rhs) const{
        vector<double> coef;
        for(int k = 0 ; k <= mDegree+ rhs.mDegree ; k++){
            coef.push_back(0);
        }
        for(int k = 0 ; k <= mDegree ; ++k){
            for(int w = 0 ; w <= rhs.mDegree ; ++w){
                coef[k+w]+=mCoeffs[k]*rhs.mCoeffs[w];
            }
        }
        Polynomial pol(coef);
        return pol;
    }

    Polynomial& operator*=(const double constant){

        for(int k = 0 ; k <=mDegree ; k++){
            mCoeffs[k]=(double) mCoeffs[k] * constant;
        }

        return *this;
    }

    Polynomial& operator/=(const double constant){
        for(int k = 0 ; k <=mDegree ; k++){
            mCoeffs[k]=(double)(mCoeffs[k] / constant);
        }

        return *this;
    }

    virtual std::vector<std::complex<double>> roots() const{
        cout<<"Implementation for method roots for polynomials with degree = "<<mDegree<<" is not available."<<endl;
        std::vector<std::complex<double>> dou;
        return dou;
    }
};

class ZeroDegreePolynomial : public Polynomial{
public:
    ZeroDegreePolynomial(const std::vector<double>& nr) : Polynomial(nr){
        mDegree = 0;
    }

    std::vector<std::complex<double>> roots() const override{
        cout<<"Polynomials with degree 0 doesn't have roots."<<endl;
        std::vector<std::complex<double>> dou;
        return dou;
    }
};

class FirstDegreePolynomial : public Polynomial{
public:
    FirstDegreePolynomial(const std::vector<double>& nr) : Polynomial(nr){
        mDegree = 1;
    }
    std::vector<std::complex<double>> roots() const override{
        std::vector<std::complex<double>> rez;
        std::complex<double> dr;
        dr = -mCoeffs[1] / mCoeffs[0];
        rez.push_back(dr);
        return rez;
    }
};

class SecondDegreePolynomial : public Polynomial{
public:
    SecondDegreePolynomial(const std::vector<double>& nr) : Polynomial(nr){
        mDegree = 2;
    }

    std::vector<std::complex<double>> roots() const override{
        std::vector<std::complex<double>> rez;
        double c = mCoeffs[2];
        double b = mCoeffs[1];
        double a = mCoeffs[0];
        std::complex<double> dr( -b/(2*a) , sqrt(-(b*b -4*a*c)) /(2*a) );
        std::complex<double> dr2(-b/(2*a) , (-sqrt(-(b*b - 4 *a *c)) / (2*a) ) );
        rez.push_back(dr);
        rez.push_back(dr2);
        return rez;
    }
};

int main(){
    unsigned n;
    cin>>n;
    double c;
    vector<Polynomial*> polin;
    for(int k = 0 ; k < n ; k++){
        vector<double> coef;
        while(cin>>c){
            coef.push_back(c);
            if (cin.peek() == '\n' || cin.peek() == EOF) break;
        }
        if(coef[0]==0 && coef[1]!=0){
            coef.erase(coef.begin());
        }
        if(coef.size() == 1){
            ZeroDegreePolynomial* pol = new ZeroDegreePolynomial(coef);
            polin.push_back(pol);
        }
        if(coef.size() == 2){
            FirstDegreePolynomial* pol = new FirstDegreePolynomial(coef);
            polin.push_back(pol);
        }
        if(coef.size() == 3){
            SecondDegreePolynomial* pol = new SecondDegreePolynomial(coef);
            polin.push_back(pol);
        }
        if(coef.size() > 3){
            Polynomial* pol = new Polynomial(coef);
            polin.push_back(pol);
        }
    }

    string cerinta;
    while(cin>>cerinta){
        if(cerinta == "roots"){
            int index;
            cin>>index;

            if(polin[index]->getDegree() >=3){
                polin[index]->roots();
            }
            if(polin[index]->getDegree() == 0){
                polin[index]->roots();
            }
            if(polin[index]->getDegree() == 1){
                cout<<"Roots of polynomial with index "<<index<<" are:"<<endl;
                cout<<"x1 = "<<fixed<<setprecision(3)<<real(polin[index]->roots()[0])<<endl;
            }
            if(polin[index]->getDegree() == 2){
                cout<<"Roots of polynomial with index "<<index<<" are:"<<endl;
                cout<<"x1 = "<<fixed<<setprecision(3)<<real(polin[index]->roots()[0]);
                if(imag(polin[index]->roots()[0]) != 0) {
                    if (imag(polin[index]->roots()[0]) >= 0) {
                        cout << "+";
                    }
                    cout << imag(polin[index]->roots()[0]) << "*i" << endl;
                }
                else{
                    cout<<endl;
                }
                cout<<"x2 = "<<fixed<<setprecision(3)<<real(polin[index]->roots()[1]);
                if(imag(polin[index]->roots()[1])!=0){
                if(imag(polin[index]->roots()[1]) >= 0){
                    cout<<"+";
                }
                cout<<imag(polin[index]->roots()[1])<<"*i"<<endl;
                }
                else{
                    cout<<endl;
                }
            }
        }
        if(cerinta == "derivate"){
            int index,index1;
            cin>>index>>index1;
            polin[index] = new Polynomial(polin[index1]->derivate());
        }

        if(cerinta == "calculate"){
            int index;
            double val;
            cin>>index>>val;
            double val2;
            if(cin.peek() == ' '){
                cin>>val2;
                complex<double> valoare(val , val2);
                cout<<"Polynomial" <<index<<" evaluated in "<<val<<" is: "<<polin[index]->calculate(valoare);
            }
            else{
                cout<<"Polynomial" <<index<<" evaluated in "<<val<<" is: "<<polin[index]->calculate(val);
            }
        }

        if(cerinta == "add"){
            int index,index1,index2;
            cin>>index>>index1>>index2;
            polin[index] = new Polynomial(*polin[index1] + *polin[index2]);
        }

        if(cerinta == "mult"){
            int index;
            double val;
            cin>>index>>val;
            double val1;
            if(cin.peek() == ' '){
                cin>>val1;
                polin[index] = new Polynomial(*polin[val] * *polin[val1]);
            }
            else{
                *polin[index]*=val;
            }
        }

        if(cerinta == "div"){
            int index;
            double val;
            cin>>index>>val;
            *polin[index]/=val;
        }
    }

    for(int k = 0 ; k < n ; k++){
        for(int j=0; j <= polin[k]->getDegree() ; j++){
            cout<<fixed<<setprecision(3)<<polin[k]->operator[](j)<<"*x^"<<polin[k]->getDegree()-j;
            if(j!=polin[k]->getDegree() && polin[k]->operator[](j)>=0){
                cout<<"+";
            }
        }
        cout<<endl;
    }

    return 0;
}

