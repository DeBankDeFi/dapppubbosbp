# dapppubbosbp

Help BP auto claim rewards

```shell
cleos set code $BP_ACCOUNT build/dapppubbosbp.wasm
cleos set abi $BP_ACCOUNT build/dapppubbosbp.abi
cleos set account permission $BP_ACCOUNT active '{"threshold": 1,"keys": [{"key": "'$EOSIO_KEY'","weight": 1}],"accounts": [{"permission":{"actor":"'$BP_ACCOUNT'","permission":"eosio.code"},"weight":1}]}' owner -p $BP_ACCOUNT
cleos push action $BP_ACCOUNT claim '[]' -p $BP_ACCOUNT
```

