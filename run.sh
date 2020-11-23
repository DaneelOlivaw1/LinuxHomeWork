if [ -f "a" ];then
    echo "清理可执行文件..."
    rm a
fi
echo "编译："
g++ 3.cpp -o a
echo "运行："
./a