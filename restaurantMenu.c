#include <stdio.h>
#include <string.h>

// Struct to store customer information: 
struct Customer
{
	char name[50]; // stores customers name
	float totalBill; // stores customers total bill
	int totalItems; // Shows the total amount of items on receipt
};

// Function prototypes:
void displayFoodMenu(struct Customer *customer);
void displayDrinkMenu(struct Customer *customer);
void displayDessertMenu(struct Customer *customer);
void viewBill(struct Customer customer);
void checkout(struct Customer *customer);

int main() // start the program:
{
	struct Customer customer; // creating a customer variable using Customer struct
	customer.totalBill = 0.0; // setting the bill at zero
	customer.totalItems = 0; // Stores total number of items ordered
	
	FILE *previousOrders;
	previousOrders = fopen("receipt.txt", "r");

	if(previousOrders != NULL)
	{
		printf("Previous receipt file found.\n");
		fclose(previousOrders);
	}
	else
	{
		printf("No previous receipt found.\n");
	}
	
	int choice; // Variable to store the customers main menu choice 
	
	printf("\n");

	// Keep asking until the user enters a valid username
	do
	{
		
		printf("Customers Name: "); // Prints out the customers name

		fgets(customer.name, sizeof(customer.name), stdin); // Reading the customers name from the keyboard 

		customer.name[strcspn(customer.name, "\n")] = '\0'; // Replacing the newline with '\0'
		
		// Check for blank names
		if(strlen(customer.name) == 0)
		{ 
			printf("\n");
			printf("ERROR: Name cannot be blank! Try again.\n");
			printf("\n");
		}			
	}
	while(strlen(customer.name) == 0);


	// Loop continues until the user chooses option five from main menu 
	do
	{	
		printf("\n");
		printf(" ====== RESTAURANT MAIN MENU ======\n");
		printf("\n");
		printf(" ==== Welcome to Digi Diner! ====\n");
		printf("\n");
		printf("Customer: %s\n", customer.name);
		printf("\n");

		// Display main menu options
		printf("1. Food Menu\n");
		printf("2. Drink Menu\n");
		printf("3. Dessert Menu\n");
		printf("4. View Total Bill\n");
		printf("5. Checkout\n");
		printf("6. Exit\n");
		printf("\n");
		
		// Ask the user their choice
		printf("Enter choice: ");
		scanf("%d", &choice);
		printf("\n");

		// Use switch case to execute menus	
		switch(choice)
		{
			case 1:
				displayFoodMenu(&customer); //Sends the customers address so the bill can be updated
				break;
			case 2:
				displayDrinkMenu(&customer); //Display drink menu
				break;
			case 3:
				displayDessertMenu(&customer); //Display dessert menu
				break;
			case 4:
				viewBill(customer); //Look at current bill
		
				break;
			case 5:
				checkout(&customer); //Begin checkout proccess
				break;
			case 6:
				printf("Thank you for visiting Digi Diner, have a great day %s!\n", customer.name); //Exiting the program
			       	break;
			default:
				printf("ERROR: Invalid choice, try again!\n");
		}
	}
	while(choice != 6);
	return 0;
}

// Display Food Menu:
void displayFoodMenu(struct Customer *customer)
{
	// Array containing all of food names 
	char foodNames[][50] =
	{
		"Compiler Club Sandwich", "Build-a-Byte Pizza", "Firewall Chicken Wings", "Pixel Pointer Pasta with Address Alfredo", "Struct Salad",
	};

	// Matching array containing food prices
	float foodPrices[] =
	{
		14.99, 15.99, 16.99, 18.99, 14.99
	};
	
	// Stores customers food selection and quantity
	int choice;
	int quantity;

	// Stay in the menu until the user chooses option 6
	do
	{
		printf("\n");
		printf(" ====== FOOD MENU ======\n");
		printf("\n");

		// Using if loop to display food menu items along with prices:
		for(int i= 0; i < 5; i++)
		{
			printf("%d. %s - $%.2f\n", i + 1, foodNames[i], foodPrices[i]);
		}		
	
		printf("6. Back to Main Menu\n");	
		printf("\n");
		printf("Enter choice: ");
		scanf("%d",&choice);

		if(choice >= 1 && choice <= 5)
		{
			// Ask how many food items the user wants
			printf("Quantity: ");
			scanf("%d", &quantity);

			if(quantity > 0)
			{
				// Add item price times quantity
				customer->totalBill += foodPrices[choice - 1] * quantity;
				
				// Add quantity to total item count
				customer->totalItems += quantity;

				// Confirming the food was added
				printf("\n");
				printf("%d x %s added to order.\n", quantity, foodNames[choice - 1]);
				printf("\n");
			}
			else
			{
				printf("ERROR: Invalid quantity, try again!\n");
			}
		}
		// Invalid menu option
		else if(choice != 6)
		{
			printf("ERROR: Invalid selection, try again!\n");
		}
	}
	while(choice != 6);

}


// Display Drink Menu:
void displayDrinkMenu(struct Customer *customer)
{
	// Array containing all of drink items
	char drinkNames[][50] =
	{
		"Binary Blast", "Syntax Soda", "Python Punch", "CharCola", "Java Coffee",
	};
	
	// Matching array containing drink prices
	float drinkPrices[] =
	{
		6.99, 7.99, 5.99, 6.99, 8.99
	};

	// Stores customers drink choice and quantity
	int choice;
	int quantity;

	// Stay in the drink menu until user chooses option 6
	do
	{
		printf("\n");
		printf(" ====== DRINK MENU ======\n");
		printf("\n");

		// Using for loop to display drink items and prices
		for(int i= 0; i < 5; i++)
		{	
			printf("%d. %s - $%.2f\n", i + 1, drinkNames[i], drinkPrices[i]);
		}
	
		printf("6. Back to Main Menu\n");
		printf("\n");
	
		// Getting drink choice from user
		printf("Enter choice: ");
		scanf("%d", &choice);

		if(choice >= 1 && choice <= 5)
		{
			// Asking the user the quantity 
			printf("Quantity: ");
			scanf("%d", &quantity);

			// Add selected drink item prices to running bill x quantity
			if(quantity > 0)
			{	
				customer->totalBill += drinkPrices[choice - 1] * quantity;
				customer->totalItems += quantity;

	
				// Confirming item was added
				printf("\n");
				printf("%d x %s added to order.\n", quantity, drinkNames[choice - 1]);
				printf("\n");
			}	
			else
			{	
				printf("ERROR: Invalid quantity, try again!!\n");
			}	
		}
	
		// Invalid menu options
		else if(choice != 6)
		{
			printf("ERROR: Invalid selection, try again!\n");
		}
	}	
	while(choice != 6);
}	


// Display Dessert Menu:
void displayDessertMenu(struct Customer *customer)
{
	// Array containing all of dessert items
	char dessertNames[][50] =
	{
		"Debug Donut", "Binary Brownie", "Raspberry Pi", "Function Funnel Cake", "Terminal Tiramisu",
	};
	
	// Matching array containing all of drink prices
	float dessertPrices[] =
	{
		1.99, 2.99, 3.99, 6.99, 5.99
	};

	// Stores users dessert choice and quantity
	int choice;
	int quantity;

	// Stay in dessert menu until user chooses option 6
	do
	{

		printf("\n");
		printf(" ====== DESSERT MENU ======\n");
		printf("\n");
	
		// Using for loop to display all dessert menu items and prices
		for(int i = 0; i < 5; i++)
		{
			printf("%d. %s - $%.2f\n", i + 1, dessertNames[i], dessertPrices[i]);
		}

		printf("6. Back to Main Menu\n");
		printf("\n");
		// Collecting users choice
		printf("Enter choice: ");
		scanf("%d", &choice);

		if(choice >= 1 && choice <= 5)
		{
			printf("Quantity: ");
			scanf("%d", &quantity);

			// Adding selected item prices to running bill
			// Using the pointer to directly update the customers bill in main()
			if(quantity > 0)
			{

				customer->totalBill += dessertPrices[choice - 1] * quantity;
				customer->totalItems += quantity;

				// Confirming item was added to order
				printf("\n");
				printf("%d x %s added to order.\n", quantity, dessertNames[choice - 1]);
				printf("\n");
			}
			else
			{
				printf("ERROR: Invalid quantity, try again!\n");
			}
		}
		
		// Invalid menu options
		else if(choice != 6)
		{
			printf("ERROR: Invalid selection, try again!\n");
		}
	}
	while(choice != 6);

}

// View Bill:
void viewBill(struct Customer customer)
{
	// Stores users choice to return to the main menu 
	char returnChoice;

	while(1)
	{

		printf("\n");
		printf(" ====== CURRENT BILL ======\n");
		printf("\n");
		printf("Customer: %s\n", customer.name);
		printf("\n");
		printf("Items Ordered: %d\n", customer.totalItems);
		printf("Total Bill: $%.2f\n", customer.totalBill);
		printf("\n");
	
		// Ask user to return to main menu
		printf("Return to Main Menu? (Y/N): ");
		scanf(" %c", &returnChoice);
		
		// Y to return to main menu 
		if(returnChoice == 'Y' || returnChoice == 'y')
		{
			printf("\n");
			printf("Returning to Main Menu...\n");
			return;
		}

		// Stay on bill screen
		else if(returnChoice == 'N' || returnChoice == 'n')
		{
			continue;
		}
		// Validate user input
		else
		{
			printf("ERROR: Enter (Y) for Yes or (N) for No.\n");
		}	
	}
}
// Check-out:
void checkout(struct Customer *customer)
{
	// Make sure the customer has ordered something
	if(customer->totalBill <= 0)
	{
		printf("ERROR: No items have been ordered, Please place an order before checkout.\n");
		printf("\n");

		return;
	}

	// Stores customers payment option
	int paymentChoice;
	// Variable used to confirm to check out
	char confirmCheckout;
	
	printf("\n");
	printf(" ====== CHECKOUT ======\n");
	printf("\n");

	// Display the total amount owed
	printf("Total due: $%.2f\n", customer->totalBill);
	printf("\n");

	// Ask if the user wants to continue with checking out
	do
	{
		printf("WARNING: Are you sure you would like to checkout?\n");
		printf("(Y/N): ");
		scanf(" %c", &confirmCheckout);

		// Display errors for invalid entre
		if(confirmCheckout != 'Y' && confirmCheckout != 'y' && confirmCheckout != 'N' && confirmCheckout != 'n')
		{
			printf("\n");
			printf("ERROR: Enter (Y) for Yes or (N) for No.\n");
			printf("\n");
		}
	}
	while(confirmCheckout != 'Y' && confirmCheckout != 'y' && confirmCheckout != 'N' && confirmCheckout != 'n');

	// If user says no return to the main menu 
	if(confirmCheckout == 'N' || confirmCheckout == 'n')
	{
		printf("\n");
		printf("Returning to Main Menu...\n");
		printf("\n");

		return;
	}

	printf("\n");
	printf(" ==== PAYMENT OPTIONS ====\n");
	printf("\n");
	printf("Receipt will be generated after payment.\n");
	printf("\n");

	// Display payment methods
	printf("1. Cash\n");
	printf("2. Card\n");
	printf("\n");

	// Force user to select either cash or card
	do
	{
		printf("Enter payment option: ");
		scanf("%d", &paymentChoice);

		if(paymentChoice != 1 && paymentChoice != 2)
		{
			printf("\n");
			printf("ERROR: Please select Cash (1) or Card (2).\n");
			printf("\n");
		}
	}
	while(paymentChoice != 1 && paymentChoice != 2);

	// Cash payment option
	if(paymentChoice == 1)
	{
		// Stores the users cash and change
		float cash;
		float change;
		// Variable used to confirm cash
		char confirmCash;

		do
		{
			printf("Enter cash amount: ");
			scanf("%f", &cash);
			printf("\n");
	
			// Display cash amount entered
			printf("You entered: $%.2f\n", cash);

			//Ask for confirmation
			printf("Are you sure you want to pay this amount? (Y/N): ");
			scanf(" %c", &confirmCash);

			// Handle invalid responses
			if(confirmCash != 'Y' && confirmCash != 'y' && confirmCash != 'N' && confirmCash != 'n')
			{
				printf("\n");
				printf("ERROR: Enter (Y) for Yes or (N) for No.\n");
				printf("\n");
			}
		
			// If user enters N, re enter cash amount
			if(confirmCash == 'N' || confirmCash == 'n')
			{
				printf("Try again.");
			}
		}
		while(confirmCash != 'Y' && confirmCash != 'y');
		
		// Verify if enough cash was entered 
		if(cash < customer->totalBill)
		{
			printf("\n");
			printf("ERROR: Not enough cash entered!\n");
			printf("Additonal amount needed: $%.2f\n", customer->totalBill - cash);
			printf("\n");
			
			return;		
		}	
	
		//Calculate change 
		change = cash - customer->totalBill;

		printf("\n");
		printf("Cash payment approved!\n");
		printf("Thank you %s!\n", customer->name);
		printf("Change: $%.2f\n", change);
		printf("\n");
	}	
	else if(paymentChoice == 2)
	{
		// Display card payment approval
		printf("Card payment approved! Thank you %s\n", customer->name);
	}
	
	// Create receipt file
	FILE *receipt = fopen("receipt.txt", "w");

	// Verify file opened successfully
	if(receipt != NULL)
	{	
		// Write receipt information to file
		fprintf(receipt, " ====== DIGI DINER RECEIPT ======\n");
		printf("\n");
		fprintf(receipt, "Customer: %s\n", customer->name);
		fprintf(receipt, "Items Ordered: %d\n", customer->totalItems);
		fprintf(receipt, "Total Bill: $%.2f\n", customer->totalBill);
		fprintf(receipt, "\nThank you for dining with Digi Diner!\n");
		
		// Close file after writing
		fclose(receipt);

		// Display Receipt
		printf(" ====== DIGI DINER RECEIPT ======\n");
		printf("\n");
		printf("Customer: %s\n", customer->name);
		printf("\n");
		printf("Items Ordered: %d\n", customer->totalItems); 
		printf("Total Bill: $%.2f\n", customer->totalBill);
		printf("\n");
		printf("Thank you for dining with us at Digi Diner, have an awesome day!\n");
		printf("\n");
		printf("Receipt saved to receipt.txt\n");	
	}	
	else
	{
		printf("ERROR: Cannot create receipt file.\n");
	}

	// Clear order after successful payment
	customer->totalBill = 0.0;
	customer->totalItems = 0;

}

