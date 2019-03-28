# dapppubbosbp

Help BP auto claim rewards

## EOS Mainnet

```shell
cleos set action permission $BP_ACCOUNT eosio claimrewards claim
cleos set account permission $BP_ACCOUNT claim '{"threshold": 1,"keys": [],"accounts": [{"permission":{"actor":"dapppub.bp","permission":"eosio.code"},"weight":1}]}' -p $BP_ACCOUNT
cleos push action dapppub.bp claim '['$BP_ACCOUNT']' -p $BP_ACCOUNT
```

## BOS

```shell
cleos set action permission $BP_ACCOUNT eosio claimrewards claim
cleos set account permission $BP_ACCOUNT claim '{"threshold": 1,"keys": [],"accounts": [{"permission":{"actor":"dapppubbosbp","permission":"eosio.code"},"weight":1}]}' -p $BP_ACCOUNT
cleos push action dapppubbosbp claim '['$BP_ACCOUNT']' -p $BP_ACCOUNT
```

