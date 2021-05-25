run Build_ename.sh
gcc  -I./lib fileio/copy.c lib/error_functions.c -o fileio/out/runcopy
gcc  -I./lib fileio/tee.c lib/error_functions.c -o fileio/out/runtee
gcc  -I./lib fileio/seek_io.c lib/error_functions.c lib/get_num.c -o fileio/out/seek_io
gcc  -I./lib fileio/t_truncate.c lib/error_functions.c lib/get_num.c -o fileio/out/t_truncate
gcc  -I./lib fileio/t_writev.c lib/error_functions.c -o fileio/out/t_writev
gcc  -I./lib fileio/atomic_append.c lib/error_functions.c lib/get_num.c -o fileio/out/atomic_append
gcc  -I./lib fileio/multi_descriptors.c lib/error_functions.c -o fileio/out/multi_descriptors

gcc  -I./lib sockets/i6d_ucase_sv.c lib/error_functions.c -o sockets/out/i6d_ucase_sv
gcc  -I./lib sockets/i6d_ucase_cl.c lib/error_functions.c -o sockets/out/i6d_ucase_cl

gcc  -I./lib sockets/is_seqnum_sv.c sockets/read_line.c lib/error_functions.c lib/get_num.c -o sockets/out/is_seqnum_sv
gcc  -I./lib sockets/is_seqnum_cl.c  sockets/read_line.c lib/error_functions.c lib/get_num.c -o sockets/out/is_seqnum_cl


gcc -c -I./lib sockets/inet_sockets.c lib/error_functions.c lib/get_num.c

gcc sockets/tcpclient.c -o sockets/out/tcpclient
gcc  -I./lib sockets/tcpserver.c lib/error_functions.c sockets/inet_sockets.c -o sockets/out/tcpserver


gcc  -I./lib sockets/voteapp/vote_cl.c lib/error_functions.c sockets/inet_sockets.c -o sockets/out/votecl
gcc  -I./lib sockets/voteapp/vote_sv.c lib/error_functions.c sockets/inet_sockets.c -o sockets/out/votesv