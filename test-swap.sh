#!/bin/bash

echo b main >> _tmp.gdb
echo r >> _tmp.gdb
echo 'source scripts/create_list_for_swap.gdb' >> _tmp.gdb
echo 'source scripts/printf_list.gdb' >> _tmp.gdb
echo 'source scripts/free_list.gdb' >> _tmp.gdb

echo 'set $address_of_head = (List **)malloc(sizeof(List *))' >> _tmp.gdb
echo 'set $head = (List*)0' >> _tmp.gdb
echo 'set $node1 = (List*)0' >> _tmp.gdb
echo 'set $node2 = (List*)0' >> _tmp.gdb

exec < $1
read var
echo 'set $nodes_array = (List **)malloc(sizeof(List*)*'$var')' >> _tmp.gdb
echo 'create_list $head' $var '$nodes_array'>> _tmp.gdb
echo 'p *($address_of_head) = $head' >> _tmp.gdb
exec < $1
echo 'set logging file '$2 >> _tmp.gdb

while (read var) 
do
	read var
	node_1=$var
	read var
	node_2=$var

	echo 'set logging on' >> _tmp.gdb
	echo 'p "test begin"' >> _tmp.gdb

	echo 'p "old_list"' >> _tmp.gdb
	echo 'printf_list (*$address_of_head)' >> _tmp.gdb
	echo 'set logging off' >> _tmp.gdb
	echo 'p $node1 = $nodes_array['$node_1'-1]' >> _tmp.gdb
	echo 'p $node2 = $nodes_array['$node_2'-1]' >> _tmp.gdb
	#echo 'p $head = swap($head,$node1,$node2)' >> _tmp.gdb
	echo 'p myswap($address_of_head,$node1,$node2)' >> _tmp.gdb
	echo 'set $tmp = (List*)0' >> _tmp.gdb
	echo 'p $tmp = $nodes_array['$node_1'-1]' >> _tmp.gdb
	echo 'p $nodes_array['$node_1'-1] = $nodes_array['$node_2'-1]' >> _tmp.gdb
	echo 'p $nodes_array['$node_2'-1] = $tmp' >> _tmp.gdb
	echo 'set logging on' >> _tmp.gdb
	echo 'p "change '$node_1' '$node_2'"' >> _tmp.gdb
	echo 'p "new_list"' >> _tmp.gdb
	#echo 'printf_list $head' >> _tmp.gdb
	echo 'printf_list (*$address_of_head)' >> _tmp.gdb
	echo 'p "  "' >> _tmp.gdb
	echo 'p "  "' >> _tmp.gdb
	echo 'set logging off' >> _tmp.gdb
done

	echo 'free_list (*$address_of_head)' >> _tmp.gdb
	echo 'free_list ($nodes_array)' >> _tmp.gdb

gdb -q -x _tmp.gdb bin-swap >> /dev/null

rm _tmp.gdb
