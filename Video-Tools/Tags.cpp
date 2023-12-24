#include "stdafx.h"
#include "Tags.h"

void DeleteTagList(TAG_LIST** tag_list)
{
	if (!tag_list || !*tag_list)
		return;

	for (int i = 0; i < (*tag_list)->iCount; i++) {
		TAG* tag = (*tag_list)->pTags[i];

		if (tag->cName)
			delete[] tag->cName;

		if (tag->cLanguage)
			delete[] tag->cLanguage;

		if (tag->cData)
			delete[] tag->cData;

		delete tag;
	}

	free(*tag_list);
	*tag_list = NULL;

	return;
}