#include "pixmap.h" 
#include "stack.h" // for creating a Stack (from my lab 4)


//creating struct of x,y coordinates for use as Stack type
struct Coordinate {

		int x;
		int	y;

		//default ctor
		Coordinate() 	{
				x = y = 0; 
		}

	  //x and y coords
		Coordinate(int a, int b) 	{
				x = a;
				y = b;

		}

};

//function that will act as a paint bucket tool
bool fill(PixMap& image, const Pixel& fillColour, int x, int y) {

		//if coords are outside of the height or width of the image, simply return false
		if (x < 0 || x >= image.width() || y < 0 || y >= image.height()) {

				return false;

		}

		Pixel myPixel = image.getPixel(x, y); //store pixel color at sepcified coords

		//return false if fillColour matches myPixel colour
		if (myPixel == fillColour) {

				return false;

		}

		//creating a Stack of a specified Coordinate
		Stack<Coordinate> myStack;

		Coordinate temp(x, y);

		myStack.push(temp);

		//while myStack has coords
		while (!myStack.isEmpty()) {

		  	//assign coords from the top of myStack to temp coords
				Coordinate coord = myStack.top();

				int tempX = coord.x;
				int tempY = coord.y;

				myStack.pop();

				/*
				if pixel left of myPixel is the same colour as myPixel, 
				it needs to be painted as well,
				and is pushed onto the stack
				*/
				if (tempX > 0 && image.getPixel(tempX - 1, tempY) == myPixel) {

						Coordinate temp(tempX - 1, tempY);
						myStack.push(temp);

				}



				/*
				if pixel right of myPixel is the same colour as myPixel,
				it needs to be painted as well,
				and is pushed onto the stack
				*/
				if (tempX < image.width() - 1 && image.getPixel(tempX + 1, tempY) == myPixel) {

						Coordinate temp(tempX + 1, tempY);
						myStack.push(temp);

				}



				/*
				if pixel above myPixel is the same colour as myPixel,
				it needs to be painted as well,
				and is pushed onto the stack
				*/

				if (tempY >0 && image.getPixel(tempX, tempY - 1) == myPixel) {

						Coordinate temp(tempX, tempY - 1);
						myStack.push(temp);

				}

				/*
				if pixel below of myPixel is the same colour as myPixel,
				it needs to be painted as well,
				and is pushed onto the stack
				*/

				if (tempY < image.height() - 1 && image.getPixel(tempX, tempY + 1) == myPixel) {

						Coordinate temp(tempX, tempY + 1);
						myStack.push(temp);

				}

				//colours the temp Coordinate
				image.setPixel(fillColour, tempX, tempY);

		} // while loop ends when Stack is empty 

		return true;

}