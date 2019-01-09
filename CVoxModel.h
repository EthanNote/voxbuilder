#pragma once

#include "CVoxPalette.h"
#include "CVoxElement.h"
#include "CVoxBuffer.h"

class CVoxModel
{
public:

	vector<CVoxElement> elements;
	int size;
	void resize(int size);


	VoxBuffer build_buffer();
	void calc_masks();

	CVoxElement* get_element(int i, int j, int k);

	CVoxModel();
	~CVoxModel();
};

