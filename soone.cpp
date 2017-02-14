#include "soone.h"
#include <stdio.h>

soone::soone(char *name) : m_name(name)
{
}

soone::~soone()
{

}

void soone::show_value()
{
	printf("my name is %s\n",m_name);
}

extern "C"
void helloworld();

extern "C"
void export_fun(student *st)
{
	st->display();
	printf("student %d\n",st->m_num);
	helloworld();
}

extern "C"
soone* new_obj(char *name)
{
	return new soone(name);
}
