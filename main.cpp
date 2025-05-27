#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

string FileName = "Clients.txt";

enum enMenueScreen
{
    ShowClientData = 1,
    AddNewClient = 2,
    DeleteClient = 3,
    UpdateClientInfo = 4,
    FindClient = 5,
    Transactions = 6,
    Exit = 7
};

enum enTransactionMenueScreen
{
    Deposite = 1,
    Withdraw = 2,
    TotalBalance = 3,
    MainMenue = 4
};

struct strClientData
{
    string AccountNumber;
    string PinCode;
    string AccountName;
    string PhoneNumber;
    double AccountBalance;
    bool MarkForDelete = false;
};

void PerformTransationMenueOptions(enTransactionMenueScreen TransactionMenueOption);

vector<string> SplitEachWordInVector(string S1, string Seperator)
{
    vector<string> vString;
    string word;
    size_t position = 0;
    while ((position = S1.find(Seperator)) != std::string::npos)
    {
        word = S1.substr(0, position);

        if (word != "")
        {
            vString.push_back(word);
        }

        S1.erase(0, position + Seperator.length());
    }
    if (S1 != "")
    {
        vString.push_back(S1);
    }
    return vString;
}

strClientData ConvertLineToRecord(string Line, string Separator = "#//#")
{
    strClientData ClientData;
    vector<string> vString;

    vString = SplitEachWordInVector(Line, Separator);

    ClientData.AccountNumber = vString[0];
    ClientData.PinCode = vString[1];
    ClientData.AccountName = vString[2];
    ClientData.PhoneNumber = vString[3];
    ClientData.AccountBalance = stod(vString[4]);

    return ClientData;
}

vector<strClientData> LoadClientDataFromFile(string FileName)
{
    vector<strClientData> vClients;
    fstream Myfile;
    Myfile.open(FileName, ios::in);

    if (Myfile.is_open())
    {
        string Line;
        strClientData Client;

        while (getline(Myfile, Line))
        {
            Client = ConvertLineToRecord(Line);
            vClients.push_back(Client);
        }
        Myfile.close();
    }

    return vClients;
}

void PrintAllClientsData()
{
    vector<strClientData> vClients = LoadClientDataFromFile(FileName);

    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Clients";
    cout << "\n------------------------------------------------------------";
    cout << "-------------------------------------------------\n"
         << endl;
    cout << "| " << setw(15) << left << "Account Name";
    cout << "| " << setw(10) << left << "Pin Code";
    cout << "| " << setw(40) << left << "Client Name";
    cout << "| " << setw(12) << left << "Phone Number";
    cout << "| " << setw(12) << left << "Balance";
    cout << "\n------------------------------------------------------------";
    cout << "-------------------------------------------------\n"
         << endl;

    for (strClientData &it : vClients)
    {

        cout << "| " << setw(15) << left << it.AccountNumber;
        cout << "| " << setw(10) << left << it.PinCode;
        cout << "| " << setw(40) << left << it.AccountName;
        cout << "| " << setw(12) << left << it.PhoneNumber;
        cout << "| " << setw(12) << left << it.AccountBalance;

        cout << endl;
    }
    cout << "-------------------------------------------------------------";
    cout << "------------------------------------------------\n\n\n";
}

string ConvertClientDataOnOneLine(strClientData ClientData, string Seperator = "#//#")
{
    string ClientRecord;

    ClientRecord += ClientData.AccountNumber + Seperator;
    ClientRecord += ClientData.PinCode + Seperator;
    ClientRecord += ClientData.AccountName + Seperator;
    ClientRecord += ClientData.PhoneNumber + Seperator;
    ClientRecord += to_string(ClientData.AccountBalance);

    return ClientRecord;
}

strClientData ReadNewClient()
{
    strClientData ClientData;

    cout << "==================\n";
    cout << "Adding New Client\n";
    cout << "==================\n";

    cout << "\nEnter Account Number? ";
    getline(cin >> ws, ClientData.AccountNumber);

    cout << "Enter Pin Code? ";
    getline(cin, ClientData.PinCode);

    cout << "Enter Account Name? ";
    getline(cin, ClientData.AccountName);

    cout << "Enter Phone Number? ";
    getline(cin, ClientData.PhoneNumber);

    cout << "Enter Account Balance? ";
    cin >> ClientData.AccountBalance;

    return ClientData;
}

void AddClientToFile(string FileName, string LineRecord)
{
    fstream Myfile;
    Myfile.open(FileName, ios::out | ios::app);

    if (Myfile.is_open())
    {
        Myfile << LineRecord << endl;
        Myfile.close();
    }
}

void AddNewClientt()
{
    strClientData Client = ReadNewClient();
    string Line = ConvertClientDataOnOneLine(Client);
    AddClientToFile(FileName, Line);
}

void AddClients()
{
    char AddMore = 'Y';
    do
    {
        system("cls");
        // cout << "Adding New Client:\n\n";

        AddNewClientt();
        cout << "\nClient Added Succ, Do You Want To Add More? (y/n)  ";
        cin >> AddMore;

    } while (toupper(AddMore) == 'Y');
}

short ReadOptionsFromUser()
{
    short Options;
    cout << "Choose What do you want to do? [1 to 7]? ";
    cin >> Options;

    return Options;
}

short ReadOptionFromUserForTransationScreen()
{
    short Option;
    cout << "Choose What do you want to do? [1 to 4]? ";
    cin >> Option;

    return Option;
}

bool FindClientByAccountNumber(string AccountNumber, strClientData &Client, vector<strClientData> vClients)
{
    for (strClientData it : vClients)
    {
        if (it.AccountNumber == AccountNumber)
        {
            Client = it;
            return true;
        }
    }
    return false;
}

void PrintClientByAccountNumber(strClientData Client)
{
    cout << "\nThe following are the client details:\n\n";

    cout << "============================================\n";
    cout << "Account Number: " << Client.AccountNumber << endl;
    cout << "Pin Code: " << Client.PinCode << endl;
    cout << "Account Name: " << Client.AccountName << endl;
    cout << "Phone Number: " << Client.PhoneNumber << endl;
    cout << "Account Balance: " << Client.AccountBalance << endl;
    cout << "============================================\n";
    cout << endl;
}

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector<strClientData> &vClients) // by ref عشان تتعدل في فانكشن الديليت
{
    for (strClientData &it : vClients) //?????by ref
    {
        if (it.AccountNumber == AccountNumber)
        {
            it.MarkForDelete = true;
            return true;
        }
    }
    return false;
}

vector<strClientData> SaveClientDataToFile(string FileName, vector<strClientData> vClients)
{
    fstream Myfile;
    Myfile.open(FileName, ios::out); // overWrite

    string Line;

    if (Myfile.is_open())
    {

        for (strClientData it : vClients)
        {
            if (it.MarkForDelete == false) // هنكتب اللي مش متعلم عليه
            {
                Line = ConvertClientDataOnOneLine(it);
                Myfile << Line << endl;
            }
        }
    }

    Myfile.close();

    return vClients;
}

bool DeleteClientByAccountNumber(string AccountNumber, vector<strClientData> &vClients) // by ref عشان تتعدل فالميين
{
    strClientData Client;
    char Answer = 'n';

    if (FindClientByAccountNumber(AccountNumber, Client, vClients))
    {
        PrintClientByAccountNumber(Client);

        cout << "Are You Sure Do you want to delete this client? (n/y)? ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
            SaveClientDataToFile(FileName, vClients);

            cout << "\nClient Deleted Successfuly " << endl;
            return true;
        }
    }
    else
    {
        cout << "\nClient Not Found" << endl;
        return false;
    }
}

string ReadAccountNumber()
{
    string AccountNumber;
    cout << "Please Enter Account Number? ";
    cin >> AccountNumber;

    return AccountNumber;
}

strClientData ChangeClientRecord(string AccountNumber)
{
    strClientData ClientData;

    ClientData.AccountNumber = AccountNumber;

    cout << "Enter Pin Code? ";
    getline(cin >> ws, ClientData.PinCode);

    cout << "Enter Account Name? ";
    getline(cin, ClientData.AccountName);

    cout << "Enter Phone Number? ";
    getline(cin, ClientData.PhoneNumber);

    cout << "Enter Account Balance? ";
    cin >> ClientData.AccountBalance;

    return ClientData;
}

bool UpdateClientByAccountNumber(string AccountNumber, vector<strClientData> &vClients)
{
    strClientData Client;
    char Answer = 'n';

    if (FindClientByAccountNumber(AccountNumber, Client, vClients))
    {
        PrintClientByAccountNumber(Client);

        cout << "Are you sure you want to Update Client Information? (y/n) ";
        cin >> Answer;

        if (Answer == 'Y' || Answer == 'y')
        {
            for (strClientData &it : vClients)
            {
                if (it.AccountNumber == AccountNumber)
                {
                    it = ChangeClientRecord(AccountNumber);
                    break;
                }
            }
            SaveClientDataToFile(FileName, vClients);

            cout << "\nClient Information Updated Successfully" << endl;
            return true;
        }
    }
    else
    {
        cout << "\nSorry Client not found" << endl;
        return false;
    }
}

void PrintClientCard(strClientData Client)
{

    cout << "\n\nThe following are the client details: \n\n";
    cout << "=========================================\n";
    cout << "Account Number: " << Client.AccountNumber;
    cout << "\nPin Code: " << Client.PinCode;
    cout << "\nName: " << Client.AccountName;
    cout << "\nPhone: " << Client.PhoneNumber;
    cout << "\nAccount Balance: " << Client.AccountBalance << endl;
    cout << "=========================================\n";
}

bool FindClientByAccountNumber(string AccountNumber, strClientData &Client)
{
    vector<strClientData> vClients = LoadClientDataFromFile(FileName);
    bool FindOrNot;

    for (strClientData it : vClients)
    {
        if (it.AccountNumber == AccountNumber)
        {
            Client = it;
            return true;
        }
    }
    return false;
}

int ExitFromProgram()
{
    cout << "\n======================================" << endl;
    cout << "             Program Ends :-)           " << endl;
    cout << "========================================" << endl;
    return 0;
}

void PerformMainMenueOptions(enMenueScreen MainMenueOption);

void MainMenueSecreen()
{
    system("cls");
    cout << "===============================================" << endl;
    cout << "===============================================" << endl;
    cout << "               Main Menue Screen               " << endl;
    cout << "===============================================" << endl;
    cout << "===============================================" << endl;
    cout << "          [1] Show Client List.                " << endl;
    cout << "          [2] Add New Client.                  " << endl;
    cout << "          [3] Delete Client.                   " << endl;
    cout << "          [4] Update Client Info.              " << endl;
    cout << "          [5] Find Client.                     " << endl;
    cout << "          [6] Transactions.                    " << endl;
    cout << "          [7] Exit.                            " << endl;
    cout << "===============================================" << endl;
    cout << "===============================================" << endl;

    PerformMainMenueOptions((enMenueScreen)ReadOptionsFromUser());
}

void TransactionMenueScreen()
{
    system("cls");
    cout << "===============================================" << endl;
    cout << "            Tansactions Menue Screen           " << endl;
    cout << "===============================================" << endl;
    cout << "              [1] Deposite.                    " << endl;
    cout << "              [2] Withdraw.                    " << endl;
    cout << "              [3] Total Balances.              " << endl;
    cout << "              [4] Main Menue.                  " << endl;
    cout << "===============================================" << endl;

    PerformTransationMenueOptions((enTransactionMenueScreen)ReadOptionFromUserForTransationScreen());
}

void GoBackToMainMenue()
{
    cout << "\nPress Any Key To Go Back To Main Menue...";
    system("pause>0");
    MainMenueSecreen();
}

void GoBackToTransactionMenue()
{
    cout << "\nPress Any key To Go Back To Transation Menue...";
    system("pause>0");
    TransactionMenueScreen();
}

void ShowAddNewClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "       Add New Clients Secreen       \n";
    cout << "-------------------------------------\n";
    AddClients();
}

void ShowDeleteClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "       Delete Client Secreen         \n";
    cout << "-------------------------------------\n";
    vector<strClientData> vClients = LoadClientDataFromFile(FileName);
    string AccountNumber = ReadAccountNumber();
    DeleteClientByAccountNumber(AccountNumber, vClients);
}

void ShowUpdateClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "       Update Client Secreen         \n";
    cout << "-------------------------------------\n";
    vector<strClientData> vClients = LoadClientDataFromFile(FileName);
    string AccountNumber = ReadAccountNumber();
    UpdateClientByAccountNumber(AccountNumber, vClients);
}

void ShowFindClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "       Find Client Secreen           \n";
    cout << "-------------------------------------\n";
    vector<strClientData> vClients = LoadClientDataFromFile(FileName);
    string AccountNumber = ReadAccountNumber();
    strClientData Client;

    if (FindClientByAccountNumber(AccountNumber, Client))
    {
        PrintClientCard(Client);
    }
    else
    {
        cout << "Client Not Found\n";
    }
}

void PerformMainMenueOptions(enMenueScreen MainMenueOption)
{
    switch (MainMenueOption)
    {

    case enMenueScreen::ShowClientData:

        system("cls");
        PrintAllClientsData();
        GoBackToMainMenue();
        break;

    case enMenueScreen::AddNewClient:

        system("cls");
        ShowAddNewClientScreen();
        GoBackToMainMenue();
        break;

    case enMenueScreen::DeleteClient:
        system("cls");
        ShowDeleteClientScreen();
        GoBackToMainMenue();
        break;

    case enMenueScreen::UpdateClientInfo:

        system("cls");
        ShowUpdateClientScreen();
        GoBackToMainMenue();
        break;

    case enMenueScreen::FindClient:

        system("cls");
        ShowFindClientScreen();
        GoBackToMainMenue();
        break;

    case enMenueScreen::Transactions:

        system("cls");
        TransactionMenueScreen();
        GoBackToTransactionMenue();
        break;

    case enMenueScreen::Exit:

        system("cls");
        ExitFromProgram();
    }
}

bool DepositeBalanceToClientByAccountNumber(string AccountNumber, double Amount, vector<strClientData> vClients)
{
    char Answer = 'n';

    cout << "\n\nAre you sure you want to make this transaction? y/n ? ";
    cin >> Answer;

    if (Answer == 'y' || Answer == 'Y')
    {
        for (strClientData it : vClients)
        {
            if (it.AccountNumber == AccountNumber)
            {
                it.AccountBalance += Amount;
                SaveClientDataToFile(FileName, vClients);
                cout << "\n\nDone Successfuly New Balance is " << it.AccountBalance << endl;

                return true;
            }
        }
    }
    else
    {
        return false;
    }
}

void PrintClientRecordBalanceLine(strClientData Client)
{
    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(40) << left << Client.AccountName;
    cout << "| " << setw(12) << left << Client.AccountBalance;
}

void ShowTotalBalances()
{
    vector<strClientData> vClients = LoadClientDataFromFile(FileName);
    cout << "\n\t\t\t\tBalances List (" << vClients.size() << ") Clients.\n";
    cout << "-----------------------------------------------------------";
    cout << "----------------------------------------------------\n\n";

    cout << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Balance";

    cout << "\n-----------------------------------------------------------";
    cout << "----------------------------------------------------\n\n";

    double TotalBalance = 0;

    if (vClients.size() == 0)
    {
        cout << "\t\t\tNo Clients Availabla is the system";
    }
    else
    {
        for (strClientData Client : vClients)
        {
            PrintClientRecordBalanceLine(Client);
            TotalBalance += Client.AccountBalance;
            cout << endl;
        }
    }

    cout << "\n-----------------------------------------------------------";
    cout << "----------------------------------------------------\n\n";
    cout << "\t\t\t\tTotal Balances " << TotalBalance << endl;
}

void ShowTotalBalancesScreen()
{
    ShowTotalBalances();
}

void ShowDepositeScreen()
{
    cout << "\n--------------------------------\n";
    cout << "       Deposite Screen            \n";
    cout << "----------------------------------\n";

    string AccountNumber = ReadAccountNumber();
    strClientData Client;
    vector<strClientData> vClients = LoadClientDataFromFile(FileName);

    while (!FindClientByAccountNumber(AccountNumber, Client, vClients))
    {
        cout << "Client with " << AccountNumber << " does not exist.\n";

        AccountNumber = ReadAccountNumber();
    }

    PrintClientByAccountNumber(Client);

    double Amount = 0;
    char Answer = 'n';

    cout << "\nPlease Enter deposite amount? ";
    cin >> Amount;

    // كان ممكن ابعت الكلاينت علي طول بس by ref
    DepositeBalanceToClientByAccountNumber(AccountNumber, Amount, vClients);
}

void ShowWithdrawScreen()
{
    cout << "\n--------------------------------\n";
    cout << "       Withdraw Screen            \n";
    cout << "----------------------------------\n";

    string AccountNumber = ReadAccountNumber();
    strClientData Client;
    vector<strClientData> vClients = LoadClientDataFromFile(FileName);

    while (!FindClientByAccountNumber(AccountNumber, Client, vClients))
    {
        cout << "Client with " << AccountNumber << " does not exist.\n";

        AccountNumber = ReadAccountNumber();
    }

    PrintClientByAccountNumber(Client);

    double Amount = 0;
    char Answer = 'n';

    cout << "\nPlease Enter withdraw amount? ";
    cin >> Amount;

    while (Amount > Client.AccountBalance)
    {
        cout << "\nAmount Exceeds The Balance" << endl;
        cout << "enter another amount ";
        cin >> Amount;
    }

    Amount *= -1;

    DepositeBalanceToClientByAccountNumber(AccountNumber, Amount, vClients);
}

void PerformTransationMenueOptions(enTransactionMenueScreen TransactionMenueOption)
{
    switch (TransactionMenueOption)
    {
    case enTransactionMenueScreen::Deposite:
        system("cls");
        ShowDepositeScreen();
        GoBackToTransactionMenue();
        break;

    case enTransactionMenueScreen::Withdraw:
        system("cls");
        ShowWithdrawScreen();
        GoBackToTransactionMenue();
        break;

    case enTransactionMenueScreen::TotalBalance:
        system("cls");
        ShowTotalBalancesScreen();
        GoBackToTransactionMenue();
        break;
    case enTransactionMenueScreen::MainMenue:
        MainMenueSecreen();
        break;
    }
}

int main()
{
    MainMenueSecreen();

    return 0;
}