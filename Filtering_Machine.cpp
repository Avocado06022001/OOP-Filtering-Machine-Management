#include<iostream>
using namespace std;
#include<vector>
class filteringmachine{
private:
    double price;
    double time;
    double input;
public:
    filteringmachine(double price, double time, double input){
        this->price=price;
        this->time=time;
        this->input=input;
    }

    void setPrice(double price){this->price=price;}
    void setTime(double time){this->time=time;}
    void setInput(double input){this->input=input;}

    double getPrice(){return price;}
    double getTime(){return time;}
    double getInput(){return input;}
    virtual double getPower()=0;
    virtual double volumefiltering()=0;
    virtual double rentalfee()=0;
    virtual double totalfee()=0;
};

class lytam: public filteringmachine{
private:
    double power;
public:
    lytam(double price, double time, double input, double power):
    filteringmachine(price,time,input){this->power=power;}
    void setPower(double power){this->power=power;}
    double getPower(){
        return power;
    }
    double volumefiltering(){
        return lytam::getPower()*lytam::getTime();
    }
    double rentalfee(){
        return 50000*lytam::getTime();
    }
    double totalfee(){
        return lytam::rentalfee()+lytam::getInput()*20000;
    }

};

class xuctac:public filteringmachine{
private:
    double power;
public:
    xuctac(double price, double time, double input, double power):
    filteringmachine(price,time,input){this->power=power;}
    void setPower(){this->power=power;}
    double getPower(){
        if (xuctac::getTime()<10){
            return power*(xuctac::getInput()/100);
        }else{
            return power*(xuctac::getInput()/100)/(xuctac::getTime()/10);
        }
    }
    double volumefiltering(){
        return xuctac::getPower()*xuctac::getTime();
    }
    double rentalfee(){
        return 80000*xuctac::getTime();
    }
    double totalfee(){
        return xuctac::rentalfee()+xuctac::getInput()*10000;
    }
};

class project{
private:
    vector<filteringmachine*>list;
public:
    void addEntity(filteringmachine* e){
        list.push_back(e);
    }
    bool checkfiltering(double volume){
        double sum=0;
        for (int i=0; i<list.size(); i++){
            sum+=list[i]->volumefiltering();
        }
        if (sum<volume){return false;}
        else{return true;}
    }
    double totalfiltering(){
        double sum=0;
        for (int i=0; i<list.size(); i++){
            sum+=list[i]->totalfee();
        }
        return sum;
    }
};

int main(){
    project p;
    lytam e1(10000,10,400,20);
    lytam e2(10500,5,350,50);
    xuctac e3(20000,7,200,60);
    filteringmachine* m1=&e1;
    filteringmachine* m2=&e2;
    filteringmachine* m3=&e3;
    p.addEntity(m1);
    p.addEntity(m2);
    p.addEntity(m3);
    double volume;
    cin>>volume;
    if (p.checkfiltering(volume)){cout<<"Can filter the lake"<<endl;}
    else{cout<<"Cannot filter the lake"<<endl;}
    cout<<p.totalfiltering()<<endl;
}
