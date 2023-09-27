using System;
using System.Dynamic;

namespace ConverterApp;

class Converter{
    private double Amount;
    private double baseValue;
    
    private double USDToBase = 34.96;
    
    private double baseToUSD = 36.96;
    
    private double EURToBase = 36.83;
    
    private double baseToEUR = 38.83;

    private string state = "UAH";

    public Converter(double amount){
        Amount = amount;
        baseValue = amount;
    }

    public void ToEUR(){
        if(state != "UAH")ToBase();
        Amount = baseValue/baseToEUR;
        state = "EUR";
    }

    public void ToUSD(){
        if(state != "UAH")ToBase();
        Amount = baseValue/baseToUSD;
        state = "USD";
    }

    public string GetInfo(){
        return Amount+" "+state;
    }
    
    public void ToBase(){
        if(state == "USD"){
            baseValue = Amount*USDToBase;
            Amount = baseValue;
        }else if(state == "EUR"){
            baseValue = Amount*EURToBase;
            Amount = baseValue;
        }
        state = "UAH";
    }
}