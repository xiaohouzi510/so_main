#include <stdio.h>
#include <dlfcn.h>

extern "C"
void helloworld()
{
	printf("hello world\n");
}

/*
	1.动态库声明要加extern "C"
	2.主程序定义要加extern "C"
	3.makefile 主程序要加-Wl-E
*/

/*
 	1.主程序中定义的类传指针到动态库,动态库是不可调用该类的成员函数。
	2.动态库导出的类,主程序可以调用其成员函数。
*/

typedef void (*cb)();
int main(int argc,char *argv[])
{
	const char *name = "soone.so";
	void *module = dlopen(name,RTLD_LAZY);
	if(module == NULL)
	{
		printf("dlopen %s error %s\n",name,dlerror());
		return 0;
	}

	cb t_cb = (cb)dlsym(module,"export_fun");
	if(t_cb == NULL)
	{
		dlclose(module);
		printf("dlsym %s error %s\n",name,dlerror());
		return 0;
	}

	t_cb();
	dlclose(module);
	return 0;
}
