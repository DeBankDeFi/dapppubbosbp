#include <eosiolib/eosio.hpp>
#include <eosiolib/transaction.hpp>
#include <eosiolib/time.hpp>

using namespace eosio;
using namespace std;

const uint32_t sec_per_day = 24 * 3600;

class dapppubbosbp: public contract {
public:
    dapppubbosbp(account_name self)
            : contract(self),
            _producers(N(eosio), N(eosio))
        {};
    void claim();
private:
    struct producer_info {
        account_name          owner;
        double                total_votes = 0;
        public_key            producer_key;
        bool                  is_active = true;
        string                url;
        uint32_t              unpaid_blocks = 0;
        time_point            last_claim_time;
        uint16_t              location = 0;

        uint64_t primary_key()const { return owner;                                   }
        double   by_votes()const    { return is_active ? -total_votes : total_votes;  }
        bool     active()const      { return is_active;                               }
        void     deactivate()       { producer_key = public_key(); is_active = false; }

        // explicit serialization macro is not necessary, used here only to improve compilation time
        EOSLIB_SERIALIZE( producer_info, (owner)(total_votes)(producer_key)(is_active)(url)
                            (unpaid_blocks)(last_claim_time)(location) )
    };
    typedef multi_index<N(producers), producer_info> producers;
    producers _producers;
};

EOSIO_ABI(dapppubbosbp, (claim))
