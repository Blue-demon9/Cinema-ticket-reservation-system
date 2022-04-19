#include <iostream>
#include <string>
#include <ctime>
#include <stdlib.h>
#include <iomanip>
#include <queue>
using namespace std;

queue <string> feedBack;
float income;
int soldTickets;
bool moviesAdded = false;

void cls(){
	system("cls");
}
string currentTime(){
	const int MAXLEN = 80;
	char s[MAXLEN];
	time_t t = time(0);
	strftime(s,MAXLEN, "%m/%d/%Y",localtime(&t));
	return s;
}
class Genre{
	public:
	struct Movie{
		string name, addDate, showDate;
		int sits;
		float ticketPrice;
		string description;
		Movie* next;
		Movie* head = NULL;
	};
	struct Movie* head=NULL;
	
	bool Search(string name){
		struct Movie* ptr;
	    ptr = head;
	    do{
	    	if(ptr->name == name)
	    		return true;
	    	else 
	    		ptr = ptr->next;
		}while(ptr!= NULL);
		return false;
	}
	void MovieData(string name){
		if(Search(name)){
			struct Movie* ptr = head;
			do{
				if(ptr->name == name){
					cls();
					cout<<"\n\t--------------------------------------------------------------------------------------------"<<endl;
					cout<<"\tName: "<<ptr->name <<endl;
					cout<<"\tAdded on: "<<ptr->addDate <<endl;
					cout<<"\tShow date: "<<ptr->showDate<<endl;
					cout<<"\tSits Left:"<<ptr->sits <<endl;
					cout<<"\tTicket Price: $"<<fixed<<setprecision(2)<<ptr->ticketPrice<<endl;
					cout<<"\tDescription: "<<ptr->description<<endl;
				  	cout<<"\t--------------------------------------------------------------------------------------------\n"<<endl;
				}
				ptr = ptr->next;
			}while(ptr!=NULL);
		}
		else
			cout<<"\n\t\t[!] The Movie wasn't found in our database"<<endl;
	}
	void Insert(string name,string addDate, string showDate, int sits, string description,float ticketPrice){
		struct Movie* new_node = new Movie;
		new_node->name = name;
		new_node->addDate = addDate;
		new_node->showDate = showDate;
		new_node->sits = sits;
		new_node->description = description;
		new_node->ticketPrice = ticketPrice;
		new_node->next = head;
		head = new_node;
	}
	void Recent(){
		struct Movie* ptr;
		ptr = head;
		int count=1;
		while(ptr!=NULL){
			cout<<count<<"."<<ptr->name<<"\t("<<ptr->addDate<<")"<<endl;
			ptr=ptr->next;
			count++;
			if(count==4)
				break;
		}
	}
	string Remove(string name){
		struct Movie* ptr;
		ptr = head;
		while(ptr!=NULL){
			struct Movie* temp;
			temp = ptr->next;
			if(temp->next == NULL){
				if(temp->name == name){
					ptr->next = NULL;
					delete temp;
					return "\n\t\t[*] Deleted Successfully!";
				}
			}
			else if(temp->name == name){
				ptr->next = temp->next;
				delete temp;
				return "\n\t\t[*] Deleted Successfully!";
			}
			else
				ptr = ptr->next;
		}
		return "\t\t[!]The movie wasn't found!";
	}
	void Update(string name){
		struct Movie* ptr;
		ptr = head;
		while(ptr!=NULL){
			if(ptr->name == name){
				int choice;
				MovieData(name);
				cout<<"\t---------Choose what you want to edit---------"<<endl;
				cout<<"\t1.Name\n\t2.Show Date\n\t3.Sits\n\t4.Description\n\t5.Ticket price"<<endl;
				cout<<"\t\t>>";
				cin>>choice;
				switch(choice){
					case 1:
						cout<<"\tNew Name: ";
						cin>>ptr->name;
						break;
					case 2:
						cout<<"\tShow Date: ";
						cin>>ptr->showDate;
						break;
					case 3:
						cout<<"\tSits: ";
						cin>>ptr->sits;
						break;
					case 4:
						cout<<"\tDescription: ";
						cin.ignore();
						getline(cin,ptr->description);
					case 5:
						cout<<"\tTicket Price: ";
						cin>>ptr->ticketPrice;
						break;
					default:
						cout<<"\t[!]Invalid choice!"<<endl;
					}
				cout<<"\t[*]The Data has been changed succesfully"<<endl;
				system("pause > nul");
				break;
			}
			else
				ptr = ptr->next;
		}
	}
	void listNames(){
		cls();
		struct Movie* ptr;
		ptr = head;
		int count=1;
		cout<<"\n\t-------------------------Movies-------------------------"<<endl;
		while(ptr != NULL){
			cout<<"\t\t\t"<<count<<". "<<ptr->name<<endl;
			ptr = ptr->next;
			count++;
		}
		cout<<endl;
	}
	void BuyTicket(){
		string movieName;
		cout<<"\t[+]Enter the name of the movies: ";
		cin>>movieName;
		if(Search(movieName)){
			struct Movie* ptr = head;
			do{
				if(ptr->name == movieName){
					cls();
					MovieData(movieName);
					int n;
					if(ptr->sits > 0){
						cout<<"\n\t[+]How much ticket do you want to buy: ";
						cin>>n;
						if(ptr->sits - n >= 0){
							ptr->sits -= n;
							soldTickets += n;
							income += (ptr->ticketPrice*n);
							cls();
							cout<<"\n\t\t-------------------BILL-----------------------"<<endl;
							cout<<"\t\t\t\tTicket for: "<<ptr->name<<endl;
							cout<<"\t\t\t\tTickets   : "<<n<<endl;
							cout<<"\t\t\t\tPrice     : $"<<ptr->ticketPrice*n<<endl;
							cout<<"\t\t---------------------------------------------------"<<endl;
							system("pause > nul");
							break;
						}
						else{
							cout<<"\n\t\t[!] Sorry there isn't enough sit!"<<endl;
							system("pause > nul");
						}
					}
					else{
						cout<<"\n\t\t[!] Sorry there isn't enough sit!"<<endl;
						system("pause > nul");
					}
				}
				else
					ptr = ptr->next;
			}while(ptr!=NULL);	
		}
		else
			cout<<"\t\t[!]The Movie name you've entered isn't in our database."<<endl;
	}
	void names(){
		struct Movie* ptr;
		ptr = head;
		while(ptr!=NULL){
			string n = ptr->name;
			int m = n.length();
			cout<<setw(m+4)<<setfill(' ')<<ptr->name;
			ptr = ptr->next;
		}
		cout<<endl;
	}
};

Genre action;
Genre romance;
Genre adult;
Genre sci_fi;
Genre animation;

void searchMovie(){
	cls();
	string movieName;
	int choice;
	cout<<"\n\t--------------Search----------------"<<endl;
	cout<<"\tName: ";
	cin>>movieName;
	cout<<"\n\t\t[+] Select Genre"<<endl;
	cout<<"\t1.Action\n\t2.Romance\n\t3.Adult\n\t4.Science Fiction\n\t5.Animation"<<endl;
	cout<<"\n\t>> ";
	cin>>choice;
	switch(choice){
		case 1:
			action.MovieData(movieName);
			break;
		case 2:
			romance.MovieData(movieName);
			break;
		case 3:
			adult.MovieData(movieName);
			break;
		case 4:
			sci_fi.MovieData(movieName);
			break;
		case 5:
			animation.MovieData(movieName);
			break;
	}
	system("pause > nul");
}
void insertMovie(){
	cls();
	string name,addDate,showDate;
	int sits;
	float ticketPrice;
	string description;

	cout<<"\n\n\t--------Enter the information of the movie below----------"<<endl;
	cout<<"\tName: ";
	cin>>name;
	addDate = currentTime();
	cout<<"\tShow Date: ";
	cin.ignore();
	getline(cin, showDate);
	cout<<"\tSits: ";
	cin>>sits;
	cin.ignore();
	cout<<"\tDescription: ";
	getline(cin, description);
	cin.ignore();
	cout<<"\tTicket Price: ";
	cin>>ticketPrice;

	int choice;
	cout<<"\n\n";
	cout<<"\t\t------Choose Genre-------:\n\t1.Action\n\t2.Romance\n\t3.Adult\n\t4.Science Fiction\n\t5.Animation"<<endl;
	cout<<"\t\t\t>> ";
	cin>>choice;
	switch(choice){
		case 1:
			action.Insert(name,addDate,showDate,sits,description,ticketPrice);
			break;
		case 2:
			romance.Insert(name,addDate,showDate,sits,description,ticketPrice);
			break;
		case 3:
			adult.Insert(name,addDate,showDate,sits,description,ticketPrice);
			break;
		case 4:
			sci_fi.Insert(name,addDate,showDate,sits,description,ticketPrice);
			break;
		case 5:
			animation.Insert(name,addDate,showDate,sits,description,ticketPrice);
			break;
		default:
			cout<<"Invalid choice!"<<endl;
	}
}
void listOfMovies(){
	cls();
	cout<<"--------------------------------------------------------------------------------------------------------------------------------"<<endl;
	cout<<"Genre            1            2            3            4            5            6	        7           8          9	"<<endl;
	cout<<"--------------------------------------------------------------------------------------------------------------------------------"<<endl;
	cout<<"Action:   ";
	action.names();
	cout<<"--------------------------------------------------------------------------------------------------------------------------------"<<endl;
	cout<<"Romance:  ";
	romance.names();
	cout<<"--------------------------------------------------------------------------------------------------------------------------------"<<endl;
	cout<<"Adult:    ";
	adult.names();
	cout<<"--------------------------------------------------------------------------------------------------------------------------------"<<endl;
	cout<<"Sci-Fi:   ";
	sci_fi.names();
	cout<<"--------------------------------------------------------------------------------------------------------------------------------"<<endl;
	cout<<"Animation:";
	animation.names();
	cout<<"--------------------------------------------------------------------------------------------------------------------------------\n\n"<<endl;
	system("pause > nul");
}
void deleteMovie(){
	cls();
	// listing
	listOfMovies();
	string movieName;
	int choice;
	cout<<"\n\t--------------Delete----------------"<<endl;
	cout<<"\tName: ";
	cin>>movieName;
	cout<<"\n\t\t[+] Select Genre"<<endl;
	cout<<"\t1.Action\n\t2.Romance\n\t3.Adult\n\t4.Science Fiction\n\t5.Animation"<<endl;
	cout<<"\n\t>> ";
	cin>>choice;
	switch(choice){
		case 1:
			cout<<action.Remove(movieName);
			break;
		case 2:
			cout<<romance.Remove(movieName);
			break;
		case 3:
			cout<<adult.Remove(movieName);
			break;
		case 4:
			cout<<sci_fi.Remove(movieName);
			break;
		case 5:
			cout<<animation.Remove(movieName);
			break;
	}
	system("pause > nul");
}
void updateMovie(){
	cls();
	listOfMovies();
	string choice;
	cout<<"Enter the movie name to Update\n>> ";
	cin>>choice;

	action.Update(choice);
	romance.Update(choice);
	adult.Update(choice);
	sci_fi.Update(choice);
	animation.Update(choice);

}
void displayMovie(){
	cls();
	action.listNames();
	romance.listNames();
	adult.listNames();
	sci_fi.listNames();
	animation.listNames();
}
void buyTicket(){
	cls();
	int choice;
	cout<<"\t\t--------Choose Genre--------\n\t\t\t1.Action\n\t\t\t2.Romance\n\t\t\t3.Adult\n\t\t\t4.Science Fiction\n\t\t\t5.Animation"<<endl;
	cout<<"\t\t--------------------------"<<endl;
	cout<<"\t\t\t>> ";
	cin>>choice;
	switch(choice){
		case 1:
			action.listNames();
			action.BuyTicket();
			break;
		case 2:
			romance.listNames();
			romance.BuyTicket();
			break;
		case 3:
			adult.listNames();
			adult.BuyTicket();
			break;
		case 4:
			sci_fi.listNames();
			sci_fi.BuyTicket();
			break;
		case 5:
			animation.listNames();
			animation.BuyTicket();
			break;
		default:
			cout<<"Invalid input!"<<endl;
	}
}
void sendFeedBack(){
	cls();
	string fdbck,name;
	cout<<"\n\t\t-----------------------FeedBack-----------------------"<<endl;
	cout<<"\n\tName: ";
	cin>>name;
	cout<<"\tFeedBack: ";
	cin.ignore();
	getline(cin,fdbck);
	feedBack.push("From: "+name+"\n"+fdbck);
	cout<<"\n\t\t[*] Feedback has been sent successfuly!"<<endl;
	system("pause > nul");
}
void showFeedBack(){
	cls();
	if(!feedBack.empty()){
		while(!feedBack.empty()){
			cout<<"\t-----------------------------------------------------------------"<<endl;
			cout<<"\t"<<feedBack.front()<<endl;
			cout<<"\t-----------------------------------------------------------------"<<endl;
			system("pause > nul");
			feedBack.pop();
		}
		cout<<"\n\tYou've seen all the feedback!"<<endl;
	}
	else{
		cout<<"\n\t[!]There are no feedbacks yet!\n\n"<<endl;
		system("pause > nul");
	}
	}
void showBills(){
	cls();
	cout<<"\n\t\t---------------Bill----------------"<<endl;
	cout<<"\t\t\tSold Tickets: "<<soldTickets<<endl;
	cout<<"\t\t\tIncome: $"<<setprecision(2)<<fixed<<income<<endl;
	system("pause > nul");
}
void recentMovie(){
	cls();
	action.Recent();
	romance.Recent();
	adult.Recent();
	sci_fi.Recent();
	animation.Recent();
	system("pause > nul");
}
void adminPanel();
void userPanel();
void addManually();
int main(){
	int choice;
	if(!moviesAdded){
		addManually();
		moviesAdded = true;
	}	
	cls();
	
	cout<<endl;
	cout<<"\t	:::       ::: :::::::::: :::        ::::::::   ::::::::  ::::    ::::  :::::::::: "<<endl<<
		"\t	:+:       :+: :+:        :+:       :+:    :+: :+:    :+: +:+:+: :+:+:+ :+:        "<<endl<<
		"\t	+:+       +:+ +:+        +:+       +:+        +:+    +:+ +:+ +:+:+ +:+ +:+        "<<endl<<
		"\t	+#+  +:+  +#+ +#++:++#   +#+       +#+        +#+    +:+ +#+  +:+  +#+ +#++:++#   "<<endl<<
		"\t	+#+ +#+#+ +#+ +#+        +#+       +#+        +#+    +#+ +#+       +#+ +#+        "<<endl<<
		"\t	 #+#+# #+#+#  #+#        #+#       #+#    #+# #+#    #+# #+#       #+# #+#        "<<endl<<
		"\t	  ###   ###   ########## ########## ########   ########  ###       ### ########## "<<endl;
	
	cout<<"\n\t\t-----------------------------Ticket Reservation system---------------------------"<<endl;
	cout<<"\n\t\t\t\t\t\t1.Admin\n\t\t\t\t\t\t2.Customer"<<endl;
	
	cout<<"\n\n\t\t\t\t\t>> ";
	cin>>choice;
	switch(choice){
		case 1:
			adminPanel();
			break;
		case 2:
			userPanel();
			break;
	}
	return 0;
}

void adminPanel(){
	cls();
	int choice;
	cout<<"\n\t------------------Admin Panel------------------"<<endl;
	cout<<"\n\t\t1.Add\n\t\t2.Remove\n\t\t3.Update\n\t\t4.List Movies\n\t\t5.Bills\n\t\t6.Show feedbacks\n\t\t7.Main Menu\n\t\t0.Exit"<<endl;
	cout<<"\n\t\t>> ";
	cin>>choice;
	switch(choice){
		case 1:
			insertMovie();
			break;
		case 2:
			deleteMovie();
			break;
		case 3:
			updateMovie();
			break;
		case 4:
			listOfMovies();
			break;
		case 5:
			showBills();
			break;
		case 6:
			showFeedBack();
			break;
        case 7:
            main();
        case 0:
        	exit(1);
		default:
			cout<<"Invalid input!"<<endl;
	}
	adminPanel();
}
void userPanel(){
	cls();
	int choice;
	cout<<"\n\t-----------------Customer Panel--------------------"<<endl;
	cout<<"\n\t\t1.Search Movie\n\t\t2.Recently Added\n\t\t3.List Movies\n\t\t4.Buy Ticket\n\t\t5.Send Feedback\n\t\t6.Main Menu\n\t\t0.Exit"<<endl;
	cout<<"\n\t\t>> ";
	cin>>choice;
	switch(choice){
		case 1:
			searchMovie();
			break;
		case 2:
			recentMovie();
			break;
		case 3:
			listOfMovies();
			break;
		case 4:
			buyTicket();
			break;
		case 5:
			sendFeedBack();
			break;
		case 6:
			main();
			break;
		case 0:
			exit(1);
		default:
			cout<<"Invalid input"<<endl;
	}
	userPanel();
}
void addManually(){
	/////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////  Action /////////////////////////////////////////////
	string name = "nobody";
	string addDate = "26/03/2021";
	string showDate = "April 29 8:45 PM";
	int Sits = 43;
	float ticketPrice = 23.00;
	string description = " When a Russian crime lord comes after his family, he has to reveal his dark side in this brutally compelling film.";
	action.Insert(name,addDate,showDate,Sits,description,ticketPrice);
	
	name = "infinite";
	addDate = "10/06/2021";
	showDate = "April 30 10:00 PM";
	Sits = 55;
	ticketPrice = 43.00;
	description = "When a Russian crime lord comes after his family, he has to reveal his dark side in this brutally compelling film.";
	action.Insert(name,addDate,showDate,Sits,description,ticketPrice);
	
	
	/////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////  Adult /////////////////////////////////////////////
	name = "Climax";
	addDate = "11/05/2018";
	showDate = "April 28 9:35 PM";
	Sits = 54;
	ticketPrice = 32.00;
	description= "French dancers gather in a remote, empty school building to rehearse on a wintry night.";
	adult.Insert(name,addDate,showDate,Sits,description,ticketPrice);
	
	name = "Blockers";
	addDate = "17/09/2018";
	showDate = "May 12 4:30 PM ";
	Sits = 20;
	ticketPrice = 22.00;
	description= "Three parents try to stop their daughters from losing their virginity on prom night.";
	adult.Insert(name,addDate,showDate,Sits,description,ticketPrice);


	name = "Dreamland";
	addDate = "17/11/2020";
	showDate = "June 8 2:00 PM";
	Sits = 27;
	ticketPrice = 23.00;
	description= "A teen bounty hunter is torn between helping or capturing a seductive fugitive bank robber hiding in his small town during the Great Depression.";
	adult.Insert(name,addDate,showDate,Sits,description,ticketPrice);

	
	name = "Closer";
	addDate = "03/12/2004";
	showDate = "May 14 2:22 PM";
	Sits = 50;
	ticketPrice = 31.50;
	description= "The relationship between two couples starts to crumble after the man from one of the couples engages in an affair with the woman of the other";
	adult.Insert(name,addDate,showDate,Sits,description,ticketPrice);


	////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////  Science Fiction ////////////////////////////////////
	name = "Breach";
	addDate = "18/12/2020";
	showDate = "April 28 4:00 AM";
	Sits = 35;
	ticketPrice = 28.00;
	description = "Earth is suffering an extinction level event, and 300,000 survivors are selected to board a spaceship called the Ark.";
	sci_fi.Insert(name,addDate,showDate,Sits,description,ticketPrice);
	
	name = "Invasion";
	addDate = "26/12/2020";
	showDate = "April 28 8:00 AM";
	Sits = 35;
	ticketPrice = 25.00;
	description = "The action takes place three years after the events of Attraction. Julia (Irina Starshenbaum), who was saved from death with the help of extraterrestrial technologies.";
	sci_fi.Insert(name,addDate,showDate,Sits,description,ticketPrice);
	
	name = "Skylines";
	addDate = "25/10/2017";
	showDate = "April 27 8:00 AM";
	Sits = 30;
	ticketPrice = 22.50;
	description = "Picking up shortly after the previous film, Rose leads the human spaceship fleet against the alien spaceship fleet. ";
	sci_fi.Insert(name,addDate,showDate,Sits,description,ticketPrice);
	
	name = "Tenet";
	addDate = "28/03/2019";
	showDate = "April 28 5:45 PM";
	Sits = 40;
	ticketPrice = 24.50;
	description = "Nolan took more than five years to write the screenplay after deliberating about Tenet's central ideas for over a decade.";
	sci_fi.Insert(name,addDate,showDate,Sits,description,ticketPrice);
	
	name = "Encounter";
	addDate = "03/03/2021";
	showDate = "April 22 5:45 PM";
	Sits = 35;
	ticketPrice = 25.00;
	description = "U.S. Marine Malik Khan has two young boys, Jay and Bobby. At home, Jay and Bobby are living with their mother Piya and their mother's new partner, Dylan.";
	sci_fi.Insert(name,addDate,showDate,Sits,description,ticketPrice);
	
	name = "Finch";
	addDate = "02/10/2020";
	showDate = "April 26 5:00 PM";
	Sits = 35;
	ticketPrice = 25.00;
	description = "Ten years have passed since a massive solar flare destroyed the ozone layer, turning the planet Earth into a largely uninhabitable wasteland ravaged.";
	sci_fi.Insert(name,addDate,showDate,Sits,description,ticketPrice);
	
	name = "Settlers";
	addDate = "18/06/2021";
	showDate = "April 25 5:45 PM";
	Sits = 40;
	ticketPrice = 24.50;
	description = "Nolan took more than five years to write the screenplay after deliberating about Tenet's central ideas for over a decade.";
	sci_fi.Insert(name,addDate,showDate,Sits,description,ticketPrice);
	
	
	name = "Tides";
	addDate = "28/03/2021";
	showDate = "April 24 5:45 PM";
	Sits = 35;
	ticketPrice = 24.50;
	description = "After a global catastrophe wipes out nearly all humanity on Earth, an astronaut named Blake from the Kepler-209 space colony.";
	sci_fi.Insert(name,addDate,showDate,Sits,description,ticketPrice);
	
	
	////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////  Animation /////////////////////////////////////////
	name = "Encanto";
	addDate = "24/11/2021";
	showDate = "April 28 8:35 PM";
	Sits = 40;
	ticketPrice = 25.00;
	description= " The magic of the Encanto has blessed every child in the family with a unique gift -- every child except Mirabel";
	animation.Insert(name,addDate,showDate,Sits,description,ticketPrice);
	
	name = "Soul";
	addDate = "11/10/2020";
	showDate = "April 22 6:35 PM";
	Sits = 30;
	ticketPrice = 23.50;
	description= " A jazz musician, stuck in a mediocre job, finally gets his big break";
	animation.Insert(name,addDate,showDate,Sits,description,ticketPrice);
	
	name = "Megamind";
	addDate = "30/10/2010";
	showDate = "April 24 9:35 PM";
	Sits = 35;
	ticketPrice = 18.00;
	description= " A supervillain named Megamind defeats and kills his enemy. Out of boredom he creates a superhero who becomes evil.";
	animation.Insert(name,addDate,showDate,Sits,description,ticketPrice);
	
	name = "Mulan";
	addDate = "09/03/2020";
	showDate = "April 25 9:20 PM";
	Sits = 30;
	ticketPrice = 22.00;
	description= " A girl disguises as a male warrior and joins the imperial army in order to prevent her sick father from being forced to enlist.";
	animation.Insert(name,addDate,showDate,Sits,description,ticketPrice);

	name = "Luca";
	addDate = "18/06/2021";
	showDate = "April 25 7:00 PM";
	Sits = 45;
	ticketPrice = 25.00;
	description= "Set in a beautiful seaside town on the Italian Riviera, story about one young boy experiencing an unforgettable summer filled with gelato, pasta and endless scooter rides. ";
	animation.Insert(name,addDate,showDate,Sits,description,ticketPrice);

	name = "Abominable";
	addDate = "27/09/2019";
	showDate = "April 26 9:35 PM";
	Sits = 40;
	ticketPrice = 15.00;
	description= " After discovering a yeti, three friends embark on a quest to reunite the creature with his family";
	animation.Insert(name,addDate,showDate,Sits,description,ticketPrice);
	
	name = "UglyDolls";
	addDate = "03/05/2019";
	showDate = "April 27 8:35 PM ";
	Sits = 54;
	ticketPrice = 24.00;
	description= " The free-spirited Moxy and her Ugly Doll friends embark on a journey beyond the comfortable borders of Uglyville.";
	animation.Insert(name,addDate,showDate,Sits,description,ticketPrice);

	name = "Zootropolis";
	addDate = "04/03/2016 ";
	showDate = "April 26 7:35 PM";
	Sits = 35;
	ticketPrice = 28.00;
	description= " When Judy Hops, a rookie officer in the Zootopia Police Department, sniffs out a sinister plot. ";
	animation.Insert(name,addDate,showDate,Sits,description,ticketPrice);
	
	
	
}