#ifndef JunParMan_HH
#define JunParMan_HH 1
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <cstdlib>
using namespace std;

struct Par_DSSD
{
	string name;
	float heigh;
	float width;
	float thick;
	int vstrips;
	int hstrips;
	float distance;
	float angle;
};

class JunParMan
{
private:
	JunParMan();
	static JunParMan* thisParMan;
public:
	virtual ~JunParMan();
	static JunParMan* Instance();
	void ReadParFile(string filename);
	float GetPar(string parname);
  void SetPar(string parname,float value);
	Par_DSSD* GetDSSDPar(string dssdname);
	void PrintAll();
	vector<string> GetAllDSSDName();
private:
	map<string,float> mPar;
	vector<Par_DSSD> vDSSDPar;
};
#endif
