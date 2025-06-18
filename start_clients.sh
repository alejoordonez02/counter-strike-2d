n_clients=3
port=1235

for i in $(seq 1 $n_clients); do
    ./build/cs2d_client localhost $port $i &
done

