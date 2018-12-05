/**
 * a4.cpp
 * Name: Animesh Soni
 * Person number: 50201844
 *
 * All definitions of functions required for A4 are contained in here.
 * Feel free to add more function definitions to this, but you must
 * include at least the required functions.
 *
 * You may only use the following headers:
 *    <algorithm>, <cstring>, <string>, <vector>, <list>, <stack>,
 *    <queue>, <sstream>, "Tag.hpp"
 */

#include "Tag.hpp"
#include <stack>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <sstream>
//#include <iostream>

bool html_is_valid (const std::string& document) {

    std::string temp = document;
    for(int i = 0; i<temp.size(); i++){
        temp.at(i) = tolower(temp.at(i));
        if(temp.at(i)==' ' ){
            int k = i+1;
            while(k < temp.size() && temp.at(k)==' ') {
                temp.erase(temp.begin() + k);
                k++;
            }
        }

    }
    if(temp.substr(0,14)!="<!doctype html"){
        return false;
    }
    bool html_pushed = false;
    bool head_pushed = false;
    bool title_pushed = false;
    bool body_pushed = false;
    //std::cout<<temp<<""<<std::endl;
    std::stack<std::string> openTags;
    for(int i = 0; i<temp.size(); i++){
        if(temp.at(i)!=' '){
            if(temp.at(i)=='<'){
                if(temp.substr(i,14) == "<!doctype html"){
                    openTags.push("<!doctype html>");
                    //std::cout<<"<!doctype html>"<<std::endl;
                }
                else if(temp.at(i+1)!= '/') {
                    if(temp.substr(i, 3)!="<br"){
                        int k = i;
                        int x= 0;
                        while (k < temp.size() && (temp.at(k) != '>' && temp.at(k) != ' ')) {
                            k++;
                            x++;
                        }
                        if(temp.substr(i + 1, x-1) == "html"){
                            if(openTags.top()!="<!doctype html>" || html_pushed == true){
                                return false;
                            }
                            html_pushed = true;
                        }
                        if(temp.substr(i + 1, x-1) == "head"){
                            if(openTags.top()!="html" || head_pushed == true){
                                return false;
                            }
                            head_pushed = true;
                        }
                        if(temp.substr(i + 1, x-1) == "title"){
                            title_pushed = true;
                            if(openTags.top()!="head"){
                                return false;
                            }
                            bool title_empty = false;
                            int a = i + x + 1;
                            while(temp.at(a)!='<'){
                                if(temp.at(a)!=' '){
                                    title_empty = true;
                                }
                                a++;
                            }
                            if(!title_empty){
                                return false;
                            }

                        }
                        if(temp.substr(i + 1, x-1) == "body"){
                            if(openTags.top()!="html" || title_pushed==false || body_pushed==true){
                                return false;
                            }
                            body_pushed = true;
                        }
                        if(temp.substr(i + 1, x-1) == "div"){
                            if(openTags.top()!="body" && openTags.top()!="div"){
                                return false;
                            }
                        }
                        if(temp.substr(i + 1, x-1) == "span"){
                            if(openTags.top()!="body" && openTags.top()!="div" && openTags.top()!="p"){
                                return false;
                            }
                        }
                        if(temp.substr(i + 1, x-1) == "p"){
                            if(openTags.top()!="body" && openTags.top()!="div"){
                                return false;
                            }
                        }
                        openTags.push(temp.substr(i+1, x-1));
                        //std::cout<<"Pushed: "<<temp.substr(i+1, x-1)<<std::endl;
                    }
                    else{
                        if(openTags.top()!="body" && openTags.top()!="p" && openTags.top()!="div"){
                            return false;
                        }
                    }
                }
                else{
                    int k = i;
                    int x = 0;
                    while (k < temp.size() && (temp.at(k) != '>' && temp.at(k)!=' ')) {
                        k++;
                        x++;
                    }
                    std::string closingTag = temp.substr(i+2, x-2);
                    //std::cout<<"to pop: "<<temp.substr(i+2,x-2)<<std::endl;
                    if(closingTag!=openTags.top()){
                        return false;
                    }
                    else{
                        openTags.pop();
                    }
                }
            }
            else if(temp.at(i)=='i' && temp.at(i+1)=='d' && temp.at(i+2) == '='){
                int b = i+4;
                while(temp.at(b)!='"'){
                    if(temp.at(b)==' '){
                        return false;
                    }
                    b++;
                }
            }
        }
    }
    if(openTags.top()!="<!doctype html>"){
        return false;
    }
    else{
        return true;
    }
    //return false;
}

Tag* generate_DOM_tree(const std::string& document) {
    Tag* retVal = nullptr;
    /*Tag* current;
    std::string temp = document;
    for(int i = 0; i<temp.size(); i++) {
        temp.at(i) = tolower(temp.at(i));
        if (document.at(i) == ' ') {
            int k = i + 1;
            while (k < temp.size() && temp.at(k) == ' ') {
                temp.erase(temp.begin() + k);
                k++;
            }
        }

    }
    std::stack<std::string> tags;
    std::stack<std::string> id;
    for(int i = 0; i<temp.size(); i++){
        if(temp.at(i)=='<'){
                int k = i;
                while (temp.at(k) != '>') {
                    k++;
                }
                tags.push(temp.substr(i, k - i));
            }
        }*/

    return retVal;
}


void determine_visible_objects(Tag* const root) {
    if(root == nullptr){
        return;
    }
    std::vector<Tag*> children = root->_children;

    for(int i = 0; i<children.size(); i++){
        determine_visible_objects(children.at(i));
    }

    if(root->_name == "content" || root->_name == "title"){
        root->_displayed = true;
    }

    for(int i = 0; i<children.size(); i++){
        if(children.at(i)->_displayed == true){
            root->_displayed=true;
        }
    }
}
std::string print_visible_elements(Tag* const root, int a){
    if(root == nullptr){
        return "";
    }
    std::string retVal = "";
    if(root->_displayed==true){
        for (int i = 0; i < a; i++) {
            retVal = retVal + " ";
        }
        retVal = retVal + root->_name + "\n";
        if(root->_content!=""){

            for (int i = 0; i < a+2; ++i) {
                retVal = retVal + " ";
            }
            retVal = retVal + root->_content + "\n";
        }
        for(int k = 0; k < root->_children.size(); k++){
            retVal = retVal + print_visible_elements(root->_children.at(k), a+2);
        }
    }
    return retVal;
}


std::string print_visible_elements(Tag* const root) {
    return print_visible_elements(root, 0);
}

Tag* getElementByID(Tag* const root, const std::string& id) {
    Tag* retVal = nullptr;
    if(root!= nullptr && id != "") {
        if (root->_id == id) {
            return root;
        }
        for(int i = 0; i < root->_children.size(); i++){
            if(retVal != nullptr){
                return retVal;
            }
            retVal = getElementByID(root->_children.at(i), id);

        }
    }
    return retVal;
}




