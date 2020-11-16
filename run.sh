if [ -f "a" ];then
    echo "清理可执行文件..."
    
    rm a
fi
echo "编译："
g++ 2.cpp -o a
echo "运行："
./a -l 2.cpp
# echo "System"
# wc -w 123
# echo "Mine"
# ./a  -w 123
