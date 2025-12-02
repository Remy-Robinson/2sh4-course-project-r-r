#include "objPosArrayList.h"

// Check lecture contents on general purpose array list construction, 
// and modify it to support objPos array list construction.

objPosArrayList::objPosArrayList()
{
    arrayCapacity = ARRAY_MAX_CAP;
    aList = new objPos[arrayCapacity];
    listSize = 0;
}

objPosArrayList::~objPosArrayList()
{
    delete[] aList;
    listSize = 0;
    arrayCapacity = 0;
}

int objPosArrayList::getSize() const
{
    return listSize;
}

void objPosArrayList::insertHead(objPos thisPos)
{    
    if (listSize >= arrayCapacity) //error checking for if list becomes bigger than max size of array
    {
        return;
    }

    for (int i = listSize; i > 0; i--)
    {
        aList[i] = aList[i-1];
    }
    aList[0] = thisPos;
    listSize++;
}

void objPosArrayList::insertTail(objPos thisPos)
{
    if (listSize < arrayCapacity) //checks if list has empty elements
    {
        aList[listSize++] = thisPos;
    }
}

void objPosArrayList::removeHead()
{
    if (listSize <= 0) //checking if list is empty
    {
        return;
    }

    for (int i = 0; i < listSize-1; i++)
    {
        aList[i] = aList[i+1];
    }

    listSize--;
}

void objPosArrayList::removeTail()
{
    if (listSize <= 0) //checking if list is empty
    {
        return;
    }
    listSize--;
}

objPos objPosArrayList::getHeadElement() const
{
    if (listSize <= 0) //is list empty
    {
        //Throw error message
    }
    return aList[0];
}

objPos objPosArrayList::getTailElement() const
{
    if (listSize <= 0) //is list empty
    {
        //throw error message
    }
    return aList[listSize-1];
}

objPos objPosArrayList::getElement(int index) const
{
    if (index < 0 || index >= arrayCapacity) //is index within the actual array elements
    {
        //throw error message
    }
    return aList[index];
}

objPos objPosArrayList::clear()
{
    listSize = 0;
}