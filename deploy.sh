cleos create account eosio dapppubbosbp $EOSIO_KEY $EOSIO_KEY -p eosio
cleos set code dapppubbosbp build/dapppubbosbp.wasm
cleos set abi dapppubbosbp build/dapppubbosbp.abi
cleos set account permission dapppubbosbp active '{"threshold": 1,"keys": [{"key": "'$EOSIO_KEY'","weight": 1}],"accounts": [{"permission":{"actor":"dapppubbosbp","permission":"eosio.code"},"weight":1}]}' owner -p dapppubbosbp
