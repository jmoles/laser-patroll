class NumGen 
{
	public:
	  NumGen (int start = 0) : current(start) { }
	  int operator() () { return current++; }
	private:
	  int current;
};
