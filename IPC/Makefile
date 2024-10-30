shm: start shm_c shm_s test
	
start: mq mq_r 
	
mq: mq.c
	cc mq.c -o mq -lrt

mq_r: mq_r.c 
	cc mq_r.c -o mq_r -lrt

shm_c: shm_c.c
	cc shm_c.c -o shm_c -lrt

shm_s: shm_s.c
	cc shm_s.c -o shm_s -lrt

test: test.c
	cc test.c -o test