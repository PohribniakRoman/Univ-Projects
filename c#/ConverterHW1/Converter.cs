using System;

namespace ConverterApp;

class Converter
{
    private readonly decimal usdExchangeRate;

    private readonly decimal eurExchangeRate;

    private static void ValidateAmount(decimal amount)
    {
        if (amount < 0)
        {
            throw new ArgumentException("Amount can not be negative", nameof(amount));
        }
    }

    public Converter(decimal usdExchangeRate, decimal eurExchangeRate)
    {
        if (usdExchangeRate <= 0)
        {
            throw new ArgumentException("USD exchange rate can not be 0 or negative", nameof(usdExchangeRate));
        }

        if (eurExchangeRate <= 0)
        {
            throw new ArgumentException("EUR exchange rate can not be 0 or negative", nameof(eurExchangeRate));
        }

        this.usdExchangeRate = usdExchangeRate;
        this.eurExchangeRate = eurExchangeRate;
    }

    public decimal ConvertToEUR(decimal amount)
    {
        ValidateAmount(amount);
        return amount / eurExchangeRate;
    }

    public decimal ConvertToUSD(decimal amount)
    {
        ValidateAmount(amount);
        return amount / usdExchangeRate;
    }

    public decimal ConvertFromEUR(decimal amount)
    {
        ValidateAmount(amount);
        return amount * eurExchangeRate;
    }

    public decimal ConvertFromUSD(decimal amount)
    {
        ValidateAmount(amount);
        return amount * usdExchangeRate;
    }
}