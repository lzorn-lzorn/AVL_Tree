#pragma once
#ifndef __BSTREE__
#define __BSTREE__
#include <iostream>
template <typename N>
struct BSTNode
{
	BSTNode<N> * lchild, *rchild;
	N data;
	int height;
	BSTNode(N value, BSTNode<N> * l, BSTNode<N> * r):data(value), rchild(r), lchild(l),height(0){}
	BSTNode<N> * operator>(BSTNode<N> * bst) { return this->data > bst->data ? this : bst; }
	BSTNode<N> * operator<(BSTNode<N> * bst) { return this->data < bst->data ? this : bst; }
	int return_height()const { return height; }
};
template <typename T>
class BSTree
{
	BSTNode<T> * root = nullptr;

	int height(BSTNode<T> * bst)const { if(bst != nullptr)		return bst->height; }
	void in_order(BSTNode<T> * bst)const;
	bool destroy(BSTNode<T> * & bst);//������
		
	BSTNode<T> *insert(BSTNode<T> * &bst, T value);	 //����ֵΪvalue�Ľ��
	BSTNode<T> * search(BSTNode<T> * bst, T value)const; //�ݹ������bst��ֵΪvalue��Ԫ��
	BSTNode<T> * remove(BSTNode<T> * & bst, BSTNode<T> * delete_bst);//��bst��ɾ��delete_bst
	BSTNode<T> * minimum(BSTNode<T> * bst);//�ҵ�bst����С�Ľ��
	BSTNode<T> * maximum(BSTNode<T> * bst);//�ҵ�bst����С�Ľ��
	BSTNode<T> * left_left_rotation(BSTNode<T> * bst);
	BSTNode<T> * right_right_rotation(BSTNode<T> * bst);
	BSTNode<T> * left_right_rotation(BSTNode<T> * bst);
	BSTNode<T> * right_left_rotation(BSTNode<T> * bst);

public:
	BSTree():root(nullptr) {  }
	BSTree(T data) { root = new BSTNode<T>(data, nullptr, nullptr); }
	BSTree(T * array, int size);
	BSTree(const BSTree<T>& bst);
	~BSTree() { destroy(root); }

	BSTNode<T> * operator+=(T value) { return insert(root, value); }
	BSTNode<T> * operator+=(BSTNode<T> bst) { return insert(root, bst->data); }
	BSTNode<T> * operator-=(T value);
	BSTNode<T> * operator-=(BSTNode<T> bst);

	int height() { return height(root); }
	int max(int a, int b) { return a > b ? a : b; }//���ش��ֵ
	void in_order() { in_order(root); }
	void remove(T value); //ɾ��ֵΪvalue�Ľ��
	bool search(const T value);
	T maximum();
	T minimum();
};
#endif // !__BSTREE__

template<typename T>
inline BSTNode<T>* BSTree<T>::left_left_rotation(BSTNode<T>* bst)
{
	BSTNode<T> * temp;

	temp = bst->lchild;
	bst->lchild = temp->rchild;
	temp->rchild = bst;

	bst->height = max(height(bst->lchild), height(bst->rchild)) + 1;
	temp->height = max(height(temp->lchild), temp->height) + 1;

	return temp;
}

template<typename T>
inline BSTNode<T>* BSTree<T>::right_right_rotation(BSTNode<T>* bst)
{
	BSTNode<T> * temp;
	temp = bst->rchild;
	bst->rchild = temp->lchild;
	temp->lchild = bst;

	bst->height = max(height(temp->lchild), height(bst->rchild)) + 1;
	temp->height = max(height(temp->rchild), bst->height) + 1;

	return temp;
}

template<typename T>
inline BSTNode<T>* BSTree<T>::left_right_rotation(BSTNode<T>* bst)
{
	bst->lchild = right_right_rotation(bst->lchild);
	return left_left_rotation(bst);
}

template<typename T>
inline BSTNode<T>* BSTree<T>::right_left_rotation(BSTNode<T>* bst)
{
	bst->rchild = left_left_rotation(bst);
	return right_right_rotation(bst);
}

template<typename T>
inline void BSTree<T>::in_order(BSTNode<T>* bst) const
{
	if (bst == nullptr)
		return;
	in_order(bst->lchild);
	std::cout << bst->data<< " ";
	in_order(bst->rchild);
}

template<typename T>
inline bool BSTree<T>::destroy(BSTNode<T>*& bst)
{
	if (bst == nullptr)
		return true;
	if (bst->lchild != nullptr)
		destroy(bst->lchild);
	if (bst->rchild != nullptr)
		destroy(bst->rchild);
	delete bst;
}

template<typename T>
inline BSTNode<T> * BSTree<T>::insert(BSTNode<T>*& bst, T value)
{
	if (bst == nullptr)
	{
		bst = new BSTNode<T>(value, nullptr, nullptr);
		if (bst == nullptr)
		{
			std::cout << "���ĳ�ʼ��ʧ�ܣ�" << std::endl;
			return nullptr;
		}
	}
	else if (value < bst->data)
	{
		bst->lchild = insert(bst->lchild, value);
		if (height(bst->lchild) - height(bst->rchild) == 2)
			if (value < bst->lchild->data)
				bst = left_left_rotation(bst);
			else
				bst = left_right_rotation(bst);
	}
	else if (value > bst->data)
	{
		bst->rchild = insert(bst->rchild, value);
		if (height(bst->rchild) - height(bst->lchild) == 2)
			if (value > bst->rchild->data)
				bst = right_right_rotation(bst);
			else
				bst = right_left_rotation(bst);
	}
	else
		std::cout << "�ýڵ��Ѵ���" << std::endl;

	bst->height = max(height(bst->lchild), height(bst->rchild)) + 1;
	return bst;
}

template<typename T>
inline BSTNode<T>* BSTree<T>::search(BSTNode<T>* bst, T value) const
{
	if (bst == nullptr || bst->data == value)
		return bst;
	if (value < bst->data)
		return search(bst->lchild, value);
	else
		return search(bst->rchild, value);
	return nullptr;
}

template<typename T>
inline BSTNode<T>* BSTree<T>::remove(BSTNode<T>*& bst, BSTNode<T>* delete_bst)
{
	if (bst == nullptr || delete_bst == nullptr)
		return nullptr;

	if (delete_bst->data < bst->data)
	{
		bst->lchild = remove(bst->lchild, delete_bst);
		if (height(bst->rchild) - height(bst->lchild) == 2)
		{
			BSTNode<T> * temp = bst->rchild;
			if (height(temp->lchild) > height(temp->rchild))
				bst = right_left_rotation(bst);
			else
				bst = right_right_rotation(bst);
		}
	}
	else if (delete_bst->data > bst->data)
	{
		bst->rchild = remove(bst->rchild, delete_bst);
		if (height(bst->lchild) - height(bst->rchild) == 2)
		{
			BSTNode<T> * temp = bst->lchild;
			if (height(temp->rchild) > height(temp->lchild))
				bst = left_right_rotation(bst);
			else
				bst = left_left_rotation(bst);
		}
	}
	else
	{
		if(bst->lchild != nullptr && (bst->rchild != nullptr))
			if (height(bst->lchild) > height(bst->rchild))
			{
				// ���bst�����������������ߣ�
				// ��(01)�ҳ�bst���������е����ڵ�
				//   (02)�������ڵ��ֵ��ֵ��bst��
				//   (03)ɾ�������ڵ㡣
				// ����������"bst�������������ڵ�"��"bst"������
				// �������ַ�ʽ�ĺô��ǣ�ɾ��"bst�������������ڵ�"֮��AVL����Ȼ��ƽ��ġ�
				BSTNode<T> * temp = maximum(bst->lchild);
				bst->data = temp->data;
				bst->lchild = remove(bst->lchild, temp);
			}
			else
			{
				// ���bst��������������������(��������ȣ�������������������1)
				// ��(01)�ҳ�bst���������е���С�ڵ�
				//   (02)������С�ڵ��ֵ��ֵ��tree��
				//   (03)ɾ������С�ڵ㡣
				// ����������"bst������������С�ڵ�"��"bst"������
				// �������ַ�ʽ�ĺô��ǣ�ɾ��"bst������������С�ڵ�"֮��AVL����Ȼ��ƽ��ġ�
				BSTNode<T> * temp = maximum(bst->rchild);
				bst->data = temp->data;
				bst->rchild = remove(bst->rchild, temp);
			}
		else
		{
			BSTNode<T> * temp = bst;
			bst = (bst->lchild != nullptr) ? bst->lchild : bst->rchild;
			delete temp;
		}
	}
	return bst;
}

template<typename T>
inline BSTNode<T>* BSTree<T>::minimum(BSTNode<T>* bst)
{
	if (bst == nullptr)
		return  nullptr;
	while (bst->lchild != nullptr)
		bst = bst->lchild;
	return bst;
}

template<typename T>
inline BSTNode<T>* BSTree<T>::maximum(BSTNode<T>* bst)
{
	if (bst == nullptr)
		return nullptr;
	while (bst->rchild != nullptr)
		bst = bst->rchild;
	return bst;
}

template<typename T>
inline BSTNode<T>* BSTree<T>::operator-=(T value)
{
	BSTNode<T> * temp;
	if ((temp = search(root, value)) != nullptr)
		return remove(root, temp);
}

template<typename T>
inline BSTNode<T>* BSTree<T>::operator-=(BSTNode<T> bst)
{
	BSTNode<T> * temp;
	if ((temp = search(root, value)) != nullptr)
		return remove(root, temp);
}

template<typename T>
inline void BSTree<T>::remove(T value)
{
	BSTNode<T> * temp;
	if ((temp = search(root, value)) != nullptr)
		root = remove(root, temp);
}

template<typename T>
inline bool BSTree<T>::search(const T value)
{
	if (search(root, value) == nullptr)
		return false;
	return true;
}

template<typename T>
inline T BSTree<T>::maximum()
{
	BSTNode<T> * temp = maximum(root);
	if (temp != nullptr)
		return temp->data;
	return (T)nullptr;
}

template<typename T>
inline T BSTree<T>::minimum()
{
	BSTNode<T> * temp = minimum(root);
	if (temp != nullptr)
		return temp->data;
	return (T)nullptr;
}
