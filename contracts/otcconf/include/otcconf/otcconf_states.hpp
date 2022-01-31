 #pragma once

#include <eosio/asset.hpp>
#include <eosio/privileged.hpp>
#include <eosio/singleton.hpp>
#include <eosio/system.hpp>
#include <eosio/time.hpp>
#include <eosio/name.hpp>

#include <optional>
#include <string>
#include <vector>
#include <map>
#include <type_traits>

namespace otc {

using namespace std;
using namespace eosio;

#define CONTRACT_TBL [[eosio::table, eosio::contract("otcconf")]]

constexpr name USDT_ERC20 = "usdt.erc"_n;
constexpr name USDT_TRC20 = "usdt.trc"_n;
constexpr name USDT_BEP20 = "usdt.bep"_n;
constexpr name CNYD_BEP20 = "cnyd.bep"_n;
constexpr name CNYD_ARC20 = "cnyd.arc"_n;
constexpr name USDT_CNY   = "usdt.cny"_n;
constexpr name CNYD_CNY   = "cnyd.cny"_n;
constexpr name BTC        = "btc"_n;
constexpr name ETH        = "eth"_n;
constexpr name CNY        = "cny"_n;
constexpr name USD        = "usd"_n;
constexpr name EUR        = "eur"_n;
constexpr name INR        = "inr"_n;


/** 
 * App upgrade info
 */
struct AppInfo_t {
    string latest_app_version;
    string android_apk_download_url; //ipfs url
    string upgrade_log;
    bool force_upgrade;
};

struct [[eosio::table("global"), eosio::contract("otcconf")]] global_t {
    AppInfo_t app_info = { 
        "0.1.0",
        "https://ipfs.io/ipfs/QmZUmzu96uKBLcCjNcnbD12hmjtMnaTs7ymLDHio3qbeDi", 
        "initial beta testing release", 
        false 
    };

    vector<name> coin_type = { USDT_ERC20, USDT_TRC20, USDT_BEP20, CNYD_BEP20, CNYD_ARC20 };
    vector<name> fiat_type = { CNY, USD, EUR, INR };

    /** 
     * OTC merchants to make sell orders with cypto
     */
    map<name, vector<name>> coin_to_fiat_conf = {
        { CNYD_BEP20,  { CNY } },
        { CNYD_ARC20,  { CNY } },
        { BTC,         { CNY } },
        { ETH,         { CNY } }
    };
    
    /** 
     * OTC merchants to make buy orders with fiat
     */
    map<name, vector<name>> fiat_to_coin_conf = {
        { CNY, {
            CNYD_BEP20, 
            CNYD_ARC20,  
            USDT_ERC20, 
            USDT_BEP20,
            BTC,
            ETH }
        }
    };

    map<name, float> coin_price = {
        { USDT_CNY, 6.3 },
        { CNYD_CNY, 1   }
    };

    global_t() {
        
    }

    EOSLIB_SERIALIZE( global_t, (app_info)(coin_type)(fiat_type)
                                (coin_to_fiat_conf)(fiat_to_coin_conf)(coin_price)
    )
};
typedef eosio::singleton< "global"_n, global_t > global_singleton;


} // OTC
