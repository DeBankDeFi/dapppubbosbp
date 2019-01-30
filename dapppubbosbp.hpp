#include <eosiolib/eosio.hpp>
#include <eosiolib/transaction.hpp>
#include <eosiolib/time.hpp>
#include <eosiolib/privileged.hpp>
#include <eosiolib/singleton.hpp>

using namespace eosio;
using namespace std;

const uint32_t sec_per_day = 24 * 3600;

class dapppubbosbp: public contract {
public:
    dapppubbosbp(account_name self)
            : contract(self),
            _producers(N(eosio), N(eosio)),
            _global(N(eosio), N(eosio))
        {};
    void claim();
private:
    struct eosio_global_state : blockchain_parameters {
        uint64_t free_ram()const { return max_ram_size - total_ram_bytes_reserved; }

        uint64_t             max_ram_size = 64ll*1024 * 1024 * 1024;
        uint64_t             total_ram_bytes_reserved = 0;
        int64_t              total_ram_stake = 0;

        block_timestamp      last_producer_schedule_update;
        time_point           last_pervote_bucket_fill;
        int64_t              pervote_bucket = 0;
        int64_t              perblock_bucket = 0;
        uint32_t             total_unpaid_blocks = 0; /// all blocks which have been produced but not paid
        int64_t              total_activated_stake = 0;
        time_point           thresh_activated_stake_time;
        uint16_t             last_producer_schedule_size = 0;
        double               total_producer_vote_weight = 0; /// the sum of all producer votes
        block_timestamp      last_name_close;

        // explicit serialization macro is not necessary, used here only to improve compilation time
        EOSLIB_SERIALIZE_DERIVED( eosio_global_state, eosio::blockchain_parameters,
                                    (max_ram_size)(total_ram_bytes_reserved)(total_ram_stake)
                                    (last_producer_schedule_update)(last_pervote_bucket_fill)
                                    (pervote_bucket)(perblock_bucket)(total_unpaid_blocks)(total_activated_stake)(thresh_activated_stake_time)
                                    (last_producer_schedule_size)(total_producer_vote_weight)(last_name_close) )
    };
    typedef eosio::singleton<N(global), eosio_global_state> global_state_singleton;
    global_state_singleton _global;

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
