COUNTER_SUCCESS=0
COUNTER_FAIL=0
DIFF_RES=""
FILENAME1="texts/1.txt"
FILENAME2="texts/2.txt"
FILENAME3="texts/3.txt"
FILENAME4="texts/4.txt"
FILENAME5="texts/5.txt"
echo "" > log.txt
PREF_TEST="testtxt/"
SHABLO=""
SHABLON="123"
SHABLON2="abc"
SHABLON3="[Xx]"
SHABLON4="[A-Z]"
SHABLON5="^[A-Z]"

for var in -v -c -l -n -i -h -s -o
do
          TEST1="$var $SHABLO $FILENAME1 $FILENAME2 $FILENAME3 $FILENAME4 $FILENAME5"
          # echo "$TEST1"
          ./s21_grep $TEST1 > testtxt/s21_grep$var.txt
          grep $TEST1 > testtxt/grep$var.txt
          DIFF_RES="$(diff -s testtxt/s21_grep$var.txt testtxt/grep$var.txt)"
          if [ "$DIFF_RES" == "Files testtxt/s21_grep$var.txt and testtxt/grep$var.txt are identical" ]
            then
              echo "SUCCES $TEST1"
              (( COUNTER_SUCCESS++ ))
            else
              echo "FAIL $TEST1"
              echo "$TEST1" >> log.txt
              (( COUNTER_FAIL++ ))
          fi
          rm testtxt/s21_grep$var.txt testtxt/grep$var.txt

done



for var in -v -c -l -n -i -h -s -o
do
  for var2 in -v -c -l -n -i -h -s -o
  do
        if [ $var != $var2 ]
        then
            TEST1="$var $var2 $SHABLO $FILENAME1 $FILENAME2 $FILENAME3 $FILENAME4 $FILENAME5"
            echo "$TEST1"
            ./s21_grep $TEST1 > testtxt/s21_grep${var}${var2}.txt
            grep $TEST1 > testtxt/grep${var}${var2}.txt
            DIFF_RES="$(diff -s testtxt/s21_grep${var}${var2}.txt testtxt/grep${var}${var2}.txt)"
            if [ "$DIFF_RES" == "Files testtxt/s21_grep${var}${var2}.txt and testtxt/grep${var}${var2}.txt are identical" ]
              then
                echo "SUCCES $TEST1"
              (( COUNTER_SUCCESS++ ))
              else
                echo "FAIL $TEST1"
                echo "$TEST1" >> log.txt
                (( COUNTER_FAIL++ ))
            fi
            rm testtxt/s21_grep$var.txt testtxt/grep$var.txt
        fi
          
  done
done
#SHABLON
####################################
for var in -v -c -l -n -i -h -s -o
do
          TEST1="$var $SHABLON $FILENAME1 $FILENAME2 $FILENAME3 $FILENAME4 $FILENAME5"
          # echo "$TEST1"
          ./s21_grep $TEST1 > testtxt/s21_grep$var.txt
          grep $TEST1 > testtxt/grep$var.txt
          DIFF_RES="$(diff -s testtxt/s21_grep$var.txt testtxt/grep$var.txt)"
          if [ "$DIFF_RES" == "Files testtxt/s21_grep$var.txt and testtxt/grep$var.txt are identical" ]
            then
              echo "SUCCES $TEST1"
              (( COUNTER_SUCCESS++ ))
            else
              echo "FAIL $TEST1"
              echo "$TEST1" >> log.txt
              (( COUNTER_FAIL++ ))
          fi
          rm testtxt/s21_grep$var.txt testtxt/grep$var.txt

done



for var in -v -c -l -n -i -h -s -o
do
  for var2 in -v -c -l -n -i -h -s -o
  do
        if [ $var != $var2 ]
        then
            TEST1="$var $var2 $SHABLON $FILENAME1 $FILENAME2 $FILENAME3 $FILENAME4 $FILENAME5"
            echo "$TEST1"
            ./s21_grep $TEST1 > testtxt/s21_grep${var}${var2}.txt
            grep $TEST1 > testtxt/grep${var}${var2}.txt
            DIFF_RES="$(diff -s testtxt/s21_grep${var}${var2}.txt testtxt/grep${var}${var2}.txt)"
            if [ "$DIFF_RES" == "Files testtxt/s21_grep${var}${var2}.txt and testtxt/grep${var}${var2}.txt are identical" ]
              then
                echo "SUCCES $TEST1"
              (( COUNTER_SUCCESS++ ))
              else
                echo "FAIL $TEST1"
                echo "$TEST1" >> log.txt
                (( COUNTER_FAIL++ ))
            fi
            rm testtxt/s21_grep${var}${var2}.txt testtxt/grep${var}${var2}.txt
        fi
          
  done
done



#SHABLON2
####################################
for var in -v -c -l -n -i -h -s -o
do
          TEST1="$var $SHABLON2 $FILENAME1 $FILENAME2 $FILENAME3 $FILENAME4 $FILENAME5"
          # echo "$TEST1"
          ./s21_grep $TEST1 > testtxt/s21_grep$var.txt
          grep $TEST1 > testtxt/grep$var.txt
          DIFF_RES="$(diff -s testtxt/s21_grep$var.txt testtxt/grep$var.txt)"
          if [ "$DIFF_RES" == "Files testtxt/s21_grep$var.txt and testtxt/grep$var.txt are identical" ]
            then
              echo "SUCCES $TEST1"
              (( COUNTER_SUCCESS++ ))
            else
              echo "FAIL $TEST1"
              echo "$TEST1" >> log.txt
              (( COUNTER_FAIL++ ))
          fi
          rm testtxt/s21_grep$var.txt testtxt/grep$var.txt

done



for var in -v -c -l -n -i -h -s -o
do
  for var2 in -v -c -l -n -i -h -s -o
  do
        if [ $var != $var2 ]
        then
            TEST1="$var $var2 $SHABLON2 $FILENAME1 $FILENAME2 $FILENAME3 $FILENAME4 $FILENAME5"
            echo "$TEST1"
            ./s21_grep $TEST1 > testtxt/s21_grep${var}${var2}.txt
            grep $TEST1 > testtxt/grep${var}${var2}.txt
            DIFF_RES="$(diff -s testtxt/s21_grep${var}${var2}.txt testtxt/grep${var}${var2}.txt)"
            if [ "$DIFF_RES" == "Files testtxt/s21_grep${var}${var2}.txt and testtxt/grep${var}${var2}.txt are identical" ]
              then
                echo "SUCCES $TEST1"
              (( COUNTER_SUCCESS++ ))
              else
                echo "FAIL $TEST1"
                echo "$TEST1" >> log.txt
                (( COUNTER_FAIL++ ))
            fi
            rm testtxt/s21_grep${var}${var2}.txt testtxt/grep${var}${var2}.txt
        fi
          
  done
done


for var in -v -c -l -n -i -h -s -o
do
          TEST1="$var \"$SHABLON3\" $FILENAME1 $FILENAME2 $FILENAME3 $FILENAME4 $FILENAME5"
          # echo "$TEST1"
          ./s21_grep $TEST1 > testtxt/s21_grep$var.txt
          grep $TEST1 > testtxt/grep$var.txt
          DIFF_RES="$(diff -s testtxt/s21_grep$var.txt testtxt/grep$var.txt)"
          if [ "$DIFF_RES" == "Files testtxt/s21_grep$var.txt and testtxt/grep$var.txt are identical" ]
            then
              echo "SUCCES $TEST1"
              (( COUNTER_SUCCESS++ ))
            else
              echo "FAIL $TEST1"
              echo "$TEST1" >> log.txt
              (( COUNTER_FAIL++ ))
          fi
          rm testtxt/s21_grep$var.txt testtxt/grep$var.txt

done

for var in -v -c -l -n -i -h -s -o
do
          TEST1="$var \"$SHABLON3\" $FILENAME1 $FILENAME2 $FILENAME3 $FILENAME4 $FILENAME5"
          # echo "$TEST1"
          ./s21_grep $TEST1 > testtxt/s21_grep$var.txt
          grep $TEST1 > testtxt/grep$var.txt
          DIFF_RES="$(diff -s testtxt/s21_grep$var.txt testtxt/grep$var.txt)"
          if [ "$DIFF_RES" == "Files testtxt/s21_grep$var.txt and testtxt/grep$var.txt are identical" ]
            then
              echo "SUCCES $TEST1"
              (( COUNTER_SUCCESS++ ))
            else
              echo "FAIL $TEST1"
              echo "$TEST1" >> log.txt
              (( COUNTER_FAIL++ ))
          fi
          rm testtxt/s21_grep$var.txt testtxt/grep$var.txt

done

for var in -v -c -l -n -i -h -s -o
do
          TEST1="$var \"$SHABLON4\" $FILENAME1 $FILENAME2 $FILENAME3 $FILENAME4 $FILENAME5"
          # echo "$TEST1"
          ./s21_grep $TEST1 > testtxt/s21_grep$var.txt
          grep $TEST1 > testtxt/grep$var.txt
          DIFF_RES="$(diff -s testtxt/s21_grep$var.txt testtxt/grep$var.txt)"
          if [ "$DIFF_RES" == "Files testtxt/s21_grep$var.txt and testtxt/grep$var.txt are identical" ]
            then
              echo "SUCCES $TEST1"
              (( COUNTER_SUCCESS++ ))
            else
              echo "FAIL $TEST1"
              echo "$TEST1" >> log.txt
              (( COUNTER_FAIL++ ))
          fi
          rm testtxt/s21_grep$var.txt testtxt/grep$var.txt

done

for var in -v -c -l -n -i -h -s -o
do
          TEST1="$var \"$SHABLON5\" $FILENAME1 $FILENAME2 $FILENAME3 $FILENAME4 $FILENAME5"
          # echo "$TEST1"
          ./s21_grep $TEST1 > testtxt/s21_grep$var.txt
          grep $TEST1 > testtxt/grep$var.txt
          DIFF_RES="$(diff -s testtxt/s21_grep$var.txt testtxt/grep$var.txt)"
          if [ "$DIFF_RES" == "Files testtxt/s21_grep$var.txt and testtxt/grep$var.txt are identical" ]
            then
              echo "SUCCES $TEST1"
              (( COUNTER_SUCCESS++ ))
            else
              echo "FAIL $TEST1"
              echo "$TEST1" >> log.txt
              (( COUNTER_FAIL++ ))
          fi
          rm testtxt/s21_grep$var.txt testtxt/grep$var.txt

done


for var in -v -c -l -n -i -h -s -o
do
          TEST1="$var -f texts/pattern.txt  $FILENAME1 $FILENAME2 $FILENAME3 $FILENAME4 $FILENAME5"
          # echo "$TEST1"
          ./s21_grep $TEST1 > testtxt/s21_grep$var.txt
          grep $TEST1 > testtxt/grep$var.txt
          DIFF_RES="$(diff -s testtxt/s21_grep$var.txt testtxt/grep$var.txt)"
          if [ "$DIFF_RES" == "Files testtxt/s21_grep$var.txt and testtxt/grep$var.txt are identical" ]
            then
              echo "SUCCES $TEST1"
              (( COUNTER_SUCCESS++ ))
            else
              echo "FAIL $TEST1"
              echo "$TEST1" >> log.txt
              (( COUNTER_FAIL++ ))
          fi
          rm testtxt/s21_grep$var.txt testtxt/grep$var.txt

done

for var in -v -c -l -n -i -h -s -o
do
          TEST1="$var -f texts/pattern.txt $FILENAME1 $FILENAME2 $FILENAME3 $FILENAME4 $FILENAME5"
          # echo "$TEST1"
          ./s21_grep $TEST1 > testtxt/s21_grep$var.txt
          grep $TEST1 > testtxt/grep$var.txt
          DIFF_RES="$(diff -s testtxt/s21_grep$var.txt testtxt/grep$var.txt)"
          if [ "$DIFF_RES" == "Files testtxt/s21_grep$var.txt and testtxt/grep$var.txt are identical" ]
            then
              echo "SUCCES $TEST1"
              (( COUNTER_SUCCESS++ ))
            else
              echo "FAIL $TEST1"
              echo "$TEST1" >> log.txt
              (( COUNTER_FAIL++ ))
          fi
          rm testtxt/s21_grep$var.txt testtxt/grep$var.txt

done

for var in -v -c -l -n -i -h -s -o
do
          TEST1="$var -f texts/pattern.txt -f texts/pattern2.txt $FILENAME1 $FILENAME2 $FILENAME3 $FILENAME4 $FILENAME5"
          # echo "$TEST1"
          ./s21_grep $TEST1 > testtxt/s21_grep$var.txt
          grep $TEST1 > testtxt/grep$var.txt
          DIFF_RES="$(diff -s testtxt/s21_grep$var.txt testtxt/grep$var.txt)"
          if [ "$DIFF_RES" == "Files testtxt/s21_grep$var.txt and testtxt/grep$var.txt are identical" ]
            then
              echo "SUCCES $TEST1"
              (( COUNTER_SUCCESS++ ))
            else
              echo "FAIL $TEST1"
              echo "$TEST1" >> log.txt
              (( COUNTER_FAIL++ ))
          fi
          rm testtxt/s21_grep$var.txt testtxt/grep$var.txt

done


for var in -v -c -l -n -i -h -s -o
do
          TEST1="$var -f texts/pattern.txt \"$SHABLON4\" $FILENAME1 $FILENAME2 $FILENAME3 $FILENAME4 $FILENAME5"
          # echo "$TEST1"
          ./s21_grep $TEST1 > testtxt/s21_grep$var.txt
          grep $TEST1 > testtxt/grep$var.txt
          DIFF_RES="$(diff -s testtxt/s21_grep$var.txt testtxt/grep$var.txt)"
          if [ "$DIFF_RES" == "Files testtxt/s21_grep$var.txt and testtxt/grep$var.txt are identical" ]
            then
              echo "SUCCES $TEST1"
              (( COUNTER_SUCCESS++ ))
            else
              echo "FAIL $TEST1"
              echo "$TEST1" >> log.txt
              (( COUNTER_FAIL++ ))
          fi
          rm testtxt/s21_grep$var.txt testtxt/grep$var.txt

done

for var in -v -c -l -n -i -h -s -o
do
  for var2 in -v -c -l -n -i -h -s -o
  do
        if [ $var != $var2 ]
        then
            TEST1="$var $var2 a $FILENAME1 $FILENAME2 $FILENAME3 $FILENAME4 $FILENAME5"
            echo "$TEST1"
            ./s21_grep $TEST1 > testtxt/s21_grep${var}${var2}.txt
            grep $TEST1 > testtxt/grep${var}${var2}.txt
            DIFF_RES="$(diff -s testtxt/s21_grep${var}${var2}.txt testtxt/grep${var}${var2}.txt)"
            if [ "$DIFF_RES" == "Files testtxt/s21_grep${var}${var2}.txt and testtxt/grep${var}${var2}.txt are identical" ]
              then
                echo "SUCCES $TEST1"
              (( COUNTER_SUCCESS++ ))
              else
                echo "FAIL $TEST1"
                echo "$TEST1" >> log.txt
                (( COUNTER_FAIL++ ))
            fi
           rm testtxt/s21_grep${var}${var2}.txt testtxt/grep${var}${var2}.txt
        fi
          
  done
done

for var in -v -c -l -n -i -h -s -o
do
  for var2 in -v -c -l -n -i -h -s -o
  do
        if [ $var != $var2 ]
        then
            TEST1="$var $var2 \"$SHABLON4\" $FILENAME1 $FILENAME2 $FILENAME3 $FILENAME4 $FILENAME5"
            echo "$TEST1"
            ./s21_grep $TEST1 > testtxt/s21_grep${var}${var2}.txt
            grep $TEST1 > testtxt/grep${var}${var2}.txt
            DIFF_RES="$(diff -s testtxt/s21_grep${var}${var2}.txt testtxt/grep${var}${var2}.txt)"
            if [ "$DIFF_RES" == "Files testtxt/s21_grep${var}${var2}.txt and testtxt/grep${var}${var2}.txt are identical" ]
              then
                echo "SUCCES $TEST1"
              (( COUNTER_SUCCESS++ ))
              else
                echo "FAIL $TEST1"
                echo "$TEST1" >> log.txt
                (( COUNTER_FAIL++ ))
            fi
           rm testtxt/s21_grep${var}${var2}.txt testtxt/grep${var}${var2}.txt
        fi
          
  done
done

for var in -v -c -l -n -i -h -s -o
do
          TEST1="$var ^[A-Z] $FILENAME1 $FILENAME2 $FILENAME3 $FILENAME4 $FILENAME5"
          # echo "$TEST1"
          ./s21_grep $TEST1 > testtxt/s21_grep$var.txt
          grep $TEST1 > testtxt/grep$var.txt
          DIFF_RES="$(diff -s testtxt/s21_grep$var.txt testtxt/grep$var.txt)"
          if [ "$DIFF_RES" == "Files testtxt/s21_grep$var.txt and testtxt/grep$var.txt are identical" ]
            then
              echo "SUCCES $TEST1"
              (( COUNTER_SUCCESS++ ))
            else
              echo "FAIL $TEST1"
              echo "$TEST1" >> log.txt
              (( COUNTER_FAIL++ ))
          fi
          rm testtxt/s21_grep$var.txt testtxt/grep$var.txt

done

echo "SUCCESS: $COUNTER_SUCCESS"
echo "FAIL: $COUNTER_FAIL"

