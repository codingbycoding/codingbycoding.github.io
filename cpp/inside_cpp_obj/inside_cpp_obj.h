#ifndef ADAM_INSIDE_CPP_OBJ_H_
#define ADAM_INSIDE_CPP_OBJ_H_

class CEmpty {
 public:
	CEmpty();
};

class CBase {
 public:
	CBase();
};


class CX : public virtual CBase {
	//class CX : public CBase {
 public:
	CX();
	virtual void abc();
};

//class CY : public virtual CBase {
class CY : public CBase {
 public:
	CY();
	virtual void cba();
};


class CXY : public CX, public CY {
 public:
	CXY();
};




class CSize {
public:
	CSize();
	virtual ~CSize();
	virtual void Echo();
private:
	int count_;
	int dummy_count_;//with or without the size of the class object will be 16 bytes in x64 compile system. nonstatic data member + vptr + align pad
};


class CSizeDerived : public CSize {
public:
	CSizeDerived ();
	virtual ~CSizeDerived();

	void Echo();//also is virtual
private:
};
