#include <chrono>
#include <cstring>

#include "Order.hpp"
#include "UtilsImpl.hpp"
#include "SignerException.hpp"

namespace signer
{

starkware::PrimeFieldElement encodeChainSide( OrderSide value )
{
    using namespace starkware;
    using Uint256 = PrimeFieldElement::ValueType;

    switch( value )
    {
        case OrderSide::Buy:
            return PrimeFieldElement::FromBigInt( Uint256( 1 ) );
        case OrderSide::Sell:
            return PrimeFieldElement::FromBigInt( Uint256( 2 ) );
    }
}

starkware::PrimeFieldElement encodeOrderType( OrderType value )
{
    using namespace starkware;

    static constexpr char const* strMarket = "MARKET";
    static constexpr char const* strLimit = "LIMIT";

    switch( value )
    {
        case OrderType::Market:
        {
            constexpr size_t numMarketLen = std::char_traits< char >::length( strMarket );
            const auto tmpMarket = signer::strToBigInt< numMarketLen >( strMarket );
            const auto market = signer::bigIntToUint256( tmpMarket );

            return PrimeFieldElement::FromBigInt( market );
        }
        case OrderType::Limit:
        {
            constexpr size_t numLimitLen = std::char_traits< char >::length( strLimit );
            const auto tmpLimit = signer::strToBigInt< numLimitLen >( strLimit );
            const auto limit = signer::bigIntToUint256( tmpLimit );

            return PrimeFieldElement::FromBigInt( limit );
        }
    }
}

Order::Order( const std::string& theMarket, OrderSide theOrderSide, OrderType theOrderType, uint64_t theSize,
    const std::optional< Uint256 >& theLimitPrice /* = std::nullopt */)
    : orderSide( theOrderSide )
    , market( theMarket )
    , orderType( theOrderType )
    , size( theSize )
{
    using namespace std::chrono;

    timestamp = duration_cast< milliseconds >( system_clock::now().time_since_epoch() );

    if( orderType == OrderType::Limit && !theLimitPrice.has_value() )
    {
        throw new SignerException( "If OrderType::Limit theLimitPrice shall exist" );
    }
    limitPrice = theLimitPrice;
}

Order::Uint256 Order::getChainPrice() const
{
    if( orderType == OrderType::Market )
    {
        return Uint256( 0 );
    }

    return limitPrice.value();
}

void Order::setTimestamp(std::chrono::milliseconds value)
{
    timestamp = value;
}

std::vector< starkware::PrimeFieldElement > Order::pedersenEncode() const
{
    using namespace starkware;

    const char* strOrderTypeName = "Order(timestamp:felt,market:felt,side:felt,orderType:felt,size:felt,price:felt)";

    const BigInt< 4 > tmpOrderTypeName = signer::getSelectorFromName( strOrderTypeName, std::strlen( strOrderTypeName ) );
    const PrimeFieldElement orderTypeName = PrimeFieldElement::FromBigInt( tmpOrderTypeName );
    const PrimeFieldElement timestamp = PrimeFieldElement::FromUint( this->timestamp.count() );
    const PrimeFieldElement market = signer::strToFelt( this->market.c_str(), this->market.length() );
    const PrimeFieldElement chainSide = encodeChainSide( this->orderSide );
    const PrimeFieldElement orderType = signer::encodeOrderType( this->orderType );
    const PrimeFieldElement chainSize = PrimeFieldElement::FromUint( size );
    const PrimeFieldElement chainPrice = PrimeFieldElement::FromBigInt( getChainPrice() );

    return { orderTypeName, timestamp, market, chainSide, orderType, chainSize, chainPrice };
}

} // namespace signer