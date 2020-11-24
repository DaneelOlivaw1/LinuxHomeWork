if [ -f "a" ];then
    echo "清理可执行文件..."
    rm a
fi
echo "编译："
g++ 5-server.cpp -o server
g++ 5-client.cpp -o client
# echo "运行："
