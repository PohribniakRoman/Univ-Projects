#include <iostream>
#include <vector>

using namespace std;

class Apartment{
    public:
        const int MIN_PRICE = 5000;
        const int MIN_TIME_TO_SUBWAY = 5;
        const int MAX_TIME_TO_SUBWAY = 120;
        const int MIN_AVALIBLE_AREA = 0;
        const int MAX_AVALIBLE_AREA = 100000;
        const int MAX_AVALIBLE_BEDROOM_QUANTITY = 10;
        const int MIN_AVALIBLE_BEDROOM_QUANTITY = 0;
        const int MAX_AVALIBLE_BATHROOM_QUANTITY = 10;
        const int MIN_AVALIBLE_BATHROOM_QUANTITY = 0;
        int bedroomsQuantity,bathroomQuantity,timeToSubway;
        double area,price;
        bool isCommercial;
        bool enterData(){
            cout << "Enter features:\nApartments area:" << endl;
            if (cin >> area) {
                if(area == MIN_AVALIBLE_AREA){
                    return false;
                }
                if (area > MAX_AVALIBLE_AREA || area < MIN_AVALIBLE_AREA) {
                    cout << "Specified number can't be value of area." << endl;
                    return false;
                }
            } else {
                cout << "Incorrect data type." << endl;
                return false;
            }

            cout << "Enter quantity of bedrooms:" << endl;

            if (cin >> bedroomsQuantity) {
                if (bedroomsQuantity > MAX_AVALIBLE_BEDROOM_QUANTITY || bedroomsQuantity < MIN_AVALIBLE_BEDROOM_QUANTITY) {
                    cout << "Specified number can't be quantity of bedrooms." << endl;
                    return false;
                }
            } else {
                cout << "Incorrect data type." << endl;
                return false;
            }

            cout << "Enter quantity of bathrooms:" << endl;

            if (cin >> bathroomQuantity) {
                if (bathroomQuantity > MAX_AVALIBLE_BATHROOM_QUANTITY || bathroomQuantity <= MIN_AVALIBLE_BATHROOM_QUANTITY) {
                    cout << "Specified number can't be quantity of bathrooms." << endl;
                    return false;
                }
            } else {
                cout << "Incorrect data type." << endl;
                return false;
            }

            cout << "Enter time to subway:" << endl;

            if (cin >> timeToSubway) {
                if (timeToSubway > MAX_TIME_TO_SUBWAY || timeToSubway < MIN_TIME_TO_SUBWAY) {
                    cout << "Specified number can't be time to subway." << endl;
                    return false;
                }
            } else {
                cout << "Incorrect data type." << endl;
                return false;
            }

            cout << "Enter type of your apartments:(1 - commercial,0 - isn't commercial)" << endl;

            if (!(cin >> isCommercial)) {
                cout << "Incorrect data type." << endl;
                return false;
            }
            return true;
        }
        bool enterPrice(){
            cout << "Enter apartment price:" << endl;

            if (cin >> price) {
                if (price < MIN_PRICE) {
                    cout << "Specified number can't be price of apartment." << endl;
                    return false;
                }
            } else {
                cout << "Incorrect data type." << endl;
                return false;
            }
            return true;
        }

        vector<double> analyzeData() const{
            double pricePerSquareMeter = price/area;
            double bedCoef;
            double bathCoef;
            double subwCoef;
            if(isCommercial){
                bedroomsQuantity ==0 ?bedCoef = pricePerSquareMeter*0.2:bedCoef = (pricePerSquareMeter*0.2)/bedroomsQuantity;
                bathCoef = (pricePerSquareMeter*0.2)/bathroomQuantity;
                subwCoef = (pricePerSquareMeter*0.4)/timeToSubway;
                // commercial is always 20% of price per meter
            }else{
                bedCoef = (pricePerSquareMeter*0.25)/bedroomsQuantity;
                bathCoef = (pricePerSquareMeter*0.25)/bathroomQuantity;
                subwCoef = (pricePerSquareMeter*0.50)/timeToSubway;
            }
            return vector<double> {bedCoef,bathCoef,subwCoef};
        }
    };

vector<double> getComputedCoef(const vector<double>& currentData,vector<double> coefficientVector){
    if(coefficientVector.empty()){
        coefficientVector = currentData;
    }else{
        for (int i = 0; i < coefficientVector.size(); ++i) {
            coefficientVector[i] = (currentData[i]+coefficientVector[i])/2;
        }
    }
    return coefficientVector;
}

double computePrice(const vector<double>& commVect,const vector<double>& defVect,double area,int bed,int bath,int subw,bool comm){
    if(comm){
        if(!commVect.empty()) {
            return ((commVect[0] * bed + commVect[1] * bath + commVect[2] * subw) * 100 / 80)*area;
        }else{
            cout << "We don't have any data to analyze price..."<<endl;
        }
    }else{
        if(!defVect.empty()){
            return (defVect[0]*bed+defVect[1]*bath+defVect[2]*subw)*area;
        }else{
            cout << "We don't have any data to analyze price..."<<endl;
        }
    }
    return 0;
}


int main() {
    vector<double> commercialCoef;
    vector<double> defaultCoef;
    vector<Apartment> apartmentList;

    while(true) {
        Apartment ApartmentObj{};
        if(!ApartmentObj.enterData() || !ApartmentObj.enterPrice() ){
            break;
        }
        ApartmentObj.isCommercial ? commercialCoef = getComputedCoef(ApartmentObj.analyzeData(),commercialCoef)
                :defaultCoef = getComputedCoef(ApartmentObj.analyzeData(),defaultCoef);
        apartmentList.push_back(ApartmentObj);
    }

    Apartment ApartmentToCompute{};
    ApartmentToCompute.enterData();

    cout << "Expected price is: " << computePrice(commercialCoef,defaultCoef,ApartmentToCompute.area,ApartmentToCompute.bedroomsQuantity,ApartmentToCompute.bathroomQuantity,ApartmentToCompute.timeToSubway,ApartmentToCompute.isCommercial) << endl;

    return 0;
}
