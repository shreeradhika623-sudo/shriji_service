echo "=============================="
echo "STDLIB FILES"
echo "=============================="
ls src/stdlib

echo
echo "=============================="
echo "FUNCTION COUNT PER MODULE"
echo "=============================="
grep -h "^Value std_" src/stdlib/*.c | wc -l

echo
echo "=============================="
echo "ALL STDLIB FUNCTIONS"
echo "=============================="
grep -h "strcmp(node->function_name" src/stdlib/*.c

echo
echo "=============================="
echo "JSON FUNCTIONS"
echo "=============================="
grep -n "json_" src/stdlib/std_json.c

echo
echo "=============================="
echo "STRING FUNCTIONS"
echo "=============================="
grep -n "function_name" src/stdlib/std_string.c

echo
echo "=============================="
echo "LIST FUNCTIONS"
echo "=============================="
grep -n "function_name" src/stdlib/std_list.c

echo
echo "=============================="
echo "DICT FUNCTIONS"
echo "=============================="
grep -n "function_name" src/stdlib/std_dict.c

echo
echo "=============================="
echo "FILE FUNCTIONS"
echo "=============================="
grep -n "function_name" src/stdlib/std_file.c

echo
echo "=============================="
echo "MATH FUNCTIONS"
echo "=============================="
grep -n "function_name" src/stdlib/std_math.c

echo
echo "=============================="
echo "TIME FUNCTIONS"
echo "=============================="
grep -n "function_name" src/stdlib/std_time.c

echo
echo "=============================="
echo "PATH FUNCTIONS"
echo "=============================="
grep -n "function_name" src/stdlib/std_path.c

echo
echo "=============================="
echo "OS FUNCTIONS"
echo "=============================="
grep -n "function_name" src/stdlib/std_os.c

echo
echo "=============================="
echo "ENV FUNCTIONS"
echo "=============================="
grep -n "function_name" src/stdlib/std_env.c

echo
echo "=============================="
echo "RANDOM FUNCTIONS"
echo "=============================="
grep -n "function_name" src/stdlib/std_random.c
