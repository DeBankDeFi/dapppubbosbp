#include "dapppubbosbp.hpp"

void dapppubbosbp::claim() {
    require_auth(_self);
    const auto& prod = _producers.get(_self, "unable to find your producer");
    const uint32_t claim_time = prod.last_claim_time.sec_since_epoch() + sec_per_day + 1;
    if (now() >= claim_time) {
        action(
            permission_level{_self, N(active)},
            N(eosio),
            N(claimrewards),
            make_tuple(_self)
        ).send();

        transaction out;
        out.actions.emplace_back(permission_level{_self, N(active)}, _self, N(claim), std::make_tuple());
        out.delay_sec = sec_per_day + 1;
        out.send(N(claim), _self);
    } else {
        transaction out;
        out.actions.emplace_back(permission_level{_self, N(active)}, _self, N(claim), std::make_tuple());
        out.delay_sec = claim_time - now();
        out.send(N(claim), _self);
    }
}