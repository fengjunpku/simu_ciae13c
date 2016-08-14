#include "myTele.hh"

myTele::myTele()
{}

myTele::~myTele()
{
    delete[] pCellSD;
    delete[] pSolidSD;
    delete[] pLogicSD;
    delete[] pPhysiSD;
}