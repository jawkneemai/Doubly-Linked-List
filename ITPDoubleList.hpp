//
// ITPDoubleList.hpp
// Defines and implements the ITPDoubleList collection
//

#pragma once
#include "error.h"
#include <ostream>
#include <sstream>
#include "leaker.h"

template <typename T>
struct Node
{
	// Data in this node
	T mData;
	// Link to previous node
	Node* mPrev;
	// Link to next node
	Node* mNext;
};

template <typename T>
class ITPDoubleList
{
public:
	// Function: Default Constructor
	// Purpose: Initializes size to 0 and head/tail to null
	// Input: None
	// Returns: Nothing
	ITPDoubleList()
	{
		mSize = 0;
		mHead = nullptr;
		mTail = nullptr;
		mCurr = nullptr;
	}

	// Function: Destructor
	// Purpose: Calls the clear function to delete the list
	// Input: None
	// Returns: Nothing
	~ITPDoubleList()
	{
		clear();
	}

	// Function: Copy Constructor
	// Purpose: Initializes this list as a deep copy of other
	// Input: Other list to copy (const reference)
	// Returns: Nothing
	ITPDoubleList(const ITPDoubleList& other)
	{
        this->clear();
        Node<T>* temp = new Node<T>;
        temp = other.mHead;
        while (temp != nullptr)
        {
            this->insert_back(temp->mData);
            temp = temp->mNext;
        }
    }

	// Assignment Operator
	// Function: Assignment Operator
	// Purpose: Clear this list, and then make a deep copy of other
	// Input: Other list to copy (const reference)
	// Returns: *this
	ITPDoubleList& operator=(const ITPDoubleList& other)
	{
        this->clear();
        Node<T>* temp = new Node<T>;
        temp = other.mHead;
        while (temp != nullptr)
        {
            this->insert_back(temp->mData);
            temp = temp->mNext;
        }
		return *this;
	}
    

	// Function: clear
	// Purpose: Deletes every node in this list, sets size to 0, and head/tail to null
	// Input: None
	// Returns: Nothing
	void clear()
	{
		while (this->size() > 0)
        {
            this->remove_back();
        }
        mSize = 0;
        mHead = nullptr;
        mTail = nullptr;
        mCurr = nullptr;
	}

	// Function: size
	// Purpose: Gets the current size of the linked list
	// Input: None
	// Returns: size of the list
	unsigned size() const
	{
        if (mSize < 0)
        {
            error("The size is negative!!");
        }
		return mSize;
	}

	// Function: insert_front
	// Purpose: Inserts a node to the front of the linked list
	// Input: Value to store in the new node
	// Returns: Nothing
	void insert_front(const T& value)
	{
        if (mHead == nullptr && mTail == nullptr && mCurr == nullptr && this->size() == 0) // Complete check for zero items in list
        {
            Node<T>* temp = new Node<T>;
            temp->mData = value;
            temp->mPrev = nullptr;
            temp->mNext = nullptr;
            mHead = temp;
            mTail = temp;
            mCurr = temp;
            mSize++;
        }
        else if (mHead == mTail && mTail == mCurr && mCurr == mHead && this->size() == 1) // Complete check for one item in the list
        {
            Node<T>* temp = new Node<T>;
            temp->mData = value;
            temp->mPrev = nullptr;
            temp->mNext = mHead;
            mHead->mPrev = temp;
            mHead = temp;
            mSize++;
        }
        else // All other cases
        {
            Node<T>* temp = new Node<T>;
            temp->mData = value;
            temp->mPrev = nullptr;
            temp->mNext = mHead;
            mHead->mPrev = temp;
            mHead = temp;
            mSize++;
        }
    } // mCurr will not be moved when adding to front.

	// Function: get_front
	// Purpose: Gets the value of the node at the front of the list
	// Input: None
	// Returns: Value of the node at the front of the list
	T& get_front()
	{
        if (mHead == nullptr && mTail == nullptr && mCurr == nullptr && this->size() == 0)
        {
            error("The list is empty!");
        }
		return mHead->mData;
	}

	// Function: remove_front
	// Purpose: Removes the node at the front of the list
	// Input: None
	// Returns: None
	void remove_front()
	{
		if (mHead == nullptr && mTail == nullptr && mCurr == nullptr && this->size() == 0)
        {
            error("The list is empty!!!!!!");
        }
        else if (mHead == mTail && mTail == mCurr && mCurr == mHead && this->size() == 1)
        {
            delete mTail;
            mHead = nullptr;
            mTail = nullptr;
            mCurr = nullptr;
            mSize--;
        }
        else
        {
            if (mCurr == mHead)
            {
                this->move_next();
            }
            mHead = mHead->mNext;
            delete mHead->mPrev;
            mHead->mPrev = nullptr;
            mSize--;
        }
	}

	// Function: insert_back
	// Purpose: Inserts a node to the back of the linked list
	// Input: Value to store in the new node
	// Returns: Nothing
	void insert_back(const T& value)
	{
        if (mHead == nullptr && mTail == nullptr && mCurr == nullptr && this->size() == 0)
        {
            Node<T>* temp = new Node<T>;
            temp->mData = value;
            temp->mPrev = nullptr;
            temp->mNext = nullptr;
            mHead = temp;
            mTail = temp;
            mCurr = temp;
            mSize++;
        }
        else if (mHead == mTail && mTail == mCurr && mCurr == mHead && this->size() == 1)
        {
            Node<T>* temp = new Node<T>;
            temp->mData = value;
            temp->mPrev = mTail;
            temp->mNext = nullptr;
            mTail->mNext = temp;
            mTail = temp;
            mSize++;
        }
        else
        {
            Node<T>* temp = new Node<T>;
            temp->mData = value;
            temp->mPrev = mTail;
            temp->mNext = nullptr;
            mTail->mNext = temp;
            mTail = temp;
            mSize++;
        }
	}

	// Function: get_back
	// Purpose: Gets the value of the node at the back of the list
	// Input: None
	// Returns: Value of the node at the back of the list
	T& get_back()
	{
        if (mHead == nullptr && mTail == nullptr && mCurr == nullptr && this->size() == 0)
        {
            error("The list is empty!");
        }
        return mTail->mData;
	}

	// Function: remove_back
	// Purpose: Removes the node at the back of the list
	// Input: None
	// Returns: Nothing
	void remove_back()
	{
        if (mHead == nullptr && mTail == nullptr && mCurr == nullptr && this->size() == 0)
        {
            error("The list is empty!!!!!!");
        }
        else if (mHead == mTail && mTail == mCurr && mCurr == mHead && this->size() == 1)
        {
            delete mHead;
            mHead = nullptr;
            mTail = nullptr;
            mCurr = nullptr;
            mSize--;
        }
        else
        {
            if (mCurr == mTail)
            {
                this->move_prev();
            }
            mTail = mTail->mPrev;
            delete mTail->mNext;
            mTail->mNext = nullptr;
            mSize--;
        }
	}

	// Function: reset
	// Purpose: Moves the current "read" pointer to the beginning of the list
	// Input: None
	// Returns: Nothing
	void reset()
	{
        if (mHead == nullptr && mTail == nullptr && mCurr == nullptr && this->size() == 0)
        {
            mCurr = nullptr;
        }
        mCurr = mHead;
	}

	// Function: has_next
	// Purpose: Checks to see if there is another node after the currently read node
	// Input: None
	// Returns: True to indicate there is another valid node to read
	bool has_next()
	{
        if (mCurr == nullptr)
        {
            error("mCurr doesn't exist");
        }
        if (mCurr->mNext != nullptr)
        {
            return true;
        }
        return false;
    }

	// Function: has_prev
	// Purpose: Checks to see if there is another node after the currently read node
	// Input: None
	// Returns: True to indicate there is another valid node to read
	bool has_prev()
	{
        if (mCurr == nullptr)
        {
            error("mCurr doesn't exist");
        }
        if (mCurr->mPrev != nullptr)
        {
            return true;
        }
        return false;
	}

	// Function: move_next
	// Purpose: Moves the reading pointer to the next node
	// Input: None
	// Returns: Nothing
	void move_next()
	{
        if (mHead == nullptr && mTail == nullptr && mCurr == nullptr && this->size() == 0)
        {
            error("List is empty!!");
        }
        else if (mHead == mTail && mTail == mCurr && mCurr == mHead && this->size() == 1)
        {
            return;
        }
        else
        {
            if(mCurr == mTail)
            {
                return;
            }
            else
            {
                mCurr = mCurr->mNext;
            }
        }
	}

	// Function: movePrev
	// Purpose: Moves the reading pointer to the previous node
	// Input: None
	// Returns: Nothing
	void move_prev()
	{
        if (mHead == nullptr && mTail == nullptr && mCurr == nullptr && this->size() == 0)
        {
            error("List is empty!!");
        }
        else if (mHead == mTail && mTail == mCurr && mCurr == mHead && this->size() == 1)
        {
            return;
        }
        else
        {
            if (mCurr == mHead)
            {
                return;
            }
            else
            {
                mCurr = mCurr->mPrev;
            }
        }
    }

	// Function: get_at_curr
	// Purpose: Gets the value of the node at the current reader pointer
	// Input: None
	// Returns: Value of the node at the reader pointer
	T& get_at_curr()
	{
        if (mHead == nullptr && mTail == nullptr && mCurr == nullptr && this->size() == 0)
        {
            error("The list is empty!!!");
        }
        return mCurr->mData;
	}

	// Function: add_at_curr
	// Purpose: Inserts a node at the current reader location in the list
	// Input: Value to store in the new node
	// Returns: Nothing
	void add_at_curr(const T& value)
	{
        if (mHead == nullptr && mTail == nullptr && mCurr == nullptr && this->size() == 0)
        {
            error("there is nothing in the list bro");
        }
        else if (mHead == mTail && mTail == mCurr && mCurr == mHead && this->size() == 1)
        {
            this->insert_front(value);
            this->reset();
        }
        else
        {
            if (mCurr == mHead)
            {
                this->insert_front(value);
            }
            
            else if (mCurr == mTail)
            {
                //Initalize the temp
                Node<T>* temp = new Node<T>;
                temp->mData = value;
                temp->mNext = mTail;
                temp->mPrev = mTail->mPrev;
                
                //Get the last and (originally) second to last
                // elements to point to temp correctly
                temp->mPrev->mNext = temp;
                temp->mNext->mPrev = temp;
                
                /// Make newly inserted object the mCurr
                /// mCurr = temp;
                
                mSize++;
            }
            
            else // Else mCurr != neither the head nor tail
            {
                
                //Initalize the temp
                Node<T>* temp = new Node<T>;
                temp->mData = value;
                temp->mNext = mCurr;
                temp->mPrev = mCurr->mPrev;
                
                // Correctly point to new element
                mCurr->mPrev->mNext = temp;
                mCurr->mPrev = temp;
                
                
                
                
                /// New element is made the mCurr
                ///mCurr = temp;
                
                mSize++;
            }
            
        }
	}
	
	// Function: remove_at_curr
	// Purpose: Removes the node pointed to by the current read pointer
	// Input: None
	// Returns: Nothing
	void remove_at_curr()
	{
        if (mHead == nullptr && mTail == nullptr && mCurr == nullptr && this->size() == 0)
        {
            error("Nothing in the list yo");
        }
        else if (mHead == mTail && mTail == mCurr && mCurr == mHead && this->size() == 1)
        {
            this->clear();
        }
        else
        {
            if (mCurr == mHead)
            {
                this->remove_front();
            }
            else if (mCurr == mTail)
            {
                this->remove_back();
            }
            else
            {
                Node<T>* temp = new Node<T>;
                temp = mCurr;
                mCurr->mPrev->mNext = mCurr->mNext;
                mCurr->mNext->mPrev = mCurr->mPrev;
                this->move_next();
                delete temp;
                mSize--;
            }
        }
	}

private:
	// Pointer to the head node
	Node<T>* mHead;
	// Pointer to the tail node
	Node<T>* mTail;
	// Pointer to current node
	Node<T>* mCurr;
	// Number of nodes currently in the list
	unsigned mSize;

public:
	// Function: Output Stream Operator
	// Purpose: Prints the contents of the list to the provided stream
	// Written in the format of {x, y, ..., z}
	// Input: Stream to write to, list to write
	// Output: Stream after values are written
	friend std::ostream& operator<<(std::ostream& os, const ITPDoubleList<T>& list)
	{
		os << "{";
		
		Node<T>* temp = list.mHead;
		while (temp != nullptr)
		{
			os << temp->mData;
			if (temp != list.mTail)
			{
				os << ",";
			}

			temp = temp->mNext;
		}

		os << "}";
		return os;
	}

	// Function: toString
	// Purpose: Converts list to a string
	// Input: None
	// Output: String (in the format as the ostream)
	std::string toString() const
	{
		std::stringstream str;
		str << *this;
		return str.str();
	}

	// Function: toReverseString
	// Purpose: Outputs the list in reverse
	// Input: None
	// Output: String in reverse
	std::string toReverseString() const
	{
		std::stringstream str;
		
		str << "{";

		Node<T>* temp = mTail;
		while (temp != nullptr)
		{
			str << temp->mData;
			if (temp != mHead)
			{
				str << ",";
			}

			temp = temp->mPrev;
		}

		str << "}";
		
		return str.str();
	}
};
