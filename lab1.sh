counter=0
# file name
#filename=''
#regex
#regex=''
# SIGINT handler
getf(){
		while :
		do
			filename=''
			read -p "enter the filename " filename
			if [ ! -f "$filename" ]; then
				echo "File $filename not found"
			else
				break
			fi
		done
}
getr(){
		while :
		do
			regex=''
			read -p "enter the regex " regex
			if [ -z "$regex" ]; then
				echo  "enter a non-empty string"
			else
				break
			fi
		done
}

sigintHandler(){
	if [ $counter -eq 11 ]
  then
	   #	exit
     exit 0
  else
    counter=`expr $counter + 1`
  fi
}


# rewrite SIGINT handler
trap sigintHandler 2

while :
do
	getf
  getr
	foo=`grep "$regex" "$filename"`
  ./b.exe $foo
done
