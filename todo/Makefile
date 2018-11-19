.PHONY: dist
todo.wasm : todo.cpp todo.hpp
	eosio-cpp -o todo.wasm todo.cpp --abigen

deploy:
	cleos set contract eos.test ../todo -p eos.test

unlock:
	cleos wallet unlock -n mywallet --password PW5JqrSNEGBrScqx9oQ3MYrvpuWDr9JFurc4XHhnGXHnch1X5H8Sa