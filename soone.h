#ifndef SOONE_H
#define SOONE_H

#include "main.h"

class soone
{
public:
	soone(char *name);

	~soone();

public:
	virtual void show_value();

	char *m_name;
};

#endif
