armstrong() {

    num=$1    
    sum=0     



    while [ $num -gt 0 ];     
    do
        tmp=`expr $num % 10`                      
        sum=`expr $sum + $tmp \* $tmp \* $tmp`  
        num=`expr $num / 10`                       
    done



    if [ $sum -eq $1 ];  
    then   
        echo "$1 is an armstrong number"        
    else
        echo "$1 is not an armstrong number"
    fi
} 

armstrong 153
