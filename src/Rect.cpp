#include "Rect.h"

Rect::Rect(float x, float y, float w, float h){
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h; 
}

bool Rect::Contains(float x1, float y1){
    if ((x1 >= x)&&(x1 <= x + w)) 
    {   
        if ((y1 >= y) && (y <= y + h)){
            return true;
        }
        else{
            return false;
        }
        
    }
    else{
        return false;
    }

}
