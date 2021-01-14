#ifndef CARS213_HPP
#define CARS213_HPP

#include <iostream>
#include <cstdlib>
#include <fstream>

#include "BST.hpp"
#include "CarData.hpp"

// DO NOT CHANGE THIS FILE.

class Cars213
{
    public:
        
        Cars213();
        Cars213(std::string fileName);
        ~Cars213();
        
        void add(std::string modelName, int price);
        void sold(int price);

        void listMostExpensive(int k);
        void listCheapest(int k);
        void priceFilter(int min, int max);

    private:
        // You can add your helper functions here - if necessary
        BSTNode<CarData>* expensive(BSTNode<CarData> *cur){
            if(cur->right){
                return expensive(cur->right);
            }
            else{
                return cur;
            }
        };

        BSTNode<CarData> *cheap(BSTNode<CarData> *cur){
            if(cur->left){
                return cheap(cur->left);
            }
            else{
                return cur;
            }
        };  

        void cheap_print(BSTNode<CarData> *cur){
            
            if(cur){
                cheap_print(cur->left);
                std::cout<< cur->data<< std::endl;
                cheap_print(cur->right); 
            }
        };

        void expensive_print(BSTNode<CarData> *cur){
            
            if(cur){
                expensive_print(cur->right);
                std::cout<< cur->data<< std::endl;
                expensive_print(cur->left); 
            }
        };

        void filter_print(BSTNode<CarData> *cur,CarData min,CarData max){
            
            if(cur){
                
                filter_print(cur->left,min,max);

                if(cur->data >= min && cur->data <= max){
                    std::cout<< cur->data<< std::endl;
                }

                filter_print(cur->right,min,max); 
            }
        };
        
    private:
        BST<CarData> carL;
};

#endif //CARS213_HPP
