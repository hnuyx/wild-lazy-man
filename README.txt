

Base Library, BL for initial abberviation as follow.
-----------------------------------------------------------------
2015.06.17
14. php/page.php: php paging
15. tcp/client/: Makefile tcp_client.cpp tcp_client.h
	tcp_client.h tcp_client.cpp: tcp client

-----------------------------------------------------------------
2015.06.11
12. doc/record.vsd : ItemPoolT ItemPoolKeyT
13. thread/
thread_base.h thread_base.cpp: thread base

-----------------------------------------------------------------
2015.06.09
11. record/
item_list_T.cpp item_list_T.h : item list
item_pool_key_T.cpp item_pool_key_T.h : item pool by key
item_pool_T.cpp  item_pool_T.h : item pool
item_queue_T.cpp  item_queue_T.h : item queue

-----------------------------------------------------------------
2015.06.03
10. shell snake.sh: eating snake

-----------------------------------------------------------------
2015.05.27
9. shell line.sh mi_line.sh cross_line.sh

-----------------------------------------------------------------
2015.05.26
7. kidding.jpg
8. temp/head.h temp/Makefile

-----------------------------------------------------------------
2015.05.04
6. add cpp/kmp.cpp cpp/qsort.cpp cpp/Makefile
	kmp.cpp: kmp get next function
	qsort.cpp: qsort function
	Makefile: compile current files

2015.04.29
5. add mysql/mysql_op.h mysql/mysql_op.cpp mysql/Makefile
	mysql_op.h mysql_op.cpp: mysql operation
	Makefile: compile libMysqlOp.so

-----------------------------------------------------------------
2015.04.28
2. add common/Makefile
	Makefile: compile libBLCommon.so

3. add file/file_op.h file/file_op.cpp file/Makefile
	file_op.h file_op.cpp: file operation
	Makefile: compile libFileOp.so

4. add Makefile
	MakeFile: compile all files
		make, make clean, make cleanall


-----------------------------------------------------------------
2015.04.28
1. add common/bl_common.h common/local_ip.h common/local_ip.cpp
	bl_common.h: common type
	local_ip.h local_ip.cpp: get local ip
