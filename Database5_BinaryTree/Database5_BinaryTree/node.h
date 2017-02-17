#pragma once
#ifndef __NODE_H
#define __NODE_H

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <conio.h>


using namespace std;

typedef struct _Node {
	char Data;
	struct _Node *Left;
	struct _Node *Right;
} Node;

#endif // __NODE_H