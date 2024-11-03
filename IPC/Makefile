# Uncomment as needed. 
# shm: sem start mq #shm_c shm_s  test
	
start: mq_r mq
	
mq: mq.c
	cc mq.c -o mq -lrt -pg

mq_r: mq_r.c 
	cc mq_r.c -o mq_r -lrt -pg

# shm_c: shm_c.c
# 	cc shm_c.c -o shm_c -lrt

# shm_s: shm_s.c
# 	cc shm_s.c -o shm_s  -lrt

# sem: sem.c
# 	cc sem.c -o sem mq.c -lrt -lpthread

# test: test.c
# 	cc test.c -o test