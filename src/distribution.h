#ifndef DISTRIBUTION_H
#define DISTRIBUTION_H

#include "base58.h"
#include "json/json_spirit_value.h"

class Distribution
{
protected:
    CBitcoinAddress addrArepashares;
    int64 nBalance;

    CArepacoinAddress addrArepacoin;
    double dDividendAmount;

public:
    Distribution(CBitcoinAddress addrArepashares, int64 nBalance, double dDividendAmount)
        : addrArepashares(addrArepashares), nBalance(nBalance), addrArepacoin(addrArepashares), dDividendAmount(dDividendAmount)
    {
    }

    const CBitcoinAddress GetPeershareAddress() const
    {
        return addrArepashares;
    }

    int64 GetBalance() const
    {
        return nBalance;
    }

    const CArepacoinAddress GetArepacoinAddress() const
    {
        return addrArepacoin;
    }

    double GetDividendAmount() const
    {
        return dDividendAmount;
    }
};

typedef std::map<const CBitcoinAddress, int64> BalanceMap;
typedef std::vector<Distribution> DistributionVector;

class DividendDistributor
{
protected:
    BalanceMap mapBalance;
    double dTotalDistributed;

    DistributionVector vDistribution;

public:
    DividendDistributor() : mapBalance(), dTotalDistributed(0)
    {
    }

    DividendDistributor(const BalanceMap& mapBalance) : mapBalance(mapBalance), dTotalDistributed(0)
    {
    }

    void SetBalanceMap(const BalanceMap &mapBalance)
    {
        this->mapBalance = mapBalance;
    }

    void Distribute(double dDistributedAmount, double dMinimumPayout);
    void GenerateOutputs(int nTransactions, std::vector<json_spirit::Object> &vTransactionOuts) const;

    int GetTransactionCount(int nMaxDistributionPerTransaction) const;

    const DistributionVector& GetDistributions() const
    {
        return vDistribution;
    }

    int DistributionCount() const
    {
        return vDistribution.size();
    }

    const Distribution& GetDistribution(const CBitcoinAddress& addrPeershare) const
    {
        for (DistributionVector::const_iterator it = vDistribution.begin(); it != vDistribution.end(); ++it)
        {
            if (it->GetPeershareAddress() == addrPeershare)
                return *it;
        }
        throw std::runtime_error("Distribution not found");
    }

    double TotalDistributed() const
    {
        return dTotalDistributed;
    }
};

DividendDistributor GenerateDistribution(const BalanceMap &mapBalance, double dAmount);
json_spirit::Array SendDistribution(const DividendDistributor &distributor);
double GetMinimumDividendPayout();
int GetMaximumDistributionPerTransaction();
double GetDistributionBalance();

#endif
