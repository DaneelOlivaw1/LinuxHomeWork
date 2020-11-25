if [ -f "a" ];then
    echo "清理可执行文件..."
    rm a
fi
echo "编译："
g++ 6-server.cpp -o server
g++ 6-client.cpp -o client
# echo "运行："
