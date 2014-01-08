/*	
Copyright (C) 2013  Niraj Rayalla

This file is part of 3-DPhysicsSim.    

3-DPhysicsSim is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

3-DPhysicsSim is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _WX_IRR_LIST
#define _WX_IRR_LIST

#define foreach(_datatype_, _name_, _list_) for(List<_datatype_>::iterator _name_ = _list_->begin(); _name_ != NULL; _name_->advance(_name_))
#define foreachfrom(_start_) for(_start_; _start_ != NULL; _start_->advance(_start_))

template <class T>
class Node
{
private:
	T data;
	bool deleteDat;

	//If data is not a pointer do nothing cause there is nothing to delete
	template<typename G>
	void DeleteData(G& dat) {}	
	//If data is a pointer delete it
	template<typename G>
	void DeleteData(G* dat) { if (deleteDat) delete dat; }
public:
	Node<T>* prev;
	Node<T>* next;

	Node(T data_In, bool _deleteDat)
	{
		data = data_In;
		deleteDat = _deleteDat;
		next = NULL;
		prev = NULL;
	}

	Node(T data_In, bool _deleteDat, Node<T>* _prev)
	{
		data = data_In;
		deleteDat = _deleteDat;
		next = NULL;
		prev = _prev;
	}

	~Node()	{ DeleteData(data);	}

	T GetData() { return data; }

	Node<T>* GetNext() { return next; }

	void advance(Node<T>* & in) { in = GetNext(); }

	void Remove()
	{
		if (prev)
			prev->next = next;
		if (next)
			next->prev = prev;
	}
};

template <class T>
class List
{
private:		
	Node<T>* head;
	Node<T>* tail;
	int size;

	void RecursiveDelete(Node<T>* current)
	{
		if (current)
		{
			Node<T>* next = current->next;
			if (next)
			{
				RecursiveDelete(current->next);
			}
			delete current;
				
			size--;
		}
	}

	void DeleteFromTail()
	{
		DeleteFromNodeBackwards(tail);
	}

	void DeleteFromNodeBackwards(Node<T>* start)
	{
		Node<T>* current = start;

		while(current)
		{
			Node<T>* nextToDelete = current->prev;

			delete current;

			current = nextToDelete;
		}
	}

public:
	typedef Node<T>* iterator;
	List() {
		head = NULL;
		tail = NULL;
		size = 0;
	}

	List(T data_In, bool _deleteDat = true) {
		//Add(data_In, _deleteDat);
		size = 0;
		Add(data_In, _deleteDat);
	}

	~List()
	{
		//RecursiveDelete(head);
		DeleteFromTail();
	}

	Node<T>* GetHead()
	{
		return head;
	}

	Node<T>* GetTail()
	{
		return tail;
	}
	///Adding//

	Node<T>* AddFront(T data_In, bool _deleteDat = true)
	{
		if (head)
		{
			return AddBefore(head, data_In, _deleteDat);
		}
		else
		{
			Node<T>* newElement = new Node<T>(data_In, _deleteDat);
			newElement->prev = NULL;
			newElement->next = NULL;

			head = newElement;
			tail = newElement;

			return newElement;
		}

		return NULL;
	}


	Node<T>* Add(T data_In, bool _deleteDat = true)
	{
		if (!head || !tail)
		{
			Node<T>* newElement = new Node<T>(data_In, _deleteDat);

			head = newElement;
			tail = newElement;

			size = 1;

			return newElement;
		}
		return AddAfter(tail, data_In, _deleteDat);
	}

	Node<T>* AddAt(int index, T data_In, bool _deleteDat = true)
	{
		if (index < size)
		{
			Node<T>* newElement = new Node<T>(data_In, _deleteDat);

			if (index == 0)
			{
				if (head)
				{
					head->prev = newElement;
					newElement->prev = NULL;
					newElement->next = head;
					head = newElement;
				}
				else
				{
					newElement->prev = NULL;
					newElement->next = NULL;
					head = newElement;
					tail = newElement;
				}
			}
			else if (index == size)
			{
				tail->next = newElement;
				newElement->prev = tail;
				newElement->next = NULL;
				tail = newElement;
			}
			else
			{
				AddBefore(GetAt(index), data_In, _deleteDat);
			}

			size++;

			return newElement;
		}

		return NULL;
	}

	Node<T>* AddBefore(Node<T>* elem, T data_In, bool _deleteDat = true)
	{
		Node<T>* newElement = new Node<T>(data_In, _deleteDat);

		if (elem == head)
		{
			head->prev = newElement;
			newElement->prev = NULL;
			newElement->next = head;
			head = newElement;
		}
		else
		{
			Node<T>* elemPrev = elem->prev;
			elemPrev->next = newElement;
			newElement->prev = elem->prev;
			elem->prev = newElement;
			newElement->next = elem;
		}

		size++;

		return newElement;
	}

	Node<T>* AddAfter(Node<T>* elem, T data_In, bool _deleteDat = true)
	{
		Node<T>* newElement = new Node<T>(data_In, _deleteDat);

		if (elem == tail)
		{
			tail->next = newElement;
			newElement->prev = tail;
			newElement->next = NULL;
			tail = newElement;
		}
		else
		{
			Node<T>* elemNext = elem->next;
			elemNext->prev = newElement;
			newElement->next = elemNext;
			newElement->prev = elem;
			elem->next = newElement;
		}

		size++;

		return newElement;
	}

	Node<T>* Append(List<T>* inputList, bool deleteInputList = true)
	{
		if (inputList)
		{
			size += inputList->GetSize();

			Node<T>* retValue = inputList->GetHead();

			if (tail)
			{
				tail->next = retValue;
				inputList->GetHead()->prev = tail;
				tail = inputList->GetTail();
			}
			else
			{
				head = retValue;
				tail = inputList->GetTail();
			}

			if (deleteInputList)
			{
				inputList->head = NULL;
				inputList->tail = NULL;
				delete inputList;				
			}

			return retValue;
		}

		return NULL;
	}

	Node<T>* GetAt(int index)
	{
		Node<T>* current = head;
		for (int i = 0; i < index; i++)
		{
			current = current->next;
		}

		return current;
	}

	Node<T>* Remove(Node<T>* elem)
	{
		if (elem)
		{
			Node<T>* retValue = elem->next;

			if (elem == head)
			{
				head = retValue;
			}
			if (elem == tail)
			{
				tail = elem->prev;
			}

			elem->Remove();

			if (!head || !tail)
			{
				head = NULL;
				tail = NULL;
				size = 0;
			}
			else
			{
				size--;
			}

			delete elem;

			return retValue;
		}

		return NULL;
	}

	Node<T>* Remove(Node<T>* elem, int numToDelete)
	{
		if (elem)
		{
			Node<T>* retValue = NULL;

			if (elem == head)
			{
				Node<T>* current = elem;
				int deletedSoFar = 0;
				while(current && deletedSoFar < numToDelete)
				{
					current = current->next;
					deletedSoFar++;
				}

				if(!current)
				{
					Clear();
					return NULL;
				}

				head = current;
				DeleteFromNodeBackwards(head->prev);
				head->prev = NULL;

				return head;
			}
			else
			{
				Node<T>* last = elem->prev;
				Node<T>* current = elem;
				int deletedSoFar = 0;
				while(current && deletedSoFar < numToDelete)
				{
					last = current;
					current = current->next;
					deletedSoFar++;
				}

				if(!current)
				{
					tail = elem->prev;
					tail->next = NULL;
					elem->prev = NULL;

					DeleteFromNodeBackwards(last);

					return NULL;
				}

				elem->prev->next = current;
				elem->prev = NULL;

				DeleteFromNodeBackwards(last);

				return current;
			}
		}

		return NULL;
	}

	void Remove(int index) { Remove(GetAt(index)); }

	void Clear()
	{		
		//RecursiveDelete(head);
		DeleteFromTail();
		size = 0;
		head = NULL;
		tail = NULL;
	}

	void operator +(const T & right)
	{
		Add(right);
	}

	void operator +=(const T & data)
	{
		Add(data);
	}

	//Node<T>* Add(T data_In, bool _deleteDat);

	iterator begin() { return GetHead(); }

	int GetSize() { return size; }
};

#endif
