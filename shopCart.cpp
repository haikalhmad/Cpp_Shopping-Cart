#include <iostream>
#include <iomanip>
#include <algorithm>

//Catalog Variable
const int productNumber[20] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
const double productPrice[20] = {5.5, 1, 0.5, 1, 2, 6, 7.5, 8, 1, 1, 1, 1.5, 1.5, 2.5, 8.5, 10, 2, 2, 1.5, 1.5},
	     discountPrice[20] = {0.2, 0, 0, 0, 0, 0.2, 0.2, 0.2, 0, 0, 0, 0, 0, 0.1, 0.3, 0.4, 0, 0, 0, 0},
	     tierDiscountPrice[3] = {0.02, 0.04, 0.05};
const std::string productName[20] = {"Pasta", "Rice", "Soup", "Bread", "Fried Rice", "Chicken", "Steak", "Lamb", "French Fries", 
				    "Vegetables", "Water", "Orange Juice", "Watermelon Juice", "Soft Drinks", "Milkshake", "Beer", 
				    "Hot Tea", "Coffee", "Ice Lemon Tea", "Apple Juice"};

//Cart Variable
int numCart[100], quantityCart[100], counterCart = 0;
double priceCart[100];
std::string detailCart[100], pNameCart[100];

//Add to cart function
void addToCart() {
    //Variable for user input
    int pNum, qNum;
    std::string detail;

    //Input product number
    std::cout << std::endl << "Enter the Product Number (1-20): ";
    std::cin >> pNum;
    while(pNum < 1 || pNum > 20){
	std::cout << "Invalid Product Number! Please refer to Catalog." << std::endl;
	std::cin.clear();
	std::cout << "Enter the Product Number (1-20): ";
	std::cin >> pNum;
    } numCart[counterCart] = pNum;
    pNameCart[counterCart] = productName[pNum - 1]; //Find the name of product based on product number.

    //Input quantity number
    std::cout << "Enter Quantity: ";
    std::cin >> qNum;
    while(qNum < 1){
	std::cout << "Invalid Quantity! Please enter at least 1." << std::endl;
	std::cin.clear();
	std::cout << "Enter Quantity: ";
	std::cin >> qNum;
    } quantityCart[counterCart] = qNum;
    priceCart[counterCart] = productPrice[pNum - 1] * qNum; //Find the price of product and multiply with quantity.

    //Input additional details
    std::cout << "Enter any additional details: ";
    std::cin.ignore(256, '\n');
    std::getline(std::cin, detail);
    detailCart[counterCart] = detail;

    counterCart++; //Add to cart array

    std::cout << "Product added to cart successfully." << std::endl;
}

//View and modify cart function
void editCart() {
    //editCart Variable
    int modMenu, modPNum, modQCart;
    std::string modDCart;
    
    do{
	//bool varibale inside loop to reset to false
	bool found = false;

	//Display cart
	std::cout << std::endl << "\t\t\t" << "Your Cart Details" << std::endl;
	std::cout << std::setw(4) << "Number" << std::setw(20) << "Product Name" << std::setw(16) << "Quantity" << std::setw(25) << "Additional Details" << std::setw(20) << "Product Price" << std::endl;
	std::cout << std::setw(4) << "------" << std::setw(20) << "------------" << std::setw(16) << "--------" << std::setw(25) << "------------------" << std::setw(20) << "-------------" << std::endl;
	for(int i = 0; i < counterCart; i++){
	    std::cout << std::setw(6) << numCart[i] << std::setw(20) << pNameCart[i] << std::setw(16) << quantityCart[i] << std::setw(25) << detailCart[i] << std::setw(20) << priceCart[i] << std::endl;
	}

	//Modify cart
	std::cout << std::endl << "1. Adjust Quantity" << std::endl;
	std::cout << "2. Remove Product" << std::endl;
	std::cout << "3. Update Additional Details" << std::endl;
	std::cout << "4. Exit" << std::endl;
	std::cout << "Please a choose how to modify your cart: ";

	std::cin >> modMenu;
	switch(modMenu){
	    case 1:
		std::cout << "Which product do you wish to adjust the quantity from the cart: ";
		std::cin >> modPNum;
		for(int i = 0; i < counterCart; i++){
		    if(modPNum == numCart[i]){
			std::cout << "Enter a new quantity: ";
			std::cin >> modQCart;
			while(modQCart < 1){
			    std::cout << "Invalid Quantity! Please enter at least 1." << std::endl;
			    std::cin.clear();
			    std::cout << "Enter a new Quantity: ";
			    std::cin >> modQCart;
			}quantityCart[i] = modQCart; //Update quantity
			priceCart[i] = productPrice[modPNum - 1] * modQCart; //Update Price

			found = true; //set flag to true
			break;
		    }
		}
		if(!found)
		    std::cout << "Product does not exist in cart!" << std::endl;
		break;
	    case 2:
		std::cout << "Which product do you wish to delete: ";
		std::cin >> modPNum;
		for(int i = 0; i < counterCart; i++){
		    if(modPNum == numCart[i]) {
			//shift elements in array to the left
			for(int j = i; j < counterCart - 1; j++) {
			    numCart[j] = numCart[j + 1];
			    pNameCart[j] = pNameCart[j + 1];
			    quantityCart[j] = quantityCart[j + 1];
			    detailCart[j] = detailCart[j + 1];
			    priceCart[j] = priceCart[j + 1];
			}
			counterCart--; //Reduce cart counter
			found = true;
			std::cout << "Product has been removed successfully." << std::endl;
			break;
		    }
		}
		if(!found)
		    std::cout << "Product does not exist in cart!" << std::endl;
		break;
	    case 3:
		std::cout << "Which product do you wish to change the details: ";
		std::cin >> modPNum;
		for(int i = 0; i < counterCart; i++){
		    if(modPNum == numCart[i]){
			std::cout << "Enter a new additional detail: ";
			std::cin.ignore(256, '\n');
			std::getline(std::cin, modDCart);
			detailCart[i] = modDCart;

			found = true;
			std::cout << "The product details has been successfully updated." << std::endl;
			break;
		    }
		}
		if(!found)
		    std::cout << "Product does not exist in cart!" << std::endl;
		break;
	    case 4:
		break;
	}
    }while(modMenu != 4);
}

void totalCost(){
    //totalCost() Variables
    double totalPrice = 0, totalDiscount = 0, tierDiscount = 0;

    //Calculate total cost from cart
    for(int i = 0; i < counterCart; i++){
	totalPrice = totalPrice + priceCart[i];
    }
    std::cout << std::endl << "Total Price: RM" << totalPrice << std::endl; //display total cost

    //Calculate total discount from cart
    for(int i = 0; i < counterCart; i++){
	totalDiscount = totalDiscount + (discountPrice[numCart[i]] * priceCart[i]); 
    }
    std::cout << "Total Discount: RM" << totalDiscount << std::endl; //display total discount

    //Calculate tiered discounts based on totalPrice
    if(totalPrice >= 10 && totalPrice <= 15)
	tierDiscount = tierDiscountPrice[0] * totalPrice;
    else if(totalPrice >= 16 && totalPrice <= 24)
	tierDiscount = tierDiscountPrice[1] * totalPrice;
    else if(totalPrice > 25)
	tierDiscount = tierDiscountPrice[2] * totalPrice;
    else
	tierDiscount = 0;

    std::cout << "Tier Discount: RM" << tierDiscount << std::endl; //display tier discount

    totalPrice = totalPrice - totalDiscount - tierDiscount;
    std::cout << "Total after discount: RM" << totalPrice << std::endl;
}

//Function to search cart
void searchCart() {
    //searchCart Variables
    int searchMenu, sPNum, numTemp, qTemp;
    double pTemp;
    std::string sPName, nameTemp, dTemp;

    do{
	//bool variable inside loop to reset to false
	bool found = false; //to identify if product exist in cart

	std::cout << std::endl << "\tSearch Cart Menu" << std::endl;
	std::cout << "1. Search by Number" << std::endl;
	std::cout << "2. Search by Name" << std::endl;
	std::cout << "3. Sort Cart in Ascending Order" << std::endl;
	std::cout << "4. Exit" << std::endl;

	std::cin >> searchMenu;
	switch(searchMenu){
	    case 1:
		std::cout << "Enter Product Number: ";
		std::cin >> sPNum;
		for(int i = 0; i < counterCart; i++){
		    //if user input matches number in cart
		    if(sPNum == numCart[i]){
			std::cout << "Product Number: " << numCart[i] << std::endl;
			std::cout << "Product Name: " << pNameCart[i] << std::endl;
			std::cout << "Quantity: " << quantityCart[i] << std::endl;
			std::cout << "Additional Details: " << detailCart[i] << std::endl;
			std::cout << "Price: " << priceCart[i] << std::endl;

			found = true;
			break;
		    }
		}
		if(!found)
		    std::cout << "Product does not exist in cart!" << std::endl;
		break;
	    case 2:
		std::cout << "Enter Product Name: ";
		std::cin.ignore(256, '\n');
		std::getline(std::cin, sPName);
		//transform user input to lowercase
		std::transform(sPName.begin(), sPName.end(), sPName.begin(), ::tolower);
		//check if user input matches product in cart
		for(int i = 0; i < counterCart; i++){
		    //transform pNameCart to lowercase
		    std::string temp = pNameCart[i]; //put in temporary variable to avoid permanent changes
		    std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
		    if(sPName == temp){
			std::cout << "Product Number: " << numCart[i] << std::endl;
			std::cout << "Product Name: " << pNameCart[i] << std::endl;
			std::cout << "Quantity: " << quantityCart[i] << std::endl;
			std::cout << "Additional Details: " << detailCart[i] << std::endl;
			std::cout << "Price: " << priceCart[i] << std::endl;

			found = true;
			break;
		    }
		}
		if(!found)
		    std::cout << "Product does not exist in cart!" << std::endl;
		break;
	    case 3:
		std::cout << "Sorting cart..." << std::endl;
		//sort in ascending order
		for(int i = 0; i < counterCart; i++) {
		    //if the 1st element is greater than the 2nd element in the array
		    if(numCart[i] > numCart[i + 1]){
			//store the 2nd element in a temporary variable to avoid deleting the
			//element
			numTemp = numCart[i + 1];
			nameTemp = pNameCart[i + 1];
			qTemp = quantityCart[i + 1];
			dTemp = detailCart[i + 1];
			pTemp = priceCart[i + 1];
			//move the 1st element to the second index array
			numCart[i + 1] = numCart[i];
			pNameCart[i + 1] = pNameCart[i];
			quantityCart[i + 1] = quantityCart[i];
			detailCart[i + 1] = detailCart[i];
			priceCart[i + 1] = priceCart[i];
			//move the 2nd element to the first index array
			numCart[i] = numTemp;
			pNameCart[i] = nameTemp;
			quantityCart[i] = qTemp;
			detailCart[i] = dTemp;
			priceCart[i] = pTemp;

			std::cout << "Cart has been sorted successfully. Please [View Cart] from the Main Menu." << std::endl;
			found = true;
			break;
		    }
		}
		if(!found)
		    std::cout << "Your cart is empty! Please [Add to Cart] from the Main Menu." << std::endl;
		break;
	}
    }while(searchMenu != 4);
}

int main() {
    //Main Menu Variable
    int menu;

    //Display Catalog
    std::cout << "\t" << "Welcome to XXX Shop" << std::endl;
    std::cout << "\t    " << "XXX Catalog" << std::endl;
    std::cout << std::setw(6) << "Number" << std::setw(19) << "Product Name" << std::setw(13) << "Price" << std::endl;
    std::cout << std::setw(6) << "------" << std::setw(19) << "------------" << std::setw(13) << "-----" << std::endl;
    for(int i = 0; i < 20; i++){
	std::cout << std::setw(6) << productNumber[i] << std::setw(19) << productName[i] << std::setw(10) << "RM" << productPrice[i] << std::endl;
    }

    do{
	//Display Main Menu
	std::cout << std::endl << "Main Menu" <<std::endl;
	std::cout << "1. Add to Cart" << std::endl;
	std::cout << "2. View and Modify Cart" << std::endl;
	std::cout << "3. Total Cost" << std::endl;
	std::cout << "4. Search Cart" << std::endl;
	std::cout << "5. Exit" << std::endl;
	std::cout << "Please choose a number from the Main Menu: ";

	std::cin >> menu;
	switch(menu){
	    case 1:
		addToCart();
		break;
	    case 2:
		editCart();
		break;
	    case 3:
		totalCost();
		break;
	    case 4:
		searchCart();
		break;
	    case 5:
		break;
	    default:
		std::cout << "Invalid number! Please choose from the Main Menu." << std::endl;
	}

    }while(menu != 5);
    return 0;
}
