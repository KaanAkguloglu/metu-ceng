#ifndef BST_HPP
#define BST_HPP

#include <iostream>
#include <vector>
#include "BSTNode.hpp"

template <class T>
class BST
{
    public: // DO NOT CHANGE THIS PART.
        BST();
        BST(const BST &obj);
        ~BST();

        BSTNode<T> *getRoot() const;

		void insert(const T &data);
		void remove(const T &data);

		BSTNode<T> *find(const T &data);

		void balanceTree();

		bool isLeaf(BSTNode<T> *node);
		int nodeHeight(BSTNode<T> *node);
		int nodeDepth(BSTNode<T> *node);
		
		void printInorder();
		void printReverseInorder();

    private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.
        
        /* HELPER FUNCTION of Destructor */
    	void destruct(BSTNode<T> *&cur){
    		if(cur){
			destruct(cur->right);
			destruct(cur->left);
			delete cur;
			}	
    	};

    	/*HELPER FUNC of insertion */
    	void insert_helper(BSTNode<T> *&cur, BSTNode<T> *&newNode){
    		if(cur == NULL){
				cur = newNode;
			}
			else if(cur->data > newNode->data){
				insert_helper(cur->left,newNode);
			}
			else if(cur->data < newNode->data){
				insert_helper(cur->right,newNode);
			}
        
    	};
		
        /*HELPER for Copy constructor*/
		void helper_construct(const BSTNode<T> *cur){
            
			if(cur){
			insert(cur->data);			
			helper_construct(cur->left);
			helper_construct(cur->right);
			}
        };
        
        /* HELPER for inorder print */
        void helper_print(BSTNode<T> *cur){
			
			if(cur){
				helper_print(cur->left);
                
                /* std::cout<<" depth = "<< nodeDepth(cur) << " "  */ ;                    

				if(biggest(root)!=cur){
					std::cout<< "	"<<cur->data<< "," << std::endl;
				}

				else{
					std::cout<< "	"<<cur->data<< std::endl;
				}

                
				helper_print(cur->right); 
			}
		};
        
        /*Helper for postoder print */
        void helper_reverse_print(BSTNode<T> *cur){
			if(cur){
				helper_reverse_print(cur->right);

				if(smallest(root)!=cur){
					std::cout<< "	"<<cur->data<< "," << std::endl;
				}

				else{
					std::cout<< "	"<<cur->data<< std::endl;
				}
				helper_reverse_print(cur->left); 
			}
		};
        
        /* Extra Function for finding biggest in tree 
		NOTE: RETURNS NULL IF TREE IS NULL
		*/

		BSTNode<T>* biggest(BSTNode<T> *cur){
			if(cur && cur->right){
				return biggest(cur->right);
			}
			else{
				return cur;
			}
		};

        BSTNode<T>* helper_find(BSTNode<T> *cur, T data){
			if(!cur){
				return NULL;
			}
			else{
				if(cur->data == data){
					return cur;
				}
				else if(data > cur->data ){
					return helper_find(cur->right,data);
				}
				else{
					return helper_find(cur->left,data);
				}
			}
		};
        
        BSTNode<T>* getParent(BSTNode<T> *cur,BSTNode<T> *node){
			if(cur){
				if( (cur->right==node) || ( cur->left==node)) {
					return cur;
				}
				else{
					if(cur->data > node->data){
						return getParent(cur->left,node);
					}
					else{
						return getParent(cur->right,node);
					}
				}
			}
			else{
			    std::cout << "no parent error (bastard)" << std::endl;
			}
		};
        
        BSTNode<T>* smallest (BSTNode<T> *cur){
			if(cur && cur->left){
				return smallest(cur->left);
			}
			else{
				return cur;
			}
		};

        void assign_only_child(BSTNode<T> *node, BSTNode<T> *child){
            BSTNode<T> *parent;
			if(node==getRoot()){
				root = child;	
			}
			else{
				parent = getParent(root,node);
		    	if(parent->left == node){
                    
		    		parent->left = child;
		    	}
		    	else {
		    		parent->right = child;
                    
		    	}
		    }
		};

        void helper_remove(BSTNode<T> *&node){
            BSTNode<T> *successor;
			/* Case 1 : Leaf */

	    	if(isLeaf(node)){
	    		
	    		if(node == getRoot()){

                    

	    			 root = NULL;
	    		}

	    		

	    		else{    			

                
		    	 assign_only_child(node,NULL);
                }
	    		delete node;
	    	}

	    

	    	
	    	else if(node->right && !(node->left) ){

                

	    		assign_only_child(node,node->right);
                delete node;
	    	}

	    
	    	else if(!(node->right) && node->left){

               

	    		assign_only_child(node,node->left);
                delete node;
	    	}

	    	
	    	else{

               

                
	    		successor = smallest(node->right);

                
	    	
            	T temp_data = successor->data;
                helper_remove(successor);

                node->data = temp_data;
               

	    	}
		};
        
        void construct_vector(BSTNode<T> *cur, std::vector<T> &v){
			if(cur){
				construct_vector(cur->left,v);
				v.push_back(cur->data);
				construct_vector(cur->right,v); 
			}
		};

		void helper_balance(int start,int end, std::vector<T> v){
			int middle;
			if(start == end){
				insert(v[start]);
			}
			else if(start+1 ==end){
				insert(v[start]);
				insert(v[end]);
			}
			else if(start +2 == end){
				insert(v[start+1]);
				insert(v[start]);
				insert(v[start+2]);
			}
			else{
				middle = (start + end) /2;

				insert(v[middle]);
				helper_balance(start,middle-1,v);
				helper_balance(middle+1,end,v);
			}
		};

        int helper_height(BSTNode<T> *cur, int depth){
			if(!cur){
				return depth;
			}
			else{
                int left,right;
                left = helper_height(cur->left,depth+1);
                right = helper_height(cur->right,depth+1);
                if(left>right){
                    return left;
                }
                else{
                    return right;
                }
				
			}
		};
    
	private: // DO NOT CHANGE THIS PART.
        BSTNode<T> *root;
};

template<class T>
BST<T>::BST()
{
    root = NULL;
}

template<class T>
BST<T>::BST(const BST &obj)
{
    root = NULL;
    
    if(obj.getRoot()){
    	helper_construct(obj.getRoot());
	}
    
    
}


template <class T>
BST<T>::~BST()
{
    
    destruct(root);
}


template<class T>
BSTNode<T> * BST<T>::getRoot() const
{
    return root;
}

template<class T>
void BST<T>::insert(const T &data)
{   
    BSTNode<T> *newNode;
	newNode = new BSTNode<T>(data,NULL,NULL);

    
    if(!root){
   		root = newNode;	
    }
    else{
    	insert_helper(root,newNode);
    }
}


template <class T>
void BST<T>::remove(const T &data)
{
    /*
    std::cout<< "HERE COMES JOHHNY FOR = "<< data << std::endl;
    */

   
    
    BSTNode <T> *node;
	node = find(data);
    
    if(node){helper_remove(node);}
    
}

template <class T>
BSTNode<T> *BST<T>::find(const T &data)
{
    return helper_find(root,data);
}

template<class T>
void BST<T>::balanceTree()
{   
    if(root){
    	
    	std::vector<T> v;
    	construct_vector(root,v);
        
    	
        destruct(root);
    	root = NULL;
    	
    	helper_balance(0, v.size()-1,v);
        
    }
}

template<class T>
bool BST<T>::isLeaf(BSTNode<T> *node)
{
    
    if(node && !(node->right) && !(node->left)){
        	return 1;
    }
    else{
    	return 0;
    }
}

template<class T>
int BST<T>::nodeDepth(BSTNode<T> *node)
{   
    if(find(node->data)){
        int depth = 0;
    
        BSTNode<T> *cur = root;
        while(cur!=node){
            depth ++;
            if(node->data < cur->data){
                cur = cur->left;
            }
            else{
                cur = cur->right;
            }
        }
    return depth;
    }
    else{
    return -1;
    }
}

template<class T>
int BST<T>::nodeHeight(BSTNode<T> *node)
{
	
    return helper_height(node,0)-1;
}

template <class T>
void BST<T>::printInorder()
{
	if(getRoot()){
		std::cout << "{" << std::endl;
		helper_print(root);
		std::cout << "}" << std::endl;
        
	}
	else{
		std::cout << "{}" << std::endl;
	}
    
}

template <class T>
void BST<T>::printReverseInorder()
{
	
    if(getRoot()){
		std::cout << "{" << std::endl;
		helper_reverse_print(root);
		std::cout << "}" << std::endl;
	}
	else{
		std::cout << "{}" << std::endl;
	}
}

#endif //BST_HPP
