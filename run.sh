if [ -f "server" ];then
    echo "清理server文件..."
    rm server
fi
if [ -f "client" ];then
    echo "清理client文件..."
    rm client
fi
echo "编译："
g++ 7-server.cpp -o server
g++ 7-client.cpp -o client
# echo "运行："
