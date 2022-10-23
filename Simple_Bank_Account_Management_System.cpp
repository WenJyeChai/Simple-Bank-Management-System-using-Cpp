#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
using namespace std;
class Bank_Account
{
	int Money_Deposit;
	char type;
	int Account_Number;
	char Account_Holder_Name[100];
public:

	void Log_Statement() const; //done
	void Deposit_Money(int); //done
	void Withdraw_Money(int); //done
	int Show_Money_Deposit() const; //done
	char Show_Bank_Account_Type() const; //done
	int Return_Account_Number() const; //done
	void Display_Account() const; //done
	void Update_Account_Type(); //done
	void Update_Account_Name(); //done
	void Update_Money_Deposit(); //done
	void Create_Bank_Account(); //done
	
};

void Bank_Account::Log_Statement() const 
{
	cout << Account_Number << setw(10) << " " << Account_Holder_Name << setw(10) << " " << type << setw(6) << Show_Money_Deposit() << endl;
}

void Bank_Account::Deposit_Money(int x)
{
	Money_Deposit+=x;
}
void Bank_Account::Withdraw_Money(int x)
{
	Money_Deposit-=x;
}
int Bank_Account::Show_Money_Deposit() const
{
	return Money_Deposit;
}
char Bank_Account::Show_Bank_Account_Type() const
{
	return type;
}
int Bank_Account::Return_Account_Number() const
{
	return Account_Number;
}
void Bank_Account::Display_Account() const
{
	cout << "\n\tBank Account No. : " << Account_Number;
	cout << "\n\tBank Account Holder Name : " << Account_Holder_Name;
	cout << "\n\tType of Bank Account : " << type;
	cout << "\n\tBalance Total Money : " << Money_Deposit;
}
void Bank_Account::Update_Account_Type()
{
	cout << "\n\tBank Account No. : " << Account_Number;
	cout << "\n\tUpdation Type of Bank Acocunt : ";
	cin >> type;
	type = toupper(type);
}
void Bank_Account::Update_Account_Name()
{
	cout << "\n\tBank Account No. : " << Account_Number;
	cout << "\n\tUpdation Bank Account Holder Name : ";
	cin.ignore();
	cin.getline(Account_Holder_Name, 50);
}
void Bank_Account::Update_Money_Deposit()
{
	cout << "\n\tBank Account No. : " << Account_Number;
	cout << "\n\tUpdation Balance Total Money : ";
	cin >> Money_Deposit;
}
void Bank_Account::Create_Bank_Account()
{
	system("CLS");
	cout << "\n\tPlease Enter the Bank_Account No. : ";
	cin >> Account_Number;
	cout << "\n\n\tPlease Enter the Name of the Bank_Account holder : ";
	cin.ignore();
	cin.getline(Account_Holder_Name, 50);
	cout << "\n\tPlease Enter Type of the Bank_Account (C/S) : ";
	cin >> type;
	type = toupper(type);
	cout << "\n\tPlease Enter The Starting Total-Money : ";
	cin >> Money_Deposit;
	cout << "\n\n\tBank_Account Created..";
}


void Write_Bank_Account();
void Display_Specific_Account(int);
void Display_All_Account();

void Delete_Bank_Account(int);
void Money_Deposit_Withdraw(int, int);
void Updation_Bank_Account(int);
int main()
{
	char ch;
	int num;

	do 
	{
		system("CLS");
		cout << "\n\n\t\t!!!!!!!!!!!!!!!!!!!!!!!!!!!!";

		cout << "\t\tBANK MANAGEMENT SYSTEM";
		cout << "\n\t\t!!!!!!!!!!!!!!!!!!!!!!!!!!!!";

		cout << "\t\t    ::MAIN MENU::\n";
		cout << "\n\t\t1. NEW Bank_Account";
		cout << "\n\t\t2. Money_Deposit Total-Money";
		cout << "\n\t\t3. WITHDRAW Total-Money";
		cout << "\n\t\t4. BALANCE ENQUIRY";
		cout << "\n\t\t5. ALL Bank_Account HOLDER LIST";
		cout << "\n\t\t6. CLOSE AN Bank_Account";
		cout << "\n\t\t7. Updation AN Bank_Account";
		cout << "\n\t\t8. EXIT";
		cout << "\n\n\t\tSelect Your Option (1-8): ";
		cin >> ch;
		switch (ch)
		{
		case '1':
			Write_Bank_Account();
			break;
		case '2':
			system("CLS");
			cout << "\n\n\tPlease Enter The Bank_Account No. : "; cin >> num;
			Money_Deposit_Withdraw(num, 1);
			break;
		case '3':
			system("CLS");
			cout << "\n\n\tPlease Enter The Bank_Account No. : "; cin >> num;
			Money_Deposit_Withdraw(num, 2);
			break;
		case '4':
			system("CLS");
			cout << "\n\n\tPlease Enter The Bank_Account No. : "; cin >> num;
			Display_Specific_Account(num);
			break;
		case '5':
			Display_All_Account();
			break;
		case '6':
			system("CLS");
			cout << "\n\n\tPlease Enter The Bank_Account No. : "; cin >> num;
			Delete_Bank_Account(num);
			break;
		case '7':
			system("CLS");
			cout << "\n\n\tPlease Enter The Bank_Account No. : "; cin >> num;
			Updation_Bank_Account(num);
			break;
		case '8':
			system("CLS");
			cout << "\n\n\tThank you";
			break;
		default:cout << "\a";
		}
		cin.ignore();
		cin.get();
	} while (ch != '8');
	return 0;
}

void Write_Bank_Account()
{
	Bank_Account New_Account;
	ofstream output_File;
	output_File.open("Bank_Account.dat", ios::binary | ios::app);
	New_Account.Create_Bank_Account();
	output_File.write(reinterpret_cast<char*> (&New_Account), sizeof(Bank_Account));
	output_File.close();
}
void Delete_Bank_Account(int n)
{
	Bank_Account Account;
	ifstream input_File;
	ofstream output_File;
	input_File.open("Bank_Account.dat", ios::binary);
	if (!input_File)
	{
		cout << "File could not be open !! Press any Key...";
		return;
	}
	output_File.open("Temp.dat", ios::binary);
	input_File.seekg(0, ios::beg);
	while (input_File.read(reinterpret_cast<char*> (&Account), sizeof(Bank_Account)))
	{
		if (Account.Return_Account_Number()!=n)
		{
			output_File.write(reinterpret_cast<char*> (&Account), sizeof(Bank_Account));
		}

	}
	input_File.close();
	output_File.close();
	remove("Bank_Account.dat");
	rename("Temp.dat", "Bank_Account.dat");
	cout << "\n\nRecord Deleted ..";
}
void Display_Specific_Account(int n)
{
	Bank_Account Account;
	bool Flag = false;
	ifstream input_File;
	input_File.open("Bank_Account.dat", ios::binary);
	if (!input_File)
	{
		cout << "File could not be open !! Press any Key...";
		return;
	}
	while (input_File.read(reinterpret_cast<char*> (&Account), sizeof(Bank_Account)))
	{
		if (Account.Return_Account_Number() == n)
		{
			Account.Display_Account();
			Flag = true;
		}

	}
	input_File.close();
	if (Flag == false)
	{
		cout << "\n\n\tBank_Account number does not exist";
	}

}
void Display_All_Account()
{
	system("CLS");
	Bank_Account Account;
	ifstream input_File;
	input_File.open("Bank_Account.dat", ios::binary);
	if (!input_File)
	{
		cout << "File could not be open !! Press any Key...";
		return;
	}
	cout << "\n\n\t\tBank_Account HOLDER LIST\n\n";
	cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!========\n";
	cout << "A/c no.      NAME           Type  Balance\n";
	cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!========\n";
	while (input_File.read(reinterpret_cast<char*> (&Account), sizeof(Bank_Account)))
	{
		Account.Log_Statement();
	}
	input_File.close();
	return;
}

void Updation_Bank_Account(int n)
{
	bool found = false;
	Bank_Account Account;
	fstream File;
	File.open("Bank_Account.dat", ios::binary | ios::in | ios::out);
	if (!File)
	{
		cout << "File could not be open !! Press any Key...";
		return;
	}
	while (!File.eof() && found == false)
	{
		char ch;
		File.read(reinterpret_cast<char*> (&Account), sizeof(Bank_Account));
		if (Account.Return_Account_Number() == n)
		{
			Account.Display_Account();
			cout << "\n\n\t\t!!!!!!!!!!!!!!!!!!!!!!!!!!!!";

			cout << "\t\t Account Updation Option";
			cout << "\n\t\t!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
			cout << "\n\t\t1. Update Account Type";
			cout << "\n\t\t2. Update Account Name";
			cout << "\n\t\t3. Update Account Money";
			cout << "\n\n\t\tSelect Your Option (1-3): ";
			cin >> ch;
			switch (ch)
			{
			case '1':
				Account.Update_Account_Type();
				break;
			case '2':
				Account.Update_Account_Name();
				break;
			case '3':
				Account.Update_Money_Deposit();
				break;
			}
			int pos = (-1) * static_cast<int>(sizeof(Bank_Account));
			File.seekp(pos, ios::cur); //fncallat1353
			File.write(reinterpret_cast<char*> (&Account), sizeof(Bank_Account));
			cout << "\n\n\tRecord Updated";
			found = true;
		}
	}
	File.close();
	if (found == false)
		cout << "\n\n\tRecord Not Found ";
}
void Money_Deposit_Withdraw(int n, int option)
{
	int Amount;
	bool found = false;
	Bank_Account Account;
	fstream File;
	File.open("Bank_Account.dat", ios::binary | ios::in | ios::out);
	if (!File)
	{
		cout << "File could not be open !! Press any Key...";
		return;
	}
	while (!File.eof() && found == false)
	{
		File.read(reinterpret_cast<char*> (&Account), sizeof(Bank_Account));
		if (Account.Return_Account_Number() == n)
		{
			Account.Display_Account();
			if (option == 1)
			{
				cout << "\n\n\tTO Money_DepositSS Total-Money";
				cout << "\n\n\tPlease Enter The Total-Money to be Money_Deposited: ";
				cin >> Amount;
				Account.Deposit_Money(Amount);

			}
			if (option == 2)
			{
				cout << "\n\n\tTO WITHDRAW Total-Money";
				cout << "\n\n\tPlease Enter The Total-Money to be withdraw: ";
				cin >> Amount;
				int bal = Account.Show_Money_Deposit() - Amount;
				if (bal < 0)
					cout << "Insufficience balance";
				else
					Account.Withdraw_Money(Amount);
			}
			int pos = (-1) * static_cast<int>(sizeof(Account));
			File.seekp(pos, ios::cur);//fn1353
			File.write(reinterpret_cast<char*> (&Account), sizeof(Bank_Account));
			cout << "\n\n\tRecord Updated";
			found = true;
		}
	}
	File.close();
	if (found == false)
		cout << "\n\n\tRecord Not Found ";
}