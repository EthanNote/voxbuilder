#include "CVoxElement.h"



bool CVoxElement::is_empty()
{
	return palette_index < 0;
}

CVoxElement::CVoxElement()
{
}

CVoxElement::CVoxElement(int palette_index, int face_mask):
	palette_index(palette_index), face_mask(face_mask)
{
}


CVoxElement::~CVoxElement()
{
}
