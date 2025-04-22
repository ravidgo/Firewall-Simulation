
#!/bin/bash


packets=$(cat -)

#removing hashtags and spaces
non_hash_laws=$(sed '/^[[:blank:]]*#/d;s/#.*//' "$1")


non_space_laws=$(echo "$non_hash_laws" | sed '/^$/d')


while read line; do
  law1=$(echo $line | awk -F, '{print $1}')

  law2=$(echo $line | awk -F, '{print $2}')

  law3=$(echo $line | awk -F, '{print $3}')

  law4=$(echo $line | awk -F, '{print $4}')

  #deliver packets to be filterd by firewall.exe
  filtered_pkts=$(echo "$packets" | ./firewall.exe "$law1" 2>/dev/null \
	  | ./firewall.exe "$law2" 2>/dev/null \
	  | ./firewall.exe "$law3" 2>/dev/null \
	  | ./firewall.exe "$law4" 2>/dev/null)
  
  #echo "$filtered_pkts"
  valid_pkts+=$(echo "\n$filtered_pkts")
 
done <<< "$non_space_laws"

echo -e "$valid_pkts" | sort | sed '/^$/d' | sed 's/ //g'
