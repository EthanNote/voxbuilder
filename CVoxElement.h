#pragma once

#include<memory>
using namespace std;


class CVoxElement
{
public:
	int palette_index;
	int face_mask;
	
	bool is_empty();
	


	CVoxElement();
	CVoxElement(int palette_index, int face_mask);
	~CVoxElement();
};

typedef shared_ptr<CVoxElement> VoxElement;