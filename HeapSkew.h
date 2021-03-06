#if !defined HEAPSKEW_H
#define HEAPSKEW_H

#include "BinaryTree.h"
#include "wx/wx.h"

template < class T >
class HeapSkew : public Drawable
{

   private:
      BinaryTree<T>* bt;
      int sze;
      BinaryTree<T>* merge(BinaryTree<T>* left, BinaryTree<T>* right);

      int (*compare_items) (T* item_1, T* item_2);

   public:
      HeapSkew(int (*comp_items) (T* item_1, T* item_2));
      ~HeapSkew();

      bool heapIsEmpty();
      void heapInsert(T* item);
      T* heapRemove();

      void draw(wxDC& dc, int width, int height);
      void mouseClicked(int x, int y);

};

// this is a MAXHEAP (largest items to top alphabetical order)
template < class T >
HeapSkew<T>::HeapSkew(int (*comp_items) (T* item_1, T* item_2)) : Drawable()
{ 
   bt = new BinaryTree<T>();
   sze = 0;

   compare_items = comp_items;
}

template < class T >
HeapSkew<T>::~HeapSkew() 
{ 
   delete bt;
}  

template < class T >
bool HeapSkew<T>::heapIsEmpty()
{
   return sze == 0;
}

template < class T >
BinaryTree<T>* HeapSkew<T>::merge(BinaryTree<T>* left, BinaryTree<T>* right)
{
  //DO THIS


	//if left is empty -- return right
	//if right is empty -- return left
	
	
	if( left->isEmpty() )
	{
		return right;
	}
	else if( right->isEmpty() )
	{
		return left;
	}
	
	//if left<right call merge (right,left)
	T* leftRootItem = left->getRootItem();
	T* rightRootItem = right->getRootItem();
	int comp = (*compare_items) (leftRootItem, rightRootItem);
	BinaryTree<T>* temp = left;
	
	if (comp < 0)
	{
		BinaryTree<T>* sub = merge(right, left);
		return sub;
	}
	else
	{
		BinaryTree<T>* LL = temp->detachLeftSubtree();
		BinaryTree<T>* LR = temp->detachRightSubtree();
		
		temp->attachRightSubtree(LL);
		if (LR->isEmpty())
		{
			temp->attachLeftSubtree(right);
			return temp;
		}
		else
		{
			BinaryTree<T>* sub = merge(LR, right);
			temp->attachLeftSubtree(sub);
			return temp;
		}
	}

}

template < class T >
void HeapSkew<T>::heapInsert(T* item)
{
   //DO THIS (calls merge, should be short)

	BinaryTree<T>* right = new BinaryTree<T>( item );
	bt = merge( bt, right );
}

template < class T >
T* HeapSkew<T>::heapRemove()
{
   //DO THIS (calls merge, should be short)
   
	T* item = bt->getRootItem();
	
	BinaryTree<T>* left = bt->detachLeftSubtree();
	BinaryTree<T>* right = bt->detachRightSubtree();

	bt = merge(left, right);
	
	return item;
}

template < class T >
void HeapSkew<T>::draw(wxDC& dc, int width, int height)
{
   bt->draw(dc, width, height);
}

template < class T >
void HeapSkew<T>::mouseClicked(int x, int y) {bt->mouseClicked(x, y);}

#endif
