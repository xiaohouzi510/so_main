#include <stdio.h>
#include <dlfcn.h>
#include <string.h>
#include "main.h"
#include "soone.h"

student::student(int num) : m_num(num)
{

}

student::~student()
{

}

void student::display()
{
	printf("m_num value is %d\n",m_num);
}

extern "C"
void helloworld()
{
	printf("hello world\n");
}

/*
	1.主程序调用动态库的函数声明要加extern "C"
	2.动态库调用主程序的函数声明要加extern "C"
 	3.主程序中定义的类,传指针到动态库中,动态库可包含主程序头文件,makefile主程序要加-Wl,-E,然后调用其成员函数.
	4.动态库导出的类,主程序通过包含头文可调用其虚函数.
*/

typedef void (*cb)(student *st);
typedef soone* (*so_cb)(char *name);

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
		printf("dlsym %s export_fun error %s\n",name,dlerror());
		return 0;
	}

	student st(10086);
	t_cb(&st);
	so_cb sc = (so_cb)dlsym(module,"new_obj");
	if(sc == NULL)
	{
		dlclose(module);
		printf("dlsym %s new_obj error %s\n",name,dlerror());
		return 0;
	}

	char t_char[]  = "您好";
	int len 	   = sizeof(t_char);
	char *new_name = new char[len];

	strcpy(new_name,t_char);
	new_name[len - 1] = 0;

	soone *so = sc(new_name);
	so->show_value();
	dlclose(module);

	return 0;
}
