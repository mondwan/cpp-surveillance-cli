1.编译前:cp libxmnetsdk.so /usr/lib64
2.编译:g++ test.cpp -L. -lxmnetsdk -o main
3.运行:./main