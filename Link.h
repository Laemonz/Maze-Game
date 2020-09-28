#ifndef LINK_H
#define LINK_H

#define TYPE int    //what var will the stack store
					//too lazy to actually template all of this
class Link {
public:
	Link();
	virtual ~Link();

	Link* getBelow();
	void setBelow(Link*);

	TYPE getContents();
	void setContents(TYPE);


private:
	Link* below;
	TYPE contents;
};

#endif // LINK_H
